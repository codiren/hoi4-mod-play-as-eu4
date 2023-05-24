#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <set>
using namespace std;
int main()
{
    //ifstream aa("00_countries.txt");
    //string t;
    //string tasai;
    string sar[] = {"KOS","USB","NHX","EJZ","NVK","SOO","BTS","SKA","MIR","MCM","DMS"};
    for (string kas:sar){
    	ofstream se(kas+".txt");
    	se<<"graphical_culture = eastern_european_gfx\ngraphical_culture_2d = eastern_european_2d\ncolor = { 18  139  228 }";
	}
}
