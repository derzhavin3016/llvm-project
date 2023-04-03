#ifndef __LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMMCASMINFO_H__
#define __LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMMCASMINFO_H__

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {

class Triple;

class SimMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit SimMCAsmInfo(const Triple &TT);
};

} // end namespace llvm

#endif // __LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMMCASMINFO_H__
