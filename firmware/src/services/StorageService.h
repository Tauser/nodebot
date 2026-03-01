#pragma once
#include "drivers/StorageDriver.h"

class StorageService {
public:
    void init();
    bool isReady() const;

private:
    StorageDriver _driver;
    bool _isMounted;
};