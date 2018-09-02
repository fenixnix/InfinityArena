#QT += core

TARGET = InfinityArena
#CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    sdl2_game.cpp \
    input.cpp \
    avatar.cpp \
    Obj/obj_human.cpp \
    Obj/obj_wall.cpp \
    Obj/objfactory.cpp \
    FSM/state_dungeon.cpp \
    Obj/obj_creature.cpp \
    Obj/obj_dmg.cpp \
    ic_map.cpp \
    item/item.cpp \
    item/itemfactory.cpp \
    mapcontainer.cpp \
    container.cpp \
    Build/building.cpp \
    Build/buildingfactory.cpp \
    materiallist.cpp \
    FSM/state_mainui.cpp \
    Build/building_prefab.cpp \
    Build/building_workbench.cpp \
    Build/building_furnace.cpp \
    Build/building_Storage.cpp \
    Obj/obj_beast.cpp \
    item/item_meleeweapon.cpp \
    Build/building_idol.cpp \
    global.cpp \
    item/item_chargerangeweapon.cpp \
    item/item_common.cpp \
    Obj/obj_ammo.cpp \
    Obj/ACE_Creature/ace_creature.cpp \
    Obj/ACE_Creature/ace_largeslime.cpp \
    FSM/state_avatar.cpp \
    world.cpp \
    Build/building_treasure.cpp \
    blocksurround.cpp \
    ObjFSM/obj_fsm.cpp \
    ObjFSM/obj_statedisable.cpp \
    ObjFSM/obj_statebusy.cpp \
    ObjFSM/obj_statenormal.cpp \
    ObjFSM/obj_statestroll.cpp \
    ObjFSM/obj_stateattack.cpp \
    ObjFSM/obj_statefollow.cpp \
    ObjFSM/obj_statepunch.cpp \
    ObjFSM/obj_stateavatar.cpp \
    ObjFSM/actslash1.cpp \
    ObjFSM/actslash2.cpp \
    ObjFSM/ai_feature.cpp \
    ObjFSM/actslash3.cpp \
    Build/plant.cpp \
    FSM/state_gamemenu.cpp \
    FSM/state_inventory.cpp \
    FSM/state_selectbuilding.cpp \
    FSM/state_putbuilding.cpp \
    FSM/state_fillmaterial.cpp \
    Event/ic_eventmgr.cpp \
    Event/ic_event.cpp \
    Event/ic_event_massanimalraid.cpp \
    ObjFSM/obj_statetobuilding.cpp \
    FSM/state_barter.cpp \
    itemlayout.cpp \
    ../_src/globaltimer.cpp \
    ../_src/Render/physxdraw.cpp \
    ../_src/FSM/finitystate.cpp \
    ../_src/FSM/fsm.cpp \
    ../_src/FSM/stateuibase.cpp \
    ../_src/sdl_input.cpp \
    ../_src/b2physx.cpp \
    ../_src/obj.cpp


include(D:/workspace/include/SDL2.pri)
include(D:/workspace/include/Box2D.pri)
include("D:/workspace/include/opengl.pri")
include("D:\workspace\include\tinyXml2.pri")
include("D:\workspace\include\base64.pri")
include(../_src/render.pri)
include(../_src/ngui.pri)
include(../_src/NixGaia.pri)

INCLUDEPATH += D:\workspace\GameDev\DungeonGenerateApp

INCLUDEPATH += ./Obj
INCLUDEPATH += ./render

HEADERS += \
    sdl2_game.h \
    input.h \
    avatar.h \
    Obj/obj_human.h \
    Obj/obj_wall.h \
    Obj/objfactory.h \
    FSM/state_dungeon.h \
    Obj/obj_creature.h \
    Obj/obj_dmg.h \
    ic_map.h \
    item/item.h \
    item/itemfactory.h \
    mapcontainer.h \
    container.h \
    Build/building.h \
    Build/buildingfactory.h \
    materiallist.h \
    FSM/state_mainui.h \
    Build/building_prefab.h \
    Build/building_workbench.h \
    Build/building_furnace.h \
    Build/building_Storage.h \
    Obj/obj_beast.h \
    item/item_meleeweapon.h \
    Build/building_idol.h \
    global.h \
    item/item_chargerangeweapon.h \
    item/item_common.h \
    Obj/obj_ammo.h \
    Obj/ACE_Creature/ace_creature.h \
    Obj/ACE_Creature/ace_largeslime.h \
    FSM/state_avatar.h \
    world.h \
    ../DungeonGenerateApp/pdungeonblock.h \
    Build/building_treasure.h \
    blocksurround.h \
    ObjFSM/obj_fsm.h \
    ObjFSM/obj_state.h \
    ObjFSM/obj_statedisable.h \
    ObjFSM/obj_statebusy.h \
    ObjFSM/obj_statenormal.h \
    ObjFSM/obj_statestroll.h \
    ObjFSM/obj_stateattack.h \
    ObjFSM/obj_statefollow.h \
    ObjFSM/obj_statepunch.h \
    ObjFSM/obj_stateavatar.h \
    ObjFSM/actslash1.h \
    ObjFSM/actslash2.h \
    ObjFSM/ai_feature.h \
    ObjFSM/actslash3.h \
    Build/plant.h \
    FSM/state_gamemenu.h \
    FSM/state_inventory.h \
    FSM/state_selectbuilding.h \
    FSM/state_putbuilding.h \
    FSM/state_fillmaterial.h \
    Event/ic_eventmgr.h \
    Event/ic_event.h \
    Event/ic_event_massanimalraid.h \
    ObjFSM/obj_statetobuilding.h \
    FSM/state_barter.h \
    itemlayout.h \
    ../_src/globaltimer.h \
    ../_src/Render/physxdraw.h \
    ../_src/FSM/finitystate.h \
    ../_src/FSM/fsm.h \
    ../_src/FSM/stateuibase.h \
    ../_src/sdl_input.h \
    ../_src/b2physx.h \
    ../_src/obj.h \
    ../_src/physxobj.h


RESOURCES += \
    res.qrc

DISTFILES += \
    slvs.vert \
    slfs.frag

