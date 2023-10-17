
#include "Global.h"
#include "SRRdtSender.h"


SRRdtSender::SRRdtSender()
{
    send_base = 0;
    nextseq = 0;
    for(int i = 0;i < 2 * Winsize;i++)
        st[i] = false;
}


SRRdtSender::~SRRdtSender()
{
}



bool SRRdtSender::getWaitingState() {
	return getWinsize() == Winsize;
}




bool SRRdtSender::send(const Message &message) {
	if (getWaitingState()) { //发送方处于等待确认状态
		return false;
	}
    //准备好需要发送的报文
	Packet pck;
    pck.acknum = -1;
    pck.seqnum = nextseq;
    pck.checksum = 0;
    memcpy(pck.payload,message.data,sizeof(message.data));
    pck.checksum = pUtils->calculateCheckSum(pck);
    pUtils->printPacket("发送方发送报文", pck);

    //启动定时器与发送报文
    pns->startTimer(SENDER,Configuration::TIME_OUT,pck.seqnum);
    pns->sendToNetworkLayer(RECEIVER,pck);
    //送入缓存，更新nextseq
    pcks[pck.seqnum] = pck;
    nextseq = (nextseq + 1) % SeqNum;
    printf("发送方窗口:[ ");
    for (int i = 0; i < getWinsize(); i++) {
        printf("%d(%d) ", (send_base + i) % SeqNum,st[(send_base + i) % SeqNum]);
    }
    printf("]\n");

    return true;
}

void SRRdtSender::receive(const Packet &ackPkt) {
    if(send_base == nextseq)
        return;
    int checkSum = pUtils->calculateCheckSum(ackPkt);
    int offset_ack = (ackPkt.acknum - send_base + SeqNum) % SeqNum;
    //检验和相等且确认序号在发送窗口内
    if(checkSum == ackPkt.checksum && offset_ack < getWinsize()){
        pUtils->printPacket("发送方正确收到确认", ackPkt);
        //确认收到并停止计时
        if(!st[ackPkt.acknum]) {
            st[ackPkt.acknum] = true;
            pns->stopTimer(SENDER, ackPkt.acknum);
        }
        printf("发送方窗口:[ ");
        for (int i = 0; i < getWinsize(); i++) {
            printf("%d(%d) ", (send_base + i) % SeqNum,st[(send_base + i) % SeqNum]);
        }
        printf("]->");
        //窗口前移
        while(st[send_base]){
            st[send_base] = false;
            send_base = (send_base + 1) % SeqNum;
        }
        printf("发送方窗口:[ ");
        for (int i = 0; i < getWinsize(); i++) {
            printf("%d(%d) ", (send_base + i) % SeqNum,st[(send_base + i) % SeqNum]);
        }
        printf("]\n");
    }else if(checkSum != ackPkt.checksum)
        pUtils->printPacket("发送方没有正确收到该报文确认,数据校验错误", ackPkt);
    else
        pUtils->printPacket("发送方已正确收到过该报文确认", ackPkt);
}

void SRRdtSender::timeoutHandler(int seqNum) {
    //超时
    pns->stopTimer(SENDER,seqNum);
    pns->startTimer(SENDER, Configuration::TIME_OUT,seqNum);
    pUtils->printPacket("发送方重新发送报文", pcks[seqNum]);
    pns->sendToNetworkLayer(RECEIVER,pcks[seqNum]);
}

int SRRdtSender::getWinsize() {
    return (nextseq + SeqNum - send_base) % SeqNum;
}
