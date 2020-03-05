#include<iostream>
using namespace std;

template<typename KeyType, typename ValueType> 
std::pair<KeyType,ValueType> get_max( const std::map<KeyType,ValueType>& x ) {
  using pairtype=std::pair<KeyType,ValueType>; 
  return *std::max_element(x.begin(), x.end(), [] (const pairtype & p1, const pairtype & p2) {
        return p1.second < p2.second;
  }); 
}

int get_partition_count(vector<Cell> cell_list, int partition_id)
{
	int num=0;
	
	for(int i=0;i< cell_list.size();i++)
	{
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
	return net_num_only;
}

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
	return net_num_all;
}
bool is_area_constraint_violated(int cell_id, int dest_partition_id, int p1_id, int p2_id, vector<Cell> cell_list, int threshold, int cell_count)
{
	int p;
	int p1_count=0;
	int p2_count=0;
	
	int index = cell_id - 1;
	
	int p_id_cell_id = cell_list[index].partition_id;
	for(int i=0;i<cell_count;i++)
	{
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
void FM_Algorithm(vector<Cell> &cell_list, int cell_count, vector<int> cell_net_list[], vector<Cell> detailed_net_list[], int net_count , int initial_cutsize,
int threshold,vector<Cell> adjacent_list[], vector<Cell> reduced_adjacent_list[], int initial_cut_size)
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
//	do
//	{
	unlock_all_cells(cell_list);
	int count=-1;
	while(get_unlocked_cell_id(cell_list) != -1)
	{
		count++;
		
		if(count ==th1)
			break;
		if(gain == 0)
			break;
	//	cout<<"unlocked cell count: "<<count_unlocked_cell(cell_list)<<endl;
	 bucket_list.clear();
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
			//cout<<"cell_id: "<<cell_id<<"area constraint: "<<area_constraint<<"count unlocked cell: "<<count_unlocked_cell(cell_list)<<endl;
			
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
			bucket_list.insert({cell_id,gain});
		
			//cout<<"cell: "<<cell_id<<" gain: "<<gain<<endl;
	 }
	 	if(!bucket_list.empty())
	 	{
			auto max = get_max(bucket_list);
			gain_max = max.second;
			
	
			int dest_p_id1;
			if(cell_list[max.first - 1].partition_id == p1)
				dest_p_id1 = p2;
			else if(cell_list[max.first - 1].partition_id == p2)
				dest_p_id1 = p1;
		
			//cout<<"Moving cell "<<max.first<<" from "<<cell_list[max.first - 1].partition_id<<" to "<<dest_p_id1<<" gain: "<<gain<<endl;
			set_cell_partition_id(max.first,dest_p_id1,cell_list,adjacent_list,reduced_adjacent_list,cell_count);
			lock_cell(max.first,cell_list);
		}	
		else
			cout<<"bucket is empty"<<endl;
		
		
		
		
		
    }
    update_detailed_netlist(cell_list,detailed_net_list,net_count);
	int new_cut_size = calculate_cutsize(detailed_net_list,net_count);
	cout<<"new cutsize: "<<new_cut_size<<endl;
	diff_cutsize = initial_cut_size - new_cut_size;
	initial_cut_size = new_cut_size;
	
	cout<<"Partition1 count: "<<get_partition_count(cell_list,p1)<<" partition2_count: "<<get_partition_count(cell_list,p2)<<endl;
	//}while(diff_cutsize > 0);
}
