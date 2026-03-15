#include "test.h"

#include <filesystem>
#include "board.h"
#include "candy.h"
#include "controller.h"
#include "game.h"
#include "util.h"
#include <iostream>

using namespace std;

bool test()
{
    if (!testBoardBasics()) {
        cout << "Error while testing boardBasics()" << endl;
        return false;
    }
    if (!testBoardShouldExplode()) {
        cout << "Error while testing testBoardShouldExplode()" << endl;
        return false;
    }
	if (!testDumpLoad()) {
		cout << "Error while testing testDumpLoad()" << endl;
		return false;
	}
    return true;
}

bool testBoardBasics()
{
    Board b = Board(10, 10);
    if (b.getCell(0, 0)->getType() != CandyType::NONE)
    {
        return false;
    }

    b.setCell(new Candy(CandyType::TYPE_BLUE), 6, 7);
    b.setCell(new Candy(CandyType::TYPE_RED), 7, 6);
    if (b.getCell(6, 7)->getType() != CandyType::TYPE_BLUE || b.getCell(7, 6)->getType() != CandyType::TYPE_RED)
    {
        return false;
    }

    if (b.getHeight() != 10 || b.getWidth() != 10) {
        return false;
    }

    return true;
}

bool testBoardShouldExplode()
{
    // Horizontal test
    {
        Board board(5,5);

        for (int x=0;x<5;x++)
            for (int y=0;y<5;y++)
                board.setCell(new Candy(CandyType::TYPE_BLUE),x,y);

        board.setCell(new Candy(CandyType::TYPE_RED),1,2);
        board.setCell(new Candy(CandyType::TYPE_RED),2,2);
        board.setCell(new Candy(CandyType::TYPE_RED),3,2);

        if (!board.shouldExplode(2,2))
            return false;
    }

    // Vertical test
    {
        Board board(5,5);

        for (int x=0;x<5;x++)
            for (int y=0;y<5;y++)
                board.setCell(new Candy(CandyType::TYPE_BLUE),x,y);

        board.setCell(new Candy(CandyType::TYPE_RED),2,1);
        board.setCell(new Candy(CandyType::TYPE_RED),2,2);
        board.setCell(new Candy(CandyType::TYPE_RED),2,3);

        if (!board.shouldExplode(2,2))
            return false;
    }

    // Ascending diagonal
    {
        Board board(5,5);

        for (int x=0;x<5;x++)
            for (int y=0;y<5;y++)
                board.setCell(new Candy(CandyType::TYPE_BLUE),x,y);

        board.setCell(new Candy(CandyType::TYPE_RED),1,1);
        board.setCell(new Candy(CandyType::TYPE_RED),2,2);
        board.setCell(new Candy(CandyType::TYPE_RED),3,3);

        if (!board.shouldExplode(2,2))
            return false;
    }

    // Descending diagonal
    {
        Board board(5,5);

        for (int x=0;x<5;x++)
            for (int y=0;y<5;y++)
                board.setCell(new Candy(CandyType::TYPE_BLUE),x,y);

        board.setCell(new Candy(CandyType::TYPE_RED),1,3);
        board.setCell(new Candy(CandyType::TYPE_RED),2,2);
        board.setCell(new Candy(CandyType::TYPE_RED),3,1);

        if (!board.shouldExplode(2,2))
            return false;
    }

    // No explosion
    {
        Board board(5,5);

        for (int x=0;x<5;x++)
            for (int y=0;y<5;y++)
                board.setCell(new Candy(CandyType::TYPE_BLUE),x,y);

        board.setCell(new Candy(CandyType::TYPE_RED),2,2);

        if (board.shouldExplode(2,2))
            return false;
    }

    return true;
}

bool testDumpLoad()
{
    // Test board 2D container
    Candy c = Candy(CandyType::TYPE_ORANGE);
    Board b(10, 10);
    b.setCell(&c, 0, 0);
	Candy c2 = Candy(CandyType::TYPE_BLUE);
    b.setCell(&c2, 3, 3);

	if (*b.getCell(0, 0) != c)
    {
        return false;
    }

	// Dump and load board
    {
        Board b2(10, 10);
        if (!b.dump(getDataDirPath() + "dump_board.txt"))
        {
            return false;
        }
        if (!b2.load(getDataDirPath() + "dump_board.txt"))
        {
            return false;
        }
        if (b2.getCell(0, 0)->getType() != c.getType())
        {
            return false;
        }
        std::filesystem::remove(getDataDirPath() + "dump_board.txt");
    }

	// TODO: TEST DUMP AND LOAD GAME
	return true;
    // Dump and load game
    {
        Game g;
        Controller cont;
        g.update(cont);
        if (!g.dump(getDataDirPath() + "dump_game.txt"))
        {
            return false;
        }
        Game g2;
        if (!g2.load(getDataDirPath() + "dump_game.txt"))
        {
            return false;
        }
        if (g != g2)
        {
            return false;
        }
        std::filesystem::remove(getDataDirPath() + "dump_game.txt");
    }
    return true;
}
