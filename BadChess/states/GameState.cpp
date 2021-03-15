#include "GameState.h"
#include <typeinfo>

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
	: State(window, states) {

	initBackground();
	initButtons();

	initVariables();

	initTiles();
}

GameState::~GameState() {

	//for (auto it = Tiles.begin(); it != Tiles.end(); ++it)
		//delete it->second;
}

void GameState::initBackground() {
	background.setSize((sf::Vector2f)window->getSize());
	background.setFillColor(sf::Color::Yellow); std::vector<std::string> _2kWords;
	std::vector<std::string> _4kWords;
	std::vector<std::string> _8kWords;
	std::vector<std::string> _16kWords;
	std::vector<std::string> _32kWords;

	std::vector<int> _8kNums;
	std::vector<int> _16kNums;
	std::vector<int> _32kNums;
	std::vector<int> _64kNums;
	std::vector<int> _128kNums;
}

void GameState::initButtons() {
	buttons["SAVE"] = new GUI(
		sf::Vector2f(450.f, 125.f),
		sf::Vector2f(window->getSize().x - 250.f, 0.f),
		sf::Color::Blue);

	buttons["LOAD"] = new GUI(
		sf::Vector2f(450.f, 125.f),
		sf::Vector2f(window->getSize().x - 250.f, 150.f),
		sf::Color::Red);

	buttons["BACK"] = new GUI(
		sf::Vector2f(450.f, 125.f),
		sf::Vector2f(window->getSize().x - 250.f, 650.f),
		sf::Color::Red);

}

void GameState::initTiles() {
	for (int y = 0; y < 8; y++)
		for (int x = 0; x < 8; x++)
			this->Tiles[y][x] = new Tile(x, y); // should handle pieces automatically
}

void GameState::initVariables() {
	cellSize = 100;

	amountOfPieces = 24;
	playerTurn = -1;
	whitePieces = blackPieces = 12;

	origin = destination = inBetweenTile = nullptr;
}

void GameState::update() {
	updateSFMLEvents(); // SFML Event objects

	updateMousePosition(); // Mouse positions.. duh

	updateDT();

	updateKeytime(); // timing for pressing buttons

	updateTiles(); // update tiles, which update pawns

	updateButtons();


}

void GameState::updateTiles() {
	for (int y = 0; y < 8; y++)
		for (int x = 0; x < 8; x++) {
			Tiles[y][x]->updateTile(mousePosition);

			if (Tiles[y][x]->getIsPressed() && getKeytime()) {
				logic(Tiles[y][x]);
			}
		}

}

void GameState::updateButtons() {
	if (buttons["SAVE"]->getIsPressed(mousePosition) && getKeytime())
		save();
	if (buttons["LOAD"]->getIsPressed(mousePosition) && getKeytime())
		load();
	if (buttons["BACK"]->getIsPressed(mousePosition) && getKeytime())
		states->pop();

}

void GameState::checkForWin() {
	if (blackPieces <= 0) {
		std::cout << "Whites won!\n";
		window->close();
	}
	if (whitePieces <= 0) {
		std::cout << "Blacks won!\n";
		window->close();
	}
}

void GameState::updatePromotions() {

	if (typeid(*destination->getPawn()) == typeid(King))
		return;

	destination->setPawnOnTile(nullptr);
	King* test = new King("../Resources/Image/checkers.png", destination->getRectangle(), origin->getPieceOnTile() < 0 ? 1 : 5);
	destination->setPawnOnTile(test);
	test = nullptr;
	std::cout << typeid(*destination->getPawn()).name();

}

void GameState::render() {
	window->draw(background);
	renderButtons();
	renderTiles();
}

void GameState::renderTiles() {
	for (int y = 0; y < 8; y++)
		for (int x = 0; x < 8; x++)
			Tiles[y][x]->renderTile(*window);
}

void GameState::renderButtons() {
	for (auto& it : buttons)
		it.second->render(window);
}







void GameState::logic(Tile* tile) {

	//if origin doesnt already exist, check if clicked tile is a valid origin
	if (!origin || origin == tile) {
		if (checkLogicOrigin(tile));

	}

	if (origin) { // check if origin exist, without it no destination
		if (checkLogicDestination(tile));
	}

	// All logic checked. MOVE

	if (origin && destination) {


		move();


		origin->setPawnOnTile(nullptr);
		destination->setTileActive(false);
		origin = destination = inBetweenTile = nullptr;
		playerTurn *= -1;
	}

}



bool GameState::checkLogicOrigin(Tile* tile) {
	//If there is no pawn on origin tile, it's not a valid origin
	if (!tile->getPawn())
		return false;

	if (playerTurn == tile->getPawn()->getPawnColor()) { // if -1 play black if 1 play white
		if (!origin) { // if there is no origin
			origin = tile;
			tile->setTileActive(true);
		}
		else if (origin == tile) {// check if origin has been "unclicked"
			origin = nullptr;
			tile->setTileActive(false);
			return false;
		}
	}
	else {
		//std::cout << "NOT YOUR PAWN DUMBASS\n";
		return false;
	}

	return true;
}

bool GameState::checkLogicDestination(Tile* tile) {
	if (tile->getPawn()) // IF IT HAS A PAWN - CANNOT MOVE ONTO THAT 
		return false;


	sf::Vector2i difference = origin->getTileCoordinates() - tile->getTileCoordinates();



	//LOAD POSSIBLE JUMPS
	checkIfTakePossible(origin->getTileCoordinates());

	std::cout << "Desired jump:\n" << tile->getTileCoordinates().x << ", " << tile->getTileCoordinates().y << "\n";
	if (!possibleJumps.empty()) {
		std::cout << "Possible jumps:\n";

		int index = 0;
		bool isDestination = false;

		for (int index = 0; index < possibleJumps.size(); index++) {

			std::cout << possibleJumps[index].x << ", " << possibleJumps[index].y << "\n";

			if (possibleJumps[index] == tile->getTileCoordinates()) {
				std::cout << " I AM TRUE";
				isDestination = true;
			}
		}

		if (isDestination == false)
			return false;
	}



	if (playerTurn == 1 && difference.y < 0 && typeid(*origin->getPawn()) == typeid(Pawn)) {
		//std::cout << "can't go back!\n";
		return false;
	}
	if (playerTurn == -1 && difference.y > 0 && typeid(*origin->getPawn()) == typeid(Pawn)) {
		//std::cout << "can't go back!\n";
		return false;
	}



	/*Check for diagonality of jump*/

	if (std::abs(difference.x) != std::abs(difference.y)) {
		//std::cout << "NOT DIAGONAL\n";
		return false;
	}

	/*Check for length of a jump*/

	int length = difference.x * difference.x + difference.y * difference.y;


	if (length > 8) {
		//std::cout << "Jump length too long!\n";
		return false;
	}

	//if there is an intermediate enemy pawn you can jump > 4
	if (length > 4) {
		//std::cout << "[INFO]Checking intermediary!\n";
		if (!intermediary(origin, tile)) // if doesnt exist, cant jump that far
			return false;
	}


	destination = tile;
	tile->setTileActive(tile);


	return true;
}

bool GameState::intermediary(Tile* tile1, Tile* tile2) {
	sf::Vector2i difference = (tile2->getTileCoordinates() - tile1->getTileCoordinates()) / 2;

	sf::Vector2i tilePosition = tile1->getTileCoordinates() + difference;



	if (Tiles[tilePosition.y][tilePosition.x]->getPawn()) {
		if (playerTurn == Tiles[tilePosition.y][tilePosition.x]->getPawn()->getPawnColor()) {
			//std::cout << "You cant jump over your own pawns!\n";
			return false;
		}
		else {
			return inBetweenTile = Tiles[tilePosition.y][tilePosition.x];
			return true;
		}
	}

	return false;
}

// MIGHT THROW ERRORS IF OUT OF BOUNDS DID NOT CHECK WARNING WARINNGG
bool GameState::checkIfMultiJump(sf::Vector2i checkAtOrigin) {

	possibleCoordsToMultiJump.clear();

	for (int y = -1; y <= 1; y += 2)
		for (int x = -1; x <= 1; x += 2) {
			if (checkAtOrigin.y + y + y >= 0 && checkAtOrigin.y + y + y <= 7 && checkAtOrigin.x + x + x >= 0 && checkAtOrigin.x + x + x <= 7)
				if (abs(x) == abs(y))
					if (Tiles[checkAtOrigin.y + y][checkAtOrigin.x + x]->getPawn())
						if (Tiles[checkAtOrigin.y + y][checkAtOrigin.x + x]->getPieceOnTile() == playerTurn * (-1))
							if (Tiles[checkAtOrigin.y + y + y][checkAtOrigin.x + x + x]->getPieceOnTile() == 0) {
								possibleCoordsToMultiJump.push_back(sf::Vector2i(checkAtOrigin.x + x + x, checkAtOrigin.y + y + y));
							}
		}


	return false;
}

void GameState::move() {

	sf::Vector2i difference = origin->getTileCoordinates() - destination->getTileCoordinates();
	int length = difference.x * difference.x + difference.y * difference.y;

	origin->setTileActive(false);

	destination->setPawnOnTile(origin->getPawn());

	origin->setPawnOnTile(nullptr);

	if (length > 4) { // if long jump, must jump over so kill
		if (inBetweenTile->getPawn()->getPawnColor() == -1)
			blackPieces--;
		if (inBetweenTile->getPawn()->getPawnColor() == 1)
			whitePieces--;

		checkForWin();

		inBetweenTile->setPawnOnTile(nullptr);
	}
	if (destination->getTileCoordinates().y == 0 && destination->getPawn()->getPawnColor() == 1) {
		updatePromotions();
	}
	else if (destination->getTileCoordinates().y == 7 && destination->getPawn()->getPawnColor() == -1) {
		updatePromotions();
	}

}



// I THINK THIS WORKS
bool GameState::checkIfTakePossible(sf::Vector2i originCoords) {

	//PREPARE THE VECTOR 
	possibleJumps.clear();

	// CHECK AROUND THE PIECE
	for (int y = -1; y <= 1; y += 2) {
		for (int x = -1; x <= 1; x += 2) {
			//CHECK IF WE ARENT OUT OF BOUNDS OF THE BOARD
			if (originCoords.y + y + y <= 7 && originCoords.y + y + y >= 0 && originCoords.x + x + x <= 7 && originCoords.x + x + x >= 0) {
				//CHECK IF AROUND THE IS A PIECE
				if (Tiles[originCoords.y + y][originCoords.x + x]->getPawn()) {
					//CHECK IF ITS ENEMY PAWN
					if (Tiles[originCoords.y + y][originCoords.x + x]->getPawn()->getPawnColor() != playerTurn) {
						// CHECK IF ITS DIAGONAL
						if (abs(x) == abs(y)) {
							//CHECK IF A TILE AFTER PIECE IS EMPTY - CAN JUMP THERE
							if (!Tiles[originCoords.y + y + y][originCoords.x + x + x]->getPawn()) {
								//  CHECK PAWN CLASS - KING?
								if (typeid(*Tiles[originCoords.y][originCoords.x]->getPawn()) != typeid(King)) {
									// CHECK IF ITS BLACK
									if (Tiles[originCoords.y][originCoords.x]->getPawn()->getPawnColor() == -1) {
										// MAKE SURE HE DOESNT GO BACK
										if (originCoords.y + y >= originCoords.y) {
											// FILL OUT THE VECTOR OF POSSIBLE JUMPS
											possibleJumps.push_back(sf::Vector2i(originCoords.x + x + x, originCoords.y + y + y));
										}
									}
									// CHECK IF ITS WHITE
									else if (Tiles[originCoords.y][originCoords.x]->getPawn()->getPawnColor() == 1) {
										// MAKE SURE HE DOESNT GO BACK
										if (originCoords.y + y <= originCoords.y) {
											std::cout << " I AM WHITE";
											// FILL OUT THE VECTOR OF POSSIBLE JUMPS
											possibleJumps.push_back(sf::Vector2i(originCoords.x + x + x, originCoords.y + y + y));				
										}
									}
								}
								// IF ITS A KING
								else if (typeid(*Tiles[originCoords.y][originCoords.x]->getPawn()) == typeid(King)) {
									possibleJumps.push_back(sf::Vector2i(originCoords.x + x + x, originCoords.y + y + y));
								
								}
							}
						}
					}
				}
			}
		}
	}


	// IF THERE ARE POSSIBLE JUMPS
	if (!possibleJumps.empty())
		return true;

	//IF NOT
	return false;
}

void GameState::save() {
	std::string savingstring = "";

	for (int y = 0; y < 8; y++)
		for (int x = 0; x < 8; x++) {
			if (Tiles[y][x]->getPawn()) {
				if (typeid(*Tiles[y][x]->getPawn()) == typeid(King)) {
					Tiles[y][x]->getPieceOnTile() < 0 ? savingstring += "-2 " : savingstring += "2 ";

				}
				else
					savingstring += std::to_string(Tiles[y][x]->getPieceOnTile()) + " ";
			}
			else
				savingstring += "0 ";
		}


	savingstring += std::to_string(playerTurn) + " ";
	std::ofstream file("saves/save.txt");
	file << savingstring;
	file.close();
}

void GameState::load() {
	std::ifstream file("saves/save.txt");
	int a, it{ 0 };
	int white = 0;
	int black = 0;

	for (int y = 0; y < 8; y++)
		for (int x = 0; x < 8; x++) {
			if (Tiles[y][x]->getPawn())
				Tiles[y][x]->killTilePawn();
			Tiles[y][x]->setTileActive(false);

		}

	origin = destination = inBetweenTile = nullptr;

	while (file >> a) {
		if (a && it < 64) {
			Tiles[it / 8][it % 8]->loadTilePiece(a);

			a > 0 ? white++ : black++;

		}
		else
			playerTurn = a;
		it++;

	}
	whitePieces = white;
	blackPieces = black;
	file.close();
}

