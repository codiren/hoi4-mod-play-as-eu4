#define MAX_PROV 20000

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <set>
#include <vector>
#include <tuple>
#include <windows.h>
#include <gdiplus.h>
#include <cstdio>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
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
std::set<std::tuple<int, int , int>> PrintRGBValues(Bitmap* bitmap)
{
    BitmapData bitmapData;
    Rect rect(0, 0, bitmap->GetWidth(), bitmap->GetHeight());
    bitmap->LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, &bitmapData);

    BYTE* pixelData = reinterpret_cast<BYTE*>(bitmapData.Scan0);
	std::set<std::tuple<int, int , int>> seh;
    for (UINT y = 0; y < bitmap->GetHeight(); y++)
    {
        for (UINT x = 0; x < bitmap->GetWidth(); x++)
        {
            BYTE blue = pixelData[x * 4];
            BYTE green = pixelData[x * 4 + 1];
            BYTE red = pixelData[x * 4 + 2];
            if(seh.find(std::tuple<int, int , int>(red,green,blue))!=seh.end())continue;
            seh.insert(std::tuple<int, int , int>(red,green,blue));
        }

        pixelData += bitmapData.Stride;
    }
	return seh;
}
struct provclass{
	std::string name = "";
	std::string owner = "NAT";
	std::vector<std::string> cores;
	int basetax = 1;
	int baseprod = 1;
	int basemen = 1;
	std::string terrain = "plains";
	std::tuple<int,int,int> color;
	bool exists = false;
	int realid = 0;
};
int main()
{
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    Bitmap* bitmap = new Bitmap(L"provinces.bmp");
    if (bitmap->GetLastStatus() != Ok)
    {
        std::cout << "Failed to load the BMP file." << std::endl;
        delete bitmap;
        return -1;
    }
    std::set<std::tuple<int, int , int>> seh = PrintRGBValues(bitmap);
    provclass prov[MAX_PROV];
    std::string t;
    std::vector<std::string> tv;
    std::ifstream defeu("map/definition eu.csv");
    std::ofstream def("map/definition.csv");
    while(std::getline(defeu,t)){
    	tv = split(t,";");
    	if(seh.find(std::tuple<int,int,int>(std::stoi(tv[1]),std::stoi(tv[2]),std::stoi(tv[3])))==seh.end())continue;
    	seh.erase(std::tuple<int,int,int>(std::stoi(tv[1]),std::stoi(tv[2]),std::stoi(tv[3])));
    	prov[std::stoi(tv[0])].name = tv[4];
    	prov[std::stoi(tv[0])].color = std::tuple<int,int,int>(std::stoi(tv[1]),std::stoi(tv[2]),std::stoi(tv[3]));
    	prov[std::stoi(tv[0])].exists = true;
	}
	if(seh.size()){std::cout<<"didnt find all definitions\n";
	for(auto kas:seh)std::cout<<"missed province with color "<<get<0>(kas)<<" "<<get<1>(kas)<<" "<<get<2>(kas)<<"\n";system("pause");return 1;}
	std::ifstream inlakes("map/default eu lakes.map");while(inlakes>>t)prov[std::stoi(t)].terrain = "lakes";
	std::ifstream insea("map/default eu seas.map");while(insea>>t)prov[std::stoi(t)].terrain = "ocean";
	std::ifstream proveu("map/only province save.eu4");bool kitascores = false;int provic = 0;
	while(std::getline(proveu,t)){
		if(kitascores){
			kitascores = false;
			for(std::string kas:split(t," ")){
				kas.erase(std::remove(kas.begin(), kas.end(), '\t'), kas.end());
				kas.erase(std::remove(kas.begin(), kas.end(), ' '), kas.end());
				if(kas.length()==0)continue;
				prov[provic].cores.push_back(kas);
			}
			continue;
		}
		if(t[0]=='-'&&t[t.length()-1]=='{'&&t[t.length()-2]=='=')provic = std::stoi(t)*-1;
		//else if (t.starts_with("\t\tname=\"")){prov[provic].name = t.substr(8,t.length()-10);}
		else if (t.starts_with("\t\towner=\"")){prov[provic].owner = t.substr(9,3);}
		//else if (t.starts_with("\t\tcontroller=\"")){prov[provic].controller = t.substr(14,3);}
		else if (t == "\t\tcores={"){kitascores=true;}
		else if (t.starts_with("\t\tbase_tax=")){prov[provic].basetax = std::stoi(t.substr(11,2));}
		else if (t.starts_with("\t\tbase_production=")){prov[provic].baseprod = std::stoi(t.substr(18,2));}
		else if (t.starts_with("\t\tbase_manpower=")){prov[provic].basemen = std::stoi(t.substr(16,2));}
	}std::ifstream ine("map/terrain eu.txt");kitascores = false;std::string terainas;
	while(std::getline(ine,t)){
		if(kitascores){
			if(t.find("}")!=18446744073709551615){kitascores = false;terainas = "plains";continue;}
			if(t.find("#")!=18446744073709551615)t = split(t,"#")[0];
			tv = split(t," ");
			for(std::string kas:tv){
				if(prov[std::atoi(kas.c_str())].terrain=="lakes"||prov[std::atoi(kas.c_str())].terrain=="ocean")continue;
				prov[std::atoi(kas.c_str())].terrain = terainas;
			}
			continue;
		}
		if(t=="\tglacier = {"||t=="\tmountain = {")terainas = "mountain";
		else if(t=="\twoods = {"||t=="\tforest = {")terainas = "forest";
		else if(t=="\thills = {"||t=="\thighlands = {")terainas = "hills";
		else if(t=="\tjungle = {")terainas = "jungle";
		else if(t=="\tmarsh = {")terainas = "marsh";
		else if(t=="\tdesert = {"||t=="\tcoastal_desert = {"||t=="\tdrylands = {")terainas = "desert";
		else if(t=="\t\tterrain_override = {")kitascores = true;
	}
    //output provinces
    def<<"0;0;0;0;land;false;unknown;0";provic = 0;int provicland = 0;kitascores = false;
    std::ofstream outairport("map/airports.txt");std::ofstream outrocketsites("map/rocketsites.txt");//std::ofstream outdepots("map/supply_nodes.txt");
    //std::ofstream strategicregions("map/strategicregions/"+std::to_string(provic)+".txt");
    std::ofstream strategicregions("map/strategicregions/0-NULINTAS.txt");
    std::ofstream localizations("localisation/english/state_names_l_english.yml");
    //localizations<<"\xEF\xBB\xBF";
	//std::ofstream loccountr("localisation/english/countries_l_english.yml");
	//loccountr<<"l_english:";
    strategicregions<<"strategic_region={\nid="<<1<<"\nname=\""<<0<<"_region\"\nprovinces={\n";localizations<<"l_english:";
    std::ofstream stateidbyrealprov("byrealid.txt");
    std::string path = "history/states/";
    for (const auto & entry : std::filesystem::directory_iterator(path))
        std::remove(entry.path().string().c_str());
    for(int i = 1;i<MAX_PROV;i++){
    	if(prov[i].exists==false)continue;provic++;
    	prov[i].realid = provic;
    	terainas = "land";
    	if(prov[i].terrain=="ocean")terainas = "sea";
    	else if(prov[i].terrain=="lakes")terainas = "lake";
    	def<<'\n'<<provic<<";"<<get<0>(prov[i].color)<<";"<<get<1>(prov[i].color)<<";"<<get<2>(prov[i].color)<<";"<<terainas<<";"<<"false"<<";"<<prov[i].terrain<<";"<<1;
		strategicregions<<provic<<'\n';
		if(terainas != "land"){continue;}provicland++;
		localizations<<"\n "<<provicland<<"_state:0 \""<<prov[i].name<<"\"";
		std::ofstream states("history/states/"+std::to_string(provicland)+".txt");
		states<<"state={\nid="<<provicland<<"\nname=\""<<provicland<<"_state\"\n"<<"manpower = "<<prov[i].basemen*20000<<"\n";
		stateidbyrealprov<<provic<<" "<<provicland<<"\n";
		states<<"history={\nowner = "<<prov[i].owner;
		states<<"\nbuildings = {\n";
		states<<"infrastructure = "<<(prov[i].basetax>10?10:prov[i].basetax)<<"\n";
		int indr = (prov[i].baseprod+prov[i].basetax)/5;
		int arm = (prov[i].baseprod+prov[i].basemen)/5;
		states<<"industrial_complex = "<<(indr>7?7:indr)<<"\n";
		int cat = (prov[i].baseprod+prov[i].basemen+prov[i].basetax)/2.5;
		states<<"arms_factory = "<<(arm>7?7:arm)<<"\n}\n";
		for(std::string kas:prov[i].cores){
			states<<"\nadd_core_of = "<<kas;
		}
		states<<"\n}\nstate_category = a"<<(cat>12?12:cat)<<"\nprovinces={\n"<<provic<<"\n}\n"<<"local_supplies=0.0"<<"\n}";
		outairport<<provicland<<"={"<<provic<<"}"<<'\n';
		outrocketsites<<provicland<<"={"<<provic<<"}"<<'\n';
		//if(rand()%5==3)outdepots<<1<<" "<<provic<<'\n';
	}strategicregions<<"\n}}";
	std::cout<<provic<<" provinces\n";
	//countries
	std::ifstream tager("common/country_tags/01_countries.txt");
	std::ofstream vesk("common/countries/colors.txt");
	while(std::getline(tager,t)){
		if(t.find("/")==-1)continue;
		//loccountr<<"\n "<<t.substr(0,3)<<":0 \""<<t.substr(t.find("/")+1,t.find(".")-t.find("/")-1)<<"\"";
		//std::cout<<split(t,"\"")[1]<<'\n';
		if(t.substr(0,3) == "ISR")break;
		std::ifstream isce("common/"+split(t,"\"")[1]);
		std::string taagas = t.substr(0,3);
		std::getline(isce,t);std::getline(isce,t);std::getline(isce,t);
		vesk<<taagas<<" = {\ncolor = rgb"<<t.substr(t.find("=")+1)<<"\n}\n";
	}
	path = "countries eu";
    for (const auto & entry : std::filesystem::directory_iterator(path)){
        std::ifstream adas(entry.path().string());
        while(std::getline(adas,t)){
        	if(t.substr(0,10)=="capital = "){
        		if(prov[std::stoi(t.substr(10))].exists==false)break;
        		std::ofstream anas("history/countries/"+entry.path().string().substr(entry.path().string().find("countries eu")+13,3)+".txt");
        		anas<<"capital = "<<prov[std::stoi(t.substr(10))].realid;
        		anas<<"\nset_politics = {\nruling_party = neutrality\nlast_election = \"1444.1.1\"\nelection_frequency = 48\nelections_allowed = no\n}\nset_popularities = {";
        		anas<<"democratic = 0\nfascism = 0\ncommunism = 0\nneutrality = 100\n}";
        		anas.close();
				break;
			}
		}
	}
	def.close();
	tager.close();
	vesk.close();
	stateidbyrealprov.close();
	defeu.close();
	//loccountr.close();
	localizations.close();
	strategicregions.close();
	outairport.close();
	outrocketsites.close();
	//system("pause");
    //system("countpixels.exe");
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}
