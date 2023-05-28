#include <string>
#include <iostream>
#include <filesystem>
#include <bits/stdc++.h>
using namespace std;
int main()
{
    string path = "/technologies";
    string t;
    string full;
    for (const auto & entry : filesystem::directory_iterator(path)){
    	ifstream isr(entry.path().string());
    	full = "";
    	while(getline(isr,t)){
    		if(t.find("1918")!=-1)full+=t.substr(0,t.find("1918")-1)+"1426"+t.substr(t.find("1918")+4)+"\n";
    		else full+=t+"\n";
		}
        isr.close();
    }
}
