// Copyright 2013-2023 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://github.com/danielaparker/jsoncons for latest version

#ifndef JSONCONS_ALLOCATOR_STRATEGY_HPP
#define JSONCONS_ALLOCATOR_STRATEGY_HPP

#include <memory>
#include <jsoncons/tag_type.hpp>

namespace jsoncons {

template <class ResultAllocator,class TempAllocator>
class wrapped_allocators
{
    ResultAllocator result_alloc_;
    TempAllocator temp_alloc_;
public:
    using result_allocator_type = ResultAllocator;
    using temp_allocator_type = TempAllocator;

    wrapped_allocators(const ResultAllocator& result_alloc, const TempAllocator& temp_alloc)
        : result_alloc_(result_alloc), temp_alloc_(temp_alloc)
    {
    }

    wrapped_allocators(const wrapped_allocators&)  = default;
    wrapped_allocators(wrapped_allocators&&)  = default;
    wrapped_allocators& operator=(const wrapped_allocators&)  = delete;
    wrapped_allocators& operator=(wrapped_allocators&&)  = delete;
    ~wrapped_allocators() = default;

    ResultAllocator get_result_allocator() const {return result_alloc_;}
    TempAllocator get_temp_allocator() const {return temp_alloc_;}
};

template <class ResultAllocator,class TempAllocator>
wrapped_allocators<ResultAllocator,TempAllocator> wrap_allocators(const ResultAllocator& result_alloc = std::allocator<char>(), 
    const TempAllocator& temp_alloc = std::allocator<char>())
{
    return wrapped_allocators<ResultAllocator,TempAllocator>(result_alloc, temp_alloc);
}

template <class TempAllocator>
wrapped_allocators<std::allocator<char>,TempAllocator> wrap_allocators(temp_allocator_arg_t, 
    const TempAllocator& temp_alloc)
{
    return wrapped_allocators<std::allocator<char>,TempAllocator>(std::allocator<char>(), temp_alloc);
}

} // namespace jsoncons

#endif
