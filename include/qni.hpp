#pragma once
#include <qni-api/qni-api.pb.h>
#include <vector>
#include <memory>
#include <mutex>
#include <atomic>
#include <functional>
#include <map>

namespace qni
{

using send_callback_t = std::function<void(const uint8_t *buf, size_t len)>;

class ConsoleContext
{
  private:
    std::vector<std::unique_ptr<api::ProgramCommand>> _commands;
    std::map<int, send_callback_t> _send_callbacks;
    std::unique_ptr<api::ProgramRequest> _request;
    std::mutex _lock;

  public:
    ~ConsoleContext();
    ConsoleContext();
    ConsoleContext(ConsoleContext const &other) = delete;
    ConsoleContext &operator=(ConsoleContext const &other) = delete;

    void append_command(std::unique_ptr<api::ProgramCommand> command)
    {
        this->_lock.lock();
        this->_commands.push_back(std::move(command));
        this->_lock.unlock();
    }

    void get_commands(api::ProgramCommandArray *arr, size_t from)
    {
        auto fields = arr->mutable_commands();

        this->_lock.lock();

        auto len = this->_commands.size();
        fields->Reserve(len);

        for (size_t i = from; i < len; i++)
            (*fields[i - from].mutable_data())->CopyFrom(*this->_commands[i]);

        this->_lock.unlock();
    }

    void append_send_callback(int key, send_callback_t callback);
    void remove_send_callback(int key);
};

} // namespace qni
