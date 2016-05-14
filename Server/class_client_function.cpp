#include "stdafx.h"
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")



bool Client::initWinSock()
{
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		cout << "WSAStartup failed with error: %d\n" << err;
		return false;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		cout << "Could not find a usable version of Winsock.dll\n" << err;
		WSACleanup();
		return false;
	}
	else
		cout << "WinSock.dll is running good\n";

	return true;
}

stMessagep Client::recvMessage()
{
	if (initWinSock() == false)
	{
		return nullptr;
	}

	msg = (stMessagep)malloc(sizeof(stMessage));
	if (msg == nullptr)
	{
		return nullptr;
	}


	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN  addrServ;
	addrServ.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(8880);

	bind(sockSrv, (SOCKADDR*)&addrServ, sizeof(SOCKADDR));

	SOCKADDR_IN  addrClient;
	int length = sizeof(SOCKADDR);

	msg->message = (char*)malloc(sizeof(char) * 20);

	if (recvfrom(sockSrv, msg->message, 100, 0, (SOCKADDR*)&addrClient, &length) < 0)
	{
		cout << "Could not receive from Client:" << WSAGetLastError();
		return nullptr;
	}
	else
	{
		msg->ip = inet_ntoa(addrClient.sin_addr);
	}

	closesocket(sockSrv);
	WSACleanup();

	return msg;
}

ClientNodep Client::Create(ClientNodep obj)
{
	if (obj == nullptr)
	{
		free(obj);
		return nullptr;
	}
	else
	{
		msg = (stMessagep)malloc(sizeof(stMessage));
		if (msg == nullptr)
		{
			return nullptr;
		}
		msg = recvMessage();
		if (msg != nullptr)
		{
			obj->id = msg->message;
			obj->ip = msg->ip;
			free(msg);
			obj->port = 8880;
			obj->next = nullptr;
		}

	}
	return obj;
}

ClientNodep Client::insert_tail(ClientNodep obj)
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


int Client::stagement()
{

	if (0 == strcmp(recvMessage()->message, "logout"))
	{
		return LOGOUT;
	}

	return 0;
}

void Client::print(ClientNodep obj)
{
	ClientNodep temp = nullptr;
	int count = 0;
	temp = obj;
	if (temp == nullptr)
	{
		cout << "link list is empty" << endl;
	}
	else
	{

		cout << "Client list:" << endl;
		while (temp != nullptr)
		{
			count++;
			cout << "------------------" << endl;
			cout << "UserID:" << temp->id << endl
				<< "Address:" << temp->ip << ":" << temp->port << endl;
			temp = temp->next;
		}
		cout << "online client(s):" << count << endl;
	}
}