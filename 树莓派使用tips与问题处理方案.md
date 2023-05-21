## 树莓派~~初始使用流程与~~问题处理方案

#### 初始使用流程

1. 给sd卡烧录系统时用官方imager烧录，在初始界面就在settings里把ssh、wifi连接、账号密码之类都预设上

2. 找树莓派ip：cmd里ping raspberrypi.local（√）
   
   手机上下载terminal emulator，使用ip neigh（√）
   
   cmd里arp -a，在一堆ip里肉眼找（×）
   
   我的ip是192.168.151.194

3. putty里输入树莓派ip以连接，输入用户名、密码，连接成功
   
   我的用户名是9，密码为12345

4. 换源（ [中科大源](https://blog.csdn.net/weixin_44908159/article/details/107441657?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522168240806116800215092382%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=168240806116800215092382&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-1-107441657-null-null.142%5Ev86%5Einsert_down1,239%5Ev2%5Einsert_chatgpt&utm_term=%E6%A0%91%E8%8E%93%E6%B4%BE%E6%8D%A2%E4%B8%AD%E7%A7%91%E5%A4%A7%E6%BA%90&spm=1018.2226.3001.4187)）([清华源](https://blog.csdn.net/weixin_45469072/article/details/124054729))
   
   换清华源时可能有公钥问题，把所有公钥都在终端"sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 公钥"一遍即可。

5. 使用远程桌面或者vnc viewer连接操作树莓派，则：
   
   （1）在树莓派上sudo apt-get install xrtp成功，可使用远程桌面连接
   
   （2）树莓派上输入sudo raspi-config，然后Interface Options----VNC----yes把vnc 服务打开。输入vncserver找到树莓派的新ip，可使用vnc连接

#### 问题与解决方案

- 在step1，没有在初始界面预设，只能手动添加ssh、wpa_supplicant.conf、userconf.txt，但还每次开关机这些文件就被清除，我添加了十几次也没有成功。

        solution：都预设好重新烧录。

- step2，树莓派ip莫名其妙改变
  
  solution：cmd里ipconfig找到倒数第三个ip，把树莓派地址第三个改成这个ip的第三个。我的从151->253

- 在step3，因为烧录系统时没有预设用户名密码，我就一直access denied。

        solution：用raspberrypi imager重新烧录了两次，才成功登录。

- 在step4(1)一直error，尝试换镜像源，但在换源后的sudo apt-get update时也全是error。
  
  solution：最后发现问题是树莓派连接的是电脑热点，而我的电脑热点是坏的，没法连接上网络。让电脑和树莓派都连接手机热点就换源成功了。

- step4(1)在树莓派连接上网络后，install xrdp一直都是E:unable to locate xrdp。solution：未知。我把网上所有可能方法都试了也没成功，最后是在一次重启后莫名其妙成功的。在换新的sd卡之后还是出现这个问题，但没有莫名其妙的成功了。

- step5远程连接上树莓派后，桌面上没有顶部工具栏，只有一个回收站。
  
  solution：终端里执行 rm -rf /home/9/*.*/ 然后重启系统就好了

- 远程桌面连接是蓝屏
  
  solution：上网一搜就解决([解决远程登录蓝屏](https://blog.csdn.net/u011983700/article/details/128330740?ops_request_misc=&request_id=&biz_id=102&utm_term=%E6%A0%91%E8%8E%93%E6%B4%BE%E8%BF%9C%E7%A8%8B%E6%A1%8C%E9%9D%A2%E8%BF%9E%E6%8E%A5%E8%93%9D%E5%B1%8F&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~sobaiduweb~default-0-128330740.142^v86^insert_down1,239^v2^insert_chatgpt&spm=1018.2226.3001.4450))

- 远程连接树莓派每次都出现no session for pid xxxx。
  
  solution：未知。但是似乎没有什么影响。

#### 需要安装的库

- 安装wiringpi：
  
  git clone git://git.drogon.net/wiringPi
  cd wiringPi
  ./build

- 安装python：sudo apt-get install python-dev

- 安装xrdp：sudo apt-get install xrdp

#### 常用指令

1. 查看全部编码：gpio readall

2. 查看板载编码：pinout

3. 关机：(1)sudo -s (2)halt
   
   sudo poweroff 关闭电源
   sudo shutdown -h now 立即关机
   sudo shutdown -r now 立即重启
   sudo reboot 重启

4. 运行代码：(1)gcc -o 文件名 文件名.c -lwiringPi (2)sudo ./文件名

5. 查看串口情况：ls /dev -al

6. 编译运行C代码：先cd到路径，再写：gcc -o 文件名 文件名.c -lwiringPi，之后可以./ 文件名 函数名
   
   例：运行放在桌面上的main.c，先cd Desktop,再gcc -o main main.c -lwiringPi，再./main front
   
   例：gcc avoid.c -o avoid -lwiringPi -lpthread
   
   ./avoid

7. 编译运行python代码：先cd到路径，再写：python3 文件名.py
   
   代码后台运行：nohup python3 文件名.py &
   
   例：运行放在桌面上的main.py，先cd Desktop,再python3 main.py

8. fn+F12进入开发者模式调试网页
