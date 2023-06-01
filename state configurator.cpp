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
	map<int,vector<int>> aprovince;
	int tt,ttt,tttt;//prov/state/euprov
	while(idsa>>tt){
		idsa>>ttt;idsa>>tttt;
		astate[tttt] = {ttt,0,0,0,0,0};
		aprovince[tt] = {tttt,0,0,0,0};
	}
	string t;string ta;string full;
	idsa.close();
	//cout<<5;
	ifstream proveu("map/only province save.eu4");bool kitascores = false;int provic = 0;
	while(getline(proveu,t)){
		if(t[0]=='-'&&t[t.length()-1]=='{'&&t[t.length()-2]=='=')provic = stoi(t)*-1;
		else if (t.starts_with("\t\tbase_tax=")){astate[provic][1] = stoi(t.substr(11,2));}
		else if (t.starts_with("\t\tbase_production=")){astate[provic][2] = stoi(t.substr(18,2));}
		else if (t.starts_with("\t\tbase_manpower=")){astate[provic][3] = stoi(t.substr(16,2));}
	}
	ifstream defiba("map/definition.csv");getline(defiba,t);cout<<5;
	while(getline(defiba,t)){
		vector<string> tv = split(t,";");
		if(tv[5]=="true"&&aprovince.find(stoi(tv[0]))!=aprovince.end()){astate[aprovince[stoi(tv[0])][0]][4] = 1;astate[aprovince[stoi(tv[0])][0]][5] = stoi(tv[0]);}
	}
	cout<<5;
	//cout<<astate.size()<<"\n";
	ifstream idsam("wasteland ids.txt");
	while(getline(idsam,t)){
		astate.erase(stoi(t));
	}
	
	//cout<<astate.size()<<"\n";
	for(auto kas:astate){//cout<<kas.second[0]<<"\n";
		ifstream in("history/states/"+to_string(kas.second[0])+".txt");
		full = "";
		while(getline(in,ta)){
			double n = (kas.second[1]+kas.second[3]+kas.second[2]);
			double a = 3347 / pow(200, 0.01/21.5);
    double b = pow(100, 1.0/21.5);
    int result = a * pow(b, n);
    		if(result>10000)result *= 3;
    		if(result>100000)result /= 2;
    		//int result = a * exp(b * n);
    		//if(result>10000&&result<60000)result *= 2;
    		if(850000<result)result = 850000+result/100;
			//if(ta.find("manpower = ")!=-1)full+= "manpower = "+to_string(result)+"\n";
			if(ta.find("buildings = {")!=-1&&kas.second[4])full+= "buildings = {\n"+to_string(kas.second[5])+" = { naval_base = 1 }\n";
			else full+= ta+"\n";
		}in.close();
		ofstream out("history/states/"+to_string(kas.second[0])+".txt");
		out<<full;
		//out<<"\nimpassable = yes";
		out.close();
	}
	
	
	
	
	
	
	
}
