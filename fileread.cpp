#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<bits/stdc++.h>
#include<algorithm>
#include<map>
#include "cell.h" 
#include "fileRead.h"
#include "print_functions.h"
#include "create_data_structure.h"
#include "kl_algo.h"
#include<vector>
#include<string>
#include "fm_algo.h"
using namespace std;



int main()
{
	int net_count;
	int cell_count;
	vector<int> net_list[2000];
	vector<string>v;
	vector<int> content;
	vector<int> size1;
	string file_name="structP.hgr";
	
	//v = fileRead_stage1(file_name);
	//fileRead_stage2(v,content,size1);
	fileRead(file_name,net_count, cell_count, net_list);
	//-----------------------------------------------------
    
    
    
    
	vector<Cell> detailed_net_list[net_count];
	vector<Cell> adjacent_list[cell_count];
	vector<Cell> reduced_adjacent_list[cell_count];
	vector<int>  cell_net_list[cell_count];
	//Checking the value of net count, cell count and netlist 
	cout<<"net_count: "<<net_count<<" cell_count: "<<cell_count<<endl;
	
	 //Printing netlist 
	//cout<<"netlist: "<<endl;
	//print_func_2(net_list,net_count);
	//----------------------------------------------------------
	
	//--Creating detailed netlist----------------------------------
	create_detailed_netlist(detailed_net_list,net_list,net_count);
	
	//Printing detailed netlist
	//print_detailed_netlist(detailed_net_list,net_count);
	//--------------------------------------------------------------
	//Creating variable for storing weights
	map< pair<int,int>, double> weight;
	vector< pair <int,int > >pair_list1;
	vector<Cell> cell_list;
	vector<int> partition_1;
	vector<int> partition_2;
	double external_cost=0, internal_cost=0,selfCost=0;
	int cut_size=0;
	//-----------------------------
	create_adj_weight(adjacent_list, cell_count, detailed_net_list, net_count, weight, cell_count, pair_list1);
	//print_adj_list(adjacent_list,cell_count);
	create_reduced_adj(adjacent_list,reduced_adjacent_list,cell_count);
	//cout<<"Reduced adj list: "<<endl;
	//print_adj_list(reduced_adjacent_list,cell_count);
	//cout<<pair_list1.size();
	//print_pair_list(pair_list1);
	//print_weight_list(pair_list1,weight);
	create_cell_net_list(detailed_net_list,net_count,cell_net_list,cell_count);
	//print_cell_netlist(cell_net_list,cell_count);
	//START OF KL AlGORITHM-----------------------------------------------------------------------------------
	//Assigning partition id depending on whether cell id is odd or even-------------------------------------
	initialise(detailed_net_list,net_count,adjacent_list,cell_count,reduced_adjacent_list);
	create_cell_list(cell_list,cell_count,detailed_net_list,net_count);
	create_partition_list(partition_1,partition_2,cell_list,cell_count);
	//cout<<cell_list.size();
	//print_cell_list(cell_list);
	//print_weight_list(pair_list1,weight);
	//external and internal cost is calculated by using adjacent list
	calculate_cost(4,cell_list,adjacent_list,cell_count,weight,external_cost,internal_cost);
	//print_adj_list(adjacent_list,cell_count);
	//print_detailed_netlist(detailed_net_list,net_count);
	//self cost is calculated by using reduced adjacent list
	selfCost = self_cost(4,5,reduced_adjacent_list,cell_count,weight);
	cut_size = calculate_cutsize(detailed_net_list,net_count);
	//cout<<"External_Cost: "<<external_cost<<" Internal Cost: "<<internal_cost<<" Self Cost: "<<selfCost<<" cut size:"<<cut_size<<endl;
	cout<<"initial cut size: "<<cut_size<<endl;
	int only_net_count = only_cell(3,2,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
	int all_cell = all_present_single_partition(3,2,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
	cout<<"only_net_count: "<<only_net_count<<" all_Cell: "<<all_cell<<endl;
	int threshold = (0.1*cell_count)+1;
	cout<<"threshold: "<<threshold<<endl;
	FM_Algorithm(cell_list,cell_count,cell_net_list,detailed_net_list,net_count,cut_size,threshold,adjacent_list,reduced_adjacent_list,cut_size);
	//print_detailed_netlist(detailed_net_list,net_count);
	//KL_Algorithm(cell_list,adjacent_list,reduced_adjacent_list,cell_count,weight, detailed_net_list,net_count,cut_size);
//	print_detailed_netlist(detailed_net_list,net_count);
	//print_cell_list(cell_list);
	//cout<<"reduced adj list before:"<<endl;
	//print_adj_list(reduced_adjacent_list,cell_count);
	//update_partition(5,1,cell_list,detailed_net_list,adjacent_list,reduced_adjacent_list,cell_count,net_count);
	//cut_size = calculate_cutsize(detailed_net_list,net_count);
	//cout<<"New cut size: "<<cut_size;
	//cout<<"reduced adj list after"<<endl;
//	print_adj_list(adjacent_list,cell_count);
	//----------
	//vector<Cell> neighbor = report_neighbors(1,reduced_adjacent_list,cell_count);
	//print_cell_list(neighbor);
	//-----------------
	
	//print_detailed_netlist(detailed_net_list,net_count);
	//print_cell_list(cell_list);
	//print_partition_list(partition_2);
	//modify_adj_list(adjacent_list,cell_count,detailed_net_list,net_count);
	//Printing to check partition assignment------------------------------------------------------------------
	//cout<<"Adj list: "<<endl;
	//print_adj_list(adjacent_list,cell_count);
	//cout<<"Reduced adj list: "<<endl;
	//print_adj_list(reduced_adjacent_list,cell_count);
	//-------------------------------------------------------------------------------------------------------
	
	
	return 0;
	
}
