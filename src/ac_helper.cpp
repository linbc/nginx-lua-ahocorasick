#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

extern "C" {
#include "aho_corasick.h"
}

AC_AUTOMATA *g_aca;
char *g_fuck_pingbi = NULL;
//m_aca = new AC_AUTOMATA;


int match_handler(MATCH *m, void *param)
{
	int pos;
	pos = m->position - m->matched_strings->length;
	ac_automata_param *p = (ac_automata_param*)param;
	for (; pos < m->position; pos++) {
		p->str[pos] = '*';
	}
	p->ret = true;

	return 0;
}

//全局输出缓冲区
static int s_output_len = 0;
static char *s_output = NULL;

struct __AC_AUTOMATA {
	__AC_AUTOMATA() {
		g_aca = new AC_AUTOMATA;
		ac_automata_init(g_aca, &match_handler);
	}

	~__AC_AUTOMATA() {
		if (g_fuck_pingbi!=NULL) 
			free(g_fuck_pingbi);
		if (g_aca != NULL) {
			ac_automata_release(g_aca);
			delete g_aca;
		}
		if (s_output){
			free(s_output);
			s_output_len = 0;
		}
	}
}__AC_AUTOMATA;

extern "C" int LoadPingbi(const char* cpath)
{
	if(g_fuck_pingbi != NULL)
	{
		free(g_fuck_pingbi);
		ac_automata_release(g_aca);
		delete g_aca;

		g_aca = new AC_AUTOMATA;
		ac_automata_init(g_aca, &match_handler);
	}

	std::ifstream file(cpath,std::ios::in | std::ios::binary);
	if(!file)
	{
		std::cout << "LoadFuckPingbi fail" << std::endl;
		return -1;
	}

	unsigned int i = 0, id = 1, start = 0, count  =0, len;	
	std::string str;
	STRING tmp_str;	
	std::stringstream buffer;

	buffer << file.rdbuf();   
	str = buffer.str();  

	file.close(); 
	len = str.length() + 1;
	g_fuck_pingbi = (char *)malloc(len * sizeof(char *));
	for(i = 0; i < len; ++i)
	{
		if(strchr("\r\n", str.c_str()[i]))
		{
			g_fuck_pingbi[i] = 0;
			count++;
		}
		else
			g_fuck_pingbi[i] = str.c_str()[i];
	}	
	
	for (i = 0; i < len; ++i)
	{
		if(g_fuck_pingbi[i] == 0)
		{
			if(start != i)
			{
				tmp_str.id = id++;
				tmp_str.str = (ALPHA *)(g_fuck_pingbi + start);
				tmp_str.length = i - start;
				ac_automata_add_string(g_aca, &tmp_str);
				//bg.step();
			}
			start = i + 1;
		}
	}
	ac_automata_locate_failure (g_aca);
	//std::cout << "Load  _fuck_pingbi.txt OK!" << std::endl;
	return 0;
}

extern "C" int FuckPingbi(char* pinbi_buff)
{
	STRING tmp_str;
	tmp_str.str = pinbi_buff;
	tmp_str.length = strlen(tmp_str.str);
	
	ac_automata_param param;
	param.str = pinbi_buff;
	param.ret = false;
	ac_automata_search (g_aca, &tmp_str, &param);
	ac_automata_reset(g_aca);
	return param.ret;
}

//////////////////////////////////////////////////////////////////////////////


//如果缓冲区太小则扩大
static int checkout_output(int newsize) {
	//如果内存还没有分配则重新分配一下
	if (s_output_len >= newsize)
		return 0;
	
	if (s_output_len == 0) {
		s_output_len = newsize;
		s_output = malloc(s_output_len);
	}
	while (s_output_len < newsize) {
		s_output_len = s_output_len << 1;
	}
	s_output = realloc(s_output, s_output_len);
	return 1;
}

static int lua_load(lua_State *L) {
	// 传入路径名
	const char* path = luaL_checkstring(L, 1);
	int ret = LoadPingbi(path);	
	if(ret != 0) {
		lua_pushboolean(L, FALSE);
		lua_pushnumber(L, ret);
		return 2;
	} else {
		lua_pushboolean(L, TRUE);
		return 1;
	}	
}

static int lua_match(lua_State *L) {
	// 传入文本
	const char* str = luaL_checkstring(L, 1);
	int len = strlen(str) + 1;
	checkout_output(len);	
	memcpy(s_output, str, len);
	
	// 返回匹配结果
	// 如果匹配上返回新值
	if (FuckPingbi(s_output) != FALSE)
		lua_pushboolean(L, TRUE);
	else
		lua_pushboolean(L, FALSE);
	lua_pushstring(L, s_output);
	return 2;
}

static const struct luaL_reg _funcs[] = {
	{ "load",				&lua_load },
	{ "match",				&lua_match },
	{ NULL, NULL }
};

extern "C" int luaopen_ahocorasick_binding(lua_State *L) {
	int startPos = lua_gettop(L);
	luaL_openlib(L, "ahocorasick", _funcs, 0);
	lua_settop(L, startPos);
	return 0;
}

void Test()
{
	string path = "..\\_fuck_pingbi.txt";
	LoadFuckPingbi(path.c_str());
	char pinbi[1024] = "a493664527h";
	int res = FuckPingbi(pinbi);
	std::cout << pinbi << std::endl;
}
