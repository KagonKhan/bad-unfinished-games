#include "King.h"

King::King(const std::string texturePath, const sf::RectangleShape& tileBox, unsigned heightY) {
	setPawnGraphics(texturePath);
	setPawnPosition(tileBox);
	setPawnColor(heightY);
	std::cout << "Creating king\n";

}

void King::setPawnColor(unsigned heightY) {
	pawnColorType = 0; // none

	if (heightY < 3) {
		pawnSprite.setTextureRect(sf::IntRect(0 * 32, 0, 32, 32));
		pawnColorType = -1; // black
	}
	if (heightY > 4) {
		pawnSprite.setTextureRect(sf::IntRect(1 * 32, 0, 32, 32));
		pawnColorType = 1; //white
	}
}