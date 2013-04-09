#include "Map.h"
//  MapLayer  //
MapLayer::MapLayer(void)
{
	setTouchEnabled(true);
    setTouchPriority(kCCMenuHandlerPriority + 1);
    setTouchMode(kCCTouchesOneByOne);
}
MapLayer::~MapLayer(void)
{
}
MapLayer* MapLayer::create()
{
	 MapLayer * pRet = new MapLayer();
	 return pRet;
	 CC_SAFE_DELETE(pRet);
	 return NULL;
}

void MapLayer::onEnter()
{
	CCLog("MapLayeronEnter");
	CCLayer::onEnter();
}

void MapLayer::onExit()
{
	CCLog("MapLayeronExit");
    CCLayer::onExit();
}  
bool MapLayer::ccTouchBegan(CCTouch *touch, CCEvent * pEvent)
{
	if(checkMoved(touch))
	CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFY_MAP_TOUCH,touch);
    return true;
}

void MapLayer::ccTouchMoved(CCTouch *touch, CCEvent * pEvent)
{
	if(checkMoved(touch))
		CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFY_MAP_MOVE,touch);
}

void MapLayer::ccTouchEnded(CCTouch *touch, CCEvent * pEvent)
{
	CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFY_MAP_END,touch);
}

void MapLayer::ccTouchCancelled(CCTouch *touch, CCEvent * pEvent)
{
	CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFY_MAP_CANCEL,touch);
}

bool MapLayer::checkMoved(CCTouch *touch)
{
	float _px=floor(touch->getLocation().x/MAP_GRID_WIDTH);
	float _py=floor(touch->getLocation().y/MAP_GRID_HEIGHT);
	bool isMove=false;
	if(px!=_px||py!=_py)
	{
		px=_px;
		py=_py;
		isMove=true;
	}
	return isMove;
}
//  Map  //

Map::Map(void)
{
	layer=MapLayer::create();
	CCSprite *tempSprite=CCSprite::create("map.png");
	tempSprite->setAnchorPoint(ccp(0,0));
	layer->addChild(tempSprite);
	layer->setContentSize(tempSprite->getContentSize());
}
Map::~Map(void)
{
}

Map* Map::create()
{
	 Map * pRet = new Map();
	 return pRet;
	 CC_SAFE_DELETE(pRet);
	 return NULL;
}
CCLayer* Map::getLayer()
{
	if(layer)
		return layer;
	else
		return NULL;
}
void Map::setLayerPosition(float x,float y)
{
	layer->setPosition(x,y);
}

void Map::addDefender(int type,int lv,float px,float py)
{
	Defender *defender=Defender::create("knight","knight_stand_0.png");
	layer->addChild(defender->getSprite());
	defender->setPosition(px*30+15,py*30+10);
}