#include<stdio.h>
#include<lua.h>
#include<lauxlib.h>
#include<lualib.h>

int main()
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	if ((luaL_loadfile(L,"func.lua")) || (lua_pcall(L,0,0,0)))
		{printf("open lua file fail %s\n",lua_tostring(L,-1));return -1;}

	lua_getglobal(L,"func");

	lua_newtable(L);
	lua_pushstring(L,"test");
	lua_pushstring(L,"testvalue");
	lua_settable(L,-3);
	//lua_setglobal(L,"name");

	if (lua_pcall(L,1,0,0) != 0)
		{printf("call func fail %s\n",lua_tostring(L,-1)); return -1;}

	lua_close(L);
	return 0;
}
