#include "Notes.h"

bool LevelNotes::isInTheSlot(const sf::CircleShape& noteSlot) {
	if (this->getGlobalBounds().intersects(noteSlot.getGlobalBounds()))
		return true;
	return false;
}

singleNote::singleNote(sf::CircleShape& noteSlot, const int& cycleLevel) {
	setRadius(noteSlot.getRadius());
	setPosition(sf::Vector2f(noteSlot.getPosition().x, -getLocalBounds().height * cycleLevel));
	setFillColor(sf::Color::White);
	this->noteSlot = getPosition().x;
}

float singleNote::getYPosition() {
	return getPosition().y;
}

sliderNote::sliderNote(sf::CircleShape& noteSlot, float noteLength, const int& cycleLevel) {
	setRadius(noteSlot.getRadius());
	setPosition(sf::Vector2f(noteSlot.getPosition().x, -getLocalBounds().height * cycleLevel));
	setFillColor(sf::Color::White);
	this->noteSlot = getPosition().x;
	this->noteLength = noteLength;
	this->associatedKey = sf::Keyboard::P; // temp
}

float sliderNote::getYPosition() {
	return getPosition().y;
}

bool sliderNote::isKeyHeld() const {
	if (sf::Keyboard::isKeyPressed(this->associatedKey))
		return true;
	return false;
}