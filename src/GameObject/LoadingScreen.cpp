#include "LoadingScreen.h"

#include "SmokeParticle.h"
#include "../Config/Settings.h"
#include "../Controller/Singleton/TextureManager.h"
#include "../Controller/Application.h"
#include "../Utility/FileUtils.h"
#include "../Utility/RandomUtils.h"
#include "../Utility/StringUtils.h"

gd::LoadingScreen::LoadingScreen() :
	GameObject("LoadingScreen"), level(*TextureManager::getInstance()->getFromTextureMap("Level Display", 0))
{
	music = sf::Music(FileUtils::getFileFromAssetsFolder("Harvest Dawn.mp3"));

	highlights.reserve(10);
	backgrounds.reserve(10);

	for (int i = 0; i < TextureManager::getInstance()->getNumLoadedHighlightTextures(); ++i)
	{
		sf::Sprite highlightSprite = sf::Sprite(*TextureManager::getInstance()->getHighlightTextureFromList(i));
		highlights.push_back(highlightSprite);
	}

	for (int i = 0; i < TextureManager::getInstance()->getNumLoadedBackgroundTextures(); ++i)
	{
		sf::Sprite backgroundSprite = sf::Sprite(*TextureManager::getInstance()->getBackgroundTextureFromList(i));
		backgroundSprite.setScale({ 0.5f, 0.5f });
		backgroundSprite.setPosition({
			WindowWidth / 2.f - backgroundSprite.getGlobalBounds().size.x / 2.f,
			WindowHeight / 2.f - backgroundSprite.getGlobalBounds().size.y / 2.f });
		backgrounds.push_back(backgroundSprite);
	}

	for (int i = 0; i < 10; ++i)
	{
		SmokeParticle* newSmoke = new SmokeParticle(sf::Vector2f(RandomUtils::random(-1.f, 1.f), -1.f).normalized());
		GameObjectManager::getInstance()->addObject(newSmoke);
		smoke.push_back(newSmoke);
	}

	level.setPosition({ (WindowWidth - level.getGlobalBounds().size.x) - 50, 0 });

	splitTipsText();
	randomizeTips();
	randomizeSprites();

	setAssetsTransparent();

	music.setLooping(true);
	music.play();
	transitionClock.start();
	smokeClock.start();
}

void gd::LoadingScreen::randomizeTips()
{
	tipLines.clear();

	int newIdx = RandomUtils::random(0, static_cast<int>(sizeof(tipsText) / sizeof(std::string) - 1));
	while (tipsIdx == newIdx)
		newIdx = RandomUtils::random(0, static_cast<int>(sizeof(tipsText) / sizeof(std::string) - 1));

	tipsIdx = newIdx;

	auto str = tipsText[tipsIdx];

	std::vector<std::string> strLines = StringUtils::split(str, '\n');

	for (int i = 0; i < strLines.size(); ++i)
	{
		sf::Text line(font);

		line.setOutlineThickness(2.f);
		line.setOutlineColor(sf::Color::Black);
		line.setString(strLines[i]);
		line.setPosition({ WindowWidth - line.getLocalBounds().size.x - 100, (WindowHeight - line.getGlobalBounds().size.y - 250) + i * 40 });

		tipLines.push_back(line);
	}
}

void gd::LoadingScreen::splitTipsText()
{
	for (std::string& text : tipsText)
	{
		constexpr size_t lineLen = 75;

		text.insert(0, " ");
		for (auto i = lineLen; i < text.length(); i += lineLen)
		{
			if (const auto cutoffIdx = text.find_first_of(' ', i); cutoffIdx > 0)
				text.insert(cutoffIdx, "\n");
		}
	}
}

void gd::LoadingScreen::spawnSmoke()
{
	if (smokeClock.getElapsedTime().asSeconds() < smokeInterval)
		return;

	//LogUtils::log("Getting smoke from pool");

	for (SmokeParticle* smokeParticle : smoke)
	{
		if (!smokeParticle->isAlive)
		{
			smokeParticle->start();
			break;
		}
	}

	smokeInterval = RandomUtils::random(1.f, 2.f);
	smokeClock.restart();
}

void gd::LoadingScreen::fadeAssetsOut(sf::Time deltaTime)
{
	// current stuff
	auto& bg = backgrounds[backgroundIdx];
	auto& hl = highlights[highlightIdx];
	auto& txt = tipLines;

	// they'll all have the same alpha anyway i think
	const auto bgAlpha = bg.getColor().a;
	const auto hlAlpha = hl.getColor().a;

	//LogUtils::log(this, "Fading out, bgAlpha = " + std::to_string(bgAlpha));

	bg.setColor(sf::Color(255, 255, 255, MathUtils::interpolateTowards(bgAlpha, 0, fadeRate * deltaTime.asSeconds())));
	hl.setColor(sf::Color(255, 255, 255, MathUtils::interpolateTowards(hlAlpha, 0, fadeRate * deltaTime.asSeconds())));

	for (sf::Text& text : txt)
	{
		const auto outlineAlpha = text.getOutlineColor().a;
		const auto fillAlpha = text.getFillColor().a;

		text.setOutlineColor(sf::Color(0, 0, 0, MathUtils::interpolateTowards(outlineAlpha, 0, fadeRate * deltaTime.asSeconds())));
		text.setFillColor(sf::Color(255, 255, 255, MathUtils::interpolateTowards(fillAlpha, 0, fadeRate * deltaTime.asSeconds())));
	}

	if (isFinishedLoading)
	{
		level.setColor(sf::Color(255, 255, 255, MathUtils::interpolateTowards(level.getColor().a, 0, fadeRate * deltaTime.asSeconds())));
		music.setVolume(MathUtils::interpolateTowards(music.getVolume(), 0, fadeRate * deltaTime.asSeconds()));
	}

	if (bgAlpha <= 0)
	{
		isFadingOut = false;
		if (isFinishedLoading)
		{
			//LogUtils::log(this, "Finished loading.");
			return;
		}

		isFadingIn = true;
		randomizeSprites();
		randomizeTips();
		setAssetsTransparent(); // coz tipsLines gets reset
		//LogUtils::log(this, "Done fading out. isFadingOut = " + std::to_string(isFadingOut));
		//LogUtils::log(this, "isFadingIn = " + std::to_string(isFadingIn));
	}
}

void gd::LoadingScreen::fadeAssetsIn(sf::Time deltaTime)
{
	// current stuff
	auto& bg = backgrounds[backgroundIdx];
	auto& hl = highlights[highlightIdx];
	auto& txt = tipLines;

	// they'll all have the same alpha anyway i think
	const auto bgAlpha = bg.getColor().a;
	const auto hlAlpha = hl.getColor().a;

	//LogUtils::log(this, "Fading in, bgAlpha = " + std::to_string(bgAlpha));

	bg.setColor(sf::Color(255, 255, 255, MathUtils::interpolateTowards(bgAlpha, 255, fadeRate * deltaTime.asSeconds())));
	hl.setColor(sf::Color(255, 255, 255, MathUtils::interpolateTowards(hlAlpha, 255, fadeRate * deltaTime.asSeconds())));

	for (sf::Text& text : txt)
	{
		const auto outlineAlpha = text.getOutlineColor().a;
		const auto fillAlpha = text.getFillColor().a;

		text.setOutlineColor(sf::Color(0, 0, 0, MathUtils::interpolateTowards(outlineAlpha, 255, fadeRate * deltaTime.asSeconds())));
		text.setFillColor(sf::Color(255, 255, 255, MathUtils::interpolateTowards(fillAlpha, 255, fadeRate * deltaTime.asSeconds())));
	}

	if (bgAlpha >= 255)
	{
		isFadingOut = false;
		isFadingIn = false;
		//LogUtils::log(this, "Done fading in, resetting timer.");
		transitionClock.restart();
	}
}

void gd::LoadingScreen::setAssetsTransparent()
{
	for (auto& bg : backgrounds)
	{
		bg.setColor(sf::Color::Transparent);
	}

	for (auto& hl : highlights)
	{
		hl.setColor(sf::Color::Transparent);
	}

	for (auto& line : tipLines)
	{
		line.setOutlineColor(sf::Color::Transparent);
		line.setFillColor(sf::Color::Transparent);
	}
}

void gd::LoadingScreen::randomizeSprites()
{
	int newBgIdx = RandomUtils::random(0, static_cast<int>(backgrounds.size() - 1));
	while (backgroundIdx == newBgIdx)
		newBgIdx = RandomUtils::random(0, static_cast<int>(backgrounds.size() - 1));

	backgroundIdx = newBgIdx;

	int newHlIdx = RandomUtils::random(0, static_cast<int>(highlights.size() - 1));
	while (highlightIdx == newHlIdx)
		newHlIdx = RandomUtils::random(0, static_cast<int>(highlights.size() - 1));

	highlightIdx = newHlIdx;
}

void gd::LoadingScreen::interpSprites(const sf::Time deltaTime)
{
	const sf::Vector2i mousePos = sf::Mouse::getPosition(Application::getInstance()->getWindow());
	//LogUtils::log("Mouse position: " + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y));

	const float xOffset = (mousePos.x - WindowWidth / 2.f);
	const float yOffset = (mousePos.y - WindowHeight / 2.f);
	constexpr float bgDepthScale = 0.02f;
	constexpr float hlDepthScale = 0.05f;
	constexpr float lerpSpeed = 100.f;

	auto& hl = highlights[highlightIdx];
	// bg original position
	auto& bg = backgrounds[backgroundIdx];
	const float xBg = WindowWidth / 2.f - bg.getGlobalBounds().size.x / 2.f;
	const float yBg = WindowHeight / 2.f - bg.getGlobalBounds().size.y / 2.f;

	const sf::Vector2f offsetVec = { xOffset, yOffset };
	const sf::Vector2f bgOriginalPos = { xBg, yBg };

	bg.setPosition(MathUtils::interpolateTowards(bg.getPosition(), bgOriginalPos + offsetVec * bgDepthScale, lerpSpeed * deltaTime.asSeconds()));
	hl.setPosition(MathUtils::interpolateTowards(hl.getPosition(), offsetVec * hlDepthScale, lerpSpeed * deltaTime.asSeconds()));
}

void gd::LoadingScreen::update(const sf::Time deltaTime)
{
	spawnSmoke();

	if (isFinishedLoading)
	{
		fadeAssetsOut(deltaTime);
		return;
	}

	if (transitionClock.getElapsedTime().asSeconds() >= transitionInterval)
	{
		isFadingOut = true;
		transitionClock.reset();
	}

	if (isFadingOut)
	{
		//LogUtils::log(this, "isFadingOut = " + std::to_string(isFadingOut));
		fadeAssetsOut(deltaTime);
	}

	if (isFadingIn)
	{
		//LogUtils::log(this, "isFadingIn = " + std::to_string(isFadingIn));
		fadeAssetsIn(deltaTime);
	}

	interpSprites(deltaTime);
}

void gd::LoadingScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// if (isFinishedLoading)
	// 	return;

	target.draw(backgrounds[backgroundIdx]);
	target.draw(highlights[highlightIdx]);
	target.draw(level);

	for (const sf::Text& line : tipLines)
	{
		target.draw(line);
	}
}

void gd::LoadingScreen::finishLoading()
{
	isFinishedLoading = true;
}
