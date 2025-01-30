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
	sf::Text accuracyText;
	// "SFML/Audio.hpp" content
	sf::Sound softHitsound;
	sf::SoundBuffer softHitsoundBuffer;
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
	// Songs & sounds
	if (!softHitsoundBuffer.loadFromFile("Assets/Sounds/soft-hitnormal.wav"))
		std::cerr << "Hitsound .wav file couldn't be loaded" << '\n';
	else
		softHitsound.setBuffer(softHitsoundBuffer);
	// RectangleShape
	playAreaBackground.setSize(sf::Vector2f((float)window.getSize().y * (9.f / 16.f), (float)window.getSize().y));
	playAreaBackground.setFillColor(sf::Color(154, 154, 154, 30));
	playAreaBackground.setOutlineColor(sf::Color(154, 154, 154));
	playAreaBackground.setOutlineThickness(2.f);
	playAreaBackground.setPosition(window.getSize().x / 2.f - playAreaBackground.getLocalBounds().width / 2.f, 0.f);
	float playAreaBackgroundWidthPercent = playAreaBackground.getSize().x / 100.f;
	float playAreaBackgroundHeightPercent = playAreaBackground.getSize().y / 100.f;
	// PrecisionHitsZone
	ThreeHundredZone.setSize(sf::Vector2f(playAreaBackground.getSize().x, playAreaBackgroundWidthPercent * 5.f));
	ThreeHundredZone.setFillColor(sf::Color(0, 255, 255, 125));
	ThreeHundredZone.setPosition(sf::Vector2f(playAreaBackground.getPosition().x, 77.78f * playAreaBackgroundHeightPercent + 7.5f * playAreaBackgroundWidthPercent));
	early100Zone.setSize(sf::Vector2f(playAreaBackground.getSize().x, playAreaBackgroundWidthPercent * 7.5f));
	early100Zone.setFillColor(sf::Color(0, 255, 0, 125));
	early100Zone.setPosition(ThreeHundredZone.getPosition().x, ThreeHundredZone.getPosition().y - early100Zone.getSize().y);
	late100Zone.setSize(early100Zone.getSize());
	late100Zone.setFillColor(early100Zone.getFillColor());
	late100Zone.setPosition(ThreeHundredZone.getPosition().x, ThreeHundredZone.getPosition().y + ThreeHundredZone.getSize().y);
	early50Zone.setSize(sf::Vector2f(playAreaBackground.getSize().x, playAreaBackgroundWidthPercent * 10.f));
	early50Zone.setFillColor(sf::Color(240, 159, 19, 125));
	early50Zone.setPosition(early100Zone.getPosition().x, early100Zone.getPosition().y - early50Zone.getSize().y);
	late50Zone.setSize(early50Zone.getSize());
	late50Zone.setFillColor(early50Zone.getFillColor());
	late50Zone.setPosition(late100Zone.getPosition().x, late100Zone.getPosition().y + late100Zone.getSize().y);
	earlyMissZone.setSize(early50Zone.getSize());
	earlyMissZone.setFillColor(sf::Color(204, 0, 0, 125));
	earlyMissZone.setPosition(early50Zone.getPosition().x, early50Zone.getPosition().y - earlyMissZone.getSize().y);
	lateMissZone.setSize(earlyMissZone.getSize());
	lateMissZone.setFillColor(earlyMissZone.getFillColor());
	lateMissZone.setPosition(late50Zone.getPosition().x, late50Zone.getPosition().y + late50Zone.getSize().y);
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
	scoreText.setFillColor(sf::Color(128, 128, 128));
	scoreText.setCharacterSize(50);
	scoreText.setString("00000000");
	scoreText.setPosition(sf::Vector2f(window.getSize().x * 0.99f - scoreText.getLocalBounds().width, window.getSize().y * 0.01f));
	accuracyText.setFont(AllerBold);
	accuracyText.setCharacterSize(30);
	accuracyText.setString("100.00%");
	accuracyText.setPosition(sf::Vector2f((window.getSize().x * 0.99f) - accuracyText.getLocalBounds().width, window.getSize().y * 0.03f + scoreText.getLocalBounds().height));
	accuracyText.setFillColor(sf::Color(128, 128, 128));
}

void draw(sf::RenderWindow& window) {
	window.clear();

	// Debug part
	/*window.draw(earlyMissZone);
	window.draw(early50Zone);
	window.draw(early100Zone);
	window.draw(ThreeHundredZone);
	window.draw(late100Zone);
	window.draw(late50Zone);
	window.draw(lateMissZone);*/

	// Gameplay area
	window.draw(playAreaBackground);
	window.draw(FPSText);

	window.draw(accuracyText);

	window.draw(DHitCircle);
	window.draw(FHitCircle);
	window.draw(JHitCircle);
	window.draw(KHitCircle);
}