#pragma once

#include <string>

namespace Galaxy
{
	class FileDialogs
	{
	public:
		static std::string OpenFile(const char* filters);
		static std::string SaveFile(const char* filters);
	};
}