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

stMessagep Client::transmit(stMessagep temp)
{
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
		cout << "Could not receive from Client:" << WSAGetLastError();
	}
	else
	{
		temp->ip = inet_ntoa(addrClient.sin_addr);
		temp->message = recvBuff;
	}

	closesocket(sockSrv);
	WSACleanup();

	return temp;
}

ClientNodep Client::Create(ClientNodep obj)
{
	if (initWinSock() == false)
	{
		free(obj);
		return nullptr;
	}

	if (obj == nullptr)
	{
		free(obj);
		return nullptr;
	}
	else
	{
		obj->next = nullptr;
		msg = (stMessagep)malloc(sizeof(stMessage));
		if (msg == nullptr)
		{
			return nullptr;
		}
		else
		{
			msg = transmit(msg);
		}
		obj->username = msg->message;
		obj->ip = msg->ip;
		obj->port = 8880;
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
		temp = head;		//��temp�����޸�head�������ֵ
		while (temp->next != nullptr)		//���������һ�����
		{
			temp = temp->next;
		}

		obj->next = nullptr;		//ȷ����������Ľ��ָ��Ϊ��
		temp->next = obj;		//���½����뵽β��

	}

	return head;
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
			cout << "UserID:" << temp->username << endl
				<< "Address:" << temp->ip << ":" << temp->port << endl;
			temp = temp->next;
		}
		cout << "online client(s):" << count << endl;
	}
}

