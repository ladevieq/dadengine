#include "window/window.hpp"

#include <tao/json.hpp>

int main()
{
    DadEngine::Application app =
        DadEngine::Application({ "DadViewer" }, true);

    while(app.GetWindow()->IsOpen()) {
        app.GetWindow()->MessagePump();
    }

    return 0;
}
