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
	initMaps();
	initMergeArr();
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
void Map::initMaps()
{
	memset(maps,NULL,sizeof(maps));
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

bool Map::addDefender(int id,int lv,int px,int py)
{
	Defender* defender=getDefender(px,py);
	if(!defender)
	{
		//to do 把assets改成動態
		Defender *defender=Defender::create(id,lv);
		layer->addChild(defender->getSprite());
		defender->setPosition(px,py);
		maps[py][px]=defender;
		initMergeArr();
		getConnectionDefenders(defender,defender->id,defender->lv,defender->px,defender->py);
		if(mergeIndex)
		{
			clearDefenders(mergeArr);
			defender->setLv(defender->lv+mergeIndex);
			initMergeArr();
		}
		return true;
	}
	else
		return false;
}
Defender* Map::getDefender(int px,int py)
{
	Defender* defender=(Defender*)maps[py][px];
	if(defender==NULL)
		return NULL;
	return defender;
}
void Map::getConnectionDefenders(Defender* defender, int id,int lv,int px,int py)
{
	do
	{
	memset(tempConnect,NULL,sizeof(tempConnect));
	tempConnectIndex=0;
	_getConnectionDefenders(defender,id,lv,px,py);
	if(checkMerge(defender->id,defender->lv,tempConnectIndex))
	{
		pushArray(mergeArr,tempConnect);
		getConnectionDefenders(defender,id,lv+1,px,py);
	}
	}while(0);
}
bool Map::checkMerge(int id,int lv,int num)
{
	return (num>=3);
}
void Map::checkConnect(Defender* defender)
{
		stopConnectAni(mergeArr);
		initMergeArr();
		getConnectionDefenders(defender,defender->id,defender->lv,defender->px,defender->py);
		if(mergeIndex)
		{
			CCLog("merge");
			showConnectAni(defender,mergeArr);
			//defender->setLv(defender->lv+mergeIndex);
		}
}
void Map::stopConnectAni(Defender* arr[])
{
	for(int i=0;i<MAP_ROW*MAP_COL;i++)
	{
		Defender* sourceDefender=arr[i];
		if(sourceDefender)
		{
			sourceDefender->getSprite()->stopAllActions();
			sourceDefender->updatePosition();
		}
	}
}
void Map::showConnectAni(Defender* targetDefender,Defender* arr[])
{
	for(int i=0;i<MAP_ROW*MAP_COL;i++)
	{
		Defender* sourceDefender=arr[i];
		if(sourceDefender)
		{
			int mx=(targetDefender->px==sourceDefender->px)?0:(targetDefender->px>sourceDefender->px)?10:-10;
			int my=(targetDefender->py==sourceDefender->py)?0:(targetDefender->py>sourceDefender->py)?10:-10;
			CCActionInterval*  actionBy = CCMoveBy::create(.5f, ccp(mx,my));
			CCActionInterval*  actionByBack = actionBy->reverse();
			CCAction*  rep = CCRepeatForever::create(CCSequence::create(actionBy, actionByBack, NULL));
			sourceDefender->getSprite()->runAction(rep);
		}
	}
}
void Map::_getConnectionDefenders(Defender* defender, int id,int lv,int px,int py)
{
	tempConnect[tempConnectIndex]=defender;
	tempConnectIndex+=1;
	const int r=4;
	const int c=2;
	int searchDirect[r][c]={{-1,0},{0,-1},{1,0},{0,1}};
	for(int i=0;i<r;i++){
			Defender *targetDefender=getDefender(px+searchDirect[i][0],py+searchDirect[i][1]);
			if(targetDefender&&targetDefender->id==id&&targetDefender->lv==lv&&!indexof(tempConnect,targetDefender))
			{
				_getConnectionDefenders(targetDefender,id,lv,px+searchDirect[i][0],py+searchDirect[i][1]);
			}
	}
}

bool Map::indexof(Defender* arr[],Defender* defender)
{
	for(int i=0;i<MAP_ROW*MAP_COL;i++)
	{
		Defender* targetDefender=arr[i];
		if(arr[i])
		{
			if(targetDefender==defender)
				return true;
		}
		else
			return false;
	}
}

void Map::pushArray(Defender* sourceArr[],Defender* targetArr[])
{
	mergeIndex++;
	int lastIndex=0;
	for(int i=0;i<MAP_ROW*MAP_COL;i++)
	{
		Defender* sourceDefender=sourceArr[i];
		if(!sourceDefender)
		{
			lastIndex=i;
			break;
		}
	}
	//因為第一個是最後一個放的 也就是升級目標 所以就不用加了
	for(int i=1;i<MAP_ROW*MAP_COL;i++)
	{
		Defender* targetDefender=targetArr[i];
		if(!targetDefender)
			break;
		else
		{
			sourceArr[lastIndex]=targetDefender;
			lastIndex++;
		}
	}
}

void Map::clearDefenders(Defender* sourceArr[])
{
	for(int i=0;i<MAP_ROW*MAP_COL;i++)
	{
		Defender* sourceDefender=sourceArr[i];
		if(sourceDefender)
		{
		layer->removeChild(sourceDefender->getSprite());
		maps[sourceDefender->py][sourceDefender->px]=NULL;
		sourceDefender=NULL;
		}
	}
}

void Map::initMergeArr()
{
	memset(mergeArr,0,sizeof(mergeArr));
	mergeIndex=0;
}