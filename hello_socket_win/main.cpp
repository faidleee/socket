#include "SocketServ.h"
#include"SocketClnt.h"
int main(int argc, char* argv[])
{
	if (argc == 4) {
		//cout << "ip port" << endl;
		cout << "ip:" << argv[1] << endl;
		cout << "port:" << argv[2] << endl;
		cout << "mode:" << argv[3] << endl;
		//1选择客户端 非1选择服务端
		if (argv[3] == "server") main_socket_clnt_win(argv[1], atoi(argv[2]));
		else if (argv[3] == "client") main_socket_serv_win(argv[1], atoi(argv[2]));
		else
		{
			HsGuide();
			ThrowError("argv[]");
		}
	}
	else
	{
		HsGuide();
		ThrowError("argc");
	}





	return 0;
}