#include "EquipScene.h"
using namespace cocos2d;
bool EquipScene::init()
{    
	bool bRet = false;
    do 
    {
        
        CC_BREAK_IF(! CCLayer::init());
		  bRet = true;
    } while (0);
    return bRet;
}
 
void EquipScene::onEnter()
{    
    // do something    
	CCLog("first");
    CCLayer::onEnter();
}
 
void EquipScene::Show()
{    
	CCDirector::sharedDirector()->purgeCachedData();
    cocos2d::CCScene *pNewScene = CCScene::create();    
	EquipScene *pLayer = EquipScene::create();    
    pNewScene->addChild(pLayer);    
    cocos2d::CCScene *pCurScene = cocos2d::CCDirector::sharedDirector()->getRunningScene();    
    if(NULL == pCurScene)    
        cocos2d::CCDirector::sharedDirector()->runWithScene(pNewScene);    
    else   
        cocos2d::CCDirector::sharedDirector()->replaceScene(pNewScene);    
}