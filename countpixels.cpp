#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <map>
#include <vector>
#include <tuple>
#include <set>
#include <windows.h>
#include <gdiplus.h>
#include <initguid.h>
#include <guiddef.h>
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
std::map<std::tuple<int, int , int>,std::tuple<int, int, int , int , int, int>> PrintRGBValues(Bitmap* bitmap)
{
    BitmapData bitmapData;
    Rect rect(0, 0, bitmap->GetWidth(), bitmap->GetHeight());
    bitmap->LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, &bitmapData);

    BYTE* pixelData = reinterpret_cast<BYTE*>(bitmapData.Scan0);
	std::map<std::tuple<int, int , int>,std::tuple<int, int , int , int, int, int>> seh;
    for (int y = 0; y < bitmap->GetHeight(); y++)
    {
        for (int x = 0; x < bitmap->GetWidth(); x++)
        {
            BYTE blue = pixelData[x * 4];
            BYTE green = pixelData[x * 4 + 1];
            BYTE red = pixelData[x * 4 + 2];
            if(seh.find(std::tuple<int, int , int>(red,green,blue))==seh.end()){
            	seh[std::tuple<int, int , int>(red,green,blue)] = std::tuple<int, int , int, int , int, int>(x,y,std::max(get<2>(seh[std::tuple<int, int , int>(red,green,blue)]),x),std::max(get<3>(seh[std::tuple<int, int , int>(red,green,blue)]),y),x,y);
            	continue;
			}
            seh[std::tuple<int, int , int>(red,green,blue)] = std::tuple<int, int , int, int , int, int>(std::min(get<0>(seh[std::tuple<int, int , int>(red,green,blue)]),x),std::min(get<1>(seh[std::tuple<int, int , int>(red,green,blue)]),y),std::max(get<2>(seh[std::tuple<int, int , int>(red,green,blue)]),x),std::max(get<3>(seh[std::tuple<int, int , int>(red,green,blue)]),y),x,y);
        }

        pixelData += bitmapData.Stride;
    }
    //bitmap->UnlockBits(&bitmapData);
	return seh;
}
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
    UINT num = 0;
    UINT size = 0;

    ImageCodecInfo* pImageCodecInfo = nullptr;

    GetImageEncodersSize(&num, &size);
    if (size == 0)
        return -1;

    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    if (pImageCodecInfo == nullptr)
        return -1;

    GetImageEncoders(num, size, pImageCodecInfo);

    for (UINT j = 0; j < num; ++j)
    {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
        {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;
        }
    }

    free(pImageCodecInfo);
    return -1;
}
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
    std::map<std::tuple<int, int , int>,std::tuple<int, int , int, int , int, int>> seh = PrintRGBValues(bitmap);
    std::multimap<int,std::tuple<int, int, int , int , int>> sem;
    std::ifstream de("error.log");
    std::string t;
    std::set<int> prob;
    std::map<std::tuple<int, int , int>,ARGB*> proa;
    while(std::getline(de,t)){
    	if(t.find("TOO LARGE BOX")==-1)continue;
    	prob.insert(std::stoi(t.substr(t.find("Province ")+9)));
	}
	std::ifstream ce("map/definition.csv");
	while(std::getline(ce,t)){
		if(prob.find(std::stoi(t))==prob.end())continue;
		ARGB* mazi = new ARGB[30*30]; // Allocate memory for the rows
		for (int x = 0; x < 30*30; x++) {
    		mazi[x] = Color::MakeARGB(255, rand() % 256, rand() % 256, rand() % 256);
		}
		proa[std::tuple<int, int , int>(std::stoi(split(t,";")[1]),std::stoi(split(t,";")[2]),std::stoi(split(t,";")[3]))] = mazi;
	}ce.close();
    
    for(auto kas:seh){
    	sem.insert(std::pair<int,std::tuple<int, int , int,int,int>>(((get<2>(kas.second)-get<0>(kas.second))+(get<3>(kas.second)-get<1>(kas.second))),std::tuple<int,int,int,int,int>(get<0>(kas.first),get<1>(kas.first),get<2>(kas.first),get<4>(kas.second),get<5>(kas.second))));
	}
	std::set<std::tuple<int,int,int>> stetes2;
	std::set<std::tuple<int,int,int>> stetes3;
	std::set<std::tuple<int,int,int>> stetes4;
	std::cout<<"too big provinces:\n";
	for(auto kas:sem){
		if(proa.find(std::tuple(get<0>(kas.second),get<1>(kas.second),get<2>(kas.second)))!=proa.end()){
			int red = get<0>(kas.second);
			int green = get<1>(kas.second);
			int blue = get<2>(kas.second);
			stetes2.insert(std::tuple<int, int , int>(red,green,blue));
    		std::cout<<kas.first<<" rgb: "<<get<0>(kas.second)<<";"<<get<1>(kas.second)<<";"<<get<2>(kas.second)<<" x: "<<get<3>(kas.second)<<" y: "<<get<4>(kas.second)<<" "<<"\n";
		}
	}
	stetes3 = stetes2;stetes4 = stetes2;
	
	
	
	
	
	
	
	
	
	Bitmap bmp(L"provinces.bmp");
	//BitmapData bitmapData;
    //Rect rect(0, 0, bitmap->GetWidth(), bitmap->GetHeight());
	//bmp.LockBits(&rect, ImageLockModeWrite, PixelFormat24bppRGB, &bitmapData);
    // Get the image dimensions
    int width = bmp.GetWidth();
    int height = bmp.GetHeight();
	std::ifstream defin("map/definition.csv");
	std::vector<std::string> dataaa;
	std::map<std::tuple<int,int,int>,std::vector<std::string>> datz;
	while(std::getline(defin,t)){dataaa.push_back(t+"\n");datz[std::tuple<int,int,int>(std::stoi(split(t,";")[1]),std::stoi(split(t,";")[2]),std::stoi(split(t,";")[3]))] = split(t,";");}
	defin.close();
	std::ofstream defino("map/definition.csv");
    // Loop through each pixel and change white pixels to black
    std::ifstream get_states("byrealid.txt");std::map<int,int> stetes;while(std::getline(get_states,t))stetes[std::stoi(split(t," ")[0])] = std::stoi(split(t," ")[1]);
    
    std::cout<<"fixing map\n";
    std::vector<int> added_provinces;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Color pixelColor;
            bmp.GetPixel(x, y, &pixelColor);
			if(proa.find(std::tuple<int, int , int>(pixelColor.GetR(),pixelColor.GetG(),pixelColor.GetB()))==proa.end())continue;	
			auto spalva = proa[std::tuple<int, int , int>(pixelColor.GetR(),pixelColor.GetG(),pixelColor.GetB())][(x+proa[std::tuple<int, int , int>(pixelColor.GetR(),pixelColor.GetG(),pixelColor.GetB())][0]%50)/100+((y+proa[std::tuple<int, int , int>(pixelColor.GetR(),pixelColor.GetG(),pixelColor.GetB())][0]%50)/100)*30];
            
            if(stetes4.find(std::tuple<int, int , int>(pixelColor.GetR(),pixelColor.GetG(),pixelColor.GetB()))!=stetes4.end()){
            	proa[std::tuple<int, int , int>(pixelColor.GetR(),pixelColor.GetG(),pixelColor.GetB())][(x+proa[std::tuple<int, int , int>(pixelColor.GetR(),pixelColor.GetG(),pixelColor.GetB())][0]%50)/100+((y+proa[std::tuple<int, int , int>(pixelColor.GetR(),pixelColor.GetG(),pixelColor.GetB())][0]%50)/100)*30] = Color::MakeARGB(255,pixelColor.GetR(),pixelColor.GetG(),pixelColor.GetB());
            	spalva = proa[std::tuple<int, int , int>(pixelColor.GetR(),pixelColor.GetG(),pixelColor.GetB())][(x+proa[std::tuple<int, int , int>(pixelColor.GetR(),pixelColor.GetG(),pixelColor.GetB())][0]%50)/100+((y+proa[std::tuple<int, int , int>(pixelColor.GetR(),pixelColor.GetG(),pixelColor.GetB())][0]%50)/100)*30];
            	stetes4.erase(std::tuple<int, int , int>(pixelColor.GetR(),pixelColor.GetG(),pixelColor.GetB()));
			}
			int red = ((spalva >> 16) & 0xFF);
            int green = ((spalva >> 8) & 0xFF);
            int blue = ((spalva) & 0xFF);
            bmp.SetPixel(x, y, spalva);
            std::vector<std::string> tk = datz[std::tuple<int, int , int>(pixelColor.GetR(),pixelColor.GetG(),pixelColor.GetB())];
            //std::cout<<tk[0]<<'\n';
            if(stetes2.find((std::tuple<int, int , int>(red,green,blue)))!=stetes2.end())continue;
            stetes2.insert(std::tuple<int, int , int>(red,green,blue));
			dataaa.push_back(std::to_string(dataaa.size())+";"+std::to_string(red)+";"+std::to_string(green)+";"+std::to_string(blue)+";"+tk[4]+";"+tk[5]+";"+tk[6]+";"+tk[7]+"\n");
			added_provinces.push_back(dataaa.size()-1);
			if(tk[4]!="land")continue;
			if(stetes3.find(std::tuple<int, int , int>(red,green,blue))!=stetes3.end())continue;
			int stateid = stetes[std::stoi(tk[0])];//og
			std::ifstream kelonta("history/states/"+std::to_string(stateid)+".txt");
			std::vector<std::string> lolm;
			while(std::getline(kelonta,t)){
				if(t=="provinces={"){
					lolm.push_back(t);
					std::getline(kelonta,t);
					t += " "+std::to_string(dataaa.size()-1);
					lolm.push_back(t);
				}
				else lolm.push_back(t);
			}
			kelonta.close();
			std::ofstream kelontaa("history/states/"+std::to_string(stateid)+".txt");
			for(auto kas:lolm){
				kelontaa<<kas<<'\n';
			}
        }
    }
	for(auto kas:dataaa){
		defino<<kas;
	}
	
	Bitmap newBitmap(width, height, PixelFormat24bppRGB);//make 24 bit
Graphics originalGraphics(&bmp);
Graphics newGraphics(&newBitmap);
newGraphics.DrawImage(&bmp, 0, 0, width, height);
	
	
    // Save the modified image
    CLSID bmpEncoderClsid;
GetEncoderClsid(L"image/bmp", &bmpEncoderClsid);
newBitmap.Save(L"map/provinces.bmp", &bmpEncoderClsid, nullptr);
std::cout<<"saved new map\n";

std::ifstream fixsupply("map/strategicregions/0-NULINTAS.txt");
std::vector<std::string> sup;

while(std::getline(fixsupply,t)){
	if(t=="}}"){//std::cout<<"\n"<<added_provinces.size()<<"\n";
		for(int kas:added_provinces){
			sup.push_back(std::to_string(kas)+"\n");
		}
		sup.push_back("}\n}");
		break;
	}
	sup.push_back(t+"\n");
}
fixsupply.close();
std::ofstream fixedsupply("map/strategicregions/0-NULINTAS.txt");
for(auto kas:sup){
	fixedsupply<<kas;
}

fixedsupply.close();
defin.close();
defino.close();
de.close();
get_states.close();


	//system("pause");
}
