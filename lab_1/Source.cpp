#include<vector>
#include<iostream>

using namespace std;

int main() {
	vector<string> s;
	copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(s));
	
	for (auto str : s)
		cout << str << endl;
	return 0;
}
