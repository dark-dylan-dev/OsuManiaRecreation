#include "Notes.h"

char LevelNotes::getAssociatedKey(std::vector<sf::CircleShape>& hitCircles) {
	if (getPosition().x == hitCircles[0].getPosition().x) {
		return 'D';
	}
	if (getPosition().x == hitCircles[1].getPosition().x) {
		return 'F';
	}
	if (getPosition().x == hitCircles[2].getPosition().x) {
		return 'J';
	}
	if (getPosition().x == hitCircles[3].getPosition().x) {
		return 'K';
	}
	return ' '; // Utilisé pour les exceptions
}

singleNote::singleNote(sf::CircleShape& noteSlot, const int& cycleLevel, const char associatedKey) {
	setRadius(noteSlot.getRadius());
	setPosition(sf::Vector2f(noteSlot.getPosition().x, -getLocalBounds().height * cycleLevel));
	setFillColor(sf::Color::White);
	this->noteSlot = getPosition().x;
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
}

float sliderNote::getYPosition() {
	return getPosition().y;
}

bool sliderNote::isKeyHeld() const {
	return true; // A changer quand je ferais les sliders
}