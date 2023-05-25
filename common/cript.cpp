#include<fstream>
#include<iostream>
#include <vector>
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
	ofstream ne("countries/colors.txt");
	string t;
	string tag;
	std::string path = "countries";
	ifstream c00("country_tags/00_countries.txt");
	ifstream c01("country_tags/01_countries.txt");
	while(getline(c00,t)){
		if(t.substr(0,3).find("#")!=-1)continue;
		if(t.find("/")==-1)continue;
		tag = t.substr(0,3);
		cout<<split(t,"\"").size()<<'\n';
		ifstream as(split(t,"\"")[1]);
		getline(as,t);
		getline(as,t);
		getline(as,t);
		as.close();
		ne<<tag<<" = { color = rgb "<<t.substr(8)<<"}\n";
	}
	while(getline(c01,t)){
		if(t.substr(0,3).find("#")!=-1)continue;
		if(t.find("/")==-1)continue;
		tag = t.substr(0,3);
		cout<<split(t,"\"").size()<<'\n';
		ifstream as(split(t,"\"")[1]);
		getline(as,t);
		getline(as,t);
		getline(as,t);
		as.close();
		ne<<tag<<" = { color = rgb "<<t.substr(8)<<"}\n";
	}
	ne.close();
}
