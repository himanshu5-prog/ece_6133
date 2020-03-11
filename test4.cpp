#include<iostream>
#include<algorithm>
#include<map>
using namespace std;

template<typename KeyType, typename ValueType> 
std::pair<KeyType,ValueType> get_max( const std::map<KeyType,ValueType>& x ) {
  using pairtype=std::pair<KeyType,ValueType>; 
  return *std::max_element(x.begin(), x.end(), [] (const pairtype & p1, const pairtype & p2) {
        return p1.second < p2.second;
  }); 
}

struct data
{
	int position;
	int velocity;
	int acceleration;
};
int main()
{
	vector<data> v_data;
	vector<data*> v_ptr;
	data *d = new data;
	for(int i=0;i<20;i++)
	{
		d->acceleration = i;
		d->position= 2*i;
		d->velocity = 4*i;
		//cout<<d->acceleration<<endl;
		v_data.push_back(*d);
	}	
	cout<<"size: "<<v_data.size();
	cout<<" acc: "<<v_data[3].acceleration<<endl;
	for(int i=0;i<20;i++)
	{
		v_ptr.push_back(&v_data[i]);
	//	cout<<v_ptr[i]->acceleration<<endl;
	}
	
	for(int i=0;i<20;i++)
	{
			cout<<v_ptr[i]->position<<endl;
	}
	cout<<"size: "<<v_ptr.size()<<endl;
	//v_ptr[3]->velocity = 987;
	v_data[3].velocity = 456;
	cout<<"new velocity: "<<v_ptr[3]->velocity<<endl;
	cout<<"size ptr: "<<v_ptr.size()<<endl;
	return 0;
}
