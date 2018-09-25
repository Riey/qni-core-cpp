#pragma once
#include "./qni.h"
#include <map>
#include <mutex>

namespace qni
{
class ConnectorContext
{
private:
  std::shared_ptr<ConsoleContext> _ctx;
  std::shared_ptr<std::map<std::string, std::shared_ptr<ConsoleContext>>> _shared_contexts;
  std::shared_ptr<std::mutex> _shared_lock;

public:
  api::QniProgramResponse process_request(api::QniConsoleRequest const &req) noexcept;
};
} // namespace qni
