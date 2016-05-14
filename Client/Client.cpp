// Client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h>
#include <iostream>
#include "client_define.h"

#pragma comment(lib,"ws2_32.lib")


using namespace std;


int Error = 0;



bool InitWinsock(int _port, char* ip)
{
	WSADATA wsaData;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		Error = WSAGetLastError();
		WSACleanup();
		return false;
	}

	if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
	{
		Error = WSAGetLastError();
		WSACleanup();
		return false;
	}


	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

	SOCKADDR_IN  addrServ;
	addrServ.sin_addr.S_un.S_addr = inet_addr(ip);
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(_port);


	cin >> sendBuff;
	if (sendto(sockClient, sendBuff, strlen(sendBuff) + 1, 0, (SOCKADDR*)&addrServ, sizeof(SOCKADDR)) < 0)
	{
		Error = WSAGetLastError();
		closesocket(sockClient);
		WSACleanup();
	}

	else
	{
		cout << "Send successfully" << endl;
	}
	closesocket(sockClient);

	system("PAUSE");
	WSACleanup();

	return true;
}

int main()
{
	char ip[13] = "127.0.0.1";
	cout << "Server address:";
	cout << ip << endl;
	cout << "Please input your account:";
	if (InitWinsock(8880, ip) == false)
	{
		cout << Error << endl;
	}


	return 0;
}

