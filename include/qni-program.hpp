#pragma once
#include "./qni.hpp"

namespace qni
{
class ProgramContext
{
  private:
    void (*start)(ConsoleContext *ctx);
};
} // namespace qni
