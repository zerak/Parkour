#ifndef __STATUS_LAYER_H__
#define __STATUS_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class StatusLayer : public cocos2d::CCLayer
{
	CCLayer *layer;
	CCLabelTTF *labelCoin;
	CCLabelTTF *labelMeter;
	int coins;
public:
	StatusLayer();
	StatusLayer(CCLayer *layer);
	~StatusLayer();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	//virtual bool init();  

	virtual bool init();  

	void addCoin(int num);
	void updateMeter(float px);
};

#endif // __STATUS_LAYER_H__
