#pragma once


typedef struct stMessage
{
	char* ip = nullptr;
	char* message = nullptr;
}*stMessagep;

typedef struct ClientNode
{
	char* ip = nullptr;
	char* id = nullptr;
	unsigned short port = 0;
	ClientNode* next = nullptr;
}*ClientNodep;


class Client
{
public:
	ClientNodep Create(ClientNodep);
	ClientNodep insert_tail(ClientNodep);
	stMessagep recvMessage();
	int stagement();
	void print(ClientNodep);
protected:
	bool initWinSock();
private:
	ClientNodep head = nullptr;
	stMessagep msg = nullptr;
	int err = 0;
};

