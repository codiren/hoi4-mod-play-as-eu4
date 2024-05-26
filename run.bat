cls
echo COMPILING...
g++ -std=c++2a -O3 -o C:\projects\hoi4-mod-play-as-eu4\master.exe C:\projects\hoi4-mod-play-as-eu4\master.cpp & if errorlevel 1 (
                                                                                                         echo [31mCOMPILATION HAS FAILED!!![0m & exit /b %errorlevel%
                                                                                                     )

rmdir /s /q C:\projects\hoi4-mod-play-as-eu4\src
mkdir C:\projects\hoi4-mod-play-as-eu4\src
C:\projects\hoi4-mod-play-as-eu4\master.exe