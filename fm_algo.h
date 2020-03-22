#include<iostream>
using namespace std;


//int chip_height = 1000;
//int  chip_width = 1000;

/*
template<typename KeyType, typename ValueType> 
std::pair<KeyType,ValueType> get_max( const std::map<KeyType,ValueType>& x ) {
  using pairtype=std::pair<KeyType,ValueType>; 
  return *std::max_element(x.begin(), x.end(), [] (const pairtype & p1, const pairtype & p2) {
        return p1.second < p2.second;
  }); 
}

*/
void update_sub_cell_list(vector<Cell> cell_list, vector<Cell> &cell_list_p1, vector<Cell> &cell_list_p2, int p1, int p2)
{
	for(int i=0; i<cell_list.size();i++)
	{
		if(cell_list[i].cell_id == 0)
			continue;
		
		else if(cell_list[i].partition_id == p1)
		{
			cell_list_p1.push_back(cell_list[i]);
		}
		else if(cell_list[i].partition_id == p2)
		{
			cell_list_p2.push_back(cell_list[i]);
		}
	}
}
void initialise(vector<Cell> detailed_net_list[], int detailed_netlist_size, vector<Cell> adjacent_list[], int adj_size )
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
		/*	
		if(!reduced_adjacent_list[i].empty())
		{
			for(int j=0;j<reduced_adjacent_list[i].size();j++)
			{
				reduced_adjacent_list[i][j].partition_id = (reduced_adjacent_list[i][j].cell_id % 2) + 1;
			}
		}
		*/
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
	assert(index >= 0);
	//assert(cell_list[index].locked == false);
	cell_list[index].locked = true;
}

void lock_cell_2(int index, vector<Cell> &cell_list)
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
//	int index = cell_id - 1;
	assert(index >= 0);
	//assert(cell_list[index].locked == false);
	cell_list[index].locked = true;
}

void unlock_all_cells (vector <Cell> &cell_list)
{
	for(int i=0;i<cell_list.size();i++)
	{
		if(cell_list[i].cell_id == 0)
		{
			continue;
		}
		cell_list[i].locked=false;
	}
}

bool check_cell_locked (int cell_id, vector<Cell> cell_list )
{
	int index = cell_id - 1;
	assert(index >=0 );
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
		if(cell_list[i].cell_id ==0)
			continue;
			
		if(cell_list[i].locked==false)
			num++;
	}
	return num;
}
int get_unlocked_cell_id(int partition_id, vector<Cell> cell_list)
{
	for(int i=0;i<cell_list.size();i++)
	{
		
		if(cell_list[i].cell_id ==0)
			continue;
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
			if(cell_list[i].cell_id ==0)
				continue;
			
			int cell_id = i+1;
			if(cell_list[i].locked == false)
			{
				return cell_id;
			}

		}
	return -1;
}

int get_unlocked_cell_id_2(vector<Cell> cell_list)
{
		for(int i=0;i<cell_list.size();i++)
		{
			if(cell_list[i].cell_id ==0)
				continue;
			
			//int cell_id = i+1;
			if(cell_list[i].locked == false)
			{
				return cell_list[i].cell_id;
			}

		}
	return -1;
}


void 
set_cell_partition_id(int cell_id, int partition_id, vector<Cell> &cell_list, vector<Cell> adjacent_list[], int cell_count)
{
	int index = cell_id - 1;
	assert(index >= 0);
	cell_list[index].partition_id = partition_id;
	bool present=false;
	for(int i=0;i<cell_count;i++)
	{
		
		if(cell_list[i].cell_id == 0)
			continue;
		
		if(!adjacent_list[i].empty())
		{
			present = is_cell_present(adjacent_list[i],adjacent_list[i].size(),cell_id);
			
			if(present)
			{
				for(int j=0;j<adjacent_list[i].size();j++)
				{
					if(cell_id == adjacent_list[i][j].cell_id)
					{
						adjacent_list[i][j].partition_id = partition_id;
						break;
					}
				}
			}
		}
	}
}


void 
set_cell_partition_id_2(int index, int partition_id, vector<Cell> &cell_list, vector<Cell> adjacent_list[], int cell_count, vector<Cell> &global_cell_list)
{
	//int index = cell_id - 1;
	assert(index >= 0);
	cell_list[index].partition_id = partition_id;
	int cell_id = cell_list[index].cell_id;
	assert(cell_id >= 1);
	global_cell_list[cell_id - 1].partition_id = partition_id;
	bool present=false;
	for(int i=0;i<cell_count;i++)
	{
		
		if(cell_list[i].cell_id == 0)
			continue;
		
		if(!adjacent_list[i].empty())
		{
			present = is_cell_present(adjacent_list[i],adjacent_list[i].size(),cell_id);
			
			if(present)
			{
				for(int j=0;j<adjacent_list[i].size();j++)
				{
					if(cell_id == adjacent_list[i][j].cell_id)
					{
						adjacent_list[i][j].partition_id = partition_id;
						break;
					}
				}
			}
		}
	}
}

int get_partition_count(vector<Cell> cell_list, int partition_id)
{
	int num=0;
	
	for(int i=0;i< cell_list.size();i++)
	{
		if(cell_list[i].cell_id ==0)
			continue;
		
		if(cell_list[i].partition_id == partition_id)
			num++;
	}
	return num;
}
int
only_cell(int cell_id, int partition_id, vector<int> cell_net_list[], int cell_count, vector<Cell> cell_list, 
vector<Cell> detailed_net_list[], int net_count)

{
	int net_id;
	int	net_num_only =0;
	//net_num_all =0;
	int cell_id_det;
	bool diff=false;
	//bool same=false;
	//Cell_list is updated
	int index = cell_id - 1;
	assert(index >= 0);
	bool v=false;
	
	for(int i=0;i<cell_net_list[index].size();i++)
	{
	
		net_id = cell_net_list[index][i];
		
		diff = true;
		v = false;
	//	same=true;
		for(int j=0;j<detailed_net_list[net_id].size();j++)
		{
			v=true;
			cell_id_det = detailed_net_list[net_id][j].cell_id;
			assert(cell_id_det >= 1);
			
			if(cell_id_det == cell_id)
				continue;
				
			if(cell_list[cell_id_det - 1].x_dim != cell_list[cell_id - 1].x_dim)
				continue;
			
			if(cell_list[cell_id_det - 1].y_dim != cell_list[cell_id - 1].y_dim)
				continue;
			
			else
			{
				
				if(partition_id == cell_list[cell_id_det - 1].partition_id)
				{
					diff=false;
					
					break;
				}
				
			}
		}
		
		if(diff==true && v==true)
			net_num_only++;
		
		//if(same==true)
		//	net_num_all++
	}
	return net_num_only;
}


//-----------
int
only_cell_2(int index, int partition_id, vector<int> cell_net_list[], int cell_count, vector<Cell> cell_list, 
vector<Cell> detailed_net_list[], int net_count, vector<Cell> global_cell_list, bool p_type, int mode, double delta, double width, double height)

{
	int net_id;
	int	net_num_only =0;
	//net_num_all =0;
	int cell_id_det;
	bool diff=false;
	//bool same=false;
	//Cell_list is updated
	//int index = cell_id - 1;
	assert(index >= 0);
	bool v=false;
	int inactive_cell_p_id=0;
	int cell_id = cell_list[index].cell_id;
	for(int i=0;i<cell_net_list[cell_id - 1].size();i++)
	{
	
		net_id = cell_net_list[cell_id - 1][i];
		
		diff = true;
		v = false;
	//	same=true;
		for(int j=0;j<detailed_net_list[net_id].size();j++)
		{
			v=true;
			cell_id_det = detailed_net_list[net_id][j].cell_id;
			assert(cell_id_det >= 1);
			
			
			if(cell_id_det == cell_id)
				continue;
			
			/*	
			if(global_cell_list[cell_id_det - 1].x_dim != cell_list[index].x_dim)
				continue;
			
			if(global_cell_list[cell_id_det - 1].y_dim != cell_list[index].y_dim)
				continue;
			*/
			if(global_cell_list[cell_id - 1].active == true)
			{
			//else if(global_cell_list[cell_id_det - 1].y_dim == cell_list[index].y_dim && global_cell_list[cell_id_det - 1].x_dim == cell_list[index].x_dim)
			//{
				//assert(cell_id_det >= 1);
				//assert(cell_id_det <= cell_count);
				if(partition_id == global_cell_list[cell_id_det - 1].partition_id)
				{
					diff=false;
					
					break;
				}
			}
			
			else if(global_cell_list[cell_id_det - 1].active == false && mode == 3)
			{
				//Terminal propogation window is 0
				//Cell is outside the active partition
				if(p_type == 0)
				{
					//Horizontal partition
					//cell_id_det is not in active region
					if(global_cell_list[cell_id_det - 1].y_dim > cell_list[index].y_dim + delta &&
					compute_abs_diff( global_cell_list[cell_id_det - 1].y_dim, cell_list[index].y_dim) >= height*delta/2 )
					{
						inactive_cell_p_id = 1;
					}
					else if (global_cell_list[cell_id_det - 1].y_dim < cell_list[index].y_dim + delta &&
					compute_abs_diff( global_cell_list[cell_id_det - 1].y_dim, cell_list[index].y_dim) >= height*delta/2  )
					{
						inactive_cell_p_id = 2;
					}	
				}
				
				else if(p_type == 1)
				{
					//Vertical partition
					//Cell is outside the active partition area
					if(global_cell_list[cell_id_det - 1].x_dim > cell_list[index].x_dim + delta &&
					compute_abs_diff( global_cell_list[cell_id_det - 1].x_dim, cell_list[index].x_dim) >= width*delta/2 )
					{
						inactive_cell_p_id = 2;
					}
					else if (global_cell_list[cell_id_det - 1].x_dim < cell_list[index].x_dim + delta &&
					compute_abs_diff( global_cell_list[cell_id_det - 1].x_dim, cell_list[index].x_dim) >= width*delta/2 )
					{
						inactive_cell_p_id = 1;
					}
				}
				
				if( partition_id == inactive_cell_p_id)
				{
					diff = false;
					break;
				}	
			}
			//}
		}
		
		if(diff==true && v==true)
			net_num_only++;
		
		//if(same==true)
		//	net_num_all++
	}
	return net_num_only;
}
//----------------
void update_cell_list_fm_only_cell_net_count (int cell_id, int partition_id, vector<int> cell_net_list[], int cell_count, vector<Cell> &cell_list, 
vector<Cell> detailed_net_list[], int net_count )
{
	int net_id;
	int	net_num_only =0;
	//net_num_all =0;
	int cell_id_det;
	bool diff=false;
	//bool same=false;
	//Cell_list is updated
	int index = cell_id - 1;
	assert(index >= 0);
	bool v=false;
	
	for(int i=0;i<cell_net_list[index].size();i++)
	{
		net_id = cell_net_list[index][i];
		
		diff = true;
		v = false;
	//	same=true;
		for(int j=0;j<detailed_net_list[net_id].size();j++)
		{
			v=true;
			cell_id_det = detailed_net_list[net_id][j].cell_id;
			
			if(cell_id_det == cell_id)
				continue;
			else
			{
				
				if(partition_id == cell_list[cell_id_det - 1].partition_id)
				{
					diff=false;
					
					break;
				}
				
			}
		}
		
		if(diff==true && v==true)
			net_num_only++;
		
		//if(same==true)
		//	net_num_all++
	}
	assert(net_num_only >= 0);
	cell_list[cell_id - 1].only_cell_net_count = net_num_only;
	
}

void update_cell_list_fm_only_cell_net_count_3 (int cell_id, int partition_id, vector<int> cell_net_list[], int cell_count, vector<Cell> &cell_list, 
vector<Cell> detailed_net_list[], int net_count, vector<Cell> &global_cell_list )
{
	int net_id;
	int	net_num_only =0;
	//net_num_all =0;
	int cell_id_det;
	bool diff=false;
	//bool same=false;
	//Cell_list is updated
	int index = cell_id - 1;
	assert(index >= 0);
	bool v=false;
	
	for(int i=0;i<cell_net_list[index].size();i++)
	{
		net_id = cell_net_list[index][i];
		
		diff = true;
		v = false;
	//	same=true;
		for(int j=0;j<detailed_net_list[net_id].size();j++)
		{
			v=true;
			cell_id_det = detailed_net_list[net_id][j].cell_id;
			
			if(cell_id_det == cell_id)
				continue;
			else
			{
				if(global_cell_list[cell_id_det - 1].active == true)
				{
					if(partition_id == cell_list[cell_id_det - 1].partition_id)
					{
						diff=false;
					
						break;
					}
				}
			}
		}
		
		if(diff==true && v==true)
			net_num_only++;
		
		//if(same==true)
		//	net_num_all++
	}
	assert(net_num_only >= 0);
	global_cell_list[cell_id - 1].only_cell_net_count = net_num_only;
	cell_list[cell_id - 1].only_cell_net_count = net_num_only;
}


void update_cell_list_fm_only_cell_net_count_2 (int index, int partition_id, vector<int> cell_net_list[], int cell_count, vector<Cell> &cell_list, 
vector<Cell> detailed_net_list[], int net_count, vector<Cell> &global_cell_list, bool p_type, int mode, double delta, double width, double height)
{
	int net_id;
	int	net_num_only =0;
	//net_num_all =0;
	int cell_id_det;
	bool diff=false;
	
	int inactive_cell_p_id;
	//bool same=false;
	//Cell_list is updated
	//int index = cell_id - 1;
	assert(index >= 0);
	int cell_id = cell_list[index].cell_id;
	bool v=false;
	
	for(int i=0;i<cell_net_list[index].size();i++)
	{
		net_id = cell_net_list[index][i];
		
		diff = true;
		v = false;
	//	same=true;
		for(int j=0;j<detailed_net_list[net_id].size();j++)
		{
			v=true;
			cell_id_det = detailed_net_list[net_id][j].cell_id;
			
			if(cell_id_det == cell_id)
				continue;
			//else
			assert(cell_id_det >= 1);
			if(global_cell_list[cell_id_det - 1].active == true)
			{
				
				if(partition_id == global_cell_list[cell_id_det - 1].partition_id)
				{
					diff=false;
					
					break;
				}
				
			}
			
			else if(global_cell_list[cell_id_det - 1].active == false && mode == 3)
			{
				//Terminal propogation window is 0
				//Cell is outside the active partition
				if(p_type == 0)
				{
					//Horizontal partition
					//cell_id_det is not in active region
					if(global_cell_list[cell_id_det - 1].y_dim > cell_list[index].y_dim && 
					compute_abs_diff( global_cell_list[cell_id_det - 1].y_dim, cell_list[index].y_dim) >= height*delta/2  )
					{
						inactive_cell_p_id = 1;
					}
					else if (global_cell_list[cell_id_det - 1].y_dim < cell_list[index].y_dim && 
					compute_abs_diff( global_cell_list[cell_id_det - 1].y_dim, cell_list[index].y_dim) >= height*delta/2)
					{
						inactive_cell_p_id = 2;
					}	
				}
				
				else if(p_type == 1)
				{
					//Vertical partition
					//Cell is outside the active partition area
					if(global_cell_list[cell_id_det - 1].x_dim > cell_list[index].x_dim && 
					compute_abs_diff( global_cell_list[cell_id_det - 1].x_dim, cell_list[index].x_dim) >= width*delta/2)
					{
						inactive_cell_p_id = 2;
					}
					else if (global_cell_list[cell_id_det - 1].x_dim < cell_list[index].x_dim && 
					compute_abs_diff( global_cell_list[cell_id_det - 1].x_dim, cell_list[index].x_dim) >= width*delta/2)
					{
						inactive_cell_p_id = 1;
					}
				}
				
				if( partition_id == inactive_cell_p_id)
				{
					diff = false;
					break;
				}	
			}
		}
		
		if(diff==true && v==true)
			net_num_only++;
		
		//if(same==true)
		//	net_num_all++
	}
	assert(net_num_only >= 0);
	cell_list[index].only_cell_net_count = net_num_only;
	global_cell_list[cell_id - 1].only_cell_net_count = net_num_only;
}

void update_cell_list_all_cell_net_count(int cell_id, int partition_id, vector<int> cell_net_list[], int cell_count, vector<Cell> &cell_list, 
vector<Cell> detailed_net_list[], int net_count )

{
	int net_id;
	int	net_num_all =0;
	//net_num_all =0;
	int cell_id_det;
	bool same=false;
	//bool same=false;
	//Cell_list is updated
	int index = cell_id - 1;
	assert(index >= 0);
	vector<int> net_list;
	bool v=false;
	
	for(int i=0;i<cell_net_list[index].size();i++)
	{
		net_id = cell_net_list[index][i];
		//cout<<"net_id: "<<net_id<<endl;
		same=true;
		v = false;
		for(int j=0;j<detailed_net_list[net_id].size();j++)
		{
			cell_id_det = detailed_net_list[net_id][j].cell_id;
			v=true;
			if(cell_id_det == cell_id)
				continue;
			else
			{
				//cout<<"cell in partition "<<cell_id_det<<"partition: "<<cell_list[cell_id_det - 1].partition_id<<endl;
				if(partition_id != cell_list[cell_id_det - 1].partition_id)
				{
					same=false;
					
					break;
				}
				
			}
		}
		
		if(same==true && v==true)
			net_num_all++;
		
		//if(same==true)
		//	net_num_all++
	}
	assert(net_num_all >= 0);
	cell_list[cell_id - 1].all_same_partition_net_count = net_num_all;
}


void update_cell_list_all_cell_net_count_3(int cell_id, int partition_id, vector<int> cell_net_list[], int cell_count, vector<Cell> &cell_list, 
vector<Cell> detailed_net_list[], int net_count, vector<Cell> &global_cell_list )

{
	int net_id;
	int	net_num_all =0;
	//net_num_all =0;
	int cell_id_det;
	bool same=false;
	//bool same=false;
	//Cell_list is updated
	int index = cell_id - 1;
	assert(index >= 0);
	vector<int> net_list;
	bool v=false;
	
	for(int i=0;i<cell_net_list[index].size();i++)
	{
		net_id = cell_net_list[index][i];
		//cout<<"net_id: "<<net_id<<endl;
		same=true;
		v = false;
		for(int j=0;j<detailed_net_list[net_id].size();j++)
		{
			cell_id_det = detailed_net_list[net_id][j].cell_id;
			v=true;
			if(cell_id_det == cell_id)
				continue;
			else
			{
				//cout<<"cell in partition "<<cell_id_det<<"partition: "<<cell_list[cell_id_det - 1].partition_id<<endl;
				if(global_cell_list[cell_id_det - 1].active == true)
				{
					if(partition_id != global_cell_list[cell_id_det - 1].partition_id)
					{
						same=false;
					
						break;
					}
				}	
			}
		}
		
		if(same==true && v==true)
			net_num_all++;
		
		//if(same==true)
		//	net_num_all++
	}
	assert(net_num_all >= 0);
	global_cell_list[cell_id - 1].all_same_partition_net_count = net_num_all;
	cell_list[cell_id - 1].all_same_partition_net_count = net_num_all;
}

/*
void update_cell_list_all_cell_net_count(int cell_id, int partition_id, vector<int> cell_net_list[], int cell_count, vector<Cell> &cell_list, 
vector<Cell> detailed_net_list[], int net_count )

{
			int net_id;
	int	net_num_all =0;
	//net_num_all =0;
	int cell_id_det;
	bool same=false;
	//bool same=false;
	//Cell_list is updated
	int index = cell_id - 1;
	assert(index >= 0);
	vector<int> net_list;
	bool v=false;
	
	for(int i=0;i<cell_net_list[index].size();i++)
	{
		net_id = cell_net_list[index][i];
		//cout<<"net_id: "<<net_id<<endl;
		same=true;
		v = false;
		for(int j=0;j<detailed_net_list[net_id].size();j++)
		{
			cell_id_det = detailed_net_list[net_id][j].cell_id;
			v=true;
			if(cell_id_det == cell_id)
				continue;
			else
			{
				//cout<<"cell in partition "<<cell_id_det<<"partition: "<<cell_list[cell_id_det - 1].partition_id<<endl;
				if(partition_id != cell_list[cell_id_det - 1].partition_id)
				{
					same=false;
					
					break;
				}
				
			}
		}
		
		if(same==true && v==true)
			net_num_all++;
		
		//if(same==true)
		//	net_num_all++
	}
	assert(net_num_all >= 0);
	cell_list[cell_id - 1].all_same_partition_net_count = net_num_all;
}
*/

void update_cell_list_all_cell_net_count_2(int index, int partition_id, vector<int> cell_net_list[], int cell_count, vector<Cell> &cell_list, 
vector<Cell> detailed_net_list[], int net_count, vector<Cell> &global_cell_list, bool p_type, int mode, double delta, double width, double height)

{
	int net_id;
	int	net_num_all =0;
	//net_num_all =0;
	int cell_id_det;
	bool same=false;
	int inactive_cell_p_id = 0;
	//bool same=false;
	//Cell_list is updated
	//int index = cell_id - 1;
	//int inactive_cell_p_id = 0;
	assert(index >= 0);
	int cell_id = cell_list[index].cell_id;
	assert(cell_id >= 1);
	//vector<int> net_list;
	bool v=false;
	//int inactive_cell_p_id;
	for(int i=0;i<cell_net_list[index].size();i++)
	{
		net_id = cell_net_list[index][i];
		//cout<<"net_id: "<<net_id<<endl;
		same=true;
		v = false;
		for(int j=0;j<detailed_net_list[net_id].size();j++)
		{
			cell_id_det = detailed_net_list[net_id][j].cell_id;
			v=true;
			if(cell_id_det == cell_id)
				continue;
			else
			{
				//cout<<"cell in partition "<<cell_id_det<<"partition: "<<cell_list[cell_id_det - 1].partition_id<<endl;
				//if(global_cell_id[cell_id_det - 1].x_dim == cell_id[index].x_dim && global_cell_list[cell_id_det - 1].y_dim != cell_list[index].y_dim)
				//{
					if(global_cell_list[cell_id_det - 1].active == true)
					{
						if(partition_id != global_cell_list[cell_id_det - 1].partition_id)
						{
							same=false;
					
							break;
						}
					}
					
					else if(global_cell_list[cell_id_det - 1].active == false && mode == 3)
					{		
						//Terminal propogation window is 0
						//Cell is outside the active partition
						if(p_type == 0)
						{
							//Horizontal partition
							//cell_id_det is not in active region
							if(global_cell_list[cell_id_det - 1].y_dim > cell_list[index].y_dim &&
							compute_abs_diff( global_cell_list[cell_id_det - 1].y_dim, cell_list[index].y_dim) >= height*delta/2   )
							{
								inactive_cell_p_id = 1;
							}
							else if (global_cell_list[cell_id_det - 1].y_dim < cell_list[index].y_dim &&
							compute_abs_diff( global_cell_list[cell_id_det - 1].y_dim, cell_list[index].y_dim) >= height*delta/2  )
							{
								inactive_cell_p_id = 2;
							}	
						}
				
						else if(p_type == 1)
						{
							//Vertical partition
							//Cell is outside the active partition area
							if(global_cell_list[cell_id_det - 1].x_dim > cell_list[index].x_dim && 
							compute_abs_diff( global_cell_list[cell_id_det - 1].x_dim, cell_list[index].x_dim) >= width*delta/2)
							{
								inactive_cell_p_id = 2;
							}
							else if (global_cell_list[cell_id_det - 1].x_dim < cell_list[index].x_dim && 
							compute_abs_diff( global_cell_list[cell_id_det - 1].x_dim, cell_list[index].x_dim) >= width*delta/2)
							{
								inactive_cell_p_id = 1;
							}
						}
				
						if( partition_id != inactive_cell_p_id)
						{
							same = false;
							break;
						}	
					}
					
					
				//}
				
			}
		}
		
		if(same==true && v==true)
			net_num_all++;
		
		//if(same==true)
		//	net_num_all++
	}
	assert(net_num_all >= 0);
	cell_list[index].all_same_partition_net_count = net_num_all;
	global_cell_list[cell_id -1].all_same_partition_net_count = net_num_all;
}


//------------------------------------------------------------------------------------------------------------------------------
void update_cell_list_all_cell_net_count_4(int index, int partition_id, vector<int> cell_net_list[], int cell_count, vector<Cell> &cell_list, 
vector<Cell> detailed_net_list[], int net_count, vector<Cell> &global_cell_list, bool p_type, int mode, double delta, double width, double height,
vector<int> bucket_ds[] , int max_connect)
{
	int net_id;
	int	net_num_all =0;
	//net_num_all =0;
	int cell_id_det;
	bool same=false;
	int inactive_cell_p_id = 0;
	//bool same=false;
	//Cell_list is updated
	//int index = cell_id - 1;
	//int inactive_cell_p_id = 0;
	assert(index >= 0);
	int cell_id = cell_list[index].cell_id;
	assert(cell_id >= 1);
	
	int gain_old;
	//vector<int> net_list;
	bool v=false;
	//int inactive_cell_p_id;
	for(int i=0;i<cell_net_list[index].size();i++)
	{
		net_id = cell_net_list[index][i];
		//cout<<"net_id: "<<net_id<<endl;
		same=true;
		v = false;
		for(int j=0;j<detailed_net_list[net_id].size();j++)
		{
			cell_id_det = detailed_net_list[net_id][j].cell_id;
			v=true;
			if(cell_id_det == cell_id)
				continue;
				
			//gain_old = global_cell_list[cell_id_det - 1]
			
			else
			{
				//cout<<"cell in partition "<<cell_id_det<<"partition: "<<cell_list[cell_id_det - 1].partition_id<<endl;
				//if(global_cell_id[cell_id_det - 1].x_dim == cell_id[index].x_dim && global_cell_list[cell_id_det - 1].y_dim != cell_list[index].y_dim)
				//{
					if(global_cell_list[cell_id_det - 1].active == true)
					{
						if(partition_id != global_cell_list[cell_id_det - 1].partition_id)
						{
							same=false;
					
							break;
						}
					}
					
					else if(global_cell_list[cell_id_det - 1].active == false && mode == 3)
					{		
						//Terminal propogation window is 0
						//Cell is outside the active partition
						if(p_type == 0)
						{
							//Horizontal partition
							//cell_id_det is not in active region
							if(global_cell_list[cell_id_det - 1].y_dim > cell_list[index].y_dim &&
							compute_abs_diff( global_cell_list[cell_id_det - 1].y_dim, cell_list[index].y_dim) >= height*delta/2   )
							{
								inactive_cell_p_id = 1;
							}
							else if (global_cell_list[cell_id_det - 1].y_dim < cell_list[index].y_dim &&
							compute_abs_diff( global_cell_list[cell_id_det - 1].y_dim, cell_list[index].y_dim) >= height*delta/2  )
							{
								inactive_cell_p_id = 2;
							}	
						}
				
						else if(p_type == 1)
						{
							//Vertical partition
							//Cell is outside the active partition area
							if(global_cell_list[cell_id_det - 1].x_dim > cell_list[index].x_dim && 
							compute_abs_diff( global_cell_list[cell_id_det - 1].x_dim, cell_list[index].x_dim) >= width*delta/2)
							{
								inactive_cell_p_id = 2;
							}
							else if (global_cell_list[cell_id_det - 1].x_dim < cell_list[index].x_dim && 
							compute_abs_diff( global_cell_list[cell_id_det - 1].x_dim, cell_list[index].x_dim) >= width*delta/2)
							{
								inactive_cell_p_id = 1;
							}
						}
				
						if( partition_id != inactive_cell_p_id)
						{
							same = false;
							break;
						}	
					}
					
					
				//}
				
			}
		}
		
		if(same==true && v==true)
			net_num_all++;
		
		//if(same==true)
		//	net_num_all++
	}
	assert(net_num_all >= 0);
	cell_list[index].all_same_partition_net_count = net_num_all;
	global_cell_list[cell_id -1].all_same_partition_net_count = net_num_all;
}
//------------------------------------------------------------------------------------------------------------------------------

int
all_present_single_partition(int cell_id, int partition_id, vector<int> cell_net_list[], int cell_count, vector<Cell> cell_list, 
vector<Cell> detailed_net_list[], int net_count)
{
	int net_id;
	int	net_num_all =0;
	//net_num_all =0;
	int cell_id_det;
	bool same=false;
	//bool same=false;
	//Cell_list is updated
	int index = cell_id - 1;
	
	if(index < 0)
	{
		cout<<"Check!! "<<"cell_id: "<<cell_id<<endl;
	}
	assert(index >= 0);
	
	//vector<int> net_list;
	bool v=false;
	
	for(int i=0;i<cell_net_list[index].size();i++)
	{
		net_id = cell_net_list[index][i];
		//cout<<"net_id: "<<net_id<<"size of net: "<<detailed_net_list[net_id].size()<<endl;
		assert(net_id >= 0);
		same=true;
		v = false;
		for(int j=0;j<detailed_net_list[net_id].size();j++)
		{
			cell_id_det = detailed_net_list[net_id][j].cell_id;
			v=true;
			if(cell_id_det == cell_id)
				continue;
			
			if(cell_list[cell_id_det - 1].x_dim != cell_list[cell_id - 1].x_dim)
				continue;
			
			if(cell_list[cell_id_det - 1].y_dim != cell_list[cell_id - 1].y_dim)
				continue;
			
			else
			{
				//cout<<"cell in partition "<<cell_id_det<<"partition: "<<cell_list[cell_id_det - 1].partition_id<<endl;
				assert(cell_id_det >= 1);
				if(partition_id != cell_list[cell_id_det - 1].partition_id)
				{
					same=false;
					
					break;
				}
				
			}
		}
		
		if(same==true && v==true)
			net_num_all++;
		
		//if(same==true)
		//	net_num_all++
	}
	return net_num_all;
}


int
all_present_single_partition_2(int index, int partition_id, vector<int> cell_net_list[], int cell_count, vector<Cell> cell_list, 
vector<Cell> detailed_net_list[], int net_count, vector<Cell> global_cell_list, bool p_type, int mode, double delta, double width, double height)
{
	int net_id;
	int	net_num_all =0;
	//net_num_all =0;
	int cell_id_det;
	bool same=false;
//	double delta = 0;
	int inactive_cell_p_id = 0;
	//bool same=false;
	//Cell_list is updated
	//int index = cell_id - 1;
	int cell_id = cell_list[index].cell_id;
	assert(cell_id > 0);
	if(index < 0)
	{
		cout<<"Check!! "<<"cell_id: "<<cell_id<<endl;
	}
	assert(index >= 0);
	
	//vector<int> net_list;
	bool v=false;
	
	for(int i=0;i<cell_net_list[cell_id - 1].size();i++)
	{
		net_id = cell_net_list[cell_id - 1][i];
		//cout<<"net_id: "<<net_id<<"size of net: "<<detailed_net_list[net_id].size()<<endl;
		assert(net_id >= 0);
		same=true;
		v = false;
		for(int j=0;j<detailed_net_list[net_id].size();j++)
		{
			cell_id_det = detailed_net_list[net_id][j].cell_id;
			v=true;
			if(cell_id_det == cell_id)
				continue;
			/*
			if(global_cell_list[cell_id_det - 1].x_dim != cell_list[index].x_dim)
			{
				cout<<"different x coord\n";
				continue;
			}
				
			
			if(global_cell_list[cell_id_det - 1].y_dim != cell_list[index].y_dim)
			{
					cout<<"different y coord\n";
					continue;
			}
			*/
			if(global_cell_list[cell_id_det - 1].active == true)
			{
			//else if(global_cell_list[cell_id_det - 1].x_dim == cell_list[index].x_dim && global_cell_list[cell_id_det - 1].y_dim == cell_list[index].y_dim)
			//{
				//cout<<"cell in partition "<<cell_id_det<<"partition: "<<cell_list[cell_id_det - 1].partition_id<<endl;
			//	assert(cell_id_det >= 1);
				//assert(cell_id_det <= cell_count);
				assert(global_cell_list[cell_id_det - 1].partition_id == 1 || global_cell_list[cell_id_det - 1].partition_id ==2);
				if(partition_id != global_cell_list[cell_id_det - 1].partition_id)
				{
					same=false;
					
					break;
				}
				
			}
			else if(global_cell_list[cell_id_det - 1].active == false && mode == 3)
			{
				//Terminal propogation window is 0
				//Cell is outside the active partition
				if(p_type == 0)
				{
					
					//Horizontal partition
					//cell_id_det is not in active region
					if(global_cell_list[cell_id_det - 1].y_dim >= cell_list[index].y_dim  && 
					compute_abs_diff( global_cell_list[cell_id_det - 1].y_dim, cell_list[index].y_dim) >= height*delta/2    )
					{
						assert(compute_abs_diff( global_cell_list[cell_id_det - 1].y_dim, cell_list[index].y_dim) >= 0);
						inactive_cell_p_id = 1;
					}
					else if (global_cell_list[cell_id_det - 1].y_dim < cell_list[index].y_dim + (height*delta)/2 &&
					compute_abs_diff( global_cell_list[cell_id_det - 1].y_dim, cell_list[index].y_dim) >= height*delta/2)
					{
						assert(compute_abs_diff( global_cell_list[cell_id_det - 1].y_dim, cell_list[index].y_dim) >= 0);
						inactive_cell_p_id = 2;
					}	
				}
				
				else if(p_type == 1)
				{
					//Vertical partition
					//Cell is outside the active partition area
					if(global_cell_list[cell_id_det - 1].x_dim > cell_list[index].x_dim &&
					compute_abs_diff( global_cell_list[cell_id_det - 1].x_dim, cell_list[index].x_dim) >= width*delta/2 )
					{
						assert(compute_abs_diff( global_cell_list[cell_id_det - 1].x_dim, cell_list[index].x_dim) >= 0);
						inactive_cell_p_id = 2;
					}
					else if (global_cell_list[cell_id_det - 1].x_dim < cell_list[index].x_dim + delta && 
					compute_abs_diff( global_cell_list[cell_id_det - 1].x_dim, cell_list[index].x_dim) >= width*delta/2)
					{
						inactive_cell_p_id = 1;
					}
				}
				
				if( partition_id != inactive_cell_p_id)
				{
					same = false;
					break;
				}	
			}
		}
		
		if(same==true && v==true)
			net_num_all++;
		
		//if(same==true)
		//	net_num_all++
	}
	return net_num_all;
}

/*
int
all_present_single_partition_2(int index, int partition_id, vector<int> cell_net_list[], int cell_count, vector<Cell> cell_list, 
vector<Cell> detailed_net_list[], int net_count)
{
	int net_id;
	int	net_num_all =0;
	//net_num_all =0;
	int cell_id_det;
	bool same=false;
	//bool same=false;
	//Cell_list is updated
//	int index = cell_id - 1;
//	assert(index>=0);
//	if(index < 0)
//	{
//		cout<<"Check!! "<<"cell_id: "<<cell_id<<endl;
//	}
	assert(index >= 0);
	
	//vector<int> net_list;
	bool v=false;
	
	for(int i=0;i<cell_net_list[index].size();i++)
	{
		net_id = cell_net_list[index][i];
		//cout<<"net_id: "<<net_id<<endl;
		assert(net_id >= 0);
		same=true;
		v = false;
		for(int j=0;j<detailed_net_list[net_id].size();j++)
		{
			cell_id_det = detailed_net_list[net_id][j].cell_id;
			v=true;
			if(cell_id_det == cell_id)
				continue;
			
			if(cell_list[cell_id_det - 1].x_dim != cell_list[index].x_dim)
				continue;
			
			if(cell_list[cell_id_det - 1].y_dim != cell_list[index].y_dim)
				continue;
			
			else
			{
				//cout<<"cell in partition "<<cell_id_det<<"partition: "<<cell_list[cell_id_det - 1].partition_id<<endl;
				assert(cell_id_det >= 1);
				if(partition_id != cell_list[cell_id_det - 1].partition_id)
				{
					same=false;
					
					break;
				}
				
			}
		}
		
		if(same==true && v==true)
			net_num_all++;
		
		//if(same==true)
		//	net_num_all++
	}
	return net_num_all;
}
*/
int get_max_connectivity(vector<int> cell_net_list[], int cell_count)
{
	int size_max=0;
	int size;
	for(int i=0;i<cell_count;i++)
	{
	//	if(cell_list[i].cell_id == 0)
	//		continue;
		
		size= cell_net_list[i].size();
		if(size > size_max)
		{
			size_max = size;
		}
	}
	return size_max;
}

void initialise_cell_list_fm_metric(vector<int> cell_net_list[], int cell_count, vector<Cell> &cell_list, vector<Cell> detailed_net_list[], int net_count)
{
	int x_all;
	int x_only;
	int cell_id;
	int p_id;
	//cout<<"inside function initialise_cell_list_fm_metric";
	for(int i=0;i<cell_count;i++)
	{
		cell_id = cell_list[i].cell_id;
		if(cell_id== 0)
			continue;
		p_id = cell_list[i].partition_id;
	//	cout<<"i: "<<i<<endl;
		//all_present_single_partition(int cell_id, int partition_id, vector<int> cell_net_list[], int cell_count, vector<Cell> cell_list, 
		//vector<Cell> detailed_net_list[], int net_count)
		x_all = all_present_single_partition(cell_id, p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
	//	cout<<"test_init"<<endl;
		cell_list[i].all_same_partition_net_count = x_all;
		
		x_only = only_cell(cell_id,p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
		cell_list[i].only_cell_net_count = x_only;
	}
	//cout<<"done with function"<<endl;
}

void initialise_cell_list_fm_metric_test(vector<int> cell_net_list[], int cell_count, vector<Cell> &cell_list, vector<Cell> detailed_net_list[], int net_count,
vector<Cell> &global_cell_list, bool p_type, int mode, double delta, double width, double height, vector<int> bucket_ds[], int max_connect)
{
	int x_all=0;
	int x_only=0;
	int cell_id;
	int p_id;
//	cout<<"inside function initialise_cell_list_fm_metric\n";
	//for(int i=0;i<cell_count;i++)
	for(int i=0;i<cell_list.size();i++)
	{
		cell_id = cell_list[i].cell_id;
		p_id = cell_list[i].partition_id;
		assert(p_id == 1 || p_id == 2);
	//	cout<<"i: "<<i<<endl;
		//all_present_single_partition(int cell_id, int partition_id, vector<int> cell_net_list[], int cell_count, vector<Cell> cell_list, 
		//vector<Cell> detailed_net_list[], int net_count)
		
		if(cell_id != 0)
		{
			//x_all = all_present_single_partition(cell_id, p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
			x_all = all_present_single_partition_2(i, p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count,global_cell_list, p_type, mode, delta, width, height);
			//cout<<"computed x_all "<<"i: "<<i<<endl;
			//cout<<"i: "<<i<<" cell_id: "<<cell_id<<" p_id: "<<p_id<<" cell_count: "<<cell_count<<endl;
			assert(x_all >= 0);
			//cout<<"x_all: "<<x_all<<" i: "<<i<<endl;
			//cout<<"x_all: "<<x_all<<endl;
		//cout<<"test_init"<<endl;
			cell_list[i].all_same_partition_net_count = x_all;
			global_cell_list[i].all_same_partition_net_count = x_all;
		//x_only = only_cell(cell_id,p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
		x_only = only_cell_2(i,p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count,global_cell_list, p_type, mode, delta, width, height);
		assert(x_only >= 0);
		cell_list[i].only_cell_net_count = x_only;
		global_cell_list[cell_id - 1].only_cell_net_count = x_only;
		
		bucket_ds[x_only - x_all + max_connect].push_back(i);
		}
	}
//	cout<<"done with function"<<endl;
	
}

bool is_area_constraint_violated(int cell_id, int dest_partition_id, int p1_id, int p2_id, vector<Cell> cell_list, int threshold, int cell_count)
{
	int p;
	int p1_count=0;
	int p2_count=0;
	
	int index = cell_id - 1;
	assert(index >=0);
	
	int p_id_cell_id = cell_list[index].partition_id;
	for(int i=0;i<cell_count;i++)
	{
		if(cell_list[i].cell_id ==0)
			continue;
		
		if(cell_list[i].partition_id == p1_id)
		{
			p1_count++;
		}
		else if(cell_list[i].partition_id == p2_id)
		{
			p2_count++;
		}
	}
	//cout<<"p1_count: "<<p1_count<<" p2_count: "<<p2_count<<endl;
	if(dest_partition_id == p1_id)
	{
		p2_count--;
	}
	else if(dest_partition_id == p2_id)
	{
		p1_count--;
	}
	
	int diff = p1_count - p2_count;
	//cout<<"diff: "<<diff<<endl;
	if(diff < 0)
		diff = -diff;
	
	assert(diff>=0);
	
	if(diff <= threshold)
		return false;
	
	else
		return true;
}

bool is_area_constraint_violated_2(int index, int dest_partition_id, int p1_id, int p2_id, vector<Cell> cell_list, int threshold, int cell_count)
{
	int p;
	int p1_count=0;
	int p2_count=0;
//	cout<<"inside area constraint check func : threshold: "<<threshold<<"  ";
	//int index = cell_id - 1;
	assert(index >=0);
	
	int p_id_cell_id = cell_list[index].partition_id;
	for(int i=0;i<cell_count;i++)
	{
		if(cell_list[i].cell_id ==0)
			continue;
		
		if(cell_list[i].partition_id == p1_id)
		{
			p1_count++;
		}
		else if(cell_list[i].partition_id == p2_id)
		{
			p2_count++;
		}
	}
//	cout<<"p1_count: "<<p1_count<<" p2_count: "<<p2_count<<" ";
	if(dest_partition_id == p1_id)
	{
		p2_count--;
	}
	else if(dest_partition_id == p2_id)
	{
		p1_count--;
	}
	
	int diff = p1_count - p2_count;
//	cout<<"diff: "<<diff<<endl;
	if(diff < 0)
		diff = -diff;
	
	assert(diff>=0);
	
	if(diff <= threshold)
		return false;
	
	else
		return true;
}

void FM_Algorithm(vector<Cell> &cell_list, int cell_count, vector<int> cell_net_list[], vector<Cell> detailed_net_list[], int net_count , int initial_cutsize,
int threshold,vector<Cell> adjacent_list[], vector<Cell> reduced_adjacent_list[], int initial_cut_size, int max_connect)
{
	map<int,int> bucket_list;
	int p1 = 1;
	int p2 = 2;
	bool area_constraint;
	int cell_id;
	int cell_p_id;
	int cell_dest_p_id;
	int all_locked;
	int only_cell_count=0, all_cell_count=0;
	int gain=-1;
	int gain_max;
	int th1= cell_count/4;
	int diff_cutsize;
	int size_bucket = (2*max_connect) + 1;
	
	vector<int> b_list[size_bucket];
	int cell_last=0;
	int cell_present=0;
	int cell_replace=0;
	//do
	//{
	unlock_all_cells(cell_list);
	int count=-1;
	int th2 = 10;
	int count2=-1;
	while(get_unlocked_cell_id(cell_list) != -1)
	{
		count++;
		
		if(count2 > th2)
		{
			cout<<"threshold2 reached\n";
			break;
		}
		
		if(count ==th1)
		{
			cout<<"threshold3 reached\n";
			break;
		}
			
	//	if(gain == 0)
	//		break;
	//	cout<<"unlocked cell count: "<<count_unlocked_cell(cell_list)<<endl;
	 bucket_list.clear();
	 
	 for(int y=0;y<size_bucket;y++)
	 {
	 	b_list[y].clear();
	 }
	 for(int i=0;i<cell_count;i++)
	 {
	 		//cout<<"Hello"<<endl;
	 		all_locked = get_unlocked_cell_id(cell_list);
	 		if(all_locked == -1)
	 			break;
	 		if(cell_list[i+1].locked == true)
	 			continue;
	 		//cout<<"Hello"<<endl;
	 		cell_id = i+1;
	 		cell_p_id = cell_list[i].partition_id;
	 		
	 		if(cell_p_id == p1)
	 		{
	 			cell_dest_p_id = p2;	
			}
			else if(cell_p_id == p2)
			{
				cell_dest_p_id = p1;
			}
			area_constraint = is_area_constraint_violated(cell_id,cell_dest_p_id,p1,p2,cell_list,threshold,cell_count);
			
			//if(count > 10000)
			  // cout<<"cell_id: "<<cell_id<<"area constraint: "<<area_constraint<<"count unlocked cell: "<<count_unlocked_cell(cell_list)<<endl;
			
			if(area_constraint==true && count_unlocked_cell(cell_list)==1 && get_unlocked_cell_id(cell_list) == i+1)
			{
					lock_cell(i+1,cell_list);
					break;	
			}
			
			
			if(area_constraint==true)
			{
				//cout<<"Area violation\n";
				continue;
			}
			
			//cout<<"Hello"<<endl;
			only_cell_count = only_cell(cell_id,cell_p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
			all_cell_count = all_present_single_partition(cell_id,cell_p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
			
			gain = only_cell_count - all_cell_count;
			assert(gain + max_connect >= 0);
			b_list[gain+max_connect].push_back(cell_id);
			bucket_list.insert({cell_id,gain});
		
			//cout<<"cell: "<<cell_id<<" gain: "<<gain<<endl;
	 }
	 
	 		for(int h=size_bucket-1; h>=0; h--)
			{
				if(!b_list[h].empty())
				{
					cell_replace = b_list[h][0];
					cell_present= cell_replace;
					
					int dest_p_id1;
					if(cell_list[cell_replace - 1].partition_id == p1)
						dest_p_id1 = p2;
					else if(cell_list[cell_replace - 1].partition_id == p2)
						dest_p_id1 = p1;
				
				//if(count > 300)	
				//	cout<<"cell to move (b_list):"<<cell_replace<<" from "<<cell_list[cell_replace-1].partition_id<<" to "<<dest_p_id1<<"gain: "<<h - max_connect<<endl;
					
					set_cell_partition_id(cell_replace,dest_p_id1,cell_list,adjacent_list,cell_count);
					lock_cell(cell_replace,cell_list);
					gain_max = h - max_connect;
					if(cell_last !=0 && cell_last== cell_present && gain_max <= 0)
					{
						count2++;
						//cout<<"count2: "<<count2<<endl;
					}
					else
						count2=0;
			
					cell_last=cell_present;
					
					
					break;
				}
			}
		/*
	 	if(!bucket_list.empty())
	 	{
	 		//make_heap(bucket_list.begin(),bucket_list.end());
			auto max = get_max(bucket_list);
			gain_max = max.second;
			cell_present= max.first;
			
			if(cell_last !=0 && cell_last== cell_present && gain_max >= 0)
			{
				count2++;
				//cout<<"count2: "<<count2<<endl;
			}
			else
				count2=0;
			
			cell_last=cell_present;
	
			int dest_p_id1;
			if(cell_list[max.first - 1].partition_id == p1)
				dest_p_id1 = p2;
			else if(cell_list[max.first - 1].partition_id == p2)
				dest_p_id1 = p1;
			
			for(int h=size_bucket-1; h>=0; h--)
			{
				if(!b_list[h].empty())
				{
					cout<<"cell to move (b_list):"<<b_list[h][0]<<" gain: "<<h - max_connect<<endl;
					break;
				}
			}
		
			cout<<"Moving cell "<<max.first<<" from "<<cell_list[max.first - 1].partition_id<<" to "<<dest_p_id1<<" gain: "<<gain<<endl;
			set_cell_partition_id(max.first,dest_p_id1,cell_list,adjacent_list,reduced_adjacent_list,cell_count);
			lock_cell(max.first,cell_list);
			
			//if(gain  <= 0)
			//	break;
		}	
		else
			cout<<"bucket is empty"<<endl;
		*/
		
		
		
		
    }
    update_detailed_netlist(cell_list,detailed_net_list,net_count);
	int new_cut_size = calculate_cutsize(detailed_net_list,net_count);
	//cout<<"new cutsize: "<<new_cut_size<<endl;
	diff_cutsize = initial_cut_size - new_cut_size;
	initial_cut_size = new_cut_size;
	
	//cout<<"Partition1 count: "<<get_partition_count(cell_list,p1)<<" partition2_count: "<<get_partition_count(cell_list,p2)<<endl;
	//}while(diff_cutsize > 0);
}


/* Original FM algorithm
void FM_Algorithm_3(vector<Cell> &cell_list, int cell_count, vector<int> cell_net_list[], vector<Cell> detailed_net_list[], int net_count , int initial_cutsize,
int threshold,vector<Cell> adjacent_list[], int initial_cut_size, int max_connect, int start_cell_count, int end_cell_count, int f_id)
{
	map<int,int> bucket_list;
	int p1 = 1;
	int p2 = 2;
	bool area_constraint;
	int cell_id;
	int cell_p_id;
	int cell_dest_p_id;
	int all_locked;
	int only_cell_count=0, all_cell_count=0;
	int gain=-1;
	int gain_max;
	int th1= cell_count/3;
	int diff_cutsize;
	int size_bucket = (2*max_connect) + 1;
	int threshold1 = (0.1*cell_count)+1;
	//cout<<"Threshold for area: "<<threshold1<<endl;
	vector<int> b_list[size_bucket];
	int cell_last=0;
	int cell_present=0;
	int cell_replace=0;
	//int int threshold1 = (0.1*cell_count)+1;
	//do
	//{
	unlock_all_cells(cell_list);
	int count=-1;
	int th2 = 10;
	int count2=-1;
	while(get_unlocked_cell_id(cell_list) != -1)
	{
		count++;
		
		if(count2 > th2)
		{
	//		cout<<"threshold2 reached\n";
			break;
		}
	
		if(count ==th1)
		{
	//		cout<<"threshold3 reached\n";
			break;
		}
		
		//gain=0;
		//if(gain == 0)
		//	break;
	//	cout<<"unlocked cell count: "<<count_unlocked_cell(cell_list)<<endl;
	 bucket_list.clear();
	 
	 for(int y=0;y<size_bucket;y++)
	 {
	 	b_list[y].clear();
	 }
	 for(int i=start_cell_count;i<end_cell_count;i++)
	 {
	 		if(cell_list[i].cell_id ==0)
			continue;
	 		//cout<<"Hello"<<endl;
	 		all_locked = get_unlocked_cell_id(cell_list);
	 		if(all_locked == -1)
	 			break;
	 		//if(cell_list[i+1].locked == true)
	 		//	continue;
	 		//cout<<"Hello"<<endl;
	 		//cell_id = i+1;
	 		cell_id = cell_list[i].cell_id;
	 		
			
	 		cell_p_id = cell_list[i].partition_id;
	 		
	 		if(cell_p_id == p1)
	 		{
	 			cell_dest_p_id = p2;	
			}
			else if(cell_p_id == p2)
			{
				cell_dest_p_id = p1;
			}
			//area_constraint = is_area_constraint_violated(cell_id,cell_dest_p_id,p1,p2,cell_list,threshold,cell_count);
			area_constraint = is_area_constraint_violated_2(i,cell_dest_p_id,p1,p2,cell_list,threshold1,cell_count);
			//if(count > 10000)
			  // cout<<"cell_id: "<<cell_id<<"area constraint: "<<area_constraint<<"count unlocked cell: "<<count_unlocked_cell(cell_list)<<endl;
			
			if(area_constraint==true && count_unlocked_cell(cell_list)==1 && get_unlocked_cell_id(cell_list) == i+1)
			{
					//lock_cell(i+1,cell_list);
					lock_cell_2(i,cell_list);
					break;	
			}
			
			
			if(area_constraint==true)
			{
				//cout<<"Area violation\n";
				
				continue;
			}
			assert(cell_id >= 1);
			//cout<<"Hello"<<endl;
			//only_cell_count = only_cell(cell_id,cell_p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
			only_cell_count = cell_list[i].only_cell_net_count;
			//if(only_cell_count < 0)
			//{
			//	cout<<"cell_id: "<<cell_id
			//}
			assert(only_cell_count >=0);
			
			//all_cell_count = all_present_single_partition(cell_id,cell_p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
			all_cell_count = cell_list[i].all_same_partition_net_count;
			assert(all_cell_count >= 0);
			gain = only_cell_count - all_cell_count;
			if(gain+max_connect < 0)
			{
				cout<<"only_cell_count: "<<only_cell_count<<" all_cell_count: "<<all_cell_count<<"gain: "<<gain<<" max_connect: "<<max_connect<<" f_id:  "<<f_id<<" start_cell: "<<start_cell_count<<" cell_id: "<<cell_id<<endl;
			}
			assert(gain + max_connect >= 0);
			b_list[gain+max_connect].push_back(cell_id);
			//bucket_list.insert({cell_id,gain});
		
			//cout<<"cell: "<<cell_id<<" gain: "<<gain<<endl;
	 }
	 	
	 		for(int h=size_bucket-1; h>=0; h--)
			{
				if(!b_list[h].empty())
				{
					cell_replace = b_list[h][0];
					cell_present= cell_replace;
					
					int dest_p_id1;
					if(cell_list[cell_replace - 1].partition_id == p1)
						dest_p_id1 = p2;
					else if(cell_list[cell_replace - 1].partition_id == p2)
						dest_p_id1 = p1;
				
				//if(count > 300)	
					//cout<<"cell to move (b_list):"<<cell_replace<<" from "<<cell_list[cell_replace-1].partition_id<<" to "<<dest_p_id1<<"gain: "<<h - max_connect<<"count: "<<count<<endl;
					
					set_cell_partition_id(cell_replace,dest_p_id1,cell_list,adjacent_list,cell_count);
					//cell_ptr.push_back(&cell_list[cell_replace - 1]);
					lock_cell(cell_replace,cell_list);
					assert(cell_list[cell_replace - 1].locked==true);
					//cout<<"locking cell: "<<cell_replace<<endl;
					gain_max = h - max_connect;
					if(cell_last !=0 && cell_last== cell_present)
					{
						count2++;
						//cout<<"count2: "<<count2<<endl;
					}
					else
						count2=0;
			
					cell_last=cell_present;
					
					//update the fm metric for neighbor of cell_replace
					update_cell_list_all_cell_net_count(cell_replace,dest_p_id1,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
					update_cell_list_fm_only_cell_net_count(cell_replace,dest_p_id1,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
					for(int g=0; g<adjacent_list[cell_replace - 1].size();g++)
					{
						int adj_cell_id = adjacent_list[cell_replace - 1][g].cell_id;
						
					//	if(adj_cell_id >= start_cell_count && adj_cell_id <= end_cell_count)
					//	{
							int adj_cell_p_id = cell_list[adj_cell_id - 1].partition_id;
							update_cell_list_all_cell_net_count(adj_cell_id,adj_cell_p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
							update_cell_list_fm_only_cell_net_count(adj_cell_id,adj_cell_p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
					//	}	
					}
					//---------------------------------------------
					break;
				}
			}
    }
    update_detailed_netlist(cell_list,detailed_net_list,net_count);
	int new_cut_size = calculate_cutsize(detailed_net_list,net_count);
	cout<<"new cutsize: "<<new_cut_size<<endl;
	diff_cutsize = initial_cut_size - new_cut_size;
	initial_cut_size = new_cut_size;
	
	cout<<"Partition1 count: "<<get_partition_count(cell_list,p1)<<" partition2_count: "<<get_partition_count(cell_list,p2)<<endl;
	//}while(diff_cutsize > 0);
}


*/
//------------------------------------------------------------------------------------------------
void FM_Algorithm_3(vector<Cell> &cell_list, int cell_count, vector<int> cell_net_list[], vector<Cell> detailed_net_list[], int net_count , int initial_cutsize,
int threshold,vector<Cell> adjacent_list[], int initial_cut_size, int max_connect, int start_cell_count, int end_cell_count, int f_id, vector<Cell> &global_cell_list, 
bool p_type, int mode, double delta, double width, double height)
{
//	cout<<"inside FM algo"<<endl;
	map<int,int> bucket_list;
	int p1 = 1;
	int p2 = 2;
	bool area_constraint;
	int cell_id;
	int cell_p_id;
	int cell_dest_p_id;
	int all_locked;
	int only_cell_count=0, all_cell_count=0;
	int gain=-1;
	int gain_max=0;
	int th1= cell_count/2;
	int diff_cutsize;
	int size_bucket = (2*max_connect) + 1;
	int threshold1 = (0.2*cell_count)+1;
//	cout<<"Threshold for area: "<<threshold1<<endl;
	vector<int> b_list[size_bucket];
	int cell_last=0;
	int cell_present_index=0;
	int cell_present=0;
	int cell_replace_index=0;
	int gain_sum=-1;
	//int int threshold1 = (0.1*cell_count)+1;
	do
	{
	unlock_all_cells(cell_list);
	int count=-1;
	int th2 = 10;
	int count2=-1;
	while(get_unlocked_cell_id_2(cell_list) != -1)
	{
		count++;
		
		if(count2 > th2)
		{
	//		cout<<"threshold2 reached\n";
			break;
		}
	
		if(count ==th1)
		{
	//		cout<<"threshold3 reached\n";
			break;
		}
		
		//gain=0;
		if(gain_max < 0)
			break;
	//	cout<<"unlocked cell count: "<<count_unlocked_cell(cell_list)<<endl;
	 //bucket_list.clear();
	 
	 for(int y=0;y<size_bucket;y++)
	 {
	 	b_list[y].clear();
	 }
	 for(int i=start_cell_count;i<end_cell_count;i++)
	 {
			//cout<<"i: "<<i<<endl;
	 		if(cell_list[i].cell_id ==0)
			continue;
			
			if(cell_list[i].locked == true)
				continue;
	 		//cout<<"Hello"<<endl;
	 		all_locked = get_unlocked_cell_id_2(cell_list);
	 		if(all_locked == -1)
	 			break;
	 		//if(cell_list[i+1].locked == true)
	 		//	continue;
	 		//cout<<"Hello"<<endl;
	 		//cell_id = i+1;
	 		cell_id = cell_list[i].cell_id;
	 		
			
	 		cell_p_id = cell_list[i].partition_id;
	 		
	 		if(cell_p_id == p1)
	 		{
	 			cell_dest_p_id = p2;	
			}
			else if(cell_p_id == p2)
			{
				cell_dest_p_id = p1;
			}
			//area_constraint = is_area_constraint_violated(cell_id,cell_dest_p_id,p1,p2,cell_list,threshold,cell_count);
			area_constraint = is_area_constraint_violated_2(i,cell_dest_p_id,p1,p2,cell_list,threshold1,cell_count);
			//if(count > 10000)
			  // cout<<"cell_id: "<<cell_id<<"area constraint: "<<area_constraint<<"count unlocked cell: "<<count_unlocked_cell(cell_list)<<endl;
			
			if(area_constraint==true && count_unlocked_cell(cell_list)==1)
			{
					//lock_cell(i+1,cell_list);
				//	lock_cell_2(i,cell_list);
					break;	
			}
			
			
			if(area_constraint==true)
			{
				//cout<<"Area violation\n";
				
				continue;
			}
			assert(cell_id >= 1);
			//cout<<"Hello"<<endl;
			//only_cell_count = only_cell(cell_id,cell_p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
			//assert(cell_list[i].all_same_partition_net_count == global_cell_list[cell_id - 1].all_same_partition_net_count);
			//assert(cell_list[i].only_cell_net_count == global_cell_list[cell_id - 1].only_cell_net_count);
			//only_cell_count = cell_list[i].only_cell_net_count;
			only_cell_count = global_cell_list[cell_id - 1].only_cell_net_count;
			
			assert(only_cell_count >= 0);
			
			//all_cell_count = all_present_single_partition(cell_id,cell_p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
			//all_cell_count = cell_list[i].all_same_partition_net_count;
			
			all_cell_count = global_cell_list[cell_id - 1].all_same_partition_net_count;
			
			assert(all_cell_count >= 0);
			gain = only_cell_count - all_cell_count;
			if(gain+max_connect < 0)
			{
				cout<<"only_cell_count: "<<only_cell_count<<" all_cell_count: "<<all_cell_count<<"gain: "<<gain<<" max_connect: "<<max_connect<<" f_id:  "<<f_id<<" start_cell: "<<start_cell_count<<" cell_id: "<<cell_id<<endl;
			}
			assert(gain + max_connect >= 0);
			//b_list[gain+max_connect].push_back(cell_id);
			b_list[gain+max_connect].push_back(i);
			//bucket_list.insert({cell_id,gain});
		
			//cout<<"cell: "<<cell_id<<" gain: "<<gain<<endl;
	 }
	 	
	 		for(int h=size_bucket-1; h>=0; h--)
			{
				if(!b_list[h].empty())
				{
					cell_replace_index = b_list[h][0];
					cell_present_index = cell_replace_index;
					assert(cell_replace_index >= 0);
					int dest_p_id1;
					
					if(cell_list[cell_replace_index].partition_id == p1)
						dest_p_id1 = p2;
					else if(cell_list[cell_replace_index].partition_id == p2)
						dest_p_id1 = p1;
					/*	
					if(cell_list[cell_replace - 1].partition_id == p1)
						dest_p_id1 = p2;
					else if(cell_list[cell_replace - 1].partition_id == p2)
						dest_p_id1 = p1;
					*/
				
				//if(count > 300)	
					//cout<<"cell to move (b_list): "<<cell_present<<" from "<<cell_list[cell_replace-1].partition_id<<" to "<<dest_p_id1<<"gain: "<<h - max_connect<<"count: "<<count<<endl;
					
					
					//Update local cell list and global cell list
					set_cell_partition_id_2(cell_replace_index,dest_p_id1,cell_list,adjacent_list,cell_count,global_cell_list);
					//------------------------------------------------------------
					
					//cell_ptr.push_back(&cell_list[cell_replace - 1]);
					lock_cell_2(cell_replace_index,cell_list);
					assert(cell_list[cell_replace_index].locked==true);
					//cout<<"locking cell: "<<cell_replace<<endl;
					gain_max = h - max_connect;
					gain_sum = gain_sum + gain_max;
					cell_present = cell_list[cell_replace_index].cell_id;
			//		cout<<"cell to move (b_list):"<<cell_present<<" gain: "<<h - max_connect<<" count: "<<count<<endl;
				//	cout<<"updated global list"<<endl;
					assert(cell_present > 0);
				//	cout<<"cell_present: "<<cell_present<<" "<<global_cell_list.size()<<endl;
				//	cout<<global_cell_list[0].cell_id<<endl;
					//global_cell_list[cell_present - 1].partition_id = dest_p_id1;
					 
					
					if(cell_last !=0 && cell_last== cell_present)
					{
						count2++;
						//cout<<"count2: "<<count2<<endl;
					}
					else
						count2=0;
			
					cell_last=cell_present;
					
					//update the fm metric for neighbor of cell_replace
					update_cell_list_all_cell_net_count_2(cell_replace_index,dest_p_id1,cell_net_list,cell_count,cell_list,detailed_net_list,net_count,global_cell_list, p_type, mode, delta, width, height);
					update_cell_list_fm_only_cell_net_count_2(cell_replace_index,dest_p_id1,cell_net_list,cell_count,cell_list,detailed_net_list,net_count,global_cell_list, p_type, mode, delta, width, height);
					
					for(int g=0; g<adjacent_list[cell_present - 1].size();g++)
					{
						int adj_cell_id = adjacent_list[cell_present - 1][g].cell_id;
						assert(adj_cell_id >= 1);
					//	if(adj_cell_id >= start_cell_count && adj_cell_id <= end_cell_count)
					//	{
						//	int adj_cell_p_id = cell_list[adj_cell_id - 1].partition_id;
							int adj_cell_p_id = global_cell_list[cell_present - 1].partition_id;
							
							if(global_cell_list[adj_cell_id - 1].active == true)
							{
								//update_cell_list_all_cell_net_count(adj_cell_id,adj_cell_p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
								update_cell_list_all_cell_net_count_3(adj_cell_id,adj_cell_p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count,global_cell_list);
								//update_cell_list_fm_only_cell_net_count(adj_cell_id,adj_cell_p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count);
								update_cell_list_fm_only_cell_net_count_3(adj_cell_id,adj_cell_p_id,cell_net_list,cell_count,cell_list,detailed_net_list,net_count,global_cell_list);
							}
					//	}	
					}
					//---------------------------------------------
					break;
				}
			}
    }
    update_detailed_netlist(cell_list,detailed_net_list,net_count);
	int new_cut_size = calculate_cutsize(detailed_net_list,net_count);
	cout<<"new cutsize: "<<new_cut_size<<endl;
	diff_cutsize = initial_cut_size - new_cut_size;
	initial_cut_size = new_cut_size;
	cout<<"f_id: "<<f_id<<endl;	
	cout<<"Partition1 count: "<<get_partition_count(cell_list,p1)<<" partition2_count: "<<get_partition_count(cell_list,p2)<<endl;
	}while(diff_cutsize > 0);
}




//----------------------------------------------------------------------------------------------------------------------------------------------


/*
void apply_FM_Algorithm(vector<Cell> &cell_list, int cell_count, vector<int> cell_net_list[], vector<Cell> detailed_net_list[], int net_count , int initial_cutsize,
int threshold,vector<Cell> adjacent_list[], int initial_cut_size, int max_connect)
{
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,0,cell_count/8);
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,cell_count/8 + 1,cell_count/4);
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,cell_count/4 + 1,(3*cell_count)/8);
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,((3*cell_count)/8) + 1,cell_count/2);
	
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect, (cell_count/2) + 1,(5*cell_count)/8);
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect, (5*cell_count)/8 + 1,(3*cell_count)/4);
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,(3*cell_count)/4 + 1, (7*cell_count)/8 );
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,(7*cell_count)/8 + 1,cell_count);
}
*/
void apply_FM_Algorithm(vector<Cell> &cell_list, int cell_count, vector<int> cell_net_list[], vector<Cell> detailed_net_list[], int net_count , int initial_cutsize
,vector<Cell> adjacent_list[], int initial_cut_size, int max_connect, vector<Cell> &cell_ptr_p1, vector<Cell> &cell_ptr_p2,bool p_type,
vector<Cell> &global_cell_list, double x_coord, double y_coord, double width, double height, int mode, double delta)
{
		int p1 = 1;
		int p2 = 2;
	//	map<int,int> gain_record;
	//	double x_coord = 0;
	//	double y_coord = 0;
		cout<<"In apply_FM_algorithm function : cell count: "<<cell_count<<endl;
	//	initialise_cell_list(cell_list);
		initialise_cell_list_2(cell_list,global_cell_list);
		vector<int> bucket_ds[2*max_connect + 1];
		//cout<<"initial partition 1 count: "<<get_partition_count(cell_list,1)<<" initial partition 2 count: "<<get_partition_count(cell_list,2)<<endl;
		//cout<<"Hello"<<endl;
		initialise_cell_list_fm_metric_test(cell_net_list,cell_count,cell_list,detailed_net_list,net_count,global_cell_list, p_type, 
		mode, delta, width, height, bucket_ds, max_connect);
	//	cout<<"size of map: "<<gain_record.size()<<endl;
		int threshold = (0.1*cell_count)+1;
//		unlock_all_cells(cell_list);
//		cout<<"unlocked all cells"<<endl;
		//vector<Cell*> cell_ptr;
		//if(cell_count < 500)
		//	return;
/*		
		if(cell_count > 1500)
		{
			cout<<"cell count more than 1500"<<endl;
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,0,cell_count/8,1,global_cell_list, 
		p_type, mode, delta, width, height);
		
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,cell_count/8 + 1,cell_count/4,2,global_cell_list, 
		p_type, mode, delta, width, height);
		//cout<<"size2: "<<cell_ptr.size()<<endl;
		
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,cell_count/4 + 1,(3*cell_count)/8,3,global_cell_list, 
		p_type, mode, delta, width, height);
		//cout<<"size3: "<<cell_ptr.size()<<endl;
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,((3*cell_count)/8) + 1, cell_count/2,4,global_cell_list,
		p_type, mode, delta, width, height);
		//cout<<"size4: "<<cell_ptr.size()<<endl;
		
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect, (cell_count/2) + 1,(5*cell_count)/8,5,global_cell_list, 
		p_type, mode, delta, width, height);
		//cout<<"size5: "<<cell_ptr.size()<<endl;
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect, (5*cell_count)/8 + 1,(3*cell_count)/4,6,global_cell_list, 
		p_type, mode, delta, width , height);
		//cout<<"size6: "<<cell_ptr.size()<<endl;
		
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,(3*cell_count)/4 + 1, (7*cell_count)/8,7 ,global_cell_list,
		 p_type, mode, delta, width, height);
		//cout<<"size7: "<<cell_ptr.size()<<endl;
		FM_Algorithm_3(cell_list,cell_count/8,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,(7*cell_count)/8 + 1,cell_count,8,global_cell_list, 
		p_type, mode, delta, width, height);
		//cout<<"size8: "<<cell_ptr.size()<<endl;
		}
		else if (cell_count > 1000)
		{
			cout<<"cell count more than 1000"<<endl;
			FM_Algorithm_3(cell_list,cell_count/4,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,0,cell_count/4,1,global_cell_list, 
			p_type, mode, delta, width, height);
			FM_Algorithm_3(cell_list,cell_count/4,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,cell_count/4 + 1,cell_count/2,2,global_cell_list,
			p_type, mode, delta, width, height);
			FM_Algorithm_3(cell_list,cell_count/4,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,cell_count/2 + 1,(3*cell_count)/4,3,global_cell_list,
			p_type, mode, delta, width, height);
			FM_Algorithm_3(cell_list,cell_count/4,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,(3*cell_count)/4 + 1,cell_count,4,global_cell_list, 
			p_type, mode, delta, width, height);
		}
		else
		{
			cout<<"cell count less than 1000"<<endl;
			FM_Algorithm_3(cell_list,cell_count/2,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,0,cell_count/2,1,global_cell_list,
			 p_type, mode, delta, width, height);
			FM_Algorithm_3(cell_list,cell_count/2,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,cell_count/2 + 1,cell_count,2,global_cell_list, 
			p_type, mode, delta, width, height);	
		}

*/		
	    FM_Algorithm_3(cell_list,cell_count,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,0,cell_count,1,global_cell_list,p_type, mode, delta, width, height);
	/*
		FM_Algorithm_3(cell_list,cell_count/2,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,0,cell_count/2,1,global_cell_list,
			p_type, mode, delta, width, height);
		FM_Algorithm_3(cell_list,cell_count/2,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,cell_count/2 + 1,cell_count,2,global_cell_list, 
			p_type, mode, delta, width, height);
	*/
/*		
		 FM_Algorithm_3(cell_list,cell_count/4,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,0,cell_count/4,1,global_cell_list,
                        p_type, mode, delta, width, height);
                        FM_Algorithm_3(cell_list,cell_count/4,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,cell_count/4 + 1,cell_count/2,2,global_cell_list,
                        p_type, mode, delta, width, height);
                        FM_Algorithm_3(cell_list,cell_count/4,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,cell_count/2 + 1,(3*cell_count)/4,3,global_cell_list,
                        p_type, mode, delta, width, height);
                        FM_Algorithm_3(cell_list,cell_count/4,cell_net_list,detailed_net_list,net_count,initial_cutsize,threshold,adjacent_list,initial_cutsize,max_connect,(3*cell_count)/4 + 1,cell_count,4,global_cell_list,
                        p_type, mode, delta, width, height);
*/
//		cout<<"End of apply_FM_algorithm function : cell count: "<<cell_list.size()<<" p_type: "<<p_type<<endl;
		
		reset_global_cell_list(cell_list, global_cell_list);
		for(int i=0;i<cell_count;i++)
		{
			
			int cell_id;
			
			//if(cell_count < 1000)
			//cout<<"cell_id: "<<cell_id<<endl;
			if(cell_list[i].partition_id == p1)
			{
				//Partition 1-----------------------------
				//cell belongs to partition 1
				cell_id = cell_list[i].cell_id;	
				
				
				if(p_type == 0) //Horizontal
				{
				//	y_coord = cell_list[i].y_dim;
			//		assert(y_coord <= chip_height);
					//cell_list[i].y_dim =  (3*y_coord/2);
					cell_list[i].y_dim =  y_coord + height/4;
			//		assert(cell_list[i].y_dim <= chip_height);
					
					if(cell_id != 0)
					{
						assert(cell_id > 0);
						global_cell_list[cell_id - 1].y_dim = y_coord + height/4;
						global_cell_list[cell_id - 1].partition_id = 3;
					}
					
				}
				else if(p_type == 1) //vertical
				{
				//	x_coord = cell_list[i].x_dim;
			//		assert(x_coord <= chip_width);
					//cell_list[i].x_dim = x_coord/2;
					cell_list[i].x_dim = x_coord - width/4;
			//			assert(cell_list[i].x_dim <= chip_width);
					
					
					if(cell_id != 0)
					{
						assert(cell_id > 0);
						global_cell_list[cell_id - 1].x_dim = x_coord - width/4;
						global_cell_list[cell_id - 1].partition_id = 3;
					}
						
						
				}
				cell_ptr_p1.push_back(cell_list[i]);
				
			
			}
			else if (cell_list[i].partition_id == p2)
			{
				//Cell belongs to partition 2
				cell_id = cell_list[i].cell_id;
				if(p_type == 0) //horizontal cut
				{
					
				//	y_coord = cell_list[i].y_dim;
			//		assert(y_coord <= chip_height);
		//			if(cell_count < 1000)
		//				cout<<"i: "<<i<<endl;
				//	cell_list[i].y_dim =  (y_coord/2);
					cell_list[i].y_dim =  y_coord - height/4;
			//		assert(cell_list[i].y_dim <= chip_height);
					
					
					if(cell_id != 0)
					{
						assert(cell_id > 0);
						global_cell_list[cell_id - 1].y_dim = y_coord - height/4;
						global_cell_list[cell_id - 1].partition_id = 4;
					}
					
				}
				else if(p_type == 1) //vertical cut
				{
					
					
				//	x_coord = cell_list[i].x_dim;
					
		//			assert(x_coord <= chip_width);
				//	cell_list[i].x_dim = 3*x_coord/2;
					cell_list[i].x_dim = x_coord + width/4;
		//			assert(cell_list[i].x_dim <= chip_width);
		//			if(cell_count< 1000) cout<<"hello"<<" "<<x_coord<<endl;
					if(cell_id != 0)
					{
						assert(cell_id > 0);
						global_cell_list[cell_id - 1].x_dim = x_coord + width/4 ;
						global_cell_list[cell_id - 1].partition_id = 4;
					}
					
				}
				cell_ptr_p2.push_back(cell_list[i]);
			}
		}
	//	cout<<"\nsize of global cell list: "<<global_cell_list[0]->x_dim<<endl;
		
		//return cell_ptr;
}
