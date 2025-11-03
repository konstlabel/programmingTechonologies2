#include "Libraries.h"

using namespace Menus;

int main()
{
    char choice = validChoice('0', '2', startMenu);
    switch (choice) {
    case '1': SignProject();
    case '2':
    default:
        return 0;
    }
}