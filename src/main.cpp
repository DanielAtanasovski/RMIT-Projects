#include <iostream>

#include "./game/MainApp.h"

int main(int argc, char **argv)
{
    App* app = new MainApp("Xtreme Pinball - Daniel Atanasovski", false, 1920, 1080);

    if (app->Init() != 0) {
        std::cout << "APP::INIT::ERROR: Failed to init app" << std::endl;
        return 1;
    }
    app->Run();
    app->Done();

    return 0;
}
