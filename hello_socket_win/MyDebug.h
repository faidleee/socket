#pragma once
#include<iostream>
using namespace std;
void Done(char* message)
{
	cout << message << '\t' << "Done" << endl;
}
void ThrowError(char* message)
{
	cout << message << '\t' << "Error" << endl;
	exit(1);
}
void HsGuide()
{
	cout << "ÊäÈë¸ñÊ½£º" << "ÎÄ¼þ" << '\t' << "ip" << '\t' 
	<< "port" << '\t' << "mode" << endl;
	cout << "mode:"<<endl<<"1:server"<<endl<<"2:client" << endl;
	cout << "example:" << "./Winsock 0.0.0.0 2000 1" << endl;

}




