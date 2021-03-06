// SPDX-License-Identifier: Apache-2.0
#include "vm/hostfunc/ethereum/externalCodeCopy.h"

namespace SSVM {
namespace Executor {

ErrCode EEIExternalCodeCopy::body(VM::EnvironmentManager &EnvMgr,
                                  Instance::MemoryInstance &MemInst,
                                  uint32_t AddressOffset, uint32_t ResultOffset,
                                  uint32_t CodeOffset, uint32_t Length) {
  /// Take additional gas of copy.
  if (addCopyCost(EnvMgr, Length) != ErrCode::Success) {
    return ErrCode::CostLimitExceeded;
  }
  evmc_context *Cxt = Env.getEVMCContext();

  /// Get address from memory instance.
  evmc_address Addr;
  if (ErrCode Status = loadAddress(MemInst, Addr, AddressOffset);
      Status != ErrCode::Success) {
    return Status;
  }

  /// Copy code to vector.
  std::vector<uint8_t> Buffer(Length, 0);
  size_t Copied =
      Cxt->host->copy_code(Cxt, &Addr, CodeOffset, &Buffer[0], Length);
  if (Length != Copied) {
    return ErrCode::AccessForbidMemory;
  }

  /// Store to memory instance.
  return MemInst.setBytes(Buffer, ResultOffset, 0, Length);
}

} // namespace Executor
} // namespace SSVM
