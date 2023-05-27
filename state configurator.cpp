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
	
	ifstream proveu("map/only province save.eu4");bool kitascores = false;int provic = 0;
	while(getline(proveu,t)){
		if(t[0]=='-'&&t[t.length()-1]=='{'&&t[t.length()-2]=='=')provic = stoi(t)*-1;
		else if (t.starts_with("\t\tbase_tax=")){astate[provic][1] = stoi(t.substr(11,2));}
		else if (t.starts_with("\t\tbase_production=")){astate[provic][2] = stoi(t.substr(18,2));}
		else if (t.starts_with("\t\tbase_manpower=")){astate[provic][3] = stoi(t.substr(16,2));}
	}
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
			if(ta.find("manpower = ")!=-1)full+= "manpower = "+to_string(result)+"\n";
			else full+= ta+"\n";
		}in.close();
		ofstream out("history/states/"+to_string(kas.second[0])+".txt");
		out<<full;
		//out<<"\nimpassable = yes";
		out.close();
	}
	
	
	
	
	
	
	
}
