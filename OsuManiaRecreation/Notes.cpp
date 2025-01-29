#include "Notes.h"

bool LevelNotes::isInTheSlot(const sf::CircleShape& noteSlot) {
	if (this->getGlobalBounds().intersects(noteSlot.getGlobalBounds()))
		return true;
	return false;
}

singleNote::singleNote(sf::CircleShape& noteSlot, const int& cycleLevel, const char associatedKey) {
	setRadius(noteSlot.getRadius());
	setPosition(sf::Vector2f(noteSlot.getPosition().x, -getLocalBounds().height * cycleLevel));
	setFillColor(sf::Color::White);
	this->noteSlot = getPosition().x;
	this->associatedKey = sf::Keyboard::Escape;
	switch (associatedKey) {
	case 'D':
		this->associatedKey = sf::Keyboard::D;
		break;
	case 'F':
		this->associatedKey = sf::Keyboard::F;
		break;
	case 'J':
		this->associatedKey = sf::Keyboard::J;
		break;
	case 'K':
		this->associatedKey = sf::Keyboard::K;
		break;
	default:
		std::cerr << "Slider note a l'emplacement " << this << " n'a pas de touche associee, par defaut elle vaudra ESCAPE" << '\n';
		break;
	}
}

float singleNote::getYPosition() {
	return getPosition().y;
}

sliderNote::sliderNote(sf::CircleShape& noteSlot, float noteLength, const int& cycleLevel, const char associatedKey) {
	setRadius(noteSlot.getRadius());
	setPosition(sf::Vector2f(noteSlot.getPosition().x, -getLocalBounds().height * cycleLevel));
	setFillColor(sf::Color::White);
	this->noteSlot = getPosition().x;
	this->noteLength = noteLength;
	this->associatedKey = sf::Keyboard::Escape;
	switch (associatedKey) {
	case 'D':
		this->associatedKey = sf::Keyboard::D;
		break;
	case 'F':
		this->associatedKey = sf::Keyboard::F;
		break;
	case 'J':
		this->associatedKey = sf::Keyboard::J;
		break;
	case 'K':
		this->associatedKey = sf::Keyboard::K;
		break;
	default:
		std::cerr << "Slider note a l'emplacement " << this << " n'a pas de touche associee, par defaut elle vaudra ESCAPE" << '\n';
		break;
	}
}

float sliderNote::getYPosition() {
	return getPosition().y;
}

bool sliderNote::isKeyHeld() const {
	if (sf::Keyboard::isKeyPressed(this->associatedKey))
		return true;
	return false;
}