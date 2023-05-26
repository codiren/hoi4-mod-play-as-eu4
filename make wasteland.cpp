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
