#include "AssetLoader.hpp"
#include "LevelFileLoader.hpp"

#include "Game.h"

namespace {
	std::vector<std::unique_ptr<LevelNotes>> levelNotesVector;
	std::vector<sf::CircleShape> hitCircles;
}

void hitVerification(sf::RenderWindow& window, const char& associatedKey, std::unique_ptr<LevelNotes>& note, int& combo, int& score, float& accuracy, int& count300, int& count100, int& count50, int& missCount);
void accuracyCalc(sf::RenderWindow& window, int& count300, int& count100, int& count50, int& missCount, float& accuracy);

Game::Game() :
	window(sf::VideoMode::getFullscreenModes().at(2), "osu! mania recreation", sf::Style::Default)
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

void accuracyCalc(sf::RenderWindow& window, int& count300, int& count100, int& count50, int& missCount, float& accuracy) {
	std::cout << "[LOG] - Stats : " << '\n' << "   - 300 : " << count300 << '\n' << "   - 100 : " << count100 << '\n' << "   - 50 : " << count50 << '\n' << "   - Miss : " << missCount << '\n';
	if (count300 == 0 && count100 == 0 && count50 == 0 && missCount == 0)
		accuracy = 100.f;
	else {
		accuracy = (
			(float)(300.f * count300 + 100.f * count100 + 50.f * count50)
			/ 
			(float)(300.f * (count300 + count100 + count50 + missCount))
		);
		accuracy *= 100;
		std::cout << " - Acc : " << accuracy << "%" << '\n';
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(2) << accuracy;
		std::string AccValue = oss.str();
		accuracyText.setString(AccValue + "%");
		accuracyText.setPosition(sf::Vector2f((window.getSize().x * 0.99f) - accuracyText.getLocalBounds().width, window.getSize().y * 0.03f + scoreText.getLocalBounds().height));
	}
}

void Game::handleInputs(sf::Event event) {
	// Pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (!isDPressed) {
			for (auto& note : levelNotesVector) {
				if (note == nullptr) {
					// Skip it
				}
				else if (note->getAssociatedKey(hitCircles) == 'D') {
					hitVerification(window, note->getAssociatedKey(hitCircles), note, combo, score, accuracy, count300, count100, count50, missCount);
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
					hitVerification(window, note->getAssociatedKey(hitCircles), note, combo, score, accuracy, count300, count100, count50, missCount);
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
					hitVerification(window, note->getAssociatedKey(hitCircles), note, combo, score, accuracy, count300, count100, count50, missCount);
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
					hitVerification(window, note->getAssociatedKey(hitCircles), note, combo, score, accuracy, count300, count100, count50, missCount);
				}
			}
		}
		KHitCircle.setFillColor(pressHitCircle);
		isKPressed = true;
	}
}

void hitVerification(sf::RenderWindow& window, const char& associatedKey, std::unique_ptr<LevelNotes>& note, int& combo, int& score, float& accuracy, int& count300, int& count100, int& count50, int& missCount) {
	// notePosition : center point of the note
	sf::Vector2f notePosition = sf::Vector2f(note->getPosition().x + note->getRadius(), note->getPosition().y + note->getRadius());
	if (associatedKey == 'D' || associatedKey == 'F' || associatedKey == 'J' || associatedKey == 'K') {
		if (ThreeHundredZone.getGlobalBounds().contains(notePosition)) { // 300
			levelNotesVector.erase(std::find(levelNotesVector.begin(), levelNotesVector.end(), note));
			score += (int)(300 + (300 * ((float)combo / 100.f)));
			count300++;
			combo++;
			softHitsound.play();
			return;
		}
		else if(early100Zone.getGlobalBounds().contains(notePosition) || late100Zone.getGlobalBounds().contains(notePosition)) { // 100
			levelNotesVector.erase(std::find(levelNotesVector.begin(), levelNotesVector.end(), note));
			score += (int)(100 + (100 * ((float)combo / 100.f)));
			count100++;
			combo++;
			softHitsound.play();
			return;
		}
		else if (early50Zone.getGlobalBounds().contains(notePosition) || late50Zone.getGlobalBounds().contains(notePosition)) { // 50
			levelNotesVector.erase(std::find(levelNotesVector.begin(), levelNotesVector.end(), note));
			score += (int)(50 + (50 * ((float)combo / 100.f)));
			combo++;
			count50++;
			softHitsound.play();
			return;
		}
		else if (earlyMissZone.getGlobalBounds().contains(notePosition) || lateMissZone.getGlobalBounds().contains(notePosition)) { // Early / late miss
			combo = 0;
			missCount++;
			levelNotesVector.erase(std::find(levelNotesVector.begin(), levelNotesVector.end(), note));
			return;
		}
		else if (notePosition.y > lateMissZone.getPosition().y + lateMissZone.getSize().y) {
			// Should normally never happen, just a safety measure.
			combo = 0;
			missCount++;
		}
		accuracyCalc(window, count300, count100, count50, missCount, accuracy);
	}
	else {
		std::cerr << "No char matches the note at the adress " << &note << " ('" << associatedKey << "')" << '\n';
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
	else if (combo == 0) {
		comboText.setString("");
		scoreTenth = 0;
	}
	if (combo > (10 * scoreTenth) && combo != 0) {
		comboText.setPosition(sf::Vector2f((float)window.getSize().x / 2 - comboText.getLocalBounds().width / 2, (float)window.getSize().y / 2));
		scoreTenth++;
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
			combo = 0;
			missCount++;
			accuracyCalc(window, count300, count100, count50, missCount, accuracy);
		}
		else {
			note->move(sf::Vector2f(0, deltaTime * 300)); // 200 à changer en variable (vitesse de défilement des notes)
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