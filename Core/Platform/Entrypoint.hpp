#ifndef __PLATFROM_ENTRYPOINT_HPP_
#define	__PLATFROM_ENTRYPOINT_HPP_

#include "../Defines.hpp"

#if defined (WINDOWS)
#define main WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int32 nCmdShow)
#endif


#endif //__PLATFROM_ENTRYPOINT_HPP_