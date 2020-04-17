#ifndef __PRIZE_H__
#define __PRIZE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

USING_NS_CC_EXT;

class Prize
{
public:
	Prize();
	~Prize();
	Prize(std::string imagePNG, std::string prizeText, int weight);

	cocos2d::Sprite* getSprite();
	int getWeight();
	double getSector();

	void saveAngle(double angle);

private:
	cocos2d::Sprite* sprite = 0;
	ui::Text* text = 0;
	int weight = 0;
	double sector = 0;
};

#endif // __PRIZE_H__