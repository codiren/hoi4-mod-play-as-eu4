#include <bits/stdc++.h>
using namespace std;
int main(){
	ifstream in("common/country_tags/00_countries.txt");
	set<string> exist;
	string t;
	while(getline(in,t)){
		exist.insert(t.substr(0,3));
	}
	ifstream ine("common/countries/colors.txt");
	string full;
	while(getline(ine,t)){
		if(exist.find(t.substr(0,3))!=exist.end()){
			full += t+"\n";
		}
	}
	ine.close();
	ofstream of("common/countries/colors.txt");
	of<<full;
	of.close();
}
