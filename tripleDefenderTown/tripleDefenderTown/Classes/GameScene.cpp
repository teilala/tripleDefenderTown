#include "GameScene.h"
using namespace cocos2d;
Map *_map;
bool GameScene::init()
{    
	bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());
		_map=Map::create();
		this->addChild(_map->getLayer());
		_map->setLayerPosition(0,0);
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameScene::onMapTouch),NOTIFY_MAP_TOUCH, NULL);
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameScene::onMapMove),NOTIFY_MAP_MOVE, NULL);
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameScene::onMapEnd),NOTIFY_MAP_END, NULL);
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameScene::onMapCancel),NOTIFY_MAP_CANCEL, NULL);
		/*CCLayer *mapLayer = CCLayer::create();
		this->addChild(mapLayer);
		 CCSprite *map=CCSprite::create("map.png");
		map->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y));
		mapLayer->addChild(map);*/
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		cache->addSpriteFramesWithFile("knight.plist", "knight.png");
		cache->addSpriteFramesWithFile("ninja.plist", "ninja.png");
		cache->addSpriteFramesWithFile("archer.plist", "archer.png");
		setNextMoveDefender();

		CCLabelTTF* pExitLabel = CCLabelTTF::create("test", "Arial", 24);
         CCMenuItemLabel* item2 = CCMenuItemLabel::create(pExitLabel, this, menu_selector(Controller::menuCallbackTest2) );
         item2->setDisabledColor( ccc3(32,32,64) );
         item2->setColor( ccc3(200,200,255) );
		 CCMenu* menu = CCMenu::create(item2, NULL);
		  menu->alignItemsVertically();
		  addChild(menu);
		  menu->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y));
		 
		bRet = true;
    } while (0);
    return bRet;
}
 
void GameScene::onEnter()
{    
    // do something    
    CCLayer::onEnter();
}
 
void GameScene::Show()
{    
	CCDirector::sharedDirector()->purgeCachedData();
    cocos2d::CCScene *pNewScene = CCScene::create();    
	GameScene *pLayer = GameScene::create();    
    pNewScene->addChild(pLayer);
    cocos2d::CCScene *pCurScene = cocos2d::CCDirector::sharedDirector()->getRunningScene();    
    if(NULL == pCurScene)    
        cocos2d::CCDirector::sharedDirector()->runWithScene(pNewScene);    
    else   
        cocos2d::CCDirector::sharedDirector()->replaceScene(pNewScene);    
}

void GameScene::menuCallbackTest(CCObject *sender)
{
	Defender *newdefender=Defender::create(1,1);
	this->addChild(newdefender->getSprite());
	newdefender->setPosition(VisibleRect::right().x,VisibleRect::center().y);
	newdefender->runAnimate(kAniSkill,.1f,5,false);
	CCLog("rand %d",rand()%10);
}

void GameScene::onClickTest(CCObject* obj)
{
}
void GameScene::onMapTouch(CCObject* obj)
{
	CCTouch *touch=(CCTouch*)obj;
	float _px=floor(touch->getLocation().x/MAP_GRID_WIDTH);
	float _py=floor(touch->getLocation().y/MAP_GRID_HEIGHT);
	if(!_map->getDefender(_px,_py))
		setMoveDefenderPosition(_px,_py);
}

void GameScene::onMapMove(CCObject* obj)
{
	CCTouch *touch=(CCTouch*)obj;
	float _px=floor(touch->getLocation().x/MAP_GRID_WIDTH);
	float _py=floor(touch->getLocation().y/MAP_GRID_HEIGHT);
	if(!_map->getDefender(_px,_py))
		setMoveDefenderPosition(_px,_py);
}

void GameScene::onMapEnd(CCObject* obj)
{
	CCTouch *touch=(CCTouch*)obj;
	float _px=floor(touch->getLocation().x/MAP_GRID_WIDTH);
	float _py=floor(touch->getLocation().y/MAP_GRID_HEIGHT);
	if(!_map->getDefender(_px,_py))
	{
	if(_map->addDefender(moveDefender->id,moveDefender->lv,_px,_py))
		{
			this->removeChild(moveDefender->getSprite());
			moveDefender=NULL;
			setNextMoveDefender();
		}
	}
}

void GameScene::onMapCancel(CCObject* obj)
{
}

void GameScene::setMoveDefenderPosition(int px,int py)
{
	moveDefender->setPosition(px,py);
	_map->checkConnect(moveDefender);
}
void GameScene::setNextMoveDefender()
{
		moveDefender=Defender::create(/*rand()%3+1*/1,1);
		this->addChild(moveDefender->getSprite());
		moveDefender->setPosition(0,MAP_ROW-1);
		//moveDefender->setScale(.5);
		moveDefender->runAnimate(kAniSkill,.1f,5,false);
}