#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "aho_corasick.h"

#define BOOL int
#define TRUE 1
#define FALSE 0

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
	p->ret = TRUE;

	return 0;
}

//全局输出缓冲区
static int s_output_len = 0;
static char *s_output = NULL;

static int AC_AUTOMATA_init(){
    g_aca = (AC_AUTOMATA*)malloc(sizeof(*g_aca));
    ac_automata_init(g_aca, &match_handler);
}

static int AC_AUTOMATA_free(){
    if (g_fuck_pingbi!=NULL) {
        free(g_fuck_pingbi);
        g_fuck_pingbi = NULL;
    }
    if (g_aca != NULL) {
        ac_automata_release(g_aca);
        free(g_aca);
    }
    if (s_output){
        free(s_output);
        s_output_len = 0;
    }
}

static int get_line(char* buffer, int buffer_size, FILE* f) {
	int count = 0;
	char ch;
	do
	{
		ch = fgetc(f);
		if (ch == '\r' || ch == '\n') {
			buffer[count] = '\0';
			return count;
		} else {
			buffer[count++] = ch;
			assert(count < buffer_size);
		}
	} while (ch != EOF);
	if(ch == EOF) 
		buffer[count] = '\0';
	return count;
}

int LoadPingbi(const char* cpath)
{
	if(g_aca != NULL){
        AC_AUTOMATA_free();        
    }
	AC_AUTOMATA_init();

	unsigned int size = 0, id = 1, start = 0, len;	
	char *dump_str;

    //每行最大读取的字符数,可根据实际情况扩大
    char line[1024];             
    FILE *fp; 
    //判断文件是否存在及可读
    if((fp = fopen(cpath,"r")) == NULL) {
        return -1;
    }
	g_fuck_pingbi = (char*)malloc(1);
    while(!feof(fp)) {
#if 0
        // 读取一行
        fgets(line, sizeof(line), fp);
		len = strlen(line);

		// 末尾总是有一个换行,所以还是处理一下吧.
		if (line[len] == '\n') {
			line[len] = '\0';
			len -= 1;
		}
#else
		len = get_line(line, sizeof(line), fp);
#endif
        // 扩展内存
        g_fuck_pingbi = (char*)realloc(g_fuck_pingbi, size + len + 1);
		dump_str = g_fuck_pingbi + size;
		size += len + 1;

        strcpy(dump_str, line);        
        
        // 加入字符串中
	    static STRING tmp_str;	
		tmp_str.id = id++;
        tmp_str.str = (ALPHA *)dump_str;
        tmp_str.length = len; 
        ac_automata_add_string(g_aca, &tmp_str);
    }
    fclose(fp);
	ac_automata_locate_failure (g_aca);
	return 0;
}

BOOL FuckPingbi(char* pinbi_buff)
{
	STRING tmp_str;
	tmp_str.str = pinbi_buff;
	tmp_str.length = strlen(tmp_str.str);
	
	ac_automata_param param;
	param.str = pinbi_buff;
	param.ret = FALSE;
	ac_automata_search (g_aca, &tmp_str, &param);
	ac_automata_reset(g_aca);
	return param.ret;
}

//////////////////////////////////////////////////////////////////////////////
#if 1
#include <lua.h>
#include <lauxlib.h>

//如果缓冲区太小则扩大
static int checkout_output(int newsize) {
	//如果内存还没有分配则重新分配一下
	if (s_output_len >= newsize)
		return 0;
	
	if (s_output_len == 0) {
		s_output_len = newsize;
		s_output = (char*)malloc(s_output_len);
	}
	while (s_output_len < newsize) {
		s_output_len = s_output_len << 1;
	}
	s_output = (char*)realloc(s_output, s_output_len);
	return 1;
}

static int lua_ahocorasick_load(lua_State *L) {
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

static int lua_ahocorasick_match(lua_State *L) {
	// 传入文本
	const char* str = luaL_checkstring(L, 1);
	//int len = strlen(str) + 1;
	checkout_output(len);	
	strcpy(s_output, str);
	
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
	{ "load",				&lua_ahocorasick_load },
	{ "match",				&lua_ahocorasick_match },
	{ NULL, NULL }
};

int luaopen_ahocorasick(lua_State *L) {
	int startPos = lua_gettop(L);
	luaL_openlib(L, "ahocorasick", _funcs, 0);
	lua_settop(L, startPos);
	return 0;
}

#endif