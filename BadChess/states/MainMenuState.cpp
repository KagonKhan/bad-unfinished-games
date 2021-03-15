#include "MainMenuState.h"
#include "GameState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states)
	: State(window, states) {

	initBackground();
	initButtons();
}

MainMenuState::~MainMenuState() {

}

void MainMenuState::initBackground() {
	background.setSize((sf::Vector2f)window->getSize());
	background.setFillColor(sf::Color::Yellow);
}

void MainMenuState::initButtons() {
	buttons["START"] = new GUI(
		sf::Vector2f(250.f, 125.f),
		sf::Vector2f(((sf::Vector2f)window->getSize() - sf::Vector2f(250.f, 500.f)) / 2.f),
		sf::Color::Blue);

		buttons["QUIT"] = new GUI(
		sf::Vector2f(250.f, 125.f),
		sf::Vector2f(((sf::Vector2f)window->getSize() - sf::Vector2f(250.f, 100.f)) / 2.f),
		sf::Color::Red);



}

void MainMenuState::renderButtons() {
	for (auto it : buttons)
		it.second->render(window);
}

void MainMenuState::updateButtons() {
	if (buttons["START"]->getIsPressed(mousePosition))
		states->push(new GameState(window, states));

	if (buttons["QUIT"]->getIsPressed(mousePosition))
		states->pop();
}


void MainMenuState::update() {
	updateSFMLEvents();
	updateMousePosition();
	updateDT();
	updateButtons();
}



void MainMenuState::render() {
	window->draw(background);
	renderButtons();
}
