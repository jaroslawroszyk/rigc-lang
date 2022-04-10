#pragma once

#include RIGCINTERPRETER_PCH

#include <RigCInterpreter/Functions.hpp>
#include <RigCInterpreter/Value.hpp>

namespace rigc::vm
{

struct Instance;

namespace builtin
{

OptValue print(Instance &vm_, Function::Args& args_, size_t argCount_);

}

}
