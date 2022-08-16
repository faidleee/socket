#pragma once
using namespace std;
#include"MyDebug.h"


#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll


int main_socket_clnt_win(char* ip, int port);

inline int main_socket_clnt_win(char* ip, int port)
{
	int wsaStartup;
	WORD wVersionRequest = MAKEWORD(2, 2);//�汾��
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
		PF_ INET	IPv4������Э����
		PF_ INET6	IPv6������Э����
		PF LOCAL	����ͨ�ŵ�UNIXЭ����
		PF PACKET	�ײ��׽��ֵ�Э����
		PF_ IPX		IPX NovellЭ����
		*/
		/*
		SOCK_STREAM	�������ӵ��׽���
		SOCK_DGRAM	������Ϣ���׽���
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

		//char* ip = "124.221.137.37";//INADDR_ANY ����ip
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
			cout <<"��Ӧ������" << i << endl;
			cout << "��������1" << endl;
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



	//Winsock��ע��
	WSACleanup();
	//�ɹ�ʱ����0��ʧ��ʱ����SOCKET_ ERROR��
	return 0;
}