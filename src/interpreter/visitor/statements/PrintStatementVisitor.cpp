#include <memory>
#include <vector>

#include "../../../parser/KaprinoParserBaseVisitor.h"
#include "../../abstructs/StatementObject.h"
#include "../../abstructs/ExprObject.h"
#include "../../internallib/PrintfInternal.h"
#include "../../StatementVisitor.h"
#include "../../KaprinoLogger.h"

class PrintStatementObject : StatementObject {
   public:
    std::vector<ExprObject*> exprs;

    virtual void codegen(llvm::IRBuilder<>* builder, llvm::Module* module) override {
        auto printfFunc = get_printf(builder, module);

        std::string formatText;
        std::vector<llvm::Value*> args;

        for (auto expr : exprs) {
            auto value = expr->codegen(builder, module);
            argconv(value, module->getContext(), formatText, args);
        }

        formatText += "\n";
        auto formatVal = builder->CreateGlobalStringPtr(formatText);

        args.insert(args.begin(), formatVal);

        builder->CreateCall(printfFunc, args);
    }

   private:
    void argconv(llvm::Value* val, llvm::LLVMContext& ctx, std::string& format, std::vector<llvm::Value*>& args) {
        auto type = val->getType();
        if (type == llvm::Type::getDoubleTy(ctx)) {
            format += "%f";
            args.push_back(val);
        }
        else if (type == llvm::Type::getInt8PtrTy(ctx)) {
            format += "%s";
            args.push_back(val);
        }
        else {
            KAPRINO_ERR("An unexpected value was served to print");
            return;
        }
    }
};

antlrcpp::Any StatementVisitor::visitPrintStatement(KaprinoParser::PrintStatementContext* ctx) {
    auto statementObj = new PrintStatementObject();

    auto exprs = ctx->expr();
    for (auto expr : exprs) {
        statementObj->exprs.push_back(visit(expr).as<ExprObject*>());
    }

    return (StatementObject*)statementObj;
}
