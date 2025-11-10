//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "nephren.hpp"
#include <iostream>

#define NTR_TEST_ASSERT(condition)                                    \
    if (!(condition))                                                 \
    {                                                                 \
        std::cerr << "Test failed at line " << __LINE__ << std::endl; \
        return 1;                                                     \
    }