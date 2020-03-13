#include<iostream>
using namespace std;

void initialise(vector<Cell> detailed_net_list[], int detailed_netlist_size, vector<Cell> adjacent_list[], int adj_size, vector<Cell> reduced_adjacent_list[] )
{
	for(int i=0;i<detailed_netlist_size;i++)
	{
		for(int j=0;j<detailed_net_list[i].size();j++)
		{
			detailed_net_list[i][j].partition_id = (detailed_net_list[i][j].cell_id % 2) + 1;
		}
	}
	
	for(int i=0; i< adj_size; i++)
	{
		if(!adjacent_list[i].empty())
		{
			for(int j=0;j<adjacent_list[i].size();j++)
			{
				adjacent_list[i][j].partition_id = (adjacent_list[i][j].cell_id % 2) + 1;
			}
		}
		
		if(!reduced_adjacent_list[i].empty())
		{
			for(int j=0;j<reduced_adjacent_list[i].size();j++)
			{
				reduced_adjacent_list[i][j].partition_id = (reduced_adjacent_list[i][j].cell_id % 2) + 1;
			}
		}
	}
}

void
calculate_cost(int cell_id, vector<Cell> cell_list, vector<Cell> adjacent_list[], int adj_size, map< pair<int,int>, double > weight, double &external_cost, double &internal_cost)
{
	int index = cell_id -1;
	assert(index >=0);
	int partition_cell = cell_list[index].partition_id;
	int partition_neighbor;
	int n_cell_id;
	int p=0,q=0;
	double w;
	double cost=0;
	double temp_cost;
	internal_cost=0;
	external_cost=0;
	for(int i=0;i<adjacent_list[index].size();i++)
	{
		partition_neighbor = adjacent_list[index][i].partition_id;
		n_cell_id = adjacent_list[index][i].cell_id;
		if(cell_id < n_cell_id)
		{
			p = cell_id;
			q= n_cell_id;
		}
		else 
		{
			p = n_cell_id;
			q = cell_id;
		}
		w = weight[ {p,q}  ];
		assert(w>0);
		if(partition_cell == partition_neighbor)
		{
			//cells are in same partition
			internal_cost += w;
		}
		else if (partition_cell != partition_neighbor)
		{
			external_cost += w;
		}
		
	}
}

double self_cost(int cell_id_1, int cell_id_2, vector<Cell> reduced_adjacent_list[], int adj_size, map< pair<int,int>, double > weight)
{
	int p=0;
	int q=0;
	double cost=0;
	bool present=false;
	
	if( cell_id_1 < cell_id_2)
	{
		p = cell_id_1;
		q = cell_id_2;
	}	
	else 
	{
		p = cell_id_2;
		q = cell_id_1;
	}
	int index = p-1;
	assert( p < q);
	//cout<<"p: "<<p<<" q: "<<q<<"weight: "<<weight[{p,q}]<<endl;
	//cout<<"p: "<<
	for(int i=0;i<reduced_adjacent_list[index].size();i++)
	{
		if(q == reduced_adjacent_list[index][i].cell_id)
		{
			present = true;
			break;
		}
	}
	if(present==false)
		return 0;
	else
	{
	//	cout<<"p: "<<p<<" q: "<<q<<"weight: "<<weight[{p,q}]<<endl;
		return 2*(weight[{p,q}]);
	}
}

int 
calculate_cutsize(  vector<Cell> detailed_net_list[], int detailed_netlist_size)
{
	int cut_size=0;
	int p1=0, p2=0;
	for(int i=0;i<detailed_netlist_size;i++)
	{
		for(int j=0;j<detailed_net_list[i].size();j++)
		{
			if(j==0)
			{
				p1 = detailed_net_list[i][j].partition_id;
			}
			else 
			{
				p2 = detailed_net_list[i][j].partition_id;
				
				if(p1!= p2)
				{
					cut_size++;
					break;
				}	
			}
		}
	}
	return cut_size;
}

void create_partition_list(vector<int> &partition_1, vector<int> &partition_2, vector<Cell> cell_list, int cell_count)
{
	int p=0;
	for(int i=0;i<cell_list.size();i++)
	{
		p = cell_list[i].partition_id;
			if(p == 1)
			{
				partition_1.push_back(cell_list[i].cell_id);
			}
			else if(p==2)
			{
				partition_2.push_back(cell_list[i].cell_id);
			}
	}
}

void 
update_partition(int cell_id_1,int partition_1, vector<Cell> &cell_list, vector<Cell> detailed_net_list[], vector<Cell> adjacent_list[], 
vector<Cell> reduced_adjacent_list[], int cell_count, int net_count)
{
	//Updating cell list
	int index = cell_id_1 -1 ;
	cell_list[index].partition_id = partition_1;
	
	
	
	//updating detailed_net_list
	bool present=false;
	for(int i=0;i<net_count;i++)
	{
		if(!detailed_net_list[i].empty())
		{
			present = is_cell_present(detailed_net_list[i],detailed_net_list[i].size(),cell_id_1);
			
			if(present)
			{
				for(int j=0;j<detailed_net_list[i].size();j++)
				{
					if(detailed_net_list[i][j].cell_id == cell_id_1)
					{
						detailed_net_list[i][j].partition_id = partition_1;
						break;
					}
				}
			}
		}
		
	}
	present = false;
	//Updating adjacent list and reduced adjacent list
	for(int i=0;i<cell_count;i++)
	{
		//Updating adjacent list----------------------------------------------------------
		if(!adjacent_list[i].empty())
		{
			present = is_cell_present(adjacent_list[i], adjacent_list[i].size(),cell_id_1);
		
			if(present)
			{
				for(int j=0;j<adjacent_list[i].size();j++)
				{
					if(adjacent_list[i][j].cell_id == cell_id_1)
					{
						adjacent_list[i][j].partition_id = partition_1;
						break;
					}
				}
			}
		}
		//-----------------------------------------------------------------------------------
		
		
		//Updating reduced_adjacent_list
		present = false;
		
		if(!reduced_adjacent_list[i].empty())
		{
			present = is_cell_present(reduced_adjacent_list[i], reduced_adjacent_list[i].size(),cell_id_1);
			
			if(present)
			{
				for(int j=0;j<reduced_adjacent_list[i].size();j++)
				{
					if(reduced_adjacent_list[i][j].cell_id == cell_id_1)
					{
						reduced_adjacent_list[i][j].partition_id = partition_1;
						break;
					}
				}
			}
		}
	
		
	}
}

void lock_cell(int cell_id, vector<Cell> &cell_list)
{
	/*
	for(int i=0;i<cell_list.size();i++)
	{
		if(cell_id == cell_list[i].cell_id)
		{
			assert(cell_list[i].locked == false);
			cell_list[i].locked=true;
			break;		
		}
	}
	*/
	int index = cell_id - 1;
	
	//assert(cell_list[index].locked == false);
	cell_list[index].locked = true;
}

void unlock_all_cells (vector <Cell> &cell_list)
{
	for(int i=0;i<cell_list.size();i++)
	{
		cell_list[i].locked=false;
	}
}

bool check_cell_locked (int cell_id, vector<Cell> cell_list )
{
	int index = cell_id - 1;
	
	if(cell_list[index].locked==false)
		return true;
	else
		return false;
}
int count_unlocked_cell(vector<Cell> cell_list)
{
	int num=0;
		for(int i=0;i<cell_list.size();i++)
	{
		if(cell_list[i].locked==false)
			num++;
	}
	return num;
}
int get_unlocked_cell_id(int partition_id, vector<Cell> cell_list)
{
	for(int i=0;i<cell_list.size();i++)
	{
		int cell_id = i+1;
		if(cell_list[i].locked == false && cell_list[i].partition_id == partition_id)
		{
			return cell_id;
		}

	}
	return -1;
}

int get_unlocked_cell_id(vector<Cell> cell_list)
{
		for(int i=0;i<cell_list.size();i++)
		{
			int cell_id = i+1;
			if(cell_list[i].locked == false)
			{
				return cell_id;
			}

		}
	return -1;
}

vector<int> get_valid_partition_cells (vector<Cell> cell_list, int partition_id)
{
	vector<int> v;
	
	for(int i=0;i<cell_list.size();i++)
	{
		if(cell_list[i].locked==false && cell_list[i].partition_id == partition_id)
		{
			v.push_back(cell_list[i].cell_id);
		}
	}
	return v;
}

int max_gain_position(vector<double>gain_list)
{
	if(gain_list.empty())
		return -1;
	
	int pos=-1;
	double gain = gain_list[0];
	double gain_last,gain_max;
		gain_max= 0;
	for(int i=1;i<gain_list.size();i++)
	{
		gain_last = gain;
		//gain_max= gain;
		gain = gain + gain_list[i];
	//	cout<<"gain: "<<gain<<endl;
		if(gain > gain_max)
		{
			gain_max= gain;
			//cout<<"gain: "<<gain<<" gain_last: "<<gain_last<<endl;
			pos=i;
		}
	}
	return pos;
}

void
KL_Algorithm(vector<Cell> &cell_list, vector<Cell> adjacent_list[], vector<Cell> reduced_adjacent_list[], int cell_count, map< pair<int,int>, double > weight,
vector<Cell> detailed_net_list[], int net_count, int initial_cutsize)
{
	int cost=0;
	bool start=true;
	
	int cell_p1 = 0;
	int cell_p2 = 0;
	bool end=false;
	int p1 = 1;
	int p2 = 2;
	vector<int> v_p1;
	vector<int> v_p2;
	int p=0,q=0;
	double internal_cost_p1=0, external_cost_p1=0, self_cost1=0;
	double internal_cost_p2=0, external_cost_p2=0;
	double gain_ref=0,gain_ref_prev=0;
	double gain=0;
	int x=0;
	double gain_pass=0;
	int pass_count=1;
	int max_pos=-1;
	vector<pair<int,int>> swap_list;
	vector<double> gain_list;
	int new_cut_size, old_cut_size;
	old_cut_size = initial_cutsize;
	int diff=0;
	int threshold=net_count;
//	while(gain_pass >= 0)
//	{
    do
    {
    	swap_list.clear();
    	gain_list.clear();
    //	cout<<"initial size: "<<gain_list.size()<<endl;
		unlock_all_cells(cell_list);
		do
		{
			
			v_p1 = get_valid_partition_cells(cell_list,p1);
			v_p2 = get_valid_partition_cells(cell_list,p2);
			
			for(int i=0; i< v_p1.size(); i++)
			{
				cell_p1 = v_p1[i];
				for(int j=0;j< v_p2.size(); j++)
				{
						cell_p2 = v_p2[j];
						
						//Swapping the cells
					//	set_cell_partition_id(cell_p1,p2,cell_list,adjacent_list,reduced_adjacent_list,cell_count);
					//	set_cell_partition_id(cell_p2,p1,cell_list,adjacent_list,reduced_adjacent_list,cell_count);
						//---------------------------------------------------------------------------------------
						
						if(start == true)
						{
							gain_ref = gain;
							p= cell_p1;
							q = cell_p2;
							start=false;
						}
						internal_cost_p1 = 0;
						internal_cost_p2 = 0;
						external_cost_p1 = 0;
						external_cost_p2 = 0;
						calculate_cost(cell_p1,cell_list,adjacent_list,cell_count,weight,external_cost_p1,internal_cost_p1);
						calculate_cost(cell_p2,cell_list,adjacent_list,cell_count,weight,external_cost_p2,internal_cost_p2);
					
						self_cost1 = self_cost(cell_p1,cell_p2,reduced_adjacent_list,cell_count,weight);
						gain = external_cost_p1 + external_cost_p2 - internal_cost_p1 - internal_cost_p2 - self_cost1;
					//cout<<"cell_p1: "<< cell_p1<<" cell_p2: " <<cell_p2<<" external_cost_p1 "<<external_cost_p1<<" external_cost_p2 "<<external_cost_p2
					//	<<" internal_p1 "<<internal_cost_p1<<" internal_p2: "<<internal_cost_p2<<" self_cost: "<<self_cost1<<endl;
						
						if(gain > gain_ref)
						{
							gain_ref = gain;	
							p = cell_p1;
							q = cell_p2;
						}	
						//Putting cell in original partitions
					//	set_cell_partition_id(cell_p1,p1,cell_list,adjacent_list,reduced_adjacent_list,cell_count);
					//	set_cell_partition_id(cell_p2,p2,cell_list,adjacent_list,reduced_adjacent_list,cell_count);
						//---------------------------------------------------------------------------------------
						
				}
			}
		//	cout<<"Swapping "<<p<<" & "<<q<<" gain: "<<gain_ref<<endl;
			lock_cell(p,cell_list);
			lock_cell(q,cell_list);
			pair<int,int> x1(p,q);
			swap_list.push_back(x1);
			gain_list.push_back(gain_ref);
			cout<<"swapped and locked "<<p<<" and "<<q<<" gain: "<<gain_ref<<" pass_count: "<<pass_count<<endl;
			
			set_cell_partition_id(p,p2,cell_list,adjacent_list,reduced_adjacent_list,cell_count);
			set_cell_partition_id(q,p1,cell_list,adjacent_list,reduced_adjacent_list,cell_count);
			gain_ref_prev = gain_ref;
			start=true;
			x++;
		}while(!v_p1.empty() && !v_p2.empty());
		swap_list.pop_back();
	//	cout<<"final size: "<<swap_list.size()<<endl;
		gain_list.pop_back();
		max_pos = max_gain_position(gain_list);
		//cout<<"max_pos: "<<max_pos<<endl;
		//restoring----------------------------------------------------------
		//vector<pair<int,int>> iterator::itr;
		for( int i=max_pos+1;i<swap_list.size();i++)
		{
			pair<int,int> pair1;
			pair1 = swap_list[i];
			int partition1=1;
			int partition2=2;
			cout<<"swapping back "<<pair1.first<<" and "<<pair1.second<<endl;
			set_cell_partition_id(pair1.first,partition1,cell_list,adjacent_list,reduced_adjacent_list,cell_count);
			set_cell_partition_id(pair1.second,partition2,cell_list,adjacent_list,reduced_adjacent_list,cell_count);
			
		}
		
		//--------------------------------------------------
		
		update_detailed_netlist(cell_list,detailed_net_list,net_count);
		new_cut_size = calculate_cutsize(detailed_net_list,net_count);
		cout<<"pass_count: "<<pass_count<<" new cutsize: "<<new_cut_size<<endl;
		//gain_pass += gain_ref;
		//cout<<"Gain from pass"<<pass_count<<" : "<<gain_pass<<endl;
		pass_count++;
		diff =  old_cut_size - new_cut_size;
		old_cut_size = new_cut_size;
		//cout<<"gain: "<<gain_list[0]<<endl;
		//cout<<"condition_var: "<<*max_element(gain_list.begin(),gain_list.end())<<endl;
		//print_cell_list(cell_list);
	} while( diff >= 0 && pass_count < threshold);
	
	
	//}
}
