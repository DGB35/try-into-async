#include "Txt.h"

#include <iostream>
#include <fstream>
#include <mutex>

namespace l1
{
	Txt::Txt() : text{ nullptr }, stringCount{ 0 }
	{
	}

	Txt::Txt(const Txt& obj) : stringCount(obj.stringCount)
	{
		std::unique_lock<std::mutex> ul(m);
		std::string* text_clone = new std::string[obj.stringCount];
		for (size_t i = 0; i < obj.stringCount; ++i)
		{
			text_clone[i] = obj.text[i];
		}
		delete[] text;

		text = text_clone;
		stringCount = obj.stringCount;
	}

	Txt::Txt(Txt&& obj) noexcept
	{
		std::swap(text, obj.text);
		std::swap(stringCount, obj.stringCount);
	}

	Txt::Txt(const char* fileName) : Txt()
	{
		std::ifstream in(fileName);

		if (!in.is_open())
			std::cout << "File read error";

		while (in.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'))
			stringCount++;

		//Setting the file pointer to the beginning
		in.clear();
		in.seekg(0, std::ios::beg);

		text = new std::string[stringCount];

		std::string line;
		for (size_t i = 0; i < stringCount; ++i)
		{
			line.clear();
			std::getline(in, line);
			text[i] = line;
		}
	}


	Txt& l1::Txt::operator=(const Txt& obj)
	{
		if (this != &obj)
		{
			std::string* text_clone = new std::string [obj.stringCount];
			for (size_t i = 0; i < obj.stringCount; ++i)
			{
				text_clone[i] = obj.text[i];
			}
			delete[] text;

			text = text_clone;
			stringCount = obj.stringCount;
		}
		return *this;
	}


	Txt& Txt::operator=(Txt&& obj) noexcept
	{
		if (this != &obj)
		{
			std::swap(text, obj.text);
			std::swap(stringCount, obj.stringCount);
		}
		return *this;
	}


	void Txt::printText()
	{
		for (int i = 0; i < stringCount; ++i)
			std::cout << text[i] << '\n';
	}


	Txt::~Txt()
	{
		delete[] text;
	}

	void Txt::operator()(const char* fileName)
	{
		std::unique_lock<std::mutex> ul(m);
		delete[] text;
		stringCount = 0;

		std::ifstream in(fileName);

		if (!in.is_open())
			std::cout << "File read error";

		while (in.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'))
			stringCount++;

		//Setting the file pointer to the beginning
		in.clear();
		in.seekg(0, std::ios::beg);

		text = new std::string[stringCount];

		std::string line;
		for (size_t i = 0; i < stringCount; ++i)
		{
			line.clear();
			std::getline(in, line);
			text[i] = line;
		}
	}

}