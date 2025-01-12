#pragma once

#include <filesystem>
#include <iostream>

namespace gd
{
	class FileUtility
	{
	public:
		// gets the path of the src folder from the bin folder in the build
		static inline std::filesystem::path getSourceFolderPath();
		static inline std::filesystem::path getFileFromSourceFolder(const std::filesystem::path& fileName);
	};

	inline std::filesystem::path FileUtility::getSourceFolderPath()
	{
		// lmao
		return std::filesystem::current_path().parent_path().parent_path().parent_path().parent_path().append("src\\");
	}

	inline std::filesystem::path FileUtility::getFileFromSourceFolder(const std::filesystem::path& fileName)
	{
		return getSourceFolderPath() / fileName; // append two paths is / operator for some reason
	}

}