#include <filesystem>
#include<fstream>
#include<iostream>
#include<map>
using namespace std;
int main(){
string t;
    string path = "Europa Universalis IV/decisions";
    map<string,string> look;
    for (const auto & entry : filesystem::directory_iterator(path)){
    	int indent = 0;
    	ifstream ce(entry.path().string());
    	string cur = "";
    	//string tagas;
    	int wil = 0;
    	while(getline(ce,t)){
    		for(auto kas:t){
    			if(kas=='{')indent++;
    			else if(kas=='}')indent--;
			}
    		if(t.find("change_tag = ")!=-1){
    			look[t.substr(t.find("change_tag = ")+13,3)] = cur;
    			//cout<<t.substr(t.find("change_tag = ")+13,3)<<" "<<indent<<"\n";
			}
			if(t.find("allow = {")!=-1)wil = indent;
			if(indent<wil)wil = 0;
			if(wil)cur+= t+"\n";
		}
    	ce.close();
	}
	ofstream farm("formables.txt");
	for(auto kas:look){
		farm<<kas.first<<"&\n";
		farm<<kas.second<<"\n";
	}
}
