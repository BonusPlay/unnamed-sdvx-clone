#pragma once
#include <map>
#include "Shared/Utility.hpp"
#include "Shared/Map.hpp"
#include "Shared/Bindable.hpp"

/*
	Template delegate class, can have multiple registered classes that handle a call to this function
*/
template<typename... A>
class Delegate
{
	std::map<std::string, FunctionBinding<void(A...)>> handlers;
public:

	// Adds an object function handler; ensure tag is of form "objectTag::functionTag"
	template<typename Class>
	void Add(std::string tag, Class* object, void (Class::*func)(A...))
	{
		assert(handlers.find(tag) == handlers.end());
		handlers.emplace(tag, ObjectBinding<Class, void(A...)>(object, func));
	}
	// Adds a static function handler
	void Add(std::string tag, std::function<void(A...)> func)
	{
		assert(handlers.find(tag) == handlers.end());
		handlers.emplace(tag, func);
	}
	// Adds a lambda function as a handler for this delegate
	template<typename T> void AddLambda(std::string tag, T&& lambda)
	{
		assert(handlers.find(tag) == handlers.end());
		handlers.emplace(tag, std::forward<T>(lambda));
	}
	// Removes a handler
	void Remove(std::string tag)
	{
		assert(handlers.find(tag) != handlers.end());
		handlers.erase(tag);
	}

	// Removes all handlers belonging to a specific namespace
	void RemoveAll(std::string objectTag)
	{
		for (auto it = handlers.begin(); it != handlers.end();)
		{
			if (it->first.rfind(objectTag, 0) == 0)
			{
				it = handlers.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	// Removes all handlers
	void Clear()
	{
		// Cleanup the pointers
		handlers.clear();
	}

	// Calls the delegate
	void operator()(A... args)
	{
		for(auto& h : handlers)
		{
			h.second(args...);
		}
	}

	// True if anything function is handling this delegate being called
	bool IsHandled() const
	{
		return !handlers.empty() || !handlers.empty() || !handlers.empty();
	}
};
