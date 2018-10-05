#include "qni-connector.hpp"

namespace qni
{

namespace connector
{

ConnectorContext::ConnectorContext(
    int id,
    std::shared_ptr<Hub> hub,
    std::shared_ptr<ConsoleContext> ctx,
    send_callback_t send_callback)
    : _id(id), _hub(std::move(hub)), _ctx(std::move(ctx)), _send_callback(send_callback)
{
    this->_ctx->append_send_callback(id, send_callback);
}

ConnectorContext::~ConnectorContext()
{
    this->_ctx->remove_send_callback(this->_id);
}

void ConnectorContext::update_console_ctx(std::shared_ptr<ConsoleContext> ctx)
{
    this->_ctx->remove_send_callback(this->_id);
    ctx->append_send_callback(this->_id, this->_send_callback);
    this->_ctx = std::move(ctx);
}

std::unique_ptr<std::string> pack_message(api::ProgramMessage const *msg)
{
    return std::make_unique<std::string>(msg->SerializeAsString());
}

std::unique_ptr<std::vector<uint8_t>> ConnectorContext::process_request(api::ConsoleRequest const &req)
{
    api::ProgramMessage msg;

    auto res = msg.mutable_res();

    switch (req.data_case)
    {
    case api::ConsoleRequest::DataCase::kGETSTATE:
    {
        size_t pos = (size_t)req.get_state();

        res->set_allocated_ok_get_state(&this->_ctx->get_commands());

        this->_ctx->export_command(arr, pos);
        res.ok_get_state = &arr;
        auto buf = pack_message(&msg);
        this->_ctx->export_command_end();

        return buf;
    }

    case QNI__API__CONSOLE_REQUEST__DATA_LOAD__STATE:
    {
        auto ctxs = this->_hub->get_shared_ctxs();

        auto itor = ctxs.find(req.share_state);

        if (itor == ctxs.end())
        {
            this->_hub->get_shared_ctxs_end();
            res.data_case = QNI__API__PROGRAM_RESPONSE__DATA_ERR;
            Qni__Api__ErrorResponse err = QNI__API__ERROR_RESPONSE__INIT;
            err.reason = "failed to load state";
            err.req_type = req.data_case;
            res.err = &err;
            return pack_message(&msg);
        }
        else
        {
            this->_ctx = itor->second;
            this->_hub->get_shared_ctxs_end();
            res.data_case = QNI__API__PROGRAM_RESPONSE__DATA_OK__EMPTY;
            res.ok_empty = get_global_empty();
            return pack_message(&msg);
        }

        break;
    }

    case QNI__API__CONSOLE_REQUEST__DATA_SHARE__STATE:
    case QNI__API__CONSOLE_REQUEST__DATA_SHARE__STATE__OVERWRITE:
    {
        int overwrite = req.data_case == QNI__API__CONSOLE_REQUEST__DATA_SHARE__STATE__OVERWRITE;
        auto ctxs = this->_hub->get_shared_ctxs();

        auto itor = ctxs.find(req.share_state);

        if (!overwrite && itor == ctxs.end())
        {
            this->_hub->get_shared_ctxs_end();
            res.data_case = QNI__API__PROGRAM_RESPONSE__DATA_ERR;
            Qni__Api__ErrorResponse err = QNI__API__ERROR_RESPONSE__INIT;
            err.reason = "failed to insert: already exists";
            err.req_type = req.data_case;
            res.err = &err;
            return pack_message(&msg);
        }
        else
        {
            ctxs.insert_or_assign(req.share_state, this->_ctx);
            this->_hub->get_shared_ctxs_end();
            res.data_case = QNI__API__PROGRAM_RESPONSE__DATA_OK__SHARE__STATE;

            //Shallow copy share state var
            res.ok_share_state = req.share_state;
            return pack_message(&msg);
        }

        break;
    }

    case QNI__API__CONSOLE_REQUEST__DATA_DELETE__STATE:
    {
        auto ctxs = this->_hub->get_shared_ctxs();

        ctxs.erase(req.delete_state);

        this->_hub->get_shared_ctxs_end();

        res.data_case = QNI__API__PROGRAM_RESPONSE__DATA_OK__EMPTY;
        res.ok_empty = get_global_empty();

        return pack_message(&msg);
    }
    }

    return NULL;
}

} // namespace connector
} // namespace qni
