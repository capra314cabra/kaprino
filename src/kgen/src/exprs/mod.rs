use inkwell::values::BasicValueEnum;
use super::program_object::CodeGen;
use exponents_object::ExponentsObject;
use expr_object::ExprObject;
use numbers_object::NumberObject;
use term_object::TermObject;
use param_object::ParamObject;
use function_call_object::FunctionCallObject;
use string_object::StringObject;

/// Object which represents evaluable expressions.
#[derive(Debug,PartialEq)]
pub enum EvaluableObject {
    NumberObject(Box<NumberObject>),
    StringObject(Box<StringObject>),
    ExponentsObject(Box<ExponentsObject>),
    TermObject(Box<TermObject>),
    ExprObject(Box<ExprObject>),
    ParamObject(Box<ParamObject>),
    FunctionCallObject(Box<FunctionCallObject>)
}

impl<'ctx> EvaluableObject {
    pub fn eval(&self) -> u32 {
        match self {
            EvaluableObject::NumberObject(obj) => obj.eval(),
            EvaluableObject::ExponentsObject(obj) => obj.eval(),
            EvaluableObject::TermObject(obj) => obj.eval(),
            EvaluableObject::ExprObject(obj) => obj.eval(),
            _ => 0
        }
    }

    pub fn codegen(&self, gen: &CodeGen<'ctx>) -> Result<BasicValueEnum<'ctx>, String> {
        match self {
            EvaluableObject::NumberObject(obj) => obj.codegen(gen),
            EvaluableObject::StringObject(obj) => obj.codegen(gen),
            EvaluableObject::ExponentsObject(obj) => obj.codegen(gen),
            EvaluableObject::TermObject(obj) => obj.codegen(gen),
            EvaluableObject::ExprObject(obj) => obj.codegen(gen),
            EvaluableObject::ParamObject(obj) => obj.codegen(gen),
            EvaluableObject::FunctionCallObject(obj) => obj.codegen(gen)
        }
    }
}

pub mod string_object;
pub mod numbers_object;
pub mod function_call_object;
pub mod paren_object;
pub mod factor_object;
pub mod exponents_object;
pub mod term_object;
pub mod expr_object;
pub mod param_object;

mod test;
