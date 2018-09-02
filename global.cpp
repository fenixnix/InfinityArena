#include "global.h"

Global* Global::p_Static = NULL;

Global::Global()
{
    reloadFlag = false;
    isDrawDebug = false;
}

float Global::distance(float x1, float y1, float x2, float y2)
{
    float dx = x1-x2;
    float dy = y1-y2;
    return sqrt(dx*dx+dy*dy);
}

