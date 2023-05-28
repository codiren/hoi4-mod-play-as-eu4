#include <string>
#include <iostream>
#include <filesystem>
#include <bits/stdc++.h>
using namespace std;
int main()
{
    string path = "technologies";
    string t;
    string full;
    for (const auto & entry : filesystem::directory_iterator(path)){
    	ifstream isr(entry.path().string());
    	full = "";
    	while(getline(isr,t)){
    		if(t.find("1918")!=-1)full+=t.substr(0,t.find("1918"))+"1426"+t.substr(t.find("1918")+4)+"\n";
    		else if(t.find("1933")!=-1)full+=t.substr(0,t.find("1933"))+"1441"+t.substr(t.find("1933")+4)+"\n";
    		else if(t.find("1936")!=-1)full+=t.substr(0,t.find("1936"))+"1444"+t.substr(t.find("1936")+4)+"\n";
    		else if(t.find("1937")!=-1)full+=t.substr(0,t.find("1937"))+"1445"+t.substr(t.find("1937")+4)+"\n";
    		else if(t.find("1938")!=-1)full+=t.substr(0,t.find("1938"))+"1446"+t.substr(t.find("1938")+4)+"\n";
    		else if(t.find("1939")!=-1)full+=t.substr(0,t.find("1939"))+"1447"+t.substr(t.find("1939")+4)+"\n";
    		else if(t.find("1940")!=-1)full+=t.substr(0,t.find("1940"))+"1448"+t.substr(t.find("1940")+4)+"\n";
    		else if(t.find("1941")!=-1)full+=t.substr(0,t.find("1941"))+"1449"+t.substr(t.find("1941")+4)+"\n";
    		else if(t.find("1942")!=-1)full+=t.substr(0,t.find("1942"))+"1450"+t.substr(t.find("1942")+4)+"\n";
    		else if(t.find("1943")!=-1)full+=t.substr(0,t.find("1943"))+"1451"+t.substr(t.find("1943")+4)+"\n";
    		else if(t.find("1944")!=-1)full+=t.substr(0,t.find("1944"))+"1452"+t.substr(t.find("1944")+4)+"\n";
    		else if(t.find("1945")!=-1)full+=t.substr(0,t.find("1945"))+"1453"+t.substr(t.find("1945")+4)+"\n";
    		else if(t.find("1946")!=-1)full+=t.substr(0,t.find("1946"))+"1454"+t.substr(t.find("1946")+4)+"\n";
    		else if(t.find("1947")!=-1)full+=t.substr(0,t.find("1947"))+"1456"+t.substr(t.find("1947")+4)+"\n";
    		else if(t.find("1948")!=-1)full+=t.substr(0,t.find("1948"))+"1457"+t.substr(t.find("1948")+4)+"\n";
    		else if(t.find("1949")!=-1)full+=t.substr(0,t.find("1949"))+"1458"+t.substr(t.find("1949")+4)+"\n";
    		else if(t.find("1950")!=-1)full+=t.substr(0,t.find("1950"))+"1459"+t.substr(t.find("1950")+4)+"\n";
    		else full+=t+"\n";
		}
        isr.close();
        ofstream isra(entry.path().string());
        isra<<full;
        isra.close();
    }
}
