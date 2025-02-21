#pragma once
#include <LLAPI.h>

// 版本记录
#define LXL_VERSION_MAJOR 0
#define LXL_VERSION_MINOR 5
#define LXL_VERSION_REVISION 10

#define LXL_VERSION_STATUS Beta
#define LXL_VERSION_STATUS_STRING "Beta"

#define LXL_VERSION LL::Version(LXL_VERSION_MAJOR, LXL_VERSION_MINOR, LXL_VERSION_REVISION, LL::Version::Status::LXL_VERSION_STATUS)