#include <bits/stdc++.h>
using namespace std;
int main(){
	ifstream inp("map/only province save.eu4");string t;string tag;string ttag;int provn;int provn2;int provn3;
	ifstream ips("byrealidv2.txt");//province; state; eu4 province
	map<int,int> byfakeid;
	while(ips>>provn){
		ips>>provn2;ips>>provn3;
		byfakeid[provn3] = provn2;
	}
	set<string> relgc;
	map<int,int> pdev;
	map<int,string> pdevr;
	provn = 0;
	while(getline(inp,t)){
		if(t[0]=='-'&&t.find("={")!=-1)provn = stoi(t)*-1;
		else if(t.find("\treligion=")!=-1)relgc.insert(t.substr(t.find("\treligion=")+10));
		if(pdev.find(byfakeid[provn])==pdev.end())pdev[byfakeid[provn]] = 0; 
		else if((t.starts_with("\t\tbase_tax=")))pdev[byfakeid[provn]] += stoi(t.substr(11,2));
		else if((t.starts_with("\t\tbase_production=")))pdev[byfakeid[provn]] += stoi(t.substr(18,2));
		else if((t.starts_with("\t\tbase_manpower=")))pdev[byfakeid[provn]] += stoi(t.substr(16,2));
		else if((t.starts_with("\t\tbase_manpower=")))pdev[byfakeid[provn]] += stoi(t.substr(16,2));
		else if((t.starts_with("\t\treligion=")))pdevr[byfakeid[provn]] = t.substr(11);
	}
	map<string,int> relntoid;
	map<int,string> relntoidatvirsktinisskaiciavimasapsuntimapa;
	int sigma_based = 0;
	for(auto kas:relgc){sigma_based++;
		relntoid[kas] = sigma_based;
		relntoidatvirsktinisskaiciavimasapsuntimapa[sigma_based] = kas;
	}

ips.close();inp.close();
	ifstream eur("00_religion.txt");
	map<string,string> bycolor;
	while(getline(eur,t)){
		//if(t.find(" = {")!=-1)cout<<t.substr(1,t.find("=")-2)<<"\n";//tag = t.substr(1,t.find("="));
		if(t.find("color = ")!=-1)bycolor[tag] = t.substr(t.find("=")+2);
		//if(t.find("color = ")!=-1)cout<<tag<<" "<<t.substr(t.find("=")+2)<<"\n";
		else if(t.find(" = {")!=-1&&t[0] == '\t'&&t[1] != '\t')tag = t.substr(1,t.find("=")-2);
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
	map<string,int*> bycntpop;
	ofstream neviegievhuwifhihibef("common/on_actions/08_bba_on_actions.txt");
	neviegievhuwifhihibef<<"on_actions = {\non_startup = {\neffect = {\n";
	for(auto kas:pdev){
		ifstream inz("history/states/"+to_string(kas.first)+".txt");
		full = "";
		while(getline(inz,ta)){
			if(ta.find("owner = ")!=-1){
				if(bycntpop.find(ta.substr(8))==bycntpop.end())bycntpop[ta.substr(8)] = reinterpret_cast<int*>(calloc(relgc.size()+1,4));//new int[relgc.size()+1];
				bycntpop[ta.substr(8)][relntoid[pdevr[kas.first]]] += kas.second;
				bycntpop[ta.substr(8)][0] += kas.second;
			}
			if(ta.find("local_supplies=0.0")!=-1){
				//full+= "set_state_flag = {\nflag = state_religion\nvalue = "+to_string(relntoid[pdevr[kas.first]])+"\n}\n";
				//full+= "set_state_flag = {\nflag = state_development\nvalue = "+to_string(kas.second)+"\n}\n";
				neviegievhuwifhihibef<<kas.first<<" = {\n";
				neviegievhuwifhihibef<<("set_state_flag = {\nflag = state_religion\nvalue = "+to_string(relntoid[pdevr[kas.first]])+"\n}\n");
				neviegievhuwifhihibef<<( "set_state_flag = {\nflag = state_development\nvalue = "+to_string(kas.second)+"\n}\n");
				neviegievhuwifhihibef<<"}";
			}
			else full+= ta+"\n";
		}in.close();
		ofstream out("history/states/"+to_string(kas.first)+".txt");
		out<<full;
		//out<<"\nimpassable = yes";
		out.close();
	}
	neviegievhuwifhihibef<<"\n}\n}\n}";
	neviegievhuwifhihibef.close();
	//to procentai
	for(auto kas:bycntpop){
		ifstream ineaeafrthrjrukotr("history/countries/"+kas.first+".txt");
		full = "";
		while(getline(ineaeafrthrjrukotr,ta)){
			if(ta.find("set_popularities = {democratic = 0")!=-1){
				full+= "set_popularities = {\n";
				int trk = 0;
				int trkindex = 1;
				for(int i = 1;i<relgc.size()+1;i++){
					kas.second[i] = int((((kas.second[i]*1.0)/(kas.second[0]*1.0))*100.0));
					//cout<<kas.second[i]<<" "<<kas.second[0]<<"\n";
					trk += kas.second[i];
					if(kas.second[i]>0)trkindex = i;
				}
				kas.second[trkindex] += 100-trk;
				for(int i = 1;i<relgc.size()+1;i++){
					if(kas.second[i]>0){
						full+=relntoidatvirsktinisskaiciavimasapsuntimapa[i]+" = "+to_string(kas.second[i])+"\n";
					}
				}
				
				
			}
			else if(ta.find("fascism = 0")!=-1);
			else if(ta.find("communism = 0")!=-1);
			else if(ta.find("neutrality = 100")!=-1);
			else full+= ta+"\n";
		}ineaeafrthrjrukotr.close();
		ofstream wiufheiuwhfwiufwdw("history/countries/"+kas.first+".txt");
		wiufheiuwhfwiufwdw<<full;
		//out<<"\nimpassable = yes";
		wiufheiuwhfwiufwdw.close();
	}
	
	
	
}
