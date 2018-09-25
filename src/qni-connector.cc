#include "qni-connector.h"

namespace qni
{

api::QniProgramResponse ConnectorContext::process_request(api::QniConsoleRequest const &req) noexcept
{
  api::QniProgramResponse res;

  switch (req.data_case())
  {
  case api::QniConsoleRequest::DataCase::DATA_NOT_SET:
  {
    auto err = res.mutable_prog_res_err();
    err->set_reason("request data is empty!");
    err->set_req_type(req.data_case());
    break;
  }
  case api::QniConsoleRequest::DataCase::kCONREQGETSTATE:
  {
    auto commands = res.mutable_prog_res_ok_get_state()->mutable_commands();
    this->_ctx->export_commands(commands, req.con_req_get_state());
    break;
  }
  case api::QniConsoleRequest::DataCase::kCONREQLOADSTATE:
  {
    this->_shared_lock->lock();

    auto context = this->_shared_contexts->find(
        req.con_req_load_state());

    if (context == this->_shared_contexts->end())
    {
      auto err = res.mutable_prog_res_err();

      err->set_reason("State not found");
      err->set_req_type(req.data_case());
    }
    else
    {
      this->_ctx = context->second;
      res.mutable_prog_res_ok_load_state();
    }

    this->_shared_lock->unlock();
    break;
  }
  case api::QniConsoleRequest::DataCase::kCONREQSHARESTATE:
  {
    this->_shared_lock->lock();

    auto ret = this->_shared_contexts->insert(
        {req.con_req_share_state(), this->_ctx});

    if (ret.second)
    {
      res.mutable_prog_res_ok_share_state();
    }
    else
    {
      auto err = res.mutable_prog_res_err();
      err->set_reason("State is already exists");
      err->set_req_type(req.data_case());
    }

    this->_shared_lock->unlock();
    break;
  }
  }

  return res;
}
} // namespace qni
