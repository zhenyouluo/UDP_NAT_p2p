// Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void welcome()
{
	printf("==========================================\n");
	printf("=========    WRITTEN BY CHIFE    =========\n");
	printf("==========================================\n");
}


int main()
{
	welcome();
	int node_count = 0;
	Client available_client;
	ClientNodep head = nullptr;
	while (true)
	{
		//ClientNodep newClientnode = (ClientNodep)malloc(sizeof(ClientNode));
		//if (newClientnode == nullptr)
		//{
		//	free(newClientnode);
		//	return 1;
		//}

		//head = available_client.Create(newClientnode);
		//if (head == nullptr)
		//{
		//	cout << "connect fail" << endl;
		//}
		//head = available_client.insert_tail(head);
		//available_client.print(head);
		//cout << "========================================" << endl << endl;

		stMessagep recvMsg = new stMessage;
		
		recvMsg = available_client.recvMessage(recvMsg);
		if (recvMsg == nullptr)
		{
			cout << "Receive fail !!!" << endl;
			break;
		}

		switch (available_client.stagement(recvMsg))
		{
		case LOGIN:
			if (!available_client.sendMessage(recvMsg->ip, "please input your account:"))
			{
				break;
			}
			recvMsg = available_client.recvMessage(recvMsg);
			if (recvMsg == nullptr)
			{
				cout << "Receive fail !!!" << endl;
				break;
			}
			else
			{
				head = new ClientNode;
				head = available_client.Create(recvMsg);
				if (head == nullptr)
				{
					cout << "create fail !!!" << endl;
				}
				else
					cout << " Login successfully" << endl;
			}
			break;
		case LOGOUT:
			cout << " Logout successfully" << endl;
			break;
		case GET_ALL_USERS:
			available_client.print(head);
			break;
		case 0:
			cout << " FAIL !!!" << endl;
			break;
		}

	}

	return 0;
}