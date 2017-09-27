//===------------------------ exception.cpp -------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "exception.hpp"
#include "new.hpp"
#include "typeinfo.hpp"

#ifdef _LIBCPP_BUILDING_HAS_NO_ABI_LIBRARY
#error dd
#endif

#if defined(LIBCXXRT) || defined(LIBCXX_BUILDING_LIBCXXABI) || \
  (defined(__APPLE__) && !defined(_LIBCPP_BUILDING_HAS_NO_ABI_LIBRARY))
  #include <../external/libcxxrt/src/cxxabi.h>
  using namespace __cxxabiv1;
  #define HAVE_DEPENDENT_EH_ABI 1
#endif

#if defined(_LIBCPP_ABI_MICROSOFT)
#include "support/runtime/exception_msvc.ipp"
#include "support/runtime/exception_pointer_msvc.ipp"
#elif defined(_LIBCPPABI_VERSION)
#include "support/runtime/exception_libcxxabi.ipp"
#include "support/runtime/exception_pointer_cxxabi.ipp"
#elif defined(LIBCXXRT)
#include "support/runtime/exception_libcxxrt.ipp"
#include "support/runtime/exception_pointer_cxxabi.ipp"
#elif defined(__GLIBCXX__)
#include "support/runtime/exception_glibcxx.ipp"
#include "support/runtime/exception_pointer_glibcxx.ipp"
#else
#include "support/runtime/exception_fallback.ipp"
#include "support/runtime/exception_pointer_unimplemented.ipp"
#endif
