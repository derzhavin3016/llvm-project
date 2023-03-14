add_llvm_component_group(Sim)

set(LLVM_TARGET_DEFINITIONS Sim.td)

tablegen(LLVM SimGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM SimGenInstrInfo.inc -gen-instr-info)

add_public_tablegen_target(SimCommonTableGen)

add_llvm_target(SimCodeGen
  RISCVTargetMachine.cpp

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
