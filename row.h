#include<iostream>
using namespace std;

struct Row
{
	double rowPointer;
	double y_coord;
	vector<int> cell_list;
	map<int,double> x_coordinate;
	vector<int> cell_order;
};
