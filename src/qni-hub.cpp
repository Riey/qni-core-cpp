#include "qni/qni-hub.hpp"

namespace qni
{

Hub::Hub(program_start_t entry)
    : _program_entry(entry), _exit_flag(false)
{
}

void Hub::on_console_ctx_removed(std::shared_ptr<ConsoleContext> const &ctx)
{
    if (ctx.use_count() <= 2)
    {
        ctx->set_exit();
    }
}

void start_program_helper(program_start_t callback, std::shared_ptr<ConsoleContext> ctx)
{
    callback(ctx.get());

    ctx->set_exit();
}

std::shared_ptr<ConsoleContext> Hub::start_new_program()
{
    auto ctx = std::make_shared<ConsoleContext>();

    auto thrd = std::thread(&start_program_helper, this->_program_entry, ctx);

    thrd.detach();

    return ctx;
}

bool Hub::insert_ctx(std::string const &key, std::shared_ptr<ConsoleContext> ctx, bool overwrite)
{
    auto ret = true;
    this->_shared_lock.lock();
    if (overwrite)
    {
        auto prev = this->_shared_ctxs.insert_or_assign(key, std::move(ctx));

        if (prev.second == false)
        {
            this->on_console_ctx_removed(prev.first->second);
        }
    }
    else
    {
        ret = this->_shared_ctxs.insert({key, std::move(ctx)}).second;
    }
    this->_shared_lock.unlock();
    return ret;
}

bool Hub::erase_ctx(std::string const &key)
{
    bool ret = false;

    this->_shared_lock.lock();

    auto itor = this->_shared_ctxs.find(key);

    if (itor != this->_shared_ctxs.end())
    {
        ret = true;

        do
        {
            auto const &ctx = *itor;
            this->on_console_ctx_removed(ctx.second);

        } while (++itor != this->_shared_ctxs.end());

        this->_shared_ctxs.erase(key);
    }

    this->_shared_lock.unlock();

    return ret;
}

std::optional<std::shared_ptr<ConsoleContext>> Hub::get_ctx(std::string const &key)
{
    auto itor = this->_shared_ctxs.find(key);

    if (itor == this->_shared_ctxs.end())
    {
        return {};
    }

    return itor->second;
}

} // namespace qni
