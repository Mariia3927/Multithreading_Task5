#include "pch.h"
#include "Photos.h"


Photos::Photos() : m_fileName(g_defaultFileName), m_delay(g_defaultDelay)
{
}

Photos::Photos(const std::string & fileName = g_defaultFileName, int delay = g_defaultDelay) : m_fileName(fileName), m_delay(delay)
{
}


Photos::~Photos()
{
}

std::vector<std::string> Photos::ReadDataFromFile()
{
	Sleep(g_defaultDelay);

	std::fstream fin(m_fileName, std::ios::in);
	if (!fin)
	{
		std::cout << "Error! Cannot open file!\n";
		return std::vector<std::string>{};
	}

	std::string tmp = "";
	while (std::getline(fin, tmp))
	{
		m_names.push_back(tmp);
	}

	fin.close();

	return m_names;
}

void Photos::ReadData()
{
	m_futureData = std::async(std::launch::async, &Photos::ReadDataFromFile, &*this);
}

void Photos::OutputReadData()
{
	m_futureData.get();
	std::for_each(m_names.begin(), m_names.end(), [](std::string name) { std::cout << name << '\n'; });
	std::cout << "Vector size: " << m_names.size() << '\n';
}
