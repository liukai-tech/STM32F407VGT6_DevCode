#include "statemachine.h"
#include <stdio.h>

//reference website:https://www.jianshu.com/p/917c0fb8778b

/*状态机注册,给它一个状态表*/
void FSM_Register(FSM_t* pFsm, FsmTable_t* pTable)
{
    pFsm->pFsmTable = pTable;
}

/*状态迁移*/
void FSM_StateTransfer(FSM_t* pFsm, int state)
{
    pFsm->curState = state;
}

/*事件处理*/
void FSM_EventHandle(FSM_t* pFsm, int event)
{
    FsmTable_t* pActTable = pFsm->pFsmTable;
    void (*eventActFun)() = NULL;  //函数指针初始化为空
    int NextState;
    int CurState = pFsm->curState;
    int g_max_num = pFsm->size;
    int flag = 0; //标识是否满足条件
    int i;

    /*获取当前动作函数*/
    for (i = 0; i<g_max_num; i++)
    {
        //当且仅当当前状态下来个指定的事件，我才执行它
        if (event == pActTable[i].event && CurState == pActTable[i].CurState)
        {
            flag = 1;
            eventActFun = pActTable[i].eventActFun;
            NextState = pActTable[i].NextState;
            break;
        }
    }


    if (flag) //如果满足条件了
    {
        /*动作执行*/
        if (eventActFun)
        {
            eventActFun();
        }

        //跳转到下一个状态
        FSM_StateTransfer(pFsm, NextState);
    }
    else
    {
        printf("there is no match\n");
    }
}


enum year_state
{
    SPRING = 1,
    SUMMER,
    AUTUMN,
    WINTER
};

enum year_event
{
    EVENT1 = 1,
    EVENT2,
    EVENT3,
    EVENT4,
};

void spring_thing()
{
    printf("this is spring\n");
}
void summer_thing()
{
    printf("this is summer\n");
}
void autumn_thing()
{
    printf("this is autumn\n");
}
void winter_thing()
{
    printf("this is winter\n");
}

FsmTable_t year_table[] =
{
    //{到来的事件，当前的状态，将要要执行的函数，下一个状态}
    { EVENT1,  SPRING,    summer_thing,  SUMMER },
    { EVENT2,  SUMMER,    autumn_thing,  AUTUMN },
    { EVENT3,  AUTUMN,    winter_thing,  WINTER },
    { EVENT4,  WINTER,    spring_thing,  SPRING },
    //add your codes here
};

void StateMachine_Test(void)
{
	FSM_t year_fsm;
    FSM_Register(&year_fsm, year_table);
    year_fsm.curState = SPRING;
    year_fsm.size = sizeof(year_table)/sizeof(FsmTable_t);


    printf("\n-------1--init spring------\n");
    printf("state:%d\n",year_fsm.curState);

    printf("\n-------2--spring->summer------\n");
    FSM_EventHandle(&year_fsm,EVENT1);
    printf("state:%d\n",year_fsm.curState);

    printf("\n-------3--summer->autumn------\n");
    FSM_EventHandle(&year_fsm,EVENT2);
    printf("state:%d\n",year_fsm.curState);

    printf("\n-------4--autumn->winter------\n");
    FSM_EventHandle(&year_fsm,EVENT3);
    printf("state:%d\n",year_fsm.curState);

    printf("\n-------5--winter->spring------\n");
    FSM_EventHandle(&year_fsm,EVENT4);
    printf("state:%d\n",year_fsm.curState);

    printf("\n-------6--receive EVENT2 not EVENT1------\n");
    FSM_EventHandle(&year_fsm,EVENT2);
    printf("state:%d\n",year_fsm.curState);
}

enum rf_cfg_state
{
    RF_CFG_IDLE = 0,
	RF_CFG_FREQ_TX,
	RF_CFG_FREQ_TX_WAIT,
	RF_CFG_FREQ_RX,
	RF_CFG_FREQ_RX_WAIT,
	RF_CFG_PRT,
	RF_CFG_PRT_WAIT,
	RF_CFG_DONE
};

enum rf_cfg_event
{
    RF_CFG_EVENT1 = 1,
    RF_CFG_EVENT2,
    RF_CFG_EVENT3,
    RF_CFG_EVENT4,
	RF_CFG_EVENT5,
    RF_CFG_EVENT6,
    RF_CFG_EVENT7,
};

void rf_cfg_freq_tx()
{
    printf("rf cfg freq tx.\n");
}
void rf_cfg_freq_tx_wait()
{
    printf("rf cfg freq tx wait.\n");
	
	
}
void rf_cfg_freq_rx()
{
    printf("rf cfg freq rx.\n");
}
void rf_cfg_freq_rx_wait()
{
    printf("rf cfg freq rx wait.\n");
}
void rf_cfg_prt()
{
    printf("rf cfg prt.\n");
}
void rf_cfg_prt_wait()
{
    printf("rf cfg prt wait.\n");
}
void rf_cfg_done()
{
    printf("rf cfg done.\n");
}

FsmTable_t rf_cfg_table[] =
{
    //{到来的事件，当前的状态，将要要执行的函数，下一个状态}
    { RF_CFG_EVENT1,  RF_CFG_IDLE,    			rf_cfg_freq_tx,  		RF_CFG_FREQ_TX },
    { RF_CFG_EVENT2,  RF_CFG_FREQ_TX,    		rf_cfg_freq_tx_wait,  	RF_CFG_FREQ_TX_WAIT },
    { RF_CFG_EVENT3,  RF_CFG_FREQ_TX_WAIT,    	rf_cfg_freq_rx,  		RF_CFG_FREQ_RX },
    { RF_CFG_EVENT4,  RF_CFG_FREQ_RX,    		rf_cfg_freq_rx_wait,  	RF_CFG_FREQ_RX_WAIT },
	{ RF_CFG_EVENT5,  RF_CFG_FREQ_RX_WAIT,    	rf_cfg_prt,  			RF_CFG_PRT },
    { RF_CFG_EVENT6,  RF_CFG_PRT,    			rf_cfg_prt_wait,  		RF_CFG_PRT_WAIT },
	{ RF_CFG_EVENT7,  RF_CFG_PRT_WAIT,    		rf_cfg_done,  			RF_CFG_DONE },
    //add your codes here
};


void StateMachine_RF_CFG_Test(void)
{
	FSM_t rf_cfg_fsm;
    FSM_Register(&rf_cfg_fsm, rf_cfg_table);
    rf_cfg_fsm.curState = RF_CFG_IDLE;
    rf_cfg_fsm.size = sizeof(rf_cfg_table)/sizeof(FsmTable_t);

    printf("\n-------1--init idle------\n");
    printf("state:%d\n",rf_cfg_fsm.curState);

    printf("\n-------2--idle->tx------\n");
    FSM_EventHandle(&rf_cfg_fsm,RF_CFG_EVENT1);
    printf("state:%d\n",rf_cfg_fsm.curState);

    printf("\n-------3--tx->tx wait------\n");
    FSM_EventHandle(&rf_cfg_fsm,RF_CFG_EVENT2);
    printf("state:%d\n",rf_cfg_fsm.curState);

    printf("\n-------4--tx wait->rx------\n");
    FSM_EventHandle(&rf_cfg_fsm,RF_CFG_EVENT3);
    printf("state:%d\n",rf_cfg_fsm.curState);

    printf("\n-------5--rx->rx wait------\n");
    FSM_EventHandle(&rf_cfg_fsm,RF_CFG_EVENT4);
    printf("state:%d\n",rf_cfg_fsm.curState);

    printf("\n-------6--rx wait->prt------\n");
    FSM_EventHandle(&rf_cfg_fsm,RF_CFG_EVENT5);
    printf("state:%d\n",rf_cfg_fsm.curState);
	
	printf("\n-------7--prt->prt wait------\n");
    FSM_EventHandle(&rf_cfg_fsm,RF_CFG_EVENT6);
    printf("state:%d\n",rf_cfg_fsm.curState);
	
	printf("\n-------8--prt wait->done------\n");
    FSM_EventHandle(&rf_cfg_fsm,RF_CFG_EVENT7);
    printf("state:%d\n",rf_cfg_fsm.curState);
}
