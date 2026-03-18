#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "candy.h"

/// @return the dynamic path to the "data" folder.
///   The path is relative to the current working directory, which may vary
///   depending on how the program is run. This prefix followed by the resource
///   (e.g., "img/candy/red.png") yields the complete file path of the resource.
std::string getDataDirPath();

std::vector<uint8_t> packToBytes(const std::vector<std::vector<Candy>>& board);

std::vector<std::vector<Candy>> unpackFromBytes(const std::vector<uint8_t>& data, int width, int height);

int bitsPerObject(int objectCount);