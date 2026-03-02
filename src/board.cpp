#include "board.h"
#include <memory>
#include <iostream>

Board::Board(int width, int height)
{
    // Implement your code here
}

Board::~Board()
{
    // Implement your code here
}


Candy* Board::getCell(int x, int y) const
{
    return cells[y][x];
}

void Board::setCell(Candy* candy, int x, int y)
{
    if (x > BOARD_WIDTH || y > BOARD_HEIGHT)
    {
        cout << "ERROR when setting cell bounds" << endl;
        exit(1);
    }
    cells[x][y] = candy;
}


int Board::getWidth() const
{
    // Implement your code here
    return -1;
}


int Board::getHeight() const
{
    // Implement your code here
    return -1;
}

bool Board::shouldExplode(int x, int y) const
{
    // Implement your code here
    return false;
}

std::vector<Candy*> Board::explodeAndDrop()
{
    // Implement your code here
    return {};
}

bool Board::dump(const std::string& output_path) const
{
    // Implement your code here
    return false;
}

bool Board::load(const std::string& input_path)
{
    // Implement your code here
    return false;
}
