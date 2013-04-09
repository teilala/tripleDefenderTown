#ifndef _DEFENDER__H_
#define _DEFENDER__H_
#include "SpriteUtils.h"
#include <string> 
using namespace std; 
using namespace cocos2d;
typedef enum tagDefenderState 
{
    kDefenderStateGrabbed,
    kDefenderStateUngrabbed
}DefenderState; 
typedef enum tagAniState 
{
    kAniAttack,
    kAniJump,
	kAniSkill
}AniState; 
class DefenderSprite :public CCSprite,public CCTargetedTouchDelegate
{
public:
	DefenderSprite(void);
    virtual ~DefenderSprite(void);
	virtual void onEnter();
    virtual void onExit();
	static DefenderSprite* createWithName(char *dSprite);
	CCRect rect();
	bool containsTouchLocation(CCTouch* touch);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchesCancelled(CCTouch *touch, CCEvent *event);
	virtual void touchDelegateRetain();
    virtual void touchDelegateRelease();
private:
	DefenderState m_state;
	float dx,dy;
};
class Defender
{
public:
	Defender::Defender(char *n,char *dSprite);
	~Defender();
	static Defender* create(char *n,char *dSprite);
	DefenderSprite* getSprite();
	void setPosition(float x,float y);
	void setScale(float s);
	void runAnimate(int nInd,float delay,int loops=-1,bool RestoreOriginalFrame=true);
private:
	DefenderSprite *sprite;
	char *name;
	char *defaultSprite;
};

#endif
