# 不紊 -- 一个c++的命令行小工具，按时间自动整理图片。
## 这是干什么的
我觉得这个问题一个演示就能说明：
![demo](https://i.loli.net/2019/11/02/yQmSlLchnrJGitU.gif)

这个工具的来源是我的相机存了好多照片，虽然定期都是备份到移动硬盘中，但是随着时间的推移，照片越来越多，在一次想回顾往事的过程中我发现我已经不能愉快的浏览了。我就想到，如果能够按照时间分类一下这些照片，会帮助我更加高效的配合我的回忆。

其实这种现成的工具有很多，但是我这个小小的功能实在是不想去下载一个软件。而我有幸在我的大学的时候，因为所做的项目而真的较为深入的了解过Exif的知识，而相机里面的文件主要都是jpeg格式的，所以，我觉得撸起袖子试一试。 

在选择语言的方面，我在思考后使用c++来做这个事情，主要原因是两个。一是因为如果用类似python这样的语言来实在是太简单了，随便调个库，调个函数就好了。而我有幸知道Exif的原理，加上使用c++可以也算多少对得起好歹我是写程序这个职业。二是因为我的照片有点多，而我想用树莓派来做这件事情，用python真的是太慢了，而用c++，虽然代码量上去了，但是速度真的是嗖嗖的变快。

## 无脑使用指南
首先，build这个程序都不需要makefile：
```
g++ --std=c++11 ./main.cpp ./cmdline.h core/* 
```
最后会得到一个a.out的程序，当然如果你需要改变生成程序的名字，可以用-o参数。

然后就是使用了，感谢[这个](https://github.com/tanakh/cmdline)c++命令行程序，让我简单而又快速的生成了优雅的命令行程序。
```
usage: ./a.out --source=string --destination=string [options] ...
options:
  -s, --source         source folder for the pictures that needs to be arranged. (string)
  -d, --destination    destination folder for the pictures that has been arranged. (string)
  -c, --choice         1.By Date, 2.By Month, 3.By Year (int [=1])
  -?, --help           print this message
```
按照这个帮助提示，以下的代码就可以运行程序：
```
./a.out -s "test" -d "test" 
```
