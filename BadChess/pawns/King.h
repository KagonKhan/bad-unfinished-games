#pragma once
#include "Pawn.h"
class King : public Pawn {


	void setPawnColor(unsigned heightY);

public:
	King(const std::string texturePath, const sf::RectangleShape& tileBox, unsigned heightY);
};

