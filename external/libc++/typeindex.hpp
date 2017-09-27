// -*- C++ -*-
//===-------------------------- typeindex ---------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_TYPEINDEX
#define _LIBCPP_TYPEINDEX

/*

    typeindex synopsis

namespace std
{

class type_index
{
public:
    type_index(const type_info& rhs) noexcept;

    bool operator==(const type_index& rhs) const noexcept;
    bool operator!=(const type_index& rhs) const noexcept;
    bool operator< (const type_index& rhs) const noexcept;
    bool operator<=(const type_index& rhs) const noexcept;
    bool operator> (const type_index& rhs) const noexcept;
    bool operator>=(const type_index& rhs) const noexcept;

    size_t hash_code() const noexcept;
    const char* name() const noexcept;
};

template <>
struct hash<type_index>
    : public unary_function<type_index, size_t>
{
    size_t operator()(type_index index) const noexcept;
};

}  // std

*/

#include <__config.hpp>
#include <typeinfo.hpp>
#include <__functional_base.hpp>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

class _LIBCPP_TEMPLATE_VIS type_index
{
    const type_info* __t_;
public:
    _LIBCPP_INLINE_VISIBILITY
    type_index(const type_info& __y) _NOEXCEPT : __t_(&__y) {}

    _LIBCPP_INLINE_VISIBILITY
    bool operator==(const type_index& __y) const _NOEXCEPT
        {return *__t_ == *__y.__t_;}
    _LIBCPP_INLINE_VISIBILITY
    bool operator!=(const type_index& __y) const _NOEXCEPT
        {return *__t_ != *__y.__t_;}
    _LIBCPP_INLINE_VISIBILITY
    bool operator< (const type_index& __y) const _NOEXCEPT
        {return  __t_->before(*__y.__t_);}
    _LIBCPP_INLINE_VISIBILITY
    bool operator<=(const type_index& __y) const _NOEXCEPT
        {return !__y.__t_->before(*__t_);}
    _LIBCPP_INLINE_VISIBILITY
    bool operator> (const type_index& __y) const _NOEXCEPT
        {return  __y.__t_->before(*__t_);}
    _LIBCPP_INLINE_VISIBILITY
    bool operator>=(const type_index& __y) const _NOEXCEPT
        {return !__t_->before(*__y.__t_);}

    _LIBCPP_INLINE_VISIBILITY
    size_t hash_code() const _NOEXCEPT {return __t_->hash_code();}
    _LIBCPP_INLINE_VISIBILITY
    const char* name() const _NOEXCEPT {return __t_->name();}
};

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS hash;

template <>
struct _LIBCPP_TEMPLATE_VIS hash<type_index>
    : public unary_function<type_index, size_t>
{
    _LIBCPP_INLINE_VISIBILITY
    size_t operator()(type_index __index) const _NOEXCEPT
        {return __index.hash_code();}
};

_LIBCPP_END_NAMESPACE_STD

#endif  // _LIBCPP_TYPEINDEX
