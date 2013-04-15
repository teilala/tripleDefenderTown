#ifndef _MAP__H_
#define _MAP__H_

#include "Basic.h"
class MapLayer : public CCLayer,public CCTargetedTouchDelegate
{
public:
	MapLayer();
	~MapLayer();
	static MapLayer* create();
	virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchCancelled(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent * pEvent);
	bool checkMoved(CCTouch *touch);
private:
	float px;
	float py;
};
class Map
{
public:
	Map();
	~Map();
	static Map* create();
	CCLayer* getLayer();
	void initMaps();
	void setLayerPosition(float x,float y);
	bool addDefender(int id,int lv,int px,int py);
	Defender* getDefender(int px,int py);
	void getConnectionDefenders(Defender* defender, int id,int lv,int px,int py);
	void _getConnectionDefenders(Defender* defender, int id,int lv,int px,int py);
	bool indexof(Defender* arr[],Defender* defender);
	bool checkMerge(int id,int lv,int num);
	void checkConnect(Defender* defender);
	void stopConnectAni(Defender* arr[]);
	void showConnectAni(Defender* targetDefender,Defender* arr[]);
private:
	MapLayer* layer;
	Defender* maps[MAP_ROW][MAP_COL];
	Defender* tempConnect[MAP_ROW*MAP_COL];
	int tempConnectIndex;
	Defender* mergeArr[MAP_ROW*MAP_COL];
	int mergeIndex;
	void pushArray(Defender* sourceArr[],Defender* targetArr[]);
	void clearDefenders(Defender* sourceArr[]);
	void initMergeArr();
};
#endif

