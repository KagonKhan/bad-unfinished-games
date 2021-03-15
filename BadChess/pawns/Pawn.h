#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

class Pawn {


protected:
	sf::Texture pawnTexture;
	sf::Sprite pawnSprite;

	short pawnColorType; // 0 - none, -1 black, 1 white

	void setPawnGraphics(const std::string texturePath);
	virtual void setPawnColor(unsigned heightY);
	void setPawnPosition(const sf::RectangleShape& tileBox);


public:
	Pawn() {};
	Pawn(const std::string texturePath, const sf::RectangleShape& tileBox, unsigned heightY);

	void setPawnPosition(sf::Vector2f position);

	int getPawnColor() const ; // ifint color = -1 black, if 1 white

	void render(sf::RenderTarget& target);

};
