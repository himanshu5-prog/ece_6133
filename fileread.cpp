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
//#include "kl_algo.h"
#include<vector>
#include<string>
#include "fm_algo.h"
using namespace std;
string file_name = "p2.hgr";
//int chip_height = 1000;
//int  chip_width = 1000;
void min_cut_placement(int cell_count, vector<Cell> &cell_list,bool p_type, int count_threshold, vector<int> cell_net_list[], vector<Cell> detailed_net_list[],
int net_count, int cut_size, vector<Cell> adjacent_list[], int max_connect, vector<Cell> &global_cell_list  )
{
	int cell_count_p1;
	int cell_count_p2;
	vector<Cell> cell_list_p1;
	vector<Cell> cell_list_p2;
	if(cell_count < 500)
	{
	//	cell_count_p1 = cell_list_p1.size();
	//	cell_count_p2 = cell_list_p2.size();
	//	cout<<"threshold sub cell list p1 size: "<<cell_count_p1<<" sub cell list p2 size: "<<cell_count_p2<<endl;
		cout<<"Threshold reached!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		return;
	}
	
//	vector<Cell> cell_list_p1;
//	vector<Cell> cell_list_p2;
	//cout<<"min cut Cell count: "<<cell_count<<endl;
//	cout<<"initial p_type: "<<p_type<<endl;
	if(p_type == 0) p_type=1;
	else p_type = 0;
	int threshold = (0.1*cell_count)+1;
//	cout<<"final p_type: "<<p_type<<endl;
	if(p_type == 0)
		cout<<"Performing horizontal cut\n";
	else 
		cout<<"Performing vertical cut\n";
	apply_FM_Algorithm(cell_list,cell_count,cell_net_list,detailed_net_list ,net_count,cut_size,adjacent_list,cut_size,max_connect,cell_list_p1,cell_list_p2,p_type,global_cell_list);
	
	//int cell_count_p1;
	//int cell_count_p2;
	
	cell_count_p1 = cell_list_p1.size();
	cell_count_p2 = cell_list_p2.size();
	cout<<"sub cell list p1 size: "<<cell_count_p1<<" sub cell list p2 size: "<<cell_count_p2<<endl;
	if(cell_count_p1)
	{
		cout<<"p1 x coord: "<<cell_list_p1[0].x_dim<<"p1 y coord: "<<cell_list_p1[0].y_dim<<endl;
	}
	
	if(cell_count_p2)
	{
		cout<<"p2 x coord: "<<cell_list_p2[0].x_dim<<"p2 y coord: "<<cell_list_p2[0].y_dim<<endl;
	}	
	
	min_cut_placement(cell_count_p1, cell_list_p1, p_type, count_threshold, cell_net_list,detailed_net_list,net_count,cut_size,adjacent_list,max_connect,global_cell_list);
	cell_list_p1.clear();
	cell_list_p1.shrink_to_fit();
	
	min_cut_placement(cell_count_p2, cell_list_p2, p_type, count_threshold, cell_net_list,detailed_net_list,net_count,cut_size,adjacent_list,max_connect,global_cell_list);
	cell_list_p2.clear();
	cell_list_p2.shrink_to_fit();
//	cell_count_p1 = cell_list_p1.size();
//	cell_count_p2 = cell_list_p2.size();
	
	//cell_list_p1.clear();
	//cell_list_p1.shrink_to_fit();
	
	//cell_list_p2.clear();
	//cell_list_p2.shrink_to_fit();
}


int main()
{
	
	int net_count;
	int cell_count;
	int temp_net_count;
	
	get_netcount_from_file(file_name,temp_net_count);
	//cout<<"extracted netcount: "<<temp_net_count<<endl;
	vector<int> net_list[temp_net_count];
	vector<string>v;
	//vector<int> content;
	vector<int> size1;
	//string file_name="biomedP.hgr";
	
	
	//v = fileRead_stage1(file_name);
	//fileRead_stage2(v,content,size1);
	fileRead(file_name,net_count, cell_count, net_list);
	
	//-----------------------------------------------------
    
    
    //int cell_last=0,cell_present=0;
    
	vector<Cell> detailed_net_list[net_count];
	
	vector<Cell> adjacent_list[cell_count];
	
	//vector<Cell> reduced_adjacent_list[cell_count];
	//vector<int> cell_net_list[cell_count];
	
	vector<int> *cell_net_list;
	cell_net_list = new vector<int>[cell_count];
//	cout<<"net_count: "<<net_count<<" cell_count: "<<cell_count<<endl;

	
	//Checking the value of net count, cell count and netlist 
	cout<<"Input file: "<<file_name<<endl;
	//cout<<"net_count: "<<net_count<<" cell_count: "<<cell_count<<endl;
	
	 //Printing netlist 
	//cout<<"netlist: "<<endl;
	//print_func_2(net_list,net_count);
	//----------------------------------------------------------
	bool cell_record[cell_count]= {false};
	
	//--Creating detailed netlist----------------------------------
	create_detailed_netlist(detailed_net_list,net_list,net_count);
	cout<<"net_count: "<<net_count<<" cell_count: "<<cell_count<<endl;
	
	//Printing detailed netlist
	//print_detailed_netlist(detailed_net_list,net_count);
	//--------------------------------------------------------------
	//Creating variable for storing weights
	//map< pair<int,int>, double> weight;
	//vector< pair <int,int > >pair_list1;
	vector<Cell> cell_list;
	vector<Cell*> cell_ptr_list;
	vector<Cell*> global_cell_list;
	//vector<int> partition_1;
	//vector<int> partition_2;
	//double external_cost=0, internal_cost=0,selfCost=0;
	int cut_size=0;
	//-----------------------------
	//create_adj_weight(adjacent_list, cell_count, detailed_net_list, net_count, weight, cell_count, pair_list1);
	//print_adj_list(adjacent_list,cell_count);
	//create_reduced_adj(adjacent_list,reduced_adjacent_list,cell_count);
	//cout<<"Reduced adj list: "<<endl;
	//print_adj_list(reduced_adjacent_list,cell_count);
	//cout<<pair_list1.size();
	//print_pair_list(pair_list1);
	//print_weight_list(pair_list1,weight);
	create_cell_net_list(detailed_net_list,net_count,cell_net_list,cell_count);
	//cout<<"Hello"<<endl;
	int max_connect  = get_max_connectivity(cell_net_list,cell_count);
	cout<<"max_connect: "<<max_connect<<endl;
	//print_cell_netlist(cell_net_list,cell_count);
	
	//Assigning partition id depending on whether cell id is odd or even-------------------------------------
	initialise(detailed_net_list,net_count,adjacent_list,cell_count);
	//cout<<"test"<<endl;
	
	//create_cell_list(cell_list,cell_count,detailed_net_list,net_count);
	create_cell_list_2(cell_list,cell_count,detailed_net_list,net_count,cell_ptr_list);
	create_global_cell_list(cell_list,global_cell_list,cell_count);
	//cout<<"cell ptr size: "<<cell_ptr_list.size()<<"cell 34: "<<cell_ptr_list[33]->cell_id<<endl;
	//vector<Cell> global_cell_list1(cell_list);
	//cout<<"cell list 300 id: "<<cell_list[300].cell_id<<" size: "<<cell_list.size()<<endl;
	//cout<<"test1"<<endl;
	//create_partition_list(partition_1,partition_2,cell_list,cell_count);
	//cout<<"test2"<<endl;
	//initialise_cell_list_fm_metric_test(cell_net_list,cell_count,cell_list,detailed_net_list,net_count,global_cell_list);
	//cout<<"test3"<<endl;
	//cout<<cell_list.size();
	//print_cell_list(cell_list);
	//print_weight_list(pair_list1,weight);
	//external and internal cost is calculated by using adjacent list
	//calculate_cost(4,cell_list,adjacent_list,cell_count,weight,external_cost,internal_cost);
	//print_adj_list(adjacent_list,cell_count);
	//print_detailed_netlist(detailed_net_list,net_count);
	//self cost is calculated by using reduced adjacent list
	//selfCost = self_cost(4,5,reduced_adjacent_list,cell_count,weight);
	//cut_size = calculate_cutsize(detailed_net_list,net_count);
	//cout<<"External_Cost: "<<external_cost<<" Internal Cost: "<<internal_cost<<" Self Cost: "<<selfCost<<" cut size:"<<cut_size<<endl;
	//cout<<"initial cut size: "<<cut_size<<endl;
	int only_net_count = only_cell(5,2,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
	int all_cell = all_present_single_partition(5,2,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
	//cout<<"only_net_count: "<<only_net_count<<" all_Cell: "<<all_cell<<endl;
	int threshold = (0.1*cell_count)+1;
	cout<<" max cell diff allowed: "<<threshold<<endl;
	//FM_Algorithm_2(cell_list,cell_count/2,cell_net_list,detailed_net_list,net_count,cut_size,threshold,adjacent_list,reduced_adjacent_list,cut_size,max_connect);
	
	//FM_Algorithm_3(cell_list,cell_count/2,cell_net_list,detailed_net_list,net_count,cut_size,threshold,adjacent_list,reduced_adjacent_list,cut_size,max_connect,0,cell_count/2);
	//FM_Algorithm_3(cell_list,cell_count/2,cell_net_list,detailed_net_list,net_count,cut_size,threshold,adjacent_list,reduced_adjacent_list,cut_size,max_connect,cell_count/2 + 1,cell_count);
	
	//if(cell_count < 10000)
	//{
	//	cout<<"cell count less than 10k\n";
	//	FM_Algorithm_3(cell_list,cell_count/4,cell_net_list,detailed_net_list,net_count,cut_size,threshold,adjacent_list,cut_size,max_connect,0,cell_count/4);
	//	FM_Algorithm_3(cell_list,cell_count/4,cell_net_list,detailed_net_list,net_count,cut_size,threshold,adjacent_list,cut_size,max_connect,cell_count/4 + 1,cell_count/2);
	//	FM_Algorithm_3(cell_list,cell_count/4,cell_net_list,detailed_net_list,net_count,cut_size,threshold,adjacent_list,cut_size,max_connect,cell_count/2 + 1,(3*cell_count)/4);
	//	FM_Algorithm_3(cell_list,cell_count/4,cell_net_list,detailed_net_list,net_count,cut_size,threshold,adjacent_list,cut_size,max_connect,((3*cell_count)/4) + 1,cell_count);
	//}
	//else if(cell_count > 10000)
	//{
	//	cout<<"cell count more than 10k\n";
		vector<Cell> global_cell_list1(cell_list);
		vector<Cell> cell_ptr_p1;
		vector<Cell> cell_ptr_p2;
		bool p_type=0; //Horizontal
	//	cout<<global_cell_list[119]->cell_id<<endl;
		//cout<<"cell location "<<global_cell_list[0]->x_dim<<endl;
		//apply_FM_Algorithm(cell_list,cell_count,cell_net_list,detailed_net_list,net_count,cut_size,adjacent_list,cut_size,max_connect,cell_ptr_p1,cell_ptr_p2,p_type,global_cell_list);
		//cout<<"size p1: "<<cell_ptr_p1.size()<<" size p2: "<<cell_ptr_p2.size()<<"x_dim: "<<cell_ptr_p2[1].x_dim<<endl;
		min_cut_placement(cell_count,cell_list,p_type,threshold,cell_net_list,detailed_net_list,net_count,cut_size,adjacent_list,max_connect,global_cell_list1);
		/*
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,cut_size,threshold,adjacent_list,cut_size,max_connect,0,cell_count/8);
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,cut_size,threshold,adjacent_list,cut_size,max_connect,cell_count/8 + 1,cell_count/4);
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,cut_size,threshold,adjacent_list,cut_size,max_connect,cell_count/4 + 1,(3*cell_count)/8);
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,cut_size,threshold,adjacent_list,cut_size,max_connect,((3*cell_count)/8) + 1,cell_count/2);
	
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,cut_size,threshold,adjacent_list,cut_size,max_connect, (cell_count/2) + 1,(5*cell_count)/8);
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,cut_size,threshold,adjacent_list,cut_size,max_connect, (5*cell_count)/8 + 1,(3*cell_count)/4);
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,cut_size,threshold,adjacent_list,cut_size,max_connect,(3*cell_count)/4 + 1, (7*cell_count)/8 );
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,cut_size,threshold,adjacent_list,cut_size,max_connect,(7*cell_count)/8 + 1,cell_count);
		*/
	//}
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
