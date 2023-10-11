#pragma once
#include "winsock2.h"
#include <cstdio>
#include <iostream>
using namespace std;

#pragma comment(lib,"ws2_32.lib")
void sendHead(char* filename, char* extname, SOCKET s);
void sendData(char* filename, SOCKET s);

int main() {
    system("chcp 65001");
    WSADATA wsaData;

    int nRc = WSAStartup(0x0202, &wsaData); //初始化Winsock
    if (nRc) {
        printf("Winsock初始化失败!\n");
        WSAGetLastError();
        return -1;
    }
    else if (wsaData.wVersion != 0x0202) {
        printf("Winsock版本不正确!\n");
        WSAGetLastError();
        return -1;
    }
    else printf("Winsock初始化成功!\n");

    SOCKET srvSocket;
    sockaddr_in srvAddr;
    srvSocket = socket(AF_INET, SOCK_STREAM, 0);  //创建一个监听socket
    if (srvSocket != INVALID_SOCKET) printf("Socket创建成功!\n");
    else {
        printf("Socket创建失败!\n");
        WSAGetLastError();
        return -1;
    }
    printf("----------------------------------------------\n");

    int srvPort;
    char srvIP[20];
    char fileAddr[50], fileName[50]; //fileName为输入主目录的副本
    printf("请输入监听IP地址：");
    scanf("%s", srvIP);
    printf("请输入监听端口号："); //置IP和端口号，以及主目录路径
    scanf("%d", &srvPort);
    printf("请输入主目录：");
    scanf("%s", fileAddr);
    printf("----------------------------------------------\n");

    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port = htons(srvPort);
    srvAddr.sin_addr.s_addr = inet_addr(srvIP);

    nRc = bind(srvSocket, (sockaddr*)&srvAddr, sizeof(srvAddr));  //监听绑定
    if (nRc != SOCKET_ERROR)
        printf("Socket绑定成功!\n");
    else {
        printf("Socket绑定失败!\n");
        WSAGetLastError();
        return -1;
    }
    nRc = listen(srvSocket, 5);  //设置等待连接状态
    if (nRc != SOCKET_ERROR)
        printf("设置等待连接状态成功!\n");
    else {
        printf("设置等待连接状态失败!\n");
        WSAGetLastError();
        return -1;
    }


    while(true){
        sockaddr_in conAddr;
        conAddr.sin_family = AF_INET;
        int addrLen = sizeof(conAddr);
        SOCKET conSocket = accept(srvSocket,(sockaddr*)&conAddr,&addrLen);
        printf("----------------------------------------------\n");
        if(conSocket != INVALID_SOCKET)
            printf("Socket与客户连接成功!\n");
        else{
            printf("Socket与客户连接失败!\n");
            WSAGetLastError();
            continue;
        }
        printf("客户端IP地址：%s\n", inet_ntoa(conAddr.sin_addr));
        printf("客户端端口号：%u\n", htons(conAddr.sin_port));

        char rcvData[2000];
        int dataLen;
        dataLen = recv(conSocket,rcvData,sizeof(rcvData),0);
        if(dataLen != SOCKET_ERROR)
            printf("接收数据成功!\n");
        else{
            printf("接收数据失败!\n");
            WSAGetLastError();
            continue;
        }
        printf("从客户端收到%d字节数据:\n %s\n", dataLen, rcvData);
        printf("----------------------------------------------\n");

        char reqName[20],extName[20];
        memset(reqName,0,sizeof(reqName));
        memset(extName,0,sizeof(extName));
        //获取文件路径
        for(int i = 0;i < dataLen;i++)
            if(rcvData[i] == '/') {
                for (int j = 0; rcvData[i] != ' '; i++, j++)
                    reqName[j] = rcvData[i];
                break;
            }
        //获取文件后缀
        for(int i = 0;i < dataLen;i++)
            if(rcvData[i] == '.'){
                i++;
                for(int j = 0;rcvData[i] != ' ';i++,j++)
                    extName[j] = rcvData[i];
                break;
            }

        strcpy(fileName, fileAddr);
        printf("请求文件名：%s\n", reqName);
        reqName[0] = '\\';
        strcat(fileName, reqName);
        printf("完整路径：%s\n", fileName);
        sendHead(fileName, extName, conSocket); //发送首部
        sendData(fileName, conSocket); //发送实体
        printf("----------------------------------------------\n\n");

        closesocket(conSocket);
    }

    closesocket(srvSocket);
    WSACleanup();
    return 0;
}

void sendHead(char* filename, char* extname, SOCKET s) {
    char content_Type[20] = ""; //设置content-type

    if (strcmp(extname, "html") == 0) strcpy(content_Type, "text/html");
    if (strcmp(extname, "gif") == 0) strcpy(content_Type, "image/gif");
    if (strcmp(extname, "jpg") == 0) strcpy(content_Type, "image/jpeg");
    if (strcmp(extname, "jpeg") == 0) strcpy(content_Type, "image/jpeg");
    if (strcmp(extname, "png") == 0) strcpy(content_Type, "image/png");

    //设置资源类型
    char sendContent_Type[40] = "Content-Type: ";
    strcat(sendContent_Type, content_Type);
    strcat(sendContent_Type, "\r\n");

    const char* ok_find = "HTTP/1.1 200 OK\r\n"; //200 OK
    const char* not_find = "HTTP/1.1 404 NOT FOUND\r\n"; //404 Not Found

    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) { //404 无法查找到文件
        if (send(s, not_find, strlen(not_find), 0) == SOCKET_ERROR) {
            printf("发送失败！\n");
            return;
        }
        printf("404 客户端请求文件查找失败！\n");
    }
    else { //200 文件查找成功
        if (send(s, ok_find, strlen(ok_find), 0) == SOCKET_ERROR) {
            printf("发送失败！\n");
            return;
        }
        printf("200 客户端请求文件查找成功！\n");
    }

    if (send(s, sendContent_Type, strlen(sendContent_Type), 0) == SOCKET_ERROR) {
        printf("发送失败！\n");
        return;
    }
    if (send(s, "\r\n", 2, 0) == SOCKET_ERROR) {
        printf("发送失败！\n");
        return;
    }
    return;
}

void sendData(char* filename, SOCKET s) {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) return;
    fseek(fp, 0L, SEEK_END);
    int dataLen = ftell(fp);  //计算文件字节数
    char* p = (char*)malloc(dataLen + 1);
    fseek(fp, 0L, SEEK_SET);
    fread(p, dataLen, 1, fp);
    if (send(s, p, dataLen, 0) == SOCKET_ERROR) {
        printf("发送失败！\n");
    }
    return;
}