#include "SocketServ.h"
#include"SocketClnt.h"
int main(int argc, char* argv[])
{
	cout << "ip port" << endl;
	cout << argv[1] << '\t' <<argv[2] << endl;;

	main_socket_clnt_win(argv[1], atoi(argv[2]));
	//main_socket_serv_win(argv[1], atoi(argv[2]));







	return 0;
}