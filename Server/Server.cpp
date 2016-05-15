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
	ClientNodep clientNode = nullptr;
	stMessagep recvMsg = nullptr;
	while (true)
	{
		recvMsg = new stMessage;
		//阻塞
		recvMsg = available_client.recvMessage(recvMsg);

		if (recvMsg == nullptr)
		{
			cout << "Receive fail !!!" << endl;
			continue;
		}


		else
		{
			//用线程处理

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
				cout << "bad input" << endl;
				if (available_client.sendMessage(recvMsg->ip, "FAIL!!") == false)
				{
					cout << "sendMessage fail!" << endl;
				}
				break;
			}
		}
	}

	return 0;
}