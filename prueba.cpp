#include <iostream>
#include <vector>
#include <algorithm>    // std::min_element, std::max_element

using namespace std;

int main ()
{
	vector<int> v (4,0);
	v[0] = 1;
	v[2] = 3;
	v[3] = 8; 
	
	cout << min_element(v.begin(),v.end())-v.begin() << endl;

  return 0;
}