#include "uitools.h"

namespace GeneCraftCore {
    UITools::UITools()
    {
    }

    void UITools::clearTreeWidget(QTreeWidget * tree)
    {
        for(int i = 0; i < tree->topLevelItemCount(); i++) {
            delete tree->topLevelItem(i);
        }

        tree->clear();
    }
}
