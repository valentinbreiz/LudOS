// -*- C++ -*-
//===------------------------------ variant -------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_VARIANT
#define _LIBCPP_VARIANT

#include <__config.hpp>
#include <__tuple.hpp>
#include <array.hpp>
#include <exception.hpp>
#include <functional.hpp>
#include <initializer_list.hpp>
#include <new.hpp>
#include <tuple.hpp>
#include <type_traits.hpp>
#include <utility.hpp>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

namespace std { // explicitly not using versioning namespace

class _LIBCPP_EXCEPTION_ABI bad_variant_access : public exception {
public:
  virtual const char* what() const _NOEXCEPT;
};

} // namespace std

_LIBCPP_BEGIN_NAMESPACE_STD

#if _LIBCPP_STD_VER > 14

_LIBCPP_NORETURN
inline _LIBCPP_INLINE_VISIBILITY
void __throw_bad_variant_access() {
#ifndef _LIBCPP_NO_EXCEPTIONS
        throw bad_variant_access();
#else
        abort();
#endif
}

template <class... _Types>
class _LIBCPP_TEMPLATE_VIS variant;

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS variant_size;

template <class _Tp>
constexpr size_t variant_size_v = variant_size<_Tp>::value;

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS variant_size<const _Tp> : variant_size<_Tp> {};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS variant_size<volatile _Tp> : variant_size<_Tp> {};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS variant_size<const volatile _Tp>
    : variant_size<_Tp> {};

template <class... _Types>
struct _LIBCPP_TEMPLATE_VIS variant_size<variant<_Types...>>
    : integral_constant<size_t, sizeof...(_Types)> {};

template <size_t _Ip, class _Tp>
struct _LIBCPP_TEMPLATE_VIS variant_alternative;

template <size_t _Ip, class _Tp>
using variant_alternative_t = typename variant_alternative<_Ip, _Tp>::type;

template <size_t _Ip, class _Tp>
struct _LIBCPP_TEMPLATE_VIS variant_alternative<_Ip, const _Tp>
    : add_const<variant_alternative_t<_Ip, _Tp>> {};

template <size_t _Ip, class _Tp>
struct _LIBCPP_TEMPLATE_VIS variant_alternative<_Ip, volatile _Tp>
    : add_volatile<variant_alternative_t<_Ip, _Tp>> {};

template <size_t _Ip, class _Tp>
struct _LIBCPP_TEMPLATE_VIS variant_alternative<_Ip, const volatile _Tp>
    : add_cv<variant_alternative_t<_Ip, _Tp>> {};

template <size_t _Ip, class... _Types>
struct _LIBCPP_TEMPLATE_VIS variant_alternative<_Ip, variant<_Types...>> {
  static_assert(_Ip < sizeof...(_Types), "Index out of bounds in std::variant_alternative<>");
  using type = __type_pack_element<_Ip, _Types...>;
};

constexpr size_t variant_npos = static_cast<size_t>(-1);
constexpr unsigned int __variant_npos = static_cast<unsigned int>(-1);

namespace __find_detail {

template <class _Tp, class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr size_t __find_index() {
  constexpr bool __matches[] = {is_same_v<_Tp, _Types>...};
  size_t __result = __not_found;
  for (size_t __i = 0; __i < sizeof...(_Types); ++__i) {
    if (__matches[__i]) {
      if (__result != __not_found) {
        return __ambiguous;
      }
      __result = __i;
    }
  }
  return __result;
}

template <size_t _Index>
struct __find_unambiguous_index_sfinae_impl
    : integral_constant<size_t, _Index> {};

template <>
struct __find_unambiguous_index_sfinae_impl<__not_found> {};

template <>
struct __find_unambiguous_index_sfinae_impl<__ambiguous> {};

template <class _Tp, class... _Types>
struct __find_unambiguous_index_sfinae
    : __find_unambiguous_index_sfinae_impl<__find_index<_Tp, _Types...>()> {};

} // namespace __find_detail

namespace __variant_detail {

struct __valueless_t {};

enum class _Trait { _TriviallyAvailable, _Available, _Unavailable };

template <typename _Tp,
          template <typename> class _IsTriviallyAvailable,
          template <typename> class _IsAvailable>
constexpr _Trait __trait =
    _IsTriviallyAvailable<_Tp>::value
        ? _Trait::_TriviallyAvailable
        : _IsAvailable<_Tp>::value ? _Trait::_Available : _Trait::_Unavailable;

inline _LIBCPP_INLINE_VISIBILITY
constexpr _Trait __common_trait(initializer_list<_Trait> __traits) {
  _Trait __result = _Trait::_TriviallyAvailable;
  for (_Trait __t : __traits) {
    if (static_cast<int>(__t) > static_cast<int>(__result)) {
      __result = __t;
    }
  }
  return __result;
}

template <typename... _Types>
struct __traits {
  static constexpr _Trait __copy_constructible_trait =
      __common_trait({__trait<_Types,
                              is_trivially_copy_constructible,
                              is_copy_constructible>...});

  static constexpr _Trait __move_constructible_trait =
      __common_trait({__trait<_Types,
                              is_trivially_move_constructible,
                              is_move_constructible>...});

  static constexpr _Trait __copy_assignable_trait = __common_trait(
      {__copy_constructible_trait,
       __trait<_Types, is_trivially_copy_assignable, is_copy_assignable>...});

  static constexpr _Trait __move_assignable_trait = __common_trait(
      {__move_constructible_trait,
       __trait<_Types, is_trivially_move_assignable, is_move_assignable>...});

  static constexpr _Trait __destructible_trait = __common_trait(
      {__trait<_Types, is_trivially_destructible, is_destructible>...});
};

namespace __access {

struct __union {
  template <class _Vp>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr auto&& __get_alt(_Vp&& __v, in_place_index_t<0>) {
    return _VSTD::forward<_Vp>(__v).__head;
  }

  template <class _Vp, size_t _Ip>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr auto&& __get_alt(_Vp&& __v, in_place_index_t<_Ip>) {
    return __get_alt(_VSTD::forward<_Vp>(__v).__tail, in_place_index<_Ip - 1>);
  }
};

struct __base {
  template <size_t _Ip, class _Vp>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr auto&& __get_alt(_Vp&& __v) {
    return __union::__get_alt(_VSTD::forward<_Vp>(__v).__data,
                              in_place_index<_Ip>);
  }
};

struct __variant {
  template <size_t _Ip, class _Vp>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr auto&& __get_alt(_Vp&& __v) {
    return __base::__get_alt<_Ip>(_VSTD::forward<_Vp>(__v).__impl);
  }
};

} // namespace __access

namespace __visitation {

struct __base {
  template <class _Visitor, class... _Vs>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr decltype(auto)
  __visit_alt_at(size_t __index, _Visitor&& __visitor, _Vs&&... __vs) {
    constexpr auto __fdiagonal =
        __make_fdiagonal<_Visitor&&,
                         decltype(_VSTD::forward<_Vs>(__vs).__as_base())...>();
    return __fdiagonal[__index](_VSTD::forward<_Visitor>(__visitor),
                                _VSTD::forward<_Vs>(__vs).__as_base()...);
  }

  template <class _Visitor, class... _Vs>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr decltype(auto) __visit_alt(_Visitor&& __visitor,
                                              _Vs&&... __vs) {
    constexpr auto __fmatrix =
        __make_fmatrix<_Visitor&&,
                       decltype(_VSTD::forward<_Vs>(__vs).__as_base())...>();
    return __at(__fmatrix, __vs.index()...)(
        _VSTD::forward<_Visitor>(__visitor),
        _VSTD::forward<_Vs>(__vs).__as_base()...);
  }

private:
  template <class _Tp>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr const _Tp& __at(const _Tp& __elem) { return __elem; }

  template <class _Tp, size_t _Np, typename... _Indices>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr auto&& __at(const array<_Tp, _Np>& __elems,
                               size_t __index, _Indices... __indices) {
    return __at(__elems[__index], __indices...);
  }

  template <class _Fp, class... _Fs>
  static constexpr void __std_visit_visitor_return_type_check() {
    static_assert(
        __all<is_same_v<_Fp, _Fs>...>::value,
        "`std::visit` requires the visitor to have a single return type.");
  }

  template <class... _Fs>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr auto __make_farray(_Fs&&... __fs) {
    __std_visit_visitor_return_type_check<decay_t<_Fs>...>();
    using __result = array<common_type_t<decay_t<_Fs>...>, sizeof...(_Fs)>;
    return __result{{_VSTD::forward<_Fs>(__fs)...}};
  }

  template <size_t... _Is>
  struct __dispatcher {
    template <class _Fp, class... _Vs>
    inline _LIBCPP_INLINE_VISIBILITY
    static constexpr decltype(auto) __dispatch(_Fp __f, _Vs... __vs) {
        return __invoke_constexpr(
            static_cast<_Fp>(__f),
            __access::__base::__get_alt<_Is>(static_cast<_Vs>(__vs))...);
    }
  };

  template <class _Fp, class... _Vs, size_t... _Is>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr auto __make_dispatch(index_sequence<_Is...>) {
    return __dispatcher<_Is...>::template __dispatch<_Fp, _Vs...>;
  }

  template <size_t _Ip, class _Fp, class... _Vs>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr auto __make_fdiagonal_impl() {
    return __make_dispatch<_Fp, _Vs...>(
        index_sequence<(__identity<_Vs>{}, _Ip)...>{});
  }

  template <class _Fp, class... _Vs, size_t... _Is>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr auto __make_fdiagonal_impl(index_sequence<_Is...>) {
    return __base::__make_farray(__make_fdiagonal_impl<_Is, _Fp, _Vs...>()...);
  }

  template <class _Fp, class _Vp, class... _Vs>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr auto __make_fdiagonal() {
    constexpr size_t _Np = decay_t<_Vp>::__size();
    static_assert(__all<(_Np == decay_t<_Vs>::__size())...>::value);
    return __make_fdiagonal_impl<_Fp, _Vp, _Vs...>(make_index_sequence<_Np>{});
  }

  template <class _Fp, class... _Vs, size_t... _Is>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr auto __make_fmatrix_impl(index_sequence<_Is...> __is) {
    return __make_dispatch<_Fp, _Vs...>(__is);
  }

  template <class _Fp, class... _Vs, size_t... _Is, size_t... _Js, class... _Ls>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr auto __make_fmatrix_impl(index_sequence<_Is...>,
                                            index_sequence<_Js...>,
                                            _Ls... __ls) {
    return __base::__make_farray(__make_fmatrix_impl<_Fp, _Vs...>(
        index_sequence<_Is..., _Js>{}, __ls...)...);
  }

  template <class _Fp, class... _Vs>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr auto __make_fmatrix() {
    return __make_fmatrix_impl<_Fp, _Vs...>(
        index_sequence<>{}, make_index_sequence<decay_t<_Vs>::__size()>{}...);
  }
};

struct __variant {
  template <class _Visitor, class... _Vs>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr decltype(auto)
  __visit_alt_at(size_t __index, _Visitor&& __visitor, _Vs&&... __vs) {
    return __base::__visit_alt_at(__index,
                                  _VSTD::forward<_Visitor>(__visitor),
                                  _VSTD::forward<_Vs>(__vs).__impl...);
  }

  template <class _Visitor, class... _Vs>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr decltype(auto) __visit_alt(_Visitor&& __visitor,
                                              _Vs&&... __vs) {
    return __base::__visit_alt(_VSTD::forward<_Visitor>(__visitor),
                               _VSTD::forward<_Vs>(__vs).__impl...);
  }

  template <class _Visitor, class... _Vs>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr decltype(auto)
  __visit_value_at(size_t __index, _Visitor&& __visitor, _Vs&&... __vs) {
    return __visit_alt_at(
        __index,
        __make_value_visitor(_VSTD::forward<_Visitor>(__visitor)),
        _VSTD::forward<_Vs>(__vs)...);
  }

  template <class _Visitor, class... _Vs>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr decltype(auto) __visit_value(_Visitor&& __visitor,
                                                _Vs&&... __vs) {
    return __visit_alt(
        __make_value_visitor(_VSTD::forward<_Visitor>(__visitor)),
        _VSTD::forward<_Vs>(__vs)...);
  }

private:
  template <class _Visitor, class... _Values>
  static constexpr void __std_visit_exhaustive_visitor_check() {
    static_assert(is_callable_v<_Visitor(_Values...)>,
                  "`std::visit` requires the visitor to be exhaustive.");
  }

  template <class _Visitor>
  struct __value_visitor {
    template <class... _Alts>
    inline _LIBCPP_INLINE_VISIBILITY
    constexpr decltype(auto) operator()(_Alts&&... __alts) const {
      __std_visit_exhaustive_visitor_check<
          _Visitor,
          decltype((_VSTD::forward<_Alts>(__alts).__value))...>();
      return __invoke_constexpr(_VSTD::forward<_Visitor>(__visitor),
                                _VSTD::forward<_Alts>(__alts).__value...);
    }
    _Visitor&& __visitor;
  };

  template <class _Visitor>
  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr auto __make_value_visitor(_Visitor&& __visitor) {
    return __value_visitor<_Visitor>{_VSTD::forward<_Visitor>(__visitor)};
  }
};

} // namespace __visitation

template <size_t _Index, class _Tp>
struct _LIBCPP_TEMPLATE_VIS __alt {
  using __value_type = _Tp;

  template <class... _Args>
  inline _LIBCPP_INLINE_VISIBILITY
  explicit constexpr __alt(in_place_t, _Args&&... __args)
      : __value(_VSTD::forward<_Args>(__args)...) {}

  __value_type __value;
};

template <_Trait _DestructibleTrait, size_t _Index, class... _Types>
union _LIBCPP_TEMPLATE_VIS __union;

template <_Trait _DestructibleTrait, size_t _Index>
union _LIBCPP_TEMPLATE_VIS __union<_DestructibleTrait, _Index> {};

#define _LIBCPP_VARIANT_UNION(destructible_trait, destructor)                  \
  template <size_t _Index, class _Tp, class... _Types>                         \
  union _LIBCPP_TEMPLATE_VIS __union<destructible_trait,                      \
                                      _Index,                                  \
                                      _Tp,                                     \
                                      _Types...> {                             \
  public:                                                                      \
    inline _LIBCPP_INLINE_VISIBILITY                                           \
    explicit constexpr __union(__valueless_t) noexcept : __dummy{} {}          \
                                                                               \
    template <class... _Args>                                                  \
    inline _LIBCPP_INLINE_VISIBILITY                                           \
    explicit constexpr __union(in_place_index_t<0>, _Args&&... __args)         \
        : __head(in_place, _VSTD::forward<_Args>(__args)...) {}                \
                                                                               \
    template <size_t _Ip, class... _Args>                                      \
    inline _LIBCPP_INLINE_VISIBILITY                                           \
    explicit constexpr __union(in_place_index_t<_Ip>, _Args&&... __args)       \
        : __tail(in_place_index<_Ip - 1>, _VSTD::forward<_Args>(__args)...) {} \
                                                                               \
    __union(const __union&) = default;                                         \
    __union(__union&&) = default;                                              \
                                                                               \
    destructor                                                                 \
                                                                               \
    __union& operator=(const __union&) = default;                              \
    __union& operator=(__union&&) = default;                                   \
                                                                               \
  private:                                                                     \
    char __dummy;                                                              \
    __alt<_Index, _Tp> __head;                                                 \
    __union<destructible_trait, _Index + 1, _Types...> __tail;                 \
                                                                               \
    friend struct __access::__union;                                           \
  }

_LIBCPP_VARIANT_UNION(_Trait::_TriviallyAvailable, ~__union() = default;);
_LIBCPP_VARIANT_UNION(_Trait::_Available, ~__union() {});
_LIBCPP_VARIANT_UNION(_Trait::_Unavailable, ~__union() = delete;);

#undef _LIBCPP_VARIANT_UNION

template <_Trait _DestructibleTrait, class... _Types>
class _LIBCPP_TEMPLATE_VIS __base {
public:
  inline _LIBCPP_INLINE_VISIBILITY
  explicit constexpr __base(__valueless_t tag) noexcept
      : __data(tag), __index(__variant_npos) {}

  template <size_t _Ip, class... _Args>
  inline _LIBCPP_INLINE_VISIBILITY
  explicit constexpr __base(in_place_index_t<_Ip>, _Args&&... __args)
      :
        __data(in_place_index<_Ip>, _VSTD::forward<_Args>(__args)...),
        __index(_Ip) {}

  inline _LIBCPP_INLINE_VISIBILITY
  constexpr bool valueless_by_exception() const noexcept {
    return index() == variant_npos;
  }

  inline _LIBCPP_INLINE_VISIBILITY
  constexpr size_t index() const noexcept {
    return __index == __variant_npos ? variant_npos : __index;
  }

protected:
  inline _LIBCPP_INLINE_VISIBILITY
  constexpr auto&& __as_base() & { return *this; }

  inline _LIBCPP_INLINE_VISIBILITY
  constexpr auto&& __as_base() && { return _VSTD::move(*this); }

  inline _LIBCPP_INLINE_VISIBILITY
  constexpr auto&& __as_base() const & { return *this; }

  inline _LIBCPP_INLINE_VISIBILITY
  constexpr auto&& __as_base() const && { return _VSTD::move(*this); }

  inline _LIBCPP_INLINE_VISIBILITY
  static constexpr size_t __size() { return sizeof...(_Types); }

  __union<_DestructibleTrait, 0, _Types...> __data;
  unsigned int __index;

  friend struct __access::__base;
  friend struct __visitation::__base;
};

template <class _Traits, _Trait = _Traits::__destructible_trait>
class _LIBCPP_TEMPLATE_VIS __destructor;

#define _LIBCPP_VARIANT_DESTRUCTOR(destructible_trait, destructor, destroy)    \
  template <class... _Types>                                                   \
  class _LIBCPP_TEMPLATE_VIS __destructor<__traits<_Types...>,                \
                                           destructible_trait>                 \
      : public __base<destructible_trait, _Types...> {                         \
    using __base_type = __base<destructible_trait, _Types...>;                 \
                                                                               \
  public:                                                                      \
    using __base_type::__base_type;                                            \
    using __base_type::operator=;                                              \
                                                                               \
    __destructor(const __destructor&) = default;                               \
    __destructor(__destructor&&) = default;                                    \
    destructor                                                                 \
    __destructor& operator=(const __destructor&) = default;                    \
    __destructor& operator=(__destructor&&) = default;                         \
                                                                               \
  protected:                                                                   \
    inline _LIBCPP_INLINE_VISIBILITY                                           \
    destroy                                                                    \
  }

_LIBCPP_VARIANT_DESTRUCTOR(
    _Trait::_TriviallyAvailable,
    ~__destructor() = default;,
    void __destroy() noexcept { this->__index = __variant_npos; });

_LIBCPP_VARIANT_DESTRUCTOR(
    _Trait::_Available,
    ~__destructor() { __destroy(); },
    void __destroy() noexcept {
      if (!this->valueless_by_exception()) {
        __visitation::__base::__visit_alt(
            [](auto& __alt) noexcept {
              using __alt_type = decay_t<decltype(__alt)>;
              __alt.~__alt_type();
            },
            *this);
      }
      this->__index = __variant_npos;
    });

_LIBCPP_VARIANT_DESTRUCTOR(
    _Trait::_Unavailable,
    ~__destructor() = delete;,
    void __destroy() noexcept = delete;);

#undef _LIBCPP_VARIANT_DESTRUCTOR

template <class _Traits>
class _LIBCPP_TEMPLATE_VIS __constructor : public __destructor<_Traits> {
  using __base_type = __destructor<_Traits>;

public:
  using __base_type::__base_type;
  using __base_type::operator=;

protected:
  template <size_t _Ip, class _Tp, class... _Args>
  inline _LIBCPP_INLINE_VISIBILITY
  static _Tp& __construct_alt(__alt<_Ip, _Tp>& __a, _Args&&... __args) {
    ::new ((void*)_VSTD::addressof(__a))
        __alt<_Ip, _Tp>(in_place, _VSTD::forward<_Args>(__args)...);
    return __a.__value;
  }

  template <class _Rhs>
  inline _LIBCPP_INLINE_VISIBILITY
  static void __generic_construct(__constructor& __lhs, _Rhs&& __rhs) {
    __lhs.__destroy();
    if (!__rhs.valueless_by_exception()) {
      __visitation::__base::__visit_alt_at(
          __rhs.index(),
          [](auto& __lhs_alt, auto&& __rhs_alt) {
            __construct_alt(
                __lhs_alt,
                _VSTD::forward<decltype(__rhs_alt)>(__rhs_alt).__value);
          },
          __lhs, _VSTD::forward<_Rhs>(__rhs));
      __lhs.__index = __rhs.index();
    }
  }
};

template <class _Traits, _Trait = _Traits::__move_constructible_trait>
class _LIBCPP_TEMPLATE_VIS __move_constructor;

#define _LIBCPP_VARIANT_MOVE_CONSTRUCTOR(move_constructible_trait,             \
                                         move_constructor)                     \
  template <class... _Types>                                                   \
  class _LIBCPP_TEMPLATE_VIS __move_constructor<__traits<_Types...>,          \
                                                 move_constructible_trait>     \
      : public __constructor<__traits<_Types...>> {                            \
    using __base_type = __constructor<__traits<_Types...>>;                    \
                                                                               \
  public:                                                                      \
    using __base_type::__base_type;                                            \
    using __base_type::operator=;                                              \
                                                                               \
    __move_constructor(const __move_constructor&) = default;                   \
    move_constructor                                                           \
    ~__move_constructor() = default;                                           \
    __move_constructor& operator=(const __move_constructor&) = default;        \
    __move_constructor& operator=(__move_constructor&&) = default;             \
  }

_LIBCPP_VARIANT_MOVE_CONSTRUCTOR(
    _Trait::_TriviallyAvailable,
    __move_constructor(__move_constructor&& __that) = default;);

_LIBCPP_VARIANT_MOVE_CONSTRUCTOR(
    _Trait::_Available,
    __move_constructor(__move_constructor&& __that) noexcept(
        __all<is_nothrow_move_constructible_v<_Types>...>::value)
        : __move_constructor(__valueless_t{}) {
      this->__generic_construct(*this, _VSTD::move(__that));
    });

_LIBCPP_VARIANT_MOVE_CONSTRUCTOR(
    _Trait::_Unavailable,
    __move_constructor(__move_constructor&&) = delete;);

#undef _LIBCPP_VARIANT_MOVE_CONSTRUCTOR

template <class _Traits, _Trait = _Traits::__copy_constructible_trait>
class _LIBCPP_TEMPLATE_VIS __copy_constructor;

#define _LIBCPP_VARIANT_COPY_CONSTRUCTOR(copy_constructible_trait,             \
                                         copy_constructor)                     \
  template <class... _Types>                                                   \
  class _LIBCPP_TEMPLATE_VIS __copy_constructor<__traits<_Types...>,          \
                                                 copy_constructible_trait>     \
      : public __move_constructor<__traits<_Types...>> {                       \
    using __base_type = __move_constructor<__traits<_Types...>>;               \
                                                                               \
  public:                                                                      \
    using __base_type::__base_type;                                            \
    using __base_type::operator=;                                              \
                                                                               \
    copy_constructor                                                           \
    __copy_constructor(__copy_constructor&&) = default;                        \
    ~__copy_constructor() = default;                                           \
    __copy_constructor& operator=(const __copy_constructor&) = default;        \
    __copy_constructor& operator=(__copy_constructor&&) = default;             \
  }

_LIBCPP_VARIANT_COPY_CONSTRUCTOR(
    _Trait::_TriviallyAvailable,
    __copy_constructor(const __copy_constructor& __that) = default;);

_LIBCPP_VARIANT_COPY_CONSTRUCTOR(
    _Trait::_Available,
    __copy_constructor(const __copy_constructor& __that)
        : __copy_constructor(__valueless_t{}) {
      this->__generic_construct(*this, __that);
    });

_LIBCPP_VARIANT_COPY_CONSTRUCTOR(
    _Trait::_Unavailable,
    __copy_constructor(const __copy_constructor&) = delete;);

#undef _LIBCPP_VARIANT_COPY_CONSTRUCTOR

template <class _Traits>
class _LIBCPP_TEMPLATE_VIS __assignment : public __copy_constructor<_Traits> {
  using __base_type = __copy_constructor<_Traits>;

public:
  using __base_type::__base_type;
  using __base_type::operator=;

  template <size_t _Ip, class... _Args>
  inline _LIBCPP_INLINE_VISIBILITY
  auto& __emplace(_Args&&... __args) {
    this->__destroy();
    auto& __res = this->__construct_alt(__access::__base::__get_alt<_Ip>(*this),
                          _VSTD::forward<_Args>(__args)...);
    this->__index = _Ip;
    return __res;
  }

protected:
  template <size_t _Ip, class _Tp, class _Arg>
  inline _LIBCPP_INLINE_VISIBILITY
  void __assign_alt(__alt<_Ip, _Tp>& __a, _Arg&& __arg) {
    if (this->index() == _Ip) {
      __a.__value = _VSTD::forward<_Arg>(__arg);
    } else {
      struct {
        void operator()(true_type) const {
          __this->__emplace<_Ip>(_VSTD::forward<_Arg>(__arg));
        }
        void operator()(false_type) const {
          __this->__emplace<_Ip>(_Tp(_VSTD::forward<_Arg>(__arg)));
        }
        __assignment* __this;
        _Arg&& __arg;
      } __impl{this, _VSTD::forward<_Arg>(__arg)};
      __impl(bool_constant<is_nothrow_constructible_v<_Tp, _Arg> ||
                           !is_nothrow_move_constructible_v<_Tp>>{});
    }
  }

  template <class _That>
  inline _LIBCPP_INLINE_VISIBILITY
  void __generic_assign(_That&& __that) {
    if (this->valueless_by_exception() && __that.valueless_by_exception()) {
      // do nothing.
    } else if (__that.valueless_by_exception()) {
      this->__destroy();
    } else {
      __visitation::__base::__visit_alt_at(
          __that.index(),
          [this](auto& __this_alt, auto&& __that_alt) {
            this->__assign_alt(
                __this_alt,
                _VSTD::forward<decltype(__that_alt)>(__that_alt).__value);
          },
          *this, _VSTD::forward<_That>(__that));
    }
  }
};

template <class _Traits, _Trait = _Traits::__move_assignable_trait>
class _LIBCPP_TEMPLATE_VIS __move_assignment;

#define _LIBCPP_VARIANT_MOVE_ASSIGNMENT(move_assignable_trait,                 \
                                        move_assignment)                       \
  template <class... _Types>                                                   \
  class _LIBCPP_TEMPLATE_VIS __move_assignment<__traits<_Types...>,           \
                                                move_assignable_trait>         \
      : public __assignment<__traits<_Types...>> {                             \
    using __base_type = __assignment<__traits<_Types...>>;                     \
                                                                               \
  public:                                                                      \
    using __base_type::__base_type;                                            \
    using __base_type::operator=;                                              \
                                                                               \
    __move_assignment(const __move_assignment&) = default;                     \
    __move_assignment(__move_assignment&&) = default;                          \
    ~__move_assignment() = default;                                            \
    __move_assignment& operator=(const __move_assignment&) = default;          \
    move_assignment                                                            \
  }

_LIBCPP_VARIANT_MOVE_ASSIGNMENT(
    _Trait::_TriviallyAvailable,
    __move_assignment& operator=(__move_assignment&& __that) = default;);

_LIBCPP_VARIANT_MOVE_ASSIGNMENT(
    _Trait::_Available,
    __move_assignment& operator=(__move_assignment&& __that) noexcept(
        __all<(is_nothrow_move_constructible_v<_Types> &&
               is_nothrow_move_assignable_v<_Types>)...>::value) {
      this->__generic_assign(_VSTD::move(__that));
      return *this;
    });

_LIBCPP_VARIANT_MOVE_ASSIGNMENT(
    _Trait::_Unavailable,
    __move_assignment& operator=(__move_assignment&&) = delete;);

#undef _LIBCPP_VARIANT_MOVE_ASSIGNMENT

template <class _Traits, _Trait = _Traits::__copy_assignable_trait>
class _LIBCPP_TEMPLATE_VIS __copy_assignment;

#define _LIBCPP_VARIANT_COPY_ASSIGNMENT(copy_assignable_trait,                 \
                                        copy_assignment)                       \
  template <class... _Types>                                                   \
  class _LIBCPP_TEMPLATE_VIS __copy_assignment<__traits<_Types...>,           \
                                                copy_assignable_trait>         \
      : public __move_assignment<__traits<_Types...>> {                        \
    using __base_type = __move_assignment<__traits<_Types...>>;                \
                                                                               \
  public:                                                                      \
    using __base_type::__base_type;                                            \
    using __base_type::operator=;                                              \
                                                                               \
    __copy_assignment(const __copy_assignment&) = default;                     \
    __copy_assignment(__copy_assignment&&) = default;                          \
    ~__copy_assignment() = default;                                            \
    copy_assignment                                                            \
    __copy_assignment& operator=(__copy_assignment&&) = default;               \
  }

_LIBCPP_VARIANT_COPY_ASSIGNMENT(
    _Trait::_TriviallyAvailable,
    __copy_assignment& operator=(const __copy_assignment& __that) = default;);

_LIBCPP_VARIANT_COPY_ASSIGNMENT(
    _Trait::_Available,
    __copy_assignment& operator=(const __copy_assignment& __that) {
      this->__generic_assign(__that);
      return *this;
    });

_LIBCPP_VARIANT_COPY_ASSIGNMENT(
    _Trait::_Unavailable,
    __copy_assignment& operator=(const __copy_assignment&) = delete;);

#undef _LIBCPP_VARIANT_COPY_ASSIGNMENT

template <class... _Types>
class _LIBCPP_TEMPLATE_VIS __impl
    : public __copy_assignment<__traits<_Types...>> {
  using __base_type = __copy_assignment<__traits<_Types...>>;

public:
  using __base_type::__base_type;
  using __base_type::operator=;

  template <size_t _Ip, class _Arg>
  inline _LIBCPP_INLINE_VISIBILITY
  void __assign(_Arg&& __arg) {
    this->__assign_alt(__access::__base::__get_alt<_Ip>(*this),
                       _VSTD::forward<_Arg>(__arg));
  }

  inline _LIBCPP_INLINE_VISIBILITY
  void __swap(__impl& __that)  {
    if (this->valueless_by_exception() && __that.valueless_by_exception()) {
      // do nothing.
    } else if (this->index() == __that.index()) {
      __visitation::__base::__visit_alt_at(
          this->index(),
          [](auto& __this_alt, auto& __that_alt) {
            using _VSTD::swap;
            swap(__this_alt.__value, __that_alt.__value);
          },
          *this,
          __that);
    } else {
      __impl* __lhs = this;
      __impl* __rhs = _VSTD::addressof(__that);
      if (__lhs->__move_nothrow() && !__rhs->__move_nothrow()) {
        _VSTD::swap(__lhs, __rhs);
      }
      __impl __tmp(_VSTD::move(*__rhs));
#ifndef _LIBCPP_NO_EXCEPTIONS
      // EXTENSION: When the move construction of `__lhs` into `__rhs` throws
      // and `__tmp` is nothrow move constructible then we move `__tmp` back
      // into `__rhs` and provide the strong exception safety guarentee.
      try {
        this->__generic_construct(*__rhs, _VSTD::move(*__lhs));
      } catch (...) {
        if (__tmp.__move_nothrow()) {
          this->__generic_construct(*__rhs, _VSTD::move(__tmp));
        }
        throw;
      }
#else
      this->__generic_construct(*__rhs, _VSTD::move(*__lhs));
#endif
      this->__generic_construct(*__lhs, _VSTD::move(__tmp));
    }
  }

private:
  inline _LIBCPP_INLINE_VISIBILITY
  bool __move_nothrow() const {
    constexpr bool __results[] = {is_nothrow_move_constructible_v<_Types>...};
    return this->valueless_by_exception() || __results[this->index()];
  }
};

template <class... _Types>
struct __overload;

template <>
struct __overload<> { void operator()() const; };

template <class _Tp, class... _Types>
struct __overload<_Tp, _Types...> : __overload<_Types...> {
  using __overload<_Types...>::operator();
  __identity<_Tp> operator()(_Tp) const;
};

template <class _Tp, class... _Types>
using __best_match_t = typename result_of_t<__overload<_Types...>(_Tp&&)>::type;

} // __variant_detail

template <class... _Types>
class _LIBCPP_TEMPLATE_VIS variant
    : private __sfinae_ctor_base<
          __all<is_copy_constructible_v<_Types>...>::value,
          __all<is_move_constructible_v<_Types>...>::value>,
      private __sfinae_assign_base<
          __all<(is_copy_constructible_v<_Types> &&
                 is_copy_assignable_v<_Types>)...>::value,
          __all<(is_move_constructible_v<_Types> &&
                 is_move_assignable_v<_Types>)...>::value> {
  static_assert(0 < sizeof...(_Types),
                "variant must consist of at least one alternative.");

  static_assert(__all<!is_array_v<_Types>...>::value,
                "variant can not have an array type as an alternative.");

  static_assert(__all<!is_reference_v<_Types>...>::value,
                "variant can not have a reference type as an alternative.");

  static_assert(__all<!is_void_v<_Types>...>::value,
                "variant can not have a void type as an alternative.");

  using __first_type = variant_alternative_t<0, variant>;

public:
  template <bool _Dummy = true,
            enable_if_t<__dependent_type<is_default_constructible<__first_type>,
                                         _Dummy>::value,
                        int> = 0>
  inline _LIBCPP_INLINE_VISIBILITY
  constexpr variant() noexcept(is_nothrow_default_constructible_v<__first_type>)
      : __impl(in_place_index<0>) {}

  variant(const variant&) = default;
  variant(variant&&) = default;

  template <
      class _Arg,
      enable_if_t<!is_same_v<decay_t<_Arg>, variant>, int> = 0,
      enable_if_t<!__is_inplace_type<decay_t<_Arg>>::value, int> = 0,
      enable_if_t<!__is_inplace_index<decay_t<_Arg>>::value, int> = 0,
      class _Tp = __variant_detail::__best_match_t<_Arg, _Types...>,
      size_t _Ip =
          __find_detail::__find_unambiguous_index_sfinae<_Tp, _Types...>::value,
      enable_if_t<is_constructible_v<_Tp, _Arg>, int> = 0>
  inline _LIBCPP_INLINE_VISIBILITY
  constexpr variant(_Arg&& __arg) noexcept(
      is_nothrow_constructible_v<_Tp, _Arg>)
      : __impl(in_place_index<_Ip>, _VSTD::forward<_Arg>(__arg)) {}

  template <size_t _Ip, class... _Args,
            class = enable_if_t<(_Ip < sizeof...(_Types)), int>,
            class _Tp = variant_alternative_t<_Ip, variant<_Types...>>,
            enable_if_t<is_constructible_v<_Tp, _Args...>, int> = 0>
  inline _LIBCPP_INLINE_VISIBILITY
  explicit constexpr variant(
      in_place_index_t<_Ip>,
      _Args&&... __args) noexcept(is_nothrow_constructible_v<_Tp, _Args...>)
      : __impl(in_place_index<_Ip>, _VSTD::forward<_Args>(__args)...) {}

  template <
      size_t _Ip,
      class _Up,
      class... _Args,
      enable_if_t<(_Ip < sizeof...(_Types)), int> = 0,
      class _Tp = variant_alternative_t<_Ip, variant<_Types...>>,
      enable_if_t<is_constructible_v<_Tp, initializer_list<_Up>&, _Args...>,
                  int> = 0>
  inline _LIBCPP_INLINE_VISIBILITY
  explicit constexpr variant(
      in_place_index_t<_Ip>,
      initializer_list<_Up> __il,
      _Args&&... __args) noexcept(
      is_nothrow_constructible_v<_Tp, initializer_list<_Up>&, _Args...>)
      : __impl(in_place_index<_Ip>, __il, _VSTD::forward<_Args>(__args)...) {}

  template <
      class _Tp,
      class... _Args,
      size_t _Ip =
          __find_detail::__find_unambiguous_index_sfinae<_Tp, _Types...>::value,
      enable_if_t<is_constructible_v<_Tp, _Args...>, int> = 0>
  inline _LIBCPP_INLINE_VISIBILITY
  explicit constexpr variant(in_place_type_t<_Tp>, _Args&&... __args) noexcept(
      is_nothrow_constructible_v<_Tp, _Args...>)
      : __impl(in_place_index<_Ip>, _VSTD::forward<_Args>(__args)...) {}

  template <
      class _Tp,
      class _Up,
      class... _Args,
      size_t _Ip =
          __find_detail::__find_unambiguous_index_sfinae<_Tp, _Types...>::value,
      enable_if_t<is_constructible_v<_Tp, initializer_list<_Up>&, _Args...>,
                  int> = 0>
  inline _LIBCPP_INLINE_VISIBILITY
  explicit constexpr variant(
      in_place_type_t<_Tp>,
      initializer_list<_Up> __il,
      _Args&&... __args) noexcept(
      is_nothrow_constructible_v<_Tp, initializer_list< _Up>&, _Args...>)
      : __impl(in_place_index<_Ip>, __il, _VSTD::forward<_Args>(__args)...) {}

  ~variant() = default;

  variant& operator=(const variant&) = default;
  variant& operator=(variant&&) = default;

  template <
      class _Arg,
      enable_if_t<!is_same_v<decay_t<_Arg>, variant>, int> = 0,
      class _Tp = __variant_detail::__best_match_t<_Arg, _Types...>,
      size_t _Ip =
          __find_detail::__find_unambiguous_index_sfinae<_Tp, _Types...>::value,
      enable_if_t<is_assignable_v<_Tp&, _Arg> && is_constructible_v<_Tp, _Arg>,
                  int> = 0>
  inline _LIBCPP_INLINE_VISIBILITY
  variant& operator=(_Arg&& __arg) noexcept(
      is_nothrow_assignable_v<_Tp&, _Arg> &&
      is_nothrow_constructible_v<_Tp, _Arg>) {
    __impl.template __assign<_Ip>(_VSTD::forward<_Arg>(__arg));
    return *this;
  }

  template <
      size_t _Ip,
      class... _Args,
      enable_if_t<(_Ip < sizeof...(_Types)), int> = 0,
      class _Tp = variant_alternative_t<_Ip, variant<_Types...>>,
      enable_if_t<is_constructible_v<_Tp, _Args...>, int> = 0>
  inline _LIBCPP_INLINE_VISIBILITY
  _Tp& emplace(_Args&&... __args) {
    return __impl.template __emplace<_Ip>(_VSTD::forward<_Args>(__args)...);
  }

  template <
      size_t _Ip,
      class _Up,
      class... _Args,
      enable_if_t<(_Ip < sizeof...(_Types)), int> = 0,
      class _Tp = variant_alternative_t<_Ip, variant<_Types...>>,
      enable_if_t<is_constructible_v<_Tp, initializer_list<_Up>&, _Args...>,
                  int> = 0>
  inline _LIBCPP_INLINE_VISIBILITY
  _Tp& emplace(initializer_list<_Up> __il, _Args&&... __args) {
    return __impl.template __emplace<_Ip>(__il, _VSTD::forward<_Args>(__args)...);
  }

  template <
      class _Tp,
      class... _Args,
      size_t _Ip =
          __find_detail::__find_unambiguous_index_sfinae<_Tp, _Types...>::value,
      enable_if_t<is_constructible_v<_Tp, _Args...>, int> = 0>
  inline _LIBCPP_INLINE_VISIBILITY
  _Tp& emplace(_Args&&... __args) {
    return __impl.template __emplace<_Ip>(_VSTD::forward<_Args>(__args)...);
  }

  template <
      class _Tp,
      class _Up,
      class... _Args,
      size_t _Ip =
          __find_detail::__find_unambiguous_index_sfinae<_Tp, _Types...>::value,
      enable_if_t<is_constructible_v<_Tp, initializer_list<_Up>&, _Args...>,
                  int> = 0>
  inline _LIBCPP_INLINE_VISIBILITY
  _Tp& emplace(initializer_list<_Up> __il, _Args&&... __args) {
    return __impl.template __emplace<_Ip>(__il, _VSTD::forward<_Args>(__args)...);
  }

  inline _LIBCPP_INLINE_VISIBILITY
  constexpr bool valueless_by_exception() const noexcept {
    return __impl.valueless_by_exception();
  }

  inline _LIBCPP_INLINE_VISIBILITY
  constexpr size_t index() const noexcept { return __impl.index(); }

  template <
      bool _Dummy = true,
      enable_if_t<
          __all<(
              __dependent_type<is_move_constructible<_Types>, _Dummy>::value &&
              __dependent_type<is_swappable<_Types>, _Dummy>::value)...>::value,
          int> = 0>
  inline _LIBCPP_INLINE_VISIBILITY
  void swap(variant& __that) noexcept(
      __all<(is_nothrow_move_constructible_v<_Types> &&
             is_nothrow_swappable_v<_Types>)...>::value) {
    __impl.__swap(__that.__impl);
  }

private:
  __variant_detail::__impl<_Types...> __impl;

  friend struct __variant_detail::__access::__variant;
  friend struct __variant_detail::__visitation::__variant;
};

template <size_t _Ip, class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr bool __holds_alternative(const variant<_Types...>& __v) noexcept {
  return __v.index() == _Ip;
}

template <class _Tp, class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr bool holds_alternative(const variant<_Types...>& __v) noexcept {
  return __holds_alternative<__find_exactly_one_t<_Tp, _Types...>::value>(__v);
}

template <size_t _Ip, class _Vp>
inline _LIBCPP_INLINE_VISIBILITY
static constexpr auto&& __generic_get(_Vp&& __v) {
  using __variant_detail::__access::__variant;
  if (!__holds_alternative<_Ip>(__v)) {
    __throw_bad_variant_access();
  }
  return __variant::__get_alt<_Ip>(_VSTD::forward<_Vp>(__v)).__value;
}

template <size_t _Ip, class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr variant_alternative_t<_Ip, variant<_Types...>>& get(
    variant<_Types...>& __v) {
  static_assert(_Ip < sizeof...(_Types));
  static_assert(!is_void_v<variant_alternative_t<_Ip, variant<_Types...>>>);
  return __generic_get<_Ip>(__v);
}

template <size_t _Ip, class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr variant_alternative_t<_Ip, variant<_Types...>>&& get(
    variant<_Types...>&& __v) {
  static_assert(_Ip < sizeof...(_Types));
  static_assert(!is_void_v<variant_alternative_t<_Ip, variant<_Types...>>>);
  return __generic_get<_Ip>(_VSTD::move(__v));
}

template <size_t _Ip, class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr const variant_alternative_t<_Ip, variant<_Types...>>& get(
    const variant<_Types...>& __v) {
  static_assert(_Ip < sizeof...(_Types));
  static_assert(!is_void_v<variant_alternative_t<_Ip, variant<_Types...>>>);
  return __generic_get<_Ip>(__v);
}

template <size_t _Ip, class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr const variant_alternative_t<_Ip, variant<_Types...>>&& get(
    const variant<_Types...>&& __v) {
  static_assert(_Ip < sizeof...(_Types));
  static_assert(!is_void_v<variant_alternative_t<_Ip, variant<_Types...>>>);
  return __generic_get<_Ip>(_VSTD::move(__v));
}

template <class _Tp, class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr _Tp& get(variant<_Types...>& __v) {
  static_assert(!is_void_v<_Tp>);
  return _VSTD::get<__find_exactly_one_t<_Tp, _Types...>::value>(__v);
}

template <class _Tp, class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr _Tp&& get(variant<_Types...>&& __v) {
  static_assert(!is_void_v<_Tp>);
  return _VSTD::get<__find_exactly_one_t<_Tp, _Types...>::value>(
      _VSTD::move(__v));
}

template <class _Tp, class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr const _Tp& get(const variant<_Types...>& __v) {
  static_assert(!is_void_v<_Tp>);
  return _VSTD::get<__find_exactly_one_t<_Tp, _Types...>::value>(__v);
}

template <class _Tp, class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr const _Tp&& get(const variant<_Types...>&& __v) {
  static_assert(!is_void_v<_Tp>);
  return _VSTD::get<__find_exactly_one_t<_Tp, _Types...>::value>(
      _VSTD::move(__v));
}

template <size_t _Ip, class _Vp>
inline _LIBCPP_INLINE_VISIBILITY
constexpr auto* __generic_get_if(_Vp* __v) noexcept {
  using __variant_detail::__access::__variant;
  return __v && __holds_alternative<_Ip>(*__v)
             ? _VSTD::addressof(__variant::__get_alt<_Ip>(*__v).__value)
             : nullptr;
}

template <size_t _Ip, class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr add_pointer_t<variant_alternative_t<_Ip, variant<_Types...>>>
get_if(variant<_Types...>* __v) noexcept {
  static_assert(_Ip < sizeof...(_Types));
  static_assert(!is_void_v<variant_alternative_t<_Ip, variant<_Types...>>>);
  return __generic_get_if<_Ip>(__v);
}

template <size_t _Ip, class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr add_pointer_t<const variant_alternative_t<_Ip, variant<_Types...>>>
get_if(const variant<_Types...>* __v) noexcept {
  static_assert(_Ip < sizeof...(_Types));
  static_assert(!is_void_v<variant_alternative_t<_Ip, variant<_Types...>>>);
  return __generic_get_if<_Ip>(__v);
}

template <class _Tp, class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr add_pointer_t<_Tp>
get_if(variant<_Types...>* __v) noexcept {
  static_assert(!is_void_v<_Tp>);
  return _VSTD::get_if<__find_exactly_one_t<_Tp, _Types...>::value>(__v);
}

template <class _Tp, class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr add_pointer_t<const _Tp>
get_if(const variant<_Types...>* __v) noexcept {
  static_assert(!is_void_v<_Tp>);
  return _VSTD::get_if<__find_exactly_one_t<_Tp, _Types...>::value>(__v);
}

template <class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr bool operator==(const variant<_Types...>& __lhs,
                          const variant<_Types...>& __rhs) {
  using __variant_detail::__visitation::__variant;
  if (__lhs.index() != __rhs.index()) return false;
  if (__lhs.valueless_by_exception()) return true;
  return __variant::__visit_value_at(__lhs.index(), equal_to<>{}, __lhs, __rhs);
}

template <class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr bool operator!=(const variant<_Types...>& __lhs,
                          const variant<_Types...>& __rhs) {
  using __variant_detail::__visitation::__variant;
  if (__lhs.index() != __rhs.index()) return true;
  if (__lhs.valueless_by_exception()) return false;
  return __variant::__visit_value_at(
      __lhs.index(), not_equal_to<>{}, __lhs, __rhs);
}

template <class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr bool operator<(const variant<_Types...>& __lhs,
                         const variant<_Types...>& __rhs) {
  using __variant_detail::__visitation::__variant;
  if (__rhs.valueless_by_exception()) return false;
  if (__lhs.valueless_by_exception()) return true;
  if (__lhs.index() < __rhs.index()) return true;
  if (__lhs.index() > __rhs.index()) return false;
  return __variant::__visit_value_at(__lhs.index(), less<>{}, __lhs, __rhs);
}

template <class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr bool operator>(const variant<_Types...>& __lhs,
                         const variant<_Types...>& __rhs) {
  using __variant_detail::__visitation::__variant;
  if (__lhs.valueless_by_exception()) return false;
  if (__rhs.valueless_by_exception()) return true;
  if (__lhs.index() > __rhs.index()) return true;
  if (__lhs.index() < __rhs.index()) return false;
  return __variant::__visit_value_at(__lhs.index(), greater<>{}, __lhs, __rhs);
}

template <class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr bool operator<=(const variant<_Types...>& __lhs,
                          const variant<_Types...>& __rhs) {
  using __variant_detail::__visitation::__variant;
  if (__lhs.valueless_by_exception()) return true;
  if (__rhs.valueless_by_exception()) return false;
  if (__lhs.index() < __rhs.index()) return true;
  if (__lhs.index() > __rhs.index()) return false;
  return __variant::__visit_value_at(
      __lhs.index(), less_equal<>{}, __lhs, __rhs);
}

template <class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
constexpr bool operator>=(const variant<_Types...>& __lhs,
                          const variant<_Types...>& __rhs) {
  using __variant_detail::__visitation::__variant;
  if (__rhs.valueless_by_exception()) return true;
  if (__lhs.valueless_by_exception()) return false;
  if (__lhs.index() > __rhs.index()) return true;
  if (__lhs.index() < __rhs.index()) return false;
  return __variant::__visit_value_at(
      __lhs.index(), greater_equal<>{}, __lhs, __rhs);
}

template <class _Visitor, class... _Vs>
inline _LIBCPP_INLINE_VISIBILITY
constexpr decltype(auto) visit(_Visitor&& __visitor, _Vs&&... __vs) {
  using __variant_detail::__visitation::__variant;
  bool __results[] = {__vs.valueless_by_exception()...};
  for (bool __result : __results) {
    if (__result) {
      __throw_bad_variant_access();
    }
  }
  return __variant::__visit_value(_VSTD::forward<_Visitor>(__visitor),
                                  _VSTD::forward<_Vs>(__vs)...);
}

struct _LIBCPP_TEMPLATE_VIS monostate {};

inline _LIBCPP_INLINE_VISIBILITY
constexpr bool operator<(monostate, monostate) noexcept { return false; }

inline _LIBCPP_INLINE_VISIBILITY
constexpr bool operator>(monostate, monostate) noexcept { return false; }

inline _LIBCPP_INLINE_VISIBILITY
constexpr bool operator<=(monostate, monostate) noexcept { return true; }

inline _LIBCPP_INLINE_VISIBILITY
constexpr bool operator>=(monostate, monostate) noexcept { return true; }

inline _LIBCPP_INLINE_VISIBILITY
constexpr bool operator==(monostate, monostate) noexcept { return true; }

inline _LIBCPP_INLINE_VISIBILITY
constexpr bool operator!=(monostate, monostate) noexcept { return false; }

template <class... _Types>
inline _LIBCPP_INLINE_VISIBILITY
auto swap(variant<_Types...>& __lhs,
          variant<_Types...>& __rhs) noexcept(noexcept(__lhs.swap(__rhs)))
    -> decltype(__lhs.swap(__rhs)) {
  __lhs.swap(__rhs);
}

template <class... _Types>
struct _LIBCPP_TEMPLATE_VIS hash<
    __enable_hash_helper<variant<_Types...>, remove_const_t<_Types>...>> {
  using argument_type = variant<_Types...>;
  using result_type = size_t;

  inline _LIBCPP_INLINE_VISIBILITY
  result_type operator()(const argument_type& __v) const {
    using __variant_detail::__visitation::__variant;
    size_t __res =
        __v.valueless_by_exception()
               ? 299792458 // Random value chosen by the universe upon creation
               : __variant::__visit_alt(
                     [](const auto& __alt) {
                       using __alt_type = decay_t<decltype(__alt)>;
                       using __value_type = remove_const_t<
                         typename __alt_type::__value_type>;
                       return hash<__value_type>{}(__alt.__value);
                     },
                     __v);
    return __hash_combine(__res, hash<size_t>{}(__v.index()));
  }
};

template <>
struct _LIBCPP_TEMPLATE_VIS hash<monostate> {
  using argument_type = monostate;
  using result_type = size_t;

  inline _LIBCPP_INLINE_VISIBILITY
  result_type operator()(const argument_type&) const _NOEXCEPT {
    return 66740831; // return a fundamentally attractive random value.
  }
};

#endif  // _LIBCPP_STD_VER > 14

_LIBCPP_END_NAMESPACE_STD

#endif  // _LIBCPP_VARIANT
