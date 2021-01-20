#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

typedef struct FsmTable_s
{
    int event;   				//事件
    int CurState;  				//当前状态
    void (*eventActFun)();  	//函数指针
    int NextState;  			//下一个状态
}FsmTable_t;

/*状态机类型*/
typedef struct FSM_s{
    int curState;				//当前状态
    FsmTable_t * pFsmTable;		//状态表
    int size;					//表的项数
}FSM_t;


void StateMachine_Test(void);
void StateMachine_RF_CFG_Test(void);

#endif
