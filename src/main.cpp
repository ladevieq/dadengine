#include "window/window.hpp"

#include <nlohmann/json.hpp>

int main()
{
    DadEngine::Application app =
        DadEngine::Application({ "DadViewer" }, true);

    while(app.GetWindow()->IsOpen()) {
        app.GetWindow()->MessagePump();
    }

    return 0;
}
