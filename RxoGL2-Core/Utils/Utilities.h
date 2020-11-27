#pragma once
#include <string>
#include <fstream>
#include <filesystem>

#include <FreeImage.h>

namespace Utilities {

	static std::string ReadFile(const char* filepath)
	{
		FILE* file = fopen(filepath, "rt");
		std::ifstream ifs(file);
		std::string content(
			std::istreambuf_iterator<char>(ifs.rdbuf()),
			std::istreambuf_iterator<char>()
		); return content;
	}

	static BYTE* LoadTexture(const char* filePath, unsigned int& width, unsigned int& height)
	{
		//image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		//pointer to the image, once loaded
		FIBITMAP* dib(0);
		//pointer to the image data
		BYTE* bits(0);

		//check the file signature and deduce its format
		fif = FreeImage_GetFileType(filePath, 0);
		//if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filePath);
		//if still unkown, return failure
		if (fif == FIF_UNKNOWN)
			return nullptr;

		//check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filePath);
		//if the image failed to load, return failure
		if (!dib)
			return nullptr;

		//retrieve the image data
		bits = FreeImage_GetBits(dib);
		//get the image width and height
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);

		//Free FreeImage's copy of the data
		//FreeImage_Unload(dib);
		return bits;
	}
}