# Kinetic Install Turtlebot
## 1.安装相关依赖和更新
终端执行：
```bash
sudo apt-get install python-rosdep python-wstool  
sudo rosdep init
rosdep update
```
注意：执行 sudo rosdep init 命令时,可能出现以下的错误:
```bash
ERROR: default sources list file already exists:
    /etc/ros/rosdep/sources.list.d/20-default.list
Please delete if you wish to re-initialize
```
解决方法：执行下述语句后再执行初始化更新
```bash
sudo rm /etc/ros/rosdep/sources.list.d/20-default.list
```
## 2.源码下载编译
建立turtlebot_ws文件夹存放三个工作空间：
```bash
mkdir ~/turtlebot_ws
cd turtlebot/ws
```
在turtlebot_ws下建立rocon目录，下载编译：
```bash
mkdir rocon
cd rocon
wstool init -j5 src https://raw.github.com/robotics-in-concert/rocon/release/kinetic/rocon.rosinstall
source /opt/ros/kinetic/setup.bash 
rosdep install --from-paths src -i -y 
catkin_make
```
在turtlebot_ws下建立kobuki目录，下载编译：
```bash
mkdir kobuki
cd kobuki
wstool init -j5 src https://raw.githubusercontent.com/yujinrobot/yujin_tools/kinetic-devel/rosinstalls/kinetic/kobuki.rosinstall
source ~/turtlebot_ws/rocon/devel/setup.bash
rosdep install --from-paths src -i -y
catkin_make
```
在turtlebot_ws下建立turtlebot目录，下载编译：
```bash
mkdir turtlebot
cd turtlebot
wstool init -j5 src https://raw.github.com/yujinrobot/yujin_tools/kinetic-devel/rosinstalls/kinetic/turtlebot.rosinstall
source ~/turtlebot_ws/kobuki/devel/setup.bash
rosdep install --from-paths src -i -y
catkin_make
```
