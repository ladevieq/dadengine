#ifndef __PLATFROM_ENTRYPOINT_HPP_
#define	__PLATFROM_ENTRYPOINT_HPP_


#if defined (WINDOWS)
#define main WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int32_t nCmdShow)
#endif


#endif //__PLATFROM_ENTRYPOINT_HPP_