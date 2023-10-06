
#include "Global.h"
#include "GBNRdtSender.h"


GBNRdtSender::GBNRdtSender(){

}


GBNRdtSender::~GBNRdtSender(){

}



bool GBNRdtSender::getWaitingState() {
	return buf.size() == WinSize;
}




bool GBNRdtSender::send(const Message &message) {
	if (getWaitingState()) { //发送方处于等待确认状态
		return false;
	}
    //准备好需要发送的分组
    Packet packet;
    packet.acknum = -1;
    packet.seqnum = nextSeq;
    nextSeq = (nextSeq + 1) % SeqNum;//更新右端
    packet.checksum = 0;
    memcpy(packet.payload,message.data,sizeof(message.data));
    packet.checksum = pUtils->calculateCheckSum(packet);
    buf.push_back(packet);//送入缓冲区

    pUtils->printPacket("发送方发送报文", packet);
//    printf("当前的左端：%d 右端：%d\n",base,nextSeq);
    if(!timer_running){
        timer_running = true;
        pns->startTimer(SENDER, Configuration::TIME_OUT,packet.seqnum);
    }
    pns->sendToNetworkLayer(RECEIVER,packet);
    return true;
}

void GBNRdtSender::receive(const Packet &ackPkt) {
    if(base == nextSeq)//说明发送窗口中没有等待确认的分组
        return;
    //检查校验和是否正确
    int checkSum = pUtils->calculateCheckSum(ackPkt);
    int offacknum = (ackPkt.acknum - base + SeqNum) % SeqNum;
    //判断该确认是否在窗口内
    if(checkSum == ackPkt.checksum && offacknum < buf.size()){
        pUtils->printPacket("发送方正确收到确认", ackPkt);
        pns->stopTimer(SENDER,base);
        timer_running = false;
        while(base != (ackPkt.acknum + 1) % SeqNum){
            buf.pop_front();
            base = (base + 1) % SeqNum;
        }
        if (buf.size() != 0) {
            timer_running = true;
            pns->startTimer(SENDER, Configuration::TIME_OUT, this->base);//以基准包的序号开启计时器
        }
    }else if(checkSum != ackPkt.checksum)
        pUtils->printPacket("发送方没有正确收到该报文确认,数据校验错误", ackPkt);
    else
        pUtils->printPacket("发送方已正确收到过该报文确认", ackPkt);
}

void GBNRdtSender::timeoutHandler(int seqNum) {
    //重发所有发送窗口中待确认的分组
//    for(auto pt : buf) {
//        pUtils->printPacket("发送方定时器时间到，重发报文", pt);
//        printf("当前的左端：%d 右端：%d\n",base,nextSeq);
//    }
    pns->stopTimer(SENDER,seqNum);
    pns->startTimer(SENDER, Configuration::TIME_OUT,seqNum);
    for(auto pt : buf)
        pns->sendToNetworkLayer(RECEIVER,pt);

}


