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