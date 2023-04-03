//===-- SimMCTargetDesc.cpp - Sim Target Descriptions -------------------===//
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

#include "SimMCTargetDesc.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MachineLocation.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "SimGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "SimGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "SimGenRegisterInfo.inc"

static MCInstrInfo *createSimMCInstrInfo() {
  auto *X = new MCInstrInfo();
  InitSimMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createSimMCRegisterInfo(const Triple &TT) {
  auto *X = new MCRegisterInfo();
  InitSimMCRegisterInfo(X, Sim::R1);
  return X;
}

static MCSubtargetInfo *createSimMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
  return createSimMCSubtargetInfoImpl(TT, CPU, /*TuneCPU=*/CPU, FS);
}

static MCAsmInfo *createSimMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT,
                                     const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new SimMCAsmInfo(TT);
  MCRegister SP = MRI.getDwarfRegNum(Sim::R2, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
  MAI->addInitialFrameState(Inst);
  return MAI;
}

static MCInstPrinter *createSimMCInstPrinter(const Triple &T,
                                             unsigned SyntaxVariant,
                                             const MCAsmInfo &MAI,
                                             const MCInstrInfo &MII,
                                             const MCRegisterInfo &MRI) {
  return new SimInstPrinter(MAI, MII, MRI);
}

SimTargetStreamer::SimTargetStreamer(MCStreamer &S) : MCTargetStreamer(S) {}
SimTargetStreamer::~SimTargetStreamer() = default;

static MCTargetStreamer *createTargetAsmStreamer(MCStreamer &S,
                                                 formatted_raw_ostream &OS,
                                                 MCInstPrinter *InstPrint,
                                                 bool isVerboseAsm) {
  return new SimTargetStreamer(S);
}

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSimTargetMC() {
  // Register the MC asm info.
  Target &TheSimTarget = getTheSimTarget();
  RegisterMCAsmInfoFn X(TheSimTarget, createSimMCAsmInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheSimTarget, createSimMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheSimTarget, createSimMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheSimTarget,
                                          createSimMCSubtargetInfo);

  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheSimTarget, createSimMCInstPrinter);

  TargetRegistry::RegisterAsmTargetStreamer(TheSimTarget,
                                            createTargetAsmStreamer);
}
