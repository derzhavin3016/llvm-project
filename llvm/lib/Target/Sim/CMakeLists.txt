add_llvm_component_group(Sim)

set(LLVM_TARGET_DEFINITIONS Sim.td)

# Generate simGenRegisterInfo.inc and simGenInstrInfo.inc which included by
#  your hand code C++ files.
# simGenRegisterInfo.inc came from simRegisterInfo.td, simGenInstrInfo.inc
#  came from simInstrInfo.td.
tablegen(LLVM SimGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM SimGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM SimGenCallingConv.inc -gen-callingconv)
tablegen(LLVM SimGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM SimGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM SimGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM SimGenDAGISel.inc -gen-dag-isel)

#tablegen(LLVM simGenDisassemblerTables.inc -gen-disassembler)

add_public_tablegen_target(SimCommonTableGen)

add_llvm_target(SimCodeGen
  SimAsmPrinter.cpp
  SimFrameLowering.cpp
  SimInstrInfo.cpp
  SimISelDagToDag.cpp
  SimISelLowering.cpp
  SimMachineFunctionInfo.cpp
  SimMCInstLower.cpp
  SimRegisterInfo.cpp
  SimSubtarget.cpp
  SimTargetMachine.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  Core
  MC
  SimDesc
  SimInfo
  SelectionDAG
  Support
  Target
  GlobalISel

  ADD_TO_COMPONENT
  Sim
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
