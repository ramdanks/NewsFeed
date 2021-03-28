#include "Formatting.h"

namespace Formatting
{
	std::string GetFilename(const std::string& filepath)
	{
		const size_t idxSeperator = filepath.find_last_of("\\/");
		auto c = filepath.c_str();
		return std::string(&c[idxSeperator+1], filepath.length() - idxSeperator);
	}

	std::string GetDirpath(const std::string& filepath)
	{
		const size_t idxSeperator = filepath.find_last_of("\\/");
		auto c = filepath.c_str();
		return std::string(&c[0], idxSeperator);
	}
}
