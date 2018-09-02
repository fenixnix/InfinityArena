#include "item.h"
#include "itemfactory.h"
#include "Render/nglrender.h"

Item::Item()
{

}

void Item::drawOnMap(float x, float y)
{
    NGLRender* render = NGLRender::the();
//    render->useTex(getDrawID());
//    render->drawPoint(x,y,0.2);
    render->setMode(MODE_SPRITE);
    render->drawTextSprite(getDrawID(),x,y,0.2,64);
}

