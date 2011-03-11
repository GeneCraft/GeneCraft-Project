/// Betajaen's GUI 016 Uncompressed
/// Written by Robin "Betajaen" Southern 07-Nov-2006, http://www.ogre3d.org/wiki/index.php/BetaGUI
/// This code is under the Whatevar! licence. Do what you want; but keep the original copyright header.
#include "BetaGUI.h"

#include "OgreTextAreaOverlayElement.h"
using namespace Ogre;
using namespace std;

namespace BetaGUI 
{
    //------------------------------------------------------------------------------------------------
	GUI::GUI(const String &baseOverlay, const String &font, int fontSize, RenderWindow *win)
		:mNextWindowToDestroy(0),
		 mMousePointerOverlay(0),
		 mFont(font),
		 mFontSize(fontSize),
		 mWindowCount(0),
		 mButtonCount(0),
		 mTextCaptionCount(0),
         mTextCaptionCountArea(0),
         mButtonCountTextArea(0),
         mNextMenuWindowPos(0,0),
         mMenuWindow(0),
         mRenderWindow(win),
         mDragWindowAction(WA_NONE),
         mActiveDraggedWindow(0),
         mActiveTextInput(0),
         mActiveButton(0),
         mUpTime(0),
         mFarZ(100),
         mNearZ(101),
         mName(baseOverlay)
    {
           
    }
    //------------------------------------------------------------------------------------------------
	GUI::~GUI() 
    {
        for(std::vector<Window*>::iterator i=mWindows.begin();i!=mWindows.end();++i) 
        {
            delete (*i); 
        }

        std::list<Effect*>::iterator itEffect = mActiveEffects.begin();
        while (itEffect != mActiveEffects.end())        
        {
            delete *itEffect;
            ++itEffect;            
        } 
    }
    //------------------------------------------------------------------------------------------------
    void GUI::setZRangeOrder(int nearZ, int FarZ) 
    {
        assert (mNearZ > mFarZ);
        mNearZ = nearZ;
        mFarZ = FarZ;
        sortZOrder();
    };
    //------------------------------------------------------------------------------------------------
    void GUI::sortZOrder()
    {
        assert (mNearZ > mFarZ);
        int farZ = mFarZ;
        for(std::vector<Window*>::iterator i=mWindows.begin();i!=mWindows.end();++i) 
        {
            (*i)->setZOrder(farZ) ; 
            if (farZ + 1 < mNearZ)
                farZ++;
        }
        if (mActiveDraggedWindow)
            mActiveDraggedWindow->setZOrder(mNearZ) ;
    }
    //------------------------------------------------------------------------------------------------
    void GUI::update (Ogre::Real timeElapsed)
    {
        mUpTime += timeElapsed;

        {
            std::vector<Window*>::iterator itWindow = mWindows.begin();       
            while (itWindow != mWindows.end())        
            {
                (*itWindow)->setUnderEffect(false);
                ++itWindow;
            } 
        }
        {
            std::list<Effect*>::iterator itEffect = mActiveEffects.begin();       
            while (itEffect != mActiveEffects.end())        
            {
                if ((*itEffect)->update(timeElapsed))
                {
                    delete *itEffect;
                    itEffect = mActiveEffects.erase(itEffect);
                }
                else
                {
                    ++itEffect;
                }
            } 
        }
        if (mNextWindowToDestroy) 
        {
            for(std::vector<Window*>::iterator i=mWindows.begin();i!=mWindows.end();++i) 
            {
                if(mNextWindowToDestroy==(*i)) 
                {
                    delete mNextWindowToDestroy;
                    mWindows.erase(i);
                    mNextWindowToDestroy=0;
                }
            }
        }
    }
    //------------------------------------------------------------------------------------------------
    void GUI::addEffect (Effect* e)
    {
        mActiveEffects.push_back(e);
    }
    //-----------------------------------------------------------------------------
	bool GUI::injectMouse(int x, int y, bool LMB) 
    {		
        if (mMousePointerOverlay)
        {
            mMousePointerOverlay->hide ();
            mMousePointerOverlay->setPosition(x,y);
        }

               
        if (LMB)
        {
            if (mActiveTextInput) 
            { 
                mActiveTextInput->mMainOverlay->setMaterialName(mActiveTextInput->mMaterialName);
                mActiveTextInput = 0;
            }


            if (mActiveButton && mActiveDraggedWindow) 
            {
                 if (mActiveDraggedWindow->mDragType == WA_MOVE) 
                 {
                       mDragWindowAction = WA_MOVE; 
                       mActiveDraggedWindow->setPosition (
                           mDragWindowX + (x - mDragX),
                           mDragWindowY + (y - mDragY)
                           );
                       return true;
                 } 
                 else if (mActiveDraggedWindow->mDragType == WA_RESIZE) 
                 {
                     mDragWindowAction = WA_RESIZE; 
                     mActiveDraggedWindow->setSize (
                         mDragWindowX + (x - mDragX),
                         mDragWindowY + (y - mDragY)
                         );
                       return true;
                 } 
            }
        }
        else if (mDragWindowAction != WA_NONE)
        {
            mDragWindowAction = WA_NONE;
            mActiveDraggedWindow = 0; 
            sortZOrder ();
        }

        assert (mDragWindowAction == WA_NONE) ;  
        for(std::vector<Window*>::iterator i=mWindows.begin();i!=mWindows.end();++i) 
        {
		    if((*i)->isVisible() && 
                (*i)->check(x, y, LMB)) 
            {
                mActiveDraggedWindow = (*i);
                sortZOrder ();

                if (mMousePointerOverlay)
                    mMousePointerOverlay->show ();
			    return true;
		    }
	    }      

		return false;
    }	
    //------------------------------------------------------------------------------------------------
	bool GUI::injectKey(const String &key, int x, int y) 
    {
        if (mActiveTextInput == 0 || key.empty()) 
            return false;

        if (key == "!b") 
        {
            mActiveTextInput->setValue(
                mActiveTextInput->mValueText.substr(0, mActiveTextInput->mValueText.length()-1)
                );
            return true;
        }

        if (mActiveTextInput->mValueText.length() >= mActiveTextInput->length) 
            return true;

        mActiveTextInput->mCaptionOverlay->setCaption(mActiveTextInput->mValueText += key);
        return false;
    }
    //------------------------------------------------------------------------------------------------
	void GUI::injectBackspace(int x, int y) 
    {
		injectKey("!b", x, y);
    }
    //------------------------------------------------------------------------------------------------
	OverlayContainer* GUI::createOverlay(const String &name, const Vector2 &position, 
        const Vector2 &dimensions, const String &material, 
        const String &caption) 
    {
        OverlayContainer* e;
        const bool isTextArea = !caption.empty();
        try
        {
            e =  static_cast<OverlayContainer*>
                (OverlayManager::getSingleton().getOverlayElement (name));
        }
        catch (...) 
        {    
            e = static_cast<OverlayContainer*>
                (OverlayManager::getSingleton().createOverlayElement(
                    (isTextArea ? "TextArea" : "Panel" ), 
                    name));
        }

        e->setMetricsMode(Ogre::GMM_PIXELS);
        e->setDimensions(dimensions.x, dimensions.y);
        e->setPosition(position.x, position.y);

        if (!material.empty())
            e->setMaterialName(material);

        if (isTextArea) 
        {
            e->setCaption(caption);
            e->setParameter("font_name", mFont);
            e->setParameter("char_height", StringConverter::toString(mFontSize));

            e->setParameter("colour_top", 
                StringConverter::toString(ColourValue(0.57, 0.86, 0.68, 1.00)));
            e->setParameter("colour_bottom", 
                StringConverter::toString(ColourValue(0.68, 0.86, 0.68, 1.00)));
        } 
		return e;
    }
    //------------------------------------------------------------------------------------------------
    OverlayContainer* GUI::createMousePointer(Vector2 d, const String &m) 
    {
        Overlay* o = (Overlay*)OverlayManager::getSingleton().getByName("BetaGUI.MP");
		if (!o)
            o = OverlayManager::getSingleton().create("BetaGUI.MP");

		o->setZOrder(649);

		mMousePointerOverlay = createOverlay("bg.mp", Vector2(0,0), d, m, "");

        if (mMousePointerOverlay != o->getChild (mMousePointerOverlay->getName ()))
		    o->add2D(mMousePointerOverlay);
		o->show();
        mMousePointerOverlay->show();
		return mMousePointerOverlay;
    }
    //------------------------------------------------------------------------------------------------
    Window* GUI::createWindow(const Vector4 &Dimensions, const String & Material, WindowFeatureType type, const String &caption) 
    {
        Window* window = new Window(Dimensions, Material, type, caption, this);
        mWindows.push_back(window);
        return window;
    }
    //------------------------------------------------------------------------------------------------
    Window *GUI::addMenuWindow(const Vector2 dimensions)
    {
        assert (mMenuWindow == 0);       
        mMenuWindow = createWindow(Vector4(0, 0, dimensions.x, dimensions.y),
            "bgui.window", WFT_NONE,  ""); 

        mNextMenuWindowPos.y = 25;
        return mMenuWindow;
    }
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    Widget::Widget(const Ogre::Vector4 &Dimension, 
        const Ogre::String &materialNameNormal,
        bool hasOverState,
        bool hasActiveState):
        mPosX(Dimension.x),
        mPosY(Dimension.y),
        mWidth(Dimension.z),
        mHeight(Dimension.w),
        mMainOverlay(0), 
        mCaptionOverlay(0),
        mMaterialName(materialNameNormal),
        mHasMaterial(!materialNameNormal.empty()),
        mHasOverState(hasOverState && mHasMaterial),
        mHasActiveState(hasActiveState && mHasMaterial),
        mUnderEffect(false),
        mOver(false),
        mActive(false)
    {

    }
    //------------------------------------------------------------------------------------------------
    Widget::~Widget() 
    {
        if (mMainOverlay && mMainOverlay->getParent()) mMainOverlay->getParent()->removeChild(mMainOverlay->getName());
        if (mCaptionOverlay && mCaptionOverlay->getParent()) mCaptionOverlay->getParent()->removeChild(mCaptionOverlay->getName());

        for(std::vector<Widget*>::iterator i=mChildren.begin();i!=mChildren.end();++i)
            delete (*i);
    }  
    //------------------------------------------------------------------------------------------------
    void Widget::over(const bool a) 
    {
        assert(!mUnderEffect);
        mOver = a;
        if (!a && mHasMaterial && mMainOverlay)
        {
            mMainOverlay->setMaterialName(mMaterialName);

            if (mCaptionOverlay)
            {
                mCaptionOverlay->setParameter("colour_top", 
                    Ogre::StringConverter::toString(Ogre::ColourValue(0.57, 0.86, 0.68, 1.0)));
                mCaptionOverlay->setParameter("colour_bottom", 
                    Ogre::StringConverter::toString(Ogre::ColourValue(0.68, 0.86, 0.68, 1.00)));
            }
        }
        if (a && mHasActiveState && mMainOverlay)
        {
            mMainOverlay->setMaterialName(mMaterialName + ".over");

            if (mCaptionOverlay)
            {
                mCaptionOverlay->setParameter("colour_top", 
                    Ogre::StringConverter::toString(Ogre::ColourValue(1.0, 0.96, 0.76, 1.0)));
                mCaptionOverlay->setParameter("colour_bottom", 
                    Ogre::StringConverter::toString(Ogre::ColourValue(1.0, 0.96, 0.76, 1.00)));
            }
        }
        // propagate ?
        //for(std::vector<Widget*>::iterator i=mChildren.begin();i!=mChildren.end();++i) 
        //{
        //    (*i)->over(a);
        //}
    }
    //------------------------------------------------------------------------------------------------
    void Widget::activate(const bool a) 
    {
        assert(!mUnderEffect);
        mActive = a;
        if (!a && mHasMaterial && mMainOverlay)
        {
            mMainOverlay->setMaterialName(mMaterialName);

            if (mCaptionOverlay)
            {
                mCaptionOverlay->setParameter("colour_top", 
                    Ogre::StringConverter::toString(Ogre::ColourValue(0.57, 0.86, 0.68, 1.0)));
                mCaptionOverlay->setParameter("colour_bottom", 
                    Ogre::StringConverter::toString(Ogre::ColourValue(0.68, 0.86, 0.68, 1.00)));
            }
        }
        if (a && mHasActiveState && mMainOverlay)
        {
            mMainOverlay->setMaterialName(mMaterialName + ".active");

            if (mCaptionOverlay)
            {
                mCaptionOverlay->setParameter("colour_top", 
                    Ogre::StringConverter::toString(Ogre::ColourValue(1.0, 0.96, 0.76, 1.0)));
                mCaptionOverlay->setParameter("colour_bottom", 
                    Ogre::StringConverter::toString(Ogre::ColourValue(1.0, 0.96, 0.76, 1.00)));
            }
        }
        // propagate ?
        //for(std::vector<Widget*>::iterator i=mChildren.begin();i!=mChildren.end();++i) 
        //{
        //    (*i)->activate(a);
        //}
    }
    //------------------------------------------------------------------------------------------------
    void Widget::setUnderEffect(const bool effect)
    {
        if (effect)
        {
            if (mActive)
                activate (false);
            if (mOver)
                over (false);
        }
        mUnderEffect = effect;
    };
    //------------------------------------------------------------------------------------------------
    void Widget::instantiateMaterial(OverlayContainer * const oc, bool reset) const
    {
        if (oc->getMaterial ().isNull ())
            return;

        const String matName (oc->getMaterial ()->getName ());
        const bool isInstantied = StringUtil::endsWith(matName, ".GuiInstance", false);
        if (reset)
        {
            if (isInstantied)
                oc->setMaterialName (
                matName.substr(0, 
                matName.length() - (oc->getName ().length() + 12)));
        }
        else if (!isInstantied)
        {
            const String newMatName(matName + oc->getName () + ".GuiInstance");
            // need to instantiate a material there...
            if (!MaterialManager::getSingleton ().resourceExists (newMatName))
            {
                oc->getMaterial ()->clone (newMatName);
            }                    
            oc->setMaterialName (newMatName);
        }
    }
    //------------------------------------------------------------------------------------------------
    void Widget::setOverlayAlpha(OverlayContainer * const oc, const Ogre::Real alpha) const
    {
        if (!oc->getMaterial ().isNull ())
        {
            TextureUnitState *t = oc->getMaterial ()->getBestTechnique ()->getPass(0)->getTextureUnitState (0);
            if (t) t->setAlphaOperation (LBX_MODULATE, LBS_TEXTURE, LBS_MANUAL, alpha, alpha, alpha);
        }
    } 
    //------------------------------------------------------------------------------------------------
    void Widget::setAlpha(const Ogre::Real alpha, const bool isContainer)
    {         
        bool noAlpha = false;
        Ogre::Real alphaValue = alpha;
    
        if (alphaValue - 1.0 > -std::numeric_limits<Real>::epsilon())
        {
            noAlpha = true;
            if (isContainer) mMainOverlay->show ();   
        }
        else if (alphaValue < std::numeric_limits<Real>::epsilon())
        {
            noAlpha = true;
            if (isContainer) mMainOverlay->hide ();
        }
        else if (isContainer)
        {
            mMainOverlay->show ();   
        }        
        if (noAlpha) alphaValue =  Ogre::Real(1.0);

        //should save in a boolean the instantiated state...
        if (mMainOverlay)
        {
            instantiateMaterial (mMainOverlay, noAlpha);
            if (!noAlpha) setOverlayAlpha (mMainOverlay, alphaValue);
        }
        if (mCaptionOverlay)
        {
            instantiateMaterial (mCaptionOverlay, noAlpha);
            if (!noAlpha) setOverlayAlpha (mCaptionOverlay, alphaValue);
        }
        for(std::vector<Widget*>::iterator i=mChildren.begin();i!=mChildren.end();++i) 
        {
            (*i)->setAlpha(alphaValue, false);
        }
    }
    //------------------------------------------------------------------------------------------------
    void Widget::setMaterialBlendFactor(const Ogre::Real blendFactor, const bool isContainer)
    {
        bool noBlendFactor = false;
        Ogre::Real blendFactorValue = blendFactor;

        if (blendFactorValue - 1.0 > -std::numeric_limits<Real>::epsilon())
        {
            noBlendFactor = true;
        }
        else if (blendFactorValue < std::numeric_limits<Real>::epsilon())
        {
            noBlendFactor = true;
        }
        if (noBlendFactor) blendFactorValue =  Ogre::Real(1.0);

        //should save in a boolean the instantiated state...
        if (mMainOverlay)
        {
            instantiateMaterial (mMainOverlay, noBlendFactor);
            if (!noBlendFactor) setOverlayMaterialBlendFactor (mMainOverlay, blendFactorValue);
        }
        if (mCaptionOverlay)
        {
            instantiateMaterial (mCaptionOverlay, noBlendFactor);
            if (!noBlendFactor) setOverlayMaterialBlendFactor (mCaptionOverlay, blendFactorValue);
        }
        for(std::vector<Widget*>::iterator i=mChildren.begin();i!=mChildren.end();++i) 
        {
            (*i)->setMaterialBlendFactor(noBlendFactor, false);
        }
    }
    //------------------------------------------------------------------------------------------------
    void Widget::setOverlayMaterialBlendFactor(OverlayContainer * const oc, const Ogre::Real blendFactor) const
    {
        if (!oc->getMaterial ().isNull ())
        {
            TextureUnitState *t = oc->getMaterial ()->getBestTechnique ()->getPass(0)->getTextureUnitState (1);
            if (t) 
                //t->setAlphaOperation (LBX_MODULATE, LBS_TEXTURE, LBS_MANUAL, blendFactor, blendFactor, blendFactor);
                t->setColourOperationEx(LBX_BLEND_MANUAL, LBS_TEXTURE, LBS_CURRENT, ColourValue::White, ColourValue::White, blendFactor);
        }
    }
    //------------------------------------------------------------------------------------------------
    void Widget::adjustSizeToContent()
    {
        Ogre::Real w = 0;
        Ogre::Real h = 0;
        for(std::vector<Widget*>::iterator i=mChildren.begin();i!=mChildren.end();++i) 
        {
            const Vector2 pos ((*i)->getPosition());
            const Vector2 size ((*i)->getSize());

            w = std::max(w, pos.x + size.x);
            h = std::max(h, pos.y + size.y);
        }
        setSize(w, h);
    }
    //------------------------------------------------------------------------------------------------
    void Widget::setPosition(const Ogre::Vector2 &position)
    {
        setPosition(position.x, position.y);
    }
    //------------------------------------------------------------------------------------------------
    void Widget::setPosition(int X,int Y)
    {
        if (mMainOverlay) mMainOverlay->setPosition(mPosX=X,mPosY=Y);
    }
    //------------------------------------------------------------------------------------------------
    void Widget::setSize(const Ogre::Vector2 &size)
    {
        setSize(size.x, size.y);
    };
    //------------------------------------------------------------------------------------------------
    void Widget::setSize(int X,int Y)
    {
        if (mMainOverlay) mMainOverlay->setDimensions(mWidth=X, mHeight=Y);
        if (mCaptionOverlay) mCaptionOverlay->setDimensions(mWidth, mHeight);
    };
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
	Window::Window(const Vector4 &Dimensions, const String &material, WindowFeatureType t, const String &caption, GUI *gui)
		: 
          Widget(Dimensions, material, true, true),
		  mGUI(gui),
		  mTitleBarButton(0),
          mCloseButton(0),
		  mResizerButton(0),
		  mActiveTextInput(0),
		  mActiveButton(0),
          mNextWidgetPos(0, 0),
          mDragType(WA_NONE)
	{
 
        const String name(gui->mName + ".w" + StringConverter::toString(gui->mWindowCount++));
        mGuiOverlay = (Overlay*)OverlayManager::getSingleton().getByName(name);
        if (!mGuiOverlay)
			mGuiOverlay = OverlayManager::getSingleton().create(name);
		mGuiOverlay->show();

        
		mMainOverlay = gui->createOverlay(name, 
                                Vector2(Dimensions.x, Dimensions.y), 
                                Vector2(Dimensions.z, Dimensions.w), 
                                material); 
        if (mMainOverlay != mGuiOverlay->getChild (mMainOverlay->getName ()))
            mGuiOverlay->add2D(mMainOverlay);
        mMainOverlay->show();

		if (t >= 2) 
        {
			Callback c;
            c.mCallbackType=4;
			mResizerButton = createButton(
                Vector4(Dimensions.z-16, Dimensions.w-16, 16, 16),
                material + ".resize", "", c);
		}
        
        if ((t == 1 || t == 3) && !caption.empty()) 
        {
			Callback c;
            c.mCallbackType=3;

			mTitleBarButton = createButton(Vector4(0,0,Dimensions.z-22,22),
                material + ".titlebar", caption, c);

            mCloseButton = createMenuButton(Vector4(Dimensions.z-22,0,22,22),
                material + ".close",  "", Callback(), this);

            mNextWidgetPos.x += 12;
            mNextWidgetPos.y += 22;
        }  
    }
    //------------------------------------------------------------------------------------------------
    Window::~Window()
    {
       //Widget::~Widget();
       //OverlayManager::getSingleton ().destroy (mGuiOverlay->getName ());
    }
    //------------------------------------------------------------------------------------------------
    void Window::addWidget(const Widget * const w, WindowPlacementType wpt)
    {
        switch(wpt)
        {
        case WPT_HORIZONTAL:
            mNextWidgetPos.x += w->getSize().x; break;
        case WPT_VERTICAL:
            mNextWidgetPos.y += w->getSize().y; break;
        case WPT_NONE:
        default:
            break;
        }
        adjustSizeToContent();
    }
    //------------------------------------------------------------------------------------------------
    Window *Window::addMenuWindowTab(const String &label, 
        bool titleBarWin,
        WindowPlacementType wpt)
    {
        const size_t labelVisualSize = label.size()*7;
        Window *aWindow = mGUI->createWindow(
            Vector4(mGUI->mNextMenuWindowPos.x, mGUI->mNextMenuWindowPos.y, 200, 48), 
            "bgui.window", 
            titleBarWin? WFT_RESIZE_AND_MOVE : WFT_NONE,  
            titleBarWin? label: "");

        Button *aButton = addMenuButton(aWindow, label, WPT_HORIZONTAL);

        if (wpt != WPT_NONE)
            mGUI->mNextMenuWindowPos.y += aWindow->getSize ().y + 25;
        return aWindow;
    }
    //------------------------------------------------------------------------------------------------
    MenuButton *Window::addMenuButton(Window *target, const String &label,
        WindowPlacementType wpt)
    {
        const size_t labelVisualSize = label.size()*7;
        MenuButton *b = createMenuButton(
            Vector4(mNextWidgetPos.x, mNextWidgetPos.y, labelVisualSize, 24),
            "bgui.button", label, Callback(), target);

        addWidget(b, wpt);
        return b;
    }
    //------------------------------------------------------------------------------------------------
    BoolButton *Window::addBoolButton(bool* value, const String &label,
        WindowPlacementType wpt)
    {
          const size_t labelVisualSize = label.size()*7;
          BoolButton *b = createBoolButton(
              Vector4(mNextWidgetPos.x, mNextWidgetPos.y, labelVisualSize, 24),
              "bgui.button", label, Callback(), value);
          
          addWidget(b, wpt);
          return b;
    }
    //------------------------------------------------------------------------------------------------
    RealButton *Window::addRealButton(Ogre::Real* value, 
        const Ogre::Vector4 &SliderMoves, 
        const String &label,
        WindowPlacementType wpt)
    {
        RealButton *b = createRealButton (value, SliderMoves, label, mNextWidgetPos);

        addWidget(b, wpt);
        return b;
    }
    //------------------------------------------------------------------------------------------------
    StaticText* Window::addStaticText(const String &label,
        WindowPlacementType wpt)
    {
        const size_t labelVisualSize = label.size()*7;
        StaticText* o = createStaticText(
            Vector4(mNextWidgetPos.x, mNextWidgetPos.y, labelVisualSize, 24),
            label);

        addWidget(o, wpt);
        return o;
    }
    //------------------------------------------------------------------------------------------------
	void Window::setSize(int X,int Y) 
    {
        Widget::setSize(X, Y);		
        if (mResizerButton)
		    mResizerButton->mMainOverlay->setPosition(mResizerButton->mPosX=mWidth-16,mResizerButton->mPosY=mHeight-16);
		if(mTitleBarButton)
        {
            mTitleBarButton->mMainOverlay->setWidth(mTitleBarButton->mWidth=mWidth-22);
            mCloseButton->mMainOverlay->setPosition(mCloseButton->mPosX = mWidth-22, 0);
		}
    }
    //------------------------------------------------------------------------------------------------
	Button* Window::createButton(const Vector4 &D, const String &M, const String &T, Callback C) 
    {
		Button *x = new Button(D, M, T, C, this);
        mButtons.push_back(x);
        mChildren.push_back(x);
		return x;
    }
    //------------------------------------------------------------------------------------------------
    MenuButton* Window::createMenuButton(const Vector4 &D, const String &M, const String &T, Callback C, Window *t) 
    {
        MenuButton *x = new MenuButton(D, M, T, C, this, t);
        mButtons.push_back(x);
        mChildren.push_back(x);
        return x;
    }
    //------------------------------------------------------------------------------------------------
    BoolButton* Window::createBoolButton(const Vector4 &D, const String &M, const String &T, Callback C, bool *boolValue) 
    {
        BoolButton *x = new BoolButton(D, M, T, C, this, boolValue);
        mButtons.push_back(x);
        mChildren.push_back(x);
        return x;
    }
    //------------------------------------------------------------------------------------------------
	TextInput* Window::createTextInput(const Vector4 &D, const String &M, const String &V, int L)
    {
		TextInput *x = new TextInput(D,M,V,L,this);
        mTextInput.push_back(x);
        mChildren.push_back(x);
		return x;
    }
    //------------------------------------------------------------------------------------------------
    RealButton *Window::createRealButton(Ogre::Real* value, 
        const Ogre::Vector4 &SliderMoves, 
        const String &label,
        const Ogre::Vector2 &pos)
    {

        RealButton *x = new RealButton(this, 
            value, 
            SliderMoves,
            label, 
            pos);

        mChildren.push_back(x);

        return x;
    }
    //------------------------------------------------------------------------------------------------
	bool Window::checkKey(const String & k, int px, int py) {
		
		if (!mMainOverlay->isVisible())
			return false;

		if(isOut(px, py))
            return false;
		
		if(mActiveTextInput == 0)
			return false;
		
		if(k=="!b") 
        {
			mActiveTextInput->setValue(mActiveTextInput->mValueText.substr(0,mActiveTextInput->mValueText.length()-1));
			return true;
		}

		if(mActiveTextInput->mValueText.length() >= mActiveTextInput->length)
			return true;
		
		mActiveTextInput->mCaptionOverlay->setCaption(mActiveTextInput->mValueText+=k);
		return true;
    }
    //------------------------------------------------------------------------------------------------
	bool Window::check(int px, int py, bool LMB) 
    {       
        if (mUnderEffect)
            return false;

        if (isOut(px, py))
        {
			if (mActiveButton) 
            {
                mActiveButton->over(false);
				if (mActiveButton->mCallback.mCallbackType == 2) 
                {
					mActiveButton->mCallback.mListener->onButtonPress(mActiveButton, 3);
				}
                mGUI->mActiveButton = 0;
				mActiveButton = 0;
			}
            if (mActiveTextInput)
            {
                mGUI->mActiveTextInput = 0;
                mActiveTextInput = 0;
            }

            over(false);
            return false;
		}

        bool event_consumed = false;
       // if we're inside window, local_x and local_y has to be positive
        const int local_x = px - mPosX;
        const int local_y = py - mPosY;
        for(std::vector<Button*>::iterator i=mButtons.begin();i!=mButtons.end();++i)
        {
			if ((*i)->isOut(local_x, local_y))
				continue;
		
			if (mActiveButton) 
            {
				if (mActiveButton != (*i)) 
                {
					mActiveButton->over(false);
					if (mActiveButton->mCallback.mCallbackType == 2) 
                    {
						mActiveButton->mCallback.mListener->onButtonPress(mActiveButton, 3);

                        mDragType = WA_NONE;
                        mGUI->mActiveButton = 0;
                        mActiveButton = 0;
					}
				}
			}

			
			if(mActiveTextInput && LMB) 
            {
				mActiveTextInput->mMainOverlay->setMaterialName(mActiveTextInput->mMaterialName);
                mGUI->mActiveTextInput = 0;
                mActiveTextInput=0;
			}

            mActiveButton = (*i);
            mActiveButton->over(true);
            mGUI->mActiveButton = mActiveButton;
            if (LMB)
            {
                if (mActiveButton == mTitleBarButton) 
                {
                    mDragType = WA_MOVE;
                    mGUI->mDragX = px;
                    mGUI->mDragY = py;
                    mGUI->mDragWindowX = mPosX;
                    mGUI->mDragWindowY = mPosY;
                    mActiveButton->activate(true);
                    return true;
                }
                else if (mActiveButton == mResizerButton) 
                {
                    mDragType = WA_RESIZE;
                    mGUI->mDragX = px;
                    mGUI->mDragY = py;
                    mGUI->mDragWindowX = mWidth;
                    mGUI->mDragWindowY = mHeight;
                    mActiveButton->activate(true);
                    return true;
                }
                else 
                {
                    mDragType = WA_PRESS;
                }               
            }
            else
            {
                mDragType = WA_NONE;
            }

            switch (mActiveButton->mCallback.mCallbackType) 
            {
            case 1: 
                mActiveButton->mCallback.fp(mActiveButton, LMB);
                break; 
            case 2:
                mActiveButton->mCallback.mListener->onButtonPress(mActiveButton, LMB);
                break;        
            default: 
                if (LMB) 
                    mActiveButton->activate(true);
                break; 
            }

            event_consumed = true;
		}

        if (!event_consumed)
        {
            if (mActiveButton) 
            {
                mActiveButton->over(false);
                if (mActiveButton->mCallback.mCallbackType == 2) 
                {
                    mActiveButton->mCallback.mListener->onButtonPress(mActiveButton, 3);

                    mDragType = WA_NONE;
                    mGUI->mActiveButton = 0;
                    mActiveButton = 0;
                }
            }

        
            for(std::vector<TextInput*>::iterator i=mTextInput.begin();i!=mTextInput.end();++i)
            {    	
		        if ((*i)->isOut(local_x, local_y))
			        continue;

                mGUI->mActiveTextInput = (*i);
		        mActiveTextInput = (*i);
		        mActiveTextInput->mMainOverlay->setMaterialName(mActiveTextInput->mMaterialName + ".over");
		        
                event_consumed = true;
	        }
        }

	    if (!event_consumed && mActiveTextInput) 
        {
		    mActiveTextInput->mMainOverlay->setMaterialName(mActiveTextInput->mMaterialName);
            mActiveTextInput=0;
            mGUI->mActiveTextInput = 0;
        }        

        over(true);
		return event_consumed;
    }
    //------------------------------------------------------------------------------------------------
    StaticText* Window::createStaticText(const Vector4 &D, const String & T) 
    {
        StaticText *x = new StaticText(D, T, this); 
        mChildren.push_back(x);
        return x;
    }
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    Button::Button(const Vector4 &Dimensions, const String & m, const String &Text, Callback cb, Window *parent)
		: 
     Widget (Dimensions, m)
	{
		Ogre::ResourcePtr ma=Ogre::MaterialManager::getSingleton().getByName(mMaterialName + ".active");
		
		mMainOverlay = parent->mGUI->createOverlay(parent->mMainOverlay->getName() + "b" + StringConverter::toString(parent->mGUI->mButtonCount++), 
            Vector2(mPosX, mPosY),
            Vector2(mWidth, mHeight),
            m,
            "");
		mCaptionOverlay = parent->mGUI->createOverlay(mMainOverlay->getName() + "c" + StringConverter::toString(parent->mGUI->mButtonCountTextArea++),
                                            Vector2(4,(mHeight - parent->mGUI->mFontSize) / 2),
                                            Vector2(mWidth, mHeight),
                                            "",
                                            Text);

        if (mCaptionOverlay->getParent () != mMainOverlay)
            mMainOverlay->addChild(mCaptionOverlay);

        if (mMainOverlay->getParent () != parent->mMainOverlay)
            parent->mMainOverlay->addChild(mMainOverlay);

        mCaptionOverlay->show ();
        mMainOverlay->show ();
        mCallback = cb;
     }
     //------------------------------------------------------------------------------------------------
     //------------------------------------------------------------------------------------------------
     //------------------------------------------------------------------------------------------------
     void MenuButton::activate(const bool a) 
     {       
         if (mTarget->getUnderEffect())
             return;

         Widget::activate (a);

         GUI * const g = mTarget->getGUI();
         const Ogre::Real t = g->getUpTime ();
         if (mTarget->isVisible ())
             g->addEffect(new AlphaEffect(mTarget, 0.5, 1, 0, 0));
         else
             g->addEffect(new AlphaEffect(mTarget, 0.5, 0, 1, 0));
     }
     //------------------------------------------------------------------------------------------------
     //------------------------------------------------------------------------------------------------
     //------------------------------------------------------------------------------------------------
     void BoolButton::activate(const bool a) 
     {      
         Widget::activate (a);
         *mBoolValue = !*mBoolValue;
     }
     //------------------------------------------------------------------------------------------------
     //------------------------------------------------------------------------------------------------
     //------------------------------------------------------------------------------------------------
     TextInput::TextInput(const Vector4 &D, const String & M, const String & V, unsigned int L, Window *P)
		: Widget (D, M), mValueText(V), length(L) 
	{
		ResourcePtr ma=Ogre::MaterialManager::getSingleton().getByName(mMaterialName);

        mMainOverlay = P->mGUI->createOverlay(
            P->mMainOverlay->getName() + "t" + StringConverter::toString(P->mGUI->mTextCaptionCount++),
            Vector2(mPosX, mPosY),
            Vector2(mWidth, mHeight),
            M,"");
		mCaptionOverlay = P->mGUI->createOverlay(
            mMainOverlay->getName() + "c" + StringConverter::toString(P->mGUI->mTextCaptionCountArea++),
            Vector2(4, (mHeight - P->mGUI->mFontSize) / 2),
            Vector2(mWidth, mHeight),"",V);

        if (mMainOverlay->getParent () != P->mMainOverlay)
            P->mMainOverlay->addChild(mMainOverlay);
		mMainOverlay->show();

        if (mCaptionOverlay->getParent () != mMainOverlay)
            mMainOverlay->addChild(mCaptionOverlay);
		mCaptionOverlay->show();
    }
     //------------------------------------------------------------------------------------------------
     //------------------------------------------------------------------------------------------------
     //------------------------------------------------------------------------------------------------
     StaticText::StaticText(const Vector4 &D, const String & V, Window *P)
        : 
            Widget (D, ""), 
          mParent(P),
          mValueText(V)
    {        

        mMainOverlay = P->mGUI->createOverlay(
            P->mMainOverlay->getName() + "st" + StringConverter::toString(P->mGUI->mTextCaptionCount++),
            Vector2(mPosX, mPosY),
            Vector2(mWidth, mHeight),"","");
        mCaptionOverlay = P->mGUI->createOverlay(
            mMainOverlay->getName() + "c" + StringConverter::toString(P->mGUI->mTextCaptionCountArea++),
            Vector2(4, (mHeight - P->mGUI->mFontSize) / 2),
            Vector2(mWidth, mHeight),
            "",V);

        if (mMainOverlay->getParent () != P->mMainOverlay)
            P->mMainOverlay->addChild(mMainOverlay);
        mMainOverlay->show();

        if (mCaptionOverlay->getParent () != mMainOverlay)
            mMainOverlay->addChild(mCaptionOverlay);
        mCaptionOverlay->show();
    }
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    RealButton::RealButton(
        Window*            window, 
        Real*              value, 
        const Vector4 &    SliderMoves,
        const String  &    label, 
        const Vector2 &    widgetPos) :
        Widget(Vector4 (widgetPos.x, widgetPos.y, 0, 0), ""),
        mValue           (value),
        mValueText (Ogre::StringConverter::toString (*value)),
        mLowSlideUnit    (SliderMoves.x),
        mFastSlideUnit   (SliderMoves.y),
        mMinValue        (SliderMoves.z),
        mMaxValue        (SliderMoves.w)
      {
        const Real charheight =  24.0;
        const Real charlength =  7.0;
        const Real labelLength =  charlength * label.size();
        const Real inputLength =  charlength * 5;

        Vector2 pos (widgetPos);

        mPosX = pos.x; 
        mPosY = pos.y;
        mWidth = labelLength           // value label.
            + inputLength    // input text value.
            + charlength + 1 // 2 buttons with single char to change value.
            + 2 * charlength + 2 // 2 buttons with 2 char to change value.
            + 12; // each item is has 1 inter space.
        mHeight = charheight;

        Vector4 itemDimension (pos.x, pos.y, labelLength, mHeight);

        window->createStaticText(itemDimension, label);

        pos.x += labelLength + 1; 
        itemDimension.x = pos.x;
        itemDimension.z = charlength*2 + 2;
        mFastRewind    = window->createButton(itemDimension,  "bgui.button", "<=", Callback(this));

        pos.x += charlength*2 + 4;
        itemDimension.x = pos.x;
        itemDimension.z = charlength + 1;
        mRewind        = window->createButton(itemDimension, "bgui.button", "-",  Callback(this));

        pos.x += charlength + 2;
        itemDimension.x = pos.x;
        itemDimension.z = inputLength;
        mtextValueInput             = window->createTextInput(itemDimension, 
            "bgui.textinput", 
            StringConverter::toString (*value), 5);

        pos.x += inputLength + 1;
        itemDimension.x = pos.x;
        itemDimension.z = charlength + 1;
        mForward       = window->createButton(itemDimension, "bgui.button", "+",  Callback(this));

        pos.x += charlength*2 + 2;
        itemDimension.x = pos.x;
        itemDimension.z = charlength*2 + 2;
        mFastForward   = window->createButton(itemDimension, "bgui.button", "=>", Callback(this));

        pos.x += charlength*2 + 2;

        mWidth = pos.x;
        mHeight = pos.y;
    } 
    //------------------------------------------------------------------------------------------------
    void RealButton::setValue(const Ogre::Real v) 
    {
        *mValue = std::min(mMaxValue, std::max(v, mMinValue)); 
        mValueText = Ogre::StringConverter::toString (v); 
        mtextValueInput->setValue(mValueText);
    }
    //------------------------------------------------------------------------------------------------
    void RealButton::onButtonPress(Button *ref, Ogre::uchar type)
    {
        if(type == 1) // button down
        {
            if(ref == mForward)
            {
                setValue(getValue () + mLowSlideUnit);
            }
            else if(ref == mFastForward)
            {
                setValue(getValue () + mFastSlideUnit);
            }
            else if(ref == mRewind)
            {
                setValue(getValue () - mLowSlideUnit);
            }
            else if(ref == mFastRewind)
            {
                setValue(getValue () - mFastSlideUnit);
            }
        }
    }
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    bool Effect::update(Ogre::Real timeElapsed)
    {
        mCurrTime += timeElapsed;
        if (mCurrTime >= mStartTime)
        {
            const bool finished = getTimeOrIsFinished();

            if (finished)
            {
                updateValue(Ogre::Real(1.0));
            }
            else
            {
                mWidget->setUnderEffect(true);
                updateValue(getTimeFactor());
            }
            return finished;
        }
        // not yet started.
        return false;
    }
    //------------------------------------------------------------------------------------------------
    Ogre::Real Effect::getTimeFactor() 
    {          
        return (mCurrTime - mStartTime) / mDuration;
    }
    //------------------------------------------------------------------------------------------------
    bool Effect::getTimeOrIsFinished()
    {
        if (mCurrTime - mStartTime > mDuration)
        {
            if (!mRepeat)
            {
               mCurrTime = mStartTime + mDuration;
               return true;
            }
            while (mCurrTime - mStartTime > mDuration)
                mCurrTime -= mDuration;
        }
        return false;
    }
    //------------------------------------------------------------------------------------------------
    Ogre::Real Effect::interpolate(const Ogre::Real start, 
        const Ogre::Real end, 
        const Ogre::Real timeFactor) const
    {
        Ogre::Real factor;
        switch(mType)
        {
        case EFFECT_SIN:
            factor = Math::Sin(Radian(timeFactor * Math::TWO_PI));
            break;
        case EFFECT_LINEARX4:
            factor = timeFactor * timeFactor * timeFactor * timeFactor;
            break;
        case EFFECT_LINEARX2:
            factor = timeFactor * timeFactor;
            break;
        case EFFECT_LINEAR:
        default:
            factor = timeFactor;
            break;
        }
        return (factor*end + (1 - factor)*start);
    }
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    void AlphaEffect::updateValue(const Ogre::Real factor)
    {
        mWidget->setAlpha(interpolate(mStartAlpha, mEndAlpha, factor), true);
    }
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    void SizeEffect::updateValue(const Ogre::Real factor)
    {
        mWidget->setSize(
            Vector2(interpolate(mStartSize.x, mEndSize.x, factor),
                    interpolate(mStartSize.y, mEndSize.y, factor))
            );
    }
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    void MoveEffect::updateValue(const Ogre::Real factor)
    {
        mWidget->setPosition(
             Vector2(interpolate(mStartPosition.x, mEndPosition.x, factor),
                     interpolate(mStartPosition.y, mEndPosition.y, factor))
            );
    }
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    void ActivateEffect::updateValue(const Ogre::Real factor)
    {
        mWidget->setMaterialBlendFactor(interpolate (0, 1, factor), true);
    } 
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    void OverEffect::updateValue(const Ogre::Real factor)
    {
        mWidget->setMaterialBlendFactor(interpolate (0, 1, factor), true);
    }
     //------------------------------------------------------------------------------------------------

} // End of Betajaen's GUI. Normal programming can resume now.
