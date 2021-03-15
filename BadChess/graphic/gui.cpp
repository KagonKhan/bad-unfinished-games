#include "gui.h"



GUI::GUI(sf::Vector2f buttonSize, sf::Vector2f buttonPosition, sf::Color buttonColor) {
	rectangle.setSize(buttonSize);
	rectangle.setPosition(buttonPosition);
	rectangle.setFillColor(buttonColor);
}

void GUI::update(sf::Vector2f mousePosition) {
}

bool GUI::getIsPressed(sf::Vector2f mousePosition) {
	if (rectangle.getGlobalBounds().contains(mousePosition))
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			return true;

	return false;
	
}

void GUI::render(sf::RenderWindow* window) {
	window->draw(rectangle);
}
	