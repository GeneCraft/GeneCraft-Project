#ifndef UITOOLS_H
#define UITOOLS_H
#include <QTreeWidgetItem>

namespace GeneCraftCore {
    class UITools
    {
    public:
        UITools();

        // Used to clear a QTreeWidget
        static void clearTreeWidget(QTreeWidget * tree);

    };
}
#endif // UITOOLS_H
