#include <iostream>
#include <vector>
#include <algorithm>    // std::min_element, std::max_element

using namespace std;

bool compare(int i, int j)
{
	return (i<j && i!=0 && j!=0);
}

int main ()
{
	vector<int> v (4,0);
	v[0] = 17;
	v[1] = 2;
	v[2] = 4;
	v[3] = 1; 
	
	cout << min_element(v.begin(),v.end(), compare)-v.begin() << endl <<*min_element(v.begin(),v.end(),compare) << endl;
	v[min_element(v.begin(),v.end(), compare)-v.begin()] = 0;
	cout << min_element(v.begin(),v.end(), compare)-v.begin() << endl <<*min_element(v.begin(),v.end(),compare) << endl;


  return 0;
}