#ifndef IC_EVENTMGR_H
#define IC_EVENTMGR_H


class IC_EventMgr
{
public:
    IC_EventMgr();
    static IC_EventMgr *the();
    void update();//time update;
private:
    static IC_EventMgr* pStatic;
    int timer;
};

#endif // IC_EVENTMGR_H
