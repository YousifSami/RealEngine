#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "SDL2/SDL.h"

typedef std::string REString;

template <typename T> 
using TArray = std::vector<T>;

template <typename T>
using TSharedPtr = std::shared_ptr<T>;

template <typename T>
using TSharedArray = TArray<TSharedPtr<T>>;

typedef uint32_t REUint;

typedef uint8_t REUint8;

// replace the standard make shared
template <typename T, typename... Params>
TSharedPtr<T> TMakeShared(Params&&... params) {
	return std::make_shared<T>(std::forward<Params>(params)...);
}


// log to the console
static void RELog(REString Message) {
	std::cout << Message << std::endl;
}


struct REAnimParams {
	REAnimParams(): 
		StartFrame(0), EndFrame(0),
		FrameCount(0),
		FrameWidth(0), FrameHeight(0),
		RowCount(0), Row(0), 
		FrameRate(24.0f) 
	{}
		
		REUint StartFrame, EndFrame;
		REUint FrameCount;
		REUint FrameWidth, FrameHeight;
		REUint RowCount,Row;
		float FrameRate;
};

struct RESpriteParams {
	RESpriteParams():
		Frame(0),
		FrameCount(0),
		FrameWidth(0), FrameHeight(0),
		RowCount(1), Row(0) {}

		REUint Frame;
		REUint FrameCount;
		REUint FrameWidth, FrameHeight;
		REUint RowCount, Row;
};