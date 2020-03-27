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
#include "row.h"
#include "placementStrategy.h"
//#include "fm_algo.h"
const double cellHeight = 1.4;
const double rowHeight = 1.4;

using namespace std;
using namespace std::chrono;
string file_name = "industry3.hgr";
string dimFileName = "industry3.dim";


//---------------------------------------------------------------
//Mode: 0 (Min cut placement)
//Mode: 1 (Mincut placement with 50% window terminal propagation)
//Mode: 2 (Mincut placement with all terminal propagation)
int Mode = 2;
//---------------------------------------------------------------

//------------------------------------------------------------
//partitionStrategy: true -> BFS
//partitionStrategy: false -> DFS
bool partitionStrategy = true;
//-------------------------------------------------------------
bool debugMode = false;

int main()
{
	auto start = high_resolution_clock::now(); 
	
	int net_count;
	int cell_count;
	int temp_net_count;
	
	get_netcount_from_file(file_name,temp_net_count);
	vector<int> net_list[temp_net_count];
	vector<string>v;
	vector<int> size1;
	bool hgrFileStatus= false;
	
	hgrFileStatus = fileRead(file_name,net_count, cell_count, net_list);
	
	if(hgrFileStatus == false)
	{
		cout<<"Problem processing hgr file!";
    	return 2;
	}
	cout<<"Done reading hgr file\n";
	//-----------------------------------------------------
    
    double *widthCell;
    widthCell = (double*) calloc(cell_count,sizeof(double));
    
    double chipHeight=1000, chipWidth=1000;
    int rowCount = 0;
    bool dimFileStatus=false;
    
    dimFileStatus = getDimension(dimFileName,chipWidth,chipHeight,widthCell,cell_count, rowCount);
    
    if(dimFileStatus == false)
    {
    	cout<<"Problem processing dim file!";
    	return 3;
	}
    cout<<"Done reading dim file: "<<dimFileName<<"\n";
    cout<<"Width: "<<chipWidth<<" height: "<<chipHeight<<"| standard cell row count: "<<rowCount<<endl;
    
    
	vector<Cell> detailed_net_list[net_count];
	vector<Cell> adjacent_list[cell_count];
	
	vector<int> *cell_net_list;
	cell_net_list = new vector<int>[cell_count];

	
	//Checking the value of net count, cell count and netlist 
	cout<<"Input file: "<<file_name<<endl;

	//--Creating detailed netlist----------------------------------
	create_detailed_netlist(detailed_net_list,net_list,net_count, chipWidth, chipHeight);
	cout<<"net_count: "<<net_count<<" cell_count: "<<cell_count<<endl;
	
	vector<Cell> cell_list;
	vector<Cell*> cell_ptr_list;
	vector<Cell*> global_cell_list;
	int cut_size=0;
	//-----------------------------
	create_cell_net_list(detailed_net_list,net_count,cell_net_list,cell_count);
	//cout<<"Hello"<<endl;
	int max_connect  = get_max_connectivity(cell_net_list,cell_count);
	cout<<"max_connect: "<<max_connect<<endl;

	
	//Assigning partition id depending on whether cell id is odd or even-------------------------------------
	initialise(detailed_net_list,net_count,adjacent_list,cell_count);
	//create_cell_list(cell_list,cell_count,detailed_net_list,net_count);
	create_cell_list_2(cell_list,cell_count,detailed_net_list,net_count,cell_ptr_list);
	create_global_cell_list(cell_list,global_cell_list,cell_count);
	cut_size = calculate_cutsize(detailed_net_list,net_count);
	
	cout<<"initial cut size: "<<cut_size<<endl;
	int threshold = (0.1*cell_count)+1;
	cout<<" max cell diff allowed: "<<threshold<<endl;
	
	cout<<"PART1: Spreading of cells starts\n";
	vector<Cell> global_cell_list1(cell_list);
	vector<Cell> cell_ptr_p1;
	vector<Cell> cell_ptr_p2;
	bool p_type=0; //Horizontal
		
	Row *row = new Row [rowCount];
		
	double x_coord_init = chipWidth/2;
	double y_coord_init = chipHeight/2;
	double init_height = chipHeight;
	double init_width = chipWidth;
		
	int mode = 0;
	mode =Mode;
	assert(mode >=0 && mode <= 2);
	double delta=0;	
	bool strat = false;
	strat = partitionStrategy;
	bool debug_mode = false;
	debug_mode = debugMode;
		
	cout<<"Mode: "<<mode<<" DebugMode: "<<debugMode<<endl;
		///*
	if(strat == false)
	{
		cout<<"Using DFS"<<endl;
			
		min_cut_placement(cell_count,cell_list,p_type,threshold,cell_net_list,detailed_net_list,net_count,cut_size,adjacent_list,
		max_connect,global_cell_list1,x_coord_init,y_coord_init,init_width,init_height, mode,delta,net_list, chipWidth, chipHeight, debug_mode);
	}	  
	else if(strat == true)
	{
		cout<<"Using BFS"<<endl;
		bool p_type_bfs=1;	

		min_cut_placement_bfs(cell_count,cell_list,p_type_bfs,threshold,cell_net_list,detailed_net_list,net_count,cut_size,adjacent_list,
		max_connect,global_cell_list1,x_coord_init,y_coord_init,init_width,init_height, mode,delta,net_list, chipWidth, chipHeight, debug_mode);		
	}
		//-------------------------------------------------------------------------------------------------------------------------------			
	unsigned int wire_len = compute_wirelength(detailed_net_list,global_cell_list1,net_count);
	cout<<"After spreading the cells, Wirelength: "<<wire_len<<endl;	
	cout<<"PART1 ENDS: done spreading the cell\n";
	cout<<"PART2 Starts: Now placing the cells\n";
		//------------------------------------------------------
	map<int,pair<double,double>> finalPlacement;
		
	performFinalPlacement(row,rowCount,rowHeight,global_cell_list1,finalPlacement, cell_count, chipWidth, widthCell);
		
	unsigned int wl2 = compute_wirelength_2(detailed_net_list,finalPlacement,net_count);
	cout<<"After placing the cells, wirelength: "<<wl2<<endl;
	
	//Generating CSV file that has coordinate of each cell
	generateCSV(finalPlacement);
	//---------------------------------------------------
	//generateRowData(row,rowCount);
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<microseconds>(stop - start); 
	cout <<"( mode: "<<mode<< ") Time taken : "<< duration.count()/1000000 << " seconds" << endl; 
	return 0;
}
