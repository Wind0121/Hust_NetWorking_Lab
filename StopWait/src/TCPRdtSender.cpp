
#include "Global.h"
#include "TCPRdtSender.h"


TCPRdtSender::TCPRdtSender()
{
    send_base = 0;
    nextseq = 0;
    repeat_cnt = 0;

}


TCPRdtSender::~TCPRdtSender()
{
}



bool TCPRdtSender::getWaitingState() {
	return buf.size() == Winsize;
}




bool TCPRdtSender::send(const Message &message) {
	if (getWaitingState()) { //发送方处于等待确认状态
		return false;
	}
    //准备好需要发送的报文
	Packet packet;
    packet.seqnum = nextseq;
    packet.acknum = -1;
    packet.checksum = 0;
    memcpy(packet.payload,message.data,sizeof(message.data));
    packet.checksum = pUtils->calculateCheckSum(packet);

    //缓冲区为空时就需要开启定时器
    if(buf.size() == 0)
        pns->startTimer(SENDER,Configuration::TIME_OUT,packet.seqnum);
    pns->sendToNetworkLayer(RECEIVER,packet);

    //推入缓冲区，更新右端
    buf.push_back(packet);
    nextseq = (nextseq + 1) % SeqNum;

    pUtils->printPacket("发送方发送报文", packet);
    printf("发送方窗口:[ ");
    for (int i = 0; i < buf.size(); i++) {
        printf("%d ", (send_base + i) % SeqNum);
    }
    printf("]\n");

    return true;
}

void TCPRdtSender::receive(const Packet &ackPkt) {
	if(send_base == nextseq)
        return;
    int checkSum = pUtils->calculateCheckSum(ackPkt);
    int offset_ack = (ackPkt.acknum - send_base + SeqNum) % SeqNum;
    if(checkSum == ackPkt.checksum && offset_ack <= buf.size() && offset_ack > 0){
        pUtils->printPacket("发送方正确收到确认", ackPkt);
        //重置重复收到确认的计数
        repeat_cnt = 0;
        //停止计时器
        pns->stopTimer(SENDER,send_base);
        while(send_base != ackPkt.acknum){
            buf.pop_front();
            send_base = (send_base + 1) % SeqNum;
        }

        printf("发送方窗口:[ ");
        for (int i = 0; i < buf.size(); i++) {
            printf("%d ", (send_base + i) % SeqNum);
        }
        printf("]\n");

        if(buf.size())
            pns->startTimer(SENDER,Configuration::TIME_OUT,send_base);
    }else if(checkSum != ackPkt.checksum)
        pUtils->printPacket("发送方没有正确收到该报文确认,数据校验错误", ackPkt);
    else {
        printf("重复收到报文\n");
        //重复收到确认报文
        repeat_cnt++;
        //快速发送
        if(repeat_cnt == 3){
            pUtils->printPacket("启动快速重传", buf.front());
            pns->stopTimer(SENDER,send_base);
            pns->startTimer(SENDER, Configuration::TIME_OUT,send_base);
            repeat_cnt = 0;//重置
            pns->sendToNetworkLayer(RECEIVER,buf.front());
        }
    }
}

void TCPRdtSender::timeoutHandler(int seqNum) {
	//唯一一个定时器,无需考虑seqNum
	pUtils->printPacket("发送方定时器时间到，重发序号最小的报文", buf.front());
	pns->stopTimer(SENDER,seqNum);
	pns->startTimer(SENDER, Configuration::TIME_OUT,seqNum);
	pns->sendToNetworkLayer(RECEIVER, buf.front());
}
