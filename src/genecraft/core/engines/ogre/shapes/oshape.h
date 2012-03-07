#ifndef OSHAPE_H
#define OSHAPE_H

#include "genecraftcoreclasses.h"
#include "base/node.h"
#include "base/link.h"
#include "bullet/btshapesfactory.h"

namespace GeneCraftCore {
    class oShape : public Node
    {
    public:
        oShape();

        virtual Position getPosition() 				{ return p;}
        virtual void     setPosition(Position p) 	{ this->p = p; }
        virtual void	 setSelected(bool selected) {}
        virtual bool	 isSelected() 				{ return false; }
        virtual void 	 setup()  					{}
        virtual void	 remove() 					{}
    protected:
        Position p;

    protected:
        Link*             physicalLink;
        btShapesFactory* physicalFactory;
    };
}
#endif // OSHAPE_H
