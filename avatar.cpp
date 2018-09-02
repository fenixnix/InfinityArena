#include "avatar.h"
#include "input.h"
#include "sdl_render.h"
#include "objfactory.h"
#include "global.h"
#include "Item/item_chargerangeweapon.h"
#include "Item/item_common.h"
//#include "mapdungeon.h"
#include "FSM/state_dungeon.h"
#include "Event/ic_eventmgr.h"

Avatar* Avatar::p_static = NULL;
SDL_Point mousePos;

Avatar::Avatar()
{
    human = nullptr;
    leftButtonDown = false;
}

void Avatar::update()
{
    IC_EventMgr::the()->update();
    Obj_Human *hm = ObjFactory::Instance()->getHumanObj(avatarID);
    if(hm == nullptr){
        return;
    }
    if(hm->phyxBody == nullptr){
        cout<<"waring!!!"<<__FUNCTION__<<__LINE__<<endl;
        return ;
    }
    sightX = hm->locX;
    sightY = hm->locY;
    mousePos = Input::Instance()->getMousePos();

    float wx,wy,wz;
    NGLRender::the()->getMousePos(wx,wy,wz);
    int mx,my;
    IC_Map::Instance()->getNearIntPos(wx,wy,mx,my);
    ostringstream os;
    os<<"x:"<<mx<<endl<<"y:"<<my<<endl;
    Building* bd = IC_Map::Instance()->takeBuilding(mx,my);
    if(bd){
        os<<bd->type<<":"<<bd->drawID<<endl;
        os<<bd->hp<<"/"<<bd->maxHp<<endl;
    }

    infoString = os.str();

    if(leftButtonDown){
        b2Transform tra = human->phyxBody->GetTransform();
        float d = Global::distance(tra.p.x,tra.p.y,wx,wy);
        if(d<=1.0){
            IC_Map::Instance()->buildingOperate(wx,wy,1);
        }
    }
    b2Rot camDir;
    //    camDir.c = SDL_Render::the()->windows["game"]->cam_dx;
    //    camDir.s = SDL_Render::the()->windows["game"]->cam_dy;
    NGLRender::the()->getCamDir(camDir.c,camDir.s);
    bool wk = Input::Instance()->getKeyState(SDL_SCANCODE_W);
    bool sk = Input::Instance()->getKeyState(SDL_SCANCODE_S);
    bool ak = Input::Instance()->getKeyState(SDL_SCANCODE_A);
    bool dk = Input::Instance()->getKeyState(SDL_SCANCODE_D);
    bool lShift = Input::Instance()->getKeyState(SDL_SCANCODE_LSHIFT);


    b2Vec2 cdir;
    cdir.x = 0;
    cdir.y = 0;
    if(wk||sk||ak||dk){
        if(wk){
            cdir.y+=1;
        }
        if(sk){
            cdir.y-=1;
        }
        if(ak){
            cdir.x-=1;
        }
        if(dk){
            cdir.x+=1;
        }
        cdir.Normalize();
        b2Rot ctrlDir;
        ctrlDir.c = cdir.x;
        ctrlDir.s = cdir.y;
        //cout<<"angle: "<<camDir.GetAngle()<<" "<<ctrlDir.GetAngle()<<endl;
        b2Rot res(ctrlDir.GetAngle() + camDir.GetAngle()-(float)M_PI/2.0f);
        cdir.x = res.c;
        cdir.y = res.s;
        if((cdir.x!=0)||(cdir.y!=0)){
            if(!lShift){
                human->walk(cdir);
            }else{
                if(human->endurance>1){
                    human->run(cdir);
                }
            }
        }
        human->operateOnMap();
    }else{
        human->stop();
    }

}

void Avatar::drawN()
{
    if(human->phyxBody == nullptr){
        cout<<"waring!!!"<<__FUNCTION__<<__LINE__<<endl;
        return;
    }

    if(ObjFactory::Instance()->getObjOnMap(avatarID)){
        NGLRender* render = NGLRender::the();

        render->getWindow(NGLRender::windowGame)->setCamera(sightX,sightY);
        IC_Map::Instance()->draw(sightX,sightY,10);

        glDepthMask(GL_FALSE);
        ObjFactory::Instance()->draw(sightX,sightY,10);
        glDepthMask(GL_TRUE);

        //        //        AnimateEffect::instance()->fadeLine(sightX,sightY,0.1f,
        //        //                                            mx,my,0.1f);
    }
}

//void Avatar::draw3D(float x, float y, float r)
//{
//    glColor4f(1.0f,1.0f,1.0f,1.0f);
//    glEnable(GL_TEXTURE_2D);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_TEXTURE_COORD_ARRAY);


//    int w = IC_Map::Instance()->getMapWidth();
//    int h = IC_Map::Instance()->getMapHeight();
//    for(int j = 0;j<h;j++){
//        for(int i = 0;i<w;i++){
//            float d = Global::distance(x,y,i,j);
//            if(d<r){
//                int id = IC_Map::Instance()->getTerra(i,j);
//                if(id != WALL){
//                    SDL_Render::the()->drawObj(string("floor"),(float)i,(float)j,0);
//                    if(IC_Map::Instance()->getTerra(i+1,j) == WALL){
//                        glPushMatrix();
//                        glTranslatef(i+0.5,j,0);
//                        SDL_Render::the()->drawVWall(string("wallSide"));
//                        glPopMatrix();
//                    }
//                    if(IC_Map::Instance()->getTerra(i,j+1) == WALL){
//                        glPushMatrix();
//                        glTranslatef(i,j+0.5,0);
//                        SDL_Render::the()->drawHWall(string("wallSide"));
//                        glPopMatrix();
//                    }
//                    if(IC_Map::Instance()->getTerra(i-1,j) == WALL){
//                        glPushMatrix();
//                        glTranslatef(i-0.5,j,0);
//                        SDL_Render::the()->drawVWall(string("wallSide"));
//                        glPopMatrix();
//                    }
//                    if(IC_Map::Instance()->getTerra(i,j-1) == WALL){
//                        glPushMatrix();
//                        glTranslatef(i,j-0.5,0);
//                        SDL_Render::the()->drawHWall(string("wallSide"));
//                        glPopMatrix();
//                    }
//                }
//                glEnable(GL_TEXTURE_2D);
//                glEnableClientState(GL_VERTEX_ARRAY);
//                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//                if(id == WALL){
//                    SDL_Render::the()->drawObj("wallTop",i,j,1);
//                }
//                if(id == ACCESS){
//                    SDL_Render::the()->drawObj("access",i,j,0.1);
//                }
//            }
//        }
//    }
//}

#include "obj_ammo.h"
void Avatar::injectMouseLeftDown()
{
    //cout<<__FUNCTION__<<endl;
    leftButtonDown = true;
    //cout<<__FUNCTION__<<__LINE__<<human<<endl;
    if(human){
        //cout<<__FUNCTION__<<__LINE__<<endl;
        if(human->isArming){
            //cout<<__FUNCTION__<<__LINE__<<endl;
            if(human->mainhand!=nullptr){
                //cout<<__FUNCTION__<<__LINE__<<endl;
                string wpID = human->mainhand->getType();
                if(human->mainhand->getDrawID() == string("Bow")){
                    if(human->offhand!=nullptr){
                        Item_ChargeRangeWeapon* bow = Item_ChargeRangeWeapon::convert(human->mainhand);
                        bow->drawWeapon(human->offhand);
                    }
                }
                if(wpID == string("melee")){
                    //cout<<__FUNCTION__<<__LINE__<<endl;

                    NGLRender* render = NGLRender::the();
                    float mx,my,mz;
                    render->getMousePos(mx,my,mz);
                    //SDL_Render::the()->windows["game"]->getMousePos(mousePos.x,mousePos.y,&mx,&my);
                    b2Vec2 dv;
                    float hx,hy;
                    hx = human->phyxBody->GetTransform().p.x;
                    hy = human->phyxBody->GetTransform().p.y;
                    //    cout<<hx<<"*"<<hy<<endl;
                    dv.x = mx - hx;
                    dv.y = my - hy;
                    dv.Normalize();
                    human->useWeapon(b2Vec2(dv.x,dv.y));
                    //Item_MeleeWeapon *imw = Item_MeleeWeapon::convert(human->mainhand);
                    //imw->swing(dv.x,dv.y,human);
                    //human->fsm.act1(dv.x,dv.y);
                }
            }
        }else{

        }
    }
    //cout<<__FUNCTION__<<__LINE__<<human<<endl;
}

void Avatar::injectMouseLeftUp()
{
    leftButtonDown = false;
    if(human){
        NGLRender* render = NGLRender::the();
        float mx,my,mz;
        render->getMousePos(mx,my,mz);
        //SDL_Render::the()->windows["game"]->getMousePos(mousePos.x,mousePos.y,&mx,&my);
        if(human->isArming){
            if(human->mainhand!=nullptr){
                if(human->mainhand->getDrawID() == string("Bow")){
                    b2Vec2 dv;
                    float hx,hy;
                    hx = human->phyxBody->GetTransform().p.x;
                    hy = human->phyxBody->GetTransform().p.y;
                    //    cout<<hx<<"*"<<hy<<endl;
                    dv.x = mx - hx;
                    dv.y = my - hy;
                    dv.Normalize();
                    Item_ChargeRangeWeapon* bow = Item_ChargeRangeWeapon::convert(human->mainhand);
                    bow->ownerID = human->id;
                    if(human->offhand){
                        bow->loss(human->offhand,b2Vec2(hx+dv.x*0.5,hy+dv.y*0.5),dv);
                        if(human->offhand->isCommon()){
                            Item_Common* itmc = Item_Common::convert(human->offhand);
                            if(itmc->stackCount<=0){
                                delete itmc;
                                human->offhand = nullptr;
                            }
                        }
                    }
                }
            }
        }else{
            //cout<<__FUNCTION__<<mx<<"*"<<my<<endl;
            b2Transform tra = human->phyxBody->GetTransform();
            if(Global::distance(mx,my,tra.p.x,tra.p.y)<1){
                human->activeOnMap(b2Vec2(mx,my));
            }
        }
    }
}

void Avatar::injectKeyDown(SDL_Scancode scan_code)
{
    if(scan_code == SDL_SCANCODE_SPACE){
        Avatar::the()->human->dash(Avatar::the()->human->face);
    }
    if(scan_code == SDL_SCANCODE_X){
        human->isArming = !human->isArming;
        cout<<"arm:"<<human->isArming<<endl;
    }
}

