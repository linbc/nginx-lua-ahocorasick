
bool SvrCoreAppImpl::LoadFuckPingbi(string path)
{
	std::cout << "Load  _fuck_pingbi.txt ING" << std::endl;
	if(m_fuck_pingbi != NULL)
	{
		free(m_fuck_pingbi);
		ac_automata_release(m_aca);
		delete m_aca;
		//3?¨º??¡¥AC¡Á??¡¥?¨²
		m_aca = new AC_AUTOMATA;
		ac_automata_init (m_aca, &match_handler);
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
	m_fuck_pingbi = (char *)malloc(len * sizeof(char *));
	//?¨¨¡¤???¨°???¡ê?2¡é¨ª3????¨ºy
	for(i = 0; i < len; ++i)
	{
		if(strchr("\r\n", str.c_str()[i]))
		{
			m_fuck_pingbi[i] = 0;
			count++;
		}
		else
			m_fuck_pingbi[i] = str.c_str()[i];
	}
	//?a??--??2????¨®??¡ê??¨¦?¨¹o¨®???1?¨¤¨°?DD??DD?¡ê
	//2?1y?¨®¨¢?¨°22?¨®¡ã?¨¬?¨¢1?
	barGoLink bg(--count);
	//?¨®¦Ì??¨¢¡À?¡Á¨¦?t?D?¡ê
	for (i = 0; i < len; ++i)
	{
		if(m_fuck_pingbi[i] == 0)
		{
			if(start != i)
			{
				tmp_str.id = id++;
				tmp_str.str = (ALPHA *)(m_fuck_pingbi + start);
				tmp_str.length = i - start;
				ac_automata_add_string(m_aca, &tmp_str);
				bg.step();
			}
			start = i + 1;
		}
	}
	ac_automata_locate_failure (m_aca);
	//std::cout << "Load  _fuck_pingbi.txt OK!" << std::endl;
	return true;
}

bool SvrCoreAppImpl::FuckPingbi(char* str)
{
	ASSERT(m_config.load_pingbi);
	STRING tmp_str;
	tmp_str.str = str;
	tmp_str.length = strlen(tmp_str.str);
	ac_automata_param param;
	param.str = str;
	param.ret = FALSE;
	ac_automata_search (m_aca, &tmp_str, &param);
	ac_automata_reset(m_aca);
	return param.ret != 0;
}