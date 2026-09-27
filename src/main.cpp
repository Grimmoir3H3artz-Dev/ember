#include "Engine/Application.hpp"

#include <iostream>
#include <stdexcept>

int main()
{
    try {
        Ember::Application app;
        return app.run();
    } catch (const std::exception& ex) {
        std::cerr << "Ember fatal: " << ex.what() << '\n';
        return 1;
    }
}
