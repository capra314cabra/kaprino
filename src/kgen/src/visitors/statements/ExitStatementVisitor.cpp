#include "kgen/visitors/StatementObject.h"
#include "kgen/visitors/StatementVisitor.h"

namespace kaprino::kgen {

class LoopStatementObject : StatementObject {
   public:
    static std::stack<llvm::BasicBlock*>& comebackpos;
};

class ExitStatementObject : StatementObject {
   public:
    virtual void codegen(llvm::IRBuilder<>* builder, llvm::Module* module) override {
        auto block = LoopStatementObject::comebackpos.top();
        builder->CreateBr(block);
        builder->SetInsertPoint((llvm::BasicBlock*)nullptr);
    }
};

antlrcpp::Any StatementVisitor::visitExitStatement(KaprinoParser::ExitStatementContext* ctx) {
    auto statementObj = new ExitStatementObject();

    return (StatementObject*)statementObj;
}

};  // namespace kaprino::kgen