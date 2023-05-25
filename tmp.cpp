#include<iostream>
#include <filesystem>
#include<fstream>
using namespace std;
int main(){
	string what = R""""(
	set_politics = {
	ruling_party = neutrality
	last_election = "1936.1.1"
	election_frequency = 48
	elections_allowed = no
}
set_popularities = {
	democratic = 0
	fascism = 20
	communism = 5
	neutrality = 75
}
	)"""";
	std::string path = "/history/countries/";
    for (const auto & entry : std::filesystem::directory_iterator(path)){
        ifstream inas(entry.path().string());
        
        inas.close();
        ofstream inaz(entry.path().string());
        
        inaz.close();
	}
}
