#include "node.h"


namespace GeneCraftCore {


    Position Linked::getPosition() {
        return this->position;
    }

    void Linked::setPosition(Position p){
        this->position = p;
    }

    void Linked::setSelected(bool selected){
        this->selected = selected;
    }

    bool Linked::isSelected() {
        return this->selected;
    }
}

