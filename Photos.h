#pragma once
#include "pch.h"

class Photos
{
public:
	Photos();
	explicit Photos(const std::string & fileName, int delay);
	Photos(const Photos&) = delete;
	Photos& operator=(const Photos&) = delete;
	~Photos();

	void ReadData();
	void OutputReadData();
	
private:
	std::vector<std::string> ReadDataFromFile();
	
private:
	std::future< std::vector<std::string> > m_futureData;
	std::vector<std::string> m_names { };
	std::string m_fileName;
	int m_delay;
};

