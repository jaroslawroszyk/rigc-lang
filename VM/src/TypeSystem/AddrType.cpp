#include RIGCVM_PCH

#include <RigCVM/TypeSystem/RefType.hpp>

#include <RigCVM/VM.hpp>
#include <RigCVM/Functions.hpp>

namespace rigc::vm
{

//////////////////////////////////////
auto RefType::getTemplateArguments() const -> std::vector<TemplateArgument> const&
{
	return templateArguments;
}

//////////////////////////////////////
void RefType::postInitialize(Instance& vm_)
{
	// Setup template arguments
	{
		templateArguments.clear();
		templateArguments.push_back(inner);
	}
}

//////////////////////////////////////
auto AddrType::getTemplateArguments() const -> std::vector<TemplateArgument> const&
{
	return templateArguments;
}

//////////////////////////////////////
void AddrType::postInitialize(Instance& vm_)
{

	// Setup template arguments
	{
		templateArguments.clear();
		templateArguments.push_back(inner);
	}

	// get method
	{
		auto& fn = vm_.universalScope().registerFunction(vm_, "get",
			Function{
				[](Instance& vm_, Function::ArgSpan args_) -> OptValue
				{
					return vm_.allocateReference(args_[0].removeRef().removePtr());
				},
				{ { "self", wrap<RefType>(vm_.universalScope(), this->shared_from_this()) } },
				1
			}
		);
		fn.returnsRef = true;
		this->addMethod("get", &fn);
	}

	// plus operator
	{
		Function::Params params;

		params[0] = { "self", this->shared_from_this() };
		params[1] = { "rhs", vm_.findType("Int32")->shared_from_this() };

		auto& fn = vm_.universalScope().registerOperator(vm_, "+", Operator::Infix,
			Function{
				[](Instance& vm_, Function::ArgSpan args_) -> OptValue
				{
					auto self = args_[0].safeRemoveRef();
					return vm_.allocateOnStack<void const*>(
							self.type,
							self.view<char const*>() + self.type->decay()->size() * args_[1].view<int32_t>()
						);
				},
				std::move(params),
				2
			}
		);
	}
}


}
