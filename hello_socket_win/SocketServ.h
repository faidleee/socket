#pragma once
using namespace std;
#include <string>
#include"MyDebug.h"

#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll


void ThrowError(char* message);
void Done(char* message);
int main_socket_serv_win(char* ip, int port);

/*
* �귭��
* WORD				unsigned short
*
*
*/
int main_socket_serv_win(char* ip, int port)
{




	//Winsock���ʼ��
		//����Winsock���ʱ��
		//���ȱ������WSAStartup����,
		//���ó������õ���Winsock�汾,����
		//ʼ����Ӧ�汾�Ŀ⡣
		/*
		int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
		�ɹ�ʱ����0,ʧ��ʱ���ط���Ĵ������ֵ��
		wVersionRequested		����ԱҪ�õ�Winsock�汾��Ϣ��
		lpWSAData				WSADATA�ṹ������ĵ�ֵַ��
		*/
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


//bind
	/*
	struct sockaddr_in
	{
		sa_family_t sin_family;		//��ַ��( Address Family )
		uint16_t	sin_port;		//16λTCP/UDP�˿ں�
		struct	in_addr	sin_addr;	//32λIP��ַ
		char	sin_zero[8];		//��ʹ��.
	};
	struct in_addr{

	In_addr_t s_addr; //32 λIPv4 ��ַ

	}
	*/

	/*
	��ַ��(Address Family)		����
	AF_INET						IPv4����Э���ʹ�õĵ�ַ��
	AF_INET6					IPv6����Э����ʹ�õĵ�ַ��
	AF LOCAL					����ͨ���в��õ�UNIXЭ��ĵ�ַ��
	*/
	//char* ip = "124.221.137.37";//INADDR_ANY ����ip
	//int port = 5050;

	sockaddr_in socaddr;
	memset(&socaddr, 0, sizeof(socaddr));
	socaddr.sin_family = AF_INET;
	socaddr.sin_port = htons(port);
	inet_pton(socaddr.sin_family, ip, (void*)(&socaddr.sin_addr));
	//socaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//socaddr.sin_addr.s_addr
	//inet_aton(ip, socaddr.sin_addr);


	bind(hs, (struct sockaddr*)&socaddr, sizeof(socaddr));
	if (hs != SOCKET_ERROR)
	{
		Done("bind");
	}
	else
		ThrowError("bind");
	//bind



	//listen
			/*
						int listen(int sock, int backlog);
						�ɹ�ʱ����0 ��ʧ��ʱ����-1
						sock
						�����������׽��ֲ�����Ϊ��������
						�׽���(�����׽���)
						backlog
						��������ȴ�����( Queue )�ĳ���,��ʾ�����������������
			*/

	int flag_listen = listen(hs, 5);

	if (flag_listen == 0)
		Done("listen");
	else
		ThrowError("listen");
	//listen

	while (1) {
		//accept
			/*
			int accept(int sock, struct sockaddr * addr, socklen_t * addrlen);
			�ɹ�ʱ���ش������׽����ļ���������ʧ��ʱ����-1

			sock
			�������׽��ֵ��ļ�������
			addr
			���淢����������Ŀͻ��˵�ַ��Ϣ�ı�����ֵַ�����ú������򴫵����ĵ�ַ
			��ͻ��˵�ַ��Ϣ
			addrlen
			�ڶ�������addr�ṹ��ĳ���,���Ǵ��г��ȵı�����ַ��
			����������ɺ󣬸ñ�����������ͻ��˵�ַ���ȡ�
			*/
		int clntserv;
		struct sockaddr_in clnt_addr;
		int clnt_addr_size = sizeof(clnt_addr);

		clntserv = accept(hs, (sockaddr*)(&clnt_addr), &clnt_addr_size);

		if (clntserv != INVALID_SOCKET)
		{
			Done("accept");
		}
		else
			ThrowError("accept");
		//accept

			//send
		char* message = "hs";
		send(clntserv, message, sizeof(message), 0);
		closesocket(clntserv);
		//send
	}

	closesocket(hs);





	//Winsock��ע��
	WSACleanup();
	//�ɹ�ʱ����0��ʧ��ʱ����SOCKET_ ERROR��
	return 0;
}












