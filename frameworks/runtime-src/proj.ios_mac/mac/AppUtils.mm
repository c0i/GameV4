#include "AppUtils.hpp"

#import <Foundation/Foundation.h>
#include <mach-o/dyld.h>

#include "base/CCDirector.h"

std::string getAppPath()
{
    char buf[256] = {0};
    uint32_t size = 256;
    _NSGetExecutablePath(buf, &size);
    std::string exePath(buf);
    std::string appPath = exePath.append("/../../../");
    return appPath;
}

std::string standardizingPath(const std::string& path)
{
    auto ret = [[[NSString stringWithUTF8String:path.c_str()] stringByStandardizingPath] UTF8String];
    return ret;
}

void delayCall(const cocos2d::ccSchedulerFunc& func, float delay)
{
    auto scheduler = cocos2d::Director::getInstance()->getScheduler();
    scheduler->schedule(func, scheduler, 0, 0, delay, false, "__delay_call__");
}
