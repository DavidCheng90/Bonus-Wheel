#include "Wheel.h"

Wheel::Wheel()
{
}

Wheel::~Wheel()
{
}

void Wheel::create(cocos2d::Size screenSize)
{
	wheel = Sprite::create("wheel_sections_8.png");
	wheel->setPosition(screenSize.width / 2, screenSize.height / 1.7);
	wheel->setScale(0.28);

	border = Sprite::create("wheel_border.png");
	border->setPosition(wheel->getPosition().x, wheel->getPosition().y);
	border->setScale(0.28);

	arrow = Sprite::create("wheel_arrow.png");
	arrow->setPosition(wheel->getPosition().x, wheel->getPosition().y + 128);
	arrow->setScale(0.28);

	addPrizes();
}

void Wheel::addPrizes()
{
	// ***** ADD PRIZES HERE *****
	prizes.push_back(Prize("heart.png", "30", 20));
	prizes.push_back(Prize("brush.png", "x3", 10));
	prizes.push_back(Prize("gem.png", "x35", 10));
	prizes.push_back(Prize("hammer.png", "x3", 10));
	prizes.push_back(Prize("coin.png", "x750", 5));
	prizes.push_back(Prize("brush.png", "x1", 20));
	prizes.push_back(Prize("gem.png", "x75", 5));
	prizes.push_back(Prize("hammer.png", "x1", 20));
	// ****************************

	setPrizeProperties();

	for (Prize p : prizes)
		wheel->addChild(p.getSprite());
}

void Wheel::setPrizeProperties()
{
	// 1. create equal sectors according to number of prizes
	sectorSize = 360 / prizes.size();

	// 2. set prize positions
	double theta = (sectorSize / 2) / 180 * 3.14 * -1; // convert sectorSize from degrees to radians (theta)

	double startPosX = 0;                                         // x
	double startPosY = (wheel->getContentSize().height / 4) + 80; // y
	double endPosX = 0;                                           // x'
	double endPosY = 0;                                           // y'

	for (int p = 0; p < int(prizes.size()); ++p)
	{
		endPosX = startPosX * cos(theta + (2 * theta * p)) - startPosY * sin(theta + (2 * theta * p)); // x' = x * cos(radians) - y * sin(radians)
		endPosY = startPosY * cos(theta + (2 * theta * p)) + startPosX * sin(theta + (2 * theta * p)); // y' = y * cos(radians) + x * sin(radians)
		endPosX += wheel->getContentSize().width / 2;                                                  // rotating positions is complete so move prizes onto wheel
		endPosY += wheel->getContentSize().height / 2;
		prizes[p].getSprite()->setPosition(endPosX, endPosY);
	}

	// 3. set prize rotation
	for (int p = 0; p < int(prizes.size()); ++p)
	{
		prizes[p].getSprite()->setRotation(sectorSize / 2 + sectorSize * p);
		prizes[p].saveAngle(360 - (sectorSize / 2 + sectorSize * p)); // save the angle (sector) of the wheel which the arrow points to to win this prize
	}

	// 4. set prize scale
	for (Prize p : prizes)
	{
		if (p.getSprite()->getResourceName() == "heart.png")
			p.getSprite()->setScale(1.15);
		if (p.getSprite()->getResourceName() == "brush.png")
			p.getSprite()->setScale(0.85);
		if (p.getSprite()->getResourceName() == "gem.png")
			p.getSprite()->setScale(1.15);
		if (p.getSprite()->getResourceName() == "hammer.png")
			p.getSprite()->setScale(1.05);
		if (p.getSprite()->getResourceName() == "coin.png")
			p.getSprite()->setScale(0.95);
	}

	// 5. set prize pool
	for (Prize p : prizes)
		prizePool.insert(prizePool.end(), p.getWeight(), p); // populate prizePool with prizes according to each prize's weight
}

cocos2d::Sprite* Wheel::getWheel()
{
	return wheel;
}

cocos2d::Sprite* Wheel::getBorder()
{
	return border;
}

cocos2d::Sprite* Wheel::getArrow()
{
	return arrow;
}

void Wheel::spinWheel()
{
	// 1. randomly select prize from prizePool
	int yourPrize = 0;
	yourPrize = cocos2d::RandomHelper::random_int(0, int(prizePool.size()) - 1);

	// 2. play animation 
	auto spin1 = RotateTo::create(0.1, 0);
	auto spin2 = Repeat::create(RotateBy::create(1, 360), 3);
	auto spin3 = RotateBy::create(1.3, 360);
	auto spin4 = RotateBy::create(1.7, 360);
	auto spin5 = RotateBy::create((prizePool[yourPrize].getSector() / (sectorSize / 2)) * (1.1 / prizes.size()), prizePool[yourPrize].getSector());
	auto animation = Sequence::create(spin1, spin2, spin3, spin4, spin5, NULL);

	wheel->runAction(animation);
}
