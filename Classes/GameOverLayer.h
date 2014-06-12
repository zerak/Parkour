#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "cocos2d.h"
USING_NS_CC;

class GameOverLayer : public cocos2d::CCLayer
{
public:
	GameOverLayer();
	~GameOverLayer();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	void onRestart(CCObject* pSender);
};

#endif // __GAMEOVER_H__
