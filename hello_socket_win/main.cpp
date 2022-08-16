#include "SocketServ.h"
#include"SocketClnt.h"
int main(int argc, char* argv[])
{
	if (argc == 4) {
		//cout << "ip port" << endl;
		cout << "ip:" << argv[1] << endl;
		cout << "port:" << argv[2] << endl;
		//1选择服务端 0选择客户端
		if (atoi(argv[3]) == 0)
		{
			cout << "mode:" << "client" << endl;
			main_socket_clnt_win(argv[1], atoi(argv[2]));
		}
		else if (atoi(argv[3]) == 1) {
			cout << "mode:" << "server" << endl;
			 main_socket_serv_win(argv[1], atoi(argv[2]));
		
		}
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