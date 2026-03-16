/**
 * Each of the candy pieces in the game.
 */
#ifndef CANDY_H
#define CANDY_H

#include <string>

/// Types of candy
enum class CandyType
{
    NONE,
    TYPE_RED,
    TYPE_BLUE,
    TYPE_GREEN,
    TYPE_YELLOW,
    TYPE_PURPLE,
    TYPE_ORANGE,
    COUNT
};

static char candySymbol(CandyType type)
{
	switch (type)
	{
		case CandyType::TYPE_RED: return 'R';
		case CandyType::TYPE_BLUE: return 'B';
		case CandyType::TYPE_GREEN: return 'G';
		case CandyType::TYPE_YELLOW: return 'Y';
		case CandyType::TYPE_PURPLE: return 'P';
		case CandyType::TYPE_ORANGE: return 'O';
		default: return '.';
	}
}

/// Width of each candy image, in pixels
const int CANDY_IMAGE_WIDTH = 47;
/// Height of each candy image, in pixels
const int CANDY_IMAGE_HEIGHT = 47;

/**
 * A piece of candy on the board.
*/
class Candy
{
public:
    /// Constructs a unique candy piece of the given type.
    explicit Candy(CandyType candyType);

    /// @return the type of this candy instance.
    CandyType getType() const;

    /// @return the resource name for the candy, e.g., "img/candy/red.png", 
    /// ready to be passed as argument to GraphicsManager::draw_image.
    std::string getResourceName() const;

	bool operator==(const Candy& other) const;

protected:
    /// the type of this candy instance.
    CandyType m_type;
};
#endif
