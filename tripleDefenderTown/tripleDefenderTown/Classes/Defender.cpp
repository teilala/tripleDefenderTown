#include "Defender.h"

Defender::Defender(char *n,char *dSprite)
{
	 name=n;
	 defaultSprite=dSprite;
}
Defender::~Defender(void)
{
}
Defender* Defender::create(char *n,char *dSprite)
{
	 Defender * pRet = new Defender(n,dSprite);
	 return pRet;
	 CC_SAFE_DELETE(pRet);
	 return NULL;
}
DefenderSprite* Defender::getSprite()
{
	if(defaultSprite)
		sprite = DefenderSprite::createWithName(defaultSprite);
	return sprite;
}

void Defender::setPosition(float x,float y)
{
	float dy=sprite->getContentSize().height/2*sprite->getScale();
	sprite->setPosition(ccp(x,y+dy));
}
void Defender::setScale(float s)
{
	sprite->setScale(s);
}
void Defender::runAnimate(int nInd,float delay,int loops,bool RestoreOriginalFrame)
{
	sprite->stopAllActions();
	string type="";
	switch(nInd)
	{
		case kAniAttack:
			type="attack";
		break;
		case kAniJump:
			type="jump";
		break;
		case kAniSkill:
			type="skill";
		break;
	}
	CCAnimation *animation = SpriteUtils::animationWithSingleFrames(string(string(name) + "_"+type+"_").c_str());
	animation->setDelayPerUnit(delay);
	animation->setLoops(loops);    // 设置循环播放  
	animation->setRestoreOriginalFrame(RestoreOriginalFrame);
	CCAnimate* action = CCAnimate::create(animation);
	 sprite->runAction(action);
}

DefenderSprite::DefenderSprite(void)
{
	m_state = kDefenderStateUngrabbed;
}

DefenderSprite::~DefenderSprite(void)
{
}

DefenderSprite* DefenderSprite::createWithName(char *dSprite)
{
	DefenderSprite* pDefenderSprite = new DefenderSprite();
	if(dSprite)
		pDefenderSprite->initWithSpriteFrameName(dSprite);
    pDefenderSprite->autorelease();
    return pDefenderSprite;
}

void DefenderSprite::onEnter()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCSprite::onEnter();
}

void DefenderSprite::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}  

CCRect DefenderSprite::rect()
{
    CCSize s = getTexture()->getContentSize();
    return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool DefenderSprite::containsTouchLocation(CCTouch* touch)
{
    return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool DefenderSprite::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    if (m_state != kDefenderStateUngrabbed) return false;
    if ( !containsTouchLocation(touch) ) return false;
	CCPoint touchPoint = touch->getLocation();
	dx=touchPoint.x-getPosition().x;
	dy=touchPoint.y-getPosition().y;
    m_state = kDefenderStateGrabbed;
    return true;
}

void DefenderSprite::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CCAssert(m_state == kDefenderStateGrabbed, "Defender - Unexpected state!");    
    
    CCPoint touchPoint = touch->getLocation();
    
    setPosition( ccp(touchPoint.x-dx,touchPoint.y-dy) );
}

void DefenderSprite::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    CCAssert(m_state == kDefenderStateGrabbed, "Defender - Unexpected state!");    
    
    m_state = kDefenderStateUngrabbed;
} 

void DefenderSprite::ccTouchesCancelled(CCTouch *touch, CCEvent *event)
{
	 m_state = kDefenderStateUngrabbed;
}
void DefenderSprite::touchDelegateRetain()
{
    this->retain();
}

void DefenderSprite::touchDelegateRelease()
{
    this->release();
}