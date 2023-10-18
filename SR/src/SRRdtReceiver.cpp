
#include "Global.h"
#include "SRRdtReceiver.h"


SRRdtReceiver::SRRdtReceiver()
{
    rcv_base = 0;
    for(int i = 0;i < 2 * Winsize;i++)
        st[i] = false;

    AckPkt.seqnum = -1;
    AckPkt.acknum = -1;
    AckPkt.checksum = 0;
    for(int i = 0; i < Configuration::PAYLOAD_SIZE;i++){
        AckPkt.payload[i] = '.';
    }
    AckPkt.checksum = pUtils->calculateCheckSum(AckPkt);
}


SRRdtReceiver::~SRRdtReceiver()
{
}

void SRRdtReceiver::receive(const Packet &packet) {
	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(packet);
    int offset_seq = (packet.seqnum - rcv_base + SeqNum) % SeqNum;
	//如果校验和正确，同时收到报文的序号在接收窗口内
	if (checkSum == packet.checksum && offset_seq < Winsize) {
		pUtils->printPacket("接收方正确收到发送方的报文", packet);

        //如果没有收到过就缓存起来
        if(st[packet.seqnum] == false) {
            memcpy(msgs[packet.seqnum].data, packet.payload, sizeof(packet.payload));
            st[packet.seqnum] = true;
        }
        printf("接收方窗口:[ ");
        for (int i = 0; i < Winsize; i++) {
            printf("%d(%d) ", (rcv_base + i) % SeqNum,st[(rcv_base + i) % SeqNum]);
        }
        printf("]\n");
        AckPkt.acknum = packet.seqnum;
        AckPkt.checksum = pUtils->calculateCheckSum(AckPkt);
        pUtils->printPacket("接收方发送确认报文", AckPkt);
        pns->sendToNetworkLayer(SENDER, AckPkt);

		if(packet.seqnum == rcv_base){//说明窗口可以前移
            while(st[rcv_base]){
                pns->delivertoAppLayer(RECEIVER,msgs[rcv_base]);
                st[rcv_base] = false;
                rcv_base = (rcv_base + 1) % SeqNum;
            }
        }
        printf("接收方窗口:[ ");
        for (int i = 0; i < Winsize; i++) {
            printf("%d(%d) ", (rcv_base + i) % SeqNum,st[(rcv_base + i) % SeqNum]);
        }
	}
	else {
		if (checkSum != packet.checksum) {
			pUtils->printPacket("接收方没有正确收到发送方的报文,数据校验错误", packet);
		}
		else {
			pUtils->printPacket("接收方已经接受过该报文", packet);
            AckPkt.acknum = packet.seqnum;
            AckPkt.checksum = pUtils->calculateCheckSum(AckPkt);
            pUtils->printPacket("接收方再次确认该报文", AckPkt);
            pns->sendToNetworkLayer(SENDER, AckPkt);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送上次的确认报文
		}

	}
}