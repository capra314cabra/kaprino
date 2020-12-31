use inkwell::context::Context;
use inkwell::OptimizationLevel;
use inkwell::execution_engine::JitFunction;
use super::super::program_object::CodeGen;
use super::super::exprs::expr_object;

pub fn execute_expr(text: &str) -> Option<u32> {
    type TestFunc = unsafe extern "C" fn(u32) -> u32;

    let context = &Context::create();
    let gen = CodeGen::new(context, "test");

    let i32_type = gen.context.i32_type();
    let fn_type = i32_type.fn_type(&[i32_type.into(), i32_type.into()], false);

    let sum = gen.module.add_function("calc", fn_type, None);
    let basic_block = gen.context.append_basic_block(sum, "entry");
    gen.builder.position_at_end(basic_block);

    match expr_object::expr_parser(text) {
        Ok((_, val1)) => {
            let generated = val1.codegen(&gen);
            match generated {
                Ok(val2) => {
                    gen.builder.build_return(Some(&val2));

                    let execution_engine = gen.module.create_jit_execution_engine(OptimizationLevel::None).unwrap();

                    let func: JitFunction<TestFunc> = unsafe { execution_engine.get_function("calc").unwrap() };
                    let ret: u32 = unsafe { func.call(0) };
                    Some(ret)
                },
                Err(_) => None
            }
        },
        Err(_) => None
    }
}
