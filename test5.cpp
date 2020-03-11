#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
	vector<int> v[3];
	v[0].push_back(2);
	v[0].push_back(3);
	
	v[1].push_back(4);
	v[2].push_back(5);
	v[2].push_back(6);
	
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<v[i].size();j++)
		{
			cout<<v[i][j]<<" ";
		}
		cout<<endl;
	}
	vector<vector<int>*> ptr;
	
	ptr.push_back(&v[0]);
	ptr.push_back(&v[1]);
	ptr.push_back(&v[2]);
	
	cout<<ptr[0]<<endl;
	//cout<<sizeof(ptr[0])<<endl;
	//cout<<sizeof(v[0]);
	return 0;
}
