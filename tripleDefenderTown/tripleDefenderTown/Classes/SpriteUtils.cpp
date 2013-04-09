#include "SpriteUtils.h"

void SpriteUtils::test(){
	CCLog("ok");
}

CCAnimation* SpriteUtils::animationWithSingleFrames(const char *name)
{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCArray *animFrames = CCArray::create();
	
	char str[80];
	int k = 0;
	while(1)
    {
        sprintf(str, "%s%d.png", name, (k));
        CCSpriteFrame *frame = cache->spriteFrameByName(str);
		if(frame) animFrames->addObject(frame);
		else break;
		k++;
    }
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames);
	return animation;
}
