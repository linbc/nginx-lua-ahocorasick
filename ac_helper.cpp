#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

extern "C"{

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


struct __AC_AUTOMATA
{
	__AC_AUTOMATA()
	{
		g_aca = new AC_AUTOMATA;
		ac_automata_init(g_aca, &match_handler);
	}

	~__AC_AUTOMATA()
	{
		free(g_fuck_pingbi);
		ac_automata_release(g_aca);
	}
}__AC_AUTOMATA;

bool LoadFuckPingbi(string path)
{

	std::cout << "Load  _fuck_pingbi.txt ING" << std::endl;
	if(g_fuck_pingbi != NULL)
	{
		free(g_fuck_pingbi);
		ac_automata_release(g_aca);
		delete g_aca;
	}


	path += "_fuck_pingbi.txt";
	std::ifstream file(path.c_str(),std::ios::in | std::ios::binary);
	if(!file)
	{
		std::cout << "LoadFuckPingbi fail" << std::endl;
		return false;
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
	}	//?a??--??2????懈芯??斜褗??懈卸?懈鈺懈芯???1?懈写懈鈻?DD??DD?斜褗
	//2?1y?懈芯懈胁?懈鈻?2?懈芯斜褍?懈屑?懈胁1?

	//barGoLink bg(--count);

	//?懈芯卸鈺??懈胁斜鈹?斜鈹葱感?t?D?斜褗
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
	return true;
}

char* FuckPingbi(char* str)
{
	static char pinbi_buff[8096];
	//memset(pinbi_buff, 0, 8096);
	strcpy(pinbi_buff, str);
	//ASSERT(m_config.load_pingbi);
	STRING tmp_str;
	tmp_str.str = pinbi_buff;
	tmp_str.length = strlen(tmp_str.str);
	ac_automata_param param;
	param.str = pinbi_buff;
	param.ret = false;
	ac_automata_search (g_aca, &tmp_str, &param);
	ac_automata_reset(g_aca);
	if (param.ret !=0 )
		return pinbi_buff;
	return NULL;
}


void Test()
{
	string path = "E:\\snake\\pingbi\\";
	LoadFuckPingbi(path);
	char* pinbi = (char*)malloc(13);// "a493664527h";
	memset(pinbi,0,13);
	const char* pb = "a493664527h";
	memcpy(pinbi, pb,strlen(pb));
	char* res = FuckPingbi(pinbi);
	std::cout << res << std::endl;
}