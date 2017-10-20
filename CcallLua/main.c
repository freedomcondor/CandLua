#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int main()
{
	//lua_State *L = lua_open();
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	if ((luaL_loadfile(L,"func.lua")) || (lua_pcall(L,0,0,0)))
		{printf("open lua file fail\n");return -1;}

	// z = func(7,8)
	lua_getglobal(L,"func");
	if (lua_isnil(L,-1)) printf("is nil\n");
	lua_pushnumber(L,7);
	lua_pushnumber(L,8);

	if (lua_pcall(L,2,1,0) != 0) 
		{printf("call lua function fail : %s\n",lua_tostring(L,-1));return -1;}
	
	double z = lua_tonumber(L,-1);

	printf("z = %f\n",z);

	// get table
	lua_getglobal(L,"aaa");
	if (!lua_istable(L,-1)) printf("not a table\n");
	//lua_pushnumber(L,1);
	lua_pushstring(L,"test");
	lua_gettable(L,-2);

	//z = lua_tonumber(L,-1);
	//printf("z = %f\n",z);

	printf("test = %s\n",lua_tostring(L,-1));

	lua_close(L);
	return 0;
}

// g++ main.c -I/usr/include/lua5.2 -llua5.2 -o main
