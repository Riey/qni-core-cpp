#pragma once

#include "./qni.hpp"
#include <thread>
#include <map>

namespace qni
{
using program_start_t = void (*)(std::shared_ptr<ConsoleContext> ctx);

class Hub
{
  private:
    program_start_t _new_program;
    std::vector<std::thread> _programs;
    std::map<std::string, std::shared_ptr<ConsoleContext>> _shared_ctxs;
    std::mutex _shared_lock;

  public:
    std::shared_ptr<ConsoleContext> start_new_program()
    {
        auto ctx = std::make_shared<ConsoleContext>();

        this->_programs.push_back(std::thread(this->_new_program, ctx));

        return ctx;
    }

    std::map<std::string, std::shared_ptr<ConsoleContext>> &get_shared_ctxs()
    {
        this->_shared_lock.lock();
        return this->_shared_ctxs;
    }

    void get_shared_ctxs_end()
    {
        this->_shared_lock.unlock();
    }
};

} // namespace qni
