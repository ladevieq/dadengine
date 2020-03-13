#include "x-window.hpp"

#include <cstdio>
#include <xcb/xcb.h>
#include <xcb/xproto.h>

namespace DadEngine
{
    Window::Window(const char *_windowName, int32_t _width, int32_t _height, bool _fullscreen, bool _veticalSync)
        : m_fullscreen(_fullscreen), m_verticalSync(_veticalSync),
          m_windowName(_windowName)
    {
        int screenNumber = 0;

        // Used to talk with the X server
        m_ptrConnection = xcb_connect(nullptr, &screenNumber);

        const xcb_setup_t *setup = xcb_get_setup(m_ptrConnection);
        xcb_screen_iterator_t screenIterator = xcb_setup_roots_iterator(setup);

        for(size_t i = 0; i < screenNumber; i++) {
            xcb_screen_next(&screenIterator);
        }

        xcb_screen_t* screen = screenIterator.data;

        printf ("\n");
        printf ("Informations of screen %p:\n", screen->root);
        printf ("  width.........: %p\n", screen->width_in_pixels);
        printf ("  height........: %p\n", screen->height_in_pixels);
        printf ("  white pixel...: %p\n", screen->white_pixel);
        printf ("  black pixel...: %p\n", screen->black_pixel);
        printf ("\n");

        xcb_window_t window = xcb_generate_id(m_ptrConnection);
        xcb_create_window(
            m_ptrConnection,
            XCB_COPY_FROM_PARENT,
            window,
            screen->root,
            0,
            0,
            800,
            600,
            10,
            XCB_WINDOW_CLASS_INPUT_OUTPUT,
            screen->root_visual,
            0,
            nullptr
        );

        xcb_map_window(m_ptrConnection, window);

        xcb_gcontext_t context = xcb_generate_id(m_ptrConnection);
        uint32_t values[] = { screen->white_pixel };

        xcb_create_gc(
            m_ptrConnection,
            context,
            window,
            XCB_GC_FOREGROUND,
            values
        );

        xcb_flush(m_ptrConnection);

        m_isOpen = true;
    }

    Window::~Window() {
        xcb_disconnect(m_ptrConnection);
    }
}
