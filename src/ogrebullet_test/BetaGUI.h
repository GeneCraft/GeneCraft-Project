#ifndef BETAGUI
#define BETAGUI

/// Betajaen's GUI 016 Uncompressed
/// Written by Robin "Betajaen" Southern 07-Nov-2006, http://www.ogre3d.org/wiki/index.php/BetaGUI
/// This code is under the Whatevar! licence. Do what you want; but keep the original copyright header.

#include "Ogre.h"

namespace BetaGUI 
{
    //------------------------------------------------------------------------------------------------
    class GUI;

    class Widget;
    class Window;

    class Button;
    class BoolButton;
    class MenuButton;
    class RealButton;

    class StaticText;
    class TextInput;

    class Callback;

    class Effect;
    class AlphaEffect;
    class MoveEffect;
    class SizeEffect;

    //------------------------------------------------------------------------------------------------
	enum WindowFeatureType 
    { 
		WFT_NONE                =   0,
		WFT_MOVE           ,
		WFT_RESIZE         ,
		WFT_RESIZE_AND_MOVE
    };
    //------------------------------------------------------------------------------------------------
     enum WindowPlacementType 
     { 
         WPT_NONE       =   0,
         WPT_VERTICAL   ,
         WPT_HORIZONTAL 
     };
    //------------------------------------------------------------------------------------------------
    enum WindowActivity 
    {
        WA_NONE   =   0,
        WA_MOVE   ,
        WA_RESIZE ,
        WA_PRESS  
    };
    //------------------------------------------------------------------------------------------------
	class GUI 
    {
		public:

			friend class Window;

            friend class Button;

            friend class MenuButton;
            friend class BoolButton;
            friend class RealButton;

            friend class StaticText;
			friend class TextInput;

            GUI(const Ogre::String &baseOverlay, const Ogre::String &font, int fontSize, Ogre::RenderWindow *win);

			~GUI();

            void sortZOrder() ;

            void setZRangeOrder(int nearZ, int FarZ);

			bool injectMouse(int x, int y, bool LMB);

			bool injectKey(const Ogre::String &key, int x, int y);

			void injectBackspace(int x, int y);

            Window*	 createWindow(
                const Ogre::Vector4 &Dimensions, 
                const Ogre::String &Material, 
                WindowFeatureType type, 
                const Ogre::String &caption = "");

			void destroyWindow(Window *window) {
                mNextWindowToDestroy=window;
            }
            Ogre::OverlayContainer* createOverlay(const Ogre::String &name, 
                const Ogre::Vector2 &position,
                const Ogre::Vector2 &dimensions, 
                const Ogre::String &material = "", 
                const Ogre::String &caption = "");

			Ogre::OverlayContainer* createMousePointer(Ogre::Vector2 dimensions, 
                const Ogre::String &material);
				
 

            Window *addMenuWindow(const Ogre::Vector2 dimensions);
           
            void update(Ogre::Real timeElapsed);
            void addEffect (Effect* e);
            Ogre::Real getUpTime() const {return mUpTime;}

	protected:
            //Ogre::Overlay*          mGuiOverlay;					// Main sheet overlay
            std::vector<Window*>    mWindows;					    // Windows
			Window *                mNextWindowToDestroy;			// Window to destroy
			Ogre::OverlayContainer* mMousePointerOverlay;			// Mouse Pointer Overlay

			Ogre::String mFont;
			int mFontSize;
			int mWindowCount, mButtonCount, mTextCaptionCount, mTextCaptionCountArea, mButtonCountTextArea;


            Ogre::uint  mDragWindowAction; 

            int         mDragX, mDragY; 
            int         mDragWindowX, mDragWindowY;

            Window *    mActiveDraggedWindow; 
            TextInput * mActiveTextInput; 
            Button *    mActiveButton; 

            Ogre::Vector2           mNextMenuWindowPos;
            Window *                mMenuWindow;
            Ogre::RenderWindow *    mRenderWindow;

            std::list<Effect*> mActiveEffects;

            Ogre::Real mUpTime;
            Ogre::String mName;
            int mFarZ;
            int mNearZ;
    };
    //------------------------------------------------------------------------------------------------
    class Widget 
    {
    public:

        friend class GUI;

        Widget(const Ogre::Vector4 &Dimension, 
            const Ogre::String &materialNameNormal,
            bool hasOverState = true,
            bool hasActiveState = true);
        
        virtual ~Widget();
        
        Ogre::Vector2 getPosition()  const{return Ogre::Vector2(mPosX,mPosY);}
        Ogre::Vector2 getSize()   const {return Ogre::Vector2(mWidth,mHeight); }
      
        void setPosition(const Ogre::Vector2 &position);
        void setSize(const Ogre::Vector2 &size);

        virtual void show(){setAlpha (1.0, true);}; 
        virtual void hide(){setAlpha (0.0, true);}; 

        virtual bool isVisible() {return mMainOverlay->isVisible ();};    

        virtual void over(const bool a);
        virtual void activate(const bool a);

        virtual void adjustSizeToContent();

        virtual void setPosition(int X,int Y);
        virtual void setSize(int X,int Y);
        virtual void setAlpha(const Ogre::Real alpha, const bool isContainer);
        virtual void setMaterialBlendFactor(const Ogre::Real blendFactor, const bool isContainer);

        // mUnderEffect getter
        bool getUnderEffect() const { return mUnderEffect; }
        // mUnderEffect setter
        void setUnderEffect(bool val);

        // mOver getter
        bool getOver() const { return mOver; }
        // mOver setter
        void setOver(bool val) { mOver = val; }
        // mActive getter
        bool getActive() const { return mActive; }
        // mActive setter
        void setActive(bool val) { mActive = val; }
        
        // mActive setter
        void setMaterial(Ogre::MaterialPtr mat);


    protected:
        //------------------------------------------------------------------------------------------------
        inline bool isOut (const int x, const int y) const 
        {
            return (x < mPosX) || (y < mPosY) 
                || (x > (mPosX + mWidth)) || 
                (y > (mPosY + mHeight));
        }
        //------------------------------------------------------------------------------------------------
        inline bool isIn (const int x, const int y) const 
        {
            return (x >= mPosX) && (y >= mPosY) 
                && (x <= (mPosX + mWidth)) && 
                (y <= (mPosY + mHeight));
        }

        void instantiateMaterial(Ogre::OverlayContainer * const oc, bool reset) const;
        void setOverlayAlpha(Ogre::OverlayContainer * const oc, const Ogre::Real alpha) const;
        void setOverlayMaterialBlendFactor(Ogre::OverlayContainer * const oc, const Ogre::Real blendFactor) const;

        int mPosX, mPosY, mWidth, mHeight;

        std::vector<Widget *> mChildren;
        Ogre::OverlayContainer* mMainOverlay;
        Ogre::OverlayContainer* mCaptionOverlay;			
        Ogre::String mMaterialName;						

        bool mHasMaterial;
        bool mHasOverState;
        bool mHasActiveState;
        bool mUnderEffect;
        bool mOver;
        bool mActive;
    };
    //------------------------------------------------------------------------------------------------
    class Window : public Widget
    {
		public:
			friend class Button;
            friend class TextInput;
            friend class StaticText;
			friend class GUI;

            Window(const Ogre::Vector4 &Dimensions, const Ogre::String &Material, WindowFeatureType type, const Ogre::String &caption, GUI *gui);
            virtual ~Window();

			Button*		createButton(const Ogre::Vector4 &Dimensions, const Ogre::String &Material, 
                const Ogre::String &Text, Callback callback);

			TextInput*	createTextInput(const Ogre::Vector4 &Dimensions, const Ogre::String &Material, 
                const Ogre::String & Value, int length);

			StaticText* createStaticText(const Ogre::Vector4 &Dimensions, const Ogre::String &Text);
		
			void setSize(int X,int Y);

            MenuButton *addMenuButton(Window *target, const Ogre::String &label, WindowPlacementType wpt = WPT_NONE);
            BoolButton *addBoolButton(bool* value, const Ogre::String &label, WindowPlacementType wpt = WPT_NONE);
            RealButton *addRealButton(Ogre::Real* value, const Ogre::Vector4 &SliderMoves, const Ogre::String &label, WindowPlacementType wpt = WPT_NONE);
            StaticText* addStaticText(const Ogre::String &label, WindowPlacementType wpt = WPT_NONE);

            Window *addMenuWindowTab(const Ogre::String &label,  
                bool titleBarWin = true, 
                WindowPlacementType wpt = WPT_VERTICAL);

            MenuButton* createMenuButton(const Ogre::Vector4 &D, const Ogre::String &M, const Ogre::String &T, Callback C, Window *t);
            BoolButton* createBoolButton(const Ogre::Vector4 &D, const Ogre::String &M, const Ogre::String &T, Callback C, bool *boolValue);
            
            RealButton *createRealButton(Ogre::Real* value, 
                const Ogre::Vector4 &SliderMoves, 
                const Ogre::String &label,
                const Ogre::Vector2 &pos);

            GUI* getGUI() const {return mGUI;}

            void setZOrder(int zOrder){mGuiOverlay->setZOrder (zOrder);}
		protected:

			
			bool check(int x, int y, bool LMB); 
            bool checkKey(const Ogre::String &key, int x, int y);

			TextInput* mActiveTextInput;				// Active TextInput

            Button 
                *mCloseButton,
                *mResizerButton,
                *mActiveButton,
                *mTitleBarButton;			// Resizer, ActiveButton, Title bar			

			GUI *mGUI;						// mGUI pointer
			
            std::vector<Button*> mButtons;	// Buttons
            std::vector<TextInput*> mTextInput;	// TextInputs

            Ogre::Overlay *mGuiOverlay;

            void addWidget(const Widget * const w, WindowPlacementType wpt);
            Ogre::Vector2 mNextWidgetPos;
            WindowActivity mDragType;  

    };
    //------------------------------------------------------------------------------------------------
	class BetaGUIListener 
    {
		public:
			virtual void onButtonPress(Button*, unsigned char) = 0;
    };
    //------------------------------------------------------------------------------------------------
	class Callback 
    {
		public:
			friend class Window;
			friend class Button;
			
			Callback() {
				mCallbackType=0;
			}
			
			Callback( void(*functionPointer)(BetaGUI::Button*, bool) ) {
				mCallbackType=1;
				fp = functionPointer;
			}

			Callback(BetaGUIListener *l){
				mCallbackType = 2;
				mListener = l;
			}
		protected:
			unsigned char mCallbackType;					// Type of callback: 0 - None, 1 - FunctionPointer 2 - GUIListener, 3 - Move Window, 4 - Resize
			void(*fp)(BetaGUI::Button*, bool);	// Function pointer (if 1)
			BetaGUIListener *mListener;		// GuiListener (if 2)
    };
    //------------------------------------------------------------------------------------------------
    class Button : public Widget
    {
		public:
            friend class Window;
            friend class GUI;
		
			Button(const Ogre::Vector4 &Dimensions, const Ogre::String &Material, 
                const Ogre::String &Text, Callback callback, Window *parent);			
            virtual ~Button() {}

		protected:
			Callback mCallback;			// Callback to use
    };
    //------------------------------------------------------------------------------------------------
    class MenuButton : public Button
    {
    public:
        MenuButton(const Ogre::Vector4 &Dimensions, const Ogre::String &Material, 
                    const Ogre::String &Text, Callback callback, Window *parent, 
                    Window *target) :
            Button(Dimensions, Material, Text, callback, parent),
            mTarget(target)
            {};
            virtual ~MenuButton(){};
    protected:
        void activate(const bool a) ;

        Window *mTarget;
    };
    //------------------------------------------------------------------------------------------------
    class BoolButton : public Button
    {
    public:
        BoolButton(const Ogre::Vector4 &Dimensions, const Ogre::String &Material, 
            const Ogre::String &Text, Callback callback, Window *parent, bool *boolValue):
            Button(Dimensions, Material, Text, callback, parent),
            mBoolValue(boolValue)
            {}
        virtual ~BoolButton(){};

    protected:
        void activate(const bool a) ;

        bool *mBoolValue;
    };
    //------------------------------------------------------------------------------------------------
    class TextInput : public Widget
    {
		public:
            friend class Window;
            friend class GUI;
			
			TextInput(const Ogre::Vector4 &Dimensions, const Ogre::String &Material, 
                        const Ogre::String &Value, unsigned int length, Window *parent);
			virtual ~TextInput(){}
            const Ogre::String &getValue() const {return mValueText;}			
			void setValue(const Ogre::String &v) {mCaptionOverlay->setCaption(mValueText = v);}

		protected:
            unsigned int length;
			Ogre::String mValueText;// MaterialName Normal, MaterialName Active
			
    };
    //------------------------------------------------------------------------------------------------
    class StaticText : public Widget
    {
    public:
        friend class Window;

        StaticText(const Ogre::Vector4 &Dimensions,
            const Ogre::String &Value,  
            Window *parent);
        virtual ~StaticText(){}

        const Ogre::String &getValue() const 
        {return mValueText;}

        void setValue(const Ogre::String &v) 
        {
            mCaptionOverlay->setCaption(mValueText = v);
            mWidth = static_cast<int> (mValueText.size () * 7);
            mParent->adjustSizeToContent ();
        }

    protected:

        int            length;
        Ogre::String   mValueText;
        Window         *mParent;
    };
    //------------------------------------------------------------------------------------------------
    class RealButton : public BetaGUIListener, public Widget
    {
        public:
            friend class Window;

            RealButton(BetaGUI::Window *window, 
                Ogre::Real* value, 
                const Ogre::Vector4 &SliderMoves,
                const Ogre::String &label, 
                const Ogre::Vector2 &pos);

            virtual ~RealButton(){};

            Ogre::Real getValue() const {return *mValue;}

            void setValue(const Ogre::Real v);

            void onButtonPress(BetaGUI::Button *ref, Ogre::uchar type);
        protected:

            int        length;

            BetaGUI::TextInput *mtextValueInput;
            BetaGUI::Button    *mForward, *mFastForward, *mRewind, *mFastRewind;

            Ogre::Real      *mValue;
            Ogre::String    mValueText;
         
            Ogre::Real     mLowSlideUnit;    
            Ogre::Real     mFastSlideUnit;   
            Ogre::Real     mMinValue;       
            Ogre::Real     mMaxValue; 

    };
    //------------------------------------------------------------------------------------------------
    class Effect
    {
    public:
        enum EffectInterpolatorType
        {
            EFFECT_LINEAR = 0,
            EFFECT_LINEARX2,
            EFFECT_LINEARX4,
            EFFECT_SIN
        };
    public:
        Effect(Widget * const widget, const Ogre::Real duration, 
            const Ogre::Real startTime, const Ogre::Real currTime = 0, const bool repeat = false,
            EffectInterpolatorType type = EFFECT_LINEARX4) : 
            mWidget(widget), 
            mStartTime(startTime), 
            mDuration(duration), 
            mRepeat(repeat),
            mCurrTime(currTime),
            mType(type)
        {
            assert (duration != 0);
        }
        virtual ~Effect(){};

        virtual void updateValue(const Ogre::Real factor) = 0;

        bool update(Ogre::Real timeElapsed);
        Ogre::Real getTimeFactor() ;
        bool getTimeOrIsFinished();
        Ogre::Real linearInterpolate(const Ogre::Real start, 
            const Ogre::Real end, 
            const Ogre::Real timeFactor) const;
        Ogre::Real interpolate(const Ogre::Real start, 
            const Ogre::Real end, 
            const Ogre::Real timeFactor) const;

    protected:
        Widget * const mWidget;
        const Ogre::Real mStartTime; 
        const Ogre::Real mDuration;
        const bool mRepeat;

        Ogre::Real mCurrTime;
        const EffectInterpolatorType mType;
    };
    //------------------------------------------------------------------------------------------------
    class AlphaEffect : public Effect
    {
    public:

        AlphaEffect(Widget * const widget, 
            const Ogre::Real duration, 
            const Ogre::Real startAlpha,
            const Ogre::Real endAlpha,
            const Ogre::Real startTime, 
            const Ogre::Real currTime = 0, 
            const bool repeat = false,
            EffectInterpolatorType type = EFFECT_LINEARX4) : 
        Effect(widget, duration, startTime,  currTime, repeat), 
            mStartAlpha(startAlpha), 
            mEndAlpha(endAlpha)
        {
            assert(mStartAlpha >= 0.0 && mStartAlpha <= 1.0);
            assert(mEndAlpha >= 0.0 && mEndAlpha <= 1.0);
        }
        virtual ~AlphaEffect(){};

        void updateValue(const Ogre::Real factor);
    private:
        const Ogre::Real mStartAlpha;
        const Ogre::Real mEndAlpha;
    };
    //------------------------------------------------------------------------------------------------
    class MoveEffect : public Effect
    {
    public:
        MoveEffect(Widget * const widget, 
            const Ogre::Real duration, 
            const Ogre::Vector2 &startPosition,
            const Ogre::Vector2 &endPosition,
            const Ogre::Real startTime, 
            const Ogre::Real currTime = 0, 
            const bool repeat = false,
            EffectInterpolatorType type = EFFECT_LINEARX4) : 
        Effect(widget, duration, startTime,  currTime, repeat), 
            mStartPosition(startPosition), 
            mEndPosition(endPosition)
        {}
        virtual ~MoveEffect(){};
        void updateValue(const Ogre::Real factor);

    private:
        const Ogre::Vector2 mStartPosition;
        const Ogre::Vector2 mEndPosition;
    };
    //------------------------------------------------------------------------------------------------
    class SizeEffect : public Effect
    {
    public:
        SizeEffect(Widget * const widget, 
            const Ogre::Real duration, 
            const Ogre::Vector2 &startSize,
            const Ogre::Vector2 &endSize,
            const Ogre::Real startTime, 
            const Ogre::Real currTime = 0, 
            const bool repeat = false,
            EffectInterpolatorType type = EFFECT_LINEARX4) : 
        Effect(widget, duration, startTime, currTime, repeat), 
            mStartSize(startSize), 
            mEndSize(endSize)
        {}
        virtual ~SizeEffect(){};
        void updateValue(const Ogre::Real factor);

    private:
        const Ogre::Vector2 mStartSize;
        const Ogre::Vector2 mEndSize;
    };
    //------------------------------------------------------------------------------------------------
    class ActivateEffect : public Effect
    {
    public:
        ActivateEffect(Widget * const widget, 
            const Ogre::Real duration, 
            const Ogre::Real startTime, 
            const Ogre::Real currTime = 0, 
            const bool repeat = false,
            EffectInterpolatorType type = EFFECT_LINEARX4): 
        Effect(widget, duration, startTime, currTime, repeat)
        {};
        virtual ~ActivateEffect(){};
        void updateValue(const Ogre::Real factor);

    };
    //------------------------------------------------------------------------------------------------
    class OverEffect : public Effect
    {
    public:
        OverEffect(Widget * const widget, 
            const Ogre::Real duration, 
            const Ogre::Real startTime, 
            const Ogre::Real currTime = 0, 
            const bool repeat = false,
            EffectInterpolatorType type = EFFECT_LINEARX4): 
        Effect(widget, duration, startTime, currTime, repeat)
        {};
        virtual ~OverEffect(){};
        void updateValue(const Ogre::Real factor);

    };
    //------------------------------------------------------------------------------------------------


} // End of Namespace
#endif

