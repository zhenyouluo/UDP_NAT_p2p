// Client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")


using namespace std;


int Error = 0;
char* recvBuff = nullptr;

bool initWinSock()
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

	return true;
}


bool sendMessage(int _port, char* ip, char* sendBuff)
{

	if (initWinSock() == false)
	{
		return false;
	}


	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

	SOCKADDR_IN  addrServ;
	addrServ.sin_addr.S_un.S_addr = inet_addr(ip);
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(_port);

	int len = sizeof(SOCKADDR);

	if (sendto(sockClient, sendBuff, strlen(sendBuff) + 1, 0, (SOCKADDR*)&addrServ, len) < 0)
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

	WSACleanup();

	return true;
}


bool recvMessage(int _port, char* ip)
{

	if (initWinSock() == false)
	{
		return false;
	}


	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN  addrServ;
	addrServ.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(8880);

	bind(sockSrv, (SOCKADDR*)&addrServ, sizeof(SOCKADDR));

	SOCKADDR_IN  addrClient;
	int length = sizeof(SOCKADDR);

	recvBuff = new char[20];

	if (recvfrom(sockSrv, recvBuff, 100, 0, (SOCKADDR*)&addrClient, &length) < 0)
	{
		cout << "Could not receive from Client:" << WSAGetLastError();
		closesocket(sockSrv);
		WSACleanup();
		return false;
	}
	cout << recvBuff << endl;

	closesocket(sockSrv);
	WSACleanup();

	return true;
}


int main()
{
	char sendBuff[15] = "";

	cout << "Server address:127.0.0.1" << endl;

	if (sendMessage(8880, "127.0.0.1", "login") == false)
	{
		cout << Error << endl;
	}
	//if (recvMessage(8880, "127.0.0.1") == false)
	//{
	//	cout << Error << endl;
	//}


	cin >> sendBuff;
	if (sendMessage(8880, "127.0.0.1", sendBuff) == false)
	{
		cout << Error << endl;
	}

	return 0;
}

