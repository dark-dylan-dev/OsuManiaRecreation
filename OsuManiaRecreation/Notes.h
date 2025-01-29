#ifndef NOTES_H
#define NOTES_H

#include "Game.h"

class LevelNotes : public sf::CircleShape {
public:
	bool isInTheSlot(const sf::CircleShape& noteSlot); // onPress
	virtual float getYPosition() = 0; // Needs to be defined for singleNote and sliderNote
	char getAssociatedKey(std::vector<sf::CircleShape>& hitCircles);
};

class singleNote : public LevelNotes {
private:
	float noteSlot;
	sf::Keyboard::Key associatedKey;
public:
	singleNote(sf::CircleShape& noteSlot, const int& cycleLevel, const char associatedKey);
	float getYPosition() override;
};

class sliderNote : public LevelNotes {
private:
	float noteSlot;
	float noteLength;
	sf::Keyboard::Key associatedKey;
public:
	sliderNote(sf::CircleShape& noteSlot, float noteLength, const int& cycleLevel, const char associatedKey);
	float getYPosition() override;
	bool isKeyHeld() const;
};

class Factory {
public:
	static std::unique_ptr<LevelNotes> createNote(const std::string& type, sf::CircleShape& noteSlot, const int& cycleLevel, const char& associatedKey) {
		if (type == "singleNote") 
			return std::make_unique<singleNote>(noteSlot, cycleLevel, associatedKey);
		else if (type == "sliderNote") 
			return std::make_unique<sliderNote>(noteSlot, 0.f, cycleLevel, associatedKey); // 0.f à changer plus tard
		return nullptr;
	}
};

#endif