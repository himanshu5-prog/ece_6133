// C++ implementation to read 
// file word by word 
#include <bits/stdc++.h> 
using namespace std; 
  
// driver code 
int main() 
{ 
    // filestream variable file 
    fstream file; 
    string word, t, q, filename; 
    vector<string> v;
    // filename of the file 
    filename = "structP.txt"; 
  
    // opening file 
    file.open(filename.c_str()); 
    
    // extracting words from the file 
    while (file >> word) 
    { 
    	v.push_back(word);
        // displaying content 
        //cout << word << endl; 
    } 
    
    cout<<v.size();
  
    return 0; 
} 
