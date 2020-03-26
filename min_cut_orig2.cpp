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
//#include "print_functions.h"
#include "create_data_structure.h"
#include "fm_algo_2.h"
//#include "kl_algo.h"
#include<vector>
#include<string>
//#include "fm_algo.h"
using namespace std;
string file_name = "structP.hgr";
string dimFIleName = "structP.dim";
//int chip_height = 1000;
//int  chip_width = 1000;

void min_cut_placement_bfs(int cell_count, vector<Cell> &cell_list,bool p_type, int count_threshold, vector<int> cell_net_list[], vector<Cell> detailed_net_list[],
int net_count, int cut_size, vector<Cell> adjacent_list[], int max_connect, vector<Cell> &global_cell_list,
double x_coord, double y_coord, double width, double height, int mode, double delta, vector<int> net_list[])
{
	queue< vector<Cell> > q_cell_list;
	
	q_cell_list.push(cell_list);
	vector<Cell> cell_list_present;
	
	vector<Cell> cell_list_p1;
	vector<Cell> cell_list_p2;
	int cell_count_present;
	int count_p_type=0;
	int limit=1;
	bool start=true;
	double x_coord1 ,y_coord1 ,width1, height1;
	x_coord1 = x_coord;
	y_coord1 = y_coord;
	width1 = width;
	height1 = height;
	int partition_id_h = 1;	
	int partition_id_v = 1;	
	int cell_count_p1, cell_count_p2;
	double x_temp,y_temp;

	double h_temp=height;
	double w_temp=width;
	while(!q_cell_list.empty())
	{
			cell_list_present = q_cell_list.front();
			q_cell_list.pop();
			
			y_temp = y_coord1;
			x_temp = x_coord1;
				
			if(count_p_type == limit)
			{
				limit = limit<<1;
				count_p_type = 0;
								
				if(p_type == 0)
				{
					p_type = 1;
					h_temp = h_temp/2;
				}
				else if(p_type == 1)
				{
					w_temp = w_temp/2;
					p_type = 0;
				}
				//cout<<"limit: "<<limit<<endl;
			}
			
			
			if(cell_list_present.size() < 5)
			{
				cout<<"Threshold reached\n";;	
			} 
			else
			{
				//if(count_p_type == 1)
				cell_count_present = cell_list_present.size();
						
				if(p_type == 0)
				{
					cout<<"Performing Horizontal cut: \n";
					/*
					if(start == true)
						start= true;
					else
					{
						 assert(cell_list_present[0].cell_id > 0);	
						if(partition_id_h == 1)
						{
							y_coord1 = cell_list_present[0].y_dim + height/4;
							height = height/2;
						}
						else if(partition_id_h == 2)
						{
							y_coord1 = cell_list_present[0].y_dim - height/4;
                                                //        height = height/2;
						}
						partition_id_h ++;
						if(partition_id_h ==3)
						{
							
							//height = height/2;
							
							partition_id_h = 1;
						}
						//y_coord2 = y_coord + height/4;
					}
					//partition_id++;
					*/
				} 
				else if(p_type == 1)
				{
					cout<<"Performing Vertical cut: \n";
				/*	
					if(start == true)
						start = true;
					
					else
					{
						assert(cell_list_present[0].cell_id > 0);
						if(partition_id_v == 1)
						{
							x_coord1 = cell_list_present[0].x_dim  - width/4;
							width = width/2;
						}
						else if (partition_id_v == 2)
						{
							x_coord1 = cell_list_present[0].x_dim + width/4;
                                               //       width = width/2;
						}
						partition_id_v ++;
						
                                                if(partition_id_v ==3)
                                                        partition_id_v = 1;
						//x_coord2 = x_coord + width/4; 
					}
				*/
				}
					
				
				//else if(p_type == 1)
				//cout<<"Performing Vertival cut\n";
				if(start==true)
				{
				apply_FM_Algorithm_5(cell_list_present,cell_count_present,cell_net_list,detailed_net_list ,net_count,cut_size,adjacent_list,max_connect,cell_list_p1,
		cell_list_p2,p_type,global_cell_list,
		x_coord1,y_coord1,width,height, mode, delta, net_list);
				//	apply_FM_Algorithm(cell_list_present,cell_count_present,cell_net_list,detailed_net_list ,net_count,cut_size,adjacent_list,cut_size,
				//max_connect,cell_list_p1,cell_list_p2,p_type,global_cell_list,x_coord1,y_coord1,width,height, mode, delta);
					start=false;
				}
				else if (p_type == 0)
				{
					//assert(cell_list_present[0].cell_id > 0);
					int p;
                                         for(int i=0;i<cell_list_present.size();i++)
                                        {
                                                if(cell_list_present[i].cell_id > 0)
                                                {
                                                        p = i;
                                                        break;
                                                }
                                        }
				//	h_temp = h_temp/2;		
					apply_FM_Algorithm_5(cell_list_present,cell_count_present,cell_net_list,detailed_net_list ,net_count,cut_size,adjacent_list,
					max_connect,cell_list_p1,
		cell_list_p2,p_type,global_cell_list,
		cell_list_present[p].x_dim,  cell_list_present[p].y_dim,width,h_temp, mode, delta, net_list);
					//apply_FM_Algorithm(cell_list_present,cell_count_present,cell_net_list,detailed_net_list ,net_count,cut_size,adjacent_list,
					//cut_size,max_connect,cell_list_p1,cell_list_p2,p_type,global_cell_list, cell_list_present[p].x_dim, cell_list_present[p].y_dim,
					// width, h_temp, mode, delta);
				}
				else if (p_type == 1)
				{
					int z;
					 for(int i=0;i<cell_list_present.size();i++)
					{
						if(cell_list_present[i].cell_id > 0)
						{
							z = i;
							break;
						}
					}
				//	w_temp = w_temp/2;
				apply_FM_Algorithm_5(cell_list_present,cell_count_present,cell_net_list,detailed_net_list ,net_count,cut_size,adjacent_list,max_connect,cell_list_p1,
		cell_list_p2,p_type,global_cell_list,
		cell_list_present[z].x_dim,cell_list_present[z].y_dim, w_temp, height, mode, delta, net_list);
				//	apply_FM_Algorithm(cell_list_present,cell_count_present,cell_net_list,detailed_net_list ,net_count,cut_size,adjacent_list,cut_size,
				//max_connect,cell_list_p1,cell_list_p2,p_type,global_cell_list, cell_list_present[z].x_dim, cell_list_present[z].y_dim, w_temp, height, mode, delta);
				}
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
					q_cell_list.push(cell_list_p1);
					q_cell_list.push(cell_list_p2);
					
					cell_list_p1.clear();
					cell_list_p1.shrink_to_fit();
					
					cell_list_p2.clear();
					cell_list_p2.shrink_to_fit();
					
					count_p_type++;
				
			}
	} 
	
}

void min_cut_placement(int cell_count, vector<Cell> &cell_list,bool p_type, int count_threshold, vector<int> cell_net_list[], vector<Cell> detailed_net_list[],
int net_count, int cut_size, vector<Cell> adjacent_list[], int max_connect, vector<Cell> &global_cell_list,
double x_coord, double y_coord, double width, double height, int mode, double delta, vector<int> net_list[])
{
	int cell_count_p1;
	int cell_count_p2;
	vector<Cell> cell_list_p1;
	vector<Cell> cell_list_p2;
	if(cell_count < 10)
	{
	//	cell_count_p1 = cell_list_p1.size();
	//	cell_count_p2 = cell_list_p2.size();
	//	cout<<"threshold sub cell list p1 size: "<<cell_count_p1<<" sub cell list p2 size: "<<cell_count_p2<<endl;
		cout<<"Threshold reached!!!!"<<"width: "<<width<<" height: "<<height<<endl;
		return;
	}
	
//	vector<Cell> cell_list_p1;
//	vector<Cell> cell_list_p2;
	//cout<<"min cut Cell count: "<<cell_count<<endl;
//	cout<<"initial p_type: "<<p_type<<endl;
	if(p_type == 0) p_type=1;
	else p_type = 0;
	int threshold = (0.1*cell_count)+1;
	
	double x_coord1, x_coord2, y_coord1, y_coord2;
	int h1, w1;
	
//	cout<<"final p_type: "<<p_type<<endl;
	if(p_type == 0)
		cout<<"Performing horizontal cut\n";
	else 
		cout<<"Performing vertical cut\n";
		
		apply_FM_Algorithm_5(cell_list,cell_count,cell_net_list,detailed_net_list ,net_count,cut_size,adjacent_list,max_connect,cell_list_p1,
		cell_list_p2,p_type,global_cell_list,
		x_coord,y_coord,width,height, mode, delta, net_list);
		
	//apply_FM_Algorithm(cell_list,cell_count,cell_net_list,detailed_net_list ,net_count,cut_size,adjacent_list,cut_size,max_connect,
	//cell_list_p1,cell_list_p2,p_type,global_cell_list,x_coord,y_coord,width,height, mode , delta);
	
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
	
	if(p_type ==1)
	{
		//vertical cut
		//width = width/2;
		x_coord1 = x_coord - width/4;
	//	width = width/2;
		x_coord2 = x_coord + width/4; 
		y_coord1 = y_coord;
		width = width/2;
		y_coord2 = y_coord;
	}
	else if (p_type == 0)
	{
		//Horizontal cut
		y_coord1 = y_coord - height/4;

		//height = height/2;
		y_coord2 = y_coord + height/4;
		height = height/2;
		x_coord1 = x_coord;
		x_coord2 = x_coord;
	}
	
	min_cut_placement(cell_count_p1, cell_list_p1, p_type, count_threshold, cell_net_list,detailed_net_list,net_count,cut_size,adjacent_list,
	max_connect,global_cell_list, x_coord1,y_coord1, width, height, mode, delta, net_list);
	cell_list_p1.clear();
	cell_list_p1.shrink_to_fit();
	
	min_cut_placement(cell_count_p2, cell_list_p2, p_type, count_threshold, cell_net_list,detailed_net_list,net_count,cut_size,adjacent_list,
	max_connect,global_cell_list,x_coord2,y_coord2, width, height, mode, delta, net_list);
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
    
    double *widthCell;
    widthCell = (double*) calloc(cell_count,sizeof(double));
    
    double chipHeight, chipWidth;
    
    getDimension()
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
	//bool cell_record[cell_count]= {false};
	
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
	cut_size = calculate_cutsize(detailed_net_list,net_count);
	//cout<<"External_Cost: "<<external_cost<<" Internal Cost: "<<internal_cost<<" Self Cost: "<<selfCost<<" cut size:"<<cut_size<<endl;
	cout<<"initial cut size: "<<cut_size<<endl;
	//int only_net_count = only_cell(5,2,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
	//int all_cell = all_present_single_partition(5,2,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
	//cout<<"only_net_count: "<<only_net_count<<" all_Cell: "<<all_cell<<endl;
	int threshold = (0.1*cell_count)+1;
	cout<<" max cell diff allowed: "<<threshold<<endl;
	
	
		vector<Cell> global_cell_list1(cell_list);
		vector<Cell> cell_ptr_p1;
		vector<Cell> cell_ptr_p2;
		bool p_type=0; //Horizontal
		
		double x_coord_init = chip_width/2;
		double y_coord_init = chip_height/2;
		double init_height = chip_height;
		double init_width = chip_width;
		
		int mode = 0;
		double delta=0;	
		
	//	apply_FM_Algorithm(cell_list,cell_count,cell_net_list,detailed_net_list ,net_count,cut_size,adjacent_list,cut_size,max_connect,cell_ptr_p1,
	//	cell_ptr_p2,p_type,global_cell_list1,
	//	x_coord_init,y_coord_init,init_width,init_height, mode, delta);
	
	  
		min_cut_placement(cell_count,cell_list,p_type,threshold,cell_net_list,detailed_net_list,net_count,cut_size,adjacent_list,
		max_connect,global_cell_list1,x_coord_init,y_coord_init,init_width,init_height, mode,delta,net_list);
	
		bool p_type_bfs=1;	
		
//	min_cut_placement_bfs(cell_count,cell_list,p_type_bfs,threshold,cell_net_list,detailed_net_list,net_count,cut_size,adjacent_list,
//	max_connect,global_cell_list1,x_coord_init,y_coord_init,init_width,init_height, mode,delta,net_list);
				
	/*	
		apply_FM_Algorithm_5(cell_list,cell_count,cell_net_list,detailed_net_list ,net_count,cut_size,adjacent_list,max_connect,cell_ptr_p1,
		cell_ptr_p2,p_type,global_cell_list1,
		x_coord_init,y_coord_init,init_width,init_height, mode, delta, net_list);
		
	
		update_detailed_netlist_55(cell_list,detailed_net_list,net_count);
		cout<<"\nFinal P1 Count: "<<get_partition_count_5(cell_list,1)<<" P2 Count: "<<get_partition_count_5(cell_list,2)<<
		" cut size: "<<calculate_cutsize_5(detailed_net_list,net_count)<<endl;
		
		cout<<"cell_list1 size: "<<cell_ptr_p1.size()<<" cell_list2 size: "<<cell_ptr_p2.size()<<endl;
		cout<<"cell_list p1 x_dim: "<<cell_ptr_p1[0].x_dim<<" cell_list p1 y_dim: "<<cell_ptr_p1[0].y_dim<<endl;
		cout<<"cell_list p2 x_dim: "<<cell_ptr_p2[0].x_dim<<" cell_list p2 y_dim: "<<cell_ptr_p2[0].y_dim<<endl;
	*/	
		
		
		//-------------------------------------------------------------------------------------------------------------------------------
	/*
		int **netDistribution = new int*[net_count];
		map<int,int> gain;
		for(int i=0;i<net_count;i++)
		{
			netDistribution[i] = new int [2];
			netDistribution[i][0] = 0;
			netDistribution[i][1] = 0;
		}
		create_net_distribution(net_list,netDistribution,net_count);
		//print_netDistr(netDistribution,net_count);
		calculate_initial_gain(netDistribution,net_count,gain,cell_count,cell_net_list,global_cell_list1,cell_list);
	//	cout<<"size: "<<gain.size()<<endl;
		//print_gain(gain,cell_count);
		
		int max_gain=0,max_pos=0;
		vector<int> movement;
		vector<int> movementGain;
		vector<int> movementGainSum;
		
		//print_cell_list_5(cell_list);
		//print_netDistr(netDistribution,net_count);
		//print_gain(gain,cell_count);
		vector<Cell> cell_list_old;
		
		int diff;
		
		do
		{
			cell_list_old = cell_list;
		FM_Algorithm_single_pass_3(cell_list,cell_count,cell_net_list,detailed_net_list ,net_count,adjacent_list,max_connect, 
		global_cell_list1, gain, netDistribution,movement,movementGain,movementGainSum);
		
		//print_cell_list_5(cell_list);
		for(int i=0;i<movementGainSum.size();i++)
		{
			if(i==0)
			{
				max_pos=0;
				max_gain = movementGainSum[0];
			}
			else
			{
				if(max_gain < movementGainSum[i])
				{
					max_gain = movementGainSum[i];
					max_pos = i;
				}
			}
		}
		
		cout<<"max_gain: "<<max_gain<<" max_pos: "<<max_pos<<endl;
		
		if(max_gain < 0)
			max_pos = 0;
			
		
		int cell_id2;
		int dest_p_id;
		for(int i=0; i<= max_pos;i++)
		{
			cell_id2 = movement[i];
			
			if(cell_list[cell_id2 - 1].partition_id == 1 )
			{
				cell_list[cell_id2 - 1].partition_id =2;
				global_cell_list1[cell_id2 - 1].partition_id =2;
			}
			else if(cell_list[cell_id2 - 1].partition_id == 2 )
			{
				cell_list[cell_id2 - 1].partition_id = 1;
				global_cell_list1[cell_id2 - 1].partition_id =2;
			}
		}
		
		update_detailed_netlist_55(cell_list,detailed_net_list,net_count);
		int new_cut_size = calculate_cutsize(detailed_net_list,net_count);
		cout<<"new cut size: "<<new_cut_size<<endl;
		
		update_net_distribution(cell_net_list,netDistribution,net_count,cell_count,cell_list);
		gain.clear();
		calculate_initial_gain(netDistribution,net_count,gain,cell_count,cell_net_list,global_cell_list1,cell_list);
		
		//print_gain(gain,cell_count);
		
		
		diff = cut_size - new_cut_size;
		cout<<"diff: "<<diff<<endl;
		cut_size = new_cut_size;
		movement.clear();
		movementGain.clear();
		movementGainSum.clear();
	}while(diff > 0);
	
	if(diff < 0)
	{
		cout<<"Negative diff!!\n";
		update_net_distribution(cell_net_list,netDistribution,net_count,cell_count,cell_list_old);
		update_detailed_netlist_55(cell_list_old,detailed_net_list,net_count);
		int new_cut_size = calculate_cutsize(detailed_net_list,net_count);
		cout<<"new cut size: "<<new_cut_size<<endl;
		cout<<"p1 count: "<<get_partition_count_5(cell_list_old,1)<<" p2_count: "<<get_partition_count_5(cell_list_old,2)<<endl;
	}
	
	*/
		//print_netDistr(netDistribution,net_count);
		//print_cell_list_5(cell_list);
	
	
	/*
		int cell_id2;
		int dest_p_id;
		int diff=0;
		print_gain(gain,cell_count);	
		do
		{
				FM_Algorithm_single_pass(cell_list,cell_count,cell_net_list,detailed_net_list ,net_count,cut_size,adjacent_list,cut_size,max_connect,cell_ptr_p1,
		cell_ptr_p2,p_type,global_cell_list1,
		x_coord_init,y_coord_init,init_width,init_height, mode, delta, 
		gain, netDistribution,movement,movementGain,movementGainSum);
		
		//print_cell_list_5(cell_list);
		for(int i=0;i<movementGainSum.size();i++)
		{
			if(i==0)
			{
				max_pos=0;
				max_gain = movementGainSum[0];
			}
			else
			{
				if(max_gain < movementGainSum[i] && max_gain > 0)   
				{
					max_gain = movementGainSum[i];
					max_pos = i;
				}
			}
		}
		
		cout<<"max_gain: "<<max_gain<<" max_pos: "<<max_pos<<endl;
		
		if(max_gain < 0)
			max_pos = 0;
		for(int i=0; i<= max_pos;i++)
		{
			cell_id2 = movement[i];
			
			if(cell_list[cell_id2 - 1].partition_id == 1 )
			{
				cell_list[cell_id2 - 1].partition_id =2;
				global_cell_list1[cell_id2 - 1].partition_id =2;
			}
			
			else if(cell_list[cell_id2 - 1].partition_id == 2 )
			{
				cell_list[cell_id2 - 1].partition_id = 1;
				global_cell_list1[cell_id2 - 1].partition_id =1;
			}
		}
		
		update_detailed_netlist_55(cell_list,detailed_net_list,net_count);
		int new_cut_size = calculate_cutsize(detailed_net_list,net_count);
		cout<<"new cut size: "<<new_cut_size<<endl;
		update_net_distribution(cell_net_list,netDistribution,net_count,cell_count,cell_list);
		gain.clear();	
		calculate_initial_gain(netDistribution,net_count,gain,cell_count,cell_net_list,global_cell_list1);
			print_gain(gain,cell_count);
		diff = cut_size - new_cut_size ;
		cout<<"diff: "<<diff<<endl;
		cut_size = new_cut_size;
		movement.clear();
		movementGain.clear();
		movementGainSum.clear();
		max_pos =0;
		max_gain=0;
		
		} while(diff > 0);
		
		*/
		
		
		
		unsigned int wire_len = compute_wirelength(detailed_net_list,global_cell_list1,net_count);
		
		
		cout<<"Wirelength: "<<wire_len<<endl;
		
		
		ofstream output_file;
		output_file.open("data1.csv");
		
		output_file<<"x,y\n";
		for(int i=0; i<global_cell_list1.size(); i++)
		{
			output_file<<global_cell_list1[i].x_dim<<","<<global_cell_list1[i].y_dim<<endl;
		}
		output_file.close();
		
	

	
	return 0;
	
}
