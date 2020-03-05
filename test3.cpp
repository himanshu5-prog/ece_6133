#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<bits/stdc++.h>
#include<string>
using namespace std;
int main()
{
	ifstream file;
	//file.open("test.txt");
	file.open("structP.hgr");
	string p = "";
	if(!file.is_open())
	{
		cout<<"Can't open the file"<<endl;
		return 0;
	}
	//cout<<"File is opened";
	int b,line_number=0;
	string word;
	int count=0;
	int count_1=0;
	vector<string> v;
	while(getline(file, word))
	{
		v.push_back(word);
	}
	cout<<v.size();
	
	file.close();
	return 0;
}

