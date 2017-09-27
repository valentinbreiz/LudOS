// -*- C++ -*-
//===-------------------------- unordered_map -----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_UNORDERED_MAP
#define _LIBCPP_UNORDERED_MAP

#include <__config.hpp>
#include <__hash_table.hpp>
#include <functional.hpp>
#include <stdexcept.hpp>
#include <tuple.hpp>

#include <__debug.hpp>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

template <class _Key, class _Cp, class _Hash, bool _IsEmpty>
class __unordered_map_hasher
    : private _Hash
{
public:
    _LIBCPP_INLINE_VISIBILITY
    __unordered_map_hasher()
        _NOEXCEPT_(is_nothrow_default_constructible<_Hash>::value)
        : _Hash() {}
    _LIBCPP_INLINE_VISIBILITY
    __unordered_map_hasher(const _Hash& __h)
        _NOEXCEPT_(is_nothrow_copy_constructible<_Hash>::value)
        : _Hash(__h) {}
    _LIBCPP_INLINE_VISIBILITY
    const _Hash& hash_function() const _NOEXCEPT {return *this;}
    _LIBCPP_INLINE_VISIBILITY
    size_t operator()(const _Cp& __x) const
        {return static_cast<const _Hash&>(*this)(__x.__cc.first);}
    _LIBCPP_INLINE_VISIBILITY
    size_t operator()(const _Key& __x) const
        {return static_cast<const _Hash&>(*this)(__x);}
    void swap(__unordered_map_hasher&__y)
        _NOEXCEPT_(__is_nothrow_swappable<_Hash>::value)
    {
        using _VSTD::swap;
        swap(static_cast<_Hash&>(*this), static_cast<_Hash&>(__y));
    }
};

template <class _Key, class _Cp, class _Hash>
class __unordered_map_hasher<_Key, _Cp, _Hash, false>
{
    _Hash __hash_;
public:
    _LIBCPP_INLINE_VISIBILITY
    __unordered_map_hasher()
        _NOEXCEPT_(is_nothrow_default_constructible<_Hash>::value)
        : __hash_() {}
    _LIBCPP_INLINE_VISIBILITY
    __unordered_map_hasher(const _Hash& __h)
        _NOEXCEPT_(is_nothrow_copy_constructible<_Hash>::value)
        : __hash_(__h) {}
    _LIBCPP_INLINE_VISIBILITY
    const _Hash& hash_function() const _NOEXCEPT {return __hash_;}
    _LIBCPP_INLINE_VISIBILITY
    size_t operator()(const _Cp& __x) const
        {return __hash_(__x.__cc.first);}
    _LIBCPP_INLINE_VISIBILITY
    size_t operator()(const _Key& __x) const
        {return __hash_(__x);}
    void swap(__unordered_map_hasher&__y)
        _NOEXCEPT_(__is_nothrow_swappable<_Hash>::value)
    {
        using _VSTD::swap;
        swap(__hash_, __y.__hash_);
    }
};

template <class _Key, class _Cp, class _Hash, bool __b>
inline _LIBCPP_INLINE_VISIBILITY
void
swap(__unordered_map_hasher<_Key, _Cp, _Hash, __b>& __x,
     __unordered_map_hasher<_Key, _Cp, _Hash, __b>& __y)
    _NOEXCEPT_(_NOEXCEPT_(__x.swap(__y)))
{
    __x.swap(__y);
}

template <class _Key, class _Cp, class _Pred, bool _IsEmpty>
class __unordered_map_equal
    : private _Pred
{
public:
    _LIBCPP_INLINE_VISIBILITY
    __unordered_map_equal()
        _NOEXCEPT_(is_nothrow_default_constructible<_Pred>::value)
        : _Pred() {}
    _LIBCPP_INLINE_VISIBILITY
    __unordered_map_equal(const _Pred& __p)
        _NOEXCEPT_(is_nothrow_copy_constructible<_Pred>::value)
        : _Pred(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    const _Pred& key_eq() const _NOEXCEPT {return *this;}
    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _Cp& __x, const _Cp& __y) const
        {return static_cast<const _Pred&>(*this)(__x.__cc.first, __y.__cc.first);}
    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _Cp& __x, const _Key& __y) const
        {return static_cast<const _Pred&>(*this)(__x.__cc.first, __y);}
    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _Key& __x, const _Cp& __y) const
        {return static_cast<const _Pred&>(*this)(__x, __y.__cc.first);}
    void swap(__unordered_map_equal&__y)
        _NOEXCEPT_(__is_nothrow_swappable<_Pred>::value)
    {
        using _VSTD::swap;
        swap(static_cast<_Pred&>(*this), static_cast<_Pred&>(__y));
    }
};

template <class _Key, class _Cp, class _Pred>
class __unordered_map_equal<_Key, _Cp, _Pred, false>
{
    _Pred __pred_;
public:
    _LIBCPP_INLINE_VISIBILITY
    __unordered_map_equal()
        _NOEXCEPT_(is_nothrow_default_constructible<_Pred>::value)
        : __pred_() {}
    _LIBCPP_INLINE_VISIBILITY
    __unordered_map_equal(const _Pred& __p)
        _NOEXCEPT_(is_nothrow_copy_constructible<_Pred>::value)
        : __pred_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    const _Pred& key_eq() const _NOEXCEPT {return __pred_;}
    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _Cp& __x, const _Cp& __y) const
        {return __pred_(__x.__cc.first, __y.__cc.first);}
    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _Cp& __x, const _Key& __y) const
        {return __pred_(__x.__cc.first, __y);}
    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _Key& __x, const _Cp& __y) const
        {return __pred_(__x, __y.__cc.first);}
    void swap(__unordered_map_equal&__y)
        _NOEXCEPT_(__is_nothrow_swappable<_Pred>::value)
    {
        using _VSTD::swap;
        swap(__pred_, __y.__pred_);
    }
};

template <class _Key, class _Cp, class _Pred, bool __b>
inline _LIBCPP_INLINE_VISIBILITY
void
swap(__unordered_map_equal<_Key, _Cp, _Pred, __b>& __x,
     __unordered_map_equal<_Key, _Cp, _Pred, __b>& __y)
    _NOEXCEPT_(_NOEXCEPT_(__x.swap(__y)))
{
    __x.swap(__y);
}

template <class _Alloc>
class __hash_map_node_destructor
{
    typedef _Alloc                              allocator_type;
    typedef allocator_traits<allocator_type>    __alloc_traits;

public:

    typedef typename __alloc_traits::pointer       pointer;
private:

    allocator_type& __na_;

    __hash_map_node_destructor& operator=(const __hash_map_node_destructor&);

public:
    bool __first_constructed;
    bool __second_constructed;

    _LIBCPP_INLINE_VISIBILITY
    explicit __hash_map_node_destructor(allocator_type& __na) _NOEXCEPT
        : __na_(__na),
          __first_constructed(false),
          __second_constructed(false)
        {}

#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    __hash_map_node_destructor(__hash_node_destructor<allocator_type>&& __x)
        _NOEXCEPT
        : __na_(__x.__na_),
          __first_constructed(__x.__value_constructed),
          __second_constructed(__x.__value_constructed)
        {
            __x.__value_constructed = false;
        }
#else  // _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    __hash_map_node_destructor(const __hash_node_destructor<allocator_type>& __x)
        : __na_(__x.__na_),
          __first_constructed(__x.__value_constructed),
          __second_constructed(__x.__value_constructed)
        {
            const_cast<bool&>(__x.__value_constructed) = false;
        }
#endif  // _LIBCPP_CXX03_LANG

    _LIBCPP_INLINE_VISIBILITY
    void operator()(pointer __p) _NOEXCEPT
    {
        if (__second_constructed)
            __alloc_traits::destroy(__na_, _VSTD::addressof(__p->__value_.__cc.second));
        if (__first_constructed)
            __alloc_traits::destroy(__na_, _VSTD::addressof(__p->__value_.__cc.first));
        if (__p)
            __alloc_traits::deallocate(__na_, __p, 1);
    }
};

#ifndef _LIBCPP_CXX03_LANG
template <class _Key, class _Tp>
union __hash_value_type
{
    typedef _Key                                     key_type;
    typedef _Tp                                      mapped_type;
    typedef pair<const key_type, mapped_type>        value_type;
    typedef pair<key_type, mapped_type>              __nc_value_type;

    value_type __cc;
    __nc_value_type __nc;

    _LIBCPP_INLINE_VISIBILITY
    __hash_value_type& operator=(const __hash_value_type& __v)
        {__nc = __v.__cc; return *this;}

    _LIBCPP_INLINE_VISIBILITY
    __hash_value_type& operator=(__hash_value_type&& __v)
        {__nc = _VSTD::move(__v.__nc); return *this;}

    template <class _ValueTp,
              class = typename enable_if<
                    __is_same_uncvref<_ValueTp, value_type>::value
                 >::type
             >
    _LIBCPP_INLINE_VISIBILITY
    __hash_value_type& operator=(_ValueTp&& __v) {
        __nc = _VSTD::forward<_ValueTp>(__v); return *this;
    }

private:
    __hash_value_type(const __hash_value_type& __v) = delete;
    __hash_value_type(__hash_value_type&& __v) = delete;
    template <class ..._Args>
    explicit __hash_value_type(_Args&& ...__args) = delete;

    ~__hash_value_type() = delete;
};

#else

template <class _Key, class _Tp>
struct __hash_value_type
{
    typedef _Key                                     key_type;
    typedef _Tp                                      mapped_type;
    typedef pair<const key_type, mapped_type>        value_type;

    value_type __cc;

private:
   ~__hash_value_type();
};

#endif

template <class _HashIterator>
class _LIBCPP_TEMPLATE_VIS __hash_map_iterator
{
    _HashIterator __i_;

    typedef  __hash_node_types_from_iterator<_HashIterator> _NodeTypes;

public:
    typedef forward_iterator_tag                                 iterator_category;
    typedef typename _NodeTypes::__map_value_type                value_type;
    typedef typename _NodeTypes::difference_type                 difference_type;
    typedef value_type&                                          reference;
    typedef typename _NodeTypes::__map_value_type_pointer       pointer;

    _LIBCPP_INLINE_VISIBILITY
    __hash_map_iterator() _NOEXCEPT {}

    _LIBCPP_INLINE_VISIBILITY
    __hash_map_iterator(_HashIterator __i) _NOEXCEPT : __i_(__i) {}

    _LIBCPP_INLINE_VISIBILITY
    reference operator*() const {return __i_->__cc;}
    _LIBCPP_INLINE_VISIBILITY
    pointer operator->() const {return pointer_traits<pointer>::pointer_to(__i_->__cc);}

    _LIBCPP_INLINE_VISIBILITY
    __hash_map_iterator& operator++() {++__i_; return *this;}
    _LIBCPP_INLINE_VISIBILITY
    __hash_map_iterator operator++(int)
    {
        __hash_map_iterator __t(*this);
        ++(*this);
        return __t;
    }

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const __hash_map_iterator& __x, const __hash_map_iterator& __y)
        {return __x.__i_ == __y.__i_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const __hash_map_iterator& __x, const __hash_map_iterator& __y)
        {return __x.__i_ != __y.__i_;}

    template <class, class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS unordered_map;
    template <class, class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS unordered_multimap;
    template <class> friend class _LIBCPP_TEMPLATE_VIS __hash_const_iterator;
    template <class> friend class _LIBCPP_TEMPLATE_VIS __hash_const_local_iterator;
    template <class> friend class _LIBCPP_TEMPLATE_VIS __hash_map_const_iterator;
};

template <class _HashIterator>
class _LIBCPP_TEMPLATE_VIS __hash_map_const_iterator
{
    _HashIterator __i_;

    typedef  __hash_node_types_from_iterator<_HashIterator> _NodeTypes;

public:
    typedef forward_iterator_tag                                 iterator_category;
    typedef typename _NodeTypes::__map_value_type                value_type;
    typedef typename _NodeTypes::difference_type                 difference_type;
    typedef const value_type&                                    reference;
    typedef typename _NodeTypes::__const_map_value_type_pointer  pointer;

    _LIBCPP_INLINE_VISIBILITY
    __hash_map_const_iterator() _NOEXCEPT {}

    _LIBCPP_INLINE_VISIBILITY
    __hash_map_const_iterator(_HashIterator __i) _NOEXCEPT : __i_(__i) {}
    _LIBCPP_INLINE_VISIBILITY
    __hash_map_const_iterator(
            __hash_map_iterator<typename _HashIterator::__non_const_iterator> __i)
                 _NOEXCEPT
                : __i_(__i.__i_) {}

    _LIBCPP_INLINE_VISIBILITY
    reference operator*() const {return __i_->__cc;}
    _LIBCPP_INLINE_VISIBILITY
    pointer operator->() const {return pointer_traits<pointer>::pointer_to(__i_->__cc);}

    _LIBCPP_INLINE_VISIBILITY
    __hash_map_const_iterator& operator++() {++__i_; return *this;}
    _LIBCPP_INLINE_VISIBILITY
    __hash_map_const_iterator operator++(int)
    {
        __hash_map_const_iterator __t(*this);
        ++(*this);
        return __t;
    }

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const __hash_map_const_iterator& __x, const __hash_map_const_iterator& __y)
        {return __x.__i_ == __y.__i_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const __hash_map_const_iterator& __x, const __hash_map_const_iterator& __y)
        {return __x.__i_ != __y.__i_;}

    template <class, class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS unordered_map;
    template <class, class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS unordered_multimap;
    template <class> friend class _LIBCPP_TEMPLATE_VIS __hash_const_iterator;
    template <class> friend class _LIBCPP_TEMPLATE_VIS __hash_const_local_iterator;
};

template <class _Key, class _Tp, class _Hash = hash<_Key>, class _Pred = equal_to<_Key>,
          class _Alloc = allocator<pair<const _Key, _Tp> > >
class _LIBCPP_TEMPLATE_VIS unordered_map
{
public:
    // types
    typedef _Key                                           key_type;
    typedef _Tp                                            mapped_type;
    typedef _Hash                                          hasher;
    typedef _Pred                                          key_equal;
    typedef _Alloc                                         allocator_type;
    typedef pair<const key_type, mapped_type>              value_type;
    typedef pair<key_type, mapped_type>                    __nc_value_type;
    typedef value_type&                                    reference;
    typedef const value_type&                              const_reference;
    static_assert((is_same<value_type, typename allocator_type::value_type>::value),
                  "Invalid allocator::value_type");

private:
    typedef __hash_value_type<key_type, mapped_type>                 __value_type;
    typedef __unordered_map_hasher<key_type, __value_type, hasher>   __hasher;
    typedef __unordered_map_equal<key_type, __value_type, key_equal> __key_equal;
    typedef typename __rebind_alloc_helper<allocator_traits<allocator_type>,
                                                 __value_type>::type __allocator_type;

    typedef __hash_table<__value_type, __hasher,
                         __key_equal,  __allocator_type>   __table;

    __table __table_;

    typedef typename __table::_NodeTypes                   _NodeTypes;
    typedef typename __table::__node_pointer               __node_pointer;
    typedef typename __table::__node_const_pointer         __node_const_pointer;
    typedef typename __table::__node_traits                __node_traits;
    typedef typename __table::__node_allocator             __node_allocator;
    typedef typename __table::__node                       __node;
    typedef __hash_map_node_destructor<__node_allocator>   _Dp;
    typedef unique_ptr<__node, _Dp>                         __node_holder;
    typedef allocator_traits<allocator_type>               __alloc_traits;

    static_assert((is_same<typename __table::__container_value_type, value_type>::value), "");
    static_assert((is_same<typename __table::__node_value_type, __value_type>::value), "");
public:
    typedef typename __alloc_traits::pointer         pointer;
    typedef typename __alloc_traits::const_pointer   const_pointer;
    typedef typename __table::size_type              size_type;
    typedef typename __table::difference_type        difference_type;

    typedef __hash_map_iterator<typename __table::iterator>       iterator;
    typedef __hash_map_const_iterator<typename __table::const_iterator> const_iterator;
    typedef __hash_map_iterator<typename __table::local_iterator> local_iterator;
    typedef __hash_map_const_iterator<typename __table::const_local_iterator> const_local_iterator;

    _LIBCPP_INLINE_VISIBILITY
    unordered_map()
        _NOEXCEPT_(is_nothrow_default_constructible<__table>::value)
        {
#if _LIBCPP_DEBUG_LEVEL >= 2
            __get_db()->__insert_c(this);
#endif
        }
    explicit unordered_map(size_type __n, const hasher& __hf = hasher(),
                           const key_equal& __eql = key_equal());
    unordered_map(size_type __n, const hasher& __hf,
                  const key_equal& __eql,
                  const allocator_type& __a);
    template <class _InputIterator>
        unordered_map(_InputIterator __first, _InputIterator __last);
    template <class _InputIterator>
        unordered_map(_InputIterator __first, _InputIterator __last,
                      size_type __n, const hasher& __hf = hasher(),
                      const key_equal& __eql = key_equal());
    template <class _InputIterator>
        unordered_map(_InputIterator __first, _InputIterator __last,
                      size_type __n, const hasher& __hf,
                      const key_equal& __eql,
                      const allocator_type& __a);
    _LIBCPP_INLINE_VISIBILITY
    explicit unordered_map(const allocator_type& __a);
    unordered_map(const unordered_map& __u);
    unordered_map(const unordered_map& __u, const allocator_type& __a);
#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    unordered_map(unordered_map&& __u)
        _NOEXCEPT_(is_nothrow_move_constructible<__table>::value);
    unordered_map(unordered_map&& __u, const allocator_type& __a);
    unordered_map(initializer_list<value_type> __il);
    unordered_map(initializer_list<value_type> __il, size_type __n,
                  const hasher& __hf = hasher(), const key_equal& __eql = key_equal());
    unordered_map(initializer_list<value_type> __il, size_type __n,
                  const hasher& __hf, const key_equal& __eql,
                  const allocator_type& __a);
#endif  // _LIBCPP_CXX03_LANG
#if _LIBCPP_STD_VER > 11
    _LIBCPP_INLINE_VISIBILITY
    unordered_map(size_type __n, const allocator_type& __a)
      : unordered_map(__n, hasher(), key_equal(), __a) {}
    _LIBCPP_INLINE_VISIBILITY
    unordered_map(size_type __n, const hasher& __hf, const allocator_type& __a)
      : unordered_map(__n, __hf, key_equal(), __a) {}
    template <class _InputIterator>
    _LIBCPP_INLINE_VISIBILITY
      unordered_map(_InputIterator __first, _InputIterator __last, size_type __n, const allocator_type& __a)
      : unordered_map(__first, __last, __n, hasher(), key_equal(), __a) {}
    template <class _InputIterator>
    _LIBCPP_INLINE_VISIBILITY
      unordered_map(_InputIterator __first, _InputIterator __last, size_type __n, const hasher& __hf,
        const allocator_type& __a)
      : unordered_map(__first, __last, __n, __hf, key_equal(), __a) {}
    _LIBCPP_INLINE_VISIBILITY
    unordered_map(initializer_list<value_type> __il, size_type __n, const allocator_type& __a)
      : unordered_map(__il, __n, hasher(), key_equal(), __a) {}
    _LIBCPP_INLINE_VISIBILITY
    unordered_map(initializer_list<value_type> __il, size_type __n, const hasher& __hf,
      const allocator_type& __a)
      : unordered_map(__il, __n, __hf, key_equal(), __a) {}
#endif
    // ~unordered_map() = default;
    _LIBCPP_INLINE_VISIBILITY
    unordered_map& operator=(const unordered_map& __u)
    {
#ifndef _LIBCPP_CXX03_LANG
        __table_ = __u.__table_;
#else
        if (this != &__u) {
            __table_.clear();
            __table_.hash_function() = __u.__table_.hash_function();
            __table_.key_eq() = __u.__table_.key_eq();
            __table_.max_load_factor() = __u.__table_.max_load_factor();
            __table_.__copy_assign_alloc(__u.__table_);
            insert(__u.begin(), __u.end());
        }
#endif
        return *this;
    }
#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    unordered_map& operator=(unordered_map&& __u)
        _NOEXCEPT_(is_nothrow_move_assignable<__table>::value);
    _LIBCPP_INLINE_VISIBILITY
    unordered_map& operator=(initializer_list<value_type> __il);
#endif  // _LIBCPP_CXX03_LANG

    _LIBCPP_INLINE_VISIBILITY
    allocator_type get_allocator() const _NOEXCEPT
        {return allocator_type(__table_.__node_alloc());}

    _LIBCPP_INLINE_VISIBILITY
    bool      empty() const _NOEXCEPT {return __table_.size() == 0;}
    _LIBCPP_INLINE_VISIBILITY
    size_type size() const _NOEXCEPT  {return __table_.size();}
    _LIBCPP_INLINE_VISIBILITY
    size_type max_size() const _NOEXCEPT {return __table_.max_size();}

    _LIBCPP_INLINE_VISIBILITY
    iterator       begin() _NOEXCEPT        {return __table_.begin();}
    _LIBCPP_INLINE_VISIBILITY
    iterator       end() _NOEXCEPT          {return __table_.end();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator begin()  const _NOEXCEPT {return __table_.begin();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator end()    const _NOEXCEPT {return __table_.end();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator cbegin() const _NOEXCEPT {return __table_.begin();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator cend()   const _NOEXCEPT {return __table_.end();}

    _LIBCPP_INLINE_VISIBILITY
    pair<iterator, bool> insert(const value_type& __x)
        {return __table_.__insert_unique(__x);}

    iterator insert(const_iterator __p, const value_type& __x) {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__p) == this,
            "unordered_map::insert(const_iterator, const value_type&) called with an iterator not"
            " referring to this unordered_map");
#else
        ((void)__p);
#endif
        return insert(__x).first;
    }

    template <class _InputIterator>
        _LIBCPP_INLINE_VISIBILITY
        void insert(_InputIterator __first, _InputIterator __last);

#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    void insert(initializer_list<value_type> __il)
        {insert(__il.begin(), __il.end());}

    _LIBCPP_INLINE_VISIBILITY
    pair<iterator, bool> insert(value_type&& __x)
        {return __table_.__insert_unique(_VSTD::move(__x));}

    iterator insert(const_iterator __p, value_type&& __x) {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__p) == this,
            "unordered_map::insert(const_iterator, const value_type&) called with an iterator not"
            " referring to this unordered_map");
#else
        ((void)__p);
#endif
        return __table_.__insert_unique(_VSTD::move(__x)).first;
    }

    template <class _Pp,
              class = typename enable_if<is_constructible<value_type, _Pp>::value>::type>
        _LIBCPP_INLINE_VISIBILITY
        pair<iterator, bool> insert(_Pp&& __x)
            {return __table_.__insert_unique(_VSTD::forward<_Pp>(__x));}

    template <class _Pp,
              class = typename enable_if<is_constructible<value_type, _Pp>::value>::type>
        _LIBCPP_INLINE_VISIBILITY
        iterator insert(const_iterator __p, _Pp&& __x)
        {
#if _LIBCPP_DEBUG_LEVEL >= 2
            _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__p) == this,
                "unordered_map::insert(const_iterator, value_type&&) called with an iterator not"
                " referring to this unordered_map");
#else
          ((void)__p);
#endif
            return insert(_VSTD::forward<_Pp>(__x)).first;
        }

    template <class... _Args>
    _LIBCPP_INLINE_VISIBILITY
    pair<iterator, bool> emplace(_Args&&... __args) {
        return __table_.__emplace_unique(_VSTD::forward<_Args>(__args)...);
    }

    template <class... _Args>
    _LIBCPP_INLINE_VISIBILITY
    iterator emplace_hint(const_iterator __p, _Args&&... __args) {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__p) == this,
            "unordered_map::emplace_hint(const_iterator, args...) called with an iterator not"
            " referring to this unordered_map");
#else
          ((void)__p);
#endif
        return __table_.__emplace_unique(_VSTD::forward<_Args>(__args)...).first;
    }

#endif  // _LIBCPP_CXX03_LANG

#if _LIBCPP_STD_VER > 14
    template <class... _Args>
        _LIBCPP_INLINE_VISIBILITY
        pair<iterator, bool> try_emplace(const key_type& __k, _Args&&... __args)
    {
        return __table_.__emplace_unique_key_args(__k, _VSTD::piecewise_construct,
            _VSTD::forward_as_tuple(__k),
            _VSTD::forward_as_tuple(_VSTD::forward<_Args>(__args)...));
    }

    template <class... _Args>
        _LIBCPP_INLINE_VISIBILITY
        pair<iterator, bool> try_emplace(key_type&& __k, _Args&&... __args)
    {
        return __table_.__emplace_unique_key_args(__k, _VSTD::piecewise_construct,
            _VSTD::forward_as_tuple(_VSTD::move(__k)),
            _VSTD::forward_as_tuple(_VSTD::forward<_Args>(__args)...));
    }

    template <class... _Args>
        _LIBCPP_INLINE_VISIBILITY
        iterator try_emplace(const_iterator __h, const key_type& __k, _Args&&... __args)
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__h) == this,
            "unordered_map::try_emplace(const_iterator, key, args...) called with an iterator not"
            " referring to this unordered_map");
#else
        ((void)__h);
#endif
        return try_emplace(__k, _VSTD::forward<_Args>(__args)...).first;
    }

    template <class... _Args>
        _LIBCPP_INLINE_VISIBILITY
        iterator try_emplace(const_iterator __h, key_type&& __k, _Args&&... __args)
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__h) == this,
            "unordered_map::try_emplace(const_iterator, key, args...) called with an iterator not"
            " referring to this unordered_map");
#else
        ((void)__h);
#endif
        return try_emplace(_VSTD::move(__k), _VSTD::forward<_Args>(__args)...).first;
    }

    template <class _Vp>
        _LIBCPP_INLINE_VISIBILITY
        pair<iterator, bool> insert_or_assign(const key_type& __k, _Vp&& __v)
    {
        pair<iterator, bool> __res = __table_.__emplace_unique_key_args(__k,
            __k, _VSTD::forward<_Vp>(__v));
        if (!__res.second) {
            __res.first->second = _VSTD::forward<_Vp>(__v);
        }
        return __res;
    }

    template <class _Vp>
        _LIBCPP_INLINE_VISIBILITY
        pair<iterator, bool> insert_or_assign(key_type&& __k, _Vp&& __v)
    {
        pair<iterator, bool> __res = __table_.__emplace_unique_key_args(__k,
            _VSTD::move(__k), _VSTD::forward<_Vp>(__v));
        if (!__res.second) {
            __res.first->second = _VSTD::forward<_Vp>(__v);
        }
        return __res;
    }

    template <class _Vp>
        _LIBCPP_INLINE_VISIBILITY
        iterator insert_or_assign(const_iterator, const key_type& __k, _Vp&& __v)
     {
          // FIXME: Add debug mode checking for the iterator input
          return insert_or_assign(__k, _VSTD::forward<_Vp>(__v)).first;
     }

    template <class _Vp>
        _LIBCPP_INLINE_VISIBILITY
        iterator insert_or_assign(const_iterator, key_type&& __k, _Vp&& __v)
     {
        // FIXME: Add debug mode checking for the iterator input
        return insert_or_assign(_VSTD::move(__k), _VSTD::forward<_Vp>(__v)).first;
     }
#endif // _LIBCPP_STD_VER > 14

    _LIBCPP_INLINE_VISIBILITY
    iterator erase(const_iterator __p) {return __table_.erase(__p.__i_);}
    _LIBCPP_INLINE_VISIBILITY
    iterator erase(iterator __p)       {return __table_.erase(__p.__i_);}
    _LIBCPP_INLINE_VISIBILITY
    size_type erase(const key_type& __k) {return __table_.__erase_unique(__k);}
    _LIBCPP_INLINE_VISIBILITY
    iterator erase(const_iterator __first, const_iterator __last)
        {return __table_.erase(__first.__i_, __last.__i_);}
    _LIBCPP_INLINE_VISIBILITY
    void clear() _NOEXCEPT {__table_.clear();}

    _LIBCPP_INLINE_VISIBILITY
    void swap(unordered_map& __u)
        _NOEXCEPT_(__is_nothrow_swappable<__table>::value)
        { __table_.swap(__u.__table_);}

    _LIBCPP_INLINE_VISIBILITY
    hasher hash_function() const
        {return __table_.hash_function().hash_function();}
    _LIBCPP_INLINE_VISIBILITY
    key_equal key_eq() const
        {return __table_.key_eq().key_eq();}

    _LIBCPP_INLINE_VISIBILITY
    iterator       find(const key_type& __k)       {return __table_.find(__k);}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator find(const key_type& __k) const {return __table_.find(__k);}
    _LIBCPP_INLINE_VISIBILITY
    size_type count(const key_type& __k) const {return __table_.__count_unique(__k);}
    _LIBCPP_INLINE_VISIBILITY
    pair<iterator, iterator>             equal_range(const key_type& __k)
        {return __table_.__equal_range_unique(__k);}
    _LIBCPP_INLINE_VISIBILITY
    pair<const_iterator, const_iterator> equal_range(const key_type& __k) const
        {return __table_.__equal_range_unique(__k);}

    mapped_type& operator[](const key_type& __k);
#ifndef _LIBCPP_CXX03_LANG
    mapped_type& operator[](key_type&& __k);
#endif

    mapped_type&       at(const key_type& __k);
    const mapped_type& at(const key_type& __k) const;

    _LIBCPP_INLINE_VISIBILITY
    size_type bucket_count() const _NOEXCEPT {return __table_.bucket_count();}
    _LIBCPP_INLINE_VISIBILITY
    size_type max_bucket_count() const _NOEXCEPT {return __table_.max_bucket_count();}

    _LIBCPP_INLINE_VISIBILITY
    size_type bucket_size(size_type __n) const
        {return __table_.bucket_size(__n);}
    _LIBCPP_INLINE_VISIBILITY
    size_type bucket(const key_type& __k) const {return __table_.bucket(__k);}

    _LIBCPP_INLINE_VISIBILITY
    local_iterator       begin(size_type __n)        {return __table_.begin(__n);}
    _LIBCPP_INLINE_VISIBILITY
    local_iterator       end(size_type __n)          {return __table_.end(__n);}
    _LIBCPP_INLINE_VISIBILITY
    const_local_iterator begin(size_type __n) const  {return __table_.cbegin(__n);}
    _LIBCPP_INLINE_VISIBILITY
    const_local_iterator end(size_type __n) const    {return __table_.cend(__n);}
    _LIBCPP_INLINE_VISIBILITY
    const_local_iterator cbegin(size_type __n) const {return __table_.cbegin(__n);}
    _LIBCPP_INLINE_VISIBILITY
    const_local_iterator cend(size_type __n) const   {return __table_.cend(__n);}

    _LIBCPP_INLINE_VISIBILITY
    float load_factor() const _NOEXCEPT {return __table_.load_factor();}
    _LIBCPP_INLINE_VISIBILITY
    float max_load_factor() const _NOEXCEPT {return __table_.max_load_factor();}
    _LIBCPP_INLINE_VISIBILITY
    void max_load_factor(float __mlf) {__table_.max_load_factor(__mlf);}
    _LIBCPP_INLINE_VISIBILITY
    void rehash(size_type __n) {__table_.rehash(__n);}
    _LIBCPP_INLINE_VISIBILITY
    void reserve(size_type __n) {__table_.reserve(__n);}

#if _LIBCPP_DEBUG_LEVEL >= 2

    bool __dereferenceable(const const_iterator* __i) const
        {return __table_.__dereferenceable(&__i->__i_);}
    bool __decrementable(const const_iterator* __i) const
        {return __table_.__decrementable(&__i->__i_);}
    bool __addable(const const_iterator* __i, ptrdiff_t __n) const
        {return __table_.__addable(&__i->__i_, __n);}
    bool __subscriptable(const const_iterator* __i, ptrdiff_t __n) const
        {return __table_.__addable(&__i->__i_, __n);}

#endif  // _LIBCPP_DEBUG_LEVEL >= 2

private:

#ifdef _LIBCPP_CXX03_LANG
    __node_holder __construct_node_with_key(const key_type& __k);
#endif
};

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_map(
        size_type __n, const hasher& __hf, const key_equal& __eql)
    : __table_(__hf, __eql)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    __table_.rehash(__n);
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_map(
        size_type __n, const hasher& __hf, const key_equal& __eql,
        const allocator_type& __a)
    : __table_(__hf, __eql, typename __table::allocator_type(__a))
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    __table_.rehash(__n);
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
inline
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_map(
        const allocator_type& __a)
    : __table_(typename __table::allocator_type(__a))
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
template <class _InputIterator>
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_map(
        _InputIterator __first, _InputIterator __last)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    insert(__first, __last);
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
template <class _InputIterator>
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_map(
        _InputIterator __first, _InputIterator __last, size_type __n,
        const hasher& __hf, const key_equal& __eql)
    : __table_(__hf, __eql)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    __table_.rehash(__n);
    insert(__first, __last);
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
template <class _InputIterator>
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_map(
        _InputIterator __first, _InputIterator __last, size_type __n,
        const hasher& __hf, const key_equal& __eql, const allocator_type& __a)
    : __table_(__hf, __eql, typename __table::allocator_type(__a))
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    __table_.rehash(__n);
    insert(__first, __last);
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_map(
        const unordered_map& __u)
    : __table_(__u.__table_)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    __table_.rehash(__u.bucket_count());
    insert(__u.begin(), __u.end());
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_map(
        const unordered_map& __u, const allocator_type& __a)
    : __table_(__u.__table_, typename __table::allocator_type(__a))
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    __table_.rehash(__u.bucket_count());
    insert(__u.begin(), __u.end());
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
inline
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_map(
        unordered_map&& __u)
    _NOEXCEPT_(is_nothrow_move_constructible<__table>::value)
    : __table_(_VSTD::move(__u.__table_))
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
    __get_db()->swap(this, &__u);
#endif
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_map(
        unordered_map&& __u, const allocator_type& __a)
    : __table_(_VSTD::move(__u.__table_), typename __table::allocator_type(__a))
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    if (__a != __u.get_allocator())
    {
        iterator __i = __u.begin();
        while (__u.size() != 0) {
            __table_.__emplace_unique(_VSTD::move(
                __u.__table_.remove((__i++).__i_)->__value_.__nc));
        }
    }
#if _LIBCPP_DEBUG_LEVEL >= 2
    else
        __get_db()->swap(this, &__u);
#endif
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_map(
        initializer_list<value_type> __il)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    insert(__il.begin(), __il.end());
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_map(
        initializer_list<value_type> __il, size_type __n, const hasher& __hf,
        const key_equal& __eql)
    : __table_(__hf, __eql)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    __table_.rehash(__n);
    insert(__il.begin(), __il.end());
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_map(
        initializer_list<value_type> __il, size_type __n, const hasher& __hf,
        const key_equal& __eql, const allocator_type& __a)
    : __table_(__hf, __eql, typename __table::allocator_type(__a))
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    __table_.rehash(__n);
    insert(__il.begin(), __il.end());
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
inline
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>&
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::operator=(unordered_map&& __u)
    _NOEXCEPT_(is_nothrow_move_assignable<__table>::value)
{
    __table_ = _VSTD::move(__u.__table_);
    return *this;
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
inline
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>&
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::operator=(
        initializer_list<value_type> __il)
{
    __table_.__assign_unique(__il.begin(), __il.end());
    return *this;
}

#endif  // _LIBCPP_CXX03_LANG

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
template <class _InputIterator>
inline
void
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::insert(_InputIterator __first,
                                                       _InputIterator __last)
{
    for (; __first != __last; ++__first)
        __table_.__insert_unique(*__first);
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
_Tp&
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::operator[](const key_type& __k)
{
    return __table_.__emplace_unique_key_args(__k,
        std::piecewise_construct, std::forward_as_tuple(__k),
                                  std::forward_as_tuple()).first->__cc.second;
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
_Tp&
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::operator[](key_type&& __k)
{
    return __table_.__emplace_unique_key_args(__k,
        std::piecewise_construct, std::forward_as_tuple(std::move(__k)),
                                  std::forward_as_tuple()).first->__cc.second;
}
#else // _LIBCPP_CXX03_LANG

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
typename unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::__node_holder
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::__construct_node_with_key(const key_type& __k)
{
    __node_allocator& __na = __table_.__node_alloc();
    __node_holder __h(__node_traits::allocate(__na, 1), _Dp(__na));
    __node_traits::construct(__na, _VSTD::addressof(__h->__value_.__cc.first), __k);
    __h.get_deleter().__first_constructed = true;
    __node_traits::construct(__na, _VSTD::addressof(__h->__value_.__cc.second));
    __h.get_deleter().__second_constructed = true;
    return _LIBCPP_EXPLICIT_MOVE(__h);  // explicitly moved for C++03
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
_Tp&
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::operator[](const key_type& __k)
{
    iterator __i = find(__k);
    if (__i != end())
        return __i->second;
    __node_holder __h = __construct_node_with_key(__k);
    pair<iterator, bool> __r = __table_.__node_insert_unique(__h.get());
    __h.release();
    return __r.first->second;
}

#endif  // _LIBCPP_CXX03_MODE

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
_Tp&
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::at(const key_type& __k)
{
    iterator __i = find(__k);
#ifndef _LIBCPP_NO_EXCEPTIONS
    if (__i == end())
        throw out_of_range("unordered_map::at: key not found");
#endif  // _LIBCPP_NO_EXCEPTIONS
    return __i->second;
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
const _Tp&
unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::at(const key_type& __k) const
{
    const_iterator __i = find(__k);
#ifndef _LIBCPP_NO_EXCEPTIONS
    if (__i == end())
        throw out_of_range("unordered_map::at: key not found");
#endif  // _LIBCPP_NO_EXCEPTIONS
    return __i->second;
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
void
swap(unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>& __x,
     unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>& __y)
    _NOEXCEPT_(_NOEXCEPT_(__x.swap(__y)))
{
    __x.swap(__y);
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
bool
operator==(const unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>& __x,
           const unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>& __y)
{
    if (__x.size() != __y.size())
        return false;
    typedef typename unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::const_iterator
                                                                 const_iterator;
    for (const_iterator __i = __x.begin(), __ex = __x.end(), __ey = __y.end();
            __i != __ex; ++__i)
    {
        const_iterator __j = __y.find(__i->first);
        if (__j == __ey || !(*__i == *__j))
            return false;
    }
    return true;
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator!=(const unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>& __x,
           const unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>& __y)
{
    return !(__x == __y);
}

template <class _Key, class _Tp, class _Hash = hash<_Key>, class _Pred = equal_to<_Key>,
          class _Alloc = allocator<pair<const _Key, _Tp> > >
class _LIBCPP_TEMPLATE_VIS unordered_multimap
{
public:
    // types
    typedef _Key                                           key_type;
    typedef _Tp                                            mapped_type;
    typedef _Hash                                          hasher;
    typedef _Pred                                          key_equal;
    typedef _Alloc                                         allocator_type;
    typedef pair<const key_type, mapped_type>              value_type;
    typedef pair<key_type, mapped_type>                    __nc_value_type;
    typedef value_type&                                    reference;
    typedef const value_type&                              const_reference;
    static_assert((is_same<value_type, typename allocator_type::value_type>::value),
                  "Invalid allocator::value_type");

private:
    typedef __hash_value_type<key_type, mapped_type>                 __value_type;
    typedef __unordered_map_hasher<key_type, __value_type, hasher>   __hasher;
    typedef __unordered_map_equal<key_type, __value_type, key_equal> __key_equal;
    typedef typename __rebind_alloc_helper<allocator_traits<allocator_type>,
                                                 __value_type>::type __allocator_type;

    typedef __hash_table<__value_type, __hasher,
                         __key_equal,  __allocator_type>   __table;

    __table __table_;

    typedef typename __table::_NodeTypes                   _NodeTypes;
    typedef typename __table::__node_traits                __node_traits;
    typedef typename __table::__node_allocator             __node_allocator;
    typedef typename __table::__node                       __node;
    typedef __hash_map_node_destructor<__node_allocator>   _Dp;
    typedef unique_ptr<__node, _Dp>                         __node_holder;
    typedef allocator_traits<allocator_type>               __alloc_traits;
    static_assert((is_same<typename __node_traits::size_type,
                          typename __alloc_traits::size_type>::value),
                 "Allocator uses different size_type for different types");
public:
    typedef typename __alloc_traits::pointer         pointer;
    typedef typename __alloc_traits::const_pointer   const_pointer;
    typedef typename __table::size_type              size_type;
    typedef typename __table::difference_type        difference_type;

    typedef __hash_map_iterator<typename __table::iterator>       iterator;
    typedef __hash_map_const_iterator<typename __table::const_iterator> const_iterator;
    typedef __hash_map_iterator<typename __table::local_iterator> local_iterator;
    typedef __hash_map_const_iterator<typename __table::const_local_iterator> const_local_iterator;

    _LIBCPP_INLINE_VISIBILITY
    unordered_multimap()
        _NOEXCEPT_(is_nothrow_default_constructible<__table>::value)
        {
#if _LIBCPP_DEBUG_LEVEL >= 2
            __get_db()->__insert_c(this);
#endif
        }
    explicit unordered_multimap(size_type __n, const hasher& __hf = hasher(),
                                const key_equal& __eql = key_equal());
    unordered_multimap(size_type __n, const hasher& __hf,
                                const key_equal& __eql,
                                const allocator_type& __a);
    template <class _InputIterator>
        unordered_multimap(_InputIterator __first, _InputIterator __last);
    template <class _InputIterator>
        unordered_multimap(_InputIterator __first, _InputIterator __last,
                      size_type __n, const hasher& __hf = hasher(),
                      const key_equal& __eql = key_equal());
    template <class _InputIterator>
        unordered_multimap(_InputIterator __first, _InputIterator __last,
                      size_type __n, const hasher& __hf,
                      const key_equal& __eql,
                      const allocator_type& __a);
    _LIBCPP_INLINE_VISIBILITY
    explicit unordered_multimap(const allocator_type& __a);
    unordered_multimap(const unordered_multimap& __u);
    unordered_multimap(const unordered_multimap& __u, const allocator_type& __a);
#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    unordered_multimap(unordered_multimap&& __u)
        _NOEXCEPT_(is_nothrow_move_constructible<__table>::value);
    unordered_multimap(unordered_multimap&& __u, const allocator_type& __a);
    unordered_multimap(initializer_list<value_type> __il);
    unordered_multimap(initializer_list<value_type> __il, size_type __n,
                       const hasher& __hf = hasher(),
                       const key_equal& __eql = key_equal());
    unordered_multimap(initializer_list<value_type> __il, size_type __n,
                       const hasher& __hf, const key_equal& __eql,
                       const allocator_type& __a);
#endif  // _LIBCPP_CXX03_LANG
#if _LIBCPP_STD_VER > 11
    _LIBCPP_INLINE_VISIBILITY
    unordered_multimap(size_type __n, const allocator_type& __a)
      : unordered_multimap(__n, hasher(), key_equal(), __a) {}
    _LIBCPP_INLINE_VISIBILITY
    unordered_multimap(size_type __n, const hasher& __hf, const allocator_type& __a)
      : unordered_multimap(__n, __hf, key_equal(), __a) {}
    template <class _InputIterator>
    _LIBCPP_INLINE_VISIBILITY
      unordered_multimap(_InputIterator __first, _InputIterator __last, size_type __n, const allocator_type& __a)
      : unordered_multimap(__first, __last, __n, hasher(), key_equal(), __a) {}
    template <class _InputIterator>
    _LIBCPP_INLINE_VISIBILITY
      unordered_multimap(_InputIterator __first, _InputIterator __last, size_type __n, const hasher& __hf,
        const allocator_type& __a)
      : unordered_multimap(__first, __last, __n, __hf, key_equal(), __a) {}
    _LIBCPP_INLINE_VISIBILITY
    unordered_multimap(initializer_list<value_type> __il, size_type __n, const allocator_type& __a)
      : unordered_multimap(__il, __n, hasher(), key_equal(), __a) {}
    _LIBCPP_INLINE_VISIBILITY
    unordered_multimap(initializer_list<value_type> __il, size_type __n, const hasher& __hf,
      const allocator_type& __a)
      : unordered_multimap(__il, __n, __hf, key_equal(), __a) {}
#endif
    // ~unordered_multimap() = default;
    _LIBCPP_INLINE_VISIBILITY
    unordered_multimap& operator=(const unordered_multimap& __u)
    {
#ifndef _LIBCPP_CXX03_LANG
        __table_ = __u.__table_;
#else
        if (this != &__u) {
            __table_.clear();
            __table_.hash_function() = __u.__table_.hash_function();
            __table_.key_eq() = __u.__table_.key_eq();
            __table_.max_load_factor() = __u.__table_.max_load_factor();
            __table_.__copy_assign_alloc(__u.__table_);
            insert(__u.begin(), __u.end());
        }
#endif
        return *this;
    }
#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    unordered_multimap& operator=(unordered_multimap&& __u)
        _NOEXCEPT_(is_nothrow_move_assignable<__table>::value);
    _LIBCPP_INLINE_VISIBILITY
    unordered_multimap& operator=(initializer_list<value_type> __il);
#endif  // _LIBCPP_CXX03_LANG

    _LIBCPP_INLINE_VISIBILITY
    allocator_type get_allocator() const _NOEXCEPT
        {return allocator_type(__table_.__node_alloc());}

    _LIBCPP_INLINE_VISIBILITY
    bool      empty() const _NOEXCEPT {return __table_.size() == 0;}
    _LIBCPP_INLINE_VISIBILITY
    size_type size() const _NOEXCEPT  {return __table_.size();}
    _LIBCPP_INLINE_VISIBILITY
    size_type max_size() const _NOEXCEPT {return __table_.max_size();}

    _LIBCPP_INLINE_VISIBILITY
    iterator       begin() _NOEXCEPT        {return __table_.begin();}
    _LIBCPP_INLINE_VISIBILITY
    iterator       end() _NOEXCEPT          {return __table_.end();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator begin()  const _NOEXCEPT {return __table_.begin();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator end()    const _NOEXCEPT {return __table_.end();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator cbegin() const _NOEXCEPT {return __table_.begin();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator cend()   const _NOEXCEPT {return __table_.end();}

    _LIBCPP_INLINE_VISIBILITY
    iterator insert(const value_type& __x) {return __table_.__insert_multi(__x);}

    _LIBCPP_INLINE_VISIBILITY
    iterator insert(const_iterator __p, const value_type& __x)
        {return __table_.__insert_multi(__p.__i_, __x);}

    template <class _InputIterator>
    _LIBCPP_INLINE_VISIBILITY
    void insert(_InputIterator __first, _InputIterator __last);

#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    void insert(initializer_list<value_type> __il)
        {insert(__il.begin(), __il.end());}
    _LIBCPP_INLINE_VISIBILITY
    iterator insert(value_type&& __x) {return __table_.__insert_multi(_VSTD::move(__x));}

    _LIBCPP_INLINE_VISIBILITY
    iterator insert(const_iterator __p, value_type&& __x)
        {return __table_.__insert_multi(__p.__i_, _VSTD::move(__x));}

    template <class _Pp,
              class = typename enable_if<is_constructible<value_type, _Pp>::value>::type>
    _LIBCPP_INLINE_VISIBILITY
    iterator insert(_Pp&& __x)
        {return __table_.__insert_multi(_VSTD::forward<_Pp>(__x));}

    template <class _Pp,
              class = typename enable_if<is_constructible<value_type, _Pp>::value>::type>
    _LIBCPP_INLINE_VISIBILITY
    iterator insert(const_iterator __p, _Pp&& __x)
        {return __table_.__insert_multi(__p.__i_, _VSTD::forward<_Pp>(__x));}

    template <class... _Args>
    iterator emplace(_Args&&... __args) {
        return __table_.__emplace_multi(_VSTD::forward<_Args>(__args)...);
    }

    template <class... _Args>
    iterator emplace_hint(const_iterator __p, _Args&&... __args) {
        return __table_.__emplace_hint_multi(__p.__i_, _VSTD::forward<_Args>(__args)...);
    }
#endif  // _LIBCPP_CXX03_LANG


    _LIBCPP_INLINE_VISIBILITY
    iterator erase(const_iterator __p) {return __table_.erase(__p.__i_);}
    _LIBCPP_INLINE_VISIBILITY
    iterator erase(iterator __p)       {return __table_.erase(__p.__i_);}
    _LIBCPP_INLINE_VISIBILITY
    size_type erase(const key_type& __k) {return __table_.__erase_multi(__k);}
    _LIBCPP_INLINE_VISIBILITY
    iterator erase(const_iterator __first, const_iterator __last)
        {return __table_.erase(__first.__i_, __last.__i_);}
    _LIBCPP_INLINE_VISIBILITY
    void clear() _NOEXCEPT {__table_.clear();}

    _LIBCPP_INLINE_VISIBILITY
    void swap(unordered_multimap& __u)
        _NOEXCEPT_(__is_nothrow_swappable<__table>::value)
        {__table_.swap(__u.__table_);}

    _LIBCPP_INLINE_VISIBILITY
    hasher hash_function() const
        {return __table_.hash_function().hash_function();}
    _LIBCPP_INLINE_VISIBILITY
    key_equal key_eq() const
        {return __table_.key_eq().key_eq();}

    _LIBCPP_INLINE_VISIBILITY
    iterator       find(const key_type& __k)       {return __table_.find(__k);}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator find(const key_type& __k) const {return __table_.find(__k);}
    _LIBCPP_INLINE_VISIBILITY
    size_type count(const key_type& __k) const {return __table_.__count_multi(__k);}
    _LIBCPP_INLINE_VISIBILITY
    pair<iterator, iterator>             equal_range(const key_type& __k)
        {return __table_.__equal_range_multi(__k);}
    _LIBCPP_INLINE_VISIBILITY
    pair<const_iterator, const_iterator> equal_range(const key_type& __k) const
        {return __table_.__equal_range_multi(__k);}

    _LIBCPP_INLINE_VISIBILITY
    size_type bucket_count() const _NOEXCEPT {return __table_.bucket_count();}
    _LIBCPP_INLINE_VISIBILITY
    size_type max_bucket_count() const _NOEXCEPT
        {return __table_.max_bucket_count();}

    _LIBCPP_INLINE_VISIBILITY
    size_type bucket_size(size_type __n) const
        {return __table_.bucket_size(__n);}
    _LIBCPP_INLINE_VISIBILITY
    size_type bucket(const key_type& __k) const {return __table_.bucket(__k);}

    _LIBCPP_INLINE_VISIBILITY
    local_iterator       begin(size_type __n)        {return __table_.begin(__n);}
    _LIBCPP_INLINE_VISIBILITY
    local_iterator       end(size_type __n)          {return __table_.end(__n);}
    _LIBCPP_INLINE_VISIBILITY
    const_local_iterator begin(size_type __n) const  {return __table_.cbegin(__n);}
    _LIBCPP_INLINE_VISIBILITY
    const_local_iterator end(size_type __n) const    {return __table_.cend(__n);}
    _LIBCPP_INLINE_VISIBILITY
    const_local_iterator cbegin(size_type __n) const {return __table_.cbegin(__n);}
    _LIBCPP_INLINE_VISIBILITY
    const_local_iterator cend(size_type __n) const   {return __table_.cend(__n);}

    _LIBCPP_INLINE_VISIBILITY
    float load_factor() const _NOEXCEPT {return __table_.load_factor();}
    _LIBCPP_INLINE_VISIBILITY
    float max_load_factor() const _NOEXCEPT {return __table_.max_load_factor();}
    _LIBCPP_INLINE_VISIBILITY
    void max_load_factor(float __mlf) {__table_.max_load_factor(__mlf);}
    _LIBCPP_INLINE_VISIBILITY
    void rehash(size_type __n) {__table_.rehash(__n);}
    _LIBCPP_INLINE_VISIBILITY
    void reserve(size_type __n) {__table_.reserve(__n);}

#if _LIBCPP_DEBUG_LEVEL >= 2

    bool __dereferenceable(const const_iterator* __i) const
        {return __table_.__dereferenceable(&__i->__i_);}
    bool __decrementable(const const_iterator* __i) const
        {return __table_.__decrementable(&__i->__i_);}
    bool __addable(const const_iterator* __i, ptrdiff_t __n) const
        {return __table_.__addable(&__i->__i_, __n);}
    bool __subscriptable(const const_iterator* __i, ptrdiff_t __n) const
        {return __table_.__addable(&__i->__i_, __n);}

#endif  // _LIBCPP_DEBUG_LEVEL >= 2


};

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_multimap(
        size_type __n, const hasher& __hf, const key_equal& __eql)
    : __table_(__hf, __eql)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    __table_.rehash(__n);
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_multimap(
        size_type __n, const hasher& __hf, const key_equal& __eql,
        const allocator_type& __a)
    : __table_(__hf, __eql, typename __table::allocator_type(__a))
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    __table_.rehash(__n);
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
template <class _InputIterator>
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_multimap(
        _InputIterator __first, _InputIterator __last)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    insert(__first, __last);
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
template <class _InputIterator>
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_multimap(
        _InputIterator __first, _InputIterator __last, size_type __n,
        const hasher& __hf, const key_equal& __eql)
    : __table_(__hf, __eql)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    __table_.rehash(__n);
    insert(__first, __last);
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
template <class _InputIterator>
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_multimap(
        _InputIterator __first, _InputIterator __last, size_type __n,
        const hasher& __hf, const key_equal& __eql, const allocator_type& __a)
    : __table_(__hf, __eql, typename __table::allocator_type(__a))
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    __table_.rehash(__n);
    insert(__first, __last);
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
inline
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_multimap(
        const allocator_type& __a)
    : __table_(typename __table::allocator_type(__a))
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_multimap(
        const unordered_multimap& __u)
    : __table_(__u.__table_)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    __table_.rehash(__u.bucket_count());
    insert(__u.begin(), __u.end());
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_multimap(
        const unordered_multimap& __u, const allocator_type& __a)
    : __table_(__u.__table_, typename __table::allocator_type(__a))
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    __table_.rehash(__u.bucket_count());
    insert(__u.begin(), __u.end());
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
inline
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_multimap(
        unordered_multimap&& __u)
    _NOEXCEPT_(is_nothrow_move_constructible<__table>::value)
    : __table_(_VSTD::move(__u.__table_))
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
    __get_db()->swap(this, &__u);
#endif
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_multimap(
        unordered_multimap&& __u, const allocator_type& __a)
    : __table_(_VSTD::move(__u.__table_), typename __table::allocator_type(__a))
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    if (__a != __u.get_allocator())
    {
        iterator __i = __u.begin();
        while (__u.size() != 0)
        {
            __table_.__insert_multi(
                      _VSTD::move(__u.__table_.remove((__i++).__i_)->__value_.__nc)
                                   );
        }
    }
#if _LIBCPP_DEBUG_LEVEL >= 2
    else
        __get_db()->swap(this, &__u);
#endif
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_multimap(
        initializer_list<value_type> __il)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    insert(__il.begin(), __il.end());
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_multimap(
        initializer_list<value_type> __il, size_type __n, const hasher& __hf,
        const key_equal& __eql)
    : __table_(__hf, __eql)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    __table_.rehash(__n);
    insert(__il.begin(), __il.end());
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_multimap(
        initializer_list<value_type> __il, size_type __n, const hasher& __hf,
        const key_equal& __eql, const allocator_type& __a)
    : __table_(__hf, __eql, typename __table::allocator_type(__a))
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    __table_.rehash(__n);
    insert(__il.begin(), __il.end());
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
inline
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>&
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>::operator=(unordered_multimap&& __u)
    _NOEXCEPT_(is_nothrow_move_assignable<__table>::value)
{
    __table_ = _VSTD::move(__u.__table_);
    return *this;
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
inline
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>&
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>::operator=(
        initializer_list<value_type> __il)
{
    __table_.__assign_multi(__il.begin(), __il.end());
    return *this;
}

#endif  // _LIBCPP_CXX03_LANG



template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
template <class _InputIterator>
inline
void
unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>::insert(_InputIterator __first,
                                                            _InputIterator __last)
{
    for (; __first != __last; ++__first)
        __table_.__insert_multi(*__first);
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
void
swap(unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>& __x,
     unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>& __y)
    _NOEXCEPT_(_NOEXCEPT_(__x.swap(__y)))
{
    __x.swap(__y);
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
bool
operator==(const unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>& __x,
           const unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>& __y)
{
    if (__x.size() != __y.size())
        return false;
    typedef typename unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>::const_iterator
                                                                 const_iterator;
    typedef pair<const_iterator, const_iterator> _EqRng;
    for (const_iterator __i = __x.begin(), __ex = __x.end(); __i != __ex;)
    {
        _EqRng __xeq = __x.equal_range(__i->first);
        _EqRng __yeq = __y.equal_range(__i->first);
        if (_VSTD::distance(__xeq.first, __xeq.second) !=
            _VSTD::distance(__yeq.first, __yeq.second) ||
                  !_VSTD::is_permutation(__xeq.first, __xeq.second, __yeq.first))
            return false;
        __i = __xeq.second;
    }
    return true;
}

template <class _Key, class _Tp, class _Hash, class _Pred, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator!=(const unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>& __x,
           const unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>& __y)
{
    return !(__x == __y);
}

_LIBCPP_END_NAMESPACE_STD

#endif  // _LIBCPP_UNORDERED_MAP
