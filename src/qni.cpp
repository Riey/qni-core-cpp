#include "qni.hpp"

namespace qni
{

ConsoleContext::ConsoleContext()
    : _request(nullptr)
{
}

ConsoleContext::~ConsoleContext()
{
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
