#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/PassManager.h>
#include <llvm/DerivedTypes.h>
#include <llvm/CallingConv.h>
#include <llvm/CodeGen/CodeGen.h>
#include <llvm/Analysis/Passes.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/ModuleProvider.h>
#include <llvm/Target/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <vector>
#include <memory>
#include <stack>
#include <iostream>

class CodeGenContext {
public:
    llvm::LLVMContext context;
    llvm::Module* module;
    std::stack<llvm::BasicBlock*> blocks;
    std::map<std::string, llvm::Value*> locals;

    CodeGenContext() {
        module = new llvm::Module("main", context);
    }

    ~CodeGenContext() {
        delete module;
    }

    llvm::BasicBlock* currentBlock() {
        return blocks.top();
    }

    void pushBlock(llvm::BasicBlock* block) {
        blocks.push(block);
    }

    void popBlock() {
        blocks.pop();
    }
};

#endif // COMPILER_CODEGENCONTEXT_H