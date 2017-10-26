#include <stdio.h>
#include <new>

extern "C"{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

//g++ obj.cpp -I/usr/include/lua5.2 -llua5.2 -fPIC -shared -o icey.so

///////////// the class //////////////////////////////////////////
class Icey
{
	public:
	double temper;
	int angry();
	int cry();
	int initIcey(int initVal);
	~Icey();
	Icey(int initVal);
};

Icey::Icey(int initVal)
{
	initIcey(initVal);
}
int Icey::initIcey(int initVal)
{
	temper = initVal;
	return 0;
}
Icey::~Icey()
{
	printf("kill qianqian too\n");
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
	icey = new((void*) icey)Icey(4);
	//icey->initIcey(4);
	luaL_getmetatable(L,"Icey");
	lua_setmetatable(L,-2);
	return 1;
}

int angry(lua_State* L)
{
	Icey* icey = (Icey*)lua_touserdata(L,1);
	icey->angry();
	printf("in angry, temper = %lf\n",icey->temper);
	return 0;
}

static const luaL_Reg clib[] = 
{
	{"new",newIcey},
	{"angry",angry},
	{NULL,NULL}
};

int icey_gc(lua_State *L)
{
	Icey* icey = (Icey*)lua_touserdata(L,1);
	printf("kill icey\n");
	icey->~Icey();
	
	// delete userdata , it seems no used to do this
	
	return 0;
}

int icey_tostring(lua_State* L)
{
	lua_pushfstring(L,"Icey:%p",lua_touserdata(L,1));
	return 1;
}

static const luaL_Reg clib_mt[] = 
{
	{"__gc",	icey_gc},
	{"__tostring",	icey_tostring},
	{NULL,NULL}
};

int luaopen_icey(lua_State *L)
{
	lua_settop(L,0);
	// a table Icey = {new = function x, angry = function xx}
	lua_newtable(L);			// stack 3
	luaL_setfuncs(L,clib,0);
	lua_setglobal(L,"Icey");	// stack 2

	// a metatable Iceymt = {__gc = xx, __tostring = xxx}
	luaL_newmetatable(L,"Icey");	//stack 3
	luaL_setfuncs(L,clib_mt,0);

							
	//Iceymt.__index = Icey
	lua_pushstring(L,"__index");	// stack 4
	lua_getglobal(L,"Icey");
	lua_settable(L,-3);

	lua_pop(L,1);	// this pops the metatable

	return 1;
}

}
