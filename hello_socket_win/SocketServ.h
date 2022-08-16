#pragma once
using namespace std;
#include <string>
#include"MyDebug.h"

#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll


void ThrowError(char* message);
void Done(char* message);
int main_socket_serv_win(char* ip, int port);

/*
* 宏翻译
* WORD				unsigned short
*
*
*/
int main_socket_serv_win(char* ip, int port)
{




	//Winsock库初始化
		//进行Winsock编程时，
		//首先必须调用WSAStartup函数,
		//设置程序中用到的Winsock版本,并初
		//始化相应版本的库。
		/*
		int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
		成功时返回0,失败时返回非零的错误代码值。
		wVersionRequested		程序员要用的Winsock版本信息。
		lpWSAData				WSADATA结构体变量的地址值。
		*/
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
		sa_family_t sin_family;		//地址族( Address Family )
		uint16_t	sin_port;		//16位TCP/UDP端口号
		struct	in_addr	sin_addr;	//32位IP地址
		char	sin_zero[8];		//不使用.
	};
	struct in_addr{

	In_addr_t s_addr; //32 位IPv4 地址

	}
	*/

	/*
	地址族(Address Family)		含义
	AF_INET						IPv4网络协议巾使用的地址族
	AF_INET6					IPv6网络协议中使用的地址族
	AF LOCAL					本地通信中采用的UNIX协议的地址族
	*/
	//char* ip = "124.221.137.37";//INADDR_ANY 本机ip
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
						成功时返回0 ，失败时返回-1
						sock
						传递描述符套接字参数成为服务器端
						套接字(监听套接字)
						backlog
						连接请求等待队列( Queue )的长度,表示最多连接请求进入队列
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
			成功时返回创建的套接字文件描述符，失败时返回-1

			sock
			服务器套接字的文件描述符
			addr
			保存发起连接请求的客户端地址信息的变量地址值，调用函数后向传递来的地址
			充客户端地址信息
			addrlen
			第二个参数addr结构体的长度,但是存有长度的变量地址。
			函数调用完成后，该变量即被填入客户端地址长度。
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





	//Winsock库注销
	WSACleanup();
	//成功时返回0，失败时返回SOCKET_ ERROR。
	return 0;
}












