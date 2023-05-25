#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
int main()
{
std::string t;
    std::string path = "countries";
    for (const auto & entry : std::filesystem::directory_iterator(path))
        {std::ifstream ce(entry.path().string());
        std::string ka = "oob = \"AAA_basic\"";
        bool first = true;
        while(std::getline(ce,t)){
        if(first == false)
        	ka += "\n"+t;
        	else
        	first = false;
		}
		ce.close();
		std::ofstream ice(entry.path().string());
		ice<<ka;
		}
}
