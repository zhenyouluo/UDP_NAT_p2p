/*
*		P2P�������ͨ�ŷ���
*		-------------------------------
*		��Ҫ֪ʶ�㣺NAT��͸��Socket
*		����֪ʶ�㣺�������߳�
*		-------------------------------
*		���ߣ�Chife_Wu	github��https://github.com/CHIFCOOK/
*/

#include "stdafx.h"

//��ӭ
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
		//����
		recvMsg = available_client.recvMessage(recvMsg);

		if (recvMsg == nullptr)
		{
			cout << "Receive fail !!!" << endl;
			continue;
		}


		else
		{
			//���̴߳���

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
				//ɾ�����
				cout << " Logout successfully" << endl;
				break;

			case GET_ALL_USERS:
				//�����û�����
				system("CLS");
				available_client.print(head);
				break;
				
			case 0:
				cout << "bad input" << endl;
				if (available_client.sendMessage(recvMsg->ip, "FAIL!!") == false)		//�˴���bug��sendmessage��
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
