#ifndef __PLATEFORM_FILE_HPP_
#define __PLATEFORM_FILE_HPP_

#include "../Defines.hpp"

#if defined (WINDOWS)
#include "Windows/WindowsTextFileIO.hpp"
#include "Windows/WindowsBinaryFileIO.hpp"
#include "Windows/WindowsFileSystem.hpp"
#endif

#endif //__PLATEFORM_FILE_HPP_