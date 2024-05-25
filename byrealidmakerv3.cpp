#include <bits/stdc++.h>
using namespace std;
int main(){
	ifstream idsa("byrealidv2.txt");//province; state; eu4 province
	map<int,vector<string>> astate;
	int tt,ttt,tttt;//prov/state/euprov
	while(idsa>>tt){
		idsa>>ttt;idsa>>tttt;
		//cout<<(tttt==1250)<<"\n";
		astate[tttt] = {to_string(ttt),string(),string(),string()};
	}
	string t;string ta;string full;
	idsa.close();
	//string t;
	
	ifstream proveu("map/only province save.eu4");bool kitascores = false;int provic = 0;
	while(getline(proveu,t)){
		if(t[0]=='-'&&t[t.length()-1]=='{'&&t[t.length()-2]=='=')provic = stoi(t)*-1;
		else if (t.starts_with("\t\ttrade_goods=")){
		if((astate.find(provic)==astate.end()))continue;
			//astate[provic].insert(stoi());
			//cout<<6;
			//cout<<<<"\n";
			//cout<<astate[provic][0]<<"\n";
			astate[provic][1] = t.substr(14);
			//cout<<6;
		}
		else if (t.starts_with("\t\tbase_production=")){astate[provic][2] = t.substr(18,2);}
		//else if (t.starts_with("\t\tbase_manpower=")){astate[provic][2] = stoi(t.substr(16,2));}
	}
	
	ifstream idsam("wasteland ids.txt");
	while(getline(idsam,t)){
		astate.erase(stoi(t));
	}
	
	
	for(auto kas:astate){
		ifstream in("history/states/"+kas.second[0]+".txt");
		full = "";
		while(getline(in,ta)){
			if(ta.find("history={")!=-1){
			full+= "resources={\n";
			if(kas.second[1].find("iron")!=-1)full+="steel = "+to_string(8*stoi(kas.second[2]))+"\n";
			if(kas.second[1].find("copper")!=-1)full+="aluminium = "+to_string(6*stoi(kas.second[2]))+"\n";
			if(kas.second[1].find("fur")!=-1)full+="rubber = "+to_string(16*stoi(kas.second[2]))+"\n";
			if(kas.second[1].find("cloth")!=-1)full+="rubber = "+to_string(2*stoi(kas.second[2]))+"\n";
			if(kas.second[1].find("wool")!=-1)full+="rubber = "+to_string(1*stoi(kas.second[2]))+"\n";
			if(kas.second[1].find("silk")!=-1)full+="rubber = "+to_string(3*stoi(kas.second[2]))+"\n";
			if(kas.second[1].find("salt")!=-1)full+="oil = "+to_string(8*stoi(kas.second[2]))+"\n";
			if(kas.second[1].find("gems")!=-1)full+="tungsten = "+to_string(4*stoi(kas.second[2]))+"\n";
			if(kas.second[1].find("slaves")!=-1)full+="chromium = "+to_string(16*stoi(kas.second[2]))+"\n";
			full+= "}\n";
			full+= "history={\n";
			}
			else full+= ta+"\n";
		}in.close();
		ofstream out("history/states/"+kas.second[0]+".txt");
		out<<full;
		//out<<"\nimpassable = yes";
		out.close();
	}
	
	
	
	
	
	/*
	
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
	}*/
}
