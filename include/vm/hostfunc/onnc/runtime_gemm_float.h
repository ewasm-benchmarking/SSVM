// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "onncwasm.h"

namespace SSVM {
namespace Executor {

class ONNCRuntimeGemmFloat : public ONNCWasm<ONNCRuntimeGemmFloat> {
public:
  ONNCRuntimeGemmFloat() : ONNCWasm("ONNC_RUNTIME_gemm_float") {}
  ErrCode body(VM::EnvironmentManager &EnvMgr,
               Instance::MemoryInstance &MemInst, uint32_t RuntimeContextOff,
               uint32_t InAOff, uint32_t InANDim, uint32_t InADimsOff,
               uint32_t InBOff, uint32_t InBNDim, uint32_t InBDimsOff,
               uint32_t InCOff, uint32_t InCNDim, uint32_t InCDimsOff,
               uint32_t OutYOff, uint32_t OutYNDim, uint32_t OutYDimsOff,
               float Alpha, float Beta, uint32_t TransA, uint32_t TransB);
};

} // namespace Executor
} // namespace SSVM
