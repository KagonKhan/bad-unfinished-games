#include "Pawn.h"


// ========================================    INITIALIZING PAWN    ========================================


Pawn::Pawn(const std::string texturePath, const sf::RectangleShape& tileBox, unsigned heightY) {
	setPawnGraphics(texturePath);
	setPawnColor(heightY);
	setPawnPosition(tileBox);
}

void Pawn::setPawnGraphics(const std::string texturePath) {
	pawnTexture.loadFromFile(texturePath);
	pawnSprite.setTexture(pawnTexture);
}

void Pawn::setPawnColor(unsigned heightY) {
	pawnColorType = 0; // none

	if (heightY < 3) {
		pawnSprite.setTextureRect(sf::IntRect(2 * 32, 0, 32, 32));
		pawnColorType = -1; // black
	}
	if (heightY > 4) {
		pawnSprite.setTextureRect(sf::IntRect(3 * 32, 0, 32, 32));
		pawnColorType = 1; //white
	}
}

void Pawn::setPawnPosition(const sf::RectangleShape& tileBox) {
	sf::Vector2f scale(tileBox.getSize().x / 32.f, tileBox.getSize().x / 32.f);
	pawnSprite.setScale(scale);

	float x = tileBox.getPosition().x + (tileBox.getGlobalBounds().width / 2.f) - pawnSprite.getGlobalBounds().width / 2.f;
	float y = tileBox.getPosition().y + (tileBox.getGlobalBounds().height / 2.f) - pawnSprite.getGlobalBounds().height / 2.f;
	sf::Vector2f position(x, y);

	pawnSprite.setPosition(position);
}


// ========================================    AUXILIARY FUNCTIONS    ========================================


int Pawn::getPawnColor() const {
	return pawnColorType;
}


void Pawn::render(sf::RenderTarget& target) {
	if(pawnColorType !=0)
		target.draw(pawnSprite);
}

void Pawn::setPawnPosition(sf::Vector2f position) {
	pawnSprite.setPosition(position);
}
