#ifndef BLOCKSURROUND_H
#define BLOCKSURROUND_H

#include <iostream>
using namespace std;

class BlockSurround
{
public:
    BlockSurround();
    void init(int x, int y);
    void get(int &x, int &y);
private:
    int count;
    int ix;
    int iy;
    int ox;
    int oy;
    int r;
};

#endif // BLOCKSURROUND_H
