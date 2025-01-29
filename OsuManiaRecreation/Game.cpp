#include "AssetLoader.hpp"
#include "LevelFileLoader.hpp"

#include "Game.h"

namespace {
	std::vector<std::unique_ptr<LevelNotes>> levelNotesVector;
	std::vector<sf::CircleShape> hitCircles;
}

Game::Game() :
	window(sf::VideoMode::getFullscreenModes().at(2), "osu! mania recreation", sf::Style::Default),
	isRunning(true),
	deltaTime(0.f),
	combo(0),
	score(0)
{
	window.setActive(true);
	window.setFramerateLimit(60);
}

std::vector<sf::CircleShape> Game::getCirclesSlots() {
	return hitCircles;
}

void Game::run() {

	loadAssets(window);
	loadLevel("Assets/Levels/testLevel.txt", levelNotesVector);
	hitCircles = getHitCircles();

	sf::Event event{};

	while (window.isOpen()) {

		deltaTime = Clock.restart().asSeconds();
		FPSCalc(deltaTime);

		handleInputs(event);
		pollEvents(event);
		update(deltaTime);
		draw(window);
		drawNotes();

	}
}

void Game::FPSCalc(const float& deltaTime) {
	float FPS = 1.f / deltaTime;
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(1) << FPS;
	std::string FPSValue = oss.str();
	FPSText.setString("FPS : " + FPSValue);
}

void Game::handleInputs(sf::Event event) {
	// Pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		// Reprendre ici pour les hits (D, F, J et K)
		if (!isDPressed) {
			for (auto& note : levelNotesVector) {
				if (note == nullptr) {
					// Skip it
				}
				else if (note->getAssociatedKey(hitCircles) == 'D') {
					if (DHitCircle.getGlobalBounds().contains(sf::Vector2f(note->getPosition().x + note->getRadius(), note->getPosition().y + note->getRadius())) || DHitCircle.getGlobalBounds().intersects(note->getGlobalBounds())) {
						levelNotesVector.erase(std::find(levelNotesVector.begin(), levelNotesVector.end(), note));
						score += (300 + (300 * ((float)combo / 100.f))); // A changer par rapport à la précision du hit (Miss, 50, 100, 300)
						combo++;
					}
				}
			}
		}
		DHitCircle.setFillColor(pressHitCircle);
		isDPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
		if (!isFPressed) {
			for (auto& note : levelNotesVector) {
				if (note == nullptr) {
					// Skip it
				}
				else if (note->getAssociatedKey(hitCircles) == 'F') {
					if (FHitCircle.getGlobalBounds().contains(sf::Vector2f(note->getPosition().x + note->getRadius(), note->getPosition().y + note->getRadius())) || FHitCircle.getGlobalBounds().intersects(note->getGlobalBounds())) {
						levelNotesVector.erase(std::find(levelNotesVector.begin(), levelNotesVector.end(), note));
						score += (300 + (300 * ((float)combo / 100.f))); // A changer par rapport à la précision du hit (Miss, 50, 100, 300)
						combo++;
					}
				}
			}
		}
		FHitCircle.setFillColor(pressHitCircle);
		isFPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		if (!isJPressed) {
			for (auto& note : levelNotesVector) {
				if (note == nullptr) {
					// Skip it
				}
				else if (note->getAssociatedKey(hitCircles) == 'J') {
					if (JHitCircle.getGlobalBounds().contains(sf::Vector2f(note->getPosition().x + note->getRadius(), note->getPosition().y + note->getRadius())) || JHitCircle.getGlobalBounds().intersects(note->getGlobalBounds())) {
						levelNotesVector.erase(std::find(levelNotesVector.begin(), levelNotesVector.end(), note));
						score += (300 + (300 * ((float)combo / 100.f))); // A changer par rapport à la précision du hit (Miss, 50, 100, 300)
						combo++;
					}
				}
			}
		}
		JHitCircle.setFillColor(pressHitCircle);
		isJPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		if (!isKPressed) {
			for (auto& note : levelNotesVector) {
				if (note == nullptr) {
					// Skip it
				}
				else if (note->getAssociatedKey(hitCircles) == 'K') {
					if (KHitCircle.getGlobalBounds().contains(sf::Vector2f(note->getPosition().x + note->getRadius(), note->getPosition().y + note->getRadius())) || KHitCircle.getGlobalBounds().intersects(note->getGlobalBounds())) {
						levelNotesVector.erase(std::find(levelNotesVector.begin(), levelNotesVector.end(), note));
						score += (300 + (300 * ((float)combo / 100.f))); // A changer par rapport à la précision du hit (Miss, 50, 100, 300)
						combo++;
					}
				}
			}
		}
		KHitCircle.setFillColor(pressHitCircle);
		isKPressed = true;
	}
}

void Game::pollEvents(sf::Event event) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		window.close();
		return;
	}
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyReleased: // Use it later for sliders too
			if (event.key.code == sf::Keyboard::D) {
				DHitCircle.setFillColor(noPressHitCircle);
				isDPressed = false;
			}
			if (event.key.code == sf::Keyboard::F) {
				FHitCircle.setFillColor(noPressHitCircle);
				isFPressed = false;
			}
			if (event.key.code == sf::Keyboard::J) {
				JHitCircle.setFillColor(noPressHitCircle);
				isJPressed = false;
			}
			if (event.key.code == sf::Keyboard::K) {
				KHitCircle.setFillColor(noPressHitCircle);
				isKPressed = false;
			}
			break;
		default:
			break;
		}
	}
}

void Game::update(const float& deltaTime) {
	// comboText
	if (combo > 0)
		comboText.setString(std::to_string(combo));
	if (combo % 10 == 0 && combo != 0) {
		comboText.setPosition(sf::Vector2f((float)window.getSize().x / 2 - comboText.getLocalBounds().width / 2, (float)window.getSize().y / 2));
	}
	// scoreText
	if (score >= 0 && score < 10)
		scoreText.setString("0000000" + std::to_string(score));
	else if (score >= 10 && score < 100)
		scoreText.setString("000000" + std::to_string(score));
	else if (score >= 100 && score < 1000)
		scoreText.setString("00000" + std::to_string(score));
	else if (score >= 1000 && score < 10000)
		scoreText.setString("0000" + std::to_string(score));
	else if (score >= 10000 && score < 100000)
		scoreText.setString("000" + std::to_string(score));
	else if (score >= 100000 && score < 1000000)
		scoreText.setString("00" + std::to_string(score));
	else if (score >= 1000000 && score < 10000000)
		scoreText.setString("0" + std::to_string(score));
	else
		scoreText.setString(std::to_string(score));
	// Single note
	for (auto& note : levelNotesVector) {
		if (note == nullptr) {
			// Juste pour skip la note vide
		}
		else if (note->getYPosition() > window.getSize().y) {
			levelNotesVector.erase(std::find(levelNotesVector.begin(), levelNotesVector.end(), note));
			std::cout << "Deletion here" << '\n';
		}
		else {
			note->move(sf::Vector2f(0, deltaTime * 200)); // 200 à changer en variable (vitesse de défilement des notes)
		}
	}
}

void Game::drawNotes() {
	for (auto& note : levelNotesVector) {
		if (levelNotesVector.empty()) {
			break;
		}
		if(note != nullptr)
			window.draw(*note);
	}

	window.draw(comboText);
	window.draw(scoreText);

	window.display();
}