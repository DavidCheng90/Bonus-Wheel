#ifndef __WHEEL_H__
#define __WHEEL_H__

#include "Prize.h"

USING_NS_CC;

USING_NS_CC_EXT;

class Wheel
{
public:
	Wheel();
	~Wheel();
	
	void create(cocos2d::Size screenSize);
	void addPrizes();
	void setPrizeProperties();

	cocos2d::Sprite* getWheel();
	cocos2d::Sprite* getBorder();
	cocos2d::Sprite* getArrow();

	void spinWheel();

private:
	cocos2d::Sprite* wheel = 0;
	cocos2d::Sprite* border = 0;
	cocos2d::Sprite* arrow = 0;

	std::vector<Prize> prizes = { };
	std::vector<Prize> prizePool = { };

	double sectorSize = 0;
};

#endif // __WHEEL_H__