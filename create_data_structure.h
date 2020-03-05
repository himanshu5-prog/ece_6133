#include<iostream>
using namespace std;

void create_detailed_netlist(vector<Cell> detailed_net_list[], vector<int> net_list[], int net_count)
{
	Cell *temp;
	temp = new Cell;
	temp->weight=0;
	double w;
	for(int i=0;i<net_count;i++)
	{
		for(int j=0;j<net_list[i].size();j++)
		{
			temp->cell_id=net_list[i][j];
			temp->locked=false;
			temp->partition_id = 0 ;
			//cout<<"size: "<<net_list[i].size()<<endl;
			//w= 1/ ((double (net_list[i].size() ))-1 );
			//	cout<<"w: "<<w<<endl;
			temp->weight = 0;
			temp->x_dim=0;
			temp->y_dim=0;
			detailed_net_list[i].push_back(*temp);
		//	cout<<detailed_net_list[i].size()<<endl;
		}
	}
}


void post_processing_weight (vector< pair<int,int> > pair_list, map< pair<int,int>, double> &weight)
{
	vector< pair<int,int> >::iterator itr;
	itr = pair_list.begin();
	
	while(itr!= pair_list.end())
	{	
		weight[{itr->first, itr->second}] /=2;
		itr++;
	}
}
bool is_cell_present(vector<Cell> net_list, int net_list_size, int node)
{
	for(int i=0; i<net_list_size;i++)
	{
		if(node== net_list[i].cell_id)
			return true;
	}
	return false;
}

void 
create_adj_weight(vector<Cell> adjacent_list[], int adj_size, vector<Cell> detailed_net_list[], int detailed_netlist_size, map< pair<int,int>, double > &weight,
int cell_count, vector< pair<int,int> > &pair_list)
{
	int cell_id,size;
	Cell cell_net_list;
	bool present=false;
	double weight1=0;
	int p,q;
	for(int i=0;i<cell_count;i++)
	{
		for(int j=0;j<detailed_netlist_size;j++)
		{
			
			cell_id = i+1;
			size = detailed_net_list[j].size();
			
			present= is_cell_present(detailed_net_list[j],size,cell_id);
			
			if(!present)
				continue;
			
			else if(present)
			{
				
				weight1 = 1/ (double (size -1));
				
				for(int k=0;k<detailed_net_list[j].size();k++)
				{
					cell_net_list = detailed_net_list[j][k];	
					if(cell_id == cell_net_list.cell_id)
						continue;
					
					else
					{
						//cout<<"for "<<cell_id<<" and "<<cell_net_list.cell_id<<" weight: "<<weight1<<endl;
						bool present_2 = is_cell_present(adjacent_list[i],adjacent_list[i].size(),cell_net_list.cell_id);
						
						if(!present_2)
						{
							adjacent_list[i].push_back(cell_net_list);
						}
						
						
						if(cell_id < cell_net_list.cell_id)
						{
							p = cell_id;
							q = cell_net_list.cell_id;	
						}
						else 
						{
							p = cell_net_list.cell_id;
							q = cell_id;
						}
						assert(p < q);
						pair<int,int> p1 (p,q);
						
						map< pair<int,int>, double > :: iterator itr;
						itr = weight.find(p1);
						
						if(itr != weight.end())
						{
							//Found
							weight[{p,q}]+=weight1;
							//cout<<"weight vector: ("<<p<<", "<<q<<") "<<weight[{p,q}]<<endl;
						//	cout<<"Found"<<endl;
						}
						else
						{
							//not found
							weight[{p,q}] = weight1;
							pair_list.push_back(p1);
							
							
						//	cout<<"Not found"<<endl;
						}
						//weight1=0;
									
					}
				}
			}		
		}
	}
	post_processing_weight(pair_list,weight);
//	cout<<"size: "<<pair_list.size()<<endl;
	//cout<<weight[{2,4}];
}

void create_reduced_adj(vector<Cell> adjacent_list[], vector<Cell> reduced_adjacent_list[], int cell_count)
{
	
	for(int i=0;i<cell_count;i++)
	{
		for(int j=0; j< adjacent_list[i].size();j++)
		{
			if(i+1 < adjacent_list[i][j].cell_id)
			{
				reduced_adjacent_list[i].push_back(adjacent_list[i][j]);
			}
		}
	}
}

void create_cell_list(vector<Cell> &cell_list, int cell_count, vector<Cell> detailed_net_list[], int detailed_netlist_size)
{
	int cell_id=0;
	bool present=false;
	bool loop_exit=false;
	for(int i=0;i<cell_count;i++)
	{
		cell_id = i+1;
		loop_exit=false;
		for(int j=0; j<detailed_netlist_size;j++)
		{
			present = is_cell_present(detailed_net_list[j], detailed_net_list[j].size(),cell_id);
			if(!present )
				continue;
			
			else if(present)
			{
				for(int k=0;k<detailed_net_list[j].size();k++)
				{
					if(cell_id == detailed_net_list[j][k].cell_id)
					{
						cell_list.push_back(detailed_net_list[j][k]);
						loop_exit=true;
						break;
					}
				}
			}
			if(loop_exit==true)
				break;
		}
	}
}

vector<Cell> report_neighbors(int cell_id, vector<Cell> reduced_adjacent_list[], int cell_count)
{
	vector <Cell> neighbor;
	int index = cell_id - 1;
	int n_cell_id = 0;
	for(int i=0; i< reduced_adjacent_list[index].size();i++)
	{
		neighbor.push_back(reduced_adjacent_list[index][i]);
	}
	return neighbor;
}

void update_detailed_netlist(vector<Cell> cell_list, vector<Cell> detailed_net_list[], int net_count)
{
	//bool present=false;
	int cell_id,index;
	for(int i=0;i<net_count;i++)
	{
		for(int j=0;j<detailed_net_list[i].size();j++)
		{
				cell_id = detailed_net_list[i][j].cell_id;
				index = cell_id - 1;
				detailed_net_list[i][j].partition_id = cell_list[index].partition_id;
		}
	}
}

void create_cell_net_list(vector<Cell> detailed_net_list[], int net_count, vector<int> cell_net_list[], int cell_count)
{
	int cell_id;
	bool present;
	for(int i=0;i<cell_count;i++)
	{
		cell_id = i + 1;
		present=false;
		for(int j=0;j<net_count;j++)
		{
			present = is_cell_present(detailed_net_list[j], detailed_net_list[j].size(),cell_id);
			
			if(present)
			{
				cell_net_list[i].push_back(j);
			}
		}
	}
}
