#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>

class GUI {
	sf::RectangleShape rectangle;

public:
	//Constructor for buttons: Size, Position, Color
	GUI(sf::Vector2f buttonSize, sf::Vector2f buttonPosition, sf::Color buttonColor);



	void update(sf::Vector2f mousePosition);
	bool getIsPressed(sf::Vector2f mousePosition);
	void render(sf::RenderWindow* window);
};

