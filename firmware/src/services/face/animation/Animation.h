#pragma once
#include <stdint.h>

class Animation {
public:
    virtual ~Animation() {}
    virtual void start() = 0;
    virtual void update(uint32_t deltaMs) = 0;
    virtual bool finished() = 0;
    virtual int priority() const { return 0; }
};