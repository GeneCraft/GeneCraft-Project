#include "brain.h"
#include "brainpluggrid.h"
#include "tools.h"
#include "qmath.h"
#include <QDebug>

namespace GeneCraftCore {
    Brain::Brain(QObject *parent) :
        QObject(parent)
    {
        // BRAIN MODIF TRY
        this->plugGrid = new BrainPlugGrid();
        this->frequency = qrand()%60 + 1;
    }

    Brain::Brain(QVariant data) {
        this->plugGrid = new BrainPlugGrid();
        this->frequency = data.toMap()["frequency"].toInt();
        if(frequency <= 0) {
            frequency = 1;
        }
        if(frequency > 60) {
            frequency = 60; // 10 per sec
        }
    }

    QVariant Brain::serialize() {
        QVariantMap data;
        data.insert("frequency", this->frequency);
        return data;
    }

    /*int Brain::randomPlugGridSize()
    {
        return pow(2,Tools::random(1,6));
    }*/
}
