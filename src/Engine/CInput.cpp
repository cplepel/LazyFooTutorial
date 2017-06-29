#include "CInput.h"
#include "CWindow.h"
//----------------------------------------------------------------------------------------------
Vect2i CInput::GetMousePosition (CWindow& win) {
    return sf::Mouse::getPosition(win.GetSFMLWindow());
}