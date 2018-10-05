#pragma once
#include <qni-api/qni-api.pb-c.h>
#include <vector>
#include <memory>
#include <mutex>
#include <atomic>
#include <functional>
#include <map>

namespace qni
{

Qni__Api__Empty *get_global_empty();

using send_callback_t = std::function<void(const uint8_t *buf, size_t len)>;

class ConsoleContext
{
  private:
    std::vector<Qni__Api__ProgramCommand *> _commands;
    std::map<int, send_callback_t> _send_callbacks;
    std::unique_ptr<Qni__Api__ProgramRequest> _request;
    std::mutex _lock;

  public:
    ~ConsoleContext();
    ConsoleContext();
    ConsoleContext(ConsoleContext const &other) = delete;
    ConsoleContext &operator=(ConsoleContext const &other) = delete;

    void append_command(Qni__Api__ProgramCommand *command);
    void export_command(Qni__Api__ProgramCommandArray &commands, size_t from);
    void export_command_end();

    void append_send_callback(int key, send_callback_t callback);
    void remove_send_callback(int key);
};

} // namespace qni
