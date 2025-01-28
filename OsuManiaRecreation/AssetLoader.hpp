#include "Game.h"
#include "Notes.h"

namespace {
	// STL booleans Assets activation related

	// sf::Drawable content
	// Colors
	sf::Color noPressHitCircle = sf::Color(200, 200, 200, 50);
	sf::Color pressHitCircle = sf::Color(230, 230, 230, 100);
	// Fonts
	sf::Font Arial;
	sf::Font AllerBold;
	// Shapes
	sf::RectangleShape playAreaBackground;
	sf::RectangleShape earlyMissZone;
	// Using a DFJK model to name the bottom cirlces
	sf::CircleShape DHitCircle;
	sf::CircleShape FHitCircle;
	sf::CircleShape JHitCircle;
	sf::CircleShape KHitCircle;
	sf::CircleShape singleTestNote;
	sf::CircleShape sliderHead;
	sf::CircleShape sliderTail;
	// Texts
	sf::Text FPSText;
	sf::Text comboText;
	sf::Text scoreText;
}

void loadAssets(sf::RenderWindow& window) {
	// Fonts
	if (!Arial.loadFromFile("Assets/Fonts/Arial.TTF"))
		std::cerr << "Arial font couldn't be loaded" << '\n';
	if (!AllerBold.loadFromFile("Assets/Fonts/Aller_Bd.ttf"))
		std::cerr << "AllerBold font couldn't be loaded" << '\n';
	// RectangleShape
	playAreaBackground.setSize(sf::Vector2f((float)window.getSize().y * (9.f / 16.f), (float)window.getSize().y));
	playAreaBackground.setFillColor(sf::Color(154, 154, 154, 30));
	playAreaBackground.setOutlineColor(sf::Color(154, 154, 154));
	playAreaBackground.setOutlineThickness(2.f);
	playAreaBackground.setPosition(window.getSize().x / 2.f - playAreaBackground.getLocalBounds().width / 2.f, 0.f);
	float playAreaBackgroundWidthPercent = playAreaBackground.getSize().x / 100.f;
	float playAreaBackgroundHeightPercent = playAreaBackground.getSize().y / 100.f;
	earlyMissZone.setSize(sf::Vector2f(playAreaBackground.getSize().x, playAreaBackgroundHeightPercent * 10.f));
	earlyMissZone.setFillColor(sf::Color(255, 0, 0, 125));
	earlyMissZone.setPosition(sf::Vector2f(playAreaBackground.getPosition().x, playAreaBackgroundHeightPercent * 70.f));
	// CircleShape
	DHitCircle.setRadius(playAreaBackground.getSize().x / 10.f);
	DHitCircle.setFillColor(sf::Color(200, 200, 200, 50));
	DHitCircle.setOutlineThickness(DHitCircle.getRadius() / 8.5f);
	DHitCircle.setOutlineColor(sf::Color(200, 200, 200, 200));
	DHitCircle.setPosition(sf::Vector2f(playAreaBackground.getPosition().x + DHitCircle.getOutlineThickness() + 2.1f * playAreaBackgroundWidthPercent, 77.78f * playAreaBackgroundHeightPercent));
	FHitCircle = DHitCircle;
	JHitCircle = DHitCircle;
	KHitCircle = DHitCircle;
	FHitCircle.setPosition(DHitCircle.getPosition().x + DHitCircle.getLocalBounds().width + 2.1f * playAreaBackgroundWidthPercent, DHitCircle.getPosition().y);
	JHitCircle.setPosition(FHitCircle.getPosition().x + DHitCircle.getLocalBounds().width + 2.1f * playAreaBackgroundWidthPercent, DHitCircle.getPosition().y);
	KHitCircle.setPosition(JHitCircle.getPosition().x + DHitCircle.getLocalBounds().width + 2.1f * playAreaBackgroundWidthPercent, DHitCircle.getPosition().y);
	singleTestNote = DHitCircle;
	singleTestNote.setFillColor(sf::Color::White);
	singleTestNote.setOutlineThickness(0);
	singleTestNote.setPosition(sf::Vector2f(DHitCircle.getPosition().x, -DHitCircle.getLocalBounds().height));
	// Texts
	FPSText.setFont(Arial);
	FPSText.setCharacterSize(20);
	FPSText.setFillColor(sf::Color::White);
	FPSText.setString("FPS : 60.00");
	FPSText.setPosition(sf::Vector2f(window.getSize().x / 2.f - FPSText.getLocalBounds().width / 2.f, 10.f));
	comboText.setFont(AllerBold);
	comboText.setFillColor(sf::Color(76, 76, 76));
	comboText.setCharacterSize(50);
	comboText.setString("");
	comboText.setPosition(sf::Vector2f((float)window.getSize().x / 2, (float)window.getSize().y / 2));
	scoreText = comboText;
	scoreText.setCharacterSize(50);
	scoreText.setString("00000000");
	scoreText.setPosition(sf::Vector2f(window.getSize().x * 0.99f - scoreText.getLocalBounds().width, window.getSize().y * 0.01f));
}

void draw(sf::RenderWindow& window) {
	window.clear();

	window.draw(earlyMissZone);
	window.draw(playAreaBackground);
	window.draw(FPSText);

	window.draw(DHitCircle);
	window.draw(FHitCircle);
	window.draw(JHitCircle);
	window.draw(KHitCircle);

	// Notes

	window.draw(singleTestNote);
}