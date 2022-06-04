#下面负责自动将插件生成的动态库拷贝到对应的插件目录
#这里限定release版本
#因为Qt安装目录下的可执行文件都是release的包括QtCreator
#切记如果拷贝到QtCreator插件目录则必须保持该QtCreator的 版本+位数+编译器 都必须一致才行
#否则就算拷贝了也没用无法加载
CONFIG(release, debug|release) {
#widnows系统
win32 {
src_file = $$PWD/../bin/quc.dll
#拷贝到Qt插件目录
dst_file = $(QTDIR)/plugins/designer
#拷贝到QtCreator插件目录
dst_file2 = $(QTDIR)/../../Tools/QtCreator/bin/plugins/designer

#转换斜杠 / 到 \\
src_file ~= s,/,\\,g
dst_file ~= s,/,\\,g
dst_file2 ~= s,/,\\,g
#多个执行指令用 && 连接
QMAKE_POST_LINK += copy $$src_file $$dst_file && copy $$src_file $$dst_file2
}

#unix系统
unix {
#拷贝到QtCreator插件目录 linux和macos对应的QtCreator在不同的位置
!macx {
dst_file2 = $(QTDIR)/../../Tools/QtCreator/lib/Qt/plugins/designer
} else {
dst_file2 = $(QTDIR)/../../Qt\ Creator.app/Contents/PlugIns/designer
}

#linux+mac系统可能有链接文件需要全部一起拷贝
src_file = $$PWD/../bin/libquc*
#拷贝到Qt插件目录
dst_file = $(QTDIR)/plugins/designer
#多个执行指令用 && 连接
QMAKE_POST_LINK += cp -r -f $$src_file $$dst_file && cp -r -f $$src_file $$dst_file2
}
}
