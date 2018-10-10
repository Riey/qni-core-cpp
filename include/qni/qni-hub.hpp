#pragma once

#include "./qni-console.hpp"
#include <map>
#include <thread>

namespace qni
{
using program_start_t = void (*)(ConsoleContext *ctx);

class Hub
{
  private:
    program_start_t _program_entry;
    std::map<std::string, std::shared_ptr<ConsoleContext>> _shared_ctxs;
    std::atomic_bool _exit_flag;
    std::mutex _shared_lock;
    std::mutex _program_lock;

  public:
    Hub(program_start_t entry);

    void on_console_ctx_removed(std::shared_ptr<ConsoleContext> const &ctx);
    std::shared_ptr<ConsoleContext> start_new_program();

    bool insert_ctx(std::string const &key, std::shared_ptr<ConsoleContext> ctx, bool overwrite);
    bool erase_ctx(std::string const &key);
    std::optional<std::shared_ptr<ConsoleContext>> get_ctx(std::string const &key);

    bool need_exit() const noexcept { return this->_exit_flag; }
    void set_exit() noexcept { this->_exit_flag = true; }
};

} // namespace qni
