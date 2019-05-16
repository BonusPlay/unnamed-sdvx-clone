#pragma once
#include <functional>
#include "Shared/Utility.hpp"
#include "Shared/Map.hpp"

template<typename R, typename... A>
struct FunctionBinding
{
	FunctionBinding(std::function<R(A...)> function) : function(function) {}
	virtual R operator()(A... args) const {
		return function(args...);
	}

	std::function<R(A...)> function;
};

template<typename R, typename... A>
struct FunctionBinding<R(A...)> : public FunctionBinding<R, A...> {
	using FunctionBinding<R, A...>::FunctionBinding;
};

// Member function binding
template<typename T, typename R, typename... A>
struct ObjectBinding : public FunctionBinding<R(A...)>
{
	ObjectBinding(T* object, R(T::* member_function)(A...)) :
		object(object),
		member_function(member_function),
		FunctionBinding([=](A... args) -> R { return std::mem_fn(member_function)(object, args...); }) {}

	bool IsSame(T* object, R(T::* member_function)(A...))
	{
		return this->object == object && this->member_function == member_function;
	}

	bool IsSame(T* object)
	{
		return this->object == object
	}

	bool operator==(const ObjectBinding<T, R, A...>& rhs)
	{
		return IsSame(rhs.object, rhs.member_function);
	}

	T* object;
	R(T::* member_function)(A...);
};

template<typename T, typename R, typename... A>
struct ObjectBinding<T, R(A...)> : public ObjectBinding<T, R, A...> {
	using ObjectBinding<T, R, A...>::ObjectBinding;
};

/* Constant return value binding */
template<typename R, typename... A>
struct ConstantBinding : public FunctionBinding<R(A...)>
{
	explicit ConstantBinding(const R& value) :
		value(value),
		FunctionBinding([=]() -> R { return value; }) {}

	bool operator==(const R& rhs) {
		return value == rhs;
	}

	R value;
};

template<typename R, typename... A>
struct ConstantBinding<R(A...)> : public ConstantBinding<R, A...>
{
	using ConstantBinding<R, A...>::ConstantBinding;
};
