# VSCode C/C++开发 ===>>windows
## 1.开发环境搭建
### 1.1 软件下载
* [**VSCode download**](https://code.visualstudio.com/Download)
* VSCode extensions install
  * C/C++
  * CMake
  * CMake Tools
* [Mingw download](https://sourceforge.net/projects/mingw-w64/files/)
* [CMake downlood](https://cmake.org/download/)  

软件下载安装完成后，把`bin`路径配置到环境变量，可以在`powershell`运行`g++ --version`、`cmake --version`检查是否成功安装 
（win10下shift+鼠标右键即可打开`powershell`窗口）
## 2.C++编译与调试
* 基于`g++`命令
* 基于`tasks.json`和`launch.json`文件
* 基于`cmake`
## 3.[从零创建一个CMakeProject](https://code.visualstudio.com/docs/cpp/cmake-linux)
## 4.win10、VSCode、Mingw下配置OpenCV
### 4.1软件版本：(注意这里的版本与上面所述存在差异）
建议直接使用编译好的文件[OpenCV-MinGW-Build](https://github.com/huihut/OpenCV-MinGW-Build)，而不是用cmake自己编译 
* [MinGW-x86_64-8.1.0-posix-seh-rt_v6-rev0](https://sourceforge.net/projects/mingw-w64/files/)
* [CMake-3.14.1](https://github.com/Kitware/CMake/releases?after=v3.15.0-rc3)
* [OpenCV-4.1.1-x64](https://github.com/huihut/OpenCV-MinGW-Build) 
把三个软件bin路径加入环境变量
### 4.2VSCode使用CMake编写OpenCV项目
* 创建一个空的项目文件夹`opencv_test`
* 在项目中新建文件`CMakeLists.txt`,内容如下:
```cmake
cmake_minimum_required(VERSION 3.0)
project(test_opencv)
set(OpenCV_DIR "D:\\OpenCV-4.1.1") 
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_executable(test_opencv src/test_opencv.cc)
target_link_libraries(test_opencv ${OpenCV_LIBRARIES})
```
* 在项目中新建文件夹src,在src中新建test_opencv.cc,内容如下：
```C++
#include "opencv2\opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Mat img=imread("E:\\vscode_test\\src\\hhu.png");
    if(img.empty())
        cout<<"empty"<<endl;
    else
        imshow("test",img);
    waitKey(0);
    return 0;
}
```
* 编译运行参考2，由此开启opencv编程
