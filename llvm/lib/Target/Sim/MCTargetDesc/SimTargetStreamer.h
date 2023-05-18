#ifndef __LLVM_LIB_TARGET_SIM_SIMTARGETSTREAMER_H__
#define __LLVM_LIB_TARGET_SIM_SIMTARGETSTREAMER_H__

#include "llvm/MC/MCStreamer.h"

namespace llvm {

class SimTargetStreamer : public MCTargetStreamer {
public:
  SimTargetStreamer(MCStreamer &S);
  ~SimTargetStreamer() override;
};

} // end namespace llvm

#endif // __LLVM_LIB_TARGET_SIM_SIMTARGETSTREAMER_H__
