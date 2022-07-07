#pragma once

//std::
#include <cassert>
#include <cmath>
#include <iomanip>
#include <limits>
#include <type_traits>
#include <initializer_list>
#include <algorithm>
#include <string>
#include <string_view>
#include <cstring>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <memory>
#include <optional>

#include <cairomm/cairomm.h>
#include <cairomm/win32_surface.h>

#ifdef _WIN32
#include <windows.h>
#include <wingdi.h>
#include <dwmapi.h>
#endif//_WIN32
