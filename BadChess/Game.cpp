#include "Game.h"

Game::Game() {

	initVariables();
	initWindow();
	initStates();
}

Game::~Game() {
	delete this->window;
}

void Game::initVariables() {
	cellSize = 100;
}

void Game::initWindow() {
	this->window = new  sf::RenderWindow(sf::VideoMode(13* cellSize, 10*cellSize), "checkers");
	this->window->setFramerateLimit(60);

}




void Game::initStates() {
	states.push(new MainMenuState(window, &states));
}



void Game::update() {

	if (!this->states.empty())
		this->states.top()->update();
	else
		window->close();
}

void Game::render() {
	window->clear();

	if (!this->states.empty())
		this->states.top()->render();

	window->display();
}

void Game::run() {
	while (window->isOpen()) {
		update();
		render();
	}
}



