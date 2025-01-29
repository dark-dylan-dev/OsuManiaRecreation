#ifndef GAME_H
#define GAME_H

// STL
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <memory>

// SFML
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class Game {
public:
	Game();
	void run();

private:
	// STL
	bool isRunning;
	float deltaTime;
	bool isLevelStarted = false;
	bool isDPressed = false;
	bool isFPressed = false;
	bool isJPressed = false;
	bool isKPressed = false;
	unsigned int combo;
	unsigned int score;
	// SFML
	sf::RenderWindow window;
	sf::Clock Clock;

private:
	void FPSCalc(const float& deltaTime);
	void pollEvents(sf::Event event);
	void update(const float& deltaTime);
	void handleInputs(sf::Event event);
	void drawNotes();

};

#endif