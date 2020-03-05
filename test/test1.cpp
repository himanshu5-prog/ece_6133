#include<iostream>
#include<map>
using namespace std;
int main()
{
	map<pair<int,int>, int> record;
	pair<int,int> p1(1,2);
	pair<int,int> p2(1,3);
	record.insert(pair<pair<int,int>,int>(p1,3));
	record.insert(pair<pair<int,int>,int>(p2,4));
	cout<<"Before: "<<record[{1,2}]<<endl;
	record[{1,2}]+=2;
	cout<<"After: "<<record[{1,2}]<<endl;
	pair<int,int>p4(1,21);
	
	map< pair<int,int>,int > ::iterator itr;
	itr= record.find(p4);
	
	if(itr!=record.end())
	{
		cout<<"Found it baby"<<endl;
	}
	else
	{
		cout<<"can't find ;("<<endl;
	}
	return 0;
}
