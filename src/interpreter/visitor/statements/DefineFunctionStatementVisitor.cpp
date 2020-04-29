#include <memory>
#include <vector>

#include "../../../parser/KaprinoParserBaseVisitor.h"
#include "../../abstructs/StatementObject.h"
#include "../../abstructs/FunctionTypeObject.h"
#include "../../abstructs/ExprObject.h"
#include "../../VariableManager.h"
#include "../../TypeManager.h"
#include "../../FunctionManager.h"
#include "../../StatementVisitor.h"
#include "../../KaprinoAccelerator.h"

class DefineFunctionStatementObject : StatementObject {
   public:
    std::string funcName;
    std::vector<std::string> inputParamNames;
    FunctionTypeObject* functionType;
    ExprObject* expr;

    virtual void codegen(llvm::IRBuilder<>* builder, llvm::Module* module) override {
        VariableManager::add_scope();
        {
            auto types = functionType->inputTypes;
            std::vector<llvm::Type*> inputTypes;
            for (auto type : types) {
                inputTypes.push_back(TypeManager::gettype(builder, module, type));
            }

            auto userdefinedType = llvm::FunctionType::get(
                TypeManager::gettype(builder, module, functionType->outputType),
                inputTypes,
                true
            );

            auto userdefinedFunc = llvm::Function::Create(
                userdefinedType,
                llvm::GlobalValue::ExternalLinkage,
                funcName,
                module
            );
            userdefinedFunc->setCallingConv(llvm::CallingConv::C);

            auto funcBody = llvm::BasicBlock::Create(module->getContext(), "", userdefinedFunc);
            builder->SetInsertPoint(funcBody);

            int size = inputParamNames.size();
            std::vector<llvm::Value*> args;
            for (auto& arg : userdefinedFunc->args()) {
                args.push_back(&arg);
            }
            for (int counter = 0; counter < size; counter++) {
                auto arg = args[counter];
                auto allocated = builder->CreateAlloca(arg->getType());
                builder->CreateStore(arg, allocated);
                VariableManager::create(
                    builder,
                    module,
                    inputParamNames[counter],
                    allocated
                );
            }

            builder->CreateRet(expr->codegen(builder, module));

            FunctionManager::create(builder, module, funcName, userdefinedFunc);
        }
        VariableManager::remove_scope();
    }
};

antlrcpp::Any StatementVisitor::visitDefineFunctionStatement(KaprinoParser::DefineFunctionStatementContext* ctx) {
    auto statementObj = new DefineFunctionStatementObject();

    auto names = ctx->ID();
    statementObj->funcName = names[0]->getText();
    int size = names.size();
    for(int counter = 1; counter < size; counter++) {
        statementObj->inputParamNames.push_back(names[counter]->getText());
    }
    statementObj->functionType = visit(ctx->function_type()).as<FunctionTypeObject*>();
    statementObj->expr = visit(ctx->expr()).as<ExprObject*>();

    return (StatementObject*)statementObj;
}