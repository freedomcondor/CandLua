#include <stdio.h>

extern "C"{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

//gcc test.c -I/usr/include/lua5.2 -llua5.2 -fPIC -shared -o test.so

class Icey
{
	public:
	double temper;
	int angry();
	int cry();
	Icey();
};

Icey::Icey()
{
	temper = 0;
}

int Icey::angry()
{
	temper++;
	if (temper == 5) cry();
	return 0;
}

int Icey::cry()
{
	printf("QianQian died\n");
	temper = 0;
	return 0;
}

///////////////////////////////////////////////////////////
/*
int main()
{
	Icey icey;
	for (int i = 0; i < 10; i++)
	{
		printf("%d ",i);
		icey.angry();
	}
}
*/
//////////////////////////////////////////////////////////

extern "C"{
int newIcey(lua_State* L)
{
	Icey* icey = (Icey*)lua_newuserdata(L, sizeof(Icey));
	icey = new Icey;
	luaL_getmetatable(L,"Iceymt");
	lua_setmetatable(L,-2);
	return 1;
}

int angry(lua_State* L)
{
	Icey* icey = (Icey*)lua_touserdata(L,1);
	icey->angry();
	return 0;
}

static const luaL_Reg clib[] = 
{
	{"new",newIcey},
	{"angry",angry},
	{NULL,NULL}
};

int luaopen_icey(lua_State *L)
{
	lua_newtable(L);
	luaL_setfuncs(L,clib,0);
	lua_setglobal(L,"Icey");

	/*
	luaL_newmetatable(L,"Iceymt");
	lua_pushstring(L,"__index");
	lua_pushuserdata(L,);
	lua_settable(L,-3);
	*/
	return 1;
}

}
