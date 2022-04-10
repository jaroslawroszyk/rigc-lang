#include RIGCINTERPRETER_PCH

#include <RigCInterpreter/TypeSystem/FuncType.hpp>

#include <RigCInterpreter/VM.hpp>
#include <RigCInterpreter/Functions.hpp>
#include <RigCInterpreter/Type.hpp>
#include <RigCInterpreter/Value.hpp>

namespace rigc::vm
{

//////////////////////////////////////
void FuncType::postInitialize(Instance& vm_)
{
	// Function::Params params;
	// for (size_t i = 0; i < parameters.size(); ++i) {
	// 	params[i].type = parameters[i];
	// 	params[i].name
	// }

	// auto& fn = vm_.universalScope().registerOperator(vm_, "()", Operator::Postfix,
	// 	Function{
	// 		[](Instance& vm_, Function::Args& args_, size_t argCount_) -> OptValue
	// 		{
	// 			Function::Args innerArgs;
	// 			for (size_t i = 1; i < argCount_; ++i) {
	// 				innerArgs[i - 1] = args_[i];
	// 			}

	// 			return vm_.executeFunction(args_[0].view<Function*>(), innerArgs, argCount_ - 1);
	// 		},
	// 		{ { "self", wrap<RefType>(vm_.universalScope(), this->shared_from_this()) } },
	// 		1
	// 	}
	// );
	// fn.returnsRef = true;
	// this->addMethod("()", &fn);
}

//////////////////////////////////////
std::string FuncType::name() const
{
	if (!result && parameters.empty())
		return std::string(BuiltinTypes::OverloadedFunction);

	std::string ret = "Func<" + result->name();
	for (auto const& param : parameters) {
		ret += ", ";
		ret += param->name();
	}
	ret += ">";
	return ret;
}

//////////////////////////////////////
std::string MethodType::name() const
{
	if (!result && parameters.empty())
		return std::string(BuiltinTypes::OverloadedMethod);

	std::string ret = "Method<" + classType->name() + ", " + result->name();
	for (auto const& param : parameters) {
		ret += ", ";
		ret += param->name();
	}
	ret += ">";
	return ret;
}

//////////////////////////////////////
Value allocateMethodOverloads(Instance& vm_, Value self_, FunctionOverloads const* overloads_)
{
	using PtrType = void const*;

	PtrType buf[ 2 ];

	buf[0] = overloads_;
	buf[1] = self_.data;

	auto type = vm_.findType(BuiltinTypes::OverloadedMethod);
	return vm_.allocateOnStack(type->shared_from_this(), (void const*)buf, sizeof(buf));
}

}
