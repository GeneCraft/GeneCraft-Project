#ifndef NODE_H
#define NODE_H

#include "genecraftcoreclasses.h"
#include <QList>
#include "node.h"
#include "LinearMath/btTransform.h"
#include <QDebug>

class btTransform;

namespace GeneCraftCore {

    typedef btTransform Position;

    class Linked {
        public:
            virtual Position getPosition() 				;
            virtual void     setPosition(Position p) 	;
            virtual void	 setSelected(bool selected) ;
            virtual bool	 isSelected() 				;
        protected:
            Position position;
            bool     selected;
    };

    template <class T> class Node : public Linked
    {
    public:
        Node(btWorld* world);

        virtual void 	 setup()  					;
        virtual void	 remove() 					;

        void addComposite(T composite);
        void removeComposite(T composite);
        void setDelegate(T delegate);
    protected:
        btWorld* world;
        QList<T> composites;
        T        delegate;
    };


    template <class T> Node<T>::Node(btWorld* world) :  world(world), delegate(NULL) {
    }

    template <class T> void     Node<T>::setup() {
        qDebug() << "setup an abstract node!";
    }

    template <class T> void     Node<T>::remove() {
        qDebug() << "remove an abstract node!";
    }


    template <class T>  void    Node<T>::addComposite(T composite) {
        this->composites.append(composite);
    }

    template <class T>  void    Node<T>::removeComposite(T composite) {
        this->composites.removeAll(composite);
    }

    template <class T>  void    Node<T>::setDelegate(T delegate) {
        this->delegate = delegate;
    }
}
#endif // NODE_H
