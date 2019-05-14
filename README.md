# my-first-game
Support repository for the C++ game development workshop @EA


## Building on Linux

```
 # git clone https://github.com/abuwarez/my-first-game.git
 # cd my-first-game/
 # mkdir build
 # cd build/
 # cmake ..
 # make
 # ./MyFirstGame 
```

## Building on Windows using Visual Studio 2017

-Install 'Git Tools for Windows' and 'GitHub for Visual Studio' under Individual Components inside Visual Studio Installer  
-Open Visual Studio 2017 -> Team -> Manage Connections...  
-Configure repo inside Team Explorer Connect -> Local Git Repositories -> Clone: URL: https://github.com/abuwarez/my-first-game.git  
-Click Clone Button and wait for Visual Studio to finish project setup  
-VS should detect CMake  
-Select MyFirstGame.exe as startup item and launch it  

