# Makefile

Makefile 是一个用于自动化构建过程的文件，通常用于编译和链接程序。它定义了一系列的规则和依赖关系，告诉 make 工具如何生成目标文件。Makefile 通常包含以下部分：

变量定义：用于简化和复用。
目标和依赖关系：定义了如何生成目标文件。
命令：在目标和依赖关系满足时执行的命令。

## Makefile规则格式

Makefile由一系列规则组成，格式如下：
```
target ... : dependency ...
    cmd1
    cmd2
    ...
```
- cmd列表中每条命令都必须TAB，不能空格！！！
例如：
```
main : main.o input.o calcu.o
    gcc -o main main.o input.o calcu.o
```
目标是生成`main`，生成它的依赖文件是`main.o`，`input.o`和`calcu.o`
如果要更新目标`main`，就必须先更新依赖文件；如果任意一个依赖文件有更新，目标也需要更新
更新的方式就是执行一遍规则中的命令列表

---
看以下例子
```
main: main.o input.o calcu.o
    gcc -o main main.o input.o calcu.o

main.o: main.c
    gcc -c main.c

input.o: input.c
    gcc -c input.c

calcu.o: calcu.c
    gcc -c calcu.c

clean:
    rm *.o
    rm main
```

- 第一条规则中的目标`main`为默认目标，检查到依赖文件不存在时，就继续查找以这个几个文件为目标的规则执行
- 最后一个规则目标是`clean`，没有依赖文件，因此会默认依赖文件都是最新，无需更新执行命令
- 想要执行`clean`，输入命令`make clean`即可，一般用于工程的清理
- 除了默认目标，也就是第一个规则的目标，其余的规则顺序无影响

---

## Makefile变量

Makefile也支持变量，例如

```
objs = main.o input.o calcu.o

main : $(objs)
    gcc -o main $(objs)
```

可以看到，使用`=`进行变量赋值，`$()`进行变量引用

赋值符共有三种，区别如下

- `=`：变量的值等于它的最后一次有效值
- `:=`：变量的值等于前面定义好的值
- `?=`：如果变量前面没有赋值，那就赋值，否则就是用之前的

看以下例子：

[example](./Makefile)
```
name1 = csy
curName1 = $(name1)
name1 = caishanyu

name2 = csy
curName2 := $(name2)
name2 = caishanyu

name3 = csy
curName3 ?= $(name3)

curName4 ?= caishanyu

print:
	@echo curName1: $(curName1)
	@echo curName2: $(curName2)
	@echo curName3: $(curName3)
	@echo curName4: $(curName4)
```
`make printf`结果如下
![makefile](https://github.com/sybc120404/image4md/blob/main/makefile.png)

此外，变量追加可以使用`+=`，用法和C语言一致

## Makefile模式规则

使用`%`进行模式匹配，例如`%.c`表示所有的.c文件，区别于通配符`*`，他是一个一个指定的

## Makefile自动化变量

![autoVal](https://github.com/sybc120404/image4md/blob/main/autoVal.png)

## Makefile伪目标

一般的目标名都是要生成的文件，而伪目标不代表真正的变量吗，在执行`make`命令时通过指定这个伪目标来执行所在规则定义的命令
伪目标主要是避免`Makefile`中定义的目标和工作目录下的实际文件出现冲突
例如`clean`，

```
clean:
    rm *.o
    rm main
```

如果工作目录下有一个`clean`文件，那么他被视作目标，没有依赖文件，所有认为依赖没有更新，也就不会执行下面的命令
此时我们可以将`clean`声明为伪目标
```
.PHONY : clean
```
之后无论是否存在`clean`文件，都会执行命令

