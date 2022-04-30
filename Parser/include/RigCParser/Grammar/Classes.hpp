#pragma once

#include RIGCPARSER_PCH

#include <RigCParser/Grammar/Functions.hpp>
#include <RigCParser/Grammar/Templates.hpp>

namespace rigc
{

struct ExplicitType
	: p::seq<p::one<':'>, OptWs, Type>
{};

struct DataMemberDef
	: p::seq< Name, OptWs, p::sor<p::seq<ExplicitType, p::opt<Initialization>>, Initialization>, OptWs, p::one<';'> >
{};

struct MethodDef
	: p::seq< p::opt< OverrideKeyword, ws >, Name, OptWs, p::opt<FunctionParams>, p::opt<OptWs, ExplicitReturnType>, OptWs, CodeBlock >
{};

struct MemberDef
	: p::sor<
		DataMemberDef,
		MethodDef
	>
{
};

struct ClassCodeBlock
	: p::seq< p::one<'{'>, OptWs, p::star<MemberDef, OptWs>, p::one<'}'> >
{
};

struct ClassDefinition
	: p::seq<
			p::opt<ExportKeyword, ws>, 
			p::opt<TemplateDefPreamble, ws>,
			p::if_must< ClassKeyword, ws, Name, OptWs, ClassCodeBlock > >
{
};


}
