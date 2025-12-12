//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "nephren.hpp"
#include <iostream>

#define NTR_TEST_ASSERT(condition)                                        \
    do                                                                    \
    {                                                                     \
        if (!(condition))                                                 \
        {                                                                 \
            std::cerr << "Test failed at " << __FILE__ << ":" << __LINE__ \
                      << " (" #condition ")" << std::endl;                \
            return 1;                                                     \
        }                                                                 \
    } while (0)