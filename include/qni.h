#pragma once
#include <qni-api/qni-api.pb.h>
#include <vector>
#include <memory>
#include <mutex>

namespace qni
{
class ConsoleContext
{
private:
  std::vector<api::QniProgramCommand> _commands;
  std::unique_ptr<api::QniProgramRequest> _request;
  std::mutex _lock;

public:
  void append_command(api::QniProgramCommand &&command) noexcept;
  void append_command(api::QniProgramCommand const &command) noexcept;
  void export_commands(google::protobuf::RepeatedPtrField<api::QniProgramCommand> *commands, std::size_t from) noexcept;
};
} // namespace qni
