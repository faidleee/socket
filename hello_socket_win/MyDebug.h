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
	cout << "输入格式：" << "文件" << '\t' << "ip" << '\t' 
	<< "port" << '\t' << "mode" << endl;
	cout << "mode:server或client" << endl;
	cout << "example:" << "./Winsock 0.0.0.0 2000 server" << endl;

}




