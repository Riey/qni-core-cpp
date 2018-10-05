#pragma once
#include "./qni.hpp"
#include "./qni-hub.hpp"
#include <map>
#include <mutex>

namespace qni
{
namespace connector
{

class ConnectorContext
{
  private:
    int _id;
    send_callback_t _send_callback;
    std::shared_ptr<ConsoleContext> _ctx;
    std::shared_ptr<Hub> _hub;

    std::unique_ptr<std::vector<uint8_t>> process_request(Qni__Api__ConsoleRequest const &req);

    void update_console_ctx(std::shared_ptr<ConsoleContext> ctx);

  public:
    ConnectorContext(
        int id,
        std::shared_ptr<Hub> hub,
        std::shared_ptr<ConsoleContext> ctx,
        send_callback_t send_callback);

    ConnectorContext(ConnectorContext const &other) = delete;
    ConnectorContext(ConnectorContext &&other);

    ~ConnectorContext();

    ConnectorContext &operator=(ConnectorContext const &other) = delete;

    std::unique_ptr<std::vector<uint8_t>> recv_msg(const uint8_t *buf, size_t len);
};

} // namespace connector
} // namespace qni