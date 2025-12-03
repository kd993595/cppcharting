#pragma once

#include <array>

namespace chartastic {

enum class ColorPalette{palette1, palette2, palette3};

std::array<Color, 12> p1 = {(Color){131,46,88,255},(Color){162,72,69,255},(Color){172,110,65,255},(Color){101,78,31,255},
                            (Color){103,109,48,255},(Color){87,142,91,255},(Color){38,93,78,255},(Color){48,115,122,255},
                            (Color){68,135,173,255},(Color){46,79,143,255},(Color){110,83,177,255},(Color){169,93,172,255}};
std::array<Color, 12> p2 = {(Color){64,73,135,255},(Color){119,78,161,255},(Color){177,84,159,255},(Color){121,54,73,255},
                            (Color){151,77,60,255},(Color){164,111,58,255},(Color){90,79,38,255},(Color){91,109,53,255},
                            (Color){75,141,98,255},(Color){41,89,83,255},(Color){50,111,125,255},(Color){65,130,180,255}};
std::array<Color, 12> p3 = {(Color){62,60,16,255},(Color){17,66,67,255},(Color){56,40,122,255},(Color){102,27,40,255},
                            (Color){99,75,23,255},(Color){30,91,76,255},(Color){40,74,151,255},(Color){135,33,85,255},
                            (Color){142,87,30,255},(Color){51,117,73,255},(Color){34,107,155,255},(Color){157,47,147,255}};

}
