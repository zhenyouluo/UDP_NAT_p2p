// Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h>
#include "server_define.h"
#pragma comment(lib,"ws2_32.lib")


bool initWinSock()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		/* Tell the user that we could not find a usable */
		/* Winsock DLL.                                  */
		cout << "WSAStartup failed with error: %d\n" << err;
		return false;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		cout << "Could not find a usable version of Winsock.dll\n" << err;
		WSACleanup();
		return false;
	}
	else
		cout << "WinSock.dll is running good\n";

	return true;
}




ClientNodep connection(ClientNodep obj)
{
	if (obj == nullptr)
	{
		free(obj);
		return nullptr;
	}
	else
	{
		obj->port = 8880;
		obj->next = nullptr;
	}

	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN  addrServ;
	addrServ.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(8880);

	bind(sockSrv, (SOCKADDR*)&addrServ, sizeof(SOCKADDR));

	SOCKADDR_IN  addrClient;
	int length = sizeof(SOCKADDR);

	recvBuff = (char*)malloc(sizeof(char) * 20);

	if (recvfrom(sockSrv, recvBuff, 100, 0, (SOCKADDR*)&addrClient, &length) < 0)
	{
		Error = WSAGetLastError();
		closesocket(sockSrv);
		WSACleanup();
	}


	obj->ip = inet_ntoa(addrClient.sin_addr);
	obj->username = recvBuff;
	cout << "recvBuff:" << recvBuff << endl;
	recvBuff = nullptr;

	closesocket(sockSrv);

	WSACleanup();

	return obj;
}



ClientNodep insert_tail(ClientNodep obj)
{
	if (obj == nullptr)
	{
		return head;
	}

	if (head == nullptr)
	{
		head = obj;
	}
	else
	{
		ClientNodep temp = nullptr;
		temp = head;		//用temp避免修改head所保存的值
		while (temp->next != nullptr)		//遍历到最后一个结点
		{
			temp = temp->next;
		}

		obj->next = nullptr;		//确保即将插入的结点指针为空
		temp->next = obj;		//将新结点插入到尾部

	}

	return head;
}


void print(ClientNodep obj, int count)
{
	ClientNodep temp = nullptr;
	count = 0;
	temp = obj;
	if (temp == nullptr)
	{
		cout << "link list is empty" << endl;
	}

	while (temp != nullptr)
	{
		count++;
		cout << temp->username << "	" << endl
			<< temp->ip << " " << temp->port << endl;
		temp = temp->next;
		cout << "-------" << endl;
	}
	cout << "online client(s):" << count << endl;
}

int main()
{
	int node_count = 0;
	int id = 0;
	ClientNodep a = nullptr;
	while (true)
	{
		if (initWinSock() == false)
		{
			return 1;
		}


		ClientNodep newClientnode = (ClientNodep)malloc(sizeof(ClientNode));
		if (newClientnode == nullptr)
		{
			free(newClientnode);
			return 1;
		}

		a = insert_tail(connection(newClientnode));

		cout << "-------------------------------------" << endl;
		print(a, node_count);


	}

	return 0;
}