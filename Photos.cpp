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
	std::cout << "Start of function ReadDataFromFile()\n";
	std::cout << "std::this_thread::get_id(): "<<std::this_thread::get_id()<<'\n';

	std::cout << "Before sleep\n";
	Sleep(g_defaultDelay);
	std::cout << "After sleep\n";

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

	std::cout << "End of function ReadDataFromFile()\n";

	return m_names;
}

void Photos::ReadData()
{
	std::cout << "Start of function ReadData()\n";
	std::cout << "std::this_thread::get_id(): " << std::this_thread::get_id() << '\n';

	m_futureData = std::async(std::launch::async, &Photos::ReadDataFromFile, &*this);

	std::cout << "End of function ReadData()\n";
}

void Photos::OutputReadData()
{
	std::cout << "Start of function OutputReadData()\n";
	std::cout << "std::this_thread::get_id(): " << std::this_thread::get_id() << '\n';

	m_futureData.get();
	std::for_each(m_names.begin(), m_names.end(), [](std::string name) { std::cout << name << '\n'; });
	std::cout << "Vector size: " << m_names.size() << '\n';

	std::cout << "End of function OutputReadData()\n";
}
