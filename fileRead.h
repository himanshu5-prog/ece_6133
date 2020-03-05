#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<bits/stdc++.h>
#include<string>
using namespace std;

void fileRead(const string file_name,int &net_count, int &cell_count, vector<int> net_list[])
{
	ifstream file;
	//file.open("test.txt");
	file.open(file_name);
	string p = "";
	if(!file.is_open())
	{
		cout<<"Can't open the file"<<endl;
		return;
	}
	//cout<<"File is opened";
	int b,line_number=0;
	string word;
	int count=0;
	int count_1=0;
	while(getline(file, word))
	{
		string temp;
		//cout<<word<<endl;
		line_number++;
		//cout<<"Line: "<<line_number<<endl;
		//count = 0;
		//b = atoi(word.c_str());
		//cout<<"word: "<<word<<endl;
		 stringstream iss(word);
		 while(iss >> temp)
		 {
		 	//cout<<temp<<" ";
		 	
		 	b = atoi(temp.c_str());
		 	//cout<<b<<endl;
		 	if(count==0)
		 	{
		 		net_count = b;
		 		//cout<<net_count<<endl;
				count++;	
			}
			else if(count==1)
			{
				cell_count=b;
				
				count++;
			}
			else if (count==2)
			{
				net_list->resize(net_count);
				net_list[count_1].clear();
				count++;
			//	cout<<"count_1: "<<count_1<<endl;
			//	cout<<net_list->size()<<endl;
				net_list[count_1].push_back(b);
				//count_1++;
			}
			else
			{
				net_list[count_1].push_back(b);
				//count_1++;
			}
			//count_1++;
		 	//cout<<b<<" ";
		 	//cout<<"count_1: "<<count_1<<endl;
		 }
		 //cout<<"count_1: "<<count_1<<endl;
		 //print_func(net_list,count_1+1);
		 if(count > 2)
		 count_1++;
		 
	
	}
	file.close();
	//cout<<"Hello";
	//print_func(net_list,net_count);
}

vector<string> 
fileRead_stage1(const string file_name)
{
	ifstream file;
	//file.open("test.txt");
	file.open(file_name);
	string p = "";
	vector<string> v;
	if(!file.is_open())
	{
		cout<<"Can't open the file"<<endl;
		return v;
	}
	//cout<<"File is opened";
	int b,line_number=0;
	string word;
	int count=0;
	int count_1=0;
	
	while(getline(file, word))
	{
		v.push_back(word);
	}
	//cout<<"size: "<<v.size();
	file.close();
	//cout<<"Hello";
	//print_func(net_list,net_count);
}

vector<int> split(const string s, char delimiter)
{
   std::vector<int> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   int b;
   while (std::getline(tokenStream, token, delimiter))
   {
   		
   	  b =  atoi(token.c_str());
      tokens.push_back(b);
   }
   return tokens;
}

unsigned int countWordsInString(std::string const& str)
{
    std::stringstream stream(str);
    return std::distance(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
}

void fileRead_stage2(vector<string> v, vector<int> &content, vector<int> &size1)
{
	string word;
	string temp;
	int count=0;
	int b;
	int count_1=0;
	vector<int> x;
	//vector<int> content;
//	vector<int> size1;
	for(int i=0;i<v.size();i++)
	{
		temp = v[i];
		size1.push_back(countWordsInString(temp));
		stringstream iss(temp);
		
		x = split(temp, ' ');
		for(int j=0;j<x.size();j++)
		{
			content.push_back(x[j]);
		}
		//cout<<x.size()<<endl;
		
	}
	cout<<content.size()<<" "<<size1[0];
	
	//return content;
	
}

