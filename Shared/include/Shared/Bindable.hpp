#pragma once
#include <functional>
#include "Shared/Utility.hpp"
#include "Shared/Map.hpp"

template<typename R, typename... A>
struct FunctionBinding
{
	FunctionBinding(std::function<R(A...)> function) : function(function) {}
	virtual R operator()(A... args) {
		return function(args...);
	}
	
	bool operator==(std::function<R(A...)> rhs)
	{
		return function == rhs;
	}

	std::function<R(A...)> function;
};

// Member function binding
template<typename Class, typename R, typename... A>
struct ObjectBinding : public FunctionBinding<R, A...>
{
	ObjectBinding(Class* object, R(Class::* func)(A...)) : FunctionBinding([=](A... args) -> R { return std::mem_fn(func)(object, args...); }) {};
};

/* Constant return value binding */
template<typename R, typename... A>
struct ConstantBinding : public FunctionBinding<R, A...>
{
	explicit ConstantBinding(const R& value) : FunctionBinding([=]() -> R { return value; }) {};
};