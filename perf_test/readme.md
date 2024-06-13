# how to use

- 1. 安装 python packages

```bash
pip install pandas
pip install numpy
pip install openpyxl
```

- 2. 将下面代码加入cmake中,参考sample中的cmakelists
```cmake
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};<minitrace_install/share/minitrace_dir>")
find_package(minitrace)
...
target_link_libraries(<your target> minitrace::minitrace)
```

- 3. 代码中添加 trace
```cpp
#include "minitrace.h"
void test_foo()
{
    MTR_SCOPE("c++", "2. b");
    xxx;
}
int main()
{
    // minitrace初始化
    mtr_init("trace.json");
    mtr_register_sigint_handler();

    test_foo();
    ...;

    // minitrace结束
    mtr_flush();
    mtr_shutdown();
    return 0;
}
```

- 4. 运行runner程序，生成trace.json,利用工具tool_report.py 生成report.xlsx

```python
python tool_report.py <trace.json dir>
```
