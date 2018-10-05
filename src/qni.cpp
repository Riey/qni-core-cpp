#include "qni.hpp"
#include "internal/qni-deleter.hpp"

namespace qni
{

Qni__Api__Empty global_empty = QNI__API__EMPTY__INIT;

Qni__Api__Empty *get_global_empty() { return &global_empty; }

ConsoleContext::ConsoleContext()
    : _request(nullptr)
{
}

ConsoleContext::~ConsoleContext()
{
    for (auto command : this->_commands)
    {
        qni_free_prog_com(command);
    }
}

void ConsoleContext::append_command(Qni__Api__ProgramCommand *command)
{
    this->_lock.lock();
    this->_commands.push_back(command);
    this->_lock.unlock();
}

void ConsoleContext::export_command(Qni__Api__ProgramCommandArray &commands, size_t from)
{
    this->_lock.lock();
    auto size = this->_commands.size();
    if (size > from)
    {
        commands.commands = &this->_commands[from];
        commands.n_commands = size - from;
    }
    else
    {
        commands.commands = NULL;
        commands.n_commands = 0;
    }
}
void ConsoleContext::export_command_end()
{
    this->_lock.unlock();
}

void ConsoleContext::append_send_callback(int key, std::function<void(const uint8_t *buf, size_t len)> callback)
{
    this->_lock.lock();
    this->_send_callbacks.insert_or_assign(key, callback);
    this->_lock.unlock();
}

void ConsoleContext::remove_send_callback(int key)
{
    this->_lock.lock();
    this->_send_callbacks.erase(key);
    this->_lock.unlock();
}

} // namespace qni
