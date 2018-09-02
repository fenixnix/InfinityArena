#ifndef IC_MAP_H
#define IC_MAP_H

#include <string>
#include <vector>
#include <tinyxml2.h>
#include <base64.h>
#include "mapcontainer.h"
#include "item/item.h"
#include "Build/buildingfactory.h"
#include "Build/building.h"
#include "Build/building_prefab.h"
#include "pdungeonblock.h"

using namespace std;
using namespace tinyxml2;

class IC_Map
{
public:
    IC_Map();
    ~IC_Map();
    static IC_Map *Instance();

    void generateFromGaia(string fileName);
    void createWall();
    void draw();
    void draw(float x, float y, float r);
    void drawItems(float x, float y, float r);
    void save(string fileName);
    void load(string fileName);

    void freeMap();
    void create(int w, int h, string name);
    void loadMap(string fileName);
    void saveMap(string fileName);
    //virtual void draw(int x, int y, int r);
    void setTerra(int x, int y, unsigned char v);
    unsigned char getTerra(int x, int y);

    void randomRound(int &x,int& y);
    static int nearIntValue(float v);
    static void getNearIntPos(float x, float y, int &map_x,int &map_y);
    static void getFloorSpace(float x,float y,float w, float h,float &cx,float &cy,int &ix, int &iy);
    static void getBuildingTopLeft(Building* b,int &ix, int &iy);

    void createBuilding(int x,int y, string classify);
    void createItem(int x, int y, string classify);
    void eraseGroundItem(int x, int y);
    //IC_Object *getBuild(int x, int y);
    //IC_Object *getItem(int x, int y);
    Item* putItem(int x,int y,Item* item);
    Item* putItemf(float x,float y,Item* item);
    Item* takeItem(int x,int y);
    Item* takeItemf(float x,float y);

    void putBuilding(Building* build);
    void buildingOperate(float x,float y,float delta);
    void buildingOperate(int x,int y,float delta);
    Building *takeBuilding(float x, float y);
    Building *takeBuilding(int x, int y);
    void destoryBuilding(Building* build);
    void destroyBuilding(float x, float y);

    bool checkAccess(float x, float y, MapAccess& access);

    bool isEmpty(int x, int y);

    void release();
    //void update();

    void drawItems();

    int getMapWidth() const;

    int getMapHeight() const;

    int getMapLevel() const;

    string getType() const;

    static string getType(string fileName);

private:
    static IC_Map* s_pInstance;
    //Map Info
    string mapName;
    string type;
    int mapWidth;
    int mapHeight;
    int mapLevel;
    //Data
    vector<unsigned char> mapTerraData;

    vector<Item*> mapItems;//maping item
    vector<Building*> mapBuildings;//maping build
    vector<MapContainer*> mapContainers;

    vector<MapAccess> access;

    //vector<IC_Object*> buildData;
    //vector<IC_Object*> liveData;
    //vector<IC_Object*> bulletData;
    //Data map
    //vector<IC_Object*> buildMapData;
    //vector<IC_Object*> itemMapData;
    //XML Storage
    XMLDocument doc;
};

#endif // IC_MAP_H
