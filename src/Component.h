#ifndef COMPONENT_H
#define COMPONENT_H
#include "pch.h"

using ComponentType = std::uint8_t;

// Used to define the size of arrays
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

#endif // COMPONENT_H
