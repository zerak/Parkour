#ifndef __MAINSCENE_SCENE_H__
#define __MAINSCENE_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::CCLayer
{
public:
	~MainScene();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(MainScene);
	
	//void update (float dt);

	// a selector callback
	void onPlay(cocos2d::Ref* pSender);
};

#endif // __MAINSCENE_SCENE_H__
