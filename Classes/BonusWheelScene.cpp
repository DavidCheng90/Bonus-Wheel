#include "BonusWheelScene.h"

USING_NS_CC;

Scene* BonusWheelScene::createScene()
{
	return BonusWheelScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool BonusWheelScene::init()
{
	if (!Scene::init())
		return false;

	// screen size
	auto screenSize = Director::getInstance()->getVisibleSize();

	// background
	//createBackground(screenSize);

	// wheel
	bonusWheel.create(screenSize);
	this->addChild(bonusWheel.getWheel());
	this->addChild(bonusWheel.getBorder());
	this->addChild(bonusWheel.getArrow());

	// button
	createButton(screenSize);

	return true;
}

/*void BonusWheelScene::createBackground(cocos2d::Size screenSize)
{
	// 1. get original background
	bgOriginal = Sprite::create("Circus.PNG");

	auto bgWidth = bgOriginal->getContentSize().width;
	auto bgHeight = bgOriginal->getContentSize().height;

	bgOriginal->setFlippedY(true);
	bgOriginal->setScale(screenSize.width / bgWidth, screenSize.height / bgHeight);
	bgOriginal->setPosition(screenSize.width / 2, screenSize.height / 2);

	// 2. create new texture with original background but use the exact size of the screen
	auto bgChangeSize = RenderTexture::create(screenSize.width, screenSize.height);

	bgChangeSize->begin();
	bgOriginal->visit();
	bgChangeSize->end();

	// 3. set the newly resized background
	bgResized = Sprite::createWithTexture(bgChangeSize->getSprite()->getTexture());

	bgResized->setPosition(Point((screenSize.width / 2), (screenSize.height / 2)));
	this->addChild(bgResized);
}*/

void BonusWheelScene::createButton(cocos2d::Size screenSize)
{
	button = ui::Button::create("spin_button.png");
	button->setPosition(Vec2(screenSize.width / 2, screenSize.height / 6.5));
	button->setScale(0.28);
	this->addChild(button);

	buttonText = ui::Text::create("Spin!", "Roboto-Black.ttf", 70);
	buttonText->setPosition(Vec2(309, 137));
	buttonText->setTextColor(Color4B::WHITE);
	buttonText->enableOutline(Color4B(0, 210, 50, 255), 8);
	button->addChild(buttonText);

	// calls pressButton method when button is pressed
	button->addTouchEventListener(CC_CALLBACK_2(BonusWheelScene::pressButton, this));
}

void BonusWheelScene::pressButton(Ref *sender, ui::Widget::TouchEventType type)
{
	if (!pressedButton) // once user spins the wheel, user cannot spin again
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN: // user's finger is on the spin button, wind back the wheel a little bit
		{
			auto setWheel = RotateBy::create(1, -30);
			bonusWheel.getWheel()->runAction(setWheel);
			break;
		}
		case ui::Widget::TouchEventType::ENDED: // user's finger let go of the spin button, spin the wheel
		{
			if (pressedButton = true)
			{
				auto fade = FadeOut::create(1);
				button->runAction(fade->clone());
				buttonText->runAction(fade->clone());

				bonusWheel.spinWheel();
			}
			break;
		}
		case ui::Widget::TouchEventType::CANCELED:
		{
			auto resetWheel = RotateTo::create(0, 0);
			bonusWheel.getWheel()->runAction(resetWheel);
			break;
		}
		default:
			break;
		}
	}
}
