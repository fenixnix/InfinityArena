#include "blocksurround.h"

BlockSurround::BlockSurround()
{

}

void BlockSurround::init(int x, int y)
{
    count = 0;
    r = 1;
    ix = 0;
    iy = 0;
    ox = x;
    oy = y;

}

void BlockSurround::get(int &x, int &y)
{
    x = ix+ox; y = iy+oy;
    int size = r+r+1;
    do{
        ix = -r+count%size;
        iy = -r+count/size;
        //cout<<"count: "<<count<<" size:"<<size<<endl;
        count++;
    }while(!((ix == -r)
           ||(ix == r)
           ||(iy == r)
           ||(iy == -r)
           ));

    if(count>=(size*size)){
        r++;
        count = 0;
    }
}
