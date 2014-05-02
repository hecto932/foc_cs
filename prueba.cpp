#include <iostream>
#include <vector>
#include <algorithm>    // std::min_element, std::max_element

using namespace std;

bool compare(int i, int j)
{
	if(i==j && i ==0 && j==0)
		return 0;
	else if(i<j)
		return i;
}

int main ()
{
	vector<int> v (4,0);
	v[0] = 3;
	v[1] = 4;
	v[2] = 2;
	v[3] = 0; 
	
	cout << *min_element(v.begin(),v.end(),compare) << endl;

  return 0;
}