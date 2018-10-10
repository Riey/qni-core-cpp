#include "qni/qni-console.hpp"
#include <thread>
#include <chrono>

namespace qni
{

ConsoleContext::ConsoleContext()
    : _exit_flag(false), _tag(0)
{
}

void ConsoleContext::on_send_msg(api::ProgramMessage const &msg)
{
  auto buf = msg.SerializeAsString();

  auto ptr = (uint8_t const *)buf.c_str();
  auto len = buf.length();

  for (const auto &callback : this->_connection_callbacks)
  {
    callback.second.send_callback(ptr, len);
  }
}

void ConsoleContext::on_accept(uint32_t tag)
{
  api::ProgramMessage accept;
  accept.set_accept_res(tag);
  this->on_send_msg(accept);
}

void ConsoleContext::append_command(std::unique_ptr<api::ProgramCommand> command)
{
  this->_lock.lock();
  this->_commands.push_back(std::move(command));
  this->_lock.unlock();
}

void ConsoleContext::get_commands(api::ProgramCommandArray *arr, size_t from)
{

  this->_lock.lock();

  auto len = this->_commands.size();

  arr->mutable_commands()->Reserve(static_cast<int>(len));

  for (size_t i = from; i < len; i++)
    arr->add_commands()->MergeFrom(*this->_commands[i]);

  this->_lock.unlock();
}

size_t ConsoleContext::get_command_count() const noexcept
{
  return this->_commands.size();
}

void ConsoleContext::append_connection_callback(int key, ConnectionCallback callback)
{
  this->_lock.lock();
  this->_connection_callbacks.insert_or_assign(key, callback);
  this->_lock.unlock();
}

void ConsoleContext::remove_connection_callback(int key)
{
  this->_lock.lock();
  this->_connection_callbacks.erase(key);
  this->_lock.unlock();
}

void ConsoleContext::set_exit() noexcept
{
  this->_exit_flag = true;
}

bool ConsoleContext::need_exit() const noexcept
{
  return _exit_flag;
}

void ConsoleContext::enter_response(api::ConsoleResponse const &res)
{
  this->_response_lock.lock();

  if (this->_response_callback && this->_response_callback.value()(res))
  {
    this->on_accept(this->_request_tag);
    this->_request_tag = 0;
    this->_response_callback = {};
  }

  this->_response_lock.unlock();
}

void ConsoleContext::wait_console(api::ProgramMessage const &request_msg, response_callback_t callback)
{
  if (!request_msg.has_req())
    return;

  this->on_send_msg(request_msg);

  this->_request_tag = request_msg.req().tag();

  this->_response_lock.lock();
  this->_response_callback = callback;
  this->_response_lock.unlock();

  while (this->_request_tag != 0)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //TOOD: impl timeout
  }

  this->_request_lock.unlock();
}

uint32_t ConsoleContext::next_req_tag()
{
  return ++this->_tag;
}

} // namespace qni
