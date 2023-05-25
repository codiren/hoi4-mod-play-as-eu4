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
	}
	std::string path = "gfx/flags/small";
    for (const auto & entry : filesystem::directory_iterator(path))
    	if(nae.find(entry.path().string().substr(path.length()+1,3))!=nae.end()){
    		rename(entry.path().string().c_str(),(path+"/"+nae[entry.path().string().substr(path.length()+1,3)]+".tga").c_str());
		}
    	//remove(entry.path().string().c_str());
        //std::cout <<<< std::endl;
}
