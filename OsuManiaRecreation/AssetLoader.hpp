#include "Game.h"

namespace {
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
	sf::RectangleShape lateMissZone;
	sf::RectangleShape early50Zone;
	sf::RectangleShape late50Zone;
	sf::RectangleShape early100Zone;
	sf::RectangleShape late100Zone;
	sf::RectangleShape ThreeHundredZone;
		// Using a DFJK model to name the bottom cirlces
	sf::CircleShape DHitCircle;
	sf::CircleShape FHitCircle;
	sf::CircleShape JHitCircle;
	sf::CircleShape KHitCircle;
	sf::CircleShape sliderHead;
	sf::CircleShape sliderTail;
	// Texts
	sf::Text FPSText;
	sf::Text comboText;
	sf::Text scoreText;
}

std::vector<sf::CircleShape> getHitCircles() {
	std::vector<sf::CircleShape> hitCircles;
	hitCircles.reserve(4);
	hitCircles.emplace_back(DHitCircle);
	hitCircles.emplace_back(FHitCircle);
	hitCircles.emplace_back(JHitCircle);
	hitCircles.emplace_back(KHitCircle);
	return hitCircles;
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
	earlyMissZone.setSize(sf::Vector2f(playAreaBackground.getSize().x, playAreaBackgroundWidthPercent * 10.f));
	earlyMissZone.setFillColor(sf::Color(255, 0, 0, 125));												   // This part = -outlineThickness + 10
	earlyMissZone.setPosition(playAreaBackground.getPosition().x, playAreaBackgroundHeightPercent * 57.77f + 8.82f * playAreaBackgroundWidthPercent);
	lateMissZone = earlyMissZone;
	lateMissZone.setPosition(earlyMissZone.getPosition().x, 77.78f * playAreaBackgroundHeightPercent + 21.18f * playAreaBackgroundWidthPercent);
	early50Zone = earlyMissZone;
	early50Zone.setSize(sf::Vector2f(earlyMissZone.getSize().x, earlyMissZone.getSize().y * 0.75f));
	early50Zone.setFillColor(sf::Color(255, 153, 51, 125));
	early50Zone.setPosition(earlyMissZone.getPosition().x, earlyMissZone.getPosition().y + earlyMissZone.getSize().y);
	early100Zone = early50Zone;
	early100Zone.setSize(sf::Vector2f(early50Zone.getSize().x, early50Zone.getSize().y * 2.f));
	early100Zone.setFillColor(sf::Color(0, 255, 0));
	early100Zone.setPosition(early50Zone.getPosition().x, early50Zone.getPosition().y + early50Zone.getSize().y);
	ThreeHundredZone = early100Zone;
	ThreeHundredZone.setSize(sf::Vector2f());
	ThreeHundredZone.setFillColor(sf::Color(0, 255, 255));
	ThreeHundredZone.setPosition(early100Zone.getPosition().x, early100Zone.getPosition().y + early100Zone.getSize().y);
	// CircleShape
	DHitCircle.setRadius(playAreaBackground.getSize().x / 10.f);
	DHitCircle.setFillColor(sf::Color(200, 200, 200, 50));
	DHitCircle.setOutlineThickness(DHitCircle.getRadius() / 8.5f);
	DHitCircle.setOutlineColor(sf::Color(200, 200, 200, 200));
	DHitCircle.setPointCount(100);
	DHitCircle.setPosition(sf::Vector2f(playAreaBackground.getPosition().x + DHitCircle.getOutlineThickness() + 2.1f * playAreaBackgroundWidthPercent, 77.78f * playAreaBackgroundHeightPercent));
	FHitCircle = DHitCircle;
	JHitCircle = DHitCircle;
	KHitCircle = DHitCircle;
	FHitCircle.setPosition(DHitCircle.getPosition().x + DHitCircle.getLocalBounds().width + 2.1f * playAreaBackgroundWidthPercent, DHitCircle.getPosition().y);
	JHitCircle.setPosition(FHitCircle.getPosition().x + DHitCircle.getLocalBounds().width + 2.1f * playAreaBackgroundWidthPercent, DHitCircle.getPosition().y);
	KHitCircle.setPosition(JHitCircle.getPosition().x + DHitCircle.getLocalBounds().width + 2.1f * playAreaBackgroundWidthPercent, DHitCircle.getPosition().y);
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

	// Debug part
	/*window.draw(earlyMissZone);
	window.draw(early50Zone);
	window.draw(early100Zone);
	window.draw(ThreeHundredZone);*/
	//window.draw(late100zone);
	//window.draw(late50zone);
	window.draw(lateMissZone);

	// Gameplay area
	window.draw(playAreaBackground);
	window.draw(FPSText);

	window.draw(DHitCircle);
	window.draw(FHitCircle);
	window.draw(JHitCircle);
	window.draw(KHitCircle);
}