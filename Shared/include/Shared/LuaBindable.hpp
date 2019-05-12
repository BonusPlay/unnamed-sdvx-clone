#pragma once
#include "lua.hpp"
#include "Bindable.hpp"
#include "String.hpp"
#include "Map.hpp"

int lMemberCallFunction(lua_State* L);
int lIndexFunction(lua_State* L);

class LuaBindable
{
public:
	Map<String, FunctionBinding<int, lua_State*>*> Bindings;
	LuaBindable(lua_State* L, String name) : m_name(name)
	{
		m_lua = L;
	}
	template<typename Class>
	void AddFunction(String name, Class* object, int (Class::*func)(lua_State*))
	{
		auto binding = new ObjectBinding<Class, int, lua_State*>(object, func);
		Bindings.Add(name, binding);
	}
	void Push()
	{
		if (luaL_newmetatable(m_lua, "Scriptable") == 1)
		{
			lua_pushcfunction(m_lua, lIndexFunction);
			lua_setfield(m_lua, -2, "__index");
		}

		LuaBindable** ud = static_cast<LuaBindable**>(lua_newuserdata(m_lua, sizeof(LuaBindable*)));
		*(ud) = this;

		luaL_setmetatable(m_lua, "Scriptable");
		lua_setglobal(m_lua, *m_name);
	}

private:
	String m_name;
	lua_State* m_lua;
};

int lMemberCallFunction(lua_State* L)
{
	FunctionBinding<int, lua_State*>** t = (FunctionBinding<int, lua_State*>**)(luaL_checkudata(L, 1, "Scriptable_Callback"));
	return (**t)(L);
}

int lIndexFunction(lua_State* L)
{
	LuaBindable** t = static_cast<LuaBindable**>(luaL_checkudata(L, 1, "Scriptable"));
	String lookup = luaL_checkstring(L, 2);

	if (luaL_newmetatable(L, "Scriptable_Callback") == 1)
	{
		lua_pushcfunction(L, lMemberCallFunction);
		lua_setfield(L, -2, "__call");
	}

	FunctionBinding<int, lua_State*>** ud = static_cast<FunctionBinding<int, lua_State*>**>(lua_newuserdata(L, sizeof(FunctionBinding<int, lua_State*>*)));
	*(ud) = (*t)->Bindings[lookup];

	luaL_setmetatable(L, "Scriptable_Callback");

	return 1;
}