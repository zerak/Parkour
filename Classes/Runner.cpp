#include "Runner.h"
#include "resource.h"
#include "PlayScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

const CCSize *Runner::gRunnerCrouchContentSize = NULL;
RunnerStat Runner::stat = RunnerStatRunning;
PhysicsSprite *Runner::sprite = NULL;

Runner::~Runner(void){
	CC_SAFE_RELEASE(runningAction);
	CC_SAFE_RELEASE(jumpUpAction);
	CC_SAFE_RELEASE(jumpDownAction);
	CC_SAFE_RELEASE(crouchAction);
	CC_SAFE_RELEASE(_emitter);
};

Runner::Runner()
{
	
}

/** Constructor
    * @param {cc.SpriteBatchNode *}
    * @param {cp.Space *}
    */
//3.跑步者将被创建并放置在物理世界的PlayLayer里。所以在构造函数里面引用物理空间和精灵表单
Runner::Runner(CCSpriteBatchNode *spriteSheet, cpSpace *space)
{
	//初始化
	this->sprite = (NULL);
	this->body = (NULL);
	this->shape = (NULL);
	this->stat = (RunnerStatRunning);
	this->runningAction = (NULL);
	this->jumpUpAction = (NULL);
	this->jumpDownAction = (NULL);
	this->crouchAction = (NULL);
	this->_emitter = (NULL);
	//gRunnerCrouchContentSize = NULL;

	this->spriteSheet = spriteSheet;
	this->space = space;
	this->init();
}

Runner * Runner::create (CCSpriteBatchNode *spriteSheet, cpSpace *space)
{
	Runner * runner = new Runner(spriteSheet,space);
	if (runner)
	{
		runner->autorelease();
		return runner;
	}
	CC_SAFE_DELETE(runner);
	return NULL;
}

bool Runner::init()
{
	//4.在你调用CCPhysicsSprite::createWithSpriteFrameName创建物理精灵之前,需要在内存里初始化
	//通过TexturePacker创建的精灵表。这部分工作将在PlayLayer完成。“runner0.png”是第一帧图片。
	sprite = PhysicsSprite::createWithSpriteFrameName("runner0.png");
	runningSize = sprite->getContentSize();

	// init crouchSize
	PhysicsSprite *tmpSprite = PhysicsSprite::createWithSpriteFrameName("runnerCrouch0.png");
	crouchSize = tmpSprite->getContentSize();

	//5.在initAction里, 从帧缓存创建一个帧动画, 让这个动画循环播放。
	initAction();

	//6.在initBody里, 创建runner的物理body, 并设置初始速度
	initBody();

	// start with running shape
	//7.在initShape里,创建与精灵大小相等的chipmunk形状
	initShape("running");

	//8.让物理引擎对象和精灵对象关联起来
	sprite->setCPBody(body);

	//9. 让精灵播放动画
	sprite->runAction(runningAction);

	//10.精灵添加到精灵表单的子节点
	spriteSheet->addChild(sprite, 1);

	//11.记录状态。我们在后面章节将会使用
	stat = RunnerStatRunning;

	return true;
}

//12.重写onExit释放runningAction
void Runner::onExit()
{
	runningAction->release();
	jumpUpAction->release();
	jumpDownAction->release();
	crouchAction->release();
}

void Runner::initAction()
{
#if 1
	// init runningAction
	CCAnimation* animation;
	//创建一个空白的序列帧动画信息
	animation = CCAnimation::create();

	//CCSpriteFrame对应的就是帧，将CCSpriteFrame添加到CCAnimation生成动画数据，
	//用CCAnimation生成CCAnimate（就是最终的动画动作），最后可以用CCSprite执行这个动作。
	CCSpriteFrame * frame;

	// num equal to spriteSheet
	for (unsigned int i = 0; i < 8; i++)
	{
		char str[100] = {0};
		sprintf(str, "runner%i.png", i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animation->addSpriteFrame(frame);
	}

	//animation = CCAnimation.create(animFrames, 0.1);
	animation->setDelayPerUnit(0.1f);

	//设置动画结束后是否保留动画帧信息
	animation->setRestoreOriginalFrame(false);

	//设置循环播放次数 (-1:无限循环)
	animation->setLoops(-1);

	//由这个动画信息创建一个序列帧动画
	runningAction = CCAnimate::create(animation);
	//保存这个动画,这行代码­­­­­retain()将避免CCObject被GC
	//runningAction = CCRepeatForever::create(CCAnimate::create(animation));
	runningAction->retain();

	// init jumpUpAction
	CCAnimation* animation1;
	animation1 = CCAnimation::create();
	CCSpriteFrame * frame1;

	// num equal to spriteSheet
	for (unsigned int i = 0; i < 4; i++)
	{
		char str[100] = {0};
		sprintf(str, "runnerJumpUp%i.png", i);
		frame1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animation1->addSpriteFrame(frame1);
	}
	animation1->setDelayPerUnit(0.2f);
	jumpUpAction = CCAnimate::create(animation1);
	jumpUpAction->retain();

	// init jumpDownAction
	CCAnimation* animation2;
	animation2 = CCAnimation::create();
	CCSpriteFrame * frame2;
	// num equal to spriteSheet
	for (unsigned int i = 0; i < 2; i++)
	{
		char str[100] = {0};
		sprintf(str, "runnerJumpDown%i.png", i);
		frame2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animation2->addSpriteFrame(frame);
	}
	animation2->setDelayPerUnit(0.2f);
	jumpDownAction = CCAnimate::create(animation2);
	jumpDownAction->retain();

	// init crouchAction
	CCAnimation* animation3;
	animation3 = CCAnimation::create();
	CCSpriteFrame * frame3;
	// num equal to spriteSheet
	for (unsigned int i = 0; i < 1; i++)
	{
		char str[100] = {0};
		sprintf(str, "runnerCrouch%i.png", i);
		frame3 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animation3->addSpriteFrame(frame3);
	}
	animation3->setDelayPerUnit(0.3f);
	crouchAction = CCAnimate::create(animation3);
	crouchAction->retain();

#else
	// init runningAction
	CCAnimationFrame *animFrames;

	// num equal to spriteSheet
	for (unsigned int i = 0; i < 8; i++) {
		char str[100] = {0};
		sprintf(str, "runner%i.png", i);
		CCSpriteFrame * frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animFrames->push(frame);
	}

	//animation = CCAnimation.create(animFrames, 0.1);
	animation->setDelayPerUnit(0.1f);

	//设置动画结束后是否保留动画帧信息
	animation->setRestoreOriginalFrame(false);

	//设置循环播放次数 (-1:无限循环)
	animation->setLoops(-1);

	//由这个动画信息创建一个序列帧动画
	runningAction = CCAnimate::create(animation);
	//保存这个动画,这行代码­­­­­retain()将避免CCObject被GC
	//runningAction = CCRepeatForever::create(CCAnimate::create(animation));

	runningAction->retain();
#endif
}

void Runner::initBody()
{
	// create chipmunk body
	int num = 4;
	cpVect verts[] = {
		cpv(-24,-54),
		cpv(-24, 54),
		cpv( 24, 54),
		cpv( 24,-54),
	};

	body = cpBodyNew(1.0f, cpMomentForBox(1,
		runningSize.width, runningSize.height));

	//body = cpBodyNew(1.0f, cpMomentForPoly(1,
		//num, verts, cpvzero));

	//body->p = cpv(offsetPx, g_groundHight + runningSize.height / 2);
	body->p = cpv(g_runnerStartX, g_groundHight + runningSize.height / 2);

	//this.body.applyImpulse(cp.v(150, 0), cp.v(0, 0));
	cpVect arg1 = cpv(150, 0); 
	cpVect arg2 = cpv(0, 0); 

	cpBodyApplyImpulse((cpBody*)body , (cpVect)arg1 , (cpVect)arg2  );

	//body->v = cpv(150, 0);//run speed

	cpSpaceAddBody(space, body);
}

void Runner::levelUp()
{
	// run faster
	//this.body.applyImpulse(cp.v(10, 0), cp.v(0, 0));
	cpVect arg1 = cpv(10, 0); 
	cpVect arg2 = cpv(0, 0); 

	cpBodyApplyImpulse((cpBody*)body , (cpVect)arg1 , (cpVect)arg2  );
}

void Runner::initShape(const char* type) {
	if (shape)
	{
		//space.removeShape(this.shape);
		cpSpaceRemoveShape(space, shape);
	}

	if (type == "running")
	{
		shape = cpBoxShapeNew(body,
			runningSize.width - 14, runningSize.height);
	}
	else{
		// crouch
		shape = cpBoxShapeNew(body,
			crouchSize.width, crouchSize.height);
	}

	//shape = cpBoxShapeNew(body,
		//runningSize.width, runningSize.height);
	//shape->setCollisionType(SpriteTag.runner);
	shape->collision_type = SpriteTagRunner;

	cpSpaceAddShape(space, shape);
}

//13. 这个助手函数在PlayLayer里用于计算相机的移动
float Runner::getPositionX()
{
	return sprite->getPositionX();
}

void Runner::runningHulk(float dt)
{
	// slow down
	//body->applyImpulse(cpv(-400, 0), cp.v(0, 0));
	cpVect arg1 = cpv(-400, 0); 
	cpVect arg2 = cpv(0, 0); 

	cpBodyApplyImpulse(this->body , arg1 , arg2  );

	stat = RunnerStatRunning;
	sprite->stopAllActions();
	sprite->runAction(this->runningAction);

	// clean screen, to avoid rock
	PlayScene *playScene = (PlayScene*)this->getParent();

	//this->getParent()->cleanScreen();
	//PlayScene::cleanScreen();
	playScene->cleanScreen();

	//this->getParent()->cleanup();

	this->unschedule(schedule_selector(Runner::incredibleEmitter));
	
	this->_emitter->removeFromParent();
	this->_emitter->release();
}

void Runner::incredibleHulk()
{
	this->stat = RunnerStatIncredible;

	// run faster
	//body.applyImpulse(cp.v(400, 0), cp.v(0, 0));
	cpVect arg1 = cpv(400, 0); 
	cpVect arg2 = cpv(0, 0); 

	cpBodyApplyImpulse((cpBody*)body , (cpVect)arg1 , (cpVect)arg2);

	//scheduleOnce(schedule_selector(TextureAsync::loadImages), 1.0f);
	this->scheduleOnce(schedule_selector(Runner::runningHulk), 3.0f);

	this->_emitter = CCParticleFlower::create();
	this->_emitter->retain();

	CCTexture2D *myTexture = CCTextureCache::sharedTextureCache()->addImage(s_star);

	this->_emitter->setTexture(myTexture);
	this->_emitter->setPosition(this->sprite->getPositionX(), this->sprite->getPositionY());

	this->addChild(this->_emitter, 10);
	this->schedule(schedule_selector(Runner::incredibleEmitter), 0.1f);
}

void Runner::incredibleEmitter(float dt)
{
	//emitter
	//CCLOG("Runner::incredibleEmitter!!");
	this->_emitter->setPosition(this->sprite->getPositionX(), this->sprite->getPositionY());
}

// return:
//      true for die
//      flase for alive
bool Runner::meetRock() 
{
	if (stat == RunnerStatIncredible) {
		return false;
	} else {
		sprite->stopAllActions();
		//TODO: player die animation
		return true;
	}
}

void Runner::jump()
{
	if (stat == RunnerStatRunning) {

		//this.body.applyImpulse(cp.v(0, 250), cp.v(0, 0));
		cpVect arg1 = cpv(0, 250); 
		cpVect arg2 = cpv(0, 0); 

		cpBodyApplyImpulse((cpBody*)body , (cpVect)arg1 , (cpVect)arg2);

		stat = RunnerStatJumpUp;

		sprite->stopAllActions();
		sprite->runAction(jumpUpAction);

		//播放音效
		//audioEngine->playEffect(s_music_jump);
	}
}

void Runner::crouch()
{
	if (stat == RunnerStatRunning) {
		initShape("crouch");
		sprite->stopAllActions();
		sprite->runAction(crouchAction);

		stat = RunnerStatCrouch;
		// after time turn to running stat
		scheduleOnce(schedule_selector(Runner::loadNormal), 1.5f);

		//audioEngine.playEffect(s_music_crouch);
	}
}

void Runner::loadNormal(float dt)
{
	initShape("running");
	sprite->stopAllActions();
	sprite->runAction(runningAction);
	stat = RunnerStatRunning;
}

void Runner::step(float dt)
{
	//线速度
	cpVect vel = body->v;
	
	if (stat == RunnerStatJumpUp) {
		if (vel.y < 0.1) {
			stat = RunnerStatJumpDown;
			sprite->stopAllActions();
			sprite->runAction(jumpDownAction);
		}
		return;
	}
	if (stat == RunnerStatJumpDown) {
		if (vel.y == 0) {
			stat = RunnerStatRunning;
			sprite->stopAllActions();
			sprite->runAction(runningAction);
		}
		return;
	}
}



