#include<iostream>
#include<fstream>
#include <filesystem>
int main(){
	std::string t;
	std::string path = "countries";
	std::string kas;
    for (const auto & entry : std::filesystem::directory_iterator(path)){
		std::ifstream ce(entry.path().string());
		bool did = true;
		kas = "";
		while(std::getline(ce,t)){
			kas += t+"\n";
			if(did){kas+="oob = \"LIT\"\n";
			did = false;}
		}
		ce.close();
		std::ofstream ne(entry.path().string());
		ne<<kas;
		ne.close();
	}
}
