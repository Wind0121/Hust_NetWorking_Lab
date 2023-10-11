#ifndef STOP_WAIT_RDT_SENDER_H
#define STOP_WAIT_RDT_SENDER_H
#include "RdtSender.h"
class SRRdtSender :public RdtSender
{
private:
	int send_base;
    int nextseq;
    Packet pcks[Winsize * 2];
    bool st[Winsize * 2];

public:

	bool getWaitingState();
	bool send(const Message &message);						//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	void receive(const Packet &ackPkt);						//接受确认Ack，将被NetworkServiceSimulator调用	
	void timeoutHandler(int seqNum);					//Timeout handler，将被NetworkServiceSimulator调用
    int getWinsize(void);

public:
	SRRdtSender();
	virtual ~SRRdtSender();
};

#endif

