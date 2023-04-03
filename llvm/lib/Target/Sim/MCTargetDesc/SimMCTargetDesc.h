//===-- SimMCTargetDesc.h - Sim Target Descriptions -----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides Sim specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef __LIB_TARGET_SIM_MCTARGETDESC_SIMMCTARGETDESC_H__
#define __LIB_TARGET_SIM_MCTARGETDESC_SIMMCTARGETDESC_H__

#include "llvm/Support/DataTypes.h"

#include <memory>

namespace llvm {
class Target;
class Triple;

extern Target TheSimTarget;

} // namespace llvm

// Defines symbolic names for Sim registers.  This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "SimGenRegisterInfo.inc"

// Defines symbolic names for the Sim instructions.
#define GET_INSTRINFO_ENUM
#include "SimGenInstrInfo.inc"

#endif // __LIB_TARGET_SIM_MCTARGETDESC_SIMMCTARGETDESC_H__
