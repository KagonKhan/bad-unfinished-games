#pragma once
#include "State.h"
class MainMenuState : public State {
	sf::RectangleShape background;

	void initBackground();

	sf::Event sfEvent;

	void initButtons();
	void renderButtons();
	void updateButtons();



public:
	MainMenuState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~MainMenuState();


	void update();
	void render();

};

