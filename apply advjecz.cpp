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


ifstream idsa("byrealidv2.txt");//province; state; eu4 province
	map<int,vector<int>> astate;
	int tt,ttt,tttt;//prov/state/euprov
	while(idsa>>tt){
		idsa>>ttt;idsa>>tttt;
		astate[tttt] = {tt,0,0,0};
	}
	idsa.close();
/*
ifstream ine("map/terrain eu.txt");kitascores = false;string terainas;
map<>
	while(getline(ine,t)){
		if(kitascores){
			if(t.find("}")!=18446744073709551615){kitascores = false;terainas = "plains";continue;}
			if(t.find("#")!=18446744073709551615)t = split(t,"#")[0];
			tv = split(t," ");
			for(std::string kas:tv){
				if(prov[atoi(kas.c_str())].terrain=="lakes"||prov[atoi(kas.c_str())].terrain=="ocean")continue;
				prov[atoi(kas.c_str())].terrain = terainas;
			}
			continue;
		}
		if(t=="\tglacier = {"||t=="\tmountain = {")terainas = "mountain";
		else if(t=="\twoods = {"||t=="\tforest = {")terainas = "forest";
		else if(t=="\thills = {"||t=="\thighlands = {")terainas = "hills";
		else if(t=="\tjungle = {")terainas = "jungle";
		else if(t=="\tmarsh = {")terainas = "marsh";
		else if(t=="\tdesert = {"||t=="\tcoastal_desert = {"||t=="\tdrylands = {")terainas = "desert";
		else if(t=="\t\tterrain_override = {")kitascores = true;
	}
*/


ifstream a("map/adjacencies eu.csv");
	ofstream b("map/adjacencies.csv");
	string t;
	b<<"From;To;Type;Through;start_x;start_y;stop_x;stop_y;adjacency_rule_name;Comment\n";
	int kzk = 0;
	while(getline(a,t)){
		auto tv = split(t,";");
		if(tv[2]=="sea"){
			b<<astate[stoi(tv[0])][0]<<";"<<astate[stoi(tv[1])][0]<<";"<<"sea"<<";"<<"-1"<<";"<<"-1"<<";"<<"-1"<<";"<<"-1"<<";"<<"-1"<<";;"<<++kzk<<"\n";
		}
	}
	b<<"-1;-1;;-1;-1;-1;-1;-1;-1";
	a.close();
	b.close();


/*
	*/
}
