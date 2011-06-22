#include "btoworld.h"

#include "mainfactory.h"
#include "bulletogre/bulletogreengine.h"
#include "Ogre.h"
#include "OgreMeshManager.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"

#include "ogre/ogreengine.h"

#include <QDebug>
#include <QVariant>
#include <QVariantMap>

namespace GeneLabCore {

    btoWorld::btoWorld(MainFactory* factory, QVariant data, QObject *parent) :
        btWorld(factory, data)
    {
        btoEngine = static_cast<BulletOgreEngine*>(factory->getEngines().find("BulletOgre").value());

    }

    void btoWorld::setup(){
         btWorld::setup();

         Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
         Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelName"));
             panel->setMetricsMode(Ogre::GMM_PIXELS);
             panel->setPosition(10, 10);
             panel->setDimensions(100, 100);

             Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(
             overlayManager.createOverlayElement("TextArea", "worldName"));
             textArea->setMetricsMode(Ogre::GMM_PIXELS);
             textArea->setPosition(10, 10);
             textArea->setDimensions(100, 200);
             textArea->setFontName("StarWars");
             textArea->setCaption(this->data["name"].toString().toStdString());
             textArea->setCharHeight(16);
             textArea->setColourBottom(Ogre::ColourValue(1, 1, 1));
             textArea->setColourTop(Ogre::ColourValue(1, 1, 1));

             Ogre::TextAreaOverlayElement* textArea2 = static_cast<Ogre::TextAreaOverlayElement*>(
             overlayManager.createOverlayElement("TextArea", "timeArea"));
             textArea2->setMetricsMode(Ogre::GMM_PIXELS);
             textArea2->setPosition(10, 30);
             textArea2->setDimensions(100, 200);
             textArea2->setFontName("StarWars");
             textArea2->setCaption("0min 0sec");
             textArea2->setCharHeight(16);
             textArea2->setColourBottom(Ogre::ColourValue(1, 1, 1));
             textArea2->setColourTop(Ogre::ColourValue(1, 1, 1));

             Ogre::Overlay* overlay = overlayManager.create("OverlayName");
             overlay->add2D(panel);
             panel->addChild(textArea);
             panel->addChild(textArea2);
             overlay->show();
    }

}
