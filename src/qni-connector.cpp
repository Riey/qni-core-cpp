#include "qni-connector.hpp"

namespace qni
{

namespace connector
{

ConnectorContext::ConnectorContext(
    int id,
    std::shared_ptr<Hub> hub,
    std::shared_ptr<ConsoleContext> ctx,
    ConnectionCallback connection_callback)
    : _id(id), _hub(std::move(hub)), _ctx(std::move(ctx)), _connection_callback(connection_callback)
{
    this->_ctx->append_connection_callback(id, connection_callback);
}

ConnectorContext::~ConnectorContext()
{
    this->_ctx->remove_connection_callback(this->_id);
    this->_hub->on_console_ctx_removed(this->_ctx);
}

void ConnectorContext::update_console_ctx(std::shared_ptr<ConsoleContext> ctx)
{
    this->_ctx->remove_connection_callback(this->_id);
    ctx->append_connection_callback(this->_id, this->_connection_callback);
    this->_hub->on_console_ctx_removed(this->_ctx);
    this->_ctx = std::move(ctx);
}

std::unique_ptr<std::vector<uint8_t>> pack_message(api::ProgramMessage const *msg)
{
    size_t len = msg->ByteSizeLong();
    auto ret = std::make_unique<std::vector<uint8_t>>(len);
    msg->SerializeToArray(&(*ret)[0], static_cast<int>(len));
    return ret;
}

std::unique_ptr<std::vector<uint8_t>> ConnectorContext::process_request(api::ConsoleRequest const &req)
{
    api::ProgramMessage msg;

    auto res = msg.mutable_res();

    switch (req.data_case())
    {
    case api::ConsoleRequest::DataCase::kGETSTATE:
    {
        size_t pos = (size_t)req.get_state();

        if (this->_ctx->need_exit() && pos >= this->_ctx->get_command_count())
        {
            auto err = res->mutable_err();
            *err->mutable_reason() = "program exited";
            err->set_req_type(req.data_case());
        }

        else
        {
            auto arr = res->mutable_ok_get_state();
            this->_ctx->get_commands(arr, pos);
        }

        return pack_message(&msg);
    }

    case api::ConsoleRequest::DataCase::kLOADSTATE:
    {
        auto ctx = this->_hub->get_ctx(req.load_state());

        if (!ctx)
        {
            auto err = res->mutable_err();
            *err->mutable_reason() = "failed to load state";
            err->set_req_type(req.data_case());
        }
        else
        {
            this->_ctx = *ctx;
            res->mutable_ok_empty();
        }

        return pack_message(&msg);
    }

    case api::ConsoleRequest::DataCase::kSHARESTATE:
    case api::ConsoleRequest::DataCase::kSHARESTATEOVERWRITE:
    {
        bool overwrite = req.data_case() == api::ConsoleRequest::DataCase::kSHARESTATEOVERWRITE;
        auto const &key = overwrite ? req.share_state_overwrite() : req.share_state();

        auto ret = this->_hub->insert_ctx(key, this->_ctx, overwrite);

        if (!ret)
        {
            auto err = res->mutable_err();
            *err->mutable_reason() = "failed to share";
            err->set_req_type(req.data_case());
        }

        else
        {
            *res->mutable_ok_share_state() = key;
        }
        return pack_message(&msg);
    }

    case api::ConsoleRequest::DataCase::kDELETESTATE:
    {
        auto ret = this->_hub->erase_ctx(req.delete_state());

        if (!ret)
        {
            auto err = res->mutable_err();
            *err->mutable_reason() = "failed to delete";
            err->set_req_type(req.data_case());
        }

        else
        {
            res->mutable_ok_empty();
        }

        return pack_message(&msg);
    }
    }

    return nullptr;
}

std::unique_ptr<std::vector<uint8_t>> ConnectorContext::recv_msg(const uint8_t *buf, size_t len)
{
    api::ConsoleMessage msg;

    if (!msg.ParseFromArray(buf, static_cast<int>(len)))
    {
        return nullptr;
    }

    if (msg.has_req())
    {
        return this->process_request(msg.req());
    }
    else if (msg.has_res())
    {
        this->_ctx->enter_response(msg.res());
    }

    return nullptr;
}

} // namespace connector
} // namespace qni
