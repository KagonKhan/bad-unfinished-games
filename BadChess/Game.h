#pragma once
#include "MainMenuState.h"


class Game {

	sf::RenderWindow* window;

	std::stack<State*> states;


	int cellSize;


	void initWindow();
	void initVariables();
	void initStates();


	void update();
	void render();


public:

	Game();
	~Game();

	void run();


};

