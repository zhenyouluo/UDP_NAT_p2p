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
		ClientNodep newClientnode = (ClientNodep)malloc(sizeof(ClientNode));
		if (newClientnode == nullptr)
		{
			free(newClientnode);
			return 1;
		}

		head = available_client.Create(newClientnode);
		if (head == nullptr)
		{
			cout << "connect fail" << endl;
		}
		head = available_client.insert_tail(head);
		available_client.print(head);
		cout << "========================================" << endl << endl;

		switch (available_client.stagement())
		{
		case LOGOUT:
			cout << head->id << " Logout successfully" << endl;
			break;
		}
	}

	return 0;
}