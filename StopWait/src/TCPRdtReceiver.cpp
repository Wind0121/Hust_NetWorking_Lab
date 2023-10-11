
#include "Global.h"
#include "TCPRdtReceiver.h"


TCPRdtReceiver::TCPRdtReceiver()
{
	rcv_base = 0;
    for(int i = 0;i < SeqNum;i++)
        st[i] = false;
    lastAckPkt.seqnum = -1;
    lastAckPkt.acknum = -1;
    lastAckPkt.checksum = 0;
    for(int i = 0; i < Configuration::PAYLOAD_SIZE;i++){
        lastAckPkt.payload[i] = '.';
    }
    lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}


TCPRdtReceiver::~TCPRdtReceiver()
{
}

void TCPRdtReceiver::receive(const Packet &packet) {
	int checkSum = pUtils->calculateCheckSum(packet);
    int offset_seq = (packet.seqnum - rcv_base + SeqNum) % SeqNum;
	//校验和正确且序号位于接收窗口内
	if (checkSum == packet.checksum && offset_seq < Winsize) {
		pUtils->printPacket("接收方正确收到发送方的报文", packet);

        //先接收该报文
		if(!st[packet.seqnum]){
            st[packet.seqnum] = true;
            memcpy(msgs[packet.seqnum].data,packet.payload,sizeof(packet.payload));
        }

		//判断窗口是否可以前移
        while(st[rcv_base]){
            st[rcv_base] = false;
            pns->delivertoAppLayer(RECEIVER,msgs[rcv_base]);
            rcv_base = (rcv_base + 1) % SeqNum;
        }

        //发送确认报文，采用累计确认，直接发送rcv_base
        lastAckPkt.acknum = rcv_base;
        lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
        pUtils->printPacket("接收方发送确认报文", lastAckPkt);
        pns->sendToNetworkLayer(SENDER, lastAckPkt);
	}
	else {
		if (checkSum != packet.checksum) {
			pUtils->printPacket("接收方没有正确收到发送方的报文,数据校验错误", packet);
		}
		else {
			pUtils->printPacket("接收方没有正确收到发送方的报文,报文序号不对", packet);
		}
        //都需要发送确认报文，都采用累计确认
		pUtils->printPacket("接收方重新发送上次的确认报文", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);

	}
}