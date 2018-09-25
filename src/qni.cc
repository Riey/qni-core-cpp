#include "qni.h"

namespace qni
{

void ConsoleContext::append_command(api::QniProgramCommand &&command) noexcept
{
  this->_lock.lock();
  this->_commands.push_back(std::move(command));
  this->_lock.unlock();
}

void ConsoleContext::append_command(api::QniProgramCommand const &command) noexcept
{
  this->_lock.lock();
  this->_commands.push_back(command);
  this->_lock.unlock();
}

void ConsoleContext::export_commands(google::protobuf::RepeatedPtrField<api::QniProgramCommand> *commands, std::size_t from) noexcept
{
  this->_lock.lock();
  auto target = this->_commands.size();
  for (std::size_t i = from; i < target; i++)
  {
    commands->AddAllocated(&this->_commands[i]);
  }
  this->_lock.unlock();
}

} // namespace qni
