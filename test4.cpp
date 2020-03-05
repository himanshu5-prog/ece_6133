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

int main()
{
	std::map<int,int> x = { { 1,1 },{ 2,21 },{3,0}}; 
auto max=get_max(x);
std::cout << max.first << "=>" << max.second << std::endl;
}
