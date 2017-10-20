#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

//gcc test.c -I/usr/include/lua5.2 -llua5.2 -fPIC -shared -o test.so

static int add_c(lua_State *L)
{
	double a = lua_tonumber(L,1);
	printf("a = %f\n",a);
	double b = lua_tonumber(L,2);
	printf("b = %f\n",b);
	printf("a+b = %f\n",a+b);
	lua_pushnumber(L,a + b);
	return 1;
}

//static const struct luaL_reg clib[] =
static const luaL_Reg clib[] =
{
	{"add",add_c},
	{NULL,NULL}
};

int luaopen_test(lua_State *L)
{
	lua_newtable(L);
	luaL_setfuncs(L,clib,0);
	lua_setglobal(L,"mylib");
	//luaL_openlib(L,"mylib",clib,0);
	return 1;
}
