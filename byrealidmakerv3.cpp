#include <bits/stdc++.h>
using namespace std;
int main(){
	ifstream idsa("byrealidv2.txt");//province; state; eu4 province
	map<int,vector<int>> astate;
	int tt,ttt,tttt;//prov/state/euprov
	while(idsa>>tt){
		idsa>>ttt;idsa>>tttt;
		astate[tttt] = {ttt,0,0,0};
	}
	string t;string ta;string full;
	idsa.close();
	string t;
	
	ifstream proveu("map/only province save.eu4");bool kitascores = false;int provic = 0;
	while(getline(proveu,t)){
		if(t[0]=='-'&&t[t.length()-1]=='{'&&t[t.length()-2]=='=')provic = stoi(t)*-1;
		else if (t.starts_with("\t\tbase_tax=")){astate[provic][0] = stoi(t.substr(11,2));}
		else if (t.starts_with("\t\tbase_production=")){astate[provic][1] = stoi(t.substr(18,2));}
		else if (t.starts_with("\t\tbase_manpower=")){astate[provic][2] = stoi(t.substr(16,2));}
	}
	
	ifstream idsam("wasteland ids.txt");
	while(getline(idsam,t)){
		astate.erase(stoi(t));
	}
	

	for(auto kas:astate){
		ifstream in("history/states/"+to_string(kas.second[0])+".txt");
		full = "";
		while(getline(in,ta)){
			if(ta.find("manpower = ")!=-1)full+= "manpower = "<<kas.second[1]+kas.second[2]*2+kas.second[3]<<"\n";
			else full+= ta+"\n";
		}in.close();
		ofstream out("history/states/"+to_string(kas.second[0])+".txt");
		out<<full;
		//out<<"\nimpassable = yes";
		out.close();
	}
	
	
	
	
	
	
	
	while(getline(idsam,t)){
		ifstream in("history/states/"+to_string(astate[stoi(t)])+".txt");
		full = "";
		while(getline(in,ta)){
			if(ta.find("infrastructure = 1")!=-1)full+= "infrastructure = 0\n";
			else full+= ta+"\n";
		}in.close();
		ofstream out("history/states/"+to_string(astate[stoi(t)])+".txt");
		out<<full;
		//out<<"\nimpassable = yes";
		out.close();
	}
}
