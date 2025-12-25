//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#define NTR_SINGLETON_IMPL(...)               \
    static NTR_INLINE __VA_ARGS__& instance() \
    {                                         \
        static __VA_ARGS__ _instance {};      \
        return _instance;                     \
    }

#define NTR_DELETE_COPY_MOVE_CONSTRUCTORS(class_name)  \
    class_name(const class_name&) = delete;            \
    class_name(class_name&&) = delete;                 \
    class_name& operator=(const class_name&) = delete; \
    class_name& operator=(class_name&&) = delete;

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <array>
#include <initializer_list>
#include <string_view>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <type_traits>

#if defined(_WIN32)
#    define _ntr_align_alloc(size, alignment) \
        _aligned_malloc(static_cast<size_t>(size), static_cast<size_t>(alignment))
#    define _ntr_align_free(ptr) _aligned_free((ptr))
#else
#    define _ntr_align_alloc(size, alignment) \
        std::aligned_alloc(static_cast<size_t>(alignment), static_cast<size_t>(size))
#    define _ntr_align_free(ptr) std::free((ptr))
#endif

#if defined(__clang__) && defined(__GNUC__)
#    define NTR_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__MINGW32__)
#    define NTR_COMPILER_GCC
#elif defined(_MSC_VER)
#    define NTR_COMPILER_MSVC
#else
#    error "ntr only support clang++, g++ and visual c++"
#endif

#if defined(NTR_COMPILER_CLANG) || defined(NTR_COMPILER_GCC)
#    define NTR_CPP_STANDARD __cplusplus
#elif defined(NTR_COMPILER_MSVC)
#    define NTR_CPP_STANDARD _MSVC_LANG
#endif

#if NTR_CPP_STANDARD < 201703L
#    error "ntr only support cpp's version > c++17"
#endif

#if defined(NTR_COMPILER_CLANG)
#    define NTR_INLINE __inline__ __attribute__((always_inline))
#elif defined(NTR_COMPILER_GCC)
#    define NTR_INLINE __inline__ __attribute__((__always_inline__))
#elif defined(NTR_COMPILER_MSVC)
#    define NTR_INLINE __forceinline
#endif

#if defined(NTR_LIB_EXPORT)
#    if defined(NTR_COMPILER_CLANG)
#        define NTR_API __attribute__((visibility("default")))
#    elif defined(NTR_COMPILER_GCC)
#        if defined(_WIN32)
#            if defined(NTR_BUILDING_LIB)
#                define NTR_API __attribute__((dllexport))
#            else
#                define NTR_API __attribute__((dllimport))
#            endif
#        else
#            define NTR_API __attribute__((visibility("default")))
#        endif
#    elif defined(NTR_COMPILER_MSVC)
#        if defined(NTR_BUILDING_LIB)
#            define NTR_API __declspec(dllexport)
#        else
#            define NTR_API __declspec(dllimport)
#        endif
#    endif
#else
#    define NTR_API
#endif