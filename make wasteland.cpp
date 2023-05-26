#include <bits/stdc++.h>
using namespace std;
int main(){
	ifstream idsa("byrealidv2.txt");//province; state; eu4 province
	map<int,int> astate;
	int tt,ttt,tttt;//prov/state/euprov
	while(idsa>>tt){
		idsa>>ttt;idsa>>tttt;
		astate[tttt] = ttt;
	}
	string t;string ta;string full;
	idsa.close();
	ifstream idsam("wasteland ids.txt");
	while(getline(idsam,t)){
		ifstream in("history/states/"+to_string(astate[stoi(t)])+".txt");
		while(getline(out,ta)){
			if(ta.find("owner =")!=-1)full+= "owner = REB\n";
			else full+= ta+"\n";
		}
		ofstream out("history/states/"+to_string(astate[stoi(t)])+".txt");
		out<<"\nimpassable = yes";
		out.close();
	}
}
