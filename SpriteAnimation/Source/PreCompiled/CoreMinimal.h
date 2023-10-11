#pragma once
#include <iostream>
#include <string>
#include "SDL2/SDL.h"

typedef std::string REString;



// log to the console
static void RELog(REString Message) {
	std::cout << Message << std::endl;
}