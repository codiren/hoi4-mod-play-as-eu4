#include <bits/stdc++.h>
using namespace std;
int main(){
	ifstream inp("blank cnt.eu4");string t;string tag;string ttag;int provn;int provn2;int provn3;
	ifstream ips("byrealidv2.txt");//province; state; eu4 province
	map<int,int> byfakeid;
	while(ips>>provn){
		ips>>provn2;ips>>provn3;
		byfakeid[provn3] = provn2;
	}
	set<string> relgc;
	while(getline(inp,t)){
		if(t[0]=='-'&&t.find("={")!=-1)provn = stoi(t)*-1;
		if(t.find("\treligion=")!=-1)relgc.insert(t.substr(t.find("\treligion=")+10));
	}

ips.close();inp.close();
	ifstream eur("00_religion.txt");
	map<string,string> bycolor;
	while(getline(eur,t)){
		//if(t.find(" = {")!=-1)cout<<t.substr(1,t.find("=")-2)<<"\n";//tag = t.substr(1,t.find("="));
		if(t.find("color = ")!=-1)bycolor[tag] = t.substr(t.find("=")+2);
		//if(t.find("color = ")!=-1)cout<<tag<<" "<<t.substr(t.find("=")+2)<<"\n";
		else if(t.find(" = {")!=-1)tag = t.substr(1,t.find("=")-2);
	}





	ofstream ifs("common/ideologies/01_ideologies.txt");
	ifs<<"ideologies = {";
	for(auto kas :relgc){
		ifs<<"\n"<<kas<<" = {";
		ifs<<"\ntypes = {";
		ifs<<"\n"<<kas<<" = {";
		ifs<<"\n}";ifs<<"\n}";
		ifs<<"\ndynamic_faction_names = {\n\"FACTION_NAME_FASCIST_1\"\n\"FACTION_NAME_FASCIST_2\"\n\"FACTION_NAME_FASCIST_3\"\n\"FACTION_NAME_FASCIST_4\"\n\"FACTION_NAME_FASCIST_5\"\n}";
		ifs<<"\ncolor = "<<bycolor[kas];
		//ifs<<"\nwar_impact_on_world_tension = 1.0";
		//ifs<<"\nfaction_impact_on_world_tension = 1.0";
		ifs<<"\nai_fascist = yes";
		ifs<<"\n}";
	}ifs<<"\n}";
	ifs.close();



	//return 0;
	ifstream in("blank cnt.eu4");
	
	
	map<string,string> mep;
	while(getline(in,t)){
		if(t.find("={")!=-1){ttag = t.substr(1,3);
			getline(in,t);
			if(t.find("government_rank=")!=-1){
				tag = ttag;
			}
		}
		if(t.find("\treligion=")!=-1){
			mep[tag] = t.substr(t.find("religion=")+9);
		}
	}
	//set<string> sep;
	string full;string ta;
	for(auto kas:mep){
		//cout<<kas.first<<" "<<kas.second<<"\n";
		//sep.insert(kas.second);
		ifstream in("history/countries/"+kas.first+".txt");
		full = "";
		while(getline(in,ta)){
			if(ta.find("ruling_party = neutrality")!=-1)full+= "ruling_party = "+kas.second+"\n";
			else full+= ta+"\n";
		}in.close();
		ofstream out("history/countries/"+kas.first+".txt");
		out<<full;
		//out<<"\nimpassable = yes";
		out.close();
	}
	/*
	cout<<mep.size()<<"\n";
	for(auto kas:sep){
		cout<<kas<<"\n";
		
	}*/
	
	
	
}
