#include "Char_Shop_Scene.hpp"


USING_NS_CC;

Scene*  Shop::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Shop::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool Shop::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    screenWidth  = visibleSize.width; // for screeen width
    screenHeight = visibleSize.height; // for screen height
    
    kScaleX = screenWidth/1024; // scalex
    kScaleY = screenHeight/768;// scaleY
    
    listner = EventListenerTouchOneByOne::create();
    listner->onTouchBegan = CC_CALLBACK_2(Char_Shop_Scene::TouchBegan, this);
    listner->onTouchMoved = CC_CALLBACK_2(Char_Shop_Scene::TouchMoved, this);
    listner->onTouchEnded = CC_CALLBACK_2(Char_Shop_Scene::TouchEnded, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
    
    // Background image of shop Scene
    Sprite *bg = Sprite::create("ShopBg.png");
    bg->setScale(kScaleX, kScaleY);
    bg->setPosition(screenWidth/2, screenHeight/2);
    this->addChild(bg);

    //button of play
    
    btn_select = MenuItemImage::create("btn_select.png", "btn_select.png", CC_CALLBACK_0(Shop::onPlay, this));
    btn_select->setScale(kScaleX);
    btn_select->setPosition(screenWidth/2, screenHeight/4.8-50*kScaleX);
   
    
    Menu *btns = Menu::create(btn_select , NULL);
    btns->setPosition(Vec2::ZERO);
    this->addChild(btns);
    
    initilizeTheme();
    
    return true;
}

void Shop::initilizeTheme()
{
    selectedIndexCharacter = 0;
    char str[30];
    for (int i = 0; i < 3; i++)
    {
        sprintf(str, "shopPlayer%d.png",i+1);
        theme[i] = Sprite::create(str);
        theme[i]->setScale(kScaleX);
        theme[i]->setPosition(cocos2d::Point(((screenWidth/4)*i)+ screenWidth/2, screenHeight/2));
        theme[i]->setOpacity(255);
        
        
        
        if (i != selectedIndexCharacter)
        {
            theme[i]->setPosition(cocos2d::Point(((screenWidth/4)*i)+screenWidth/2, screenHeight/2));
            theme[i]->setScale(0.8*kScaleX);
            theme[i]->setOpacity(150);
        }
        
        this->addChild(theme[i], 1);
    }

}

#pragma mark
#pragma mark on Slide For Change character

void Shop::changeTheme(int posType)
{
    float bydistance;
    if (posType == setNextPos)
    {
        bydistance = -(screenWidth/4);
        selectedIndexCharacter++;
        UserDefault::getInstance()->setIntegerForKey("selectedIndexCharacter",selectedIndexCharacter);
        
        
    }
    
    else if (posType == setPreviousPos)
    {
        bydistance = screenWidth/4;
        selectedIndexCharacter--;
        UserDefault::getInstance()->setIntegerForKey("selectedIndexCharacter",selectedIndexCharacter);
        
    }
    
    else
    {
        bydistance = 0;
    }
    
    for (int i = 0; i < 3; i++)
    {
        cocos2d::Point currentPos = theme[i]->getPosition();
        cocos2d::Point destPoint = cocos2d::Point(currentPos.x + bydistance, currentPos.y);
        
        float sX,sY;
        
        sX = kScaleX;
        sY = kScaleY;
        
        theme[i]->setOpacity(255);
        
        if (i != selectedIndexCharacter)
        {
            sX = kScaleX*0.8;
            sX = kScaleX*0.8;
            theme[i]->setOpacity(150);
        }
        
        
        ScaleTo* newScale = ScaleTo::create(0.1, sX);
        MoveTo* newDest = MoveTo::create(0.1, destPoint);
        Spawn* newSpwn = Spawn::create(newScale, newDest, NULL);
        theme[i]->runAction(newSpwn);
    }
    
    isSwipe = false;
}

#pragma mark -
#pragma mark - Touch Methods

bool Char_Shop_Scene::TouchBegan(Touch *pTouch, Event *pEvent)
{
    isSwipe = true;
    return true;
}

void Char_Shop_Scene::TouchMoved(Touch *pTouch, Event *pEvent)
{
    Touch *touch = (Touch*)pTouch;
    
    cocos2d::Point startPoint = touch->getStartLocationInView();
    cocos2d::Point endPoint   = touch->getLocationInView();
    
    startPoint = Director::getInstance()->convertToGL(startPoint);
    endPoint   = Director::getInstance()->convertToGL(endPoint);
    
    float distance = fabs(startPoint.x - endPoint.x);
    if (isSwipe)
    {
        if (distance > 50*kScaleX && startPoint.x > endPoint.x && selectedIndexCharacter < 2)
        {
            this->changeTheme(setNextPos);
            getInfo();
        }
        
        else if (distance < 50*kScaleX && startPoint.x < endPoint.x && selectedIndexCharacter > 0)
        {
            this->changeTheme(setPreviousPos);
            getInfo();
            
        }
    }

}

void Char_Shop_Scene::TouchEnded(Touch *pTouch, Event *pEvent)
{
    isSwipe = false;
}


#pragma mark
#pragma mark OnSelectButton

void Char_Shop_Scene::onPlay()
{
    Director::getInstance()->replaceScene(TransitionMoveInT::create(0.2, GamePlay::createScene()));//replace scene with game play or something you want.
}

