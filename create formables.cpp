#include <bits/stdc++.h>
using namespace std;
int main(){
	ofstream ze("common/decisions/formable_nation_decisions.txt");
	ze<<"formables = {";
	ifstream zen("formables.txt");
	ifstream idsa("byrealidv2.txt");//province; state; eu4 province
	map<int,int> astate;
	int tt,ttt,tttt;//prov/state/euprov
	while(idsa>>tt){
		idsa>>ttt;idsa>>tttt;
		astate[tttt] = ttt;
	}
	string t;
	string tag;
	bool can = false;
	vector<int> corpse;
	while(getline(zen,t)){
		if(t.find("&")!=-1){
		if(can&&corpse.size()>0){
			ze<<"\nform_"<<tag<<" = {";
			ze<<"\nicon = generic_form_nation";
			//ze<<"\nallowed = { always = yes }"
			ze<<"\nvisible = { OR = {";
			for(auto ka:corpse){
				ze<<"\ncontrols_state = "<<astate[ka];
			}
			ze<<"\n}}";
			ze<<"\navailable = {";
			ze<<"\nis_subject = no";
			for(auto ka:corpse){
				ze<<"\ncontrols_state = "<<astate[ka];
			}
			ze<<"\n}";
			ze<<"\ncomplete_effect = {";
			ze<<"\nset_cosmetic_tag = "<<tag;
			ze<<"\nadd_stability = 0.1";
			ze<<"\nadd_political_power = 100";
			for(auto ka:corpse){
				ze<<"\n"<<astate[ka]<<" = { add_core_of = ROOT }";
			}
			ze<<"\n}";
			ze<<"\n}";
		}
		corpse.clear();
		tag = t.substr(0,3);can = true;
		}
		if(t.find("num_of_cities")!=-1)can = false;
		if(t.find("num_of_owned_provinces_with")!=-1)can = false;
		if(t.find("_area")!=-1)can = false;
		if(t.find("owns_core_province")!=-1&&can)corpse.push_back(stoi(t.substr(t.find("=")+1)));
	}
	
	
	
	
	
	
	
	
	
	
	
	
	ze<<"\n}";
	ze.close();
}
