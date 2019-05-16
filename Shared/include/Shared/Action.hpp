#pragma once
#include <memory>
#include "Bindable.hpp"

/*
	Action is an objects that holds the neccesary information to call a single static function / member function / lambda
*/
template<typename R = void, typename... A>
class Action
{
public:
	Action() = default;
	explicit Action(std::function<R(A...)> function)
	{
		m_binding.reset(new FunctionBinding<R(A...)>(function));
	}

	template<typename L>
	Action(L&& lambda)
	{
		m_binding.reset(new FunctionBinding<R(A...)>(std::forward<L>(lambda)));
	}

	Action(Action&& other) noexcept
	{
		m_binding.reset(other.m_binding.release());
	}

	Action& operator=(Action&& other) noexcept
	{
		m_binding.reset(other.m_binding.release());
		return *this;
	}

	void Bind(std::function<R(A...)>)
	{
		m_binding.reset(new FunctionBinding<R(A...)>(staticFunction));
	}

	template<typename T>
	void Bind(T* obj, R(T::*memberFunc)(A...))
	{
		m_binding.reset(new ObjectBinding<T, R(A...)>(obj, memberFunc));
	}

	template<typename L>
	void BindLambda(L&& lambda)
	{
		m_binding.reset(new FunctionBinding<R(A...)>(std::forward<L>(lambda)));
	}

	R operator()(A... args)
	{
		assert(IsBound());
		return (*m_binding)(args...);
	}

	bool IsBound() const
	{
		return (bool)m_binding;
	}

private:
	std::unique_ptr<FunctionBinding<R(A...)>> m_binding;
};

/* 
	Bindable property 
	This field either acts just as a normal variable or acts a a property using Get/Set methods to interface with the underlying value
*/
template<typename T>
class Property
{
public:
	Property() = default;
	explicit Property(T val)
		: m_value(val)
	{}

	Property(Action<T> get, Action<void, T> set)
		: Get(move(get)), Set(move(set))
	{}

	// Get
	inline operator T() const
	{
		return m_Get();
	}

	// Set
	inline Property& operator=(const T& other)
	{
		m_Set(other);
		return *this;
	}

	Action<T> Get;
	Action<void, T> Set;

protected:
	T m_value;

	inline T m_Get() const
	{
		if(Get.IsBound())
			return const_cast<Property*>(this)->Get();
		else
			return m_value;
	}

	inline void m_Set(const T& val)
	{
		if (Set.IsBound())
			Set(val);
		else
			m_value = val;
	}
};