#pragma once
#include "./api/qni-api.pb.h"
#include <vector>
#include <memory>
#include <mutex>
#include <atomic>
#include <functional>
#include <map>
#include <optional>

namespace qni
{

using send_callback_t = std::function<void(const uint8_t *buf, size_t len)>;
using response_callback_t = std::function<bool(api::ConsoleResponse const &res)>;

typedef struct _ConnectionCallback
{
  send_callback_t send_callback;
} ConnectionCallback;

class ConsoleContext
{
private:
  std::vector<std::unique_ptr<api::ProgramCommand>> _commands;
  std::map<int, ConnectionCallback> _connection_callbacks;
  std::optional<response_callback_t> _response_callback;
  std::atomic_uint32_t _request_tag, _tag;
  std::mutex _response_lock;
  std::mutex _request_lock;
  std::atomic_bool _exit_flag;
  std::mutex _lock;

  void on_send_msg(api::ProgramMessage const &msg);
  void on_accept(uint32_t tag);

public:
  ConsoleContext();
  ConsoleContext(ConsoleContext const &other) = delete;
  ConsoleContext &operator=(ConsoleContext const &other) = delete;

  void append_command(std::unique_ptr<api::ProgramCommand> command);

  void get_commands(api::ProgramCommandArray *arr, size_t from);

  size_t get_command_count() const noexcept;

  void set_exit() noexcept;
  bool need_exit() const noexcept;

  void append_connection_callback(int key, ConnectionCallback callback);
  void remove_connection_callback(int key);

  void enter_response(api::ConsoleResponse const &res);

  void wait_console(api::ProgramMessage const &request_msg, response_callback_t callback);

  uint32_t next_req_tag();
};

} // namespace qni
