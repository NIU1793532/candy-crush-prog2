#include "util.h"
#include <filesystem>
#include <iostream>
#include <cmath>

int bitsPerObject(int objectCount) {
	return std::ceil(std::log2(objectCount));
}

std::vector<uint8_t> packToBytes(const std::vector<std::vector<Candy>>& board)
{

	int size = board.size() * board[0].size();
	int bits = bitsPerObject(static_cast<int>(CandyType::COUNT));
	int totalBytes = std::ceil((size * bits) / 8.0);
	std::vector<uint8_t> result(totalBytes, 0);
	uint bitPos = 0;

	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			Candy c = board[i][j];
			int candyByte = static_cast<int>(c.getType());
			for (int b = 0; b < bits; b++)
			{
				if ((candyByte >> b) & 1u) result[bitPos / 8] |= 1 << (bitPos % 8);
				bitPos++;
			}
		}
	}
	return result;
}

std::vector<std::vector<Candy>> unpackFromBytes(const std::vector<uint8_t>& data, int width, int height)
{
	int size = width * height;
	int bits = bitsPerObject(static_cast<int>(CandyType::COUNT));
	std::vector result(width, std::vector<Candy>(height, Candy(CandyType::NONE)));
	uint bitPos = 0;
	for (int i = 0; i < size; i++)
	{
		int candyByte = 0;
		for (int b = 0; b < bits; b++)
		{
			int currentByte = bitPos / 8;
			int currentBit = bitPos % 8;
			if (data[currentByte] & (1u << currentBit))
				candyByte |= 1u << b;

			bitPos++;
		}
		CandyType candyType = static_cast<CandyType>(candyByte);
		result[i % width][i / width] = Candy(candyType);
	}
	return result;
}

std::string getDataDirPath()
{
    const std::string current_dirname = std::filesystem::current_path().filename().generic_string();
    std::string resource_prefix = "";

    if (current_dirname == "drcandy"
        || current_dirname == "drcandy_public"
        || current_dirname == "drcandy_solution"
        || current_dirname == "source")
    {
        resource_prefix = "./";
    }
    else if (current_dirname == "src"
        || current_dirname == "build"
        || current_dirname == "visual_studio"
        || current_dirname.find("cmake") != std::string::npos)
    {
        resource_prefix = "../";
    }
    else if (current_dirname == "0. Windows Desktop")
    {
        resource_prefix = "../../";
    }
    else if (current_dirname == "Program")
    {
        resource_prefix = "../../../";
    }
    else
    {
        std::cerr << "Cannot find resources folder. Current directory: '"
            + current_dirname + "'.\nPlease run with run.sh or run.bat" << std::endl;
    }

    return resource_prefix + "data/";
}
