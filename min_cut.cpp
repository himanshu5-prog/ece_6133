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
//#include "fm_algo.h"
const double cellHeight = 1.4;
const double rowHeight = 1.4;

using namespace std;
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
//int chip_height = 1000;
//int  chip_width = 1000;

void min_cut_placement_bfs(int cell_count, vector<Cell> &cell_list,bool p_type, int count_threshold, vector<int> cell_net_list[], vector<Cell> detailed_net_list[],
int net_count, int cut_size, vector<Cell> adjacent_list[], int max_connect, vector<Cell> &global_cell_list,
double x_coord, double y_coord, double width, double height, int mode, double delta, vector<int> net_list[], double chipWidth, double chipHeight, bool debug)
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
				//cout<<"Threshold reached"<<" height: "<<h_temp<<" width: "<<w_temp<<endl;	
			} 
			else
			{
				//if(count_p_type == 1)
				cell_count_present = cell_list_present.size();
						
				if(p_type == 0)
				{
					cout<<"Performing Horizontal cut: \n";
				} 
				else if(p_type == 1)
				{
					cout<<"Performing Vertical cut: \n";
				}
					
				
				//else if(p_type == 1)
				//cout<<"Performing Vertival cut\n";
				if(start==true)
				{
				apply_FM_Algorithm_5(cell_list_present,cell_count_present,cell_net_list,detailed_net_list ,net_count,cut_size,adjacent_list,max_connect,cell_list_p1,
		cell_list_p2,p_type,global_cell_list,
		x_coord1,y_coord1,width,height, mode, delta, net_list, chipWidth, chipHeight, debug);
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
		cell_list_present[p].x_dim,  cell_list_present[p].y_dim,width,h_temp, mode, delta, net_list, chipWidth, chipHeight, debug);
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
		cell_list_present[z].x_dim,cell_list_present[z].y_dim, w_temp, height, mode, delta, net_list,chipWidth, chipHeight, debug);
				//	apply_FM_Algorithm(cell_list_present,cell_count_present,cell_net_list,detailed_net_list ,net_count,cut_size,adjacent_list,cut_size,
				//max_connect,cell_list_p1,cell_list_p2,p_type,global_cell_list, cell_list_present[z].x_dim, cell_list_present[z].y_dim, w_temp, height, mode, delta);
				}
				cell_count_p1 = cell_list_p1.size();
				cell_count_p2 = cell_list_p2.size();
				cout<<"sub cell list p1 size: "<<cell_count_p1<<" sub cell list p2 size: "<<cell_count_p2<<endl;
				if(cell_count_p1)
				{
					cout<<"p1 x coord: "<<cell_list_p1[0].x_dim<<" p1 y coord: "<<cell_list_p1[0].y_dim<<endl;
				}
	
				if(cell_count_p2)
				{
					cout<<"p2 x coord: "<<cell_list_p2[0].x_dim<<" p2 y coord: "<<cell_list_p2[0].y_dim<<endl;
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
double x_coord, double y_coord, double width, double height, int mode, double delta, vector<int> net_list[], double chipWidth, double chipHeight, bool debug)
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
		x_coord,y_coord,width,height, mode, delta, net_list,chipWidth, chipHeight, debug);
		
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
	max_connect,global_cell_list, x_coord1,y_coord1, width, height, mode, delta, net_list, chipWidth, chipHeight, debug);
	cell_list_p1.clear();
	cell_list_p1.shrink_to_fit();
	
	min_cut_placement(cell_count_p2, cell_list_p2, p_type, count_threshold, cell_net_list,detailed_net_list,net_count,cut_size,adjacent_list,
	max_connect,global_cell_list,x_coord2,y_coord2, width, height, mode, delta, net_list, chipWidth, chipHeight, debug);
	cell_list_p2.clear();
	cell_list_p2.shrink_to_fit();
//	cell_count_p1 = cell_list_p1.size();
//	cell_count_p2 = cell_list_p2.size();
	
	//cell_list_p1.clear();
	//cell_list_p1.shrink_to_fit();
	
	//cell_list_p2.clear();
	//cell_list_p2.shrink_to_fit();
}


bool sortByVal(const pair<int, double> &a, 
               const pair<int, double> &b) 
{ 
    return (a.second < b.second); 
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
    
    double chipHeight=0, chipWidth=0;
    int rowCount = 0;
    getDimension(dimFileName,chipWidth,chipHeight,widthCell,cell_count, rowCount);
    cout<<"Done reading dim file: "<<dimFileName<<"\n";
    cout<<"Width: "<<chipWidth<<" height: "<<chipHeight<<"| standard cell row count: "<<rowCount<<endl;
   
    
   // for(int p =0; p<cell_count;p++)
   // 	cout<<widthCell[p]<<" ";
    //int cell_last=0,cell_present=0;
    
	vector<Cell> detailed_net_list[net_count];
	vector<Cell> adjacent_list[cell_count];
	
	vector<int> *cell_net_list;
	cell_net_list = new vector<int>[cell_count];
//	cout<<"net_count: "<<net_count<<" cell_count: "<<cell_count<<endl;

	
	//Checking the value of net count, cell count and netlist 
	cout<<"Input file: "<<file_name<<endl;
	//cout<<"net_count: "<<net_count<<" cell_count: "<<cell_count<<endl;
	
	 
	
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
	//print_cell_netlist(cell_net_list,cell_count);
	
	//Assigning partition id depending on whether cell id is odd or even-------------------------------------
	initialise(detailed_net_list,net_count,adjacent_list,cell_count);
	//cout<<"test"<<endl;
	//create_cell_list(cell_list,cell_count,detailed_net_list,net_count);
	create_cell_list_2(cell_list,cell_count,detailed_net_list,net_count,cell_ptr_list);
	create_global_cell_list(cell_list,global_cell_list,cell_count);
	cut_size = calculate_cutsize(detailed_net_list,net_count);
	//cout<<"External_Cost: "<<external_cost<<" Internal Cost: "<<internal_cost<<" Self Cost: "<<selfCost<<" cut size:"<<cut_size<<endl;
	cout<<"initial cut size: "<<cut_size<<endl;
	int threshold = (0.1*cell_count)+1;
	cout<<" max cell diff allowed: "<<threshold<<endl;
	
	
		vector<Cell> global_cell_list1(cell_list);
		vector<Cell> cell_ptr_p1;
		vector<Cell> cell_ptr_p2;
		bool p_type=0; //Horizontal
		
		//double x_coord_init = chip_width/2;
		//double y_coord_init = chip_height/2;
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
		
		
		///*
		if(strat == false)
		{
			cout<<"Using DFS"<<endl;
			
			min_cut_placement(cell_count,cell_list,p_type,threshold,cell_net_list,detailed_net_list,net_count,cut_size,adjacent_list,
		    max_connect,global_cell_list1,x_coord_init,y_coord_init,init_width,init_height, mode,delta,net_list, chipWidth, chipHeight, debug_mode);
		}	  
		//min_cut_placement(cell_count,cell_list,p_type,threshold,cell_net_list,detailed_net_list,net_count,cut_size,adjacent_list,
		//max_connect,global_cell_list1,x_coord_init,y_coord_init,init_width,init_height, mode,delta,net_list);
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
		
		
		
		/*
		ofstream output_file;
		output_file.open("data1.csv");
		
		output_file<<"x,y\n";
		for(int i=0; i<global_cell_list1.size(); i++)
		{
			output_file<<global_cell_list1[i].x_dim<<","<<global_cell_list1[i].y_dim<<endl;
		}
		output_file.close();
		*/
		//*/
		
		cout<<"done spreading the cell\n";
		
		cout<<"Now placing the cells\n";
		//------------------------------------------------------
		map<int,pair<double,double>> finalPlacement;
		map<int,double> yCoordinate;
		map<int,double> xCoordinate;
		
		int cell_id;
		double y_coordinate;
		double x_coordinate;
		for(int x = 0; x< cell_count; x++)
		{
			cell_id = global_cell_list1[x].cell_id;
			
			if(cell_id == 0)
				continue;
			
			y_coordinate = global_cell_list1[x].y_dim;
			x_coordinate = global_cell_list1[x].x_dim;
			yCoordinate.insert({cell_id,y_coordinate});
			xCoordinate.insert({cell_id,x_coordinate});
		}
		cout<<"Done with x coordinate and ycoordinate map"<<endl;
		//cout<<"size y: "<<yCoordinate.size()<<" size x: "<<xCoordinate.size()<<endl;
		
		int row_id=0;
		vector< pair<int, double> > vec_y;
		map<int,double> :: iterator itr;
		
		for(itr = yCoordinate.begin(); itr != yCoordinate.end(); itr++)
		{
			vec_y.push_back( make_pair(  itr ->first, itr->second)  );
			
		}
		sort(vec_y.begin(), vec_y.end(), sortByVal);
		
		double width_cell=0;
		double width_cell_sum=0;
		double x_coord2;
		int sum_cell=0;
		int index_row = row_id;
		for(int i=0; i<vec_y.size(); i++)
		{
		//	cout<<vec_y[i].first<<" -> "<<vec_y[i].second<<endl;
			//row[row_id].rowPointer = 0;
			
			//row[row_id].y_coord = 2*row_id*rowHeight;
			//cout<<2*row_id*rowHeight;
			cell_id = vec_y[i].first;
			assert(cell_id >= 1);
			width_cell = widthCell[cell_id - 1];
			width_cell_sum += width_cell;
			
			
			if(width_cell_sum <= chipWidth - 5)
			{
				row[row_id].rowPointer = 0;
				row[row_id].cell_list.push_back(cell_id);
				row[row_id].y_coord = 2*row_id*rowHeight;
				//cell_id = vec_y[i].first;
				
				sum_cell++;
				x_coord2 = xCoordinate[cell_id];
				row[row_id].x_coordinate.insert({cell_id,x_coord2});
			}
			else
			{
				//cout<<"row #"<<row_id<<" : "<<row[row_id].cell_list.size()<<" width_cell_sum: "<<width_cell_sum<<"y coord: "<<row[row_id].y_coord<<endl;
			//	sum_cell += row[row_id].cell_list.size();
				row_id++;
				assert(row_id < rowCount);
				row[row_id].rowPointer = 0;
				row[row_id].cell_list.push_back(cell_id);
				sum_cell++;
				row[row_id].y_coord = 2*row_id*rowHeight;
				//cell_id = vec_y[i].first;
				x_coord2 = xCoordinate[cell_id];
				row[row_id].x_coordinate.insert({cell_id,x_coord2});
				
			
				width_cell_sum = 0;	
				
			}	
		}
		
		cout<<"cell count: "<<sum_cell<<" row used: "<<row_id + 1<<" out of "<<rowCount<<endl;
		
		
		
		/*
		int row_size;
		double row_y;
		double row_cell_width=0;
		
		for(int i=0; i<rowCount;i++)
		{
			row_size = row[i].cell_list.size();
			row_y = row[i].y_coord;
			row_cell_width = 0;
			map<int,double> :: iterator itr;
			for(itr = row[i].x_coordinate.begin(); itr!= row[i].x_coordinate.end(); itr++)
			{
				
				row_cell_width += widthCell[itr->first - 1];
			}
			
			cout<<"row id: "<<i<<" row_y: "<<row_y<<" row_size: "<<row_size<<" row width: "<<row_cell_width<<endl;
		}
		*/
		
		vector< pair<int, double> > vec_x;
		int cell_id_row;
		for(int i=0; i<rowCount; i++)
		{
				if( row[i].cell_list.size() > 0)
				{
						map<int,double> :: iterator itr;
						
						for(itr = row[i].x_coordinate.begin(); itr!= row[i].x_coordinate.end();itr++)
						{
							assert(itr->first >= 1);
							vec_x.push_back(make_pair(itr->first,itr->second));
						}
						
						sort(vec_x.begin(), vec_x.end(), sortByVal);
						
					//	if(i==0)
					//	{
						double w=0;
							for(int j=0; j< vec_x.size(); j++)
							{
								
							//	if(i==43)
							//		cout<<vec_x[j].first<<" -> "<<vec_x[j].second<<endl;
								cell_id_row = vec_x[j].first;
								if(cell_id_row < 1)
									cout<<"cell_id: "<<cell_id_row<<" i: "<<i<<endl;
								assert(cell_id_row >= 1);
								row[i].cell_order.push_back(cell_id_row);
								
								pair<double,double> p1 (w,row[i].y_coord);
								if(w > chipWidth)
								{
									cout<<"w is beyond chip_width: "<<w<<endl;
								}
								w= w + widthCell[cell_id_row - 1];
								if(w > chipWidth)
								{
									cout<<"overflow in row #"<<i<<" by "<<w - chipWidth<<endl;
								}
								finalPlacement.insert({cell_id_row, p1});
							}
							
								
					//	}
					//	cout<<"size of vec_x: "<<vec_x.size()<<" final cell x coord: "<< finalPlacement[row[i].cell_order.back()].first<<" final cell ycoord: "
					//	<<finalPlacement[row[i].cell_order.back()].second<<endl;
						vec_x.clear();				
				}
				
		}
		
		unsigned int wl2 = compute_wirelength_2(detailed_net_list,finalPlacement,net_count);
		cout<<"After placing the cells, wirelength: "<<wl2<<endl;
		
		
		ofstream output_file;
		output_file.open("data1.csv");
		
		
		map<int, pair<double,double> > :: iterator itr3;
		//output_file<<"x,y,cell_id\n";
		output_file<<"x,y\n";
		for(itr3 = finalPlacement.begin(); itr3 != finalPlacement.end(); itr3++ )
		{
			
			//output_file<<itr3->second.first<<","<<itr3->second.second<<","<<itr3->first<<endl;
			output_file<<itr3->second.first<<","<<itr3->second.second<<endl;
			//cout<<itr3->second.first<<","<<itr3->second.second<<endl;
		}
		
		output_file.close();
		cout<<"CSV file generated\n";
		/*
		int cell_id;
		double y_coord;
		double temp, diff;
		int row_id;
		double width_cell=0;
	    for(int i=0; i< cell_count; i++)
	    {
	    	cell_id = global_cell_list1[i].cell_id;
	    	
	    	if(cell_id == 0)
	    		continue;
	    	y_coord = global_cell_list1[i].y_dim;
	    	
	    	temp = y_coord/ (2*rowHeight);
	    	
	    	row_id = int (y_coord/ (2*rowHeight) );
	    	diff = temp - row_id;
	    	if(row_id >= rowCount)
	    		cout<<"row_id: "<<row_id<<"y_coord: "<<y_coord<<endl;
	    	assert(row_id < rowCount);
	    	
	    	if(row_id != rowCount - 1)
	    	{	
	    	//	cout<<"i: "<<i<<endl;
	    		if(diff > 0.5)
	    		{
	    			row[row_id + 1].rowPointer = 0;
	    			row[row_id + 1].cell_id.push_back(cell_id);
	    			row[row_id + 1].y_coord = 0;
	    			width_cell = widthCell[cell_id - 1];
	    			row[row_id + 1].x_coordinate.insert(pair<int,double>(cell_id, width_cell)  );
	    			//row[row_id + 1].cell_id.push_back(cell_id);
				}
				else 
				{
					row[row_id].rowPointer = 0;
	    			row[row_id].cell_id.push_back(cell_id);
	    			row[row_id].y_coord = 0;
	    			width_cell = widthCell[cell_id - 1];
	    			row[row_id].x_coordinate.insert(pair<int,double>(cell_id, width_cell)  );
	    			//row[row_id].cell_id.push_back(cell_id);
				}
			}
			else if(row_id == rowCount - 1)
			{
				row[row_id].rowPointer = 0;
	    		row[row_id].cell_id.push_back(cell_id);
	    		row[row_id + 1].y_coord = 0;
	    		width_cell = widthCell[cell_id - 1];
	    		row[row_id].x_coordinate.insert(pair<int,double>(cell_id, width_cell)  );
	    		//row[row_id].cell_id.push_back(cell_id);
			}
	    
	    	//assert(row_id < rowCount);
	    
		}
		
		double widthSum=0;
		int num_cell=0;
		int total_sum=0;
		map<int,double> ::iterator itr;
		for(int i=0; i<rowCount; i++)
		{
			total_sum += row[i].cell_id.size();
		//	cout<<"cell count in row#"<<i<<" : "<<row[i].cell_id.size()<<endl;
			widthSum=0;
			for(itr = row[i].x_coordinate.begin(); itr != row[i].x_coordinate.end(); itr++)
			{
				widthSum += itr->second;
			}
			cout<<"cell count in row#"<<i<<" : "<<row[i].cell_id.size()<<" total width sum: "<<widthSum<<endl;	
		}
		cout<<"total cell count: "<<total_sum<<endl;
		*/
	return 0;
	
}
