#ifndef TOOLS_H
#define TOOLS_H

#include <QTreeWidgetItem>
#include "LinearMath/btScalar.h"

namespace GeneLabCore {

class Tools
{
public:
    Tools();

    static int random(int min, int max);
    static btScalar random(btScalar min, btScalar max);
    static double random(double min, double max);

    static void clearTreeWidgetItem(QTreeWidgetItem * item);

    // Used to clear a QTreeWidget
    static void clearTreeWidget(QTreeWidget * tree);
};

}
#endif // TOOLS_H
