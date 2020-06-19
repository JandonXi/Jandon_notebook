# Ubuntu16.04 ROS_Kinetic Use Livox-Horizon
## step 1 Install Ubuntu16.04

## step 2 Install Ros-Kinetic
### 2.1 Configure Ubuntu repositories allow "restricted," "universe," and "multiverse."
### 2.2 Set up sources.list
```
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
```
### 2.3 Set up keys
```
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
```
### 2.4 Installation
```
sudo apt-get update
sudo apt-get install ros-kinetic-desktop-full
```
### 2.5 Initialize rosdep
```
sudo apt install python-rosdep
sudo rosdep init
rosdep update
```
if failed and error like 'sudo rosdep init error: cannot download default sources list from: [closed],you can 
```
sudo gedit /etc/hosts
# 在文件末尾添加如下语句,保存并退出
151.101.84.133 raw.githubusercontent.com
```
### 2.6 Environment setup
```
echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
```
### 2.7 Install rosinstall
```
sudo apt install python-rosinstall python-rosinstall-generator python-wstool build-essential
```
### 2.8 `Remove` Ros-Kinetic
```
$ sudo apt-get remove ros-kinetic-*
```
## step 3 Compile Livox-SDK
### 3.1 Dependencies
Livox SDK requires [CMake 3.0.0+](https://cmake.org/) as dependencies. You can install these packages using apt:
```
sudo apt install cmake pkg-config
```
### 3.2 Compile

In the Livox SDK directory, run the following commands to compile the project:
```
git clone https://github.com/Livox-SDK/Livox-SDK.git
cd Livox-SDK
```
Install apr library by:

```
sudo ./third_party/apr/apr_build.sh
```

or by:

```
sudo apt install libapr1-dev
```

then

```
cd build && cmake ..
make
sudo make install
```
## step 4 Install Livox-Ros-Driver
### 4.1 Get and build livox_ros_driver
Get livox_ros_driver from GitHub :  
```
git clone https://github.com/Livox-SDK/livox_ros_driver.git ws_livox/src
```
Use the following command to build livox_ros_driver :
```bash
cd ws_livox
catkin_make
```
Use the following command to update the current ROS package environment :  
```
source ./devel/setup.sh
```
### 4.2 Run livox_ros_driver