// Server.cpp : �������̨Ӧ�ó������ڵ㡣
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
	ClientNodep clientNode = nullptr;
	while (true)
	{
		stMessagep recvMsg = new stMessage;

		recvMsg = available_client.recvMessage(recvMsg);
		if (recvMsg == nullptr)
		{
			cout << "Receive fail !!!" << endl;
			continue;
		}

		switch (available_client.stagement(recvMsg))
		{
		case LOGIN:
			recvMsg = available_client.recvMessage(recvMsg);
			if (recvMsg == nullptr)
			{
				cout << "Receive fail !!!" << endl;
				break;
			}
			else
			{
				clientNode = new ClientNode;
				clientNode = available_client.Create(recvMsg);
				if (clientNode == nullptr)
				{
					cout << "create fail !!!" << endl;
				}
				else
				{
					system("CLS");
					cout << clientNode->id;
					head = available_client.insert_tail(clientNode);
					if (head == nullptr)
					{
						cout << " Login fail!!" << endl;
					}
					else
					{
						cout << " login successfully!!" << endl;
					}
				}

			}
			break;

		case LOGOUT:
			cout << " Logout successfully" << endl;
			break;

		case GET_ALL_USERS:
			system("CLS");
			available_client.print(head);
			break;

		case 0:
			available_client.sendMessage(recvMsg->ip, "FAIL!!");
			break;
		}
	}

	return 0;
}