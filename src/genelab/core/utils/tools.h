#ifndef TOOLS_H
#define TOOLS_H

#include <QTreeWidgetItem>
#include "LinearMath/btScalar.h"

namespace GeneCraftCore {

class Tools
{
public:
    Tools();

    static int random(int min, int max);
    static btScalar random(btScalar min, btScalar max);

#ifndef BT_USE_DOUBLE_PRECISION
    static double random(double min, double max);
#endif

    static void clearTreeWidgetItem(QTreeWidgetItem * item);

    // Used to clear a QTreeWidget
    static void clearTreeWidget(QTreeWidget * tree);
};

}
#endif // TOOLS_H
