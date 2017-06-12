#include "Input.h"
#include "Window.h"
//----------------------------------------------------------------------------------------------
Vect2i Input::GetMousePosition (Window& win) {
    return sf::Mouse::getPosition(win.GetSFMLWindow());
}