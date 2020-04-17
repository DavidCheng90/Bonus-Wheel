#ifndef __BONUSWHEELSCENE_H__
#define __BONUSWHEELSCENE_H__

#include "Wheel.h"

USING_NS_CC;

USING_NS_CC_EXT;

class BonusWheelScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(BonusWheelScene);

	//void createBackground(cocos2d::Size screenSize);

	void createButton(cocos2d::Size screenSize);
	void pressButton(Ref *sender, ui::Widget::TouchEventType type);

private:
	//cocos2d::Sprite *bgOriginal = 0; // original background
	//cocos2d::Sprite *bgResized = 0;  // resized background

	Wheel bonusWheel;

	ui::Button* button = 0;
	ui::Text* buttonText = 0;
	bool pressedButton = false;
};

#endif // __BONUSWHEELSCENE_H__