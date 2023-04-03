#ifndef __CLANG_LIB_BASIC_TARGETS_SIM_H__
#define __CLANG_LIB_BASIC_TARGETS_SIM_H__

#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Support/Compiler.h"
#include <array>

namespace clang::targets {

class LLVM_LIBRARY_VISIBILITY SimTargetInfo : public TargetInfo {
public:
  SimTargetInfo(const llvm::Triple &triple, const TargetOptions &)
      : TargetInfo(triple) {
    NoAsmVariants = true;
    LongLongAlign = 32;
    SuitableAlign = 32;
    DoubleAlign = LongDoubleAlign = 32;
    SizeType = UnsignedInt;
    PtrDiffType = SignedInt;
    IntPtrType = SignedInt;
    UseZeroLengthBitfieldAlignment = true;
    resetDataLayout("e-m:e-p:32:32-i1:8:32-i8:8:32-i16:16:32-"
                    "i32:32:32-f32:32:32-i64:32-f64:32-a:0:32-n32");
  }

  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;

  ArrayRef<Builtin::Info> getTargetBuiltins() const override {
    return std::nullopt;
  }

  BuiltinVaListKind getBuiltinVaListKind() const override {
    return TargetInfo::VoidPtrBuiltinVaList;
  }

  const char *getClobbers() const override { return ""; }

  ArrayRef<const char *> getGCCRegNames() const override {
    static constexpr std::array GCCRegNames = {
        "r0", "r1",  "r2",  "r3",  "r4",  "r5",  "r6",  "r7", "r8",
        "r9", "r10", "r11", "r12", "r13", "r14", "r15", "r16"};
    return GCCRegNames;
  }

  ArrayRef<TargetInfo::GCCRegAlias> getGCCRegAliases() const override {
    return std::nullopt;
  }

  bool validateAsmConstraint(const char *&,
                             TargetInfo::ConstraintInfo &) const override {
    return false;
  }

  bool hasBitIntType() const override { return true; }

  bool isCLZForZeroUndef() const override { return false; }
};
} // namespace clang::targets

#endif // __CLANG_LIB_BASIC_TARGETS_SIM_H__
