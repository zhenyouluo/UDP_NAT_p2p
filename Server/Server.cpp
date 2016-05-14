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
	Client avilable;
	ClientNodep head = nullptr;
	while (true)
	{
		ClientNodep newClientnode = (ClientNodep)malloc(sizeof(ClientNode));
		if (newClientnode == nullptr)
		{
			free(newClientnode);
			return 1;
		}

		head = avilable.Create(newClientnode);
		head = avilable.insert_tail(head);
		avilable.print(head);

		cout << "========================================" << endl << endl;

	}

	return 0;
}