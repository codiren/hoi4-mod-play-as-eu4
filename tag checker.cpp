#include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<filesystem>
using namespace std;
int main(){
	map<string,string> nae;
	string t;string tt;string ttt;
	ifstream ae("realreal.txt");
	while(getline(ae,t)){
		nae[t.substr(0,3)] = t.substr(4,3);
	}/*
	std::string path = "history/countries";
    for (const auto & entry : filesystem::directory_iterator(path))
    	if(nae.find(entry.path().string().substr(path.length()+1,3))==nae.end())
    	remove(entry.path().string().c_str());
        //std::cout <<<< std::endl;*/
    ifstream ne("common/countries/colors.txt");
    string outas;
    while(getline(ne,t)){
    	getline(ne,tt);
    	getline(ne,ttt);
    	if(nae.find(t.substr(0,3))!=nae.end())
    	{outas+=nae[t.substr(0,3)]+" = {";outas+="\n";outas+=tt;outas+="\n";outas+=ttt;outas+="\n";}
    	else {outas+=t;outas+="\n";outas+=tt;outas+="\n";outas+=ttt;outas+="\n";}
	}
	ne.close();
	ofstream nee("common/countries/colors.txt");
	nee<<outas;
	nee.close();
}
