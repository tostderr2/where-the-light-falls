#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>




// fixme: add correct checks and add the declspec
// and this should be in some other place, platform.h maybe

#ifndef CORE_API

#if (MSVC)
#define CORE_API
#else
#define CORE_API
#endif
#endif
