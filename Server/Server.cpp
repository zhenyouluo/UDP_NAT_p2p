/*
*		P2P跨局域网通信方案
*		-------------------------------
*		主要知识点：NAT穿透，Socket
*		其他知识点：链表，多线程
*		-------------------------------
*		作者：Chife_Wu	github：https://github.com/CHIFCOOK/
*/

#include "stdafx.h"

//欢迎
void welcome();

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
				//删除结点
				cout << " Logout successfully" << endl;
				break;

			case GET_ALL_USERS:
				//发送用户链表
				system("CLS");
				available_client.print(head);
				break;
				
			case 0:
				cout << "bad input" << endl;
				if (available_client.sendMessage(recvMsg->ip, "FAIL!!") == false)		//此处有bug（sendmessage）
				{
					cout << "sendMessage fail!" << endl;
				}
				break;
			}
		}
	}

	return 0;
}



void welcome()
{
	printf("==========================================\n");
	printf("=========    WRITTEN BY CHIFE    =========\n");
	printf("==========================================\n");
}
