#include<iostream>
using namespace std;
struct Cell
{
	int cell_id;
	double weight;
	int partition_id;
	bool locked;
	bool active;
	double x_dim;
	double y_dim;
	int only_cell_net_count;
	int all_same_partition_net_count;
};
