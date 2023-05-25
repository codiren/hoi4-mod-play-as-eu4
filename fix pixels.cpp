#include <iostream>
#include <windows.h>
#include <gdiplus.h>
#include <map>
#include <tuple>
#include <vector>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
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
    std::rename("map/provinces.bmp", "map/provinces2.bmp");
	Bitmap bmp(L"map/provinces2.bmp");
	int width = bmp.GetWidth();
    int height = bmp.GetHeight();
	
	ARGB matm[width][height];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++){//std::cout<<x<<" "<<y<<"\n";
			Color pixelColor;
            bmp.GetPixel(x, y, &pixelColor);
            matm[x][y] = Color::MakeARGB(255, pixelColor.GetR(), pixelColor.GetG(), pixelColor.GetB());
		}
	}
	for (int y = 1; y < height; y++)
    {
        for (int x = 1; x < width; x++){
        	if(matm[x][y]!=matm[x-1][y]&&matm[x][y]!=matm[x][y-1]&&matm[x][y]!=matm[x-1][y-1]&&matm[x-1][y]!=matm[x-1][y-1]&&matm[x-1][y]!=matm[x][y-1]&&matm[x][y-1]!=matm[x-1][y-1])
        		{
        			std::cout<<7;
        			matm[x-1][y] = matm[x][y];
        			matm[x][y-1] = matm[x][y];
        			matm[x-1][y-1] = matm[x][y];
        			bmp.SetPixel(x-1, y, matm[x][y]);
        			bmp.SetPixel(x, y-1, matm[x][y]);
        			bmp.SetPixel(x-1, y-1, matm[x][y]);
				}
		}
	}std::cout<<'\n';
	std::map<int,std::vector<int>> ce;
	for (int y = 0; y < height; y++){for (int x = 0; x < width; x++){
		if(ce.find(matm[x][y])==ce.end()){ce[matm[x][y]].push_back(0);ce[matm[x][y]].push_back(x);ce[matm[x][y]].push_back(y);}
		ce[matm[x][y]][0]++;
	}}
    std::vector<std::pair<int,int>> ca;
    ca.push_back(std::pair<int,int>(1,0));ca.push_back(std::pair<int,int>(1,1));ca.push_back(std::pair<int,int>(0,1));ca.push_back(std::pair<int,int>(-1,1));
    ca.push_back(std::pair<int,int>(-1,0));ca.push_back(std::pair<int,int>(-1,-1));ca.push_back(std::pair<int,int>(0,-1));ca.push_back(std::pair<int,int>(1,-1));
    ca.push_back(std::pair<int,int>(2,0));ca.push_back(std::pair<int,int>(2,1));ca.push_back(std::pair<int,int>(2,2));ca.push_back(std::pair<int,int>(1,2));
    ca.push_back(std::pair<int,int>(0,2));ca.push_back(std::pair<int,int>(-1,2));ca.push_back(std::pair<int,int>(-2,2));ca.push_back(std::pair<int,int>(-2,1));
    ca.push_back(std::pair<int,int>(-2,0));ca.push_back(std::pair<int,int>(-2,-1));ca.push_back(std::pair<int,int>(-2,-2));ca.push_back(std::pair<int,int>(-1,-2));
    ca.push_back(std::pair<int,int>(0,-2));ca.push_back(std::pair<int,int>(1,-2));ca.push_back(std::pair<int,int>(2,-2));ca.push_back(std::pair<int,int>(2,-1));
    for(auto kas:ce){
    	if(kas.second[0]>8)continue;
    	std::cout<<kas.second[0]<<"\n";
    	int x = kas.second[1];
    	int y = kas.second[2];
    	ARGB s = kas.first;
    	for(int i = 0;kas.second[0]<=13;i++){std::cout<<(ca[i].first+x)<<" "<<(ca[i].second+y)<<'\n';
    		if(i>ca.size())return -1;
    		if((ca[i].second+y)>-1&&(ca[i].first+x)>-1&&(ca[i].second+y)<height&&(ca[i].first+x)<width&&matm[ca[i].first+x][ca[i].second+y] != s)
			{kas.second[0]++;matm[ca[i].first+x][ca[i].second+y] = s;bmp.SetPixel(ca[i].first+x, ca[i].second+y, s);}
		}
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
//GdiplusShutdown(&gdiplusToken);
	while(!std::remove("map/provinces2.bmp"));
    
    //system("pause");
    return 0;
}

