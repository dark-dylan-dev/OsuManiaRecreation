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
#include <algorithm>

// SFML
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class Game {
public:
	Game();
	void run();

private:
	// STL
	bool isRunning = true;
	float deltaTime = 0.f;
	float accuracy = 100.f;
	bool isLevelStarted = false;
	bool isDPressed = false;
	bool isFPressed = false;
	bool isJPressed = false;
	bool isKPressed = false;
	int combo = 0;
	int score = 0;
	int scoreTenth = 0;
	int count300 = 0;
	int count100 = 0;
	int count50 = 0;
	int missCount = 0;
	// SFML
	sf::RenderWindow window;
	sf::Clock Clock;

private:
	void FPSCalc(const float& deltaTime);
	void pollEvents(sf::Event event);
	void update(const float& deltaTime);
	void handleInputs(sf::Event event);
	void drawNotes();

public:
	// Only for Notes.h
	std::vector<sf::CircleShape> getCirclesSlots();
};

#endif