#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states) {
	this->window = window;
	this->states = states;
	dt = 0.f;
	keytime = 0.f;
	keytimeMax = 25.f;
}

State::~State()
{
}

void State::updateMousePosition() {
	mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void State::updateDT() {
	this->dt = dtClock.restart().asSeconds();
}

void State::updateSFMLEvents() {
	while (window->pollEvent(sfEvent))
		switch (sfEvent.type) {

		case sf::Event::Closed:
			window->close();
		}

}

void State::updateKeytime() {
	if (keytime < keytimeMax)
		keytime += 105.f * dt;
}

const bool State::getKeytime() {
	if (this->keytime >= this->keytimeMax) {
		this->keytime = 0.f;
		return true;
	}
	return false;
}
