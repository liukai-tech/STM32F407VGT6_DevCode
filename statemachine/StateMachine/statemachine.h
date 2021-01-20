#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

typedef struct FsmTable_s
{
    int event;   				//�¼�
    int CurState;  				//��ǰ״̬
    void (*eventActFun)();  	//����ָ��
    int NextState;  			//��һ��״̬
}FsmTable_t;

/*״̬������*/
typedef struct FSM_s{
    int curState;				//��ǰ״̬
    FsmTable_t * pFsmTable;		//״̬��
    int size;					//�������
}FSM_t;


void StateMachine_Test(void);
void StateMachine_RF_CFG_Test(void);

#endif
