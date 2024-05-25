#include <bits/stdc++.h>
using namespace std;
vector<string> split(string &str,string delim){
	vector<string> rez;
	int wher = 0;
	int prev = 0;
	while(wher != -1){
		wher = str.find(delim,wher+1);
		rez.push_back(str.substr(prev,wher-prev));
		prev = wher+1;
	}
	return rez;
}
int main(){
	
}



/* eh later
set_autonomy = {
		target = MEN
		autonomous_state = autonomy_integrated_puppet
	}
	
	
	
	
	
	
	
	
	
	
	*/
