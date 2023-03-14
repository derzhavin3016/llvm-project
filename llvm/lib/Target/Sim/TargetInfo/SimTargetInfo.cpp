//===-- SimTargetInfo.cpp - Sim Target Implementation -------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Sim.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/TargetRegistry.h"
using namespace llvm;

Target llvm::TheSimTarget;

extern "C" void LLVMInitializeSimTargetInfo() {
  RegisterTarget<Triple::sim_riscv,
                 /*HasJIT=*/false>
      X(TheSimTarget, "Sim", "Sim: 32-bit riscv simulator arch", "Sim");
}
