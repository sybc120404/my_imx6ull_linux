# LED_BSP

本例程讲BSP工程管理，管理led项目

## BSP工程管理原理

BSP工程管理目的是模块化整理代码，相同属性的文件存放在相同目录中

最终文件结构

```
❯ tree
.
├── bsp
│   ├── clk
│   │   ├── bsp_clk.c
│   │   └── bsp_clk.h
│   ├── delay
│   │   ├── bsp_delay.c
│   │   └── bsp_delay.h
│   └── led
│       ├── bsp_led.c
│       └── bsp_led.h
├── imx6ull
│   └── imx6u.h
├── imx6ull.lds
├── imxdownload
├── led.bin
├── led.dis
├── led.elf
├── load.imx
├── Makefile
├── obj
│   ├── bsp_clk.o
│   ├── bsp_delay.o
│   ├── bsp_led.o
│   ├── main.o
│   └── start.o
├── project
│   ├── main.c
│   └── start.s
└── README.md

8 directories, 22 files
```

## 通用测试Makefile编写

Makefile指定头文件搜索路径需要使用`-I`

----

Makefile 中使用了 `patsubst` 函数来处理包含目录列表。让我们逐步解释这条语句：

```makefile
INCLUDES := $(patsubst %, -I%, $(INCDIRS))
```

1. `$(INCDIRS)`：这是一个变量，通常包含多个包含目录的路径，例如 `src/include`、`lib/include` 等。

2. `$(patsubst %, -I%, $(INCDIRS))`：
   - `patsubst` 是Makefile中的一个函数，用于模式替换。
   - `patsubst` 的语法是 `$(patsubst pattern, replacement, text)`，它会在 `text` 中找到所有匹配 `pattern` 的部分，并将它们替换为 `replacement`。
   - 在这个例子中，`pattern` 是 `%`，表示通配符，可以匹配任何字符串。
   - `replacement` 是 `-I%`，表示将匹配的字符串前面加上 `-I`。
   - `text` 是 `$(INCDIRS)`，即包含目录的列表。

3. 结果：
   - `patsubst` 函数会将 `$(INCDIRS)` 中的每个目录前面加上 `-I`，生成一个新的列表。
   - 例如，如果 `$(INCDIRS)` 包含 `src/include` 和 `lib/include`，那么 `$(patsubst %, -I%, $(INCDIRS))` 的结果将是 `-Isrc/include -Ilib/include`。

最终，`INCLUDES` 变量将包含所有包含目录的路径，并且每个路径前面都有一个 `-I`，这通常用于编译器的包含路径选项。

---

这条语句是一个Makefile中的变量定义，用于收集所有源目录中的汇编文件。让我们逐步解析这条语句：

```makefile
SFILES := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s))
```

1. `$(SRCDIRS)`：这是一个变量，通常包含一个或多个源代码目录的路径。例如，它可能包含 `src`、`lib` 等目录。

2. `$(foreach dir, $(SRCDIRS), ...)`：这是Makefile中的一个循环结构。它会遍历 `$(SRCDIRS)` 中的每一个目录，并将当前目录赋值给变量 `dir`。

3. `$(wildcard $(dir)/*.s)`：这是一个通配符函数，用于查找匹配指定模式的文件。在这里，它会查找当前目录 `$(dir)` 中所有扩展名为 `.s` 的文件（通常是汇编文件）。

4. `$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s))`：将上述步骤结合起来，这个表达式会遍历 `$(SRCDIRS)` 中的每一个目录，并收集每个目录中所有的 `.s` 文件。

5. `SFILES := ...`：最终，将所有找到的 `.s` 文件路径赋值给变量 `SFILES`。

总结：这条语句的作用是遍历所有源代码目录，收集其中的所有汇编文件，并将这些文件的路径存储在变量 `SFILES` 中。

---

这行代码是一个Makefile中的变量定义，用于处理C语言源文件的目录和文件名。具体解释如下：

```makefile
CFILENDIR := $(notdir $(CFILES))
```

- `CFILENDIR`：这是一个变量名，用于存储处理后的值。
- `$(CFILES)`：这是另一个变量，假设它包含了一组C语言源文件的路径列表。
- `$(notdir ...)`：这是一个Makefile函数，用于从路径中提取文件名部分，去掉目录部分。

举个例子，如果`$(CFILES)`的值是`src/main.c src/utils.c`，那么`$(notdir $(CFILES))`的结果将是`main.c utils.c`。最终，`CFILENDIR`变量将包含这些文件名。

这个操作通常用于在编译过程中只需要文件名而不需要完整路径的场景。

---

`VPATH` 变量在 Makefile 中用于指定搜索源文件的目录。当你在 Makefile 中使用 `VPATH` 变量时，`make` 工具会在这些目录中查找源文件，而不仅仅是在当前目录中查找。这对于项目中源文件分布在多个目录中的情况非常有用。

---