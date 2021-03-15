#pragma once
#include <stack>
#include <map>


#include "SFML/Graphics.hpp"
#include "gui.h"

class State {
protected:
	sf::RenderWindow* window;
	std::stack<State*>* states;
	sf::Vector2f mousePosition;

	sf::Event sfEvent;

	std::map<std::string, GUI*> buttons;

	float keytime, keytimeMax;

	float dt;
	sf::Clock dtClock;


	void updateMousePosition();
	void updateDT();
	void updateSFMLEvents();
	void updateKeytime();
	const bool getKeytime();

	virtual void initButtons() = 0;
	virtual void renderButtons() = 0;



public:
	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();

	virtual void render() = 0;
	virtual void update() = 0;

};

