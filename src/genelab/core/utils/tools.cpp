#include "tools.h"
#include <ctime>
#include <cstdlib>

namespace GeneLabCore {

    Tools::Tools() {
        qsrand((unsigned int)time(NULL));
    }

    int Tools::random(int min, int max) {
        //return (int)((max - min) * qrand()/(float) RAND_MAX + min);
        //return min+int((max-min)*(float)qrand()/(RAND_MAX));
        return min + (qrand() % (int)(max - min + 1));
    }

    float Tools::random(float min, float max) {
        return ((max - min) * ((float) qrand()/RAND_MAX)) + min;
    }

    double Tools::random(double min, double max) {
        return ((max - min) * ((double) qrand()/RAND_MAX)) + min;
    }

    // Used to clear a recurcively QTreeWidgetItem
    void Tools::clearTreeWidgetItem(QTreeWidgetItem * item)
    {
        QTreeWidgetItem * child;
        while(item->childCount()) {
            child = item->child(0);
            Tools::clearTreeWidgetItem(child);
            item->removeChild(child);
            delete child;
        }
    }

    // Used to clear a QTreeWidget
    void Tools::clearTreeWidget(QTreeWidget * tree)
    {
        QTreeWidgetItem * topItem;
        while(tree->topLevelItemCount()) {

            topItem = tree->topLevelItem(0);

            Tools::clearTreeWidgetItem(topItem);
            tree->removeItemWidget(topItem,0);

            delete topItem;
        }
    }

}
