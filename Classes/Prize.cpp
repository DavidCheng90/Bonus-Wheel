#include "Prize.h"

Prize::Prize()
{
}

Prize::~Prize()
{
}

Prize::Prize(std::string imagePNG, std::string prizeText, int weight) : weight(weight)
{
	sprite = Sprite::create(imagePNG);

	text = ui::Text::create(prizeText, "Roboto-Black.ttf", 70);
	text->setPosition(Vec2(sprite->getContentSize().width - text->getContentSize().width / 2, text->getContentSize().height / 2));
	text->setTextColor(Color4B::WHITE);
	text->enableOutline(Color4B(141, 94, 47, 255), 4);
	sprite->addChild(text);
}

cocos2d::Sprite* Prize::getSprite()
{
	return sprite;
}

int Prize::getWeight()
{
	return weight;
}

double Prize::getSector()
{
	return sector;
}

void Prize::saveAngle(double angle)
{
	sector = angle;
}
