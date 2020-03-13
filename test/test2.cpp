#include<iostream>
using namespace std;
double x = 500;
int main()
{
	double y= x/2;
	cout<<y<<endl;
	double diff= x - y;
	double p = 2;
	for(int i=0;i<10;i++)
	{
		 y = y - diff/2;
		 diff = x - y;
		 cout<<y<<endl;
		 p = 2*p;
	}
	return 0;
}
