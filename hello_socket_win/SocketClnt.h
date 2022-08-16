#pragma once
using namespace std;
#include"MyDebug.h"


#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll


int main_socket_clnt_win(char* ip, int port);

inline int main_socket_clnt_win(char* ip, int port)
{
	int wsaStartup;
	WORD wVersionRequest = MAKEWORD(2, 2);//版本号
	WSADATA wsaData;//
	wsaStartup = WSAStartup(wVersionRequest, &wsaData);
	if (wsaStartup == 0)
	{
		Done("WSAStartup");
	}
	else
		ThrowError("WSAStartup");


	//Socket
		/*
		PF_ INET	IPv4互联网协议族
		PF_ INET6	IPv6互联网协议族
		PF LOCAL	本地通信的UNIX协议族
		PF PACKET	底层套接字的协议族
		PF_ IPX		IPX Novell协议族
		*/
		/*
		SOCK_STREAM	面向连接的套接字
		SOCK_DGRAM	面向消息的套接字
		*/
	int domin;
	int type;
	int protocol;
	domin = PF_INET;
	type = SOCK_STREAM;
	protocol = IPPROTO_TCP;

	int i = 0;
	while (1) {
		SOCKET hs;
		hs = socket(domin, type, protocol);
		if (hs != INVALID_SOCKET)
		{
			Done("socket");
		}
		else
			ThrowError("socket");
		//int udp_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//Socket

		//char* ip = "124.221.137.37";//INADDR_ANY 本机ip
		//int port = 5050;


		sockaddr_in socaddr;
		memset(&socaddr, 0, sizeof(socaddr));
		socaddr.sin_family = AF_INET;
		socaddr.sin_port = htons(port);
		inet_pton(socaddr.sin_family, ip, (void*)(&socaddr.sin_addr));
		//connect
		int flag_connect = connect(hs, (SOCKADDR*)&socaddr, sizeof(socaddr));
		if (flag_connect == 0)
		{
			Done("connect");
		}
		else
		{
			ThrowError("connect");
		}
		//connect
		int flag;
		while (1) {
			char message[30];
			int flag_recv = recv(hs, message, sizeof(message) - 1, 0);
			if (flag_recv != -1)
			{
				Done("recv");
			}
			else
			{
				ThrowError("recv");
			}

			cout <<"message from server:" << message << endl;

			i++;
			cout <<"相应次数：" << i << endl;
			cout << "继续输入1" << endl;
			cin >> flag;
			if (flag == 1)
			{
			}
			else
			{
				ThrowError("cin");
			}
		}
		closesocket(hs);
	}



	//Winsock库注销
	WSACleanup();
	//成功时返回0，失败时返回SOCKET_ ERROR。
	return 0;
}