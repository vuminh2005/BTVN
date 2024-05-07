#include "colors.h"

using namespace std;

    const SDL_Color darkGrey {26, 31, 40, 255};
    const SDL_Color green = {47, 230, 23, 255};
    const SDL_Color red = {232, 18, 18, 255};
    const SDL_Color orange = {226, 116, 17, 255};
    const SDL_Color yellow = {237, 234, 4, 255};
    const SDL_Color purple = {166, 0, 247, 255};
    const SDL_Color cyan = {21, 204, 209, 255};
    const SDL_Color blue = {13, 64, 216, 255};
    const SDL_Color lightBlue = {59, 85, 162, 255};
    const SDL_Color darkBlue = {44, 44, 127, 255};
    const SDL_Color white = {255, 255, 255, 255};

vector<SDL_Color> GetCellColors() {
    return {darkGrey, green, red, orange, yellow, purple, cyan, blue};
}
