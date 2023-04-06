#ifndef __LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMINFO_H__
#define __LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMINFO_H__

#include "llvm/MC/MCInstrDesc.h"

namespace llvm {

namespace simCC {
enum CondCode {
  EQ,
  NE,
  LE,
  GT,
  LEU,
  GTU,
  INVALID,
};

CondCode getOppositeBranchCondition(CondCode);

enum BRCondCode {
  BREQ = 0x0,
};
} // end namespace simCC

namespace simOp {
enum OperandType : unsigned {
  OPERAND_SIMM16 = MCOI::OPERAND_FIRST_TARGET,
  OPERAND_UIMM16,
};
} // namespace simOp

} // end namespace llvm

#endif // __LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMINFO_H__
