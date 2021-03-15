#include "Tile.h"


void Tile::setTilePosition(int x, int y) {
	this->tileCoordinates = sf::Vector2i(x, y);
	this->tile.setPosition(sf::Vector2f(float(x * (cellSize + 1)), float(y * (cellSize + 1))));

}

void Tile::setTileGraphics(int x, int y) {
	this->tile.setSize(sf::Vector2f(float(cellSize), float(cellSize)));

	this->tile.setFillColor(sf::Color::White);

	if ((x + y) % 2!= 0)
		this->tile.setFillColor(sf::Color::Black);

	

	tileMask = tile; // for hightlighting
	tileMask.setFillColor(sf::Color::Transparent);
	tileMask.setOutlineThickness(1.f);
}

void Tile::setTilePawn(int x, int y) {

	if ((x + y) % 2 != 0) {
		if (y < 3)
			pawn = new Pawn("../Resources/Image/checkers.png", tile, y);

		if (y > 4)
			pawn = new Pawn("../Resources/Image/checkers.png", tile, y);
	}

}

Tile::Tile(int x, int y) {
	tileState = TileStates::TILE_IDLE;
	pieceOnTileType = 0;
	tileStaysActive = false;
	pawn = nullptr;



	if (x >= 0 and x < 8 and y >= 0 and y < 8) {
		setTilePosition(x, y);
		setTileGraphics(x, y);
		setTilePawn(x, y);
	}
	else
		std::cout << "INCORRECT COORDINATES!\n";


}


//==============================              SETTERS             ============================


void Tile::killTilePawn() {
	if (this->pawn !=nullptr)
		delete this->pawn;
	pawn = nullptr;
}

void Tile::setPawnOnTile(Pawn* pawn) {
	this->pawn = pawn;
	pawn = nullptr;

	sf::Vector2f position = tile.getPosition();
	if(this->pawn)
		this->pawn->setPawnPosition(position);
}


//==============================              GETTERS             ============================


const int Tile::getPieceOnTile() const {
	return this->pieceOnTileType;
}

const bool Tile::getIsPressed() const {
	if (this->tileState == TileStates::TILE_ACTIVE)
		return true;

	return false;
}


const bool Tile::getIsActive() const {
	if (tileStaysActive)
		return true;
	return false;
}

const sf::Vector2i Tile::getTileCoordinates() {
	return tileCoordinates;
}


//==============================              UPDATES             ============================


void Tile::updateTile(const sf::Vector2f& mousePos) {
	updateTilePiece();
	updateTileState(mousePos);
	updateTileColoring();
}

void Tile::updateTilePiece() {
	if (pawn)
		pieceOnTileType = pawn->getPawnColor();
	else
		pieceOnTileType = 0; // fragment later to another function
}

void Tile::updateTileState(const sf::Vector2f& mousePos) {
	if (!tileStaysActive)
		this->tileState = TileStates::TILE_IDLE;

	//HOVERED
	if (this->tile.getGlobalBounds().contains(mousePos)) {
		this->tileState = TileStates::TILE_HOVER;

		//PRESSING
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->tileState = TileStates::TILE_ACTIVE;

	}
}

void Tile::updateTileColoring() {

	if (tileStaysActive)
		this->tileMask.setFillColor(sf::Color(255, 100, 0, 150));
	else
		this->tileMask.setFillColor(sf::Color::Transparent);

	//COLORING
	switch (this->tileState) {
	case TileStates::TILE_IDLE:
		this->tileMask.setFillColor(sf::Color::Transparent);
		break;

	case TileStates::TILE_HOVER:
		this->tileMask.setOutlineColor(sf::Color(225,100,0,100));
		break;

	case TileStates::TILE_ACTIVE:
		this->tileMask.setFillColor(sf::Color(0,255,100,100));
		break;

	default:

		break;
	}
}



//==============================              RENDER             ============================

void Tile::renderTile(sf::RenderTarget& target) {
	target.draw(this->tile);
	target.draw(this->tileMask);

	if (pawn)
		pawn->render(target);

}


















void Tile::loadTilePiece(int type) {

	if (type >= -1 && type <= 1)
		pawn = new Pawn("../Resources/Image/checkers.png", tile, type < 0 ? 1 : 5); //, , num > 4 - white, <3 - black

	else {

		std::cout << "\nType: " << type;

		pawn = new King("../Resources/Image/checkers.png", tile, type < 0 ? 1 : 5);
	}
}

