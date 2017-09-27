// -*- C++ -*-
//===---------------------------- list ------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_LIST
#define _LIBCPP_LIST

#include <__config.hpp>

#include <memory.hpp>
#include <limits.hpp>
#include <initializer_list.hpp>
#include <iterator.hpp>
#include <algorithm.hpp>
#include <type_traits.hpp>

#include <__debug.hpp>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_PUSH_MACROS
#include <__undef_macros.hpp>


_LIBCPP_BEGIN_NAMESPACE_STD

template <class _Tp, class _VoidPtr> struct __list_node;
template <class _Tp, class _VoidPtr> struct __list_node_base;

template <class _Tp, class _VoidPtr>
struct __list_node_pointer_traits {
  typedef typename __rebind_pointer<_VoidPtr, __list_node<_Tp, _VoidPtr> >::type
        __node_pointer;
  typedef typename __rebind_pointer<_VoidPtr, __list_node_base<_Tp, _VoidPtr> >::type
        __base_pointer;

#if defined(_LIBCPP_ABI_LIST_REMOVE_NODE_POINTER_UB)
  typedef __base_pointer __link_pointer;
#else
  typedef typename conditional<
          is_pointer<_VoidPtr>::value,
          __base_pointer,
          __node_pointer
  >::type __link_pointer;
#endif

  typedef typename conditional<
          is_same<__link_pointer, __node_pointer>::value,
          __base_pointer,
          __node_pointer
  >::type __non_link_pointer;

  static _LIBCPP_INLINE_VISIBILITY
  __link_pointer __unsafe_link_pointer_cast(__link_pointer __p) {
      return __p;
  }

  static _LIBCPP_INLINE_VISIBILITY
  __link_pointer __unsafe_link_pointer_cast(__non_link_pointer __p) {
      return static_cast<__link_pointer>(static_cast<_VoidPtr>(__p));
  }

};

template <class _Tp, class _VoidPtr>
struct __list_node_base
{
    typedef __list_node_pointer_traits<_Tp, _VoidPtr> _NodeTraits;
    typedef typename _NodeTraits::__node_pointer __node_pointer;
    typedef typename _NodeTraits::__base_pointer __base_pointer;
    typedef typename _NodeTraits::__link_pointer __link_pointer;

    __link_pointer __prev_;
    __link_pointer __next_;

    _LIBCPP_INLINE_VISIBILITY
    __list_node_base() : __prev_(_NodeTraits::__unsafe_link_pointer_cast(__self())),
                         __next_(_NodeTraits::__unsafe_link_pointer_cast(__self())) {}

    _LIBCPP_INLINE_VISIBILITY
    __base_pointer __self() {
        return pointer_traits<__base_pointer>::pointer_to(*this);
    }

    _LIBCPP_INLINE_VISIBILITY
    __node_pointer __as_node() {
        return static_cast<__node_pointer>(__self());
    }
};

template <class _Tp, class _VoidPtr>
struct __list_node
    : public __list_node_base<_Tp, _VoidPtr>
{
    _Tp __value_;

    typedef __list_node_base<_Tp, _VoidPtr> __base;
    typedef typename __base::__link_pointer __link_pointer;

    _LIBCPP_INLINE_VISIBILITY
    __link_pointer __as_link() {
        return static_cast<__link_pointer>(__base::__self());
    }
};

template <class _Tp, class _Alloc = allocator<_Tp> > class _LIBCPP_TEMPLATE_VIS list;
template <class _Tp, class _Alloc> class __list_imp;
template <class _Tp, class _VoidPtr> class _LIBCPP_TEMPLATE_VIS __list_const_iterator;

template <class _Tp, class _VoidPtr>
class _LIBCPP_TEMPLATE_VIS __list_iterator
{
    typedef __list_node_pointer_traits<_Tp, _VoidPtr> _NodeTraits;
    typedef typename _NodeTraits::__link_pointer __link_pointer;

    __link_pointer __ptr_;

#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_INLINE_VISIBILITY
    explicit __list_iterator(__link_pointer __p, const void* __c) _NOEXCEPT
        : __ptr_(__p)
    {
        __get_db()->__insert_ic(this, __c);
    }
#else
    _LIBCPP_INLINE_VISIBILITY
    explicit __list_iterator(__link_pointer __p) _NOEXCEPT : __ptr_(__p) {}
#endif



    template<class, class> friend class list;
    template<class, class> friend class __list_imp;
    template<class, class> friend class __list_const_iterator;
public:
    typedef bidirectional_iterator_tag       iterator_category;
    typedef _Tp                              value_type;
    typedef value_type&                      reference;
    typedef typename __rebind_pointer<_VoidPtr, value_type>::type pointer;
    typedef typename pointer_traits<pointer>::difference_type difference_type;

    _LIBCPP_INLINE_VISIBILITY
    __list_iterator() _NOEXCEPT : __ptr_(nullptr)
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        __get_db()->__insert_i(this);
#endif
    }

#if _LIBCPP_DEBUG_LEVEL >= 2

    _LIBCPP_INLINE_VISIBILITY
    __list_iterator(const __list_iterator& __p)
        : __ptr_(__p.__ptr_)
    {
        __get_db()->__iterator_copy(this, &__p);
    }

    _LIBCPP_INLINE_VISIBILITY
    ~__list_iterator()
    {
        __get_db()->__erase_i(this);
    }

    _LIBCPP_INLINE_VISIBILITY
    __list_iterator& operator=(const __list_iterator& __p)
    {
        if (this != &__p)
        {
            __get_db()->__iterator_copy(this, &__p);
            __ptr_ = __p.__ptr_;
        }
        return *this;
    }

#endif  // _LIBCPP_DEBUG_LEVEL >= 2

    _LIBCPP_INLINE_VISIBILITY
    reference operator*() const
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__dereferenceable(this),
                       "Attempted to dereference a non-dereferenceable list::iterator");
#endif
        return __ptr_->__as_node()->__value_;
    }
    _LIBCPP_INLINE_VISIBILITY
    pointer operator->() const
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__dereferenceable(this),
                       "Attempted to dereference a non-dereferenceable list::iterator");
#endif
        return pointer_traits<pointer>::pointer_to(__ptr_->__as_node()->__value_);
    }

    _LIBCPP_INLINE_VISIBILITY
    __list_iterator& operator++()
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__dereferenceable(this),
                       "Attempted to increment non-incrementable list::iterator");
#endif
        __ptr_ = __ptr_->__next_;
        return *this;
    }
    _LIBCPP_INLINE_VISIBILITY
    __list_iterator operator++(int) {__list_iterator __t(*this); ++(*this); return __t;}

    _LIBCPP_INLINE_VISIBILITY
    __list_iterator& operator--()
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__decrementable(this),
                       "Attempted to decrement non-decrementable list::iterator");
#endif
        __ptr_ = __ptr_->__prev_;
        return *this;
    }
    _LIBCPP_INLINE_VISIBILITY
    __list_iterator operator--(int) {__list_iterator __t(*this); --(*this); return __t;}

    friend _LIBCPP_INLINE_VISIBILITY
    bool operator==(const __list_iterator& __x, const __list_iterator& __y)
    {
        return __x.__ptr_ == __y.__ptr_;
    }
    friend _LIBCPP_INLINE_VISIBILITY
     bool operator!=(const __list_iterator& __x, const __list_iterator& __y)
        {return !(__x == __y);}
};

template <class _Tp, class _VoidPtr>
class _LIBCPP_TEMPLATE_VIS __list_const_iterator
{
    typedef __list_node_pointer_traits<_Tp, _VoidPtr> _NodeTraits;
    typedef typename _NodeTraits::__link_pointer __link_pointer;

    __link_pointer __ptr_;

#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_INLINE_VISIBILITY
    explicit __list_const_iterator(__link_pointer __p, const void* __c) _NOEXCEPT
        : __ptr_(__p)
    {
        __get_db()->__insert_ic(this, __c);
    }
#else
    _LIBCPP_INLINE_VISIBILITY
    explicit __list_const_iterator(__link_pointer __p) _NOEXCEPT : __ptr_(__p) {}
#endif

    template<class, class> friend class list;
    template<class, class> friend class __list_imp;
public:
    typedef bidirectional_iterator_tag       iterator_category;
    typedef _Tp                              value_type;
    typedef const value_type&                reference;
    typedef typename __rebind_pointer<_VoidPtr, const value_type>::type pointer;
    typedef typename pointer_traits<pointer>::difference_type difference_type;

    _LIBCPP_INLINE_VISIBILITY
    __list_const_iterator() _NOEXCEPT : __ptr_(nullptr)
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        __get_db()->__insert_i(this);
#endif
    }
    _LIBCPP_INLINE_VISIBILITY
    __list_const_iterator(const __list_iterator<_Tp, _VoidPtr>& __p) _NOEXCEPT
        : __ptr_(__p.__ptr_)
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        __get_db()->__iterator_copy(this, &__p);
#endif
    }

#if _LIBCPP_DEBUG_LEVEL >= 2

    _LIBCPP_INLINE_VISIBILITY
    __list_const_iterator(const __list_const_iterator& __p)
        : __ptr_(__p.__ptr_)
    {
        __get_db()->__iterator_copy(this, &__p);
    }

    _LIBCPP_INLINE_VISIBILITY
    ~__list_const_iterator()
    {
        __get_db()->__erase_i(this);
    }

    _LIBCPP_INLINE_VISIBILITY
    __list_const_iterator& operator=(const __list_const_iterator& __p)
    {
        if (this != &__p)
        {
            __get_db()->__iterator_copy(this, &__p);
            __ptr_ = __p.__ptr_;
        }
        return *this;
    }

#endif  // _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_INLINE_VISIBILITY
    reference operator*() const
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__dereferenceable(this),
                       "Attempted to dereference a non-dereferenceable list::const_iterator");
#endif
        return __ptr_->__as_node()->__value_;
    }
    _LIBCPP_INLINE_VISIBILITY
    pointer operator->() const
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__dereferenceable(this),
                       "Attempted to dereference a non-dereferenceable list::iterator");
#endif
        return pointer_traits<pointer>::pointer_to(__ptr_->__as_node()->__value_);
    }

    _LIBCPP_INLINE_VISIBILITY
    __list_const_iterator& operator++()
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__dereferenceable(this),
                       "Attempted to increment non-incrementable list::const_iterator");
#endif
        __ptr_ = __ptr_->__next_;
        return *this;
    }
    _LIBCPP_INLINE_VISIBILITY
    __list_const_iterator operator++(int) {__list_const_iterator __t(*this); ++(*this); return __t;}

    _LIBCPP_INLINE_VISIBILITY
    __list_const_iterator& operator--()
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__decrementable(this),
                       "Attempted to decrement non-decrementable list::const_iterator");
#endif
        __ptr_ = __ptr_->__prev_;
        return *this;
    }
    _LIBCPP_INLINE_VISIBILITY
    __list_const_iterator operator--(int) {__list_const_iterator __t(*this); --(*this); return __t;}

    friend _LIBCPP_INLINE_VISIBILITY
    bool operator==(const __list_const_iterator& __x, const __list_const_iterator& __y)
    {
        return __x.__ptr_ == __y.__ptr_;
    }
    friend _LIBCPP_INLINE_VISIBILITY
    bool operator!=(const __list_const_iterator& __x, const __list_const_iterator& __y)
        {return !(__x == __y);}
};

template <class _Tp, class _Alloc>
class __list_imp
{
    __list_imp(const __list_imp&);
    __list_imp& operator=(const __list_imp&);
protected:
    typedef _Tp                                                     value_type;
    typedef _Alloc                                                  allocator_type;
    typedef allocator_traits<allocator_type>                        __alloc_traits;
    typedef typename __alloc_traits::size_type                      size_type;
    typedef typename __alloc_traits::void_pointer                   __void_pointer;
    typedef __list_iterator<value_type, __void_pointer>             iterator;
    typedef __list_const_iterator<value_type, __void_pointer>       const_iterator;
    typedef __list_node_base<value_type, __void_pointer>            __node_base;
    typedef __list_node<value_type, __void_pointer>                 __node;
    typedef typename __rebind_alloc_helper<__alloc_traits, __node>::type __node_allocator;
    typedef allocator_traits<__node_allocator>                       __node_alloc_traits;
    typedef typename __node_alloc_traits::pointer                    __node_pointer;
    typedef typename __node_alloc_traits::pointer                    __node_const_pointer;
    typedef __list_node_pointer_traits<value_type, __void_pointer> __node_pointer_traits;
    typedef typename __node_pointer_traits::__link_pointer __link_pointer;
    typedef __link_pointer __link_const_pointer;
    typedef typename __alloc_traits::pointer                         pointer;
    typedef typename __alloc_traits::const_pointer                   const_pointer;
    typedef typename __alloc_traits::difference_type                 difference_type;

    typedef typename __rebind_alloc_helper<__alloc_traits, __node_base>::type __node_base_allocator;
    typedef typename allocator_traits<__node_base_allocator>::pointer __node_base_pointer;

    __node_base __end_;
    __compressed_pair<size_type, __node_allocator> __size_alloc_;

    _LIBCPP_INLINE_VISIBILITY
    __link_pointer __end_as_link() const _NOEXCEPT {
        return __node_pointer_traits::__unsafe_link_pointer_cast(
                const_cast<__node_base&>(__end_).__self());
    }

    _LIBCPP_INLINE_VISIBILITY
          size_type& __sz() _NOEXCEPT {return __size_alloc_.first();}
    _LIBCPP_INLINE_VISIBILITY
    const size_type& __sz() const _NOEXCEPT
        {return __size_alloc_.first();}
    _LIBCPP_INLINE_VISIBILITY
          __node_allocator& __node_alloc() _NOEXCEPT
          {return __size_alloc_.second();}
    _LIBCPP_INLINE_VISIBILITY
    const __node_allocator& __node_alloc() const _NOEXCEPT
        {return __size_alloc_.second();}

    _LIBCPP_INLINE_VISIBILITY
    size_type __node_alloc_max_size() const _NOEXCEPT {
        return __node_alloc_traits::max_size(__node_alloc());
    }
    _LIBCPP_INLINE_VISIBILITY
    static void __unlink_nodes(__link_pointer __f, __link_pointer __l) _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY
    __list_imp()
        _NOEXCEPT_(is_nothrow_default_constructible<__node_allocator>::value);
    _LIBCPP_INLINE_VISIBILITY
    __list_imp(const allocator_type& __a);
    ~__list_imp();
    void clear() _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    bool empty() const _NOEXCEPT {return __sz() == 0;}

    _LIBCPP_INLINE_VISIBILITY
    iterator begin() _NOEXCEPT
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        return iterator(__end_.__next_, this);
#else
        return iterator(__end_.__next_);
#endif
    }
    _LIBCPP_INLINE_VISIBILITY
    const_iterator begin() const  _NOEXCEPT
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        return const_iterator(__end_.__next_, this);
#else
        return const_iterator(__end_.__next_);
#endif
    }
    _LIBCPP_INLINE_VISIBILITY
    iterator end() _NOEXCEPT
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        return iterator(__end_as_link(), this);
#else
        return iterator(__end_as_link());
#endif
    }
    _LIBCPP_INLINE_VISIBILITY
    const_iterator end() const _NOEXCEPT
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        return const_iterator(__end_as_link(), this);
#else
        return const_iterator(__end_as_link());
#endif
    }

    void swap(__list_imp& __c)
#if _LIBCPP_STD_VER >= 14
        _NOEXCEPT_DEBUG;
#else
        _NOEXCEPT_DEBUG_(!__alloc_traits::propagate_on_container_swap::value ||
                    __is_nothrow_swappable<allocator_type>::value);
#endif

    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const __list_imp& __c)
        {__copy_assign_alloc(__c, integral_constant<bool,
                      __node_alloc_traits::propagate_on_container_copy_assignment::value>());}

    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(__list_imp& __c)
        _NOEXCEPT_(
            !__node_alloc_traits::propagate_on_container_move_assignment::value ||
            is_nothrow_move_assignable<__node_allocator>::value)
        {__move_assign_alloc(__c, integral_constant<bool,
                      __node_alloc_traits::propagate_on_container_move_assignment::value>());}

private:
    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const __list_imp& __c, true_type)
        {
            if (__node_alloc() != __c.__node_alloc())
                clear();
            __node_alloc() = __c.__node_alloc();
        }

    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const __list_imp&, false_type)
        {}

    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(__list_imp& __c, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<__node_allocator>::value)
        {
            __node_alloc() = _VSTD::move(__c.__node_alloc());
        }

    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(__list_imp&, false_type)
        _NOEXCEPT
        {}

    _LIBCPP_INLINE_VISIBILITY
    void __invalidate_all_iterators() {
#if _LIBCPP_DEBUG_LEVEL >= 2
      __get_db()->__invalidate_all(this);
#endif
    }
};

// Unlink nodes [__f, __l]
template <class _Tp, class _Alloc>
inline
void
__list_imp<_Tp, _Alloc>::__unlink_nodes(__link_pointer __f, __link_pointer __l)
    _NOEXCEPT
{
    __f->__prev_->__next_ = __l->__next_;
    __l->__next_->__prev_ = __f->__prev_;
}

template <class _Tp, class _Alloc>
inline
__list_imp<_Tp, _Alloc>::__list_imp()
        _NOEXCEPT_(is_nothrow_default_constructible<__node_allocator>::value)
    : __size_alloc_(0)
{
}

template <class _Tp, class _Alloc>
inline
__list_imp<_Tp, _Alloc>::__list_imp(const allocator_type& __a)
    : __size_alloc_(0, __node_allocator(__a))
{
}

template <class _Tp, class _Alloc>
__list_imp<_Tp, _Alloc>::~__list_imp()
{
    clear();
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__erase_c(this);
#endif
}

template <class _Tp, class _Alloc>
void
__list_imp<_Tp, _Alloc>::clear() _NOEXCEPT
{
    if (!empty())
    {
        __node_allocator& __na = __node_alloc();
        __link_pointer __f = __end_.__next_;
        __link_pointer __l = __end_as_link();
        __unlink_nodes(__f, __l->__prev_);
        __sz() = 0;
        while (__f != __l)
        {
            __node_pointer __np = __f->__as_node();
            __f = __f->__next_;
            __node_alloc_traits::destroy(__na, _VSTD::addressof(__np->__value_));
            __node_alloc_traits::deallocate(__na, __np, 1);
        }
        __invalidate_all_iterators();
    }
}

template <class _Tp, class _Alloc>
void
__list_imp<_Tp, _Alloc>::swap(__list_imp& __c)
#if _LIBCPP_STD_VER >= 14
        _NOEXCEPT_DEBUG
#else
        _NOEXCEPT_DEBUG_(!__alloc_traits::propagate_on_container_swap::value ||
                    __is_nothrow_swappable<allocator_type>::value)
#endif
{
    _LIBCPP_ASSERT(__alloc_traits::propagate_on_container_swap::value ||
                   this->__node_alloc() == __c.__node_alloc(),
                   "list::swap: Either propagate_on_container_swap must be true"
                   " or the allocators must compare equal");
    using _VSTD::swap;
    __swap_allocator(__node_alloc(), __c.__node_alloc());
    swap(__sz(), __c.__sz());
    swap(__end_, __c.__end_);
    if (__sz() == 0)
        __end_.__next_ = __end_.__prev_ = __end_as_link();
    else
        __end_.__prev_->__next_ = __end_.__next_->__prev_ = __end_as_link();
    if (__c.__sz() == 0)
        __c.__end_.__next_ = __c.__end_.__prev_ = __c.__end_as_link();
    else
        __c.__end_.__prev_->__next_ = __c.__end_.__next_->__prev_ = __c.__end_as_link();

#if _LIBCPP_DEBUG_LEVEL >= 2
    __libcpp_db* __db = __get_db();
    __c_node* __cn1 = __db->__find_c_and_lock(this);
    __c_node* __cn2 = __db->__find_c(&__c);
    std::swap(__cn1->beg_, __cn2->beg_);
    std::swap(__cn1->end_, __cn2->end_);
    std::swap(__cn1->cap_, __cn2->cap_);
    for (__i_node** __p = __cn1->end_; __p != __cn1->beg_;)
    {
        --__p;
        const_iterator* __i = static_cast<const_iterator*>((*__p)->__i_);
        if (__i->__ptr_ == __c.__end_as_link())
        {
            __cn2->__add(*__p);
            if (--__cn1->end_ != __p)
                memmove(__p, __p+1, (__cn1->end_ - __p)*sizeof(__i_node*));
        }
        else
            (*__p)->__c_ = __cn1;
    }
    for (__i_node** __p = __cn2->end_; __p != __cn2->beg_;)
    {
        --__p;
        const_iterator* __i = static_cast<const_iterator*>((*__p)->__i_);
        if (__i->__ptr_ == __end_as_link())
        {
            __cn1->__add(*__p);
            if (--__cn2->end_ != __p)
                memmove(__p, __p+1, (__cn2->end_ - __p)*sizeof(__i_node*));
        }
        else
            (*__p)->__c_ = __cn2;
    }
    __db->unlock();
#endif
}

template <class _Tp, class _Alloc /*= allocator<_Tp>*/>
class _LIBCPP_TEMPLATE_VIS list
    : private __list_imp<_Tp, _Alloc>
{
    typedef __list_imp<_Tp, _Alloc> base;
    typedef typename base::__node              __node;
    typedef typename base::__node_allocator    __node_allocator;
    typedef typename base::__node_pointer      __node_pointer;
    typedef typename base::__node_alloc_traits __node_alloc_traits;
    typedef typename base::__node_base         __node_base;
    typedef typename base::__node_base_pointer __node_base_pointer;
    typedef typename base::__link_pointer __link_pointer;

public:
    typedef _Tp                                      value_type;
    typedef _Alloc                                   allocator_type;
    static_assert((is_same<value_type, typename allocator_type::value_type>::value),
                  "Invalid allocator::value_type");
    typedef value_type&                              reference;
    typedef const value_type&                        const_reference;
    typedef typename base::pointer                   pointer;
    typedef typename base::const_pointer             const_pointer;
    typedef typename base::size_type                 size_type;
    typedef typename base::difference_type           difference_type;
    typedef typename base::iterator                  iterator;
    typedef typename base::const_iterator            const_iterator;
    typedef _VSTD::reverse_iterator<iterator>         reverse_iterator;
    typedef _VSTD::reverse_iterator<const_iterator>   const_reverse_iterator;

    _LIBCPP_INLINE_VISIBILITY
    list()
        _NOEXCEPT_(is_nothrow_default_constructible<__node_allocator>::value)
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        __get_db()->__insert_c(this);
#endif
    }
    _LIBCPP_INLINE_VISIBILITY
    explicit list(const allocator_type& __a) : base(__a)
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        __get_db()->__insert_c(this);
#endif
    }
    explicit list(size_type __n);
#if _LIBCPP_STD_VER > 11
    explicit list(size_type __n, const allocator_type& __a);
#endif
    list(size_type __n, const value_type& __x);
    list(size_type __n, const value_type& __x, const allocator_type& __a);
    template <class _InpIter>
        list(_InpIter __f, _InpIter __l,
             typename enable_if<__is_input_iterator<_InpIter>::value>::type* = 0);
    template <class _InpIter>
        list(_InpIter __f, _InpIter __l, const allocator_type& __a,
             typename enable_if<__is_input_iterator<_InpIter>::value>::type* = 0);

    list(const list& __c);
    list(const list& __c, const allocator_type& __a);
    _LIBCPP_INLINE_VISIBILITY
    list& operator=(const list& __c);
#ifndef _LIBCPP_CXX03_LANG
    list(initializer_list<value_type> __il);
    list(initializer_list<value_type> __il, const allocator_type& __a);

    _LIBCPP_INLINE_VISIBILITY
    list(list&& __c)
        _NOEXCEPT_(is_nothrow_move_constructible<__node_allocator>::value);
    _LIBCPP_INLINE_VISIBILITY
    list(list&& __c, const allocator_type& __a);
    _LIBCPP_INLINE_VISIBILITY
    list& operator=(list&& __c)
        _NOEXCEPT_(
            __node_alloc_traits::propagate_on_container_move_assignment::value &&
            is_nothrow_move_assignable<__node_allocator>::value);

    _LIBCPP_INLINE_VISIBILITY
    list& operator=(initializer_list<value_type> __il)
        {assign(__il.begin(), __il.end()); return *this;}

    _LIBCPP_INLINE_VISIBILITY
    void assign(initializer_list<value_type> __il)
        {assign(__il.begin(), __il.end());}
#endif  // _LIBCPP_CXX03_LANG

    template <class _InpIter>
        void assign(_InpIter __f, _InpIter __l,
             typename enable_if<__is_input_iterator<_InpIter>::value>::type* = 0);
    void assign(size_type __n, const value_type& __x);

    _LIBCPP_INLINE_VISIBILITY
    allocator_type get_allocator() const _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY
    size_type size() const _NOEXCEPT     {return base::__sz();}
    _LIBCPP_INLINE_VISIBILITY
    bool empty() const _NOEXCEPT         {return base::empty();}
    _LIBCPP_INLINE_VISIBILITY
    size_type max_size() const _NOEXCEPT
        {
            return std::min<size_type>(
                base::__node_alloc_max_size(),
                numeric_limits<difference_type >::max());
        }

    _LIBCPP_INLINE_VISIBILITY
          iterator begin() _NOEXCEPT        {return base::begin();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator begin()  const _NOEXCEPT {return base::begin();}
    _LIBCPP_INLINE_VISIBILITY
          iterator end() _NOEXCEPT          {return base::end();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator end()    const _NOEXCEPT {return base::end();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator cbegin() const _NOEXCEPT {return base::begin();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator cend()   const _NOEXCEPT {return base::end();}

    _LIBCPP_INLINE_VISIBILITY
          reverse_iterator rbegin() _NOEXCEPT
            {return       reverse_iterator(end());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator rbegin()  const _NOEXCEPT
        {return const_reverse_iterator(end());}
    _LIBCPP_INLINE_VISIBILITY
          reverse_iterator rend() _NOEXCEPT
            {return       reverse_iterator(begin());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator rend()    const _NOEXCEPT
        {return const_reverse_iterator(begin());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator crbegin() const _NOEXCEPT
        {return const_reverse_iterator(end());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator crend()   const _NOEXCEPT
        {return const_reverse_iterator(begin());}

    _LIBCPP_INLINE_VISIBILITY
    reference front()
    {
        _LIBCPP_ASSERT(!empty(), "list::front called on empty list");
        return base::__end_.__next_->__as_node()->__value_;
    }
    _LIBCPP_INLINE_VISIBILITY
    const_reference front() const
    {
        _LIBCPP_ASSERT(!empty(), "list::front called on empty list");
        return base::__end_.__next_->__as_node()->__value_;
    }
    _LIBCPP_INLINE_VISIBILITY
    reference back()
    {
        _LIBCPP_ASSERT(!empty(), "list::back called on empty list");
        return base::__end_.__prev_->__as_node()->__value_;
    }
    _LIBCPP_INLINE_VISIBILITY
    const_reference back() const
    {
        _LIBCPP_ASSERT(!empty(), "list::back called on empty list");
        return base::__end_.__prev_->__as_node()->__value_;
    }

#ifndef _LIBCPP_CXX03_LANG
    void push_front(value_type&& __x);
    void push_back(value_type&& __x);

    template <class... _Args>
#if _LIBCPP_STD_VER > 14
       reference emplace_front(_Args&&... __args);
#else
       void      emplace_front(_Args&&... __args);
#endif
    template <class... _Args>
#if _LIBCPP_STD_VER > 14
        reference emplace_back(_Args&&... __args);
#else
       void       emplace_back(_Args&&... __args);
#endif
    template <class... _Args>
        iterator emplace(const_iterator __p, _Args&&... __args);

    iterator insert(const_iterator __p, value_type&& __x);

    _LIBCPP_INLINE_VISIBILITY
    iterator insert(const_iterator __p, initializer_list<value_type> __il)
        {return insert(__p, __il.begin(), __il.end());}
#endif  // _LIBCPP_CXX03_LANG

    void push_front(const value_type& __x);
    void push_back(const value_type& __x);

    iterator insert(const_iterator __p, const value_type& __x);
    iterator insert(const_iterator __p, size_type __n, const value_type& __x);
    template <class _InpIter>
        iterator insert(const_iterator __p, _InpIter __f, _InpIter __l,
             typename enable_if<__is_input_iterator<_InpIter>::value>::type* = 0);

    _LIBCPP_INLINE_VISIBILITY
    void swap(list& __c)
#if _LIBCPP_STD_VER >= 14
        _NOEXCEPT_DEBUG
#else
        _NOEXCEPT_DEBUG_(!__node_alloc_traits::propagate_on_container_swap::value ||
                   __is_nothrow_swappable<__node_allocator>::value)
#endif
        {base::swap(__c);}
    _LIBCPP_INLINE_VISIBILITY
    void clear() _NOEXCEPT {base::clear();}

    void pop_front();
    void pop_back();

    iterator erase(const_iterator __p);
    iterator erase(const_iterator __f, const_iterator __l);

    void resize(size_type __n);
    void resize(size_type __n, const value_type& __x);

    void splice(const_iterator __p, list& __c);
#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    void splice(const_iterator __p, list&& __c) {splice(__p, __c);}
    _LIBCPP_INLINE_VISIBILITY
    void splice(const_iterator __p, list&& __c, const_iterator __i)
        {splice(__p, __c, __i);}
    _LIBCPP_INLINE_VISIBILITY
    void splice(const_iterator __p, list&& __c, const_iterator __f, const_iterator __l)
        {splice(__p, __c, __f, __l);}
#endif
    void splice(const_iterator __p, list& __c, const_iterator __i);
    void splice(const_iterator __p, list& __c, const_iterator __f, const_iterator __l);

    void remove(const value_type& __x);
    template <class _Pred> void remove_if(_Pred __pred);
    _LIBCPP_INLINE_VISIBILITY
    void unique();
    template <class _BinaryPred>
        void unique(_BinaryPred __binary_pred);
    _LIBCPP_INLINE_VISIBILITY
    void merge(list& __c);
#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    void merge(list&& __c) {merge(__c);}

    template <class _Comp>
    _LIBCPP_INLINE_VISIBILITY
        void merge(list&& __c, _Comp __comp) {merge(__c, __comp);}
#endif
    template <class _Comp>
        void merge(list& __c, _Comp __comp);

    _LIBCPP_INLINE_VISIBILITY
    void sort();
    template <class _Comp>
        _LIBCPP_INLINE_VISIBILITY
        void sort(_Comp __comp);

    void reverse() _NOEXCEPT;

    bool __invariants() const;

#if _LIBCPP_DEBUG_LEVEL >= 2

    bool __dereferenceable(const const_iterator* __i) const;
    bool __decrementable(const const_iterator* __i) const;
    bool __addable(const const_iterator* __i, ptrdiff_t __n) const;
    bool __subscriptable(const const_iterator* __i, ptrdiff_t __n) const;

#endif  // _LIBCPP_DEBUG_LEVEL >= 2

private:
    _LIBCPP_INLINE_VISIBILITY
    static void __link_nodes  (__link_pointer __p, __link_pointer __f, __link_pointer __l);
    _LIBCPP_INLINE_VISIBILITY
    void __link_nodes_at_front(__link_pointer __f, __link_pointer __l);
    _LIBCPP_INLINE_VISIBILITY
    void __link_nodes_at_back (__link_pointer __f, __link_pointer __l);
    iterator __iterator(size_type __n);
    template <class _Comp>
        static iterator __sort(iterator __f1, iterator __e2, size_type __n, _Comp& __comp);

    void __move_assign(list& __c, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<__node_allocator>::value);
    void __move_assign(list& __c, false_type);
};

// Link in nodes [__f, __l] just prior to __p
template <class _Tp, class _Alloc>
inline
void
list<_Tp, _Alloc>::__link_nodes(__link_pointer __p, __link_pointer __f, __link_pointer __l)
{
    __p->__prev_->__next_ = __f;
    __f->__prev_ = __p->__prev_;
    __p->__prev_ = __l;
    __l->__next_ = __p;
}

// Link in nodes [__f, __l] at the front of the list
template <class _Tp, class _Alloc>
inline
void
list<_Tp, _Alloc>::__link_nodes_at_front(__link_pointer __f, __link_pointer __l)
{
    __f->__prev_ = base::__end_as_link();
    __l->__next_ = base::__end_.__next_;
    __l->__next_->__prev_ = __l;
    base::__end_.__next_ = __f;
}

// Link in nodes [__f, __l] at the front of the list
template <class _Tp, class _Alloc>
inline
void
list<_Tp, _Alloc>::__link_nodes_at_back(__link_pointer __f, __link_pointer __l)
{
    __l->__next_ = base::__end_as_link();
    __f->__prev_ = base::__end_.__prev_;
    __f->__prev_->__next_ = __f;
    base::__end_.__prev_ = __l;
}


template <class _Tp, class _Alloc>
inline
typename list<_Tp, _Alloc>::iterator
list<_Tp, _Alloc>::__iterator(size_type __n)
{
    return __n <= base::__sz() / 2 ? _VSTD::next(begin(), __n)
                                   : _VSTD::prev(end(), base::__sz() - __n);
}

template <class _Tp, class _Alloc>
list<_Tp, _Alloc>::list(size_type __n)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    for (; __n > 0; --__n)
#ifndef _LIBCPP_CXX03_LANG
        emplace_back();
#else
        push_back(value_type());
#endif
}

#if _LIBCPP_STD_VER > 11
template <class _Tp, class _Alloc>
list<_Tp, _Alloc>::list(size_type __n, const allocator_type& __a) : base(__a)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    for (; __n > 0; --__n)
        emplace_back();
}
#endif

template <class _Tp, class _Alloc>
list<_Tp, _Alloc>::list(size_type __n, const value_type& __x)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    for (; __n > 0; --__n)
        push_back(__x);
}

template <class _Tp, class _Alloc>
list<_Tp, _Alloc>::list(size_type __n, const value_type& __x, const allocator_type& __a)
    : base(__a)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    for (; __n > 0; --__n)
        push_back(__x);
}

template <class _Tp, class _Alloc>
template <class _InpIter>
list<_Tp, _Alloc>::list(_InpIter __f, _InpIter __l,
                        typename enable_if<__is_input_iterator<_InpIter>::value>::type*)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    for (; __f != __l; ++__f)
        push_back(*__f);
}

template <class _Tp, class _Alloc>
template <class _InpIter>
list<_Tp, _Alloc>::list(_InpIter __f, _InpIter __l, const allocator_type& __a,
                        typename enable_if<__is_input_iterator<_InpIter>::value>::type*)
    : base(__a)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    for (; __f != __l; ++__f)
        push_back(*__f);
}

template <class _Tp, class _Alloc>
list<_Tp, _Alloc>::list(const list& __c)
    : base(allocator_type(
           __node_alloc_traits::select_on_container_copy_construction(
                __c.__node_alloc())))
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    for (const_iterator __i = __c.begin(), __e = __c.end(); __i != __e; ++__i)
        push_back(*__i);
}

template <class _Tp, class _Alloc>
list<_Tp, _Alloc>::list(const list& __c, const allocator_type& __a)
    : base(__a)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    for (const_iterator __i = __c.begin(), __e = __c.end(); __i != __e; ++__i)
        push_back(*__i);
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Tp, class _Alloc>
list<_Tp, _Alloc>::list(initializer_list<value_type> __il, const allocator_type& __a)
    : base(__a)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    for (typename initializer_list<value_type>::const_iterator __i = __il.begin(),
            __e = __il.end(); __i != __e; ++__i)
        push_back(*__i);
}

template <class _Tp, class _Alloc>
list<_Tp, _Alloc>::list(initializer_list<value_type> __il)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    for (typename initializer_list<value_type>::const_iterator __i = __il.begin(),
            __e = __il.end(); __i != __e; ++__i)
        push_back(*__i);
}

template <class _Tp, class _Alloc>
inline
list<_Tp, _Alloc>::list(list&& __c)
    _NOEXCEPT_(is_nothrow_move_constructible<__node_allocator>::value)
    : base(allocator_type(_VSTD::move(__c.__node_alloc())))
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    splice(end(), __c);
}

template <class _Tp, class _Alloc>
inline
list<_Tp, _Alloc>::list(list&& __c, const allocator_type& __a)
    : base(__a)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    if (__a == __c.get_allocator())
        splice(end(), __c);
    else
    {
        typedef move_iterator<iterator> _Ip;
        assign(_Ip(__c.begin()), _Ip(__c.end()));
    }
}

template <class _Tp, class _Alloc>
inline
list<_Tp, _Alloc>&
list<_Tp, _Alloc>::operator=(list&& __c)
        _NOEXCEPT_(
            __node_alloc_traits::propagate_on_container_move_assignment::value &&
            is_nothrow_move_assignable<__node_allocator>::value)
{
    __move_assign(__c, integral_constant<bool,
          __node_alloc_traits::propagate_on_container_move_assignment::value>());
    return *this;
}

template <class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::__move_assign(list& __c, false_type)
{
    if (base::__node_alloc() != __c.__node_alloc())
    {
        typedef move_iterator<iterator> _Ip;
        assign(_Ip(__c.begin()), _Ip(__c.end()));
    }
    else
        __move_assign(__c, true_type());
}

template <class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::__move_assign(list& __c, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<__node_allocator>::value)
{
    clear();
    base::__move_assign_alloc(__c);
    splice(end(), __c);
}

#endif  // _LIBCPP_CXX03_LANG

template <class _Tp, class _Alloc>
inline
list<_Tp, _Alloc>&
list<_Tp, _Alloc>::operator=(const list& __c)
{
    if (this != &__c)
    {
        base::__copy_assign_alloc(__c);
        assign(__c.begin(), __c.end());
    }
    return *this;
}

template <class _Tp, class _Alloc>
template <class _InpIter>
void
list<_Tp, _Alloc>::assign(_InpIter __f, _InpIter __l,
                          typename enable_if<__is_input_iterator<_InpIter>::value>::type*)
{
    iterator __i = begin();
    iterator __e = end();
    for (; __f != __l && __i != __e; ++__f, ++__i)
        *__i = *__f;
    if (__i == __e)
        insert(__e, __f, __l);
    else
        erase(__i, __e);
#if _LIBCPP_DEBUG_LEVEL >= 2
      __get_db()->__invalidate_all(this);
#endif
}

template <class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::assign(size_type __n, const value_type& __x)
{
    iterator __i = begin();
    iterator __e = end();
    for (; __n > 0 && __i != __e; --__n, ++__i)
        *__i = __x;
    if (__i == __e)
        insert(__e, __n, __x);
    else
        erase(__i, __e);
#if _LIBCPP_DEBUG_LEVEL >= 2
      __get_db()->__invalidate_all(this);
#endif
}

template <class _Tp, class _Alloc>
inline
_Alloc
list<_Tp, _Alloc>::get_allocator() const _NOEXCEPT
{
    return allocator_type(base::__node_alloc());
}

template <class _Tp, class _Alloc>
typename list<_Tp, _Alloc>::iterator
list<_Tp, _Alloc>::insert(const_iterator __p, const value_type& __x)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__p) == this,
        "list::insert(iterator, x) called with an iterator not"
        " referring to this list");
#endif
    __node_allocator& __na = base::__node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __hold->__prev_ = 0;
    __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_), __x);
    __link_nodes(__p.__ptr_, __hold->__as_link(), __hold->__as_link());
    ++base::__sz();
#if _LIBCPP_DEBUG_LEVEL >= 2
    return iterator(__hold.release()->__as_link(), this);
#else
    return iterator(__hold.release()->__as_link());
#endif
}

template <class _Tp, class _Alloc>
typename list<_Tp, _Alloc>::iterator
list<_Tp, _Alloc>::insert(const_iterator __p, size_type __n, const value_type& __x)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__p) == this,
        "list::insert(iterator, n, x) called with an iterator not"
        " referring to this list");
    iterator __r(__p.__ptr_, this);
#else
    iterator __r(__p.__ptr_);
#endif
    if (__n > 0)
    {
        size_type __ds = 0;
        __node_allocator& __na = base::__node_alloc();
        typedef __allocator_destructor<__node_allocator> _Dp;
        unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
        __hold->__prev_ = 0;
        __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_), __x);
        ++__ds;
#if _LIBCPP_DEBUG_LEVEL >= 2
        __r = iterator(__hold->__as_link(), this);
#else
        __r = iterator(__hold->__as_link());
#endif
        __hold.release();
        iterator __e = __r;
#ifndef _LIBCPP_NO_EXCEPTIONS
        try
        {
#endif  // _LIBCPP_NO_EXCEPTIONS
            for (--__n; __n != 0; --__n, ++__e, ++__ds)
            {
                __hold.reset(__node_alloc_traits::allocate(__na, 1));
                __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_), __x);
                __e.__ptr_->__next_ = __hold->__as_link();
                __hold->__prev_ = __e.__ptr_;
                __hold.release();
            }
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
            while (true)
            {
                __node_alloc_traits::destroy(__na, _VSTD::addressof(*__e));
                __link_pointer __prev = __e.__ptr_->__prev_;
                __node_alloc_traits::deallocate(__na, __e.__ptr_->__as_node(), 1);
                if (__prev == 0)
                    break;
#if _LIBCPP_DEBUG_LEVEL >= 2
                __e = iterator(__prev, this);
#else
                __e = iterator(__prev);
#endif
            }
            throw;
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
        __link_nodes(__p.__ptr_, __r.__ptr_, __e.__ptr_);
        base::__sz() += __ds;
    }
    return __r;
}

template <class _Tp, class _Alloc>
template <class _InpIter>
typename list<_Tp, _Alloc>::iterator
list<_Tp, _Alloc>::insert(const_iterator __p, _InpIter __f, _InpIter __l,
             typename enable_if<__is_input_iterator<_InpIter>::value>::type*)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__p) == this,
        "list::insert(iterator, range) called with an iterator not"
        " referring to this list");
    iterator __r(__p.__ptr_, this);
#else
    iterator __r(__p.__ptr_);
#endif
    if (__f != __l)
    {
        size_type __ds = 0;
        __node_allocator& __na = base::__node_alloc();
        typedef __allocator_destructor<__node_allocator> _Dp;
        unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
        __hold->__prev_ = 0;
        __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_), *__f);
        ++__ds;
#if _LIBCPP_DEBUG_LEVEL >= 2
        __r = iterator(__hold.get()->__as_link(), this);
#else
        __r = iterator(__hold.get()->__as_link());
#endif
        __hold.release();
        iterator __e = __r;
#ifndef _LIBCPP_NO_EXCEPTIONS
        try
        {
#endif  // _LIBCPP_NO_EXCEPTIONS
            for (++__f; __f != __l; ++__f, (void) ++__e, (void) ++__ds)
            {
                __hold.reset(__node_alloc_traits::allocate(__na, 1));
                __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_), *__f);
                __e.__ptr_->__next_ = __hold.get()->__as_link();
                __hold->__prev_ = __e.__ptr_;
                __hold.release();
            }
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
            while (true)
            {
                __node_alloc_traits::destroy(__na, _VSTD::addressof(*__e));
                __link_pointer __prev = __e.__ptr_->__prev_;
                __node_alloc_traits::deallocate(__na, __e.__ptr_->__as_node(), 1);
                if (__prev == 0)
                    break;
#if _LIBCPP_DEBUG_LEVEL >= 2
                __e = iterator(__prev, this);
#else
                __e = iterator(__prev);
#endif
            }
            throw;
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
        __link_nodes(__p.__ptr_, __r.__ptr_, __e.__ptr_);
        base::__sz() += __ds;
    }
    return __r;
}

template <class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::push_front(const value_type& __x)
{
    __node_allocator& __na = base::__node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_), __x);
    __link_pointer __nl = __hold->__as_link();
    __link_nodes_at_front(__nl, __nl);
    ++base::__sz();
    __hold.release();
}

template <class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::push_back(const value_type& __x)
{
    __node_allocator& __na = base::__node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_), __x);
    __link_nodes_at_back(__hold.get()->__as_link(), __hold.get()->__as_link());
    ++base::__sz();
    __hold.release();
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::push_front(value_type&& __x)
{
    __node_allocator& __na = base::__node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_), _VSTD::move(__x));
    __link_nodes_at_front(__hold.get()->__as_link(), __hold.get()->__as_link());
    ++base::__sz();
    __hold.release();
}

template <class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::push_back(value_type&& __x)
{
    __node_allocator& __na = base::__node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_), _VSTD::move(__x));
    __link_nodes_at_back(__hold.get()->__as_link(), __hold.get()->__as_link());
    ++base::__sz();
    __hold.release();
}

template <class _Tp, class _Alloc>
template <class... _Args>
#if _LIBCPP_STD_VER > 14
typename list<_Tp, _Alloc>::reference
#else
void
#endif
list<_Tp, _Alloc>::emplace_front(_Args&&... __args)
{
    __node_allocator& __na = base::__node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_), _VSTD::forward<_Args>(__args)...);
    __link_nodes_at_front(__hold.get()->__as_link(), __hold.get()->__as_link());
    ++base::__sz();
#if _LIBCPP_STD_VER > 14
    return __hold.release()->__value_;
#else
    __hold.release();
#endif
}

template <class _Tp, class _Alloc>
template <class... _Args>
#if _LIBCPP_STD_VER > 14
typename list<_Tp, _Alloc>::reference
#else
void
#endif
list<_Tp, _Alloc>::emplace_back(_Args&&... __args)
{
    __node_allocator& __na = base::__node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_), _VSTD::forward<_Args>(__args)...);
    __link_pointer __nl = __hold->__as_link();
    __link_nodes_at_back(__nl, __nl);
    ++base::__sz();
#if _LIBCPP_STD_VER > 14
    return __hold.release()->__value_;
#else
    __hold.release();
#endif
}

template <class _Tp, class _Alloc>
template <class... _Args>
typename list<_Tp, _Alloc>::iterator
list<_Tp, _Alloc>::emplace(const_iterator __p, _Args&&... __args)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__p) == this,
        "list::emplace(iterator, args...) called with an iterator not"
        " referring to this list");
#endif
    __node_allocator& __na = base::__node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __hold->__prev_ = 0;
    __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_), _VSTD::forward<_Args>(__args)...);
    __link_pointer __nl = __hold.get()->__as_link();
    __link_nodes(__p.__ptr_, __nl, __nl);
    ++base::__sz();
    __hold.release();
#if _LIBCPP_DEBUG_LEVEL >= 2
    return iterator(__nl, this);
#else
    return iterator(__nl);
#endif
}

template <class _Tp, class _Alloc>
typename list<_Tp, _Alloc>::iterator
list<_Tp, _Alloc>::insert(const_iterator __p, value_type&& __x)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__p) == this,
        "list::insert(iterator, x) called with an iterator not"
        " referring to this list");
#endif
    __node_allocator& __na = base::__node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __hold->__prev_ = 0;
    __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_), _VSTD::move(__x));
    __link_pointer __nl = __hold->__as_link();
    __link_nodes(__p.__ptr_, __nl, __nl);
    ++base::__sz();
    __hold.release();
#if _LIBCPP_DEBUG_LEVEL >= 2
    return iterator(__nl, this);
#else
    return iterator(__nl);
#endif
}

#endif  // _LIBCPP_CXX03_LANG

template <class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::pop_front()
{
    _LIBCPP_ASSERT(!empty(), "list::pop_front() called with empty list");
    __node_allocator& __na = base::__node_alloc();
    __link_pointer __n = base::__end_.__next_;
    base::__unlink_nodes(__n, __n);
    --base::__sz();
#if _LIBCPP_DEBUG_LEVEL >= 2
    __c_node* __c = __get_db()->__find_c_and_lock(this);
    for (__i_node** __p = __c->end_; __p != __c->beg_; )
    {
        --__p;
        iterator* __i = static_cast<iterator*>((*__p)->__i_);
        if (__i->__ptr_ == __n)
        {
            (*__p)->__c_ = nullptr;
            if (--__c->end_ != __p)
                memmove(__p, __p+1, (__c->end_ - __p)*sizeof(__i_node*));
        }
    }
    __get_db()->unlock();
#endif
    __node_pointer __np = __n->__as_node();
    __node_alloc_traits::destroy(__na, _VSTD::addressof(__np->__value_));
    __node_alloc_traits::deallocate(__na, __np, 1);
}

template <class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::pop_back()
{
    _LIBCPP_ASSERT(!empty(), "list::pop_back() called with empty list");
    __node_allocator& __na = base::__node_alloc();
    __link_pointer __n = base::__end_.__prev_;
    base::__unlink_nodes(__n, __n);
    --base::__sz();
#if _LIBCPP_DEBUG_LEVEL >= 2
    __c_node* __c = __get_db()->__find_c_and_lock(this);
    for (__i_node** __p = __c->end_; __p != __c->beg_; )
    {
        --__p;
        iterator* __i = static_cast<iterator*>((*__p)->__i_);
        if (__i->__ptr_ == __n)
        {
            (*__p)->__c_ = nullptr;
            if (--__c->end_ != __p)
                memmove(__p, __p+1, (__c->end_ - __p)*sizeof(__i_node*));
        }
    }
    __get_db()->unlock();
#endif
    __node_pointer __np = __n->__as_node();
    __node_alloc_traits::destroy(__na, _VSTD::addressof(__np->__value_));
    __node_alloc_traits::deallocate(__na, __np, 1);
}

template <class _Tp, class _Alloc>
typename list<_Tp, _Alloc>::iterator
list<_Tp, _Alloc>::erase(const_iterator __p)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__p) == this,
        "list::erase(iterator) called with an iterator not"
        " referring to this list");
#endif
    _LIBCPP_ASSERT(__p != end(),
        "list::erase(iterator) called with a non-dereferenceable iterator");
    __node_allocator& __na = base::__node_alloc();
    __link_pointer __n = __p.__ptr_;
    __link_pointer __r = __n->__next_;
    base::__unlink_nodes(__n, __n);
    --base::__sz();
#if _LIBCPP_DEBUG_LEVEL >= 2
    __c_node* __c = __get_db()->__find_c_and_lock(this);
    for (__i_node** __ip = __c->end_; __ip != __c->beg_; )
    {
        --__ip;
        iterator* __i = static_cast<iterator*>((*__ip)->__i_);
        if (__i->__ptr_ == __n)
        {
            (*__ip)->__c_ = nullptr;
            if (--__c->end_ != __ip)
                memmove(__ip, __ip+1, (__c->end_ - __ip)*sizeof(__i_node*));
        }
    }
    __get_db()->unlock();
#endif
    __node_pointer __np = __n->__as_node();
    __node_alloc_traits::destroy(__na, _VSTD::addressof(__np->__value_));
    __node_alloc_traits::deallocate(__na, __np, 1);
#if _LIBCPP_DEBUG_LEVEL >= 2
    return iterator(__r, this);
#else
    return iterator(__r);
#endif
}

template <class _Tp, class _Alloc>
typename list<_Tp, _Alloc>::iterator
list<_Tp, _Alloc>::erase(const_iterator __f, const_iterator __l)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__f) == this,
        "list::erase(iterator, iterator) called with an iterator not"
        " referring to this list");
   _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__l) == this,
        "list::erase(iterator, iterator) called with an iterator not"
        " referring to this list");
#endif
    if (__f != __l)
    {
        __node_allocator& __na = base::__node_alloc();
        base::__unlink_nodes(__f.__ptr_, __l.__ptr_->__prev_);
        while (__f != __l)
        {
            __link_pointer __n = __f.__ptr_;
            ++__f;
            --base::__sz();
#if _LIBCPP_DEBUG_LEVEL >= 2
            __c_node* __c = __get_db()->__find_c_and_lock(this);
            for (__i_node** __p = __c->end_; __p != __c->beg_; )
            {
                --__p;
                iterator* __i = static_cast<iterator*>((*__p)->__i_);
                if (__i->__ptr_ == __n)
                {
                    (*__p)->__c_ = nullptr;
                    if (--__c->end_ != __p)
                        memmove(__p, __p+1, (__c->end_ - __p)*sizeof(__i_node*));
                }
            }
            __get_db()->unlock();
#endif
            __node_pointer __np = __n->__as_node();
            __node_alloc_traits::destroy(__na, _VSTD::addressof(__np->__value_));
            __node_alloc_traits::deallocate(__na, __np, 1);
        }
    }
#if _LIBCPP_DEBUG_LEVEL >= 2
    return iterator(__l.__ptr_, this);
#else
    return iterator(__l.__ptr_);
#endif
}

template <class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::resize(size_type __n)
{
    if (__n < base::__sz())
        erase(__iterator(__n), end());
    else if (__n > base::__sz())
    {
        __n -= base::__sz();
        size_type __ds = 0;
        __node_allocator& __na = base::__node_alloc();
        typedef __allocator_destructor<__node_allocator> _Dp;
        unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
        __hold->__prev_ = 0;
        __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_));
        ++__ds;
#if _LIBCPP_DEBUG_LEVEL >= 2
        iterator __r = iterator(__hold.release()->__as_link(), this);
#else
        iterator __r = iterator(__hold.release()->__as_link());
#endif
        iterator __e = __r;
#ifndef _LIBCPP_NO_EXCEPTIONS
        try
        {
#endif  // _LIBCPP_NO_EXCEPTIONS
            for (--__n; __n != 0; --__n, ++__e, ++__ds)
            {
                __hold.reset(__node_alloc_traits::allocate(__na, 1));
                __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_));
                __e.__ptr_->__next_ = __hold.get()->__as_link();
                __hold->__prev_ = __e.__ptr_;
                __hold.release();
            }
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
            while (true)
            {
                __node_alloc_traits::destroy(__na, _VSTD::addressof(*__e));
                __link_pointer __prev = __e.__ptr_->__prev_;
                __node_alloc_traits::deallocate(__na, __e.__ptr_->__as_node(), 1);
                if (__prev == 0)
                    break;
#if _LIBCPP_DEBUG_LEVEL >= 2
                __e = iterator(__prev, this);
#else
                __e = iterator(__prev);
#endif
            }
            throw;
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
        __link_nodes_at_back(__r.__ptr_, __e.__ptr_);
        base::__sz() += __ds;
    }
}

template <class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::resize(size_type __n, const value_type& __x)
{
    if (__n < base::__sz())
        erase(__iterator(__n), end());
    else if (__n > base::__sz())
    {
        __n -= base::__sz();
        size_type __ds = 0;
        __node_allocator& __na = base::__node_alloc();
        typedef __allocator_destructor<__node_allocator> _Dp;
        unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
        __hold->__prev_ = 0;
        __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_), __x);
        ++__ds;
        __link_pointer __nl = __hold.release()->__as_link();
#if _LIBCPP_DEBUG_LEVEL >= 2
        iterator __r = iterator(__nl, this);
#else
        iterator __r = iterator(__nl);
#endif
        iterator __e = __r;
#ifndef _LIBCPP_NO_EXCEPTIONS
        try
        {
#endif  // _LIBCPP_NO_EXCEPTIONS
            for (--__n; __n != 0; --__n, ++__e, ++__ds)
            {
                __hold.reset(__node_alloc_traits::allocate(__na, 1));
                __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_), __x);
                __e.__ptr_->__next_ = __hold.get()->__as_link();
                __hold->__prev_ = __e.__ptr_;
                __hold.release();
            }
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
            while (true)
            {
                __node_alloc_traits::destroy(__na, _VSTD::addressof(*__e));
                __link_pointer __prev = __e.__ptr_->__prev_;
                __node_alloc_traits::deallocate(__na, __e.__ptr_->__as_node(), 1);
                if (__prev == 0)
                    break;
#if _LIBCPP_DEBUG_LEVEL >= 2
                __e = iterator(__prev, this);
#else
                __e = iterator(__prev);
#endif
            }
            throw;
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
        __link_nodes(base::__end_as_link(), __r.__ptr_, __e.__ptr_);
        base::__sz() += __ds;
    }
}

template <class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::splice(const_iterator __p, list& __c)
{
    _LIBCPP_ASSERT(this != &__c,
                   "list::splice(iterator, list) called with this == &list");
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__p) == this,
        "list::splice(iterator, list) called with an iterator not"
        " referring to this list");
#endif
    if (!__c.empty())
    {
        __link_pointer __f = __c.__end_.__next_;
        __link_pointer __l = __c.__end_.__prev_;
        base::__unlink_nodes(__f, __l);
        __link_nodes(__p.__ptr_, __f, __l);
        base::__sz() += __c.__sz();
        __c.__sz() = 0;
#if _LIBCPP_DEBUG_LEVEL >= 2
        __libcpp_db* __db = __get_db();
        __c_node* __cn1 = __db->__find_c_and_lock(this);
        __c_node* __cn2 = __db->__find_c(&__c);
        for (__i_node** __ip = __cn2->end_; __ip != __cn2->beg_;)
        {
            --__ip;
            iterator* __i = static_cast<iterator*>((*__ip)->__i_);
            if (__i->__ptr_ != __c.__end_as_link())
            {
                __cn1->__add(*__ip);
                (*__ip)->__c_ = __cn1;
                if (--__cn2->end_ != __ip)
                    memmove(__ip, __ip+1, (__cn2->end_ - __ip)*sizeof(__i_node*));
            }
        }
        __db->unlock();
#endif
    }
}

template <class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::splice(const_iterator __p, list& __c, const_iterator __i)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__p) == this,
        "list::splice(iterator, list, iterator) called with first iterator not"
        " referring to this list");
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__i) == &__c,
        "list::splice(iterator, list, iterator) called with second iterator not"
        " referring to list argument");
    _LIBCPP_ASSERT(__get_const_db()->__dereferenceable(&__i),
        "list::splice(iterator, list, iterator) called with second iterator not"
        " derefereceable");
#endif
    if (__p.__ptr_ != __i.__ptr_ && __p.__ptr_ != __i.__ptr_->__next_)
    {
        __link_pointer __f = __i.__ptr_;
        base::__unlink_nodes(__f, __f);
        __link_nodes(__p.__ptr_, __f, __f);
        --__c.__sz();
        ++base::__sz();
#if _LIBCPP_DEBUG_LEVEL >= 2
        __libcpp_db* __db = __get_db();
        __c_node* __cn1 = __db->__find_c_and_lock(this);
        __c_node* __cn2 = __db->__find_c(&__c);
        for (__i_node** __ip = __cn2->end_; __ip != __cn2->beg_;)
        {
            --__ip;
            iterator* __j = static_cast<iterator*>((*__ip)->__i_);
            if (__j->__ptr_ == __f)
            {
                __cn1->__add(*__ip);
                (*__ip)->__c_ = __cn1;
                if (--__cn2->end_ != __ip)
                    memmove(__ip, __ip+1, (__cn2->end_ - __ip)*sizeof(__i_node*));
            }
        }
        __db->unlock();
#endif
    }
}

template <class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::splice(const_iterator __p, list& __c, const_iterator __f, const_iterator __l)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__p) == this,
        "list::splice(iterator, list, iterator, iterator) called with first iterator not"
        " referring to this list");
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__f) == &__c,
        "list::splice(iterator, list, iterator, iterator) called with second iterator not"
        " referring to list argument");
    if (this == &__c)
    {
        for (const_iterator __i = __f; __i != __l; ++__i)
            _LIBCPP_ASSERT(__i != __p,
                           "list::splice(iterator, list, iterator, iterator)"
                           " called with the first iterator within the range"
                           " of the second and third iterators");
    }
#endif
    if (__f != __l)
    {
        if (this != &__c)
        {
            size_type __s = _VSTD::distance(__f, __l);
            __c.__sz() -= __s;
            base::__sz() += __s;
        }
        __link_pointer __first = __f.__ptr_;
        --__l;
        __link_pointer __last = __l.__ptr_;
        base::__unlink_nodes(__first, __last);
        __link_nodes(__p.__ptr_, __first, __last);
#if _LIBCPP_DEBUG_LEVEL >= 2
        __libcpp_db* __db = __get_db();
        __c_node* __cn1 = __db->__find_c_and_lock(this);
        __c_node* __cn2 = __db->__find_c(&__c);
        for (__i_node** __ip = __cn2->end_; __ip != __cn2->beg_;)
        {
            --__ip;
            iterator* __j = static_cast<iterator*>((*__ip)->__i_);
            for (__link_pointer __k = __f.__ptr_;
                                          __k != __l.__ptr_; __k = __k->__next_)
            {
                if (__j->__ptr_ == __k)
                {
                    __cn1->__add(*__ip);
                    (*__ip)->__c_ = __cn1;
                    if (--__cn2->end_ != __ip)
                        memmove(__ip, __ip+1, (__cn2->end_ - __ip)*sizeof(__i_node*));
                }
            }
        }
        __db->unlock();
#endif
    }
}

template <class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::remove(const value_type& __x)
{
    list<_Tp, _Alloc> __deleted_nodes(get_allocator()); // collect the nodes we're removing
    for (const_iterator __i = begin(), __e = end(); __i != __e;)
    {
        if (*__i == __x)
        {
            const_iterator __j = _VSTD::next(__i);
            for (; __j != __e && *__j == __x; ++__j)
                ;
            __deleted_nodes.splice(__deleted_nodes.end(), *this, __i, __j);
            __i = __j;
            if (__i != __e)
                ++__i;
        }
        else
            ++__i;
    }
}

template <class _Tp, class _Alloc>
template <class _Pred>
void
list<_Tp, _Alloc>::remove_if(_Pred __pred)
{
    for (iterator __i = begin(), __e = end(); __i != __e;)
    {
        if (__pred(*__i))
        {
            iterator __j = _VSTD::next(__i);
            for (; __j != __e && __pred(*__j); ++__j)
                ;
            __i = erase(__i, __j);
            if (__i != __e)
                ++__i;
        }
        else
            ++__i;
    }
}

template <class _Tp, class _Alloc>
inline
void
list<_Tp, _Alloc>::unique()
{
    unique(__equal_to<value_type>());
}

template <class _Tp, class _Alloc>
template <class _BinaryPred>
void
list<_Tp, _Alloc>::unique(_BinaryPred __binary_pred)
{
    for (iterator __i = begin(), __e = end(); __i != __e;)
    {
        iterator __j = _VSTD::next(__i);
        for (; __j != __e && __binary_pred(*__i, *__j); ++__j)
            ;
        if (++__i != __j)
            __i = erase(__i, __j);
    }
}

template <class _Tp, class _Alloc>
inline
void
list<_Tp, _Alloc>::merge(list& __c)
{
    merge(__c, __less<value_type>());
}

template <class _Tp, class _Alloc>
template <class _Comp>
void
list<_Tp, _Alloc>::merge(list& __c, _Comp __comp)
{
    if (this != &__c)
    {
        iterator __f1 = begin();
        iterator __e1 = end();
        iterator __f2 = __c.begin();
        iterator __e2 = __c.end();
        while (__f1 != __e1 && __f2 != __e2)
        {
            if (__comp(*__f2, *__f1))
            {
                size_type __ds = 1;
                iterator __m2 = _VSTD::next(__f2);
                for (; __m2 != __e2 && __comp(*__m2, *__f1); ++__m2, ++__ds)
                    ;
                base::__sz() += __ds;
                __c.__sz() -= __ds;
                __link_pointer __f = __f2.__ptr_;
                __link_pointer __l = __m2.__ptr_->__prev_;
                __f2 = __m2;
                base::__unlink_nodes(__f, __l);
                __m2 = _VSTD::next(__f1);
                __link_nodes(__f1.__ptr_, __f, __l);
                __f1 = __m2;
            }
            else
                ++__f1;
        }
        splice(__e1, __c);
#if _LIBCPP_DEBUG_LEVEL >= 2
        __libcpp_db* __db = __get_db();
        __c_node* __cn1 = __db->__find_c_and_lock(this);
        __c_node* __cn2 = __db->__find_c(&__c);
        for (__i_node** __p = __cn2->end_; __p != __cn2->beg_;)
        {
            --__p;
            iterator* __i = static_cast<iterator*>((*__p)->__i_);
            if (__i->__ptr_ != __c.__end_as_link())
            {
                __cn1->__add(*__p);
                (*__p)->__c_ = __cn1;
                if (--__cn2->end_ != __p)
                    memmove(__p, __p+1, (__cn2->end_ - __p)*sizeof(__i_node*));
            }
        }
        __db->unlock();
#endif
    }
}

template <class _Tp, class _Alloc>
inline
void
list<_Tp, _Alloc>::sort()
{
    sort(__less<value_type>());
}

template <class _Tp, class _Alloc>
template <class _Comp>
inline
void
list<_Tp, _Alloc>::sort(_Comp __comp)
{
    __sort(begin(), end(), base::__sz(), __comp);
}

template <class _Tp, class _Alloc>
template <class _Comp>
typename list<_Tp, _Alloc>::iterator
list<_Tp, _Alloc>::__sort(iterator __f1, iterator __e2, size_type __n, _Comp& __comp)
{
    switch (__n)
    {
    case 0:
    case 1:
        return __f1;
    case 2:
        if (__comp(*--__e2, *__f1))
        {
            __link_pointer __f = __e2.__ptr_;
            base::__unlink_nodes(__f, __f);
            __link_nodes(__f1.__ptr_, __f, __f);
            return __e2;
        }
        return __f1;
    }
    size_type __n2 = __n / 2;
    iterator __e1 = _VSTD::next(__f1, __n2);
    iterator  __r = __f1 = __sort(__f1, __e1, __n2, __comp);
    iterator __f2 = __e1 = __sort(__e1, __e2, __n - __n2, __comp);
    if (__comp(*__f2, *__f1))
    {
        iterator __m2 = _VSTD::next(__f2);
        for (; __m2 != __e2 && __comp(*__m2, *__f1); ++__m2)
            ;
        __link_pointer __f = __f2.__ptr_;
        __link_pointer __l = __m2.__ptr_->__prev_;
        __r = __f2;
        __e1 = __f2 = __m2;
        base::__unlink_nodes(__f, __l);
        __m2 = _VSTD::next(__f1);
        __link_nodes(__f1.__ptr_, __f, __l);
        __f1 = __m2;
    }
    else
        ++__f1;
    while (__f1 != __e1 && __f2 != __e2)
    {
        if (__comp(*__f2, *__f1))
        {
            iterator __m2 = _VSTD::next(__f2);
            for (; __m2 != __e2 && __comp(*__m2, *__f1); ++__m2)
                ;
            __link_pointer __f = __f2.__ptr_;
            __link_pointer __l = __m2.__ptr_->__prev_;
            if (__e1 == __f2)
                __e1 = __m2;
            __f2 = __m2;
            base::__unlink_nodes(__f, __l);
            __m2 = _VSTD::next(__f1);
            __link_nodes(__f1.__ptr_, __f, __l);
            __f1 = __m2;
        }
        else
            ++__f1;
    }
    return __r;
}

template <class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::reverse() _NOEXCEPT
{
    if (base::__sz() > 1)
    {
        iterator __e = end();
        for (iterator __i = begin(); __i.__ptr_ != __e.__ptr_;)
        {
            _VSTD::swap(__i.__ptr_->__prev_, __i.__ptr_->__next_);
            __i.__ptr_ = __i.__ptr_->__prev_;
        }
        _VSTD::swap(__e.__ptr_->__prev_, __e.__ptr_->__next_);
    }
}

template <class _Tp, class _Alloc>
bool
list<_Tp, _Alloc>::__invariants() const
{
    return size() == _VSTD::distance(begin(), end());
}

#if _LIBCPP_DEBUG_LEVEL >= 2

template <class _Tp, class _Alloc>
bool
list<_Tp, _Alloc>::__dereferenceable(const const_iterator* __i) const
{
    return __i->__ptr_ != this->__end_as_link();
}

template <class _Tp, class _Alloc>
bool
list<_Tp, _Alloc>::__decrementable(const const_iterator* __i) const
{
    return !empty() &&  __i->__ptr_ != base::__end_.__next_;
}

template <class _Tp, class _Alloc>
bool
list<_Tp, _Alloc>::__addable(const const_iterator*, ptrdiff_t) const
{
    return false;
}

template <class _Tp, class _Alloc>
bool
list<_Tp, _Alloc>::__subscriptable(const const_iterator*, ptrdiff_t) const
{
    return false;
}

#endif  // _LIBCPP_DEBUG_LEVEL >= 2

template <class _Tp, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator==(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
{
    return __x.size() == __y.size() && _VSTD::equal(__x.begin(), __x.end(), __y.begin());
}

template <class _Tp, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator< (const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
{
    return _VSTD::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
}

template <class _Tp, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator!=(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
{
    return !(__x == __y);
}

template <class _Tp, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator> (const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
{
    return __y < __x;
}

template <class _Tp, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator>=(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
{
    return !(__x < __y);
}

template <class _Tp, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator<=(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
{
    return !(__y < __x);
}

template <class _Tp, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
void
swap(list<_Tp, _Alloc>& __x, list<_Tp, _Alloc>& __y)
    _NOEXCEPT_(_NOEXCEPT_(__x.swap(__y)))
{
    __x.swap(__y);
}

_LIBCPP_END_NAMESPACE_STD

_LIBCPP_POP_MACROS

#endif  // _LIBCPP_LIST
