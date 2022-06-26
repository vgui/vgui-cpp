# vgui
vgui - C++ crossplatform Vector Graphics User Interface library.

### Building
CMake and GCC is preferred toolchain now.
vgui uses only one submodule - https://github.com/Crascit/DownloadProject.git
All other libraries downloads by this library from GitHub to external folder.
That allow do not increase size of .git folder and project folder.
Possible build problems:
1.Git no in PATH. Git used to download projects from GitHub.
2.Try git submodule update --init for cmake/DownloadProject.
3.Try change CMake generator. On Windows with CMakeLists.txt 
from agg directory ninja don't work. Change ninja to MSYS Makefile and all will OK.
4.Edit cmake/dependencies.cmake file.

### Testing
Use Google Testing framework.

### Style of code
Use C++17 as much as possible.

|Item    |  Convension|
| -------- | ------------ |
|Types   |CamelCase   |
|Enum constants|CamelCase|
|Constants in types      |CamelCase|
|Macroses                |UPPER_SNAKE_CASE|
|Functions    |CamelCase|
|Methods      |CamelCase|
|Private member variables|m_prefixed|
|Private static variables|s_prefixed|
|Local variables         |noprefixed|
|Namespaces              | If possible use short lower case name: vgui, detail...|

#### Special cases
>`std::` dependent types( like `std::vector::iterator`) written as is:
```
using iterator = typename std::vector<T>::iterator;
```

#### Special special cases
Often used atomic types and fucntions write in lower case.

#### Doxigen documenation
Self-documenting comments in the form of:
```
/**
    Some method
    @param arg
    @return ret
*/
bool SomeMethod(int arg)
{
  return true;
}
```
>'@' sign is more distinct

Try writing self documenting code. Less comments - less maintaining.
