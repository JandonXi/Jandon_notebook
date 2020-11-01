# Solution for ROS Workspace Overlay
解决ros工作空间在bashrc中的覆盖问题  
问题来源：安装完turtlebot后，把turtlebot环境变量写入bashrc,引起其他工作空间环境变量失效  
## 1.重置bashrc
打开bashrc,删除其余source语句,只保留ros环境变量`source /opt/ros/kinetic/setup.bash`
```bash
gedit ~/.bashrc
```
## 2.建立一个新的工作空间用于管理环境变量
```bash
mkdir -p catkin_overlay_ws/src
cd catkin_overlay_ws/src
catkin_init_workspace
cd ..
catkin_make
```
## 3.修改catkin_overlay_ws/devel目录下的_setup_util.py文件
找到：
```python
if not args.local:
  # environment at generation time
  CMAKE_PREFIX_PATH = '/opt/ros/kinetic'.split(';')
else:
  # don't consider any other prefix path than this one
  CMAKE_PREFIX_PATH = []
```
在CAMKE_PREFIX_PATH后面加上工作空间环境变量，注意顺序：
```python
CMAKE_PREFIX_PATH = '/home/elong/gui_ws/devel;/home/elong/catkin_ws/devel;/home/elong/livox_ws/devel;' \
'/home/elong/turtlebot_ws/turtlebot/devel;/home/elong/turtlebot_ws/kobuki/devel;/home/elong/turtlebot_ws/rocon/devel;' \
'/opt/ros/kinetic'.split(';')
```
重新编译：
```bash
catkin_make
```
## 4.配置bashrc,检查是否生效
打开bashrc,删除ros环境变量，添加catkin_overlay_ws环境变量,修改后只有一行source语句：
```bash
source ~/catkin_overlay_ws/devel/setup.bash
```
检查是环境变量是否全部生效：
```bash
source ~/.bashrc
echo $ROS_PACKAGE_PATH
```
终端输出所有功能包路径
