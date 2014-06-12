#ifndef __RUNNER_SCENE_H__
#define __RUNNER_SCENE_H__

#include "cocos2d.h"
#include "chipmunk.h"
#include "cocos-ext.h"
#include "Utils.h"

USING_NS_CC;
USING_NS_CC_EXT;

// define enum for runner status
//1.定义一个runner状态的枚举，跑步者有许多状态
enum RunnerStat
{
	RunnerStatRunning,
	RunnerStatJumpUp,
	RunnerStatJumpDown,
	RunnerStatCrouch,
	RunnerStatIncredible,
};

//2.PhysicsSprite 没有扩展方法。所以Runner类从cc.Node里扩展
class Runner : public cocos2d::CCNode
{
public:
	Runner();
#if 0
	Runner(CCSpriteBatchNode *spriteSheet, cpSpace *space)
		:sprite(NULL)
		,space(NULL)
		,body(NULL)
		,shape(NULL)
		,stat(RunnerStatRunning)
		,runningAction(NULL)
		,jumpUpAction(NULL)
		,jumpDownAction(NULL)
		,crouchAction(NULL)
		,spriteSheet(NULL)
		,_emitter(NULL)
	{

	}
#else
	Runner(CCSpriteBatchNode *spriteSheet, cpSpace *space);
#endif
	virtual ~Runner(void);
	static Runner * create (CCSpriteBatchNode *spriteSheet, cpSpace *space);

	bool init();  
	virtual void onExit();
	virtual float getPositionX();
	void initAction();
	void initBody();

	void levelUp();

	void initShape(const char* type);

	int getOffsetPx() {
		return 100;
	}

	void runningHulk(float dt);

	void incredibleHulk();

	void incredibleEmitter(float dt);

	static bool meetRock();

	void jump();

	void crouch();

	void loadNormal(float dt);

	void step(float dt);

	static const CCSize *gRunnerCrouchContentSize;
	static const CCSize *getCrouchContentSize()
	{
		if (NULL == gRunnerCrouchContentSize)
		{
			PhysicsSprite *sprite = PhysicsSprite::createWithSpriteFrameName("runnerCrouch0.png");

			gRunnerCrouchContentSize = &sprite->getContentSize();
		}

		return gRunnerCrouchContentSize;
	}

public:
	static PhysicsSprite *sprite;

	CCSize runningSize;
	CCSize crouchSize;

	cpSpace *space;
	cpBody *body;// current chipmunk body

	cpShape  *shape;// current chipmunk shape

	static RunnerStat stat;// init with running status

	CCAction *runningAction;
	CCAction *jumpUpAction;
	CCAction *jumpDownAction;
	CCAction *crouchAction;

	CCSpriteBatchNode *spriteSheet;
	CCParticleSystem *_emitter;
	//CCParticleFlower *_emitter;
	int offsetPx;
};

#endif // __RUNNER_SCENE_H__