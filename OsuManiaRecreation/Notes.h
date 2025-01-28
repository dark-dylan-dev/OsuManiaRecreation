#ifndef NOTES_H
#define NOTES_H

#include "Game.h"

class LevelNotes : public sf::CircleShape {
public:
	bool isInTheSlot(const sf::CircleShape& noteSlot); // onPress
	virtual float getYPosition() = 0; // Needs to be defined for singleNote and sliderNote
};

class singleNote : public LevelNotes {
private:
	float noteSlot;
public:
	singleNote(sf::CircleShape& noteSlot, const int& cycleLevel);
	float getYPosition() override;
};

class sliderNote : public LevelNotes {
private:
	float noteSlot;
	float noteLength;
	sf::Keyboard::Key associatedKey;
public:
	sliderNote(sf::CircleShape& noteSlot, float noteLength, const int& cycleLevel);
	float getYPosition() override;
	bool isKeyHeld() const;
};

class Factory {
public:
	static std::unique_ptr<LevelNotes> createNote(const std::string& type, sf::CircleShape& noteSlot, const int& cycleLevel) {
		if (type == "singleNote") return std::make_unique<singleNote>(noteSlot, cycleLevel);
		else if (type == "sliderNote") return std::make_unique<sliderNote>(noteSlot, 0.f, cycleLevel);
		return nullptr;
	}
};

#endif