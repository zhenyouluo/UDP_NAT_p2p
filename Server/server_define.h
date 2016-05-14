#pragma once

typedef struct ClientNode
{
	char* username = nullptr;
	char* ip = nullptr;
	unsigned short port = 0;
	ClientNode* next = nullptr;
}*ClientNodep;

typedef struct stMessage
{
	char* ip = nullptr;
	char* message = nullptr;
}*stMessagep;


class Client
{
public:
	ClientNodep Create(ClientNodep);
	ClientNodep insert_tail(ClientNodep);
	void print(ClientNodep);
protected:
	bool initWinSock();
	stMessagep transmit(stMessagep);
private:
	ClientNodep head = nullptr;
	stMessagep msg = nullptr;
	char* recvBuff = nullptr;
	int err = 0;
};

