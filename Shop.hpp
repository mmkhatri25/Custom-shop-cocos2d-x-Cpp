

#ifndef Shop_hpp
#define Shop_hpp

#include <stdio.h>

enum
{
    setNextPos,
    setPreviousPos
};

class Shop : public cocos2d::Layer
{
public:
    
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    EventListenerTouchOneByOne *listner;
    bool TouchBegan(cocos2d::Touch *pTouch,cocos2d::Event *pEvent);
    void TouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    void TouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

    float kScaleX, kScaleY;
    float screenWidth, screenHeight;
    
    bool isSwipe;
    int unlockValue[3] = {0, 0, 0};
    
    Label *lbl_required;
    Sprite* theme[3];
    
    MenuItemImage *btn_select;
    void getInfo();
    void chkUnlockStatus();

    void onPlay();
    void initilizeTheme();
    void changeTheme(int posType);
    CREATE_FUNC(Shop);
};


#endif /* Shop_Scene_hpp */
