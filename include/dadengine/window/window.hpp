#pragma once

#if defined(_WIN32) || defined(_WIN64)
#include "windows-window.hpp"
#elif defined(__linux__)
#include "x-window.hpp"
#endif

#include "application.hpp"
