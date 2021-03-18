#ifndef AppUtils_hpp
#define AppUtils_hpp

#include <string>
#include <functional>

#include "base/CCScheduler.h"

std::string getAppPath();
std::string standardizingPath(const std::string& path);
void delayCall(const cocos2d::ccSchedulerFunc& func, float delay = 1.0f /* seconds */);

#endif /* AppUtils_hpp */
