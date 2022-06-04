TEMPLATE = subdirs
#定义了ordered表示子项目按照添加的顺序来编译
CONFIG  += ordered
SUBDIRS += designer
SUBDIRS += demo
SUBDIRS += examples

#下面是另外一种指定编译依赖顺序的方法
#examples项目依赖designer项目 要求designer项目先编译完生成动态库文件 examples项目需要去链接这个文件
#examples.depends = designer
