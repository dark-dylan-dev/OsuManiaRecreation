#include "AssetLoader.hpp"
#include "LevelFileLoader.hpp"

#include "Game.h"

namespace {
	std::vector<std::unique_ptr<LevelNotes>> levelNotesVector;
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

void Game::run() {

	loadAssets(window);
	loadLevel("Assets/Levels/testLevel.txt", levelNotesVector);

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
	oss << std::fixed << std::setprecision(2) << FPS;
	std::string FPSValue = oss.str();
	FPSText.setString("FPS : " + FPSValue);
}

void Game::handleInputs(sf::Event event) {
	// Pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (!isDPressed) {
			combo++;
			score += 300;
		}
		DHitCircle.setFillColor(pressHitCircle);
		isDPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
		if (!isFPressed) {
			combo++;
			score += 300;
		}
		FHitCircle.setFillColor(pressHitCircle);
		isFPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		if (!isJPressed) {
			combo++;
			score += 300;
		}
		JHitCircle.setFillColor(pressHitCircle);
		isJPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		if (!isKPressed) {
			combo++;
			score += 300;
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
		case sf::Event::KeyReleased:
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
		note->move(sf::Vector2f(0, deltaTime * 200));
	}

}

void Game::drawNotes() {
	for (auto& note : levelNotesVector) {
		window.draw(*note);
	}

	window.draw(comboText);
	window.draw(scoreText);

	window.display();
}