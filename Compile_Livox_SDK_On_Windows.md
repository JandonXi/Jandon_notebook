# Compile livox-sdk on windows 7 use vs-2017
## 1.Method from official website
***
### Dependencies
Livox SDK supports Visual Studio 2015/2017 and requires install [CMake 3.0.0+](https://cmake.org/) as dependencies.  

In the Livox SDK directory, run the following commands to create the Visual Studio solution file. 
Generate the 32-bit project:

```
cd Livox-SDK
.\third_party\apr\apr_build.bat
cd build && \
cmake ..
```
Generate the 64-bit project:
```
cd Livox-SDK
.\third_party\apr\apr_build.bat amd64
cd build && \
cmake .. -G "Visual Studio 15 2017 Win64"
```
#### Compile Livox SDK
You can now compile the Livox SDK in Visual Studio.
***
## 2.Some questions and solutions
### Questions
1. When excete `.\third_party\apr\apr_build.bat` cmd report some erros lead to fail to compile apr.   
2. After excete `cmake ..`, use vs-2017 compile sdk some outer symbol can not be parsed.
### My method
Open apr_build.bat can find it just do two things: install and compile apr & use cmake build sdk project
#### 1.Install and compile apr
apr-1.6.5 has been in our sdk_package
```
cd apr-1.6.5
"path\vcvarsall.bat" x86_amd64
nmake /f Makefile.win ARCH="x64 Release" PREFIX=..\apr-1.6.5-dist buildall install
```
copy the three folder bin include lib in pr-1.6.5-dist to the apr-1.6.5
#### 2.Compile sdk
```
cd Livos-SDK
cd build 
cmake .. -G "Visual Studio 15 2017 Win64"
```
**pay attention to x86 or x64, here we compile x64 version.**  
Then open project in vs-2017 and compile the sdk.
