#include <Framework.h>
#include "Game.h"

class App : public Application
{
public:
    App()
    {
        PushLayer<Game>();
    }
};

auto main() -> int
{
    auto app = MakeScoped<App>();
    app->Run();
}