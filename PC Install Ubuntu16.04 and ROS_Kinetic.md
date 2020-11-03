# PC Install Ubuntu16.04 and ROS_Kinetic
## 1.安装Ubuntu16.04
[Ubuntu安装教程](https://ubuntu.com/tutorials/install-ubuntu-desktop)     
[Ubuntu16.04 镜像下载](https://releases.ubuntu.com/?_ga=2.86995736.1014249643.1604302018-1117975173.1604302018)
## 2.安装ROS_Kinetic
[安装ROS_Kinetic](http://wiki.ros.org/cn/kinetic/Installation/Ubuntu)
### 2.1 配置 Ubuntu 软件仓库以允许 "restricted"、"universe" 和 "multiverse"这三种安装模式
### 2.2 添加 sources.list(建议采用国内源）
```bash
sudo sh -c '. /etc/lsb-release && echo "deb http://mirrors.tuna.tsinghua.edu.cn/ros/ubuntu/ `lsb_release -cs` main" > /etc/apt/sources.list.d/ros-latest.list'
```
[镜像源列表](http://wiki.ros.org/ROS/Installation/UbuntuMirrors)
### 2.3 添加公钥
```bash
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
```
### 2.4 安装
```bash
sudo apt-get update
sudo apt-get install ros-kinetic-desktop-full
```
### 2.5 初始化 rosdep
```bash
sudo apt install python-rosdep
sudo rosdep init
rosdep update
```
注意：由于网络问题，执行rosdep init和rosdep update可能出现相关错误   
解决方法：
```bash
sudo gedit /etc/hosts
# 在文件末尾添加如下语句,保存并退出
151.101.76.133 raw.githubusercontent.com
```
### 2.6 环境配置
添加ros环境变量到bashrc:
```bash
echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
```
### 2.7 构建工厂依赖
```bash
sudo apt install python-rosinstall python-rosinstall-generator python-wstool build-essential
```
### 2.8 检查是否安装成功
```bash
roscore
```
