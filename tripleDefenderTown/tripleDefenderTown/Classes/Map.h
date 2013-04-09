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
	void setLayerPosition(float x,float y);
	void addDefender(int type,int lv,float px,float py);
private:
	MapLayer *layer;
};
#endif

