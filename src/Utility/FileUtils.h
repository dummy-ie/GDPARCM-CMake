#pragma once

#include <filesystem>
#include <iostream>

namespace gd
{
	class FileUtils
	{
	public:
		// gets the path of the src folder from the bin folder in the build
		static inline std::filesystem::path getSourceFolderPath();
		static inline std::filesystem::path getFileFromSourceFolder(const std::filesystem::path& fileName);
		static inline std::filesystem::path getFileFromAssetsFolder(const std::filesystem::path& fileName);
	};

	inline std::filesystem::path FileUtils::getSourceFolderPath()
	{
		// lmao
		return std::filesystem::current_path().parent_path().parent_path().parent_path().parent_path().append("src\\");
	}

	inline std::filesystem::path FileUtils::getFileFromSourceFolder(const std::filesystem::path& fileName)
	{
		return getSourceFolderPath() / fileName; // append two paths is / operator for some reason
	}

	inline std::filesystem::path FileUtils::getFileFromAssetsFolder(const std::filesystem::path& fileName)
	{
		return getFileFromSourceFolder("Assets\\") / fileName; 
	}

}