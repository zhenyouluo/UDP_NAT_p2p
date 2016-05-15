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

	return true;
}

bool Client::sendMessage(char* ip, char* msg)
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

	if (SOCKET_ERROR == bind(sockSrv, (SOCKADDR*)&addrServ, sizeof(SOCKADDR)))
	{
		cout << "Could not Bind:" << WSAGetLastError();
		closesocket(sockSrv);
		WSACleanup();
		return nullptr;
	}

	SOCKADDR_IN  addrClient;
	int length = sizeof(SOCKADDR);


	if (sendto(sockSrv, msg, strlen(msg) + 1, 0, (SOCKADDR*)&addrClient, length) < 0)
	{
		cout << "Could not send to Client:" << WSAGetLastError();
		closesocket(sockSrv);
		WSACleanup();
	}

	else
	{
		cout << "Send successfully" << endl;
	}


	closesocket(sockSrv);
	WSACleanup();
	return true;
}

stMessagep Client::recvMessage(stMessagep msg)
{
	if (initWinSock() == false)
	{
		return nullptr;
	}

	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN  addrServ;
	addrServ.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(8880);

	if (SOCKET_ERROR == bind(sockSrv, (SOCKADDR*)&addrServ, sizeof(SOCKADDR)))
	{
		closesocket(sockSrv);
		WSACleanup();
		cout << "Could not Bind:" << WSAGetLastError();
		return nullptr;
	}

	SOCKADDR_IN  addrClient;
	int length = sizeof(SOCKADDR);

	msg->message = new char[20];
	cout << "Receiving......" << endl;
	if (recvfrom(sockSrv, msg->message, 100, 0, (SOCKADDR*)&addrClient, &length) < 0)
	{

		cout << "Could not receive from Client:" << WSAGetLastError();
		closesocket(sockSrv);
		WSACleanup();
		return nullptr;
	}
	else
	{
		msg->ip = inet_ntoa(addrClient.sin_addr);
		cout << msg->ip << ":" << msg->message << endl;
	}

	closesocket(sockSrv);
	WSACleanup();

	return msg;
}

ClientNodep Client::Create(stMessagep msg)
{
	if (msg == nullptr)
	{
		delete msg;
		return nullptr;
	}
	else
	{
		node = new ClientNode;
		node->id = msg->message;
		node->ip = msg->ip;
		node->next = nullptr;
		node->port = 8880;
	}
	return node;
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

int Client::stagement(stMessagep temp)
{

	if (temp == nullptr)
	{
		return 0;
	}

	if (0 == strcmp(temp->message, "login"))
	{
		return LOGIN;
	}

	if (0 == strcmp(temp->message, "logout"))
	{
		return LOGOUT;
	}

	if (0 == strcmp(temp->message, "ls"))
	{
		return GET_ALL_USERS;
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
			cout << "----------------------" << endl;
			cout << "UserID:" << temp->id << endl
				<< "Address:" << temp->ip << ":" << temp->port << endl;
			temp = temp->next;
		}
		cout << "----------------------" << endl
			<< "online client(s):" << count << endl
			<< "----------------------" << endl;

	}
}