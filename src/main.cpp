#include <iostream>
#include <concepts>

#include <SFML/Graphics.hpp>

#include "Controller/Application.h"

using namespace gd;

int main()
{
    Application::getInstance()->execute();
    //app.execute();
}
