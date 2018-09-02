#ifndef ITEMLAYOUT_H
#define ITEMLAYOUT_H

#include "CEGUI/CEGUI.h"
#include "container.h"

typedef void (*FunPtr)(const CEGUI::EventArgs &);

class ItemLayout
{
public:
    ItemLayout();
    static void itemLayout(CEGUI::Window* win,Container* bag,FunPtr funPtr);
};

#endif // ITEMLAYOUT_H
