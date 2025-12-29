//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "nephren.hpp"
#include <iostream>
#include <sstream>

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

#define NTR_TEST_THROW(condition)                                  \
    do                                                             \
    {                                                              \
        if (!(condition))                                          \
        {                                                          \
            std::stringstream ss;                                  \
            ss << "Test failed at " << __FILE__ << ":" << __LINE__ \
               << " (" #condition ")" << std::endl;                \
            throw std::runtime_error(ss.str());                    \
        }                                                          \
    } while (0)