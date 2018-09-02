#include "ic_map.h"
#include "global.h"
#include "Build/buildingfactory.h"
#include "obj/objfactory.h"
#include "gaia/nixgaiatype.h"
#include "obj/obj_beast.h"

using namespace nixgaia;

IC_Map* IC_Map::s_pInstance = 0;

IC_Map::IC_Map()
{
    cout<<__FUNCTION__<<endl;
}

IC_Map::~IC_Map()
{
    freeMap();
}

IC_Map *IC_Map::Instance()
{
    if(s_pInstance == 0){
        s_pInstance = new IC_Map;
    }
    return s_pInstance;
}

void IC_Map::generateFromGaia(string fileName)
{
    cout<<__FUNCTION__<<": "<<fileName<<"==";
    doc.Clear();
    cout<< doc.LoadFile(fileName.c_str())<<endl;
    XMLElement* root = doc.RootElement();
    mapWidth = atoi(root->Attribute("width"));
    mapHeight = atoi(root->Attribute("height"));
    mapLevel = atoi(root->Attribute("level"));
    type = string(root->Attribute("type"));
    cout<<__FUNCTION__<<" Map Size: "<<mapWidth<<"*"<<mapHeight<<endl;
    freeMap();
    create(mapWidth,mapHeight,"home");

    cout<<"Item Container Size:"<<mapItems.size()<<endl;
    XMLNode* layer = root->FirstChild();
    while(layer){
        cout<<layer->ToElement()->Name()<<endl;
        if(string(layer->ToElement()->Name()) == "layer"){
            //            cout<<layer->ToElement()->Attribute("name")<<endl;

            if(string(layer->ToElement()->Attribute("name")) == "ecoregion"){
                cout<<"load map unit"<<endl;
                XMLElement* d = layer->FirstChildElement("data");
                string src(d->FirstChild()->ToText()->Value());
                mapTerraData = Base64::decode(src);
            }
        }
        createWall();

        if(string(layer->ToElement()->Name()) == "ObjectLayer"){
            if(string(layer->ToElement()->Attribute("name")) == "object"){
                cout<<"load map object"<<endl;
                XMLElement* d = layer->FirstChildElement("data");
                string src(d->FirstChild()->ToText()->Value());
                vector<unsigned char> objData;
                objData = Base64::decode(src);
                for(int i = 0;i<objData.size();i++){
                    ObjectType type = (ObjectType)objData[i];
                    switch(type){
                    case nixgaia::NOTHING: break;
                    case nixgaia::TREE:BuildingFactory::the()->createDirectly("tree",i%mapWidth,i/mapWidth);break;
                    case nixgaia::BUSH:BuildingFactory::the()->createDirectly("bush",i%mapWidth,i/mapWidth);break;break;
                    case PILE:putItem(i%mapWidth,i/mapWidth,Item_Common::create("pile",6));break;
                    //case BEAST:Obj_Beast::create("deer",i%mapWidth,i/mapWidth);break;
                    default:break;
                    }
                }
            }
            BuildingFactory::the()->createDirectly("Idol",mapWidth/2+0.5,mapWidth/2+0.5);
        }
        layer = layer->NextSibling();
    }
    cout<<__FUNCTION__<<": finish"<<endl;
}

void IC_Map::createWall()
{
    int w = mapWidth;
    int h = mapHeight;
    B2Physx::the()->createBlockWall(-0.5,-0.5,w-0.5,-0.5);
    B2Physx::the()->createBlockWall(-0.5,-0.5,-0.5,h-0.5);
    B2Physx::the()->createBlockWall(w-0.5,h-0.5,w-0.5,-0.5);
    B2Physx::the()->createBlockWall(w-0.5,h-0.5,-0.5,h-0.5);

    for(int j = 0;j<h;j++){
        for(int i = 0;i<w;i++){
            int id = IC_Map::Instance()->getTerra(i,j);
            if(id != CLIFF){
                if(IC_Map::Instance()->getTerra(i+1,j) == CLIFF){
                    B2Physx::the()->createBlockWall(i+0.5,j-0.5,i+0.5,j+0.5);
                }
                if(IC_Map::Instance()->getTerra(i,j+1) == CLIFF){
                    B2Physx::the()->createBlockWall(i-0.5,j+0.5,i+0.5,j+0.5);
                }
                if(IC_Map::Instance()->getTerra(i-1,j) == CLIFF){
                    B2Physx::the()->createBlockWall(i-0.5,j-0.5,i-0.5,j+0.5);
                }
                if(IC_Map::Instance()->getTerra(i,j-1) == CLIFF){
                    B2Physx::the()->createBlockWall(i-0.5,j-0.5,i+0.5,j-0.5);
                }
            }
        }
    }
}

void IC_Map::draw()
{

}

void IC_Map::draw(float x, float y, float r)
{
    glEnable(GL_DEPTH_TEST);
    int w = mapWidth;
    int h = mapHeight;
    NGLRender *render = NGLRender::the();
    render->setMode(MODE_TEX);
    for(int j = 0;j<h;j++){
        for(int i = 0;i<w;i++){
            float d = Global::distance(x,y,i,j);
            if(d<r){
                int id = getTerra(i,j);
                if(id != CLIFF){
                    render->useTex(id);
                    //render->useTex(string("tree"));
                    render->drawFloor(i,j);
                    if(getTerra(i+1,j) == CLIFF){
                        render->useTex(CLIFF);
                        render->drawWall(i+0.5,j+0.5,i+0.5,j-0.5);
                    }
                    if(getTerra(i,j+1) == CLIFF){
                        render->useTex(CLIFF);
                        render->drawWall(i-0.5,j+0.5,i+0.5,j+0.5);
                    }
                    if(getTerra(i-1,j) == CLIFF){
                        render->useTex(CLIFF);
                        render->drawWall(i-0.5,j+0.5,i-0.5,j-0.5);
                    }
                    if(getTerra(i,j-1) == CLIFF){
                        render->useTex(CLIFF);
                        render->drawWall(i-0.5,j-0.5,i+0.5,j-0.5);
                    }
                }
                if(id == CLIFF){
                    render->drawCeil(i,j);
                }
            }
        }
    }

    render->setMode(MODE_SPRITE);
    render->setSpriteSize(128);
    BuildingFactory::the()->draw3D(x,y,r);
    drawItems(x,y,r);
}

void IC_Map::drawItems(float x, float y, float r)
{
    NGLRender *render = NGLRender::the();
    render->setMode(MODE_SPRITE);
    for(auto itr = mapContainers.begin();itr!=mapContainers.end();itr++){
        MapContainer* mc = *itr;
        float d = Global::distance(x,y,mc->x,mc->y);
        if(d<r){
            //render->useTex("pile");
            //render->drawPoint(mc->x,mc->y,0.2);
            mc->item->drawOnMap(mc->x,mc->y);
        }
        //mc->item->drawOnMap(mc->x,mc->y);
    }
}

void IC_Map::freeMap()
{
    B2Physx::the()->clearWall();
    for(auto itr = mapContainers.begin();itr!=mapContainers.end();itr++){
        delete (*itr)->item;
        delete (*itr);
    }
    mapBuildings.clear();
    mapTerraData.clear();
    mapItems.clear();
    mapContainers.clear();
    access.clear();
    BuildingFactory::the()->clear();
    cout<<__FUNCTION__<<__LINE__<<endl;
    Global::the()->world.loadTeam();
    cout<<__FUNCTION__<<__LINE__<<endl;
    ObjFactory::Instance()->clear();
    cout<<__FUNCTION__<<__LINE__<<endl;
    Global::the()->world.putTeam();
    cout<<__FUNCTION__<<__LINE__<<endl;
}

void IC_Map::create(int w, int h, string name)
{
    mapName = name;
    mapWidth = w;
    mapHeight = h;
    //Data
    freeMap();
    mapTerraData.assign(w*h,0);
    mapItems.assign(mapWidth*mapHeight,NULL);
    mapBuildings.assign(mapWidth*mapHeight,NULL);
}

void IC_Map::loadMap(string fileName)
{
    cout<<__FUNCTION__<<": "<<fileName<<"==";
    doc.Clear();
    cout<< doc.LoadFile(fileName.c_str())<<endl;
    XMLElement* root = doc.RootElement();
    mapWidth = atoi(root->Attribute("width"));
    mapHeight = atoi(root->Attribute("height"));
    mapLevel = atoi(root->Attribute("level"));
    type = string(root->Attribute("type"));
    cout<<__FUNCTION__<<" Map Size: "<<mapWidth<<"*"<<mapHeight<<endl;
    freeMap();
    create(mapWidth,mapHeight,"home");

    cout<<"Item Container Size:"<<mapItems.size()<<endl;
    XMLNode* layer = root->FirstChild();
    while(layer){
        cout<<layer->ToElement()->Name()<<endl;
        if(string(layer->ToElement()->Name()) == "layer"){
            //            cout<<layer->ToElement()->Attribute("name")<<endl;

            if(string(layer->ToElement()->Attribute("name")) == "ecoregion"){
                cout<<"load ecoregion"<<endl;
                XMLElement* d = layer->FirstChildElement("data");
                string src(d->FirstChild()->ToText()->Value());
                mapTerraData = Base64::decode(src);
            }

            if(string(layer->ToElement()->Attribute("name")) == "build"){
                cout<<"load build"<<endl;
                XMLNode* n = layer->FirstChild();
                while(n){
                    string classify = n->ToElement()->Name();
                    //cout<<classify<<endl;
                    int x = atoi(n->ToElement()->Attribute("x"));
                    int y = atoi(n->ToElement()->Attribute("y"));
                    if(classify == "Idol"){
                        BuildingFactory::the()->createDirectly(classify,x,y);
                    }else{
                        BuildingFactory::the()->createDirectly(string("Tree"),x,y);
                    }
                    n = n->NextSibling();
                }
            }

            if(string(layer->ToElement()->Attribute("name")) == "item"){
                cout<<"load item"<<endl;
                XMLNode* n = layer->FirstChild();
                int itemCount = 0;
                while(n){
                    itemCount ++;
                    string classify = n->ToElement()->Name();
                    int x = atoi(n->ToElement()->Attribute("x"));
                    int y = atoi(n->ToElement()->Attribute("y"));
                    putItem(x,y,Item_Common::create(classify,10));
                    n = n->NextSibling();
                }
                cout<<"Item Count: "<<itemCount<<endl;
            }

            if(string(layer->ToElement()->Attribute("name")) == "access"){
                cout<<"load item"<<endl;
                XMLNode* n = layer->FirstChild();
                int itemCount = 0;
                while(n){
                    MapAccess ac;
                    ac.id = string(n->ToElement()->Name());
                    ac.srcLoc.x = n->ToElement()->IntAttribute("src_x");
                    ac.srcLoc.y = n->ToElement()->IntAttribute("src_y");
                    ac.dstLoc.x = n->ToElement()->IntAttribute("dst_x");
                    ac.dstLoc.y = n->ToElement()->IntAttribute("dst_y");
                    access.push_back(ac);
                    n = n->NextSibling();
                }
                cout<<"Item Count: "<<itemCount<<endl;
            }
        }
        layer = layer->NextSibling();
    }
    cout<<__FUNCTION__<<": finish"<<endl;
}

void IC_Map::saveMap(string fileName)
{
    //    doc.Clear();
    //    XMLDeclaration *declare = doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    //    doc.LinkEndChild(declare);
    //    doc.LinkEndChild(doc.NewComment("Infinity Chaos tiled map Info"));
    //    XMLElement* root = doc.NewElement("map");doc.LinkEndChild(root);
    //    root->SetAttribute("width",mapWidth);
    //    root->SetAttribute("height",mapHeight);
    //    root->SetAttribute("level",mapLevel);
    //    XMLElement* tileSet = doc.NewElement("tileset");root->LinkEndChild(tileSet);
    //    tileSet->SetAttribute("source","tileSet.tsx");
    //    tileSet->SetAttribute("orientation","orthogonal");
    //    //tileSet->SetAttribute("name",tileSetName.c_str());

    //    //可以包含下列元素：属性（自Tiled0.8.0版本）,图像，图块
    //    XMLElement* layer = doc.NewElement("layer");root->LinkEndChild(layer);
    //    layer->SetAttribute("name","ecoregion");
    //    layer->SetAttribute("opacity",1.0f);
    //    layer->SetAttribute("visible",true);

    //    XMLElement* data = doc.NewElement("data");layer->LinkEndChild(data);
    //    data->SetAttribute("encoding","base64");

    //    string ds = Base64::encode(this->mapTerraData);
    //    XMLText* textData = doc.NewText(ds.c_str());data->LinkEndChild(textData);


    //    XMLElement* buildlayer = doc.NewElement("layer");root->LinkEndChild(buildlayer);
    //    buildlayer->SetAttribute("name","build");
    //    buildlayer->SetAttribute("opacity",1.0f);
    //    buildlayer->SetAttribute("visible",true);
    //    for(int i = 0;i<buildData.size();i++){
    //        IC_BuildObject *bo = (IC_BuildObject*)buildData.at(i);
    //        XMLElement* build = doc.NewElement((bo->getBuildClassify()).c_str());
    //        build->SetAttribute("x",bo->getLocX());
    //        build->SetAttribute("y",bo->getLocY());
    //        buildlayer->LinkEndChild(build);
    //    }

    //    XMLElement* itemlayer = doc.NewElement("layer");root->LinkEndChild(itemlayer);
    //    itemlayer->SetAttribute("name","item");
    //    itemlayer->SetAttribute("opacity",1.0f);
    //    itemlayer->SetAttribute("visible",true);

    //    for(int j = 0; j<mapHeight; j++){
    //        for(int i = 0; i<mapWidth; i++){
    //            if(itemMapData.at(j*mapWidth+i)!=0){
    //                IC_ItemObject *bo = (IC_ItemObject*)itemMapData.at(j*mapWidth+i);
    //                XMLElement* item = doc.NewElement(bo->itemClassify.c_str());
    //                item->SetAttribute("x",i);
    //                item->SetAttribute("y",j);
    //                itemlayer->LinkEndChild(item);
    //            }
    //        }
    //    }
    //    doc.SaveFile(fileName.c_str());
}

//void IC_Map::draw(int x, int y, int r)
//{
//    sdl_render2D::Instance()->tileMap.begin();
//    int w = IC_Map::Instance()->getMapWidth();
//    int h = IC_Map::Instance()->getMapHeight();
//    for(int j = 0;j<h;j++){
//        for(int i = 0;i<w;i++){
//            int id = IC_Map::Instance()->getTerra(i,j);
//            sdl_render2D::Instance()->tileMap.draw(i,j,id-1);
//        }
//    }
//    sdl_render2D::Instance()->tileMap.end();
//}

void IC_Map::setTerra(int x, int y, unsigned char v)
{
    if((x<0)||(x>=mapWidth)||(y<0)||(y>=mapHeight)){
        return;
    }
    mapTerraData.at(y*mapWidth+x) = v;
}

unsigned char IC_Map::getTerra(int x, int y)
{
    if((x<0)||(x>=mapWidth)||(y<0)||(y>=mapHeight)){
        return 0;
    }
    return mapTerraData.at(y*mapWidth+x);
}

void IC_Map::randomRound(int &x, int &y)
{
    int w,h;
    w = getMapWidth();
    h = getMapHeight();
    if(rand()%2){
        if(rand()%2){
            x = 0;
        }else{
            x = w-1;
        }
        y = rand()%h;
    }else{
        if(rand()%2){
            y = 0;
        }else{
            y = h-1;
        }
        x = rand()%w;
    }
}

inline int IC_Map::nearIntValue(float v)
{
    return floor(v+0.5);
}

void IC_Map::getNearIntPos(float x, float y, int &map_x, int &map_y)
{
    map_x = nearIntValue(x);
    map_y = nearIntValue(y);
}

void IC_Map::getFloorSpace(float x, float y, float w, float h, float &cx, float &cy, int &ix, int &iy)
{
    //cout<<__FUNCTION__<<":";
    //cout<<x<<"*"<<y<<"*"<<w<<"*"<<h;
    float tlx = x-w/2.0f+0.5f;
    float tly = y-h/2.0f+0.5f;
    IC_Map::getNearIntPos(tlx,tly,ix,iy);
    cx = ix+w/2.0f-0.5;
    cy = iy+h/2.0f-0.5;
}

void IC_Map::getBuildingTopLeft(Building *b, int &ix, int &iy)
{
    cout<<__FUNCTION__<<endl;
    //cout<<x<<"*"<<y<<"*"<<w<<"*"<<h;
    float tlx = b->x-b->w/2.0f+0.5f;
    float tly = b->y-b->h/2.0f+0.5f;
    IC_Map::getNearIntPos(tlx,tly,ix,iy);
}

//put item 2 near diff place
Item* IC_Map::putItem(int x, int y, Item *item)
{
    cout<<__FUNCTION__<<" x:"<<x<<" y:"<<y<<endl;
    int px = x;
    int py = y;
    int count = 0;
    Item * tit = item;
    while(tit){
        //change place to stack;
        Item* it = mapItems[px+mapWidth*py];
        if(it==nullptr){
            it = tit;
            MapContainer* mc = new MapContainer;
            mc->x = x;
            mc->y = y;
            mc->item = tit;
            mapContainers.push_back(mc);
            mapItems[px+mapWidth*py] = mc->item;
            //cout<<"items:"<<items[px+py*mapWidth]<<endl;
            return nullptr;
        }
        if(it->isCommon()&&tit->isCommon()){
            Item_Common* itmc = Item_Common::convert(it);
            Item_Common* itmcd = Item_Common::convert(tit);
            tit = itmc->stack(itmcd);
        }
        count++;
    }
    return nullptr;
}

Item *IC_Map::putItemf(float fx, float fy, Item *item)
{
    int x,y;
    IC_Map::getNearIntPos(fx,fy,x,y);
    return putItem(x,y,item);
}

Item *IC_Map::takeItem(int x, int y)
{
    //cout<<__FUNCTION__<<" "<<x<<"*"<<y;
    Item* tmp = mapItems[x+y*mapWidth];
    if(tmp == NULL){
        //cout<<"empty place!"<<endl;
        return nullptr;
    }
    mapItems[x+y*mapWidth] = nullptr;
    for(auto i = mapContainers.begin();i!=mapContainers.end();){
        MapContainer* mc = *i;
        if((mc->x == x)&&(mc->y == y)){
            delete mc;
            i = mapContainers.erase(i);
        }else{
            i++;
        }
    }
    return tmp;
}

Item *IC_Map::takeItemf(float fx, float fy)
{
    int x,y;
    IC_Map::getNearIntPos(fx,fy,x,y);
    return takeItem(x,y);
}

void IC_Map::putBuilding(Building *build)
{
    //cout<<__FUNCTION__<<build<<" "<<build->x<<" "<<build->y<<" "<<build->w<<" "<<build->h;
    int x,y;
    //float fx,fy;
    getFloorSpace(build->x,build->y,build->w,build->h,build->x,build->y,x,y);
    //cout<<" "<<x<<" "<<y;
    for(int row = y;row<(build->w+y);row++){
        for(int col = x;col<(build->w+x);col++){
            mapBuildings[row*mapWidth+col] = build;
            //cout<<"*"<<row*mapWidth+col;
        }
    }
    //cout<<endl;
}

void IC_Map::buildingOperate(float x, float y, float delta)
{
    //cout<<__FUNCTION__;
    int ix,iy;
    getNearIntPos(x,y,ix,iy);
    //cout<<"*"<<ix<<"*"<<iy;
    //cout<<endl;
    return buildingOperate(ix,iy,delta);
}

void IC_Map::buildingOperate(int x, int y, float delta)
{
    //cout<<"pos: "<<x<<"*"<<y<<endl;
    Building* bd = IC_Map::Instance()->takeBuilding(x,y);
    if(bd){
        //cout<<__FUNCTION__<<bd<<endl;
        bd->operate();
        bd->active();
        //cout<<__FUNCTION__<<__LINE__<<endl;
    }
}

Building *IC_Map::takeBuilding(float x, float y)
{
    cout<<__FUNCTION__;
    int ix,iy;
    getNearIntPos(x,y,ix,iy);
    cout<<"*"<<ix<<"*"<<iy;
    cout<<endl;
    return takeBuilding(ix,iy);
}

Building *IC_Map::takeBuilding(int x, int y)
{
    if((x<0)||(x>=mapWidth)||(y<0)||(y>=mapHeight)){
        return nullptr;
    }
    return mapBuildings[x+y*mapWidth];
}

void IC_Map::destoryBuilding(Building *build)
{
    cout<<__FUNCTION__<<build<< endl;
    int x,y;
    getBuildingTopLeft(build,x,y);
    for(int row = y;row<y+build->h;row++){
        for(int col = x; col<x+build->w;col++){
            mapBuildings[col+row*mapWidth] = nullptr;
        }
    }
}

void IC_Map::destroyBuilding(float x, float y)
{
    destoryBuilding(takeBuilding(x,y));
}

bool IC_Map::checkAccess(float x, float y, MapAccess &ac)
{
    for(auto itr = access.begin();itr!=access.end();itr++){
        float d = Global::distance(x,y,itr->srcLoc.x,itr->srcLoc.y);
        if(d<0.5f){
            ac = *itr;
            return true;
        }
    }
    return false;
}

bool IC_Map::isEmpty(int x, int y)
{
    if(mapBuildings[x+y*mapWidth]){
        //cout<<__FUNCTION__<<":building"<<endl;
        return false;
    }
    if(mapItems[x+y*mapWidth]){
        //cout<<__FUNCTION__<<":item"<<endl;
        return false;
    }
    return true;
}

void IC_Map::drawItems()
{
    //cout<<__FUNCTION__<<endl;
    for(auto itr = mapContainers.begin();itr!=mapContainers.end();itr++){
        MapContainer* mc = *itr;
        mc->item->drawOnMap(mc->x,mc->y);
    }
}

//void IC_Map::createBuilding(int x, int y, string classify)
//{
//    IC_Object* obj = IC_BuildPrefab::Instance()->create(x,y,classify);
//    buildData.push_back(obj);
//    buildMapData.at(y*mapWidth+x) = obj;
//}

//void IC_Map::createItem(int x, int y, string classify)
//{
//    IC_Object* obj = IC_ItemPrefab::Instance()->create(classify,1,10);
//    //itemData.push_back(obj);
//    itemMapData.at(y*mapWidth+x) = obj;
//}

//void IC_Map::eraseGroundItem(int x, int y)
//{
//    if((x<0)||(x>=mapWidth)||(y<0)||(y>=mapHeight)){
//        return;
//    }
//    itemMapData.at(y*mapWidth+x) = 0;
//}

//IC_Object *IC_Map::getBuild(int x, int y)
//{
//    if((x<0)||(x>=mapWidth)||(y<0)||(y>=mapHeight)){
//        return 0;
//    }
//    return buildMapData.at(y*mapWidth+x);
//}

//IC_Object *IC_Map::getItem(int x, int y)
//{
//    if((x<0)||(x>=mapWidth)||(y<0)||(y>=mapHeight)){
//        return 0;
//    }
//    return itemMapData.at(y*mapWidth+x);
//}

int IC_Map::getMapWidth() const
{
    return mapWidth;
}

int IC_Map::getMapHeight() const
{
    return mapHeight;
}

int IC_Map::getMapLevel() const
{
    return mapLevel;
}

string IC_Map::getType() const
{
    return type;
}

string IC_Map::getType(string fileName)
{
    XMLDocument d;
    cout<<__FUNCTION__<<fileName;
    cout<< d.LoadFile(fileName.c_str())<<endl;
    XMLElement* root = d.RootElement();
    return string(root->Attribute("type"));
}

