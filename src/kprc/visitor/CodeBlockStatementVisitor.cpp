#include <memory>
#include <vector>

#include "../KaprinoAccelerator.h"
#include "../StatementVisitor.h"
#include "KaprinoParserBaseVisitor.h"
#include "statements/StatementObject.h"

antlrcpp::Any StatementVisitor::visitCodeBlockStatement(KaprinoParser::CodeBlockStatementContext* ctx) {
    auto statementObj = new std::vector<StatementObject*>();

    auto statements = ctx->statement();
    for (auto st : statements) {
        statementObj->push_back(visit(st).as<StatementObject*>());
    }

    return statementObj;
}