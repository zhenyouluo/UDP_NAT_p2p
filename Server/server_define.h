#pragma once
const int LOGIN = 0;
const int LOGOUT = 0;

using namespace std;
int Error = 0;
int option = 0;

char* recvBuff = nullptr;

typedef struct ClientNode
{
	char* username = nullptr;
	char* ip = nullptr;
	unsigned short port = 0;
	ClientNode* next = nullptr;
}ClientNode, *ClientNodep;

ClientNodep head = nullptr;
