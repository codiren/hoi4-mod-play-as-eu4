#include<iostream>
#include<fstream>
#include<filesystem>
#include<windows.h>
#include<vector>
#include <cstdlib>
#include <sstream>
int printNum = 1;
int start = GetTickCount();
void print(){std::cout<<printNum++<<"|test"<<"\n";}
void print(std::string input){std::cout<<printNum++<<"|"<<input<<"\n";}
void print(int input){std::cout<<printNum++<<"|"<<input<<"\n";}

std::vector<std::string> split(std::string &str,std::string delim){
	std::vector<std::string> rez;
	int wher = 0;
	int prev = 0;
	while(wher != -1){
		wher = str.find(delim,wher+1);
		rez.push_back(str.substr(prev,wher-prev));
		prev = wher+1;
	}
	return rez;
}
std::string between(std::string line,std::string str){
	int start = line.find(str);
	int end = line.find(str, start + 1);
	return line.substr(start + 1, end - start - 1);
};
std::string between(std::string line,std::string str,std::string str2){
	int start = line.find(str);
	int end = line.find(str2, start + 1);
	return line.substr(start + 1, end - start - 1);
};
std::string join(std::vector<std::string> &str){
    std::string rez;
	for( auto i: str){
	    rez+=i;
	}
	return rez;
}
std::ofstream copy_file(std::string a,std::string b){
    std::ifstream  src(a, std::ios::binary);
    std::ofstream  dst(b, std::ios::binary);
    dst << src.rdbuf();src.close();dst.close();
	dst.close();src.close();
    return std::ofstream(b, std::ios_base::app);
}
std::ofstream newFile(std::string path){
    std::filesystem::create_directories(path.substr(0, path.find_last_of('/')));
    return std::ofstream(path);
};
bool isUpper(char character){
    return (character>='A'&&character<='Z');
};
//----INTERFACES----INTERFACES----INTERFACES----INTERFACES----INTERFACES----INTERFACES
struct eventInterface{
    std::string id;
    std::string title = "Breaking news";
    std::string desc = "Event description";
    std::string picture = "GFX_report_event_soviet_soldiers";
    std::string major = "yes";
    std::string trigger;
    std::vector<std::string> responseOptions;
};
struct countryInterface{
    std::string name = "Agartha";
	std::string tag;
	std::string religion = "fascism";
	int red,green,blue;
	int capital = 1;
};
struct provinceInterface{
    std::string name = "Land";
	std::string terrain = "plains";
	std::string owner = "NAT";
	int red,green,blue;
	int id,eu4id;
	provinceInterface(int iid){id = iid;}
};
//----CLASSES----CLASSES----CLASSES----CLASSES----CLASSES----CLASSES----CLASSES----CLASSES
struct localisationControllerClass{
    std::ofstream file;
    int localisationIdCounter = 1;
    localisationControllerClass(){
	std::filesystem::create_directories("src/localisation/english");
	file = copy_file("utf8 bom.yml", "src/localisation/english/translation_l_english.yml");
        file<<"l_english:";
    }
    ~localisationControllerClass(){
        file.close();
    }
    std::string addLocalization(std::string str,std::string nameSpace){
        std::string tag = nameSpace+"."+std::to_string(localisationIdCounter++);
        file<<"\n "<<tag<<":0 \""<<str<<"\"";
        return tag;
    }
};localisationControllerClass localisationController;
struct eventControllerClass{
    std::ofstream file;
    std::string contents = "add_namespace = news\n";
    std::vector<eventInterface*> events;
    int newsIdCounter = 100000;
    eventInterface* addEvent(){
        eventInterface* newEvent = new eventInterface();
        newEvent->id = "news."+std::to_string(newsIdCounter++);
        events.push_back(newEvent);
        return newEvent;
    }
    eventControllerClass(){
        file = newFile("src/events/NewsEventsModded.txt");
    }
    ~eventControllerClass(){
        //file<<contents;
        file<<"add_namespace = news\n";
        for(auto ii: events){
			auto i = (*ii);
            file<<"\nnews_event = {";
            file<<"\nid = "<<i.id;
            file<<"\ntitle = "<<localisationController.addLocalization(i.title,"news");
            file<<"\ndesc = "<<localisationController.addLocalization(i.desc,"news");
            file<<"\npicture = "<<i.picture;
            file<<"\nmajor = "<<i.major;
            file<<"\nimmediate = {set_global_flag = "<<i.id<<"}";
            file<<"\ntrigger = {date > 1936.01.2 "<<"NOT = {has_global_flag = "<<i.id<<"}"<<"}";
            file<<"\nmean_time_to_happen = {days = 2}";
            file<<"\nmajor = "<<i.major;
            file<<"\n}";
        }
        file.close();
    }
};
struct countryControllerClass{
	std::vector<countryInterface*> countries;
	countryInterface* addCountry(){
		countryInterface* newCountry = new countryInterface();
		std::string c = "QWERTYUIOPLKJHGFDSAZXCVBNM7896541230";
		newCountry->tag += 'A'+rand()%(('z'+1)-'a');
		newCountry->tag += c[rand()%c.length()];
		newCountry->tag += c[rand()%c.length()];
		countries.push_back(newCountry);
		return newCountry;
	}
	countryControllerClass(){
		std::filesystem::create_directories("src/history/countries");
		std::filesystem::create_directories("src/history/units");
		std::filesystem::create_directories("src/common/country_tags");
		std::filesystem::create_directories("src/common/countries");
		//newFile("");
	}
	~countryControllerClass(){
		std::ofstream tags = std::ofstream("src/common/country_tags/medieval_tags.txt");
		std::ofstream colors = std::ofstream("src/common/countries/colors.txt");
		for (auto ii : countries){
			auto i = (*ii);
			std::ofstream history = std::ofstream("src/common/countries/"+i.tag+".txt");
			std::ofstream common = std::ofstream("src/history/countries/"+i.tag+".txt");
			tags<<i.tag<<" = \"countries/"<<i.tag<<".txt\"\n";
			history<<"graphical_culture = western_european_gfx";
			history<<"\ngraphical_culture_2d = western_european_2d";
			history<<"\ncolor = { "<<i.red<<" "<<i.green<<" "<<i.blue<<" }";
			common<<"capital = "<<i.capital;
			common<<"\noob = \""<<i.tag<<"\"";
			//common<<"\nset_research_slots = 1";
			common<<"\nset_popularities = { fascism = 100 }";
			common<<"\nset_politics = { ruling_party = fascism";
			common<<"\nlast_election = \"1000.1.1\"";
			common<<"\nelection_frequency = 48";
			common<<"\nelections_allowed = no}";
			//common<<"\nrecruit_character = SOV_nikolay_ustryalov";
			colors<<i.tag<<" = { color = rgb { "<<i.red<<" "<<i.green<<" "<<i.blue<<" }\n";
			colors<<"color_ui = rgb { "<<i.red<<" "<<i.green<<" "<<i.blue<<" }}\n";
			history.close();
			common.close();
		}
		tags.close();
		colors.close();
	}
};
struct mapClass{
	std::vector<provinceInterface*> provById = std::vector<provinceInterface*>(20000);
	std::vector<int> provByEu4Id = std::vector<int>(20000);
	int idCounter = 1;
	provinceInterface* addProvince(int fakeid){
		provinceInterface* province = new provinceInterface(idCounter);
		province->eu4id = fakeid;
		provById[idCounter] = province;
		provByEu4Id[fakeid] = idCounter++;
		return province;
	}
};
struct modClass{
    ~modClass(){
    copy_file("hoi4-data/descriptor.mod", "src/descriptor.mod");
    copy_file("hoi4-data/thumbnail.png", "src/thumbnail.png");
    std::cout<<"SUCCESS, took "<<((GetTickCount()-start)/1000.)<<" seconds\n";}
};

modClass mod;
mapClass mapController;
countryControllerClass countryController;
eventControllerClass eventController;
//----MAIN----MAIN----MAIN----MAIN----MAIN----MAIN----MAIN----MAIN----MAIN----MAIN
int main(){//system("cls");

	std::ifstream eu4CountryTags = std::ifstream("eu4-data/country_tags/00_countries.txt");
	std::string line,line2;
	while (std::getline(eu4CountryTags, line)) {
		if(!(isUpper(line[0])&&isUpper(line[1])&&isUpper(line[2])))continue;
		countryInterface* country = countryController.addCountry();
		country->tag = line.substr(0, 3);
		
		std::ifstream eu4CountryFile = std::ifstream("eu4-data/"+between(line,"\""));
		while (std::getline(eu4CountryFile, line2)) {
			if(line2.find("color") == std::string::npos)continue;
			std::stringstream rgb(between(line2,"{","}"));
			rgb>>country->red>>country->green>>country->blue;
			break;
		}
		eu4CountryFile.close();
		
		std::ifstream eu4HistoryCountryFile = 
		std::ifstream("eu4-data/countries/"+country->tag+" - "+between(line,"/","\""));
		while (std::getline(eu4HistoryCountryFile, line2)) {
			if(line2.find("capital") != std::string::npos)
				country->capital = std::stoi(line2.substr(line.find("=")+1));
			if(line2.find("religion") != std::string::npos)country->religion = line2.substr(line.find("=")+1);
			break;
		}
		eu4CountryFile.close();
	}eu4CountryTags.close();
	
	std::ifstream definition = std::ifstream("eu4-data/map/definition.csv");
	std::getline(definition, line);
	while (std::getline(definition, line)) {
		std::vector<std::string> splt = split(line,";");
		provinceInterface* province = mapController.addProvince(std::stoi(splt[0]));
		province->red = std::stoi(splt[1]);
		province->green = std::stoi(splt[2]);
		province->blue = std::stoi(splt[3]);
	}
	
	
	
	definition.close();

}

//eventController.addEvent();
//countryController.addCountry();