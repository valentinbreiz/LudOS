// -*- C++ -*-
//===--------------------------- random -----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_RANDOM
#define _LIBCPP_RANDOM

#include "utility.hpp"

/*
    random synopsis

#include <initializer_list>

namespace std
{

// Engines

template <class UIntType, UIntType a, UIntType c, UIntType m>
class linear_congruential_engine
{
public:
    // types
    typedef UIntType result_type;

    // engine characteristics
    static constexpr result_type multiplier = a;
    static constexpr result_type increment = c;
    static constexpr result_type modulus = m;
    static constexpr result_type min() { return c == 0u ? 1u: 0u;}
    static constexpr result_type max() { return m - 1u;}
    static constexpr result_type default_seed = 1u;

    // constructors and seeding functions
    explicit linear_congruential_engine(result_type s = default_seed);
    template<class Sseq> explicit linear_congruential_engine(Sseq& q);
    void seed(result_type s = default_seed);
    template<class Sseq> void seed(Sseq& q);

    // generating functions
    result_type operator()();
    void discard(unsigned long long z);
};

template <class UIntType, UIntType a, UIntType c, UIntType m>
bool
operator==(const linear_congruential_engine<UIntType, a, c, m>& x,
           const linear_congruential_engine<UIntType, a, c, m>& y);

template <class UIntType, UIntType a, UIntType c, UIntType m>
bool
operator!=(const linear_congruential_engine<UIntType, a, c, m>& x,
           const linear_congruential_engine<UIntType, a, c, m>& y);

template <class charT, class traits,
          class UIntType, UIntType a, UIntType c, UIntType m>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os,
           const linear_congruential_engine<UIntType, a, c, m>& x);

template <class charT, class traits,
          class UIntType, UIntType a, UIntType c, UIntType m>
basic_istream<charT, traits>&
operator>>(basic_istream<charT, traits>& is,
           linear_congruential_engine<UIntType, a, c, m>& x);

template <class UIntType, size_t w, size_t n, size_t m, size_t r,
          UIntType a, size_t u, UIntType d, size_t s,
          UIntType b, size_t t, UIntType c, size_t l, UIntType f>
class mersenne_twister_engine
{
public:
    // types
    typedef UIntType result_type;

    // engine characteristics
    static constexpr size_t word_size = w;
    static constexpr size_t state_size = n;
    static constexpr size_t shift_size = m;
    static constexpr size_t mask_bits = r;
    static constexpr result_type xor_mask = a;
    static constexpr size_t tempering_u = u;
    static constexpr result_type tempering_d = d;
    static constexpr size_t tempering_s = s;
    static constexpr result_type tempering_b = b;
    static constexpr size_t tempering_t = t;
    static constexpr result_type tempering_c = c;
    static constexpr size_t tempering_l = l;
    static constexpr result_type initialization_multiplier = f;
    static constexpr result_type min () { return 0; }
    static constexpr result_type max() { return 2^w - 1; }
    static constexpr result_type default_seed = 5489u;

    // constructors and seeding functions
    explicit mersenne_twister_engine(result_type value = default_seed);
    template<class Sseq> explicit mersenne_twister_engine(Sseq& q);
    void seed(result_type value = default_seed);
    template<class Sseq> void seed(Sseq& q);

    // generating functions
    result_type operator()();
    void discard(unsigned long long z);
};

template <class UIntType, size_t w, size_t n, size_t m, size_t r,
          UIntType a, size_t u, UIntType d, size_t s,
          UIntType b, size_t t, UIntType c, size_t l, UIntType f>
bool
operator==(
    const mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>& x,
    const mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>& y);

template <class UIntType, size_t w, size_t n, size_t m, size_t r,
          UIntType a, size_t u, UIntType d, size_t s,
          UIntType b, size_t t, UIntType c, size_t l, UIntType f>
bool
operator!=(
    const mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>& x,
    const mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>& y);

template <class charT, class traits,
          class UIntType, size_t w, size_t n, size_t m, size_t r,
          UIntType a, size_t u, UIntType d, size_t s,
          UIntType b, size_t t, UIntType c, size_t l, UIntType f>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os,
           const mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>& x);

template <class charT, class traits,
          class UIntType, size_t w, size_t n, size_t m, size_t r,
          UIntType a, size_t u, UIntType d, size_t s,
          UIntType b, size_t t, UIntType c, size_t l, UIntType f>
basic_istream<charT, traits>&
operator>>(basic_istream<charT, traits>& is,
           mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>& x);

template<class UIntType, size_t w, size_t s, size_t r>
class subtract_with_carry_engine
{
public:
    // types
    typedef UIntType result_type;

    // engine characteristics
    static constexpr size_t word_size = w;
    static constexpr size_t short_lag = s;
    static constexpr size_t long_lag = r;
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return m-1; }
    static constexpr result_type default_seed = 19780503u;

    // constructors and seeding functions
    explicit subtract_with_carry_engine(result_type value = default_seed);
    template<class Sseq> explicit subtract_with_carry_engine(Sseq& q);
    void seed(result_type value = default_seed);
    template<class Sseq> void seed(Sseq& q);

    // generating functions
    result_type operator()();
    void discard(unsigned long long z);
};

template<class UIntType, size_t w, size_t s, size_t r>
bool
operator==(
    const subtract_with_carry_engine<UIntType, w, s, r>& x,
    const subtract_with_carry_engine<UIntType, w, s, r>& y);

template<class UIntType, size_t w, size_t s, size_t r>
bool
operator!=(
    const subtract_with_carry_engine<UIntType, w, s, r>& x,
    const subtract_with_carry_engine<UIntType, w, s, r>& y);

template <class charT, class traits,
          class UIntType, size_t w, size_t s, size_t r>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os,
           const subtract_with_carry_engine<UIntType, w, s, r>& x);

template <class charT, class traits,
          class UIntType, size_t w, size_t s, size_t r>
basic_istream<charT, traits>&
operator>>(basic_istream<charT, traits>& is,
           subtract_with_carry_engine<UIntType, w, s, r>& x);

template<class Engine, size_t p, size_t r>
class discard_block_engine
{
public:
    // types
    typedef typename Engine::result_type result_type;

    // engine characteristics
    static constexpr size_t block_size = p;
    static constexpr size_t used_block = r;
    static constexpr result_type min() { return Engine::min(); }
    static constexpr result_type max() { return Engine::max(); }

    // constructors and seeding functions
    discard_block_engine();
    explicit discard_block_engine(const Engine& e);
    explicit discard_block_engine(Engine&& e);
    explicit discard_block_engine(result_type s);
    template<class Sseq> explicit discard_block_engine(Sseq& q);
    void seed();
    void seed(result_type s);
    template<class Sseq> void seed(Sseq& q);

    // generating functions
    result_type operator()();
    void discard(unsigned long long z);

    // property functions
    const Engine& base() const noexcept;
};

template<class Engine, size_t p, size_t r>
bool
operator==(
    const discard_block_engine<Engine, p, r>& x,
    const discard_block_engine<Engine, p, r>& y);

template<class Engine, size_t p, size_t r>
bool
operator!=(
    const discard_block_engine<Engine, p, r>& x,
    const discard_block_engine<Engine, p, r>& y);

template <class charT, class traits,
          class Engine, size_t p, size_t r>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os,
           const discard_block_engine<Engine, p, r>& x);

template <class charT, class traits,
          class Engine, size_t p, size_t r>
basic_istream<charT, traits>&
operator>>(basic_istream<charT, traits>& is,
           discard_block_engine<Engine, p, r>& x);

template<class Engine, size_t w, class UIntType>
class independent_bits_engine
{
public:
    // types
    typedef UIntType result_type;

    // engine characteristics
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return 2^w - 1; }

    // constructors and seeding functions
    independent_bits_engine();
    explicit independent_bits_engine(const Engine& e);
    explicit independent_bits_engine(Engine&& e);
    explicit independent_bits_engine(result_type s);
    template<class Sseq> explicit independent_bits_engine(Sseq& q);
    void seed();
    void seed(result_type s);
    template<class Sseq> void seed(Sseq& q);

    // generating functions
    result_type operator()(); void discard(unsigned long long z);

    // property functions
    const Engine& base() const noexcept;
};

template<class Engine, size_t w, class UIntType>
bool
operator==(
    const independent_bits_engine<Engine, w, UIntType>& x,
    const independent_bits_engine<Engine, w, UIntType>& y);

template<class Engine, size_t w, class UIntType>
bool
operator!=(
    const independent_bits_engine<Engine, w, UIntType>& x,
    const independent_bits_engine<Engine, w, UIntType>& y);

template <class charT, class traits,
          class Engine, size_t w, class UIntType>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os,
           const independent_bits_engine<Engine, w, UIntType>& x);

template <class charT, class traits,
          class Engine, size_t w, class UIntType>
basic_istream<charT, traits>&
operator>>(basic_istream<charT, traits>& is,
           independent_bits_engine<Engine, w, UIntType>& x);

template<class Engine, size_t k>
class shuffle_order_engine
{
public:
    // types
    typedef typename Engine::result_type result_type;

    // engine characteristics
    static constexpr size_t table_size = k;
    static constexpr result_type min() { return Engine::min; }
    static constexpr result_type max() { return Engine::max; }

    // constructors and seeding functions
    shuffle_order_engine();
    explicit shuffle_order_engine(const Engine& e);
    explicit shuffle_order_engine(Engine&& e);
    explicit shuffle_order_engine(result_type s);
    template<class Sseq> explicit shuffle_order_engine(Sseq& q);
    void seed();
    void seed(result_type s);
    template<class Sseq> void seed(Sseq& q);

    // generating functions
    result_type operator()();
    void discard(unsigned long long z);

    // property functions
    const Engine& base() const noexcept;
};

template<class Engine, size_t k>
bool
operator==(
    const shuffle_order_engine<Engine, k>& x,
    const shuffle_order_engine<Engine, k>& y);

template<class Engine, size_t k>
bool
operator!=(
    const shuffle_order_engine<Engine, k>& x,
    const shuffle_order_engine<Engine, k>& y);

template <class charT, class traits,
          class Engine, size_t k>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os,
           const shuffle_order_engine<Engine, k>& x);

template <class charT, class traits,
          class Engine, size_t k>
basic_istream<charT, traits>&
operator>>(basic_istream<charT, traits>& is,
           shuffle_order_engine<Engine, k>& x);

typedef linear_congruential_engine<uint32_t, 16807, 0, 2147483647>
                                                                   minstd_rand0;
typedef linear_congruential_engine<uint32_t, 48271, 0, 2147483647>
                                                                    minstd_rand;
typedef mersenne_twister_engine<uint32_t, 32, 624, 397, 31,
                                0x9908b0df,
                                11, 0xffffffff,
                                7,  0x9d2c5680,
                                15, 0xefc60000,
                                18, 1812433253>                         mt19937;
typedef mersenne_twister_engine<uint_fast64_t, 64, 312, 156, 31,
                                0xb5026f5aa96619e9,
                                29, 0x5555555555555555,
                                17, 0x71d67fffeda60000,
                                37, 0xfff7eee000000000,
                                43, 6364136223846793005>             mt19937_64;
typedef subtract_with_carry_engine<uint32_t, 24, 10, 24>     ranlux24_base;
typedef subtract_with_carry_engine<uint_fast64_t, 48,  5, 12>     ranlux48_base;
typedef discard_block_engine<ranlux24_base, 223, 23>                   ranlux24;
typedef discard_block_engine<ranlux48_base, 389, 11>                   ranlux48;
typedef shuffle_order_engine<minstd_rand0, 256>                         knuth_b;
typedef minstd_rand                                       default_random_engine;

// Generators

class random_device
{
public:
    // types
    typedef unsigned int result_type;

    // generator characteristics
    static constexpr result_type min() { return numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return numeric_limits<result_type>::max(); }

    // constructors
    explicit random_device(const string& token = "/dev/urandom");

    // generating functions
    result_type operator()();

    // property functions
    double entropy() const noexcept;

    // no copy functions
    random_device(const random_device& ) = delete;
    void operator=(const random_device& ) = delete;
};

// Utilities

class seed_seq
{
public:
    // types
    typedef uint_least32_t result_type;

    // constructors
    seed_seq();
    template<class T>
        seed_seq(initializer_list<T> il);
    template<class InputIterator>
        seed_seq(InputIterator begin, InputIterator end);

    // generating functions
    template<class RandomAccessIterator>
        void generate(RandomAccessIterator begin, RandomAccessIterator end);

    // property functions
    size_t size() const;
    template<class OutputIterator>
        void param(OutputIterator dest) const;

    // no copy functions
    seed_seq(const seed_seq&) = delete;
    void operator=(const seed_seq& ) = delete;
};

template<class RealType, size_t bits, class URNG>
    RealType generate_canonical(URNG& g);

// Distributions

template<class IntType = int>
class uniform_int_distribution
{
public:
    // types
    typedef IntType result_type;

    class param_type
    {
    public:
        typedef uniform_int_distribution distribution_type;

        explicit param_type(IntType a = 0,
                                    IntType b = numeric_limits<IntType>::max());

        result_type a() const;
        result_type b() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructors and reset functions
    explicit uniform_int_distribution(IntType a = 0,
                                    IntType b = numeric_limits<IntType>::max());
    explicit uniform_int_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    result_type a() const;
    result_type b() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const uniform_int_distribution& x,
                           const uniform_int_distribution& y);
    friend bool operator!=(const uniform_int_distribution& x,
                           const uniform_int_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const uniform_int_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               uniform_int_distribution& x);
};

template<class RealType = double>
class uniform_real_distribution
{
public:
    // types
    typedef RealType result_type;

    class param_type
    {
    public:
        typedef uniform_real_distribution distribution_type;

        explicit param_type(RealType a = 0,
                            RealType b = 1);

        result_type a() const;
        result_type b() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructors and reset functions
    explicit uniform_real_distribution(RealType a = 0.0, RealType b = 1.0);
    explicit uniform_real_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    result_type a() const;
    result_type b() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const uniform_real_distribution& x,
                           const uniform_real_distribution& y);
    friend bool operator!=(const uniform_real_distribution& x,
                           const uniform_real_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const uniform_real_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               uniform_real_distribution& x);
};

class bernoulli_distribution
{
public:
    // types
    typedef bool result_type;

    class param_type
    {
    public:
        typedef bernoulli_distribution distribution_type;

        explicit param_type(double p = 0.5);

        double p() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructors and reset functions
    explicit bernoulli_distribution(double p = 0.5);
    explicit bernoulli_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    double p() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const bernoulli_distribution& x,
                           const bernoulli_distribution& y);
    friend bool operator!=(const bernoulli_distribution& x,
                           const bernoulli_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const bernoulli_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               bernoulli_distribution& x);
};

template<class IntType = int>
class binomial_distribution
{
public:
    // types
    typedef IntType result_type;

    class param_type
    {
    public:
        typedef binomial_distribution distribution_type;

        explicit param_type(IntType t = 1, double p = 0.5);

        IntType t() const;
        double p() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructors and reset functions
    explicit binomial_distribution(IntType t = 1, double p = 0.5);
    explicit binomial_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    IntType t() const;
    double p() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const binomial_distribution& x,
                           const binomial_distribution& y);
    friend bool operator!=(const binomial_distribution& x,
                           const binomial_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const binomial_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               binomial_distribution& x);
};

template<class IntType = int>
class geometric_distribution
{
public:
    // types
    typedef IntType result_type;

    class param_type
    {
    public:
        typedef geometric_distribution distribution_type;

        explicit param_type(double p = 0.5);

        double p() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructors and reset functions
    explicit geometric_distribution(double p = 0.5);
    explicit geometric_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    double p() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const geometric_distribution& x,
                           const geometric_distribution& y);
    friend bool operator!=(const geometric_distribution& x,
                           const geometric_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const geometric_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               geometric_distribution& x);
};

template<class IntType = int>
class negative_binomial_distribution
{
public:
    // types
    typedef IntType result_type;

    class param_type
    {
    public:
        typedef negative_binomial_distribution distribution_type;

        explicit param_type(result_type k = 1, double p = 0.5);

        result_type k() const;
        double p() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructor and reset functions
    explicit negative_binomial_distribution(result_type k = 1, double p = 0.5);
    explicit negative_binomial_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    result_type k() const;
    double p() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const negative_binomial_distribution& x,
                           const negative_binomial_distribution& y);
    friend bool operator!=(const negative_binomial_distribution& x,
                           const negative_binomial_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const negative_binomial_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               negative_binomial_distribution& x);
};

template<class IntType = int>
class poisson_distribution
{
public:
    // types
    typedef IntType result_type;

    class param_type
    {
    public:
        typedef poisson_distribution distribution_type;

        explicit param_type(double mean = 1.0);

        double mean() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructors and reset functions
    explicit poisson_distribution(double mean = 1.0);
    explicit poisson_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    double mean() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const poisson_distribution& x,
                           const poisson_distribution& y);
    friend bool operator!=(const poisson_distribution& x,
                           const poisson_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const poisson_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               poisson_distribution& x);
};

template<class RealType = double>
class exponential_distribution
{
public:
    // types
    typedef RealType result_type;

    class param_type
    {
    public:
        typedef exponential_distribution distribution_type;

        explicit param_type(result_type lambda = 1.0);

        result_type lambda() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructors and reset functions
    explicit exponential_distribution(result_type lambda = 1.0);
    explicit exponential_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    result_type lambda() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const exponential_distribution& x,
                           const exponential_distribution& y);
    friend bool operator!=(const exponential_distribution& x,
                           const exponential_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const exponential_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               exponential_distribution& x);
};

template<class RealType = double>
class gamma_distribution
{
public:
    // types
    typedef RealType result_type;

    class param_type
    {
    public:
        typedef gamma_distribution distribution_type;

        explicit param_type(result_type alpha = 1, result_type beta = 1);

        result_type alpha() const;
        result_type beta() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructors and reset functions
    explicit gamma_distribution(result_type alpha = 1, result_type beta = 1);
    explicit gamma_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    result_type alpha() const;
    result_type beta() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const gamma_distribution& x,
                           const gamma_distribution& y);
    friend bool operator!=(const gamma_distribution& x,
                           const gamma_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const gamma_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               gamma_distribution& x);
};

template<class RealType = double>
class weibull_distribution
{
public:
    // types
    typedef RealType result_type;

    class param_type
    {
    public:
        typedef weibull_distribution distribution_type;

        explicit param_type(result_type alpha = 1, result_type beta = 1);

        result_type a() const;
        result_type b() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructor and reset functions
    explicit weibull_distribution(result_type a = 1, result_type b = 1);
    explicit weibull_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    result_type a() const;
    result_type b() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const weibull_distribution& x,
                           const weibull_distribution& y);
    friend bool operator!=(const weibull_distribution& x,
                           const weibull_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const weibull_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               weibull_distribution& x);
};

template<class RealType = double>
class extreme_value_distribution
{
public:
    // types
    typedef RealType result_type;

    class param_type
    {
    public:
        typedef extreme_value_distribution distribution_type;

        explicit param_type(result_type a = 0, result_type b = 1);

        result_type a() const;
        result_type b() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructor and reset functions
    explicit extreme_value_distribution(result_type a = 0, result_type b = 1);
    explicit extreme_value_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    result_type a() const;
    result_type b() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const extreme_value_distribution& x,
                           const extreme_value_distribution& y);
    friend bool operator!=(const extreme_value_distribution& x,
                           const extreme_value_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const extreme_value_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               extreme_value_distribution& x);
};

template<class RealType = double>
class normal_distribution
{
public:
    // types
    typedef RealType result_type;

    class param_type
    {
    public:
        typedef normal_distribution distribution_type;

        explicit param_type(result_type mean = 0, result_type stddev = 1);

        result_type mean() const;
        result_type stddev() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructors and reset functions
    explicit normal_distribution(result_type mean = 0, result_type stddev = 1);
    explicit normal_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    result_type mean() const;
    result_type stddev() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const normal_distribution& x,
                           const normal_distribution& y);
    friend bool operator!=(const normal_distribution& x,
                           const normal_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const normal_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               normal_distribution& x);
};

template<class RealType = double>
class lognormal_distribution
{
public:
    // types
    typedef RealType result_type;

    class param_type
    {
    public:
        typedef lognormal_distribution distribution_type;

        explicit param_type(result_type m = 0, result_type s = 1);

        result_type m() const;
        result_type s() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructor and reset functions
    explicit lognormal_distribution(result_type m = 0, result_type s = 1);
    explicit lognormal_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    result_type m() const;
    result_type s() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const lognormal_distribution& x,
                           const lognormal_distribution& y);
    friend bool operator!=(const lognormal_distribution& x,
                           const lognormal_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const lognormal_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               lognormal_distribution& x);
};

template<class RealType = double>
class chi_squared_distribution
{
public:
    // types
    typedef RealType result_type;

    class param_type
    {
    public:
        typedef chi_squared_distribution distribution_type;

        explicit param_type(result_type n = 1);

        result_type n() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructor and reset functions
    explicit chi_squared_distribution(result_type n = 1);
    explicit chi_squared_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    result_type n() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const chi_squared_distribution& x,
                           const chi_squared_distribution& y);
    friend bool operator!=(const chi_squared_distribution& x,
                           const chi_squared_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const chi_squared_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               chi_squared_distribution& x);
};

template<class RealType = double>
class cauchy_distribution
{
public:
    // types
    typedef RealType result_type;

    class param_type
    {
    public:
        typedef cauchy_distribution distribution_type;

        explicit param_type(result_type a = 0, result_type b = 1);

        result_type a() const;
        result_type b() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructor and reset functions
    explicit cauchy_distribution(result_type a = 0, result_type b = 1);
    explicit cauchy_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    result_type a() const;
    result_type b() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const cauchy_distribution& x,
                           const cauchy_distribution& y);
    friend bool operator!=(const cauchy_distribution& x,
                           const cauchy_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const cauchy_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               cauchy_distribution& x);
};

template<class RealType = double>
class fisher_f_distribution
{
public:
    // types
    typedef RealType result_type;

    class param_type
    {
    public:
        typedef fisher_f_distribution distribution_type;

        explicit param_type(result_type m = 1, result_type n = 1);

        result_type m() const;
        result_type n() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructor and reset functions
    explicit fisher_f_distribution(result_type m = 1, result_type n = 1);
    explicit fisher_f_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    result_type m() const;
    result_type n() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const fisher_f_distribution& x,
                           const fisher_f_distribution& y);
    friend bool operator!=(const fisher_f_distribution& x,
                           const fisher_f_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const fisher_f_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               fisher_f_distribution& x);
};

template<class RealType = double>
class student_t_distribution
{
public:
    // types
    typedef RealType result_type;

    class param_type
    {
    public:
        typedef student_t_distribution distribution_type;

        explicit param_type(result_type n = 1);

        result_type n() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructor and reset functions
    explicit student_t_distribution(result_type n = 1);
    explicit student_t_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    result_type n() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const student_t_distribution& x,
                           const student_t_distribution& y);
    friend bool operator!=(const student_t_distribution& x,
                           const student_t_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const student_t_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               student_t_distribution& x);
};

template<class IntType = int>
class discrete_distribution
{
public:
    // types
    typedef IntType result_type;

    class param_type
    {
    public:
        typedef discrete_distribution distribution_type;

        param_type();
        template<class InputIterator>
            param_type(InputIterator firstW, InputIterator lastW);
        param_type(initializer_list<double> wl);
        template<class UnaryOperation>
            param_type(size_t nw, double xmin, double xmax, UnaryOperation fw);

        vector<double> probabilities() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructor and reset functions
    discrete_distribution();
    template<class InputIterator>
        discrete_distribution(InputIterator firstW, InputIterator lastW);
    discrete_distribution(initializer_list<double> wl);
    template<class UnaryOperation>
        discrete_distribution(size_t nw, double xmin, double xmax,
                              UnaryOperation fw);
    explicit discrete_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    vector<double> probabilities() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const discrete_distribution& x,
                           const discrete_distribution& y);
    friend bool operator!=(const discrete_distribution& x,
                           const discrete_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const discrete_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               discrete_distribution& x);
};

template<class RealType = double>
class piecewise_constant_distribution
{
    // types
    typedef RealType result_type;

    class param_type
    {
    public:
        typedef piecewise_constant_distribution distribution_type;

        param_type();
        template<class InputIteratorB, class InputIteratorW>
            param_type(InputIteratorB firstB, InputIteratorB lastB,
                       InputIteratorW firstW);
        template<class UnaryOperation>
            param_type(initializer_list<result_type> bl, UnaryOperation fw);
        template<class UnaryOperation>
            param_type(size_t nw, result_type xmin, result_type xmax,
                       UnaryOperation fw);

        vector<result_type> intervals() const;
        vector<result_type> densities() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructor and reset functions
    piecewise_constant_distribution();
    template<class InputIteratorB, class InputIteratorW>
        piecewise_constant_distribution(InputIteratorB firstB,
                                        InputIteratorB lastB,
                                        InputIteratorW firstW);
    template<class UnaryOperation>
        piecewise_constant_distribution(initializer_list<result_type> bl,
                                        UnaryOperation fw);
    template<class UnaryOperation>
        piecewise_constant_distribution(size_t nw, result_type xmin,
                                        result_type xmax, UnaryOperation fw);
    explicit piecewise_constant_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    vector<result_type> intervals() const;
    vector<result_type> densities() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const piecewise_constant_distribution& x,
                           const piecewise_constant_distribution& y);
    friend bool operator!=(const piecewise_constant_distribution& x,
                           const piecewise_constant_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const piecewise_constant_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               piecewise_constant_distribution& x);
};

template<class RealType = double>
class piecewise_linear_distribution
{
    // types
    typedef RealType result_type;

    class param_type
    {
    public:
        typedef piecewise_linear_distribution distribution_type;

        param_type();
        template<class InputIteratorB, class InputIteratorW>
            param_type(InputIteratorB firstB, InputIteratorB lastB,
                       InputIteratorW firstW);
        template<class UnaryOperation>
            param_type(initializer_list<result_type> bl, UnaryOperation fw);
        template<class UnaryOperation>
            param_type(size_t nw, result_type xmin, result_type xmax,
                       UnaryOperation fw);

        vector<result_type> intervals() const;
        vector<result_type> densities() const;

        friend bool operator==(const param_type& x, const param_type& y);
        friend bool operator!=(const param_type& x, const param_type& y);
    };

    // constructor and reset functions
    piecewise_linear_distribution();
    template<class InputIteratorB, class InputIteratorW>
        piecewise_linear_distribution(InputIteratorB firstB,
                                      InputIteratorB lastB,
                                      InputIteratorW firstW);

    template<class UnaryOperation>
        piecewise_linear_distribution(initializer_list<result_type> bl,
                                      UnaryOperation fw);

    template<class UnaryOperation>
        piecewise_linear_distribution(size_t nw, result_type xmin,
                                      result_type xmax, UnaryOperation fw);

    explicit piecewise_linear_distribution(const param_type& parm);
    void reset();

    // generating functions
    template<class URNG> result_type operator()(URNG& g);
    template<class URNG> result_type operator()(URNG& g, const param_type& parm);

    // property functions
    vector<result_type> intervals() const;
    vector<result_type> densities() const;

    param_type param() const;
    void param(const param_type& parm);

    result_type min() const;
    result_type max() const;

    friend bool operator==(const piecewise_linear_distribution& x,
                           const piecewise_linear_distribution& y);
    friend bool operator!=(const piecewise_linear_distribution& x,
                           const piecewise_linear_distribution& y);

    template <class charT, class traits>
    friend
    basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os,
               const piecewise_linear_distribution& x);

    template <class charT, class traits>
    friend
    basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is,
               piecewise_linear_distribution& x);
};

} // std
*/

#include "__config.hpp"
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include "type_traits.hpp"
#include "initializer_list.hpp"
#include "limits.hpp"
#include "algorithm.hpp"
#include "numeric.hpp"
#include "vector.hpp"
#include "string.hpp"
//#include <istream>
//#include <ostream>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_PUSH_MACROS
#include "__undef_macros.hpp"


_LIBCPP_BEGIN_NAMESPACE_STD

// __is_seed_sequence

template <class _Sseq, class _Engine>
struct __is_seed_sequence
{
    static _LIBCPP_CONSTEXPR const bool value =
              !is_convertible<_Sseq, typename _Engine::result_type>::value &&
              !is_same<typename remove_cv<_Sseq>::type, _Engine>::value;
};

// linear_congruential_engine

template <unsigned long long __a, unsigned long long __c,
          unsigned long long __m, unsigned long long _Mp,
          bool _MightOverflow = (__a != 0 && __m != 0 && __m-1 > (_Mp-__c)/__a)>
struct __lce_ta;

// 64

template <unsigned long long __a, unsigned long long __c, unsigned long long __m>
struct __lce_ta<__a, __c, __m, (unsigned long long)(~0), true>
{
    typedef unsigned long long result_type;
    _LIBCPP_INLINE_VISIBILITY
    static result_type next(result_type __x)
    {
        // Schrage's algorithm
        const result_type __q = __m / __a;
        const result_type __r = __m % __a;
        const result_type __t0 = __a * (__x % __q);
        const result_type __t1 = __r * (__x / __q);
        __x = __t0 + (__t0 < __t1) * __m - __t1;
        __x += __c - (__x >= __m - __c) * __m;
        return __x;
    }
};

template <unsigned long long __a, unsigned long long __m>
struct __lce_ta<__a, 0, __m, (unsigned long long)(~0), true>
{
    typedef unsigned long long result_type;
    _LIBCPP_INLINE_VISIBILITY
    static result_type next(result_type __x)
    {
        // Schrage's algorithm
        const result_type __q = __m / __a;
        const result_type __r = __m % __a;
        const result_type __t0 = __a * (__x % __q);
        const result_type __t1 = __r * (__x / __q);
        __x = __t0 + (__t0 < __t1) * __m - __t1;
        return __x;
    }
};

template <unsigned long long __a, unsigned long long __c, unsigned long long __m>
struct __lce_ta<__a, __c, __m, (unsigned long long)(~0), false>
{
    typedef unsigned long long result_type;
    _LIBCPP_INLINE_VISIBILITY
    static result_type next(result_type __x)
    {
        return (__a * __x + __c) % __m;
    }
};

template <unsigned long long __a, unsigned long long __c>
struct __lce_ta<__a, __c, 0, (unsigned long long)(~0), false>
{
    typedef unsigned long long result_type;
    _LIBCPP_INLINE_VISIBILITY
    static result_type next(result_type __x)
    {
        return __a * __x + __c;
    }
};

// 32

template <unsigned long long _Ap, unsigned long long _Cp, unsigned long long _Mp>
struct __lce_ta<_Ap, _Cp, _Mp, unsigned(~0), true>
{
    typedef unsigned result_type;
    _LIBCPP_INLINE_VISIBILITY
    static result_type next(result_type __x)
    {
        const result_type __a = static_cast<result_type>(_Ap);
        const result_type __c = static_cast<result_type>(_Cp);
        const result_type __m = static_cast<result_type>(_Mp);
        // Schrage's algorithm
        const result_type __q = __m / __a;
        const result_type __r = __m % __a;
        const result_type __t0 = __a * (__x % __q);
        const result_type __t1 = __r * (__x / __q);
        __x = __t0 + (__t0 < __t1) * __m - __t1;
        __x += __c - (__x >= __m - __c) * __m;
        return __x;
    }
};

template <unsigned long long _Ap, unsigned long long _Mp>
struct __lce_ta<_Ap, 0, _Mp, unsigned(~0), true>
{
    typedef unsigned result_type;
    _LIBCPP_INLINE_VISIBILITY
    static result_type next(result_type __x)
    {
        const result_type __a = static_cast<result_type>(_Ap);
        const result_type __m = static_cast<result_type>(_Mp);
        // Schrage's algorithm
        const result_type __q = __m / __a;
        const result_type __r = __m % __a;
        const result_type __t0 = __a * (__x % __q);
        const result_type __t1 = __r * (__x / __q);
        __x = __t0 + (__t0 < __t1) * __m - __t1;
        return __x;
    }
};

template <unsigned long long _Ap, unsigned long long _Cp, unsigned long long _Mp>
struct __lce_ta<_Ap, _Cp, _Mp, unsigned(~0), false>
{
    typedef unsigned result_type;
    _LIBCPP_INLINE_VISIBILITY
    static result_type next(result_type __x)
    {
        const result_type __a = static_cast<result_type>(_Ap);
        const result_type __c = static_cast<result_type>(_Cp);
        const result_type __m = static_cast<result_type>(_Mp);
        return (__a * __x + __c) % __m;
    }
};

template <unsigned long long _Ap, unsigned long long _Cp>
struct __lce_ta<_Ap, _Cp, 0, unsigned(~0), false>
{
    typedef unsigned result_type;
    _LIBCPP_INLINE_VISIBILITY
    static result_type next(result_type __x)
    {
        const result_type __a = static_cast<result_type>(_Ap);
        const result_type __c = static_cast<result_type>(_Cp);
        return __a * __x + __c;
    }
};

// 16

template <unsigned long long __a, unsigned long long __c, unsigned long long __m, bool __b>
struct __lce_ta<__a, __c, __m, (unsigned short)(~0), __b>
{
    typedef unsigned short result_type;
    _LIBCPP_INLINE_VISIBILITY
    static result_type next(result_type __x)
    {
        return static_cast<result_type>(__lce_ta<__a, __c, __m, unsigned(~0)>::next(__x));
    }
};

template <class _UIntType, _UIntType __a, _UIntType __c, _UIntType __m>
class _LIBCPP_TEMPLATE_VIS linear_congruential_engine;

template <class _CharT, class _Traits,
          class _Up, _Up _Ap, _Up _Cp, _Up _Np>
_LIBCPP_INLINE_VISIBILITY
basic_ostream<_CharT, _Traits>&
operator<<(basic_ostream<_CharT, _Traits>& __os,
           const linear_congruential_engine<_Up, _Ap, _Cp, _Np>&);

template <class _CharT, class _Traits,
          class _Up, _Up _Ap, _Up _Cp, _Up _Np>
basic_istream<_CharT, _Traits>&
operator>>(basic_istream<_CharT, _Traits>& __is,
           linear_congruential_engine<_Up, _Ap, _Cp, _Np>& __x);

template <class _UIntType, _UIntType __a, _UIntType __c, _UIntType __m>
class _LIBCPP_TEMPLATE_VIS linear_congruential_engine
{
public:
    // types
    typedef _UIntType result_type;

private:
    result_type __x_;

    static _LIBCPP_CONSTEXPR const result_type _Mp = result_type(~0);

    static_assert(__m == 0 || __a < __m, "linear_congruential_engine invalid parameters");
    static_assert(__m == 0 || __c < __m, "linear_congruential_engine invalid parameters");
public:
    static _LIBCPP_CONSTEXPR const result_type _Min = __c == 0u ? 1u: 0u;
    static _LIBCPP_CONSTEXPR const result_type _Max = __m - 1u;
    static_assert(_Min < _Max,           "linear_congruential_engine invalid parameters");

    // engine characteristics
    static _LIBCPP_CONSTEXPR const result_type multiplier = __a;
    static _LIBCPP_CONSTEXPR const result_type increment = __c;
    static _LIBCPP_CONSTEXPR const result_type modulus = __m;
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR result_type min() {return _Min;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR result_type max() {return _Max;}
    static _LIBCPP_CONSTEXPR const result_type default_seed = 1u;

    // constructors and seeding functions
    _LIBCPP_INLINE_VISIBILITY
    explicit linear_congruential_engine(result_type __s = default_seed)
        {seed(__s);}
    template<class _Sseq>
        _LIBCPP_INLINE_VISIBILITY
        explicit linear_congruential_engine(_Sseq& __q,
        typename enable_if<__is_seed_sequence<_Sseq, linear_congruential_engine>::value>::type* = 0)
        {seed(__q);}
    _LIBCPP_INLINE_VISIBILITY
    void seed(result_type __s = default_seed)
        {seed(integral_constant<bool, __m == 0>(),
              integral_constant<bool, __c == 0>(), __s);}
    template<class _Sseq>
        _LIBCPP_INLINE_VISIBILITY
        typename enable_if
        <
            __is_seed_sequence<_Sseq, linear_congruential_engine>::value,
            void
        >::type
        seed(_Sseq& __q)
            {__seed(__q, integral_constant<unsigned,
                1 + (__m == 0 ? (sizeof(result_type) * __CHAR_BIT__ - 1)/32
                             :  (__m > 0x100000000ull))>());}

    // generating functions
    _LIBCPP_INLINE_VISIBILITY
    result_type operator()()
        {return __x_ = static_cast<result_type>(__lce_ta<__a, __c, __m, _Mp>::next(__x_));}
    _LIBCPP_INLINE_VISIBILITY
    void discard(unsigned long long __z) {for (; __z; --__z) operator()();}

    friend _LIBCPP_INLINE_VISIBILITY
    bool operator==(const linear_congruential_engine& __x,
                    const linear_congruential_engine& __y)
        {return __x.__x_ == __y.__x_;}
    friend _LIBCPP_INLINE_VISIBILITY
    bool operator!=(const linear_congruential_engine& __x,
                    const linear_congruential_engine& __y)
        {return !(__x == __y);}

private:

    _LIBCPP_INLINE_VISIBILITY
    void seed(true_type, true_type, result_type __s) {__x_ = __s == 0 ? 1 : __s;}
    _LIBCPP_INLINE_VISIBILITY
    void seed(true_type, false_type, result_type __s) {__x_ = __s;}
    _LIBCPP_INLINE_VISIBILITY
    void seed(false_type, true_type, result_type __s) {__x_ = __s % __m == 0 ?
                                                                 1 : __s % __m;}
    _LIBCPP_INLINE_VISIBILITY
    void seed(false_type, false_type, result_type __s) {__x_ = __s % __m;}

    template<class _Sseq>
        void __seed(_Sseq& __q, integral_constant<unsigned, 1>);
    template<class _Sseq>
        void __seed(_Sseq& __q, integral_constant<unsigned, 2>);

    template <class _CharT, class _Traits,
              class _Up, _Up _Ap, _Up _Cp, _Up _Np>
    friend
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
               const linear_congruential_engine<_Up, _Ap, _Cp, _Np>&);

    template <class _CharT, class _Traits,
              class _Up, _Up _Ap, _Up _Cp, _Up _Np>
    friend
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __is,
               linear_congruential_engine<_Up, _Ap, _Cp, _Np>& __x);
};

template <class _UIntType, _UIntType __a, _UIntType __c, _UIntType __m>
    _LIBCPP_CONSTEXPR const typename linear_congruential_engine<_UIntType, __a, __c, __m>::result_type
    linear_congruential_engine<_UIntType, __a, __c, __m>::multiplier;

template <class _UIntType, _UIntType __a, _UIntType __c, _UIntType __m>
    _LIBCPP_CONSTEXPR const typename linear_congruential_engine<_UIntType, __a, __c, __m>::result_type
    linear_congruential_engine<_UIntType, __a, __c, __m>::increment;

template <class _UIntType, _UIntType __a, _UIntType __c, _UIntType __m>
    _LIBCPP_CONSTEXPR const typename linear_congruential_engine<_UIntType, __a, __c, __m>::result_type
    linear_congruential_engine<_UIntType, __a, __c, __m>::modulus;

template <class _UIntType, _UIntType __a, _UIntType __c, _UIntType __m>
    _LIBCPP_CONSTEXPR const typename linear_congruential_engine<_UIntType, __a, __c, __m>::result_type
    linear_congruential_engine<_UIntType, __a, __c, __m>::default_seed;

template <class _UIntType, _UIntType __a, _UIntType __c, _UIntType __m>
template<class _Sseq>
void
linear_congruential_engine<_UIntType, __a, __c, __m>::__seed(_Sseq& __q,
                                                 integral_constant<unsigned, 1>)
{
    const unsigned __k = 1;
    uint32_t __ar[__k+3];
    __q.generate(__ar, __ar + __k + 3);
    result_type __s = static_cast<result_type>(__ar[3] % __m);
    __x_ = __c == 0 && __s == 0 ? result_type(1) : __s;
}

template <class _UIntType, _UIntType __a, _UIntType __c, _UIntType __m>
template<class _Sseq>
void
linear_congruential_engine<_UIntType, __a, __c, __m>::__seed(_Sseq& __q,
                                                 integral_constant<unsigned, 2>)
{
    const unsigned __k = 2;
    uint32_t __ar[__k+3];
    __q.generate(__ar, __ar + __k + 3);
    result_type __s = static_cast<result_type>((__ar[3] +
                                              ((uint64_t)__ar[4] << 32)) % __m);
    __x_ = __c == 0 && __s == 0 ? result_type(1) : __s;
}

//template <class _CharT, class _Traits,
//          class _UIntType, _UIntType __a, _UIntType __c, _UIntType __m>
//inline _LIBCPP_INLINE_VISIBILITY
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const linear_congruential_engine<_UIntType, __a, __c, __m>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left);
//    __os.fill(__os.widen(' '));
//    return __os << __x.__x_;
//}

//template <class _CharT, class _Traits,
//          class _UIntType, _UIntType __a, _UIntType __c, _UIntType __m>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           linear_congruential_engine<_UIntType, __a, __c, __m>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    _UIntType __t;
//    __is >> __t;
//    if (!__is.fail())
//        __x.__x_ = __t;
//    return __is;
//}

typedef linear_congruential_engine<uint32_t, 16807, 0, 2147483647>
                                                                   minstd_rand0;
typedef linear_congruential_engine<uint32_t, 48271, 0, 2147483647>
                                                                    minstd_rand;
typedef minstd_rand                                       default_random_engine;
// mersenne_twister_engine

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
class _LIBCPP_TEMPLATE_VIS mersenne_twister_engine;

template <class _UInt, size_t _Wp, size_t _Np, size_t _Mp, size_t _Rp,
          _UInt _Ap, size_t _Up, _UInt _Dp, size_t _Sp,
          _UInt _Bp, size_t _Tp, _UInt _Cp, size_t _Lp, _UInt _Fp>
bool
operator==(const mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
                                         _Bp, _Tp, _Cp, _Lp, _Fp>& __x,
           const mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
                                         _Bp, _Tp, _Cp, _Lp, _Fp>& __y);

template <class _UInt, size_t _Wp, size_t _Np, size_t _Mp, size_t _Rp,
          _UInt _Ap, size_t _Up, _UInt _Dp, size_t _Sp,
          _UInt _Bp, size_t _Tp, _UInt _Cp, size_t _Lp, _UInt _Fp>
_LIBCPP_INLINE_VISIBILITY
bool
operator!=(const mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
                                         _Bp, _Tp, _Cp, _Lp, _Fp>& __x,
           const mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
                                         _Bp, _Tp, _Cp, _Lp, _Fp>& __y);

template <class _CharT, class _Traits,
          class _UInt, size_t _Wp, size_t _Np, size_t _Mp, size_t _Rp,
          _UInt _Ap, size_t _Up, _UInt _Dp, size_t _Sp,
          _UInt _Bp, size_t _Tp, _UInt _Cp, size_t _Lp, _UInt _Fp>
basic_ostream<_CharT, _Traits>&
operator<<(basic_ostream<_CharT, _Traits>& __os,
           const mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
                                         _Bp, _Tp, _Cp, _Lp, _Fp>& __x);

template <class _CharT, class _Traits,
          class _UInt, size_t _Wp, size_t _Np, size_t _Mp, size_t _Rp,
          _UInt _Ap, size_t _Up, _UInt _Dp, size_t _Sp,
          _UInt _Bp, size_t _Tp, _UInt _Cp, size_t _Lp, _UInt _Fp>
basic_istream<_CharT, _Traits>&
operator>>(basic_istream<_CharT, _Traits>& __is,
           mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
                                   _Bp, _Tp, _Cp, _Lp, _Fp>& __x);

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
class _LIBCPP_TEMPLATE_VIS mersenne_twister_engine
{
public:
    // types
    typedef _UIntType result_type;

private:
    result_type __x_[__n];
    size_t      __i_;

    static_assert(  0 <  __m, "mersenne_twister_engine invalid parameters");
    static_assert(__m <= __n, "mersenne_twister_engine invalid parameters");
    static _LIBCPP_CONSTEXPR const result_type _Dt = numeric_limits<result_type>::digits;
    static_assert(__w <= _Dt, "mersenne_twister_engine invalid parameters");
    static_assert(  2 <= __w, "mersenne_twister_engine invalid parameters");
    static_assert(__r <= __w, "mersenne_twister_engine invalid parameters");
    static_assert(__u <= __w, "mersenne_twister_engine invalid parameters");
    static_assert(__s <= __w, "mersenne_twister_engine invalid parameters");
    static_assert(__t <= __w, "mersenne_twister_engine invalid parameters");
    static_assert(__l <= __w, "mersenne_twister_engine invalid parameters");
public:
    static _LIBCPP_CONSTEXPR const result_type _Min = 0;
    static _LIBCPP_CONSTEXPR const result_type _Max = __w == _Dt ? result_type(~0) :
                                                      (result_type(1) << __w) - result_type(1);
    static_assert(_Min < _Max, "mersenne_twister_engine invalid parameters");
    static_assert(__a <= _Max, "mersenne_twister_engine invalid parameters");
    static_assert(__b <= _Max, "mersenne_twister_engine invalid parameters");
    static_assert(__c <= _Max, "mersenne_twister_engine invalid parameters");
    static_assert(__d <= _Max, "mersenne_twister_engine invalid parameters");
    static_assert(__f <= _Max, "mersenne_twister_engine invalid parameters");

    // engine characteristics
    static _LIBCPP_CONSTEXPR const size_t word_size = __w;
    static _LIBCPP_CONSTEXPR const size_t state_size = __n;
    static _LIBCPP_CONSTEXPR const size_t shift_size = __m;
    static _LIBCPP_CONSTEXPR const size_t mask_bits = __r;
    static _LIBCPP_CONSTEXPR const result_type xor_mask = __a;
    static _LIBCPP_CONSTEXPR const size_t tempering_u = __u;
    static _LIBCPP_CONSTEXPR const result_type tempering_d = __d;
    static _LIBCPP_CONSTEXPR const size_t tempering_s = __s;
    static _LIBCPP_CONSTEXPR const result_type tempering_b = __b;
    static _LIBCPP_CONSTEXPR const size_t tempering_t = __t;
    static _LIBCPP_CONSTEXPR const result_type tempering_c = __c;
    static _LIBCPP_CONSTEXPR const size_t tempering_l = __l;
    static _LIBCPP_CONSTEXPR const result_type initialization_multiplier = __f;
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR result_type min() { return _Min; }
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR result_type max() { return _Max; }
    static _LIBCPP_CONSTEXPR const result_type default_seed = 5489u;

    // constructors and seeding functions
    _LIBCPP_INLINE_VISIBILITY
    explicit mersenne_twister_engine(result_type __sd = default_seed)
        {seed(__sd);}
    template<class _Sseq>
        _LIBCPP_INLINE_VISIBILITY
        explicit mersenne_twister_engine(_Sseq& __q,
        typename enable_if<__is_seed_sequence<_Sseq, mersenne_twister_engine>::value>::type* = 0)
        {seed(__q);}
    void seed(result_type __sd = default_seed);
    template<class _Sseq>
        _LIBCPP_INLINE_VISIBILITY
        typename enable_if
        <
            __is_seed_sequence<_Sseq, mersenne_twister_engine>::value,
            void
        >::type
        seed(_Sseq& __q)
            {__seed(__q, integral_constant<unsigned, 1 + (__w - 1) / 32>());}

    // generating functions
    result_type operator()();
    _LIBCPP_INLINE_VISIBILITY
    void discard(unsigned long long __z) {for (; __z; --__z) operator()();}

    template <class _UInt, size_t _Wp, size_t _Np, size_t _Mp, size_t _Rp,
              _UInt _Ap, size_t _Up, _UInt _Dp, size_t _Sp,
              _UInt _Bp, size_t _Tp, _UInt _Cp, size_t _Lp, _UInt _Fp>
    friend
    bool
    operator==(const mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
                                             _Bp, _Tp, _Cp, _Lp, _Fp>& __x,
               const mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
                                             _Bp, _Tp, _Cp, _Lp, _Fp>& __y);

    template <class _UInt, size_t _Wp, size_t _Np, size_t _Mp, size_t _Rp,
              _UInt _Ap, size_t _Up, _UInt _Dp, size_t _Sp,
              _UInt _Bp, size_t _Tp, _UInt _Cp, size_t _Lp, _UInt _Fp>
    friend
    bool
    operator!=(const mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
                                             _Bp, _Tp, _Cp, _Lp, _Fp>& __x,
               const mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
                                             _Bp, _Tp, _Cp, _Lp, _Fp>& __y);

    template <class _CharT, class _Traits,
              class _UInt, size_t _Wp, size_t _Np, size_t _Mp, size_t _Rp,
              _UInt _Ap, size_t _Up, _UInt _Dp, size_t _Sp,
              _UInt _Bp, size_t _Tp, _UInt _Cp, size_t _Lp, _UInt _Fp>
    friend
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
               const mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
                                             _Bp, _Tp, _Cp, _Lp, _Fp>& __x);

    template <class _CharT, class _Traits,
              class _UInt, size_t _Wp, size_t _Np, size_t _Mp, size_t _Rp,
              _UInt _Ap, size_t _Up, _UInt _Dp, size_t _Sp,
              _UInt _Bp, size_t _Tp, _UInt _Cp, size_t _Lp, _UInt _Fp>
    friend
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __is,
               mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
                                       _Bp, _Tp, _Cp, _Lp, _Fp>& __x);
private:

    template<class _Sseq>
        void __seed(_Sseq& __q, integral_constant<unsigned, 1>);
    template<class _Sseq>
        void __seed(_Sseq& __q, integral_constant<unsigned, 2>);

    template <size_t __count>
        _LIBCPP_INLINE_VISIBILITY
        static
        typename enable_if
        <
            __count < __w,
            result_type
        >::type
        __lshift(result_type __x) {return (__x << __count) & _Max;}

    template <size_t __count>
        _LIBCPP_INLINE_VISIBILITY
        static
        typename enable_if
        <
            (__count >= __w),
            result_type
        >::type
        __lshift(result_type) {return result_type(0);}

    template <size_t __count>
        _LIBCPP_INLINE_VISIBILITY
        static
        typename enable_if
        <
            __count < _Dt,
            result_type
        >::type
        __rshift(result_type __x) {return __x >> __count;}

    template <size_t __count>
        _LIBCPP_INLINE_VISIBILITY
        static
        typename enable_if
        <
            (__count >= _Dt),
            result_type
        >::type
        __rshift(result_type) {return result_type(0);}
};

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
    _LIBCPP_CONSTEXPR const size_t
    mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::word_size;

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
    _LIBCPP_CONSTEXPR const size_t
    mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::state_size;

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
    _LIBCPP_CONSTEXPR const size_t
    mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::shift_size;

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
    _LIBCPP_CONSTEXPR const size_t
    mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::mask_bits;

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
    _LIBCPP_CONSTEXPR const typename mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::result_type
    mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::xor_mask;

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
    _LIBCPP_CONSTEXPR const size_t
    mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::tempering_u;

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
    _LIBCPP_CONSTEXPR const typename mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::result_type
    mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::tempering_d;

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
    _LIBCPP_CONSTEXPR const size_t
    mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::tempering_s;

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
    _LIBCPP_CONSTEXPR const typename mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::result_type
    mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::tempering_b;

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
    _LIBCPP_CONSTEXPR const size_t
    mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::tempering_t;

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
    _LIBCPP_CONSTEXPR const typename mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::result_type
    mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::tempering_c;

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
    _LIBCPP_CONSTEXPR const size_t
    mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::tempering_l;

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
    _LIBCPP_CONSTEXPR const typename mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::result_type
    mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::initialization_multiplier;

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
    _LIBCPP_CONSTEXPR const typename mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::result_type
    mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b, __t, __c, __l, __f>::default_seed;

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
void
mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b,
    __t, __c, __l, __f>::seed(result_type __sd)
    _LIBCPP_DISABLE_UBSAN_UNSIGNED_INTEGER_CHECK
{   // __w >= 2
    __x_[0] = __sd & _Max;
    for (size_t __i = 1; __i < __n; ++__i)
        __x_[__i] = (__f * (__x_[__i-1] ^ __rshift<__w - 2>(__x_[__i-1])) + __i) & _Max;
    __i_ = 0;
}

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
template<class _Sseq>
void
mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b,
    __t, __c, __l, __f>::__seed(_Sseq& __q, integral_constant<unsigned, 1>)
{
    const unsigned __k = 1;
    uint32_t __ar[__n * __k];
    __q.generate(__ar, __ar + __n * __k);
    for (size_t __i = 0; __i < __n; ++__i)
        __x_[__i] = static_cast<result_type>(__ar[__i] & _Max);
    const result_type __mask = __r == _Dt ? result_type(~0) :
                                       (result_type(1) << __r) - result_type(1);
    __i_ = 0;
    if ((__x_[0] & ~__mask) == 0)
    {
        for (size_t __i = 1; __i < __n; ++__i)
            if (__x_[__i] != 0)
                return;
        __x_[0] = _Max;
    }
}

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
template<class _Sseq>
void
mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b,
    __t, __c, __l, __f>::__seed(_Sseq& __q, integral_constant<unsigned, 2>)
{
    const unsigned __k = 2;
    uint32_t __ar[__n * __k];
    __q.generate(__ar, __ar + __n * __k);
    for (size_t __i = 0; __i < __n; ++__i)
        __x_[__i] = static_cast<result_type>(
            (__ar[2 * __i] + ((uint64_t)__ar[2 * __i + 1] << 32)) & _Max);
    const result_type __mask = __r == _Dt ? result_type(~0) :
                                       (result_type(1) << __r) - result_type(1);
    __i_ = 0;
    if ((__x_[0] & ~__mask) == 0)
    {
        for (size_t __i = 1; __i < __n; ++__i)
            if (__x_[__i] != 0)
                return;
        __x_[0] = _Max;
    }
}

template <class _UIntType, size_t __w, size_t __n, size_t __m, size_t __r,
          _UIntType __a, size_t __u, _UIntType __d, size_t __s,
          _UIntType __b, size_t __t, _UIntType __c, size_t __l, _UIntType __f>
_UIntType
mersenne_twister_engine<_UIntType, __w, __n, __m, __r, __a, __u, __d, __s, __b,
    __t, __c, __l, __f>::operator()()
{
    const size_t __j = (__i_ + 1) % __n;
    const result_type __mask = __r == _Dt ? result_type(~0) :
                                       (result_type(1) << __r) - result_type(1);
    const result_type _Yp = (__x_[__i_] & ~__mask) | (__x_[__j] & __mask);
    const size_t __k = (__i_ + __m) % __n;
    __x_[__i_] = __x_[__k] ^ __rshift<1>(_Yp) ^ (__a * (_Yp & 1));
    result_type __z = __x_[__i_] ^ (__rshift<__u>(__x_[__i_]) & __d);
    __i_ = __j;
    __z ^= __lshift<__s>(__z) & __b;
    __z ^= __lshift<__t>(__z) & __c;
    return __z ^ __rshift<__l>(__z);
}

template <class _UInt, size_t _Wp, size_t _Np, size_t _Mp, size_t _Rp,
          _UInt _Ap, size_t _Up, _UInt _Dp, size_t _Sp,
          _UInt _Bp, size_t _Tp, _UInt _Cp, size_t _Lp, _UInt _Fp>
bool
operator==(const mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
                                         _Bp, _Tp, _Cp, _Lp, _Fp>& __x,
           const mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
                                         _Bp, _Tp, _Cp, _Lp, _Fp>& __y)
{
    if (__x.__i_ == __y.__i_)
        return _VSTD::equal(__x.__x_, __x.__x_ + _Np, __y.__x_);
    if (__x.__i_ == 0 || __y.__i_ == 0)
    {
        size_t __j = _VSTD::min(_Np - __x.__i_, _Np - __y.__i_);
        if (!_VSTD::equal(__x.__x_ + __x.__i_, __x.__x_ + __x.__i_ + __j,
                         __y.__x_ + __y.__i_))
            return false;
        if (__x.__i_ == 0)
            return _VSTD::equal(__x.__x_ + __j, __x.__x_ + _Np, __y.__x_);
        return _VSTD::equal(__x.__x_, __x.__x_ + (_Np - __j), __y.__x_ + __j);
    }
    if (__x.__i_ < __y.__i_)
    {
        size_t __j = _Np - __y.__i_;
        if (!_VSTD::equal(__x.__x_ + __x.__i_, __x.__x_ + (__x.__i_ + __j),
                         __y.__x_ + __y.__i_))
            return false;
        if (!_VSTD::equal(__x.__x_ + (__x.__i_ + __j), __x.__x_ + _Np,
                         __y.__x_))
            return false;
        return _VSTD::equal(__x.__x_, __x.__x_ + __x.__i_,
                           __y.__x_ + (_Np - (__x.__i_ + __j)));
    }
    size_t __j = _Np - __x.__i_;
    if (!_VSTD::equal(__y.__x_ + __y.__i_, __y.__x_ + (__y.__i_ + __j),
                     __x.__x_ + __x.__i_))
        return false;
    if (!_VSTD::equal(__y.__x_ + (__y.__i_ + __j), __y.__x_ + _Np,
                     __x.__x_))
        return false;
    return _VSTD::equal(__y.__x_, __y.__x_ + __y.__i_,
                       __x.__x_ + (_Np - (__y.__i_ + __j)));
}

template <class _UInt, size_t _Wp, size_t _Np, size_t _Mp, size_t _Rp,
          _UInt _Ap, size_t _Up, _UInt _Dp, size_t _Sp,
          _UInt _Bp, size_t _Tp, _UInt _Cp, size_t _Lp, _UInt _Fp>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator!=(const mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
                                         _Bp, _Tp, _Cp, _Lp, _Fp>& __x,
           const mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
                                         _Bp, _Tp, _Cp, _Lp, _Fp>& __y)
{
    return !(__x == __y);
}

//template <class _CharT, class _Traits,
//          class _UInt, size_t _Wp, size_t _Np, size_t _Mp, size_t _Rp,
//          _UInt _Ap, size_t _Up, _UInt _Dp, size_t _Sp,
//          _UInt _Bp, size_t _Tp, _UInt _Cp, size_t _Lp, _UInt _Fp>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
//                                         _Bp, _Tp, _Cp, _Lp, _Fp>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    __os << __x.__x_[__x.__i_];
//    for (size_t __j = __x.__i_ + 1; __j < _Np; ++__j)
//        __os << __sp << __x.__x_[__j];
//    for (size_t __j = 0; __j < __x.__i_; ++__j)
//        __os << __sp << __x.__x_[__j];
//    return __os;
//}

//template <class _CharT, class _Traits,
//          class _UInt, size_t _Wp, size_t _Np, size_t _Mp, size_t _Rp,
//          _UInt _Ap, size_t _Up, _UInt _Dp, size_t _Sp,
//          _UInt _Bp, size_t _Tp, _UInt _Cp, size_t _Lp, _UInt _Fp>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           mersenne_twister_engine<_UInt, _Wp, _Np, _Mp, _Rp, _Ap, _Up, _Dp, _Sp,
//                                   _Bp, _Tp, _Cp, _Lp, _Fp>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    _UInt __t[_Np];
//    for (size_t __i = 0; __i < _Np; ++__i)
//        __is >> __t[__i];
//    if (!__is.fail())
//    {
//        for (size_t __i = 0; __i < _Np; ++__i)
//            __x.__x_[__i] = __t[__i];
//        __x.__i_ = 0;
//    }
//    return __is;
//}

typedef mersenne_twister_engine<uint32_t, 32, 624, 397, 31,
                                0x9908b0df, 11, 0xffffffff,
                                7,  0x9d2c5680,
                                15, 0xefc60000,
                                18, 1812433253>                         mt19937;
typedef mersenne_twister_engine<uint64_t, 64, 312, 156, 31,
                                0xb5026f5aa96619e9ULL, 29, 0x5555555555555555ULL,
                                17, 0x71d67fffeda60000ULL,
                                37, 0xfff7eee000000000ULL,
                                43, 6364136223846793005ULL>          mt19937_64;

// subtract_with_carry_engine

template<class _UIntType, size_t __w, size_t __s, size_t __r>
class _LIBCPP_TEMPLATE_VIS subtract_with_carry_engine;

template<class _UInt, size_t _Wp, size_t _Sp, size_t _Rp>
bool
operator==(
    const subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __x,
    const subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __y);

template<class _UInt, size_t _Wp, size_t _Sp, size_t _Rp>
_LIBCPP_INLINE_VISIBILITY
bool
operator!=(
    const subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __x,
    const subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __y);

template <class _CharT, class _Traits,
          class _UInt, size_t _Wp, size_t _Sp, size_t _Rp>
basic_ostream<_CharT, _Traits>&
operator<<(basic_ostream<_CharT, _Traits>& __os,
           const subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __x);

template <class _CharT, class _Traits,
          class _UInt, size_t _Wp, size_t _Sp, size_t _Rp>
basic_istream<_CharT, _Traits>&
operator>>(basic_istream<_CharT, _Traits>& __is,
           subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __x);

template<class _UIntType, size_t __w, size_t __s, size_t __r>
class _LIBCPP_TEMPLATE_VIS subtract_with_carry_engine
{
public:
    // types
    typedef _UIntType result_type;

private:
    result_type __x_[__r];
    result_type  __c_;
    size_t      __i_;

    static _LIBCPP_CONSTEXPR const result_type _Dt = numeric_limits<result_type>::digits;
    static_assert(  0 <  __w, "subtract_with_carry_engine invalid parameters");
    static_assert(__w <= _Dt, "subtract_with_carry_engine invalid parameters");
    static_assert(  0 <  __s, "subtract_with_carry_engine invalid parameters");
    static_assert(__s <  __r, "subtract_with_carry_engine invalid parameters");
public:
    static _LIBCPP_CONSTEXPR const result_type _Min = 0;
    static _LIBCPP_CONSTEXPR const result_type _Max = __w == _Dt ? result_type(~0) :
                                                      (result_type(1) << __w) - result_type(1);
    static_assert(_Min < _Max, "subtract_with_carry_engine invalid parameters");

    // engine characteristics
    static _LIBCPP_CONSTEXPR const size_t word_size = __w;
    static _LIBCPP_CONSTEXPR const size_t short_lag = __s;
    static _LIBCPP_CONSTEXPR const size_t long_lag = __r;
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR result_type min() { return _Min; }
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR result_type max() { return _Max; }
    static _LIBCPP_CONSTEXPR const result_type default_seed = 19780503u;

    // constructors and seeding functions
    _LIBCPP_INLINE_VISIBILITY
    explicit subtract_with_carry_engine(result_type __sd = default_seed)
        {seed(__sd);}
    template<class _Sseq>
        _LIBCPP_INLINE_VISIBILITY
        explicit subtract_with_carry_engine(_Sseq& __q,
        typename enable_if<__is_seed_sequence<_Sseq, subtract_with_carry_engine>::value>::type* = 0)
        {seed(__q);}
    _LIBCPP_INLINE_VISIBILITY
    void seed(result_type __sd = default_seed)
        {seed(__sd, integral_constant<unsigned, 1 + (__w - 1) / 32>());}
    template<class _Sseq>
        _LIBCPP_INLINE_VISIBILITY
        typename enable_if
        <
            __is_seed_sequence<_Sseq, subtract_with_carry_engine>::value,
            void
        >::type
        seed(_Sseq& __q)
            {__seed(__q, integral_constant<unsigned, 1 + (__w - 1) / 32>());}

    // generating functions
    result_type operator()();
    _LIBCPP_INLINE_VISIBILITY
    void discard(unsigned long long __z) {for (; __z; --__z) operator()();}

    template<class _UInt, size_t _Wp, size_t _Sp, size_t _Rp>
    friend
    bool
    operator==(
        const subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __x,
        const subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __y);

    template<class _UInt, size_t _Wp, size_t _Sp, size_t _Rp>
    friend
    bool
    operator!=(
        const subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __x,
        const subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __y);

    template <class _CharT, class _Traits,
              class _UInt, size_t _Wp, size_t _Sp, size_t _Rp>
    friend
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
               const subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __x);

    template <class _CharT, class _Traits,
              class _UInt, size_t _Wp, size_t _Sp, size_t _Rp>
    friend
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __is,
               subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __x);

private:

    void seed(result_type __sd, integral_constant<unsigned, 1>);
    void seed(result_type __sd, integral_constant<unsigned, 2>);
    template<class _Sseq>
        void __seed(_Sseq& __q, integral_constant<unsigned, 1>);
    template<class _Sseq>
        void __seed(_Sseq& __q, integral_constant<unsigned, 2>);
};

template<class _UIntType, size_t __w, size_t __s, size_t __r>
    _LIBCPP_CONSTEXPR const size_t subtract_with_carry_engine<_UIntType, __w, __s, __r>::word_size;

template<class _UIntType, size_t __w, size_t __s, size_t __r>
    _LIBCPP_CONSTEXPR const size_t subtract_with_carry_engine<_UIntType, __w, __s, __r>::short_lag;

template<class _UIntType, size_t __w, size_t __s, size_t __r>
    _LIBCPP_CONSTEXPR const size_t subtract_with_carry_engine<_UIntType, __w, __s, __r>::long_lag;

template<class _UIntType, size_t __w, size_t __s, size_t __r>
    _LIBCPP_CONSTEXPR const typename subtract_with_carry_engine<_UIntType, __w, __s, __r>::result_type
    subtract_with_carry_engine<_UIntType, __w, __s, __r>::default_seed;

template<class _UIntType, size_t __w, size_t __s, size_t __r>
void
subtract_with_carry_engine<_UIntType, __w, __s, __r>::seed(result_type __sd,
        integral_constant<unsigned, 1>)
{
    linear_congruential_engine<result_type, 40014u, 0u, 2147483563u>
        __e(__sd == 0u ? default_seed : __sd);
    for (size_t __i = 0; __i < __r; ++__i)
        __x_[__i] = static_cast<result_type>(__e() & _Max);
    __c_ = __x_[__r-1] == 0;
    __i_ = 0;
}

template<class _UIntType, size_t __w, size_t __s, size_t __r>
void
subtract_with_carry_engine<_UIntType, __w, __s, __r>::seed(result_type __sd,
        integral_constant<unsigned, 2>)
{
    linear_congruential_engine<result_type, 40014u, 0u, 2147483563u>
        __e(__sd == 0u ? default_seed : __sd);
    for (size_t __i = 0; __i < __r; ++__i)
    {
        result_type __e0 = __e();
        __x_[__i] = static_cast<result_type>(
                                    (__e0 + ((uint64_t)__e() << 32)) & _Max);
    }
    __c_ = __x_[__r-1] == 0;
    __i_ = 0;
}

template<class _UIntType, size_t __w, size_t __s, size_t __r>
template<class _Sseq>
void
subtract_with_carry_engine<_UIntType, __w, __s, __r>::__seed(_Sseq& __q,
        integral_constant<unsigned, 1>)
{
    const unsigned __k = 1;
    uint32_t __ar[__r * __k];
    __q.generate(__ar, __ar + __r * __k);
    for (size_t __i = 0; __i < __r; ++__i)
        __x_[__i] = static_cast<result_type>(__ar[__i] & _Max);
    __c_ = __x_[__r-1] == 0;
    __i_ = 0;
}

template<class _UIntType, size_t __w, size_t __s, size_t __r>
template<class _Sseq>
void
subtract_with_carry_engine<_UIntType, __w, __s, __r>::__seed(_Sseq& __q,
        integral_constant<unsigned, 2>)
{
    const unsigned __k = 2;
    uint32_t __ar[__r * __k];
    __q.generate(__ar, __ar + __r * __k);
    for (size_t __i = 0; __i < __r; ++__i)
        __x_[__i] = static_cast<result_type>(
                  (__ar[2 * __i] + ((uint64_t)__ar[2 * __i + 1] << 32)) & _Max);
    __c_ = __x_[__r-1] == 0;
    __i_ = 0;
}

template<class _UIntType, size_t __w, size_t __s, size_t __r>
_UIntType
subtract_with_carry_engine<_UIntType, __w, __s, __r>::operator()()
{
    const result_type& __xs = __x_[(__i_ + (__r - __s)) % __r];
    result_type& __xr = __x_[__i_];
    result_type __new_c = __c_ == 0 ? __xs < __xr : __xs != 0 ? __xs <= __xr : 1;
    __xr = (__xs - __xr - __c_) & _Max;
    __c_ = __new_c;
    __i_ = (__i_ + 1) % __r;
    return __xr;
}

template<class _UInt, size_t _Wp, size_t _Sp, size_t _Rp>
bool
operator==(
    const subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __x,
    const subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __y)
{
    if (__x.__c_ != __y.__c_)
        return false;
    if (__x.__i_ == __y.__i_)
        return _VSTD::equal(__x.__x_, __x.__x_ + _Rp, __y.__x_);
    if (__x.__i_ == 0 || __y.__i_ == 0)
    {
        size_t __j = _VSTD::min(_Rp - __x.__i_, _Rp - __y.__i_);
        if (!_VSTD::equal(__x.__x_ + __x.__i_, __x.__x_ + __x.__i_ + __j,
                         __y.__x_ + __y.__i_))
            return false;
        if (__x.__i_ == 0)
            return _VSTD::equal(__x.__x_ + __j, __x.__x_ + _Rp, __y.__x_);
        return _VSTD::equal(__x.__x_, __x.__x_ + (_Rp - __j), __y.__x_ + __j);
    }
    if (__x.__i_ < __y.__i_)
    {
        size_t __j = _Rp - __y.__i_;
        if (!_VSTD::equal(__x.__x_ + __x.__i_, __x.__x_ + (__x.__i_ + __j),
                         __y.__x_ + __y.__i_))
            return false;
        if (!_VSTD::equal(__x.__x_ + (__x.__i_ + __j), __x.__x_ + _Rp,
                         __y.__x_))
            return false;
        return _VSTD::equal(__x.__x_, __x.__x_ + __x.__i_,
                           __y.__x_ + (_Rp - (__x.__i_ + __j)));
    }
    size_t __j = _Rp - __x.__i_;
    if (!_VSTD::equal(__y.__x_ + __y.__i_, __y.__x_ + (__y.__i_ + __j),
                     __x.__x_ + __x.__i_))
        return false;
    if (!_VSTD::equal(__y.__x_ + (__y.__i_ + __j), __y.__x_ + _Rp,
                     __x.__x_))
        return false;
    return _VSTD::equal(__y.__x_, __y.__x_ + __y.__i_,
                       __x.__x_ + (_Rp - (__y.__i_ + __j)));
}

template<class _UInt, size_t _Wp, size_t _Sp, size_t _Rp>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator!=(
    const subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __x,
    const subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __y)
{
    return !(__x == __y);
}

//template <class _CharT, class _Traits,
//          class _UInt, size_t _Wp, size_t _Sp, size_t _Rp>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    __os << __x.__x_[__x.__i_];
//    for (size_t __j = __x.__i_ + 1; __j < _Rp; ++__j)
//        __os << __sp << __x.__x_[__j];
//    for (size_t __j = 0; __j < __x.__i_; ++__j)
//        __os << __sp << __x.__x_[__j];
//    __os << __sp << __x.__c_;
//    return __os;
//}

//template <class _CharT, class _Traits,
//          class _UInt, size_t _Wp, size_t _Sp, size_t _Rp>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           subtract_with_carry_engine<_UInt, _Wp, _Sp, _Rp>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    _UInt __t[_Rp+1];
//    for (size_t __i = 0; __i < _Rp+1; ++__i)
//        __is >> __t[__i];
//    if (!__is.fail())
//    {
//        for (size_t __i = 0; __i < _Rp; ++__i)
//            __x.__x_[__i] = __t[__i];
//        __x.__c_ = __t[_Rp];
//        __x.__i_ = 0;
//    }
//    return __is;
//}

typedef subtract_with_carry_engine<uint32_t, 24, 10, 24>     ranlux24_base;
typedef subtract_with_carry_engine<uint64_t, 48,  5, 12>     ranlux48_base;

// discard_block_engine

template<class _Engine, size_t __p, size_t __r>
class _LIBCPP_TEMPLATE_VIS discard_block_engine
{
    _Engine __e_;
    int     __n_;

    static_assert(  0 <  __r, "discard_block_engine invalid parameters");
    static_assert(__r <= __p, "discard_block_engine invalid parameters");
    static_assert(__r <= INT_MAX, "discard_block_engine invalid parameters");
public:
    // types
    typedef typename _Engine::result_type result_type;

    // engine characteristics
    static _LIBCPP_CONSTEXPR const size_t block_size = __p;
    static _LIBCPP_CONSTEXPR const size_t used_block = __r;

#ifdef _LIBCPP_CXX03_LANG
    static const result_type _Min = _Engine::_Min;
    static const result_type _Max = _Engine::_Max;
#else
    static _LIBCPP_CONSTEXPR const result_type _Min = _Engine::min();
    static _LIBCPP_CONSTEXPR const result_type _Max = _Engine::max();
#endif

    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR result_type min() { return _Engine::min(); }
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR result_type max() { return _Engine::max(); }

    // constructors and seeding functions
    _LIBCPP_INLINE_VISIBILITY
    discard_block_engine() : __n_(0) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit discard_block_engine(const _Engine& __e)
        : __e_(__e), __n_(0) {}
#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    explicit discard_block_engine(_Engine&& __e)
        : __e_(_VSTD::move(__e)), __n_(0) {}
#endif  // _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    explicit discard_block_engine(result_type __sd) : __e_(__sd), __n_(0) {}
    template<class _Sseq>
        _LIBCPP_INLINE_VISIBILITY
        explicit discard_block_engine(_Sseq& __q,
        typename enable_if<__is_seed_sequence<_Sseq, discard_block_engine>::value &&
                           !is_convertible<_Sseq, _Engine>::value>::type* = 0)
        : __e_(__q), __n_(0) {}
    _LIBCPP_INLINE_VISIBILITY
    void seed() {__e_.seed(); __n_ = 0;}
    _LIBCPP_INLINE_VISIBILITY
    void seed(result_type __sd) {__e_.seed(__sd); __n_ = 0;}
    template<class _Sseq>
        _LIBCPP_INLINE_VISIBILITY
        typename enable_if
        <
            __is_seed_sequence<_Sseq, discard_block_engine>::value,
            void
        >::type
        seed(_Sseq& __q) {__e_.seed(__q); __n_ = 0;}

    // generating functions
    result_type operator()();
    _LIBCPP_INLINE_VISIBILITY
    void discard(unsigned long long __z) {for (; __z; --__z) operator()();}

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    const _Engine& base() const _NOEXCEPT {return __e_;}

    template<class _Eng, size_t _Pp, size_t _Rp>
    friend
    bool
    operator==(
        const discard_block_engine<_Eng, _Pp, _Rp>& __x,
        const discard_block_engine<_Eng, _Pp, _Rp>& __y);

    template<class _Eng, size_t _Pp, size_t _Rp>
    friend
    bool
    operator!=(
        const discard_block_engine<_Eng, _Pp, _Rp>& __x,
        const discard_block_engine<_Eng, _Pp, _Rp>& __y);

    template <class _CharT, class _Traits,
              class _Eng, size_t _Pp, size_t _Rp>
    friend
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
               const discard_block_engine<_Eng, _Pp, _Rp>& __x);

    template <class _CharT, class _Traits,
              class _Eng, size_t _Pp, size_t _Rp>
    friend
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __is,
               discard_block_engine<_Eng, _Pp, _Rp>& __x);
};

template<class _Engine, size_t __p, size_t __r>
    _LIBCPP_CONSTEXPR const size_t discard_block_engine<_Engine, __p, __r>::block_size;

template<class _Engine, size_t __p, size_t __r>
    _LIBCPP_CONSTEXPR const size_t discard_block_engine<_Engine, __p, __r>::used_block;

template<class _Engine, size_t __p, size_t __r>
typename discard_block_engine<_Engine, __p, __r>::result_type
discard_block_engine<_Engine, __p, __r>::operator()()
{
    if (__n_ >= static_cast<int>(__r))
    {
        __e_.discard(__p - __r);
        __n_ = 0;
    }
    ++__n_;
    return __e_();
}

template<class _Eng, size_t _Pp, size_t _Rp>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator==(const discard_block_engine<_Eng, _Pp, _Rp>& __x,
           const discard_block_engine<_Eng, _Pp, _Rp>& __y)
{
    return __x.__n_ == __y.__n_ && __x.__e_ == __y.__e_;
}

template<class _Eng, size_t _Pp, size_t _Rp>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator!=(const discard_block_engine<_Eng, _Pp, _Rp>& __x,
           const discard_block_engine<_Eng, _Pp, _Rp>& __y)
{
    return !(__x == __y);
}

//template <class _CharT, class _Traits,
//          class _Eng, size_t _Pp, size_t _Rp>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const discard_block_engine<_Eng, _Pp, _Rp>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    return __os << __x.__e_ << __sp << __x.__n_;
//}

//template <class _CharT, class _Traits,
//          class _Eng, size_t _Pp, size_t _Rp>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           discard_block_engine<_Eng, _Pp, _Rp>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    _Eng __e;
//    int __n;
//    __is >> __e >> __n;
//    if (!__is.fail())
//    {
//        __x.__e_ = __e;
//        __x.__n_ = __n;
//    }
//    return __is;
//}

typedef discard_block_engine<ranlux24_base, 223, 23> ranlux24;
typedef discard_block_engine<ranlux48_base, 389, 11> ranlux48;

// independent_bits_engine

template<class _Engine, size_t __w, class _UIntType>
class _LIBCPP_TEMPLATE_VIS independent_bits_engine
{
    template <class _UInt, _UInt _R0, size_t _Wp, size_t _Mp>
    class __get_n
    {
        static _LIBCPP_CONSTEXPR const size_t _Dt = numeric_limits<_UInt>::digits;
        static _LIBCPP_CONSTEXPR const size_t _Np = _Wp / _Mp + (_Wp % _Mp != 0);
        static _LIBCPP_CONSTEXPR const size_t _W0 = _Wp / _Np;
        static _LIBCPP_CONSTEXPR const _UInt _Y0 = _W0 >= _Dt ? 0 : (_R0 >> _W0) << _W0;
    public:
        static _LIBCPP_CONSTEXPR const size_t value = _R0 - _Y0 > _Y0 / _Np ? _Np + 1 : _Np;
    };
public:
    // types
    typedef _UIntType result_type;

private:
    _Engine __e_;

    static _LIBCPP_CONSTEXPR const result_type _Dt = numeric_limits<result_type>::digits;
    static_assert(  0 <  __w, "independent_bits_engine invalid parameters");
    static_assert(__w <= _Dt, "independent_bits_engine invalid parameters");

    typedef typename _Engine::result_type _Engine_result_type;
    typedef typename conditional
        <
            sizeof(_Engine_result_type) <= sizeof(result_type),
                result_type,
                _Engine_result_type
        >::type _Working_result_type;
#ifdef _LIBCPP_CXX03_LANG
    static const _Working_result_type _Rp = _Engine::_Max - _Engine::_Min
                                          + _Working_result_type(1);
#else
    static _LIBCPP_CONSTEXPR const _Working_result_type _Rp = _Engine::max() - _Engine::min()
                                                            + _Working_result_type(1);
#endif
    static _LIBCPP_CONSTEXPR const size_t __m = __log2<_Working_result_type, _Rp>::value;
    static _LIBCPP_CONSTEXPR const size_t __n = __get_n<_Working_result_type, _Rp, __w, __m>::value;
    static _LIBCPP_CONSTEXPR const size_t __w0 = __w / __n;
    static _LIBCPP_CONSTEXPR const size_t __n0 = __n - __w % __n;
    static _LIBCPP_CONSTEXPR const size_t _WDt = numeric_limits<_Working_result_type>::digits;
    static _LIBCPP_CONSTEXPR const size_t _EDt = numeric_limits<_Engine_result_type>::digits;
    static _LIBCPP_CONSTEXPR const _Working_result_type __y0 = __w0 >= _WDt ? 0 :
                                                               (_Rp >> __w0) << __w0;
    static _LIBCPP_CONSTEXPR const _Working_result_type __y1 = __w0 >= _WDt - 1 ? 0 :
                                                               (_Rp >> (__w0+1)) << (__w0+1);
    static _LIBCPP_CONSTEXPR const _Engine_result_type __mask0 = __w0 > 0 ?
                                _Engine_result_type(~0) >> (_EDt - __w0) :
                                _Engine_result_type(0);
    static _LIBCPP_CONSTEXPR const _Engine_result_type __mask1 = __w0 < _EDt - 1 ?
                                _Engine_result_type(~0) >> (_EDt - (__w0 + 1)) :
                                _Engine_result_type(~0);
public:
    static _LIBCPP_CONSTEXPR const result_type _Min = 0;
    static _LIBCPP_CONSTEXPR const result_type _Max = __w == _Dt ? result_type(~0) :
                                                      (result_type(1) << __w) - result_type(1);
    static_assert(_Min < _Max, "independent_bits_engine invalid parameters");

    // engine characteristics
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR result_type min() { return _Min; }
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR result_type max() { return _Max; }

    // constructors and seeding functions
    _LIBCPP_INLINE_VISIBILITY
    independent_bits_engine() {}
    _LIBCPP_INLINE_VISIBILITY
    explicit independent_bits_engine(const _Engine& __e)
        : __e_(__e) {}
#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    explicit independent_bits_engine(_Engine&& __e)
        : __e_(_VSTD::move(__e)) {}
#endif  // _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    explicit independent_bits_engine(result_type __sd) : __e_(__sd) {}
    template<class _Sseq>
        _LIBCPP_INLINE_VISIBILITY
        explicit independent_bits_engine(_Sseq& __q,
        typename enable_if<__is_seed_sequence<_Sseq, independent_bits_engine>::value &&
                           !is_convertible<_Sseq, _Engine>::value>::type* = 0)
         : __e_(__q) {}
    _LIBCPP_INLINE_VISIBILITY
    void seed() {__e_.seed();}
    _LIBCPP_INLINE_VISIBILITY
    void seed(result_type __sd) {__e_.seed(__sd);}
    template<class _Sseq>
        _LIBCPP_INLINE_VISIBILITY
        typename enable_if
        <
            __is_seed_sequence<_Sseq, independent_bits_engine>::value,
            void
        >::type
        seed(_Sseq& __q) {__e_.seed(__q);}

    // generating functions
    _LIBCPP_INLINE_VISIBILITY
    result_type operator()() {return __eval(integral_constant<bool, _Rp != 0>());}
    _LIBCPP_INLINE_VISIBILITY
    void discard(unsigned long long __z) {for (; __z; --__z) operator()();}

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    const _Engine& base() const _NOEXCEPT {return __e_;}

    template<class _Eng, size_t _Wp, class _UInt>
    friend
    bool
    operator==(
        const independent_bits_engine<_Eng, _Wp, _UInt>& __x,
        const independent_bits_engine<_Eng, _Wp, _UInt>& __y);

    template<class _Eng, size_t _Wp, class _UInt>
    friend
    bool
    operator!=(
        const independent_bits_engine<_Eng, _Wp, _UInt>& __x,
        const independent_bits_engine<_Eng, _Wp, _UInt>& __y);

    template <class _CharT, class _Traits,
              class _Eng, size_t _Wp, class _UInt>
    friend
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
               const independent_bits_engine<_Eng, _Wp, _UInt>& __x);

    template <class _CharT, class _Traits,
              class _Eng, size_t _Wp, class _UInt>
    friend
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __is,
               independent_bits_engine<_Eng, _Wp, _UInt>& __x);

private:
    _LIBCPP_INLINE_VISIBILITY
    result_type __eval(false_type);
    result_type __eval(true_type);

    template <size_t __count>
        _LIBCPP_INLINE_VISIBILITY
        static
        typename enable_if
        <
            __count < _Dt,
            result_type
        >::type
        __lshift(result_type __x) {return __x << __count;}

    template <size_t __count>
        _LIBCPP_INLINE_VISIBILITY
        static
        typename enable_if
        <
            (__count >= _Dt),
            result_type
        >::type
        __lshift(result_type) {return result_type(0);}
};

template<class _Engine, size_t __w, class _UIntType>
inline
_UIntType
independent_bits_engine<_Engine, __w, _UIntType>::__eval(false_type)
{
    return static_cast<result_type>(__e_() & __mask0);
}

template<class _Engine, size_t __w, class _UIntType>
_UIntType
independent_bits_engine<_Engine, __w, _UIntType>::__eval(true_type)
{
    result_type _Sp = 0;
    for (size_t __k = 0; __k < __n0; ++__k)
    {
        _Engine_result_type __u;
        do
        {
            __u = __e_() - _Engine::min();
        } while (__u >= __y0);
        _Sp = static_cast<result_type>(__lshift<__w0>(_Sp) + (__u & __mask0));
    }
    for (size_t __k = __n0; __k < __n; ++__k)
    {
        _Engine_result_type __u;
        do
        {
            __u = __e_() - _Engine::min();
        } while (__u >= __y1);
        _Sp = static_cast<result_type>(__lshift<__w0+1>(_Sp) + (__u & __mask1));
    }
    return _Sp;
}

template<class _Eng, size_t _Wp, class _UInt>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator==(
    const independent_bits_engine<_Eng, _Wp, _UInt>& __x,
    const independent_bits_engine<_Eng, _Wp, _UInt>& __y)
{
    return __x.base() == __y.base();
}

template<class _Eng, size_t _Wp, class _UInt>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator!=(
    const independent_bits_engine<_Eng, _Wp, _UInt>& __x,
    const independent_bits_engine<_Eng, _Wp, _UInt>& __y)
{
    return !(__x == __y);
}

template <class _CharT, class _Traits,
          class _Eng, size_t _Wp, class _UInt>
basic_ostream<_CharT, _Traits>&
operator<<(basic_ostream<_CharT, _Traits>& __os,
           const independent_bits_engine<_Eng, _Wp, _UInt>& __x)
{
    return __os << __x.base();
}

template <class _CharT, class _Traits,
          class _Eng, size_t _Wp, class _UInt>
basic_istream<_CharT, _Traits>&
operator>>(basic_istream<_CharT, _Traits>& __is,
           independent_bits_engine<_Eng, _Wp, _UInt>& __x)
{
    _Eng __e;
    __is >> __e;
    if (!__is.fail())
        __x.__e_ = __e;
    return __is;
}

// shuffle_order_engine

template <uint64_t _Xp, uint64_t _Yp>
struct __ugcd
{
    static _LIBCPP_CONSTEXPR const uint64_t value = __ugcd<_Yp, _Xp % _Yp>::value;
};

template <uint64_t _Xp>
struct __ugcd<_Xp, 0>
{
    static _LIBCPP_CONSTEXPR const uint64_t value = _Xp;
};

template <uint64_t _Np, uint64_t _Dp>
class __uratio
{
    static_assert(_Dp != 0, "__uratio divide by 0");
    static _LIBCPP_CONSTEXPR const uint64_t __gcd = __ugcd<_Np, _Dp>::value;
public:
    static _LIBCPP_CONSTEXPR const uint64_t num = _Np / __gcd;
    static _LIBCPP_CONSTEXPR const uint64_t den = _Dp / __gcd;

    typedef __uratio<num, den> type;
};

template<class _Engine, size_t __k>
class _LIBCPP_TEMPLATE_VIS shuffle_order_engine
{
    static_assert(0 < __k, "shuffle_order_engine invalid parameters");
public:
    // types
    typedef typename _Engine::result_type result_type;

private:
    _Engine __e_;
    result_type _V_[__k];
    result_type _Y_;

public:
    // engine characteristics
    static _LIBCPP_CONSTEXPR const size_t table_size = __k;

#ifdef _LIBCPP_CXX03_LANG
    static const result_type _Min = _Engine::_Min;
    static const result_type _Max = _Engine::_Max;
#else
    static _LIBCPP_CONSTEXPR const result_type _Min = _Engine::min();
    static _LIBCPP_CONSTEXPR const result_type _Max = _Engine::max();
#endif
    static_assert(_Min < _Max, "shuffle_order_engine invalid parameters");
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR result_type min() { return _Min; }
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR result_type max() { return _Max; }

    static _LIBCPP_CONSTEXPR const unsigned long long _Rp = _Max - _Min + 1ull;

    // constructors and seeding functions
    _LIBCPP_INLINE_VISIBILITY
    shuffle_order_engine() {__init();}
    _LIBCPP_INLINE_VISIBILITY
    explicit shuffle_order_engine(const _Engine& __e)
        : __e_(__e) {__init();}
#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    explicit shuffle_order_engine(_Engine&& __e)
        : __e_(_VSTD::move(__e)) {__init();}
#endif  // _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    explicit shuffle_order_engine(result_type __sd) : __e_(__sd) {__init();}
    template<class _Sseq>
        _LIBCPP_INLINE_VISIBILITY
        explicit shuffle_order_engine(_Sseq& __q,
        typename enable_if<__is_seed_sequence<_Sseq, shuffle_order_engine>::value &&
                           !is_convertible<_Sseq, _Engine>::value>::type* = 0)
         : __e_(__q) {__init();}
    _LIBCPP_INLINE_VISIBILITY
    void seed() {__e_.seed(); __init();}
    _LIBCPP_INLINE_VISIBILITY
    void seed(result_type __sd) {__e_.seed(__sd); __init();}
    template<class _Sseq>
        _LIBCPP_INLINE_VISIBILITY
        typename enable_if
        <
            __is_seed_sequence<_Sseq, shuffle_order_engine>::value,
            void
        >::type
        seed(_Sseq& __q) {__e_.seed(__q); __init();}

    // generating functions
    _LIBCPP_INLINE_VISIBILITY
    result_type operator()() {return __eval(integral_constant<bool, _Rp != 0>());}
    _LIBCPP_INLINE_VISIBILITY
    void discard(unsigned long long __z) {for (; __z; --__z) operator()();}

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    const _Engine& base() const _NOEXCEPT {return __e_;}

private:
    template<class _Eng, size_t _Kp>
    friend
    bool
    operator==(
        const shuffle_order_engine<_Eng, _Kp>& __x,
        const shuffle_order_engine<_Eng, _Kp>& __y);

    template<class _Eng, size_t _Kp>
    friend
    bool
    operator!=(
        const shuffle_order_engine<_Eng, _Kp>& __x,
        const shuffle_order_engine<_Eng, _Kp>& __y);

    template <class _CharT, class _Traits,
              class _Eng, size_t _Kp>
    friend
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
               const shuffle_order_engine<_Eng, _Kp>& __x);

    template <class _CharT, class _Traits,
              class _Eng, size_t _Kp>
    friend
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __is,
               shuffle_order_engine<_Eng, _Kp>& __x);

    _LIBCPP_INLINE_VISIBILITY
    void __init()
    {
        for (size_t __i = 0; __i < __k; ++__i)
            _V_[__i] = __e_();
        _Y_ = __e_();
    }

    _LIBCPP_INLINE_VISIBILITY
    result_type __eval(false_type) {return __eval2(integral_constant<bool, __k & 1>());}
    _LIBCPP_INLINE_VISIBILITY
    result_type __eval(true_type) {return __eval(__uratio<__k, _Rp>());}

    _LIBCPP_INLINE_VISIBILITY
    result_type __eval2(false_type) {return __eval(__uratio<__k/2, 0x8000000000000000ull>());}
    _LIBCPP_INLINE_VISIBILITY
    result_type __eval2(true_type) {return __evalf<__k, 0>();}

    template <uint64_t _Np, uint64_t _Dp>
        _LIBCPP_INLINE_VISIBILITY
        typename enable_if
        <
            (__uratio<_Np, _Dp>::num > 0xFFFFFFFFFFFFFFFFull / (_Max - _Min)),
            result_type
        >::type
        __eval(__uratio<_Np, _Dp>)
            {return __evalf<__uratio<_Np, _Dp>::num, __uratio<_Np, _Dp>::den>();}

    template <uint64_t _Np, uint64_t _Dp>
        _LIBCPP_INLINE_VISIBILITY
        typename enable_if
        <
            __uratio<_Np, _Dp>::num <= 0xFFFFFFFFFFFFFFFFull / (_Max - _Min),
            result_type
        >::type
        __eval(__uratio<_Np, _Dp>)
        {
            const size_t __j = static_cast<size_t>(__uratio<_Np, _Dp>::num * (_Y_ - _Min)
                                                   / __uratio<_Np, _Dp>::den);
            _Y_ = _V_[__j];
            _V_[__j] = __e_();
            return _Y_;
        }

    template <uint64_t __n, uint64_t __d>
        _LIBCPP_INLINE_VISIBILITY
        result_type __evalf()
        {
            const double _Fp = __d == 0 ?
                __n / (2. * 0x8000000000000000ull) :
                __n / (double)__d;
            const size_t __j = static_cast<size_t>(_Fp * (_Y_ - _Min));
            _Y_ = _V_[__j];
            _V_[__j] = __e_();
            return _Y_;
        }
};

template<class _Engine, size_t __k>
    _LIBCPP_CONSTEXPR const size_t shuffle_order_engine<_Engine, __k>::table_size;

template<class _Eng, size_t _Kp>
bool
operator==(
    const shuffle_order_engine<_Eng, _Kp>& __x,
    const shuffle_order_engine<_Eng, _Kp>& __y)
{
    return __x._Y_ == __y._Y_ && _VSTD::equal(__x._V_, __x._V_ + _Kp, __y._V_) &&
           __x.__e_ == __y.__e_;
}

template<class _Eng, size_t _Kp>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator!=(
    const shuffle_order_engine<_Eng, _Kp>& __x,
    const shuffle_order_engine<_Eng, _Kp>& __y)
{
    return !(__x == __y);
}

//template <class _CharT, class _Traits,
//          class _Eng, size_t _Kp>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const shuffle_order_engine<_Eng, _Kp>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    __os << __x.__e_ << __sp << __x._V_[0];
//    for (size_t __i = 1; __i < _Kp; ++__i)
//        __os << __sp << __x._V_[__i];
//    return __os << __sp << __x._Y_;
//}

//template <class _CharT, class _Traits,
//          class _Eng, size_t _Kp>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           shuffle_order_engine<_Eng, _Kp>& __x)
//{
//    typedef typename shuffle_order_engine<_Eng, _Kp>::result_type result_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    _Eng __e;
//    result_type _Vp[_Kp+1];
//    __is >> __e;
//    for (size_t __i = 0; __i < _Kp+1; ++__i)
//        __is >> _Vp[__i];
//    if (!__is.fail())
//    {
//        __x.__e_ = __e;
//        for (size_t __i = 0; __i < _Kp; ++__i)
//            __x._V_[__i] = _Vp[__i];
//        __x._Y_ = _Vp[_Kp];
//    }
//    return __is;
//}

typedef shuffle_order_engine<minstd_rand0, 256>                         knuth_b;

// random_device

class _LIBCPP_TYPE_VIS random_device
{
#ifdef _LIBCPP_USING_DEV_RANDOM
    int __f_;
#endif // defined(_LIBCPP_USING_DEV_RANDOM)
public:
    // types
    typedef unsigned result_type;

    // generator characteristics
    static _LIBCPP_CONSTEXPR const result_type _Min = 0;
    static _LIBCPP_CONSTEXPR const result_type _Max = 0xFFFFFFFFu;

    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR result_type min() { return _Min;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR result_type max() { return _Max;}

    // constructors
    explicit random_device(const string& __token = "/dev/urandom");
    ~random_device();

    // generating functions
    result_type operator()();

    // property functions
    double entropy() const _NOEXCEPT;

private:
    // no copy functions
    random_device(const random_device&); // = delete;
    random_device& operator=(const random_device&); // = delete;
};

// seed_seq

class _LIBCPP_TEMPLATE_VIS seed_seq
{
public:
    // types
    typedef uint32_t result_type;

private:
    vector<result_type> __v_;

    template<class _InputIterator>
        void init(_InputIterator __first, _InputIterator __last);
public:
    // constructors
    _LIBCPP_INLINE_VISIBILITY
    seed_seq() _NOEXCEPT {}
#ifndef _LIBCPP_CXX03_LANG
    template<class _Tp>
        _LIBCPP_INLINE_VISIBILITY
        seed_seq(initializer_list<_Tp> __il) {init(__il.begin(), __il.end());}
#endif  // _LIBCPP_CXX03_LANG

    template<class _InputIterator>
        _LIBCPP_INLINE_VISIBILITY
        seed_seq(_InputIterator __first, _InputIterator __last)
             {init(__first, __last);}

    // generating functions
    template<class _RandomAccessIterator>
        void generate(_RandomAccessIterator __first, _RandomAccessIterator __last);

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    size_t size() const _NOEXCEPT {return __v_.size();}
    template<class _OutputIterator>
        _LIBCPP_INLINE_VISIBILITY
        void param(_OutputIterator __dest) const
            {_VSTD::copy(__v_.begin(), __v_.end(), __dest);}

private:
    // no copy functions
    seed_seq(const seed_seq&); // = delete;
    void operator=(const seed_seq&); // = delete;

    _LIBCPP_INLINE_VISIBILITY
    static result_type _Tp(result_type __x) {return __x ^ (__x >> 27);}
};

template<class _InputIterator>
void
seed_seq::init(_InputIterator __first, _InputIterator __last)
{
    for (_InputIterator __s = __first; __s != __last; ++__s)
        __v_.push_back(*__s & 0xFFFFFFFF);
}

template<class _RandomAccessIterator>
void
seed_seq::generate(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
    if (__first != __last)
    {
        _VSTD::fill(__first, __last, 0x8b8b8b8b);
        const size_t __n = static_cast<size_t>(__last - __first);
        const size_t __s = __v_.size();
        const size_t __t = (__n >= 623) ? 11
                         : (__n >= 68) ? 7
                         : (__n >= 39) ? 5
                         : (__n >= 7)  ? 3
                         : (__n - 1) / 2;
        const size_t __p = (__n - __t) / 2;
        const size_t __q = __p + __t;
        const size_t __m = _VSTD::max(__s + 1, __n);
        // __k = 0;
        {
            result_type __r = 1664525 * _Tp(__first[0] ^ __first[__p]
                                                      ^  __first[__n - 1]);
            __first[__p] += __r;
            __r += __s;
            __first[__q] += __r;
            __first[0] = __r;
        }
        for (size_t __k = 1; __k <= __s; ++__k)
        {
            const size_t __kmodn = __k % __n;
            const size_t __kpmodn = (__k + __p) % __n;
            result_type __r = 1664525 * _Tp(__first[__kmodn] ^ __first[__kpmodn]
                                           ^ __first[(__k - 1) % __n]);
            __first[__kpmodn] += __r;
            __r +=  __kmodn + __v_[__k-1];
            __first[(__k + __q) % __n] += __r;
            __first[__kmodn] = __r;
        }
        for (size_t __k = __s + 1; __k < __m; ++__k)
        {
            const size_t __kmodn = __k % __n;
            const size_t __kpmodn = (__k + __p) % __n;
            result_type __r = 1664525 * _Tp(__first[__kmodn] ^ __first[__kpmodn]
                                           ^ __first[(__k - 1) % __n]);
            __first[__kpmodn] += __r;
            __r +=  __kmodn;
            __first[(__k + __q) % __n] += __r;
            __first[__kmodn] = __r;
        }
        for (size_t __k = __m; __k < __m + __n; ++__k)
        {
            const size_t __kmodn = __k % __n;
            const size_t __kpmodn = (__k + __p) % __n;
            result_type __r = 1566083941 * _Tp(__first[__kmodn] +
                                              __first[__kpmodn] +
                                              __first[(__k - 1) % __n]);
            __first[__kpmodn] ^= __r;
            __r -= __kmodn;
            __first[(__k + __q) % __n] ^= __r;
            __first[__kmodn] = __r;
        }
    }
}

// generate_canonical

template<class _RealType, size_t __bits, class _URNG>
_RealType
generate_canonical(_URNG& __g)
{
    const size_t _Dt = numeric_limits<_RealType>::digits;
    const size_t __b = _Dt < __bits ? _Dt : __bits;
#ifdef _LIBCPP_CXX03_LANG
    const size_t __logR = __log2<uint64_t, _URNG::_Max - _URNG::_Min + uint64_t(1)>::value;
#else
    const size_t __logR = __log2<uint64_t, _URNG::max() - _URNG::min() + uint64_t(1)>::value;
#endif
    const size_t __k = __b / __logR + (__b % __logR != 0) + (__b == 0);
    const _RealType _Rp = _URNG::max() - _URNG::min() + _RealType(1);
    _RealType __base = _Rp;
    _RealType _Sp = __g() - _URNG::min();
    for (size_t __i = 1; __i < __k; ++__i, __base *= _Rp)
        _Sp += (__g() - _URNG::min()) * __base;
    return _Sp / __base;
}

// uniform_int_distribution

// in <algorithm>

//template <class _CharT, class _Traits, class _IT>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const uniform_int_distribution<_IT>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    return __os << __x.a() << __sp << __x.b();
//}

//template <class _CharT, class _Traits, class _IT>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           uniform_int_distribution<_IT>& __x)
//{
//    typedef uniform_int_distribution<_IT> _Eng;
//    typedef typename _Eng::result_type result_type;
//    typedef typename _Eng::param_type param_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    result_type __a;
//    result_type __b;
//    __is >> __a >> __b;
//    if (!__is.fail())
//        __x.param(param_type(__a, __b));
//    return __is;
//}

// uniform_real_distribution

template<class _RealType = double>
class _LIBCPP_TEMPLATE_VIS uniform_real_distribution
{
public:
    // types
    typedef _RealType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        result_type __a_;
        result_type __b_;
    public:
        typedef uniform_real_distribution distribution_type;

        _LIBCPP_INLINE_VISIBILITY
        explicit param_type(result_type __a = 0,
                            result_type __b = 1)
            : __a_(__a), __b_(__b) {}

        _LIBCPP_INLINE_VISIBILITY
        result_type a() const {return __a_;}
        _LIBCPP_INLINE_VISIBILITY
        result_type b() const {return __b_;}

        friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__a_ == __y.__a_ && __x.__b_ == __y.__b_;}
        friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
    };

private:
    param_type __p_;

public:
    // constructors and reset functions
    _LIBCPP_INLINE_VISIBILITY
    explicit uniform_real_distribution(result_type __a = 0, result_type __b = 1)
        : __p_(param_type(__a, __b)) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit uniform_real_distribution(const param_type& __p) : __p_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    void reset() {}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG> _LIBCPP_INLINE_VISIBILITY result_type operator()(_URNG& __g, const param_type& __p);

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    result_type a() const {return __p_.a();}
    _LIBCPP_INLINE_VISIBILITY
    result_type b() const {return __p_.b();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return a();}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return b();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const uniform_real_distribution& __x,
                        const uniform_real_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const uniform_real_distribution& __x,
                        const uniform_real_distribution& __y)
        {return !(__x == __y);}
};

template<class _RealType>
template<class _URNG>
inline
typename uniform_real_distribution<_RealType>::result_type
uniform_real_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
{
    return (__p.b() - __p.a())
        * _VSTD::generate_canonical<_RealType, numeric_limits<_RealType>::digits>(__g)
        + __p.a();
}

//template <class _CharT, class _Traits, class _RT>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const uniform_real_distribution<_RT>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    return __os << __x.a() << __sp << __x.b();
//}

//template <class _CharT, class _Traits, class _RT>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           uniform_real_distribution<_RT>& __x)
//{
//    typedef uniform_real_distribution<_RT> _Eng;
//    typedef typename _Eng::result_type result_type;
//    typedef typename _Eng::param_type param_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    result_type __a;
//    result_type __b;
//    __is >> __a >> __b;
//    if (!__is.fail())
//        __x.param(param_type(__a, __b));
//    return __is;
//}

// bernoulli_distribution

class _LIBCPP_TEMPLATE_VIS bernoulli_distribution
{
public:
    // types
    typedef bool result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        double __p_;
    public:
        typedef bernoulli_distribution distribution_type;

        _LIBCPP_INLINE_VISIBILITY
        explicit param_type(double __p = 0.5) : __p_(__p) {}

        _LIBCPP_INLINE_VISIBILITY
        double p() const {return __p_;}

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__p_ == __y.__p_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
    };

private:
    param_type __p_;

public:
    // constructors and reset functions
    _LIBCPP_INLINE_VISIBILITY
    explicit bernoulli_distribution(double __p = 0.5)
        : __p_(param_type(__p)) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit bernoulli_distribution(const param_type& __p) : __p_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    void reset() {}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG> _LIBCPP_INLINE_VISIBILITY result_type operator()(_URNG& __g, const param_type& __p);

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    double p() const {return __p_.p();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return false;}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return true;}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const bernoulli_distribution& __x,
                        const bernoulli_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const bernoulli_distribution& __x,
                        const bernoulli_distribution& __y)
        {return !(__x == __y);}
};

template<class _URNG>
inline
bernoulli_distribution::result_type
bernoulli_distribution::operator()(_URNG& __g, const param_type& __p)
{
    uniform_real_distribution<double> __gen;
    return __gen(__g) < __p.p();
}

//template <class _CharT, class _Traits>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os, const bernoulli_distribution& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    return __os << __x.p();
//}

//template <class _CharT, class _Traits>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is, bernoulli_distribution& __x)
//{
//    typedef bernoulli_distribution _Eng;
//    typedef typename _Eng::param_type param_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    double __p;
//    __is >> __p;
//    if (!__is.fail())
//        __x.param(param_type(__p));
//    return __is;
//}

// binomial_distribution

template<class _IntType = int>
class _LIBCPP_TEMPLATE_VIS binomial_distribution
{
public:
    // types
    typedef _IntType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        result_type __t_;
        double __p_;
        double __pr_;
        double __odds_ratio_;
        result_type __r0_;
    public:
        typedef binomial_distribution distribution_type;

        explicit param_type(result_type __t = 1, double __p = 0.5);

        _LIBCPP_INLINE_VISIBILITY
        result_type t() const {return __t_;}
        _LIBCPP_INLINE_VISIBILITY
        double p() const {return __p_;}

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__t_ == __y.__t_ && __x.__p_ == __y.__p_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}

        friend class binomial_distribution;
    };

private:
    param_type __p_;

public:
    // constructors and reset functions
    _LIBCPP_INLINE_VISIBILITY
    explicit binomial_distribution(result_type __t = 1, double __p = 0.5)
        : __p_(param_type(__t, __p)) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit binomial_distribution(const param_type& __p) : __p_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    void reset() {}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    result_type t() const {return __p_.t();}
    _LIBCPP_INLINE_VISIBILITY
    double p() const {return __p_.p();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return 0;}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return t();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const binomial_distribution& __x,
                        const binomial_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const binomial_distribution& __x,
                        const binomial_distribution& __y)
        {return !(__x == __y);}
};

#ifndef _LIBCPP_MSVCRT
extern "C" double lgamma_r(double, int *);
#endif

inline _LIBCPP_INLINE_VISIBILITY double __libcpp_lgamma(double __d) {
#if defined(_LIBCPP_MSVCRT)
  return lgamma(__d);
#else
  int __sign;
  return lgamma_r(__d, &__sign);
#endif
}

template<class _IntType>
binomial_distribution<_IntType>::param_type::param_type(const result_type __t, const double __p)
    : __t_(__t), __p_(__p)
{
    if (0 < __p_ && __p_ < 1)
    {
        __r0_ = static_cast<result_type>((__t_ + 1) * __p_);
        __pr_ = exp(__libcpp_lgamma(__t_ + 1.) -
                           __libcpp_lgamma(__r0_ + 1.) -
                           __libcpp_lgamma(__t_ - __r0_ + 1.) + __r0_ * math_log(__p_) +
                           (__t_ - __r0_) * math_log(1 - __p_));
        __odds_ratio_ = __p_ / (1 - __p_);
    }
}

// Reference: Kemp, C.D. (1986). `A modal method for generating binomial
//           variables', Commun. Statist. - Theor. Meth. 15(3), 805-813.
template<class _IntType>
template<class _URNG>
_IntType
binomial_distribution<_IntType>::operator()(_URNG& __g, const param_type& __pr)
{
    if (__pr.__t_ == 0 || __pr.__p_ == 0)
        return 0;
    if (__pr.__p_ == 1)
        return __pr.__t_;
    uniform_real_distribution<double> __gen;
    double __u = __gen(__g) - __pr.__pr_;
    if (__u < 0)
        return __pr.__r0_;
    double __pu = __pr.__pr_;
    double __pd = __pu;
    result_type __ru = __pr.__r0_;
    result_type __rd = __ru;
    while (true)
    {
        if (__rd >= 1)
        {
            __pd *= __rd / (__pr.__odds_ratio_ * (__pr.__t_ - __rd + 1));
            __u -= __pd;
            if (__u < 0)
                return __rd - 1;
        }
        if ( __rd != 0 )
            --__rd;
        ++__ru;
        if (__ru <= __pr.__t_)
        {
            __pu *= (__pr.__t_ - __ru + 1) * __pr.__odds_ratio_ / __ru;
            __u -= __pu;
            if (__u < 0)
                return __ru;
        }
    }
}

//template <class _CharT, class _Traits, class _IntType>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const binomial_distribution<_IntType>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    return __os << __x.t() << __sp << __x.p();
//}

//template <class _CharT, class _Traits, class _IntType>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           binomial_distribution<_IntType>& __x)
//{
//    typedef binomial_distribution<_IntType> _Eng;
//    typedef typename _Eng::result_type result_type;
//    typedef typename _Eng::param_type param_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    result_type __t;
//    double __p;
//    __is >> __t >> __p;
//    if (!__is.fail())
//        __x.param(param_type(__t, __p));
//    return __is;
//}

// exponential_distribution

template<class _RealType = double>
class _LIBCPP_TEMPLATE_VIS exponential_distribution
{
public:
    // types
    typedef _RealType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        result_type __lambda_;
    public:
        typedef exponential_distribution distribution_type;

        _LIBCPP_INLINE_VISIBILITY
        explicit param_type(result_type __lambda = 1) : __lambda_(__lambda) {}

        _LIBCPP_INLINE_VISIBILITY
        result_type lambda() const {return __lambda_;}

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__lambda_ == __y.__lambda_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
    };

private:
    param_type __p_;

public:
    // constructors and reset functions
    _LIBCPP_INLINE_VISIBILITY
    explicit exponential_distribution(result_type __lambda = 1)
        : __p_(param_type(__lambda)) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit exponential_distribution(const param_type& __p) : __p_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    void reset() {}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    result_type lambda() const {return __p_.lambda();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return 0;}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return numeric_limits<result_type>::infinity();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const exponential_distribution& __x,
                        const exponential_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const exponential_distribution& __x,
                        const exponential_distribution& __y)
        {return !(__x == __y);}
};

template <class _RealType>
template<class _URNG>
_RealType
exponential_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
{
    return -log
                  (
                      result_type(1) -
                      _VSTD::generate_canonical<result_type,
                                       numeric_limits<result_type>::digits>(__g)
                  )
                  / __p.lambda();
}

//template <class _CharT, class _Traits, class _RealType>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const exponential_distribution<_RealType>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    return __os << __x.lambda();
//}

//template <class _CharT, class _Traits, class _RealType>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           exponential_distribution<_RealType>& __x)
//{
//    typedef exponential_distribution<_RealType> _Eng;
//    typedef typename _Eng::result_type result_type;
//    typedef typename _Eng::param_type param_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    result_type __lambda;
//    __is >> __lambda;
//    if (!__is.fail())
//        __x.param(param_type(__lambda));
//    return __is;
//}

// normal_distribution

template<class _RealType = double>
class _LIBCPP_TEMPLATE_VIS normal_distribution
{
public:
    // types
    typedef _RealType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        result_type __mean_;
        result_type __stddev_;
    public:
        typedef normal_distribution distribution_type;

        _LIBCPP_INLINE_VISIBILITY
        explicit param_type(result_type __mean = 0, result_type __stddev = 1)
            : __mean_(__mean), __stddev_(__stddev) {}

        _LIBCPP_INLINE_VISIBILITY
        result_type mean() const {return __mean_;}
        _LIBCPP_INLINE_VISIBILITY
        result_type stddev() const {return __stddev_;}

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__mean_ == __y.__mean_ && __x.__stddev_ == __y.__stddev_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
    };

private:
    param_type __p_;
    result_type _V_;
    bool _V_hot_;

public:
    // constructors and reset functions
    _LIBCPP_INLINE_VISIBILITY
    explicit normal_distribution(result_type __mean = 0, result_type __stddev = 1)
        : __p_(param_type(__mean, __stddev)), _V_hot_(false) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit normal_distribution(const param_type& __p)
        : __p_(__p), _V_hot_(false) {}
    _LIBCPP_INLINE_VISIBILITY
    void reset() {_V_hot_ = false;}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    result_type mean() const {return __p_.mean();}
    _LIBCPP_INLINE_VISIBILITY
    result_type stddev() const {return __p_.stddev();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return -numeric_limits<result_type>::infinity();}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return numeric_limits<result_type>::infinity();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const normal_distribution& __x,
                        const normal_distribution& __y)
        {return __x.__p_ == __y.__p_ && __x._V_hot_ == __y._V_hot_ &&
                (!__x._V_hot_ || __x._V_ == __y._V_);}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const normal_distribution& __x,
                        const normal_distribution& __y)
        {return !(__x == __y);}

    template <class _CharT, class _Traits, class _RT>
    friend
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
               const normal_distribution<_RT>& __x);

    template <class _CharT, class _Traits, class _RT>
    friend
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __is,
               normal_distribution<_RT>& __x);
};

template <class _RealType>
template<class _URNG>
_RealType
normal_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
{
    result_type _Up;
    if (_V_hot_)
    {
        _V_hot_ = false;
        _Up = _V_;
    }
    else
    {
        uniform_real_distribution<result_type> _Uni(-1, 1);
        result_type __u;
        result_type __v;
        result_type __s;
        do
        {
            __u = _Uni(__g);
            __v = _Uni(__g);
            __s = __u * __u + __v * __v;
        } while (__s > 1 || __s == 0);
        result_type _Fp = sqrt(-2 * log(__s) / __s);
        _V_ = __v * _Fp;
        _V_hot_ = true;
        _Up = __u * _Fp;
    }
    return _Up * __p.stddev() + __p.mean();
}

//template <class _CharT, class _Traits, class _RT>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const normal_distribution<_RT>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    __os << __x.mean() << __sp << __x.stddev() << __sp << __x._V_hot_;
//    if (__x._V_hot_)
//        __os << __sp << __x._V_;
//    return __os;
//}

//template <class _CharT, class _Traits, class _RT>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           normal_distribution<_RT>& __x)
//{
//    typedef normal_distribution<_RT> _Eng;
//    typedef typename _Eng::result_type result_type;
//    typedef typename _Eng::param_type param_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    result_type __mean;
//    result_type __stddev;
//    result_type _Vp = 0;
//    bool _V_hot = false;
//    __is >> __mean >> __stddev >> _V_hot;
//    if (_V_hot)
//        __is >> _Vp;
//    if (!__is.fail())
//    {
//        __x.param(param_type(__mean, __stddev));
//        __x._V_hot_ = _V_hot;
//        __x._V_ = _Vp;
//    }
//    return __is;
//}

// lognormal_distribution

template<class _RealType = double>
class _LIBCPP_TEMPLATE_VIS lognormal_distribution
{
public:
    // types
    typedef _RealType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        normal_distribution<result_type> __nd_;
    public:
        typedef lognormal_distribution distribution_type;

        _LIBCPP_INLINE_VISIBILITY
        explicit param_type(result_type __m = 0, result_type __s = 1)
            : __nd_(__m, __s) {}

        _LIBCPP_INLINE_VISIBILITY
        result_type m() const {return __nd_.mean();}
        _LIBCPP_INLINE_VISIBILITY
        result_type s() const {return __nd_.stddev();}

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__nd_ == __y.__nd_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
        friend class lognormal_distribution;

        template <class _CharT, class _Traits, class _RT>
        friend
        basic_ostream<_CharT, _Traits>&
        operator<<(basic_ostream<_CharT, _Traits>& __os,
                   const lognormal_distribution<_RT>& __x);

        template <class _CharT, class _Traits, class _RT>
        friend
        basic_istream<_CharT, _Traits>&
        operator>>(basic_istream<_CharT, _Traits>& __is,
                   lognormal_distribution<_RT>& __x);
    };

private:
    param_type __p_;

public:
    // constructor and reset functions
    _LIBCPP_INLINE_VISIBILITY
    explicit lognormal_distribution(result_type __m = 0, result_type __s = 1)
        : __p_(param_type(__m, __s)) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit lognormal_distribution(const param_type& __p)
        : __p_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    void reset() {__p_.__nd_.reset();}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g, const param_type& __p)
        {return exp(const_cast<normal_distribution<result_type>&>(__p.__nd_)(__g));}

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    result_type m() const {return __p_.m();}
    _LIBCPP_INLINE_VISIBILITY
    result_type s() const {return __p_.s();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return 0;}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return numeric_limits<result_type>::infinity();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const lognormal_distribution& __x,
                        const lognormal_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const lognormal_distribution& __x,
                        const lognormal_distribution& __y)
        {return !(__x == __y);}

    template <class _CharT, class _Traits, class _RT>
    friend
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
               const lognormal_distribution<_RT>& __x);

    template <class _CharT, class _Traits, class _RT>
    friend
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __is,
               lognormal_distribution<_RT>& __x);
};

template <class _CharT, class _Traits, class _RT>
inline _LIBCPP_INLINE_VISIBILITY
basic_ostream<_CharT, _Traits>&
operator<<(basic_ostream<_CharT, _Traits>& __os,
           const lognormal_distribution<_RT>& __x)
{
    return __os << __x.__p_.__nd_;
}

template <class _CharT, class _Traits, class _RT>
inline _LIBCPP_INLINE_VISIBILITY
basic_istream<_CharT, _Traits>&
operator>>(basic_istream<_CharT, _Traits>& __is,
           lognormal_distribution<_RT>& __x)
{
    return __is >> __x.__p_.__nd_;
}

// poisson_distribution

template<class _IntType = int>
class _LIBCPP_TEMPLATE_VIS poisson_distribution
{
public:
    // types
    typedef _IntType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        double __mean_;
        double __s_;
        double __d_;
        double __l_;
        double __omega_;
        double __c0_;
        double __c1_;
        double __c2_;
        double __c3_;
        double __c_;

    public:
        typedef poisson_distribution distribution_type;

        explicit param_type(double __mean = 1.0);

        _LIBCPP_INLINE_VISIBILITY
        double mean() const {return __mean_;}

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__mean_ == __y.__mean_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}

        friend class poisson_distribution;
    };

private:
    param_type __p_;

public:
    // constructors and reset functions
    _LIBCPP_INLINE_VISIBILITY
    explicit poisson_distribution(double __mean = 1.0) : __p_(__mean) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit poisson_distribution(const param_type& __p) : __p_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    void reset() {}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    double mean() const {return __p_.mean();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return 0;}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return numeric_limits<result_type>::max();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const poisson_distribution& __x,
                        const poisson_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const poisson_distribution& __x,
                        const poisson_distribution& __y)
        {return !(__x == __y);}
};

template<class _IntType>
poisson_distribution<_IntType>::param_type::param_type(double __mean)
    : __mean_(__mean)
{
    if (__mean_ < 10)
    {
        __s_ = 0;
        __d_ = 0;
        __l_ = exp(-__mean_);
        __omega_ = 0;
        __c3_ = 0;
        __c2_ = 0;
        __c1_ = 0;
        __c0_ = 0;
        __c_ = 0;
    }
    else
    {
        __s_ = sqrt(__mean_);
        __d_ = 6 * __mean_ * __mean_;
        __l_ = static_cast<result_type>(__mean_ - 1.1484);
        __omega_ = .3989423 / __s_;
        double __b1_ = .4166667E-1 / __mean_;
        double __b2_ = .3 * __b1_ * __b1_;
        __c3_ = .1428571 * __b1_ * __b2_;
        __c2_ = __b2_ - 15. * __c3_;
        __c1_ = __b1_ - 6. * __b2_ + 45. * __c3_;
        __c0_ = 1. - __b1_ + 3. * __b2_ - 15. * __c3_;
        __c_ = .1069 / __mean_;
    }
}

template <class _IntType>
template<class _URNG>
_IntType
poisson_distribution<_IntType>::operator()(_URNG& __urng, const param_type& __pr)
{
    result_type __x;
    uniform_real_distribution<double> __urd;
    if (__pr.__mean_ < 10)
    {
         __x = 0;
        for (double __p = __urd(__urng); __p > __pr.__l_; ++__x)
            __p *= __urd(__urng);
    }
    else
    {
        double __difmuk;
        double __g = __pr.__mean_ + __pr.__s_ * normal_distribution<double>()(__urng);
        double __u;
        if (__g > 0)
        {
            __x = static_cast<result_type>(__g);
            if (__x >= __pr.__l_)
                return __x;
            __difmuk = __pr.__mean_ - __x;
            __u = __urd(__urng);
            if (__pr.__d_ * __u >= __difmuk * __difmuk * __difmuk)
                return __x;
        }
        exponential_distribution<double> __edist;
        for (bool __using_exp_dist = false; true; __using_exp_dist = true)
        {
            double __e;
            if (__using_exp_dist || __g < 0)
            {
                double __t;
                do
                {
                    __e = __edist(__urng);
                    __u = __urd(__urng);
                    __u += __u - 1;
                    __t = 1.8 + (__u < 0 ? -__e : __e);
                } while (__t <= -.6744);
                __x = __pr.__mean_ + __pr.__s_ * __t;
                __difmuk = __pr.__mean_ - __x;
                __using_exp_dist = true;
            }
            double __px;
            double __py;
            if (__x < 10)
            {
                const result_type __fac[] = {1, 1, 2, 6, 24, 120, 720, 5040,
                                             40320, 362880};
                __px = -__pr.__mean_;
                __py = pow(__pr.__mean_, (double)__x) / __fac[__x];
            }
            else
            {
                double __del = .8333333E-1 / __x;
                __del -= 4.8 * __del * __del * __del;
                double __v = __difmuk / __x;
                if (abs(__v) > 0.25)
                    __px = __x * math_log(1 + __v) - __difmuk - __del;
                else
                    __px = __x * __v * __v * (((((((.1250060 * __v + -.1384794) *
                           __v + .1421878) * __v + -.1661269) * __v + .2000118) *
                           __v + -.2500068) * __v + .3333333) * __v + -.5) - __del;
                __py = .3989423 / sqrt(__x);
            }
            double __r = (0.5 - __difmuk) / __pr.__s_;
            double __r2 = __r * __r;
            double __fx = -0.5 * __r2;
            double __fy = __pr.__omega_ * (((__pr.__c3_ * __r2 + __pr.__c2_) *
                                        __r2 + __pr.__c1_) * __r2 + __pr.__c0_);
            if (__using_exp_dist)
            {
                if (__pr.__c_ * abs(__u) <= __py * exp(__px + __e) -
                                                   __fy * exp(__fx + __e))
                    break;
            }
            else
            {
                if (__fy - __u * __fy <= __py * exp(__px - __fx))
                    break;
            }
        }
    }
    return __x;
}

//template <class _CharT, class _Traits, class _IntType>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const poisson_distribution<_IntType>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    return __os << __x.mean();
//}

//template <class _CharT, class _Traits, class _IntType>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           poisson_distribution<_IntType>& __x)
//{
//    typedef poisson_distribution<_IntType> _Eng;
//    typedef typename _Eng::param_type param_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    double __mean;
//    __is >> __mean;
//    if (!__is.fail())
//        __x.param(param_type(__mean));
//    return __is;
//}

// weibull_distribution

template<class _RealType = double>
class _LIBCPP_TEMPLATE_VIS weibull_distribution
{
public:
    // types
    typedef _RealType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        result_type __a_;
        result_type __b_;
    public:
        typedef weibull_distribution distribution_type;

        _LIBCPP_INLINE_VISIBILITY
        explicit param_type(result_type __a = 1, result_type __b = 1)
            : __a_(__a), __b_(__b) {}

        _LIBCPP_INLINE_VISIBILITY
        result_type a() const {return __a_;}
        _LIBCPP_INLINE_VISIBILITY
        result_type b() const {return __b_;}

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__a_ == __y.__a_ && __x.__b_ == __y.__b_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
    };

private:
    param_type __p_;

public:
    // constructor and reset functions
    _LIBCPP_INLINE_VISIBILITY
    explicit weibull_distribution(result_type __a = 1, result_type __b = 1)
        : __p_(param_type(__a, __b)) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit weibull_distribution(const param_type& __p)
        : __p_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    void reset() {}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g, const param_type& __p)
        {return __p.b() *
            pow(exponential_distribution<result_type>()(__g), 1/__p.a());}

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    result_type a() const {return __p_.a();}
    _LIBCPP_INLINE_VISIBILITY
    result_type b() const {return __p_.b();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return 0;}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return numeric_limits<result_type>::infinity();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const weibull_distribution& __x,
                        const weibull_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const weibull_distribution& __x,
                        const weibull_distribution& __y)
        {return !(__x == __y);}
};

//template <class _CharT, class _Traits, class _RT>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const weibull_distribution<_RT>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    __os << __x.a() << __sp << __x.b();
//    return __os;
//}

//template <class _CharT, class _Traits, class _RT>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           weibull_distribution<_RT>& __x)
//{
//    typedef weibull_distribution<_RT> _Eng;
//    typedef typename _Eng::result_type result_type;
//    typedef typename _Eng::param_type param_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    result_type __a;
//    result_type __b;
//    __is >> __a >> __b;
//    if (!__is.fail())
//        __x.param(param_type(__a, __b));
//    return __is;
//}

template<class _RealType = double>
class _LIBCPP_TEMPLATE_VIS extreme_value_distribution
{
public:
    // types
    typedef _RealType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        result_type __a_;
        result_type __b_;
    public:
        typedef extreme_value_distribution distribution_type;

        _LIBCPP_INLINE_VISIBILITY
        explicit param_type(result_type __a = 0, result_type __b = 1)
            : __a_(__a), __b_(__b) {}

        _LIBCPP_INLINE_VISIBILITY
        result_type a() const {return __a_;}
        _LIBCPP_INLINE_VISIBILITY
        result_type b() const {return __b_;}

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__a_ == __y.__a_ && __x.__b_ == __y.__b_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
    };

private:
    param_type __p_;

public:
    // constructor and reset functions
    _LIBCPP_INLINE_VISIBILITY
    explicit extreme_value_distribution(result_type __a = 0, result_type __b = 1)
        : __p_(param_type(__a, __b)) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit extreme_value_distribution(const param_type& __p)
        : __p_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    void reset() {}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    result_type a() const {return __p_.a();}
    _LIBCPP_INLINE_VISIBILITY
    result_type b() const {return __p_.b();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return -numeric_limits<result_type>::infinity();}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return numeric_limits<result_type>::infinity();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const extreme_value_distribution& __x,
                        const extreme_value_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const extreme_value_distribution& __x,
                        const extreme_value_distribution& __y)
        {return !(__x == __y);}
};

template<class _RealType>
template<class _URNG>
_RealType
extreme_value_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
{
    return __p.a() - __p.b() *
         log(-log(1-uniform_real_distribution<result_type>()(__g)));
}

//template <class _CharT, class _Traits, class _RT>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const extreme_value_distribution<_RT>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    __os << __x.a() << __sp << __x.b();
//    return __os;
//}

//template <class _CharT, class _Traits, class _RT>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           extreme_value_distribution<_RT>& __x)
//{
//    typedef extreme_value_distribution<_RT> _Eng;
//    typedef typename _Eng::result_type result_type;
//    typedef typename _Eng::param_type param_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    result_type __a;
//    result_type __b;
//    __is >> __a >> __b;
//    if (!__is.fail())
//        __x.param(param_type(__a, __b));
//    return __is;
//}

// gamma_distribution

template<class _RealType = double>
class _LIBCPP_TEMPLATE_VIS gamma_distribution
{
public:
    // types
    typedef _RealType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        result_type __alpha_;
        result_type __beta_;
    public:
        typedef gamma_distribution distribution_type;

        _LIBCPP_INLINE_VISIBILITY
        explicit param_type(result_type __alpha = 1, result_type __beta = 1)
            : __alpha_(__alpha), __beta_(__beta) {}

        _LIBCPP_INLINE_VISIBILITY
        result_type alpha() const {return __alpha_;}
        _LIBCPP_INLINE_VISIBILITY
        result_type beta() const {return __beta_;}

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__alpha_ == __y.__alpha_ && __x.__beta_ == __y.__beta_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
    };

private:
    param_type __p_;

public:
    // constructors and reset functions
    _LIBCPP_INLINE_VISIBILITY
    explicit gamma_distribution(result_type __alpha = 1, result_type __beta = 1)
        : __p_(param_type(__alpha, __beta)) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit gamma_distribution(const param_type& __p)
        : __p_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    void reset() {}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    result_type alpha() const {return __p_.alpha();}
    _LIBCPP_INLINE_VISIBILITY
    result_type beta() const {return __p_.beta();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return 0;}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return numeric_limits<result_type>::infinity();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const gamma_distribution& __x,
                        const gamma_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const gamma_distribution& __x,
                        const gamma_distribution& __y)
        {return !(__x == __y);}
};

template <class _RealType>
template<class _URNG>
_RealType
gamma_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
{
    result_type __a = __p.alpha();
    uniform_real_distribution<result_type> __gen(0, 1);
    exponential_distribution<result_type> __egen;
    result_type __x;
    if (__a == 1)
        __x = __egen(__g);
    else if (__a > 1)
    {
        const result_type __b = __a - 1;
        const result_type __c = 3 * __a - result_type(0.75);
        while (true)
        {
            const result_type __u = __gen(__g);
            const result_type __v = __gen(__g);
            const result_type __w = __u * (1 - __u);
            if (__w != 0)
            {
                const result_type __y = sqrt(__c / __w) *
                                        (__u - result_type(0.5));
                __x = __b + __y;
                if (__x >= 0)
                {
                    const result_type __z = 64 * __w * __w * __w * __v * __v;
                    if (__z <= 1 - 2 * __y * __y / __x)
                        break;
                    if (log(__z) <= 2 * (__b * log(__x / __b) - __y))
                        break;
                }
            }
        }
    }
    else  // __a < 1
    {
        while (true)
        {
            const result_type __u = __gen(__g);
            const result_type __es = __egen(__g);
            if (__u <= 1 - __a)
            {
                __x = pow(__u, 1 / __a);
                if (__x <= __es)
                    break;
            }
            else
            {
                const result_type __e = -log((1-__u)/__a);
                __x = pow(1 - __a + __a * __e, 1 / __a);
                if (__x <= __e + __es)
                    break;
            }
        }
    }
    return __x * __p.beta();
}

//template <class _CharT, class _Traits, class _RT>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const gamma_distribution<_RT>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    __os << __x.alpha() << __sp << __x.beta();
//    return __os;
//}

//template <class _CharT, class _Traits, class _RT>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           gamma_distribution<_RT>& __x)
//{
//    typedef gamma_distribution<_RT> _Eng;
//    typedef typename _Eng::result_type result_type;
//    typedef typename _Eng::param_type param_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    result_type __alpha;
//    result_type __beta;
//    __is >> __alpha >> __beta;
//    if (!__is.fail())
//        __x.param(param_type(__alpha, __beta));
//    return __is;
//}

// negative_binomial_distribution

template<class _IntType = int>
class _LIBCPP_TEMPLATE_VIS negative_binomial_distribution
{
public:
    // types
    typedef _IntType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        result_type __k_;
        double __p_;
    public:
        typedef negative_binomial_distribution distribution_type;

        _LIBCPP_INLINE_VISIBILITY
        explicit param_type(result_type __k = 1, double __p = 0.5)
            : __k_(__k), __p_(__p) {}

        _LIBCPP_INLINE_VISIBILITY
        result_type k() const {return __k_;}
        _LIBCPP_INLINE_VISIBILITY
        double p() const {return __p_;}

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__k_ == __y.__k_ && __x.__p_ == __y.__p_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
    };

private:
    param_type __p_;

public:
    // constructor and reset functions
    _LIBCPP_INLINE_VISIBILITY
    explicit negative_binomial_distribution(result_type __k = 1, double __p = 0.5)
        : __p_(__k, __p) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit negative_binomial_distribution(const param_type& __p) : __p_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    void reset() {}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    result_type k() const {return __p_.k();}
    _LIBCPP_INLINE_VISIBILITY
    double p() const {return __p_.p();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return 0;}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return numeric_limits<result_type>::max();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const negative_binomial_distribution& __x,
                        const negative_binomial_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const negative_binomial_distribution& __x,
                        const negative_binomial_distribution& __y)
        {return !(__x == __y);}
};

template <class _IntType>
template<class _URNG>
_IntType
negative_binomial_distribution<_IntType>::operator()(_URNG& __urng, const param_type& __pr)
{
    result_type __k = __pr.k();
    double __p = __pr.p();
    if (__k <= 21 * __p)
    {
        bernoulli_distribution __gen(__p);
        result_type __f = 0;
        result_type __s = 0;
        while (__s < __k)
        {
            if (__gen(__urng))
                ++__s;
            else
                ++__f;
        }
        return __f;
    }
    return poisson_distribution<result_type>(gamma_distribution<double>
                                            (__k, (1-__p)/__p)(__urng))(__urng);
}

//template <class _CharT, class _Traits, class _IntType>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const negative_binomial_distribution<_IntType>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    return __os << __x.k() << __sp << __x.p();
//}

//template <class _CharT, class _Traits, class _IntType>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           negative_binomial_distribution<_IntType>& __x)
//{
//    typedef negative_binomial_distribution<_IntType> _Eng;
//    typedef typename _Eng::result_type result_type;
//    typedef typename _Eng::param_type param_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    result_type __k;
//    double __p;
//    __is >> __k >> __p;
//    if (!__is.fail())
//        __x.param(param_type(__k, __p));
//    return __is;
//}

// geometric_distribution

template<class _IntType = int>
class _LIBCPP_TEMPLATE_VIS geometric_distribution
{
public:
    // types
    typedef _IntType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        double __p_;
    public:
        typedef geometric_distribution distribution_type;

        _LIBCPP_INLINE_VISIBILITY
        explicit param_type(double __p = 0.5) : __p_(__p) {}

        _LIBCPP_INLINE_VISIBILITY
        double p() const {return __p_;}

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__p_ == __y.__p_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
    };

private:
    param_type __p_;

public:
    // constructors and reset functions
    _LIBCPP_INLINE_VISIBILITY
    explicit geometric_distribution(double __p = 0.5) : __p_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit geometric_distribution(const param_type& __p) : __p_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    void reset() {}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g, const param_type& __p)
        {return negative_binomial_distribution<result_type>(1, __p.p())(__g);}

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    double p() const {return __p_.p();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return 0;}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return numeric_limits<result_type>::max();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const geometric_distribution& __x,
                        const geometric_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const geometric_distribution& __x,
                        const geometric_distribution& __y)
        {return !(__x == __y);}
};

//template <class _CharT, class _Traits, class _IntType>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const geometric_distribution<_IntType>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    return __os << __x.p();
//}

//template <class _CharT, class _Traits, class _IntType>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           geometric_distribution<_IntType>& __x)
//{
//    typedef geometric_distribution<_IntType> _Eng;
//    typedef typename _Eng::param_type param_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    double __p;
//    __is >> __p;
//    if (!__is.fail())
//        __x.param(param_type(__p));
//    return __is;
//}

// chi_squared_distribution

template<class _RealType = double>
class _LIBCPP_TEMPLATE_VIS chi_squared_distribution
{
public:
    // types
    typedef _RealType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        result_type __n_;
    public:
        typedef chi_squared_distribution distribution_type;

        _LIBCPP_INLINE_VISIBILITY
        explicit param_type(result_type __n = 1) : __n_(__n) {}

        _LIBCPP_INLINE_VISIBILITY
        result_type n() const {return __n_;}

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__n_ == __y.__n_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
    };

private:
    param_type __p_;

public:
    // constructor and reset functions
    _LIBCPP_INLINE_VISIBILITY
    explicit chi_squared_distribution(result_type __n = 1)
        : __p_(param_type(__n)) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit chi_squared_distribution(const param_type& __p)
        : __p_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    void reset() {}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g, const param_type& __p)
        {return gamma_distribution<result_type>(__p.n() / 2, 2)(__g);}

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    result_type n() const {return __p_.n();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return 0;}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return numeric_limits<result_type>::infinity();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const chi_squared_distribution& __x,
                        const chi_squared_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const chi_squared_distribution& __x,
                        const chi_squared_distribution& __y)
        {return !(__x == __y);}
};

//template <class _CharT, class _Traits, class _RT>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const chi_squared_distribution<_RT>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    __os << __x.n();
//    return __os;
//}

//template <class _CharT, class _Traits, class _RT>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           chi_squared_distribution<_RT>& __x)
//{
//    typedef chi_squared_distribution<_RT> _Eng;
//    typedef typename _Eng::result_type result_type;
//    typedef typename _Eng::param_type param_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    result_type __n;
//    __is >> __n;
//    if (!__is.fail())
//        __x.param(param_type(__n));
//    return __is;
//}

// cauchy_distribution

template<class _RealType = double>
class _LIBCPP_TEMPLATE_VIS cauchy_distribution
{
public:
    // types
    typedef _RealType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        result_type __a_;
        result_type __b_;
    public:
        typedef cauchy_distribution distribution_type;

        _LIBCPP_INLINE_VISIBILITY
        explicit param_type(result_type __a = 0, result_type __b = 1)
            : __a_(__a), __b_(__b) {}

        _LIBCPP_INLINE_VISIBILITY
        result_type a() const {return __a_;}
        _LIBCPP_INLINE_VISIBILITY
        result_type b() const {return __b_;}

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__a_ == __y.__a_ && __x.__b_ == __y.__b_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
    };

private:
    param_type __p_;

public:
    // constructor and reset functions
    _LIBCPP_INLINE_VISIBILITY
    explicit cauchy_distribution(result_type __a = 0, result_type __b = 1)
        : __p_(param_type(__a, __b)) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit cauchy_distribution(const param_type& __p)
        : __p_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    void reset() {}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG> _LIBCPP_INLINE_VISIBILITY result_type operator()(_URNG& __g, const param_type& __p);

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    result_type a() const {return __p_.a();}
    _LIBCPP_INLINE_VISIBILITY
    result_type b() const {return __p_.b();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return -numeric_limits<result_type>::infinity();}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return numeric_limits<result_type>::infinity();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const cauchy_distribution& __x,
                        const cauchy_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const cauchy_distribution& __x,
                        const cauchy_distribution& __y)
        {return !(__x == __y);}
};

template <class _RealType>
template<class _URNG>
inline
_RealType
cauchy_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
{
    uniform_real_distribution<result_type> __gen;
    // purposefully let tan arg get as close to pi/2 as it wants, tan will return a finite
    return __p.a() + __p.b() * tan(3.1415926535897932384626433832795 * __gen(__g));
}

//template <class _CharT, class _Traits, class _RT>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const cauchy_distribution<_RT>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    __os << __x.a() << __sp << __x.b();
//    return __os;
//}

//template <class _CharT, class _Traits, class _RT>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           cauchy_distribution<_RT>& __x)
//{
//    typedef cauchy_distribution<_RT> _Eng;
//    typedef typename _Eng::result_type result_type;
//    typedef typename _Eng::param_type param_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    result_type __a;
//    result_type __b;
//    __is >> __a >> __b;
//    if (!__is.fail())
//        __x.param(param_type(__a, __b));
//    return __is;
//}

// fisher_f_distribution

template<class _RealType = double>
class _LIBCPP_TEMPLATE_VIS fisher_f_distribution
{
public:
    // types
    typedef _RealType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        result_type __m_;
        result_type __n_;
    public:
        typedef fisher_f_distribution distribution_type;

        _LIBCPP_INLINE_VISIBILITY
        explicit param_type(result_type __m = 1, result_type __n = 1)
            : __m_(__m), __n_(__n) {}

        _LIBCPP_INLINE_VISIBILITY
        result_type m() const {return __m_;}
        _LIBCPP_INLINE_VISIBILITY
        result_type n() const {return __n_;}

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__m_ == __y.__m_ && __x.__n_ == __y.__n_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
    };

private:
    param_type __p_;

public:
    // constructor and reset functions
    _LIBCPP_INLINE_VISIBILITY
    explicit fisher_f_distribution(result_type __m = 1, result_type __n = 1)
        : __p_(param_type(__m, __n)) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit fisher_f_distribution(const param_type& __p)
        : __p_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    void reset() {}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    result_type m() const {return __p_.m();}
    _LIBCPP_INLINE_VISIBILITY
    result_type n() const {return __p_.n();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return 0;}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return numeric_limits<result_type>::infinity();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const fisher_f_distribution& __x,
                        const fisher_f_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const fisher_f_distribution& __x,
                        const fisher_f_distribution& __y)
        {return !(__x == __y);}
};

template <class _RealType>
template<class _URNG>
_RealType
fisher_f_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
{
    gamma_distribution<result_type> __gdm(__p.m() * result_type(.5));
    gamma_distribution<result_type> __gdn(__p.n() * result_type(.5));
    return __p.n() * __gdm(__g) / (__p.m() * __gdn(__g));
}

//template <class _CharT, class _Traits, class _RT>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const fisher_f_distribution<_RT>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    __os << __x.m() << __sp << __x.n();
//    return __os;
//}

//template <class _CharT, class _Traits, class _RT>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           fisher_f_distribution<_RT>& __x)
//{
//    typedef fisher_f_distribution<_RT> _Eng;
//    typedef typename _Eng::result_type result_type;
//    typedef typename _Eng::param_type param_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    result_type __m;
//    result_type __n;
//    __is >> __m >> __n;
//    if (!__is.fail())
//        __x.param(param_type(__m, __n));
//    return __is;
//}

// student_t_distribution

template<class _RealType = double>
class _LIBCPP_TEMPLATE_VIS student_t_distribution
{
public:
    // types
    typedef _RealType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        result_type __n_;
    public:
        typedef student_t_distribution distribution_type;

        _LIBCPP_INLINE_VISIBILITY
        explicit param_type(result_type __n = 1) : __n_(__n) {}

        _LIBCPP_INLINE_VISIBILITY
        result_type n() const {return __n_;}

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__n_ == __y.__n_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
    };

private:
    param_type __p_;
    normal_distribution<result_type> __nd_;

public:
    // constructor and reset functions
    _LIBCPP_INLINE_VISIBILITY
    explicit student_t_distribution(result_type __n = 1)
        : __p_(param_type(__n)) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit student_t_distribution(const param_type& __p)
        : __p_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    void reset() {__nd_.reset();}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    result_type n() const {return __p_.n();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return -numeric_limits<result_type>::infinity();}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return numeric_limits<result_type>::infinity();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const student_t_distribution& __x,
                        const student_t_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const student_t_distribution& __x,
                        const student_t_distribution& __y)
        {return !(__x == __y);}
};

template <class _RealType>
template<class _URNG>
_RealType
student_t_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
{
    gamma_distribution<result_type> __gd(__p.n() * .5, 2);
    return __nd_(__g) * sqrt(__p.n()/__gd(__g));
}

//template <class _CharT, class _Traits, class _RT>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const student_t_distribution<_RT>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    __os << __x.n();
//    return __os;
//}

//template <class _CharT, class _Traits, class _RT>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           student_t_distribution<_RT>& __x)
//{
//    typedef student_t_distribution<_RT> _Eng;
//    typedef typename _Eng::result_type result_type;
//    typedef typename _Eng::param_type param_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    result_type __n;
//    __is >> __n;
//    if (!__is.fail())
//        __x.param(param_type(__n));
//    return __is;
//}

// discrete_distribution

template<class _IntType = int>
class _LIBCPP_TEMPLATE_VIS discrete_distribution
{
public:
    // types
    typedef _IntType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        vector<double> __p_;
    public:
        typedef discrete_distribution distribution_type;

        _LIBCPP_INLINE_VISIBILITY
        param_type() {}
        template<class _InputIterator>
            _LIBCPP_INLINE_VISIBILITY
            param_type(_InputIterator __f, _InputIterator __l)
            : __p_(__f, __l) {__init();}
#ifndef _LIBCPP_CXX03_LANG
        _LIBCPP_INLINE_VISIBILITY
        param_type(initializer_list<double> __wl)
            : __p_(__wl.begin(), __wl.end()) {__init();}
#endif  // _LIBCPP_CXX03_LANG
        template<class _UnaryOperation>
            param_type(size_t __nw, double __xmin, double __xmax,
                       _UnaryOperation __fw);

        vector<double> probabilities() const;

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__p_ == __y.__p_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}

    private:
        void __init();

        friend class discrete_distribution;

        template <class _CharT, class _Traits, class _IT>
        friend
        basic_ostream<_CharT, _Traits>&
        operator<<(basic_ostream<_CharT, _Traits>& __os,
                   const discrete_distribution<_IT>& __x);

        template <class _CharT, class _Traits, class _IT>
        friend
        basic_istream<_CharT, _Traits>&
        operator>>(basic_istream<_CharT, _Traits>& __is,
                   discrete_distribution<_IT>& __x);
    };

private:
    param_type __p_;

public:
    // constructor and reset functions
    _LIBCPP_INLINE_VISIBILITY
    discrete_distribution() {}
    template<class _InputIterator>
        _LIBCPP_INLINE_VISIBILITY
        discrete_distribution(_InputIterator __f, _InputIterator __l)
            : __p_(__f, __l) {}
#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    discrete_distribution(initializer_list<double> __wl)
        : __p_(__wl) {}
#endif  // _LIBCPP_CXX03_LANG
    template<class _UnaryOperation>
        _LIBCPP_INLINE_VISIBILITY
        discrete_distribution(size_t __nw, double __xmin, double __xmax,
                              _UnaryOperation __fw)
        : __p_(__nw, __xmin, __xmax, __fw) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit discrete_distribution(const param_type& __p)
        : __p_(__p) {}
    _LIBCPP_INLINE_VISIBILITY
    void reset() {}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    vector<double> probabilities() const {return __p_.probabilities();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return 0;}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return __p_.__p_.size();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const discrete_distribution& __x,
                        const discrete_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const discrete_distribution& __x,
                        const discrete_distribution& __y)
        {return !(__x == __y);}

    template <class _CharT, class _Traits, class _IT>
    friend
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
               const discrete_distribution<_IT>& __x);

    template <class _CharT, class _Traits, class _IT>
    friend
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __is,
               discrete_distribution<_IT>& __x);
};

template<class _IntType>
template<class _UnaryOperation>
discrete_distribution<_IntType>::param_type::param_type(size_t __nw,
                                                        double __xmin,
                                                        double __xmax,
                                                        _UnaryOperation __fw)
{
    if (__nw > 1)
    {
        __p_.reserve(__nw - 1);
        double __d = (__xmax - __xmin) / __nw;
        double __d2 = __d / 2;
        for (size_t __k = 0; __k < __nw; ++__k)
            __p_.push_back(__fw(__xmin + __k * __d + __d2));
        __init();
    }
}

template<class _IntType>
void
discrete_distribution<_IntType>::param_type::__init()
{
    if (!__p_.empty())
    {
        if (__p_.size() > 1)
        {
            double __s = _VSTD::accumulate(__p_.begin(), __p_.end(), 0.0);
            for (_VSTD::vector<double>::iterator __i = __p_.begin(), __e = __p_.end();
                                                                       __i < __e; ++__i)
                *__i /= __s;
            vector<double> __t(__p_.size() - 1);
            _VSTD::partial_sum(__p_.begin(), __p_.end() - 1, __t.begin());

            auto tmp = __t;
            __t = __p_;
            __p_ = tmp;
        }
        else
        {
            __p_.clear();
            __p_.shrink_to_fit();
        }
    }
}

template<class _IntType>
vector<double>
discrete_distribution<_IntType>::param_type::probabilities() const
{
    size_t __n = __p_.size();
    _VSTD::vector<double> __p(__n+1);
    _VSTD::adjacent_difference(__p_.begin(), __p_.end(), __p.begin());
    if (__n > 0)
        __p[__n] = 1 - __p_[__n-1];
    else
        __p[0] = 1;
    return __p;
}

template<class _IntType>
template<class _URNG>
_IntType
discrete_distribution<_IntType>::operator()(_URNG& __g, const param_type& __p)
{
    uniform_real_distribution<double> __gen;
    return static_cast<_IntType>(
           _VSTD::upper_bound(__p.__p_.begin(), __p.__p_.end(), __gen(__g)) -
                                                              __p.__p_.begin());
}

//template <class _CharT, class _Traits, class _IT>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const discrete_distribution<_IT>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    size_t __n = __x.__p_.__p_.size();
//    __os << __n;
//    for (size_t __i = 0; __i < __n; ++__i)
//        __os << __sp << __x.__p_.__p_[__i];
//    return __os;
//}

//template <class _CharT, class _Traits, class _IT>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           discrete_distribution<_IT>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    size_t __n;
//    __is >> __n;
//    vector<double> __p(__n);
//    for (size_t __i = 0; __i < __n; ++__i)
//        __is >> __p[__i];
//    if (!__is.fail())
//        swap(__x.__p_.__p_, __p);
//    return __is;
//}

// piecewise_constant_distribution

template<class _RealType = double>
class _LIBCPP_TEMPLATE_VIS piecewise_constant_distribution
{
public:
    // types
    typedef _RealType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        vector<result_type> __b_;
        vector<result_type> __densities_;
        vector<result_type> __areas_;
    public:
        typedef piecewise_constant_distribution distribution_type;

        param_type();
        template<class _InputIteratorB, class _InputIteratorW>
            param_type(_InputIteratorB __fB, _InputIteratorB __lB,
                       _InputIteratorW __fW);
#ifndef _LIBCPP_CXX03_LANG
        template<class _UnaryOperation>
            param_type(initializer_list<result_type> __bl, _UnaryOperation __fw);
#endif  // _LIBCPP_CXX03_LANG
        template<class _UnaryOperation>
            param_type(size_t __nw, result_type __xmin, result_type __xmax,
                       _UnaryOperation __fw);
        param_type & operator=(const param_type& __rhs);

        _LIBCPP_INLINE_VISIBILITY
        vector<result_type> intervals() const {return __b_;}
        _LIBCPP_INLINE_VISIBILITY
        vector<result_type> densities() const {return __densities_;}

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__densities_ == __y.__densities_ && __x.__b_ == __y.__b_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}

    private:
        void __init();

        friend class piecewise_constant_distribution;

        template <class _CharT, class _Traits, class _RT>
        friend
        basic_ostream<_CharT, _Traits>&
        operator<<(basic_ostream<_CharT, _Traits>& __os,
                   const piecewise_constant_distribution<_RT>& __x);

        template <class _CharT, class _Traits, class _RT>
        friend
        basic_istream<_CharT, _Traits>&
        operator>>(basic_istream<_CharT, _Traits>& __is,
                   piecewise_constant_distribution<_RT>& __x);
    };

private:
    param_type __p_;

public:
    // constructor and reset functions
    _LIBCPP_INLINE_VISIBILITY
    piecewise_constant_distribution() {}
    template<class _InputIteratorB, class _InputIteratorW>
        _LIBCPP_INLINE_VISIBILITY
        piecewise_constant_distribution(_InputIteratorB __fB,
                                        _InputIteratorB __lB,
                                        _InputIteratorW __fW)
        : __p_(__fB, __lB, __fW) {}

#ifndef _LIBCPP_CXX03_LANG
    template<class _UnaryOperation>
        _LIBCPP_INLINE_VISIBILITY
        piecewise_constant_distribution(initializer_list<result_type> __bl,
                                        _UnaryOperation __fw)
        : __p_(__bl, __fw) {}
#endif  // _LIBCPP_CXX03_LANG

    template<class _UnaryOperation>
        _LIBCPP_INLINE_VISIBILITY
        piecewise_constant_distribution(size_t __nw, result_type __xmin,
                                        result_type __xmax, _UnaryOperation __fw)
        : __p_(__nw, __xmin, __xmax, __fw) {}

    _LIBCPP_INLINE_VISIBILITY
    explicit piecewise_constant_distribution(const param_type& __p)
        : __p_(__p) {}

    _LIBCPP_INLINE_VISIBILITY
    void reset() {}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    vector<result_type> intervals() const {return __p_.intervals();}
    _LIBCPP_INLINE_VISIBILITY
    vector<result_type> densities() const {return __p_.densities();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return __p_.__b_.front();}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return __p_.__b_.back();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const piecewise_constant_distribution& __x,
                        const piecewise_constant_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const piecewise_constant_distribution& __x,
                           const piecewise_constant_distribution& __y)
        {return !(__x == __y);}

    template <class _CharT, class _Traits, class _RT>
    friend
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
               const piecewise_constant_distribution<_RT>& __x);

    template <class _CharT, class _Traits, class _RT>
    friend
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __is,
               piecewise_constant_distribution<_RT>& __x);
};

template<class _RealType>
typename piecewise_constant_distribution<_RealType>::param_type &
piecewise_constant_distribution<_RealType>::param_type::operator=
                                                       (const param_type& __rhs)
{
//  These can throw
    __b_.reserve        (__rhs.__b_.size ());
    __densities_.reserve(__rhs.__densities_.size());
    __areas_.reserve    (__rhs.__areas_.size());

//  These can not throw
    __b_         = __rhs.__b_;
    __densities_ = __rhs.__densities_;
    __areas_     =  __rhs.__areas_;
    return *this;
}

template<class _RealType>
void
piecewise_constant_distribution<_RealType>::param_type::__init()
{
    // __densities_ contains non-normalized areas
    result_type __total_area = _VSTD::accumulate(__densities_.begin(),
                                                __densities_.end(),
                                                result_type());
    for (size_t __i = 0; __i < __densities_.size(); ++__i)
        __densities_[__i] /= __total_area;
    // __densities_ contains normalized areas
    __areas_.assign(__densities_.size(), result_type());
    _VSTD::partial_sum(__densities_.begin(), __densities_.end() - 1,
                                                          __areas_.begin() + 1);
    // __areas_ contains partial sums of normalized areas: [0, __densities_ - 1]
    __densities_.back() = 1 - __areas_.back();  // correct round off error
    for (size_t __i = 0; __i < __densities_.size(); ++__i)
        __densities_[__i] /= (__b_[__i+1] - __b_[__i]);
    // __densities_ now contains __densities_
}

template<class _RealType>
piecewise_constant_distribution<_RealType>::param_type::param_type()
    : __b_(2),
      __densities_(1, 1.0),
      __areas_(1, 0.0)
{
    __b_[1] = 1;
}

template<class _RealType>
template<class _InputIteratorB, class _InputIteratorW>
piecewise_constant_distribution<_RealType>::param_type::param_type(
        _InputIteratorB __fB, _InputIteratorB __lB, _InputIteratorW __fW)
    : __b_(__fB, __lB)
{
    if (__b_.size() < 2)
    {
        __b_.resize(2);
        __b_[0] = 0;
        __b_[1] = 1;
        __densities_.assign(1, 1.0);
        __areas_.assign(1, 0.0);
    }
    else
    {
        __densities_.reserve(__b_.size() - 1);
        for (size_t __i = 0; __i < __b_.size() - 1; ++__i, ++__fW)
            __densities_.push_back(*__fW);
        __init();
    }
}

#ifndef _LIBCPP_CXX03_LANG

template<class _RealType>
template<class _UnaryOperation>
piecewise_constant_distribution<_RealType>::param_type::param_type(
        initializer_list<result_type> __bl, _UnaryOperation __fw)
    : __b_(__bl.begin(), __bl.end())
{
    if (__b_.size() < 2)
    {
        __b_.resize(2);
        __b_[0] = 0;
        __b_[1] = 1;
        __densities_.assign(1, 1.0);
        __areas_.assign(1, 0.0);
    }
    else
    {
        __densities_.reserve(__b_.size() - 1);
        for (size_t __i = 0; __i < __b_.size() - 1; ++__i)
            __densities_.push_back(__fw((__b_[__i+1] + __b_[__i])*.5));
        __init();
    }
}

#endif  // _LIBCPP_CXX03_LANG

template<class _RealType>
template<class _UnaryOperation>
piecewise_constant_distribution<_RealType>::param_type::param_type(
        size_t __nw, result_type __xmin, result_type __xmax, _UnaryOperation __fw)
    : __b_(__nw == 0 ? 2 : __nw + 1)
{
    size_t __n = __b_.size() - 1;
    result_type __d = (__xmax - __xmin) / __n;
    __densities_.reserve(__n);
    for (size_t __i = 0; __i < __n; ++__i)
    {
        __b_[__i] = __xmin + __i * __d;
        __densities_.push_back(__fw(__b_[__i] + __d*.5));
    }
    __b_[__n] = __xmax;
    __init();
}

template<class _RealType>
template<class _URNG>
_RealType
piecewise_constant_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
{
    typedef uniform_real_distribution<result_type> _Gen;
    result_type __u = _Gen()(__g);
    ptrdiff_t __k = _VSTD::upper_bound(__p.__areas_.begin(), __p.__areas_.end(),
                                      __u) - __p.__areas_.begin() - 1;
    return (__u - __p.__areas_[__k]) / __p.__densities_[__k] + __p.__b_[__k];
}

//template <class _CharT, class _Traits, class _RT>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const piecewise_constant_distribution<_RT>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    size_t __n = __x.__p_.__b_.size();
//    __os << __n;
//    for (size_t __i = 0; __i < __n; ++__i)
//        __os << __sp << __x.__p_.__b_[__i];
//    __n = __x.__p_.__densities_.size();
//    __os << __sp << __n;
//    for (size_t __i = 0; __i < __n; ++__i)
//        __os << __sp << __x.__p_.__densities_[__i];
//    __n = __x.__p_.__areas_.size();
//    __os << __sp << __n;
//    for (size_t __i = 0; __i < __n; ++__i)
//        __os << __sp << __x.__p_.__areas_[__i];
//    return __os;
//}

//template <class _CharT, class _Traits, class _RT>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           piecewise_constant_distribution<_RT>& __x)
//{
//    typedef piecewise_constant_distribution<_RT> _Eng;
//    typedef typename _Eng::result_type result_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    size_t __n;
//    __is >> __n;
//    vector<result_type> __b(__n);
//    for (size_t __i = 0; __i < __n; ++__i)
//        __is >> __b[__i];
//    __is >> __n;
//    vector<result_type> __densities(__n);
//    for (size_t __i = 0; __i < __n; ++__i)
//        __is >> __densities[__i];
//    __is >> __n;
//    vector<result_type> __areas(__n);
//    for (size_t __i = 0; __i < __n; ++__i)
//        __is >> __areas[__i];
//    if (!__is.fail())
//    {
//        swap(__x.__p_.__b_, __b);
//        swap(__x.__p_.__densities_, __densities);
//        swap(__x.__p_.__areas_, __areas);
//    }
//    return __is;
//}

// piecewise_linear_distribution

template<class _RealType = double>
class _LIBCPP_TEMPLATE_VIS piecewise_linear_distribution
{
public:
    // types
    typedef _RealType result_type;

    class _LIBCPP_TEMPLATE_VIS param_type
    {
        vector<result_type> __b_;
        vector<result_type> __densities_;
        vector<result_type> __areas_;
    public:
        typedef piecewise_linear_distribution distribution_type;

        param_type();
        template<class _InputIteratorB, class _InputIteratorW>
            param_type(_InputIteratorB __fB, _InputIteratorB __lB,
                       _InputIteratorW __fW);
#ifndef _LIBCPP_CXX03_LANG
        template<class _UnaryOperation>
            param_type(initializer_list<result_type> __bl, _UnaryOperation __fw);
#endif  // _LIBCPP_CXX03_LANG
        template<class _UnaryOperation>
            param_type(size_t __nw, result_type __xmin, result_type __xmax,
                       _UnaryOperation __fw);
        param_type & operator=(const param_type& __rhs);

        _LIBCPP_INLINE_VISIBILITY
        vector<result_type> intervals() const {return __b_;}
        _LIBCPP_INLINE_VISIBILITY
        vector<result_type> densities() const {return __densities_;}

        friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__densities_ == __y.__densities_ && __x.__b_ == __y.__b_;}
        friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}

    private:
        void __init();

        friend class piecewise_linear_distribution;

        template <class _CharT, class _Traits, class _RT>
        friend
        basic_ostream<_CharT, _Traits>&
        operator<<(basic_ostream<_CharT, _Traits>& __os,
                   const piecewise_linear_distribution<_RT>& __x);

        template <class _CharT, class _Traits, class _RT>
        friend
        basic_istream<_CharT, _Traits>&
        operator>>(basic_istream<_CharT, _Traits>& __is,
                   piecewise_linear_distribution<_RT>& __x);
    };

private:
    param_type __p_;

public:
    // constructor and reset functions
    _LIBCPP_INLINE_VISIBILITY
    piecewise_linear_distribution() {}
    template<class _InputIteratorB, class _InputIteratorW>
        _LIBCPP_INLINE_VISIBILITY
        piecewise_linear_distribution(_InputIteratorB __fB,
                                      _InputIteratorB __lB,
                                      _InputIteratorW __fW)
        : __p_(__fB, __lB, __fW) {}

#ifndef _LIBCPP_CXX03_LANG
    template<class _UnaryOperation>
        _LIBCPP_INLINE_VISIBILITY
        piecewise_linear_distribution(initializer_list<result_type> __bl,
                                      _UnaryOperation __fw)
        : __p_(__bl, __fw) {}
#endif  // _LIBCPP_CXX03_LANG

    template<class _UnaryOperation>
        _LIBCPP_INLINE_VISIBILITY
        piecewise_linear_distribution(size_t __nw, result_type __xmin,
                                      result_type __xmax, _UnaryOperation __fw)
        : __p_(__nw, __xmin, __xmax, __fw) {}

    _LIBCPP_INLINE_VISIBILITY
    explicit piecewise_linear_distribution(const param_type& __p)
        : __p_(__p) {}

    _LIBCPP_INLINE_VISIBILITY
    void reset() {}

    // generating functions
    template<class _URNG>
        _LIBCPP_INLINE_VISIBILITY
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
    template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);

    // property functions
    _LIBCPP_INLINE_VISIBILITY
    vector<result_type> intervals() const {return __p_.intervals();}
    _LIBCPP_INLINE_VISIBILITY
    vector<result_type> densities() const {return __p_.densities();}

    _LIBCPP_INLINE_VISIBILITY
    param_type param() const {return __p_;}
    _LIBCPP_INLINE_VISIBILITY
    void param(const param_type& __p) {__p_ = __p;}

    _LIBCPP_INLINE_VISIBILITY
    result_type min() const {return __p_.__b_.front();}
    _LIBCPP_INLINE_VISIBILITY
    result_type max() const {return __p_.__b_.back();}

    friend _LIBCPP_INLINE_VISIBILITY
        bool operator==(const piecewise_linear_distribution& __x,
                        const piecewise_linear_distribution& __y)
        {return __x.__p_ == __y.__p_;}
    friend _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const piecewise_linear_distribution& __x,
                        const piecewise_linear_distribution& __y)
        {return !(__x == __y);}

    template <class _CharT, class _Traits, class _RT>
    friend
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
               const piecewise_linear_distribution<_RT>& __x);

    template <class _CharT, class _Traits, class _RT>
    friend
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __is,
               piecewise_linear_distribution<_RT>& __x);
};

template<class _RealType>
typename piecewise_linear_distribution<_RealType>::param_type &
piecewise_linear_distribution<_RealType>::param_type::operator=
                                                       (const param_type& __rhs)
{
//  These can throw
    __b_.reserve        (__rhs.__b_.size ());
    __densities_.reserve(__rhs.__densities_.size());
    __areas_.reserve    (__rhs.__areas_.size());

//  These can not throw
    __b_         = __rhs.__b_;
    __densities_ = __rhs.__densities_;
    __areas_     =  __rhs.__areas_;
    return *this;
}


template<class _RealType>
void
piecewise_linear_distribution<_RealType>::param_type::__init()
{
    __areas_.assign(__densities_.size() - 1, result_type());
    result_type _Sp = 0;
    for (size_t __i = 0; __i < __areas_.size(); ++__i)
    {
        __areas_[__i] = (__densities_[__i+1] + __densities_[__i]) *
                        (__b_[__i+1] - __b_[__i]) * .5;
        _Sp += __areas_[__i];
    }
    for (size_t __i = __areas_.size(); __i > 1;)
    {
        --__i;
        __areas_[__i] = __areas_[__i-1] / _Sp;
    }
    __areas_[0] = 0;
    for (size_t __i = 1; __i < __areas_.size(); ++__i)
        __areas_[__i] += __areas_[__i-1];
    for (size_t __i = 0; __i < __densities_.size(); ++__i)
        __densities_[__i] /= _Sp;
}

template<class _RealType>
piecewise_linear_distribution<_RealType>::param_type::param_type()
    : __b_(2),
      __densities_(2, 1.0),
      __areas_(1, 0.0)
{
    __b_[1] = 1;
}

template<class _RealType>
template<class _InputIteratorB, class _InputIteratorW>
piecewise_linear_distribution<_RealType>::param_type::param_type(
        _InputIteratorB __fB, _InputIteratorB __lB, _InputIteratorW __fW)
    : __b_(__fB, __lB)
{
    if (__b_.size() < 2)
    {
        __b_.resize(2);
        __b_[0] = 0;
        __b_[1] = 1;
        __densities_.assign(2, 1.0);
        __areas_.assign(1, 0.0);
    }
    else
    {
        __densities_.reserve(__b_.size());
        for (size_t __i = 0; __i < __b_.size(); ++__i, ++__fW)
            __densities_.push_back(*__fW);
        __init();
    }
}

#ifndef _LIBCPP_CXX03_LANG

template<class _RealType>
template<class _UnaryOperation>
piecewise_linear_distribution<_RealType>::param_type::param_type(
        initializer_list<result_type> __bl, _UnaryOperation __fw)
    : __b_(__bl.begin(), __bl.end())
{
    if (__b_.size() < 2)
    {
        __b_.resize(2);
        __b_[0] = 0;
        __b_[1] = 1;
        __densities_.assign(2, 1.0);
        __areas_.assign(1, 0.0);
    }
    else
    {
        __densities_.reserve(__b_.size());
        for (size_t __i = 0; __i < __b_.size(); ++__i)
            __densities_.push_back(__fw(__b_[__i]));
        __init();
    }
}

#endif  // _LIBCPP_CXX03_LANG

template<class _RealType>
template<class _UnaryOperation>
piecewise_linear_distribution<_RealType>::param_type::param_type(
        size_t __nw, result_type __xmin, result_type __xmax, _UnaryOperation __fw)
    : __b_(__nw == 0 ? 2 : __nw + 1)
{
    size_t __n = __b_.size() - 1;
    result_type __d = (__xmax - __xmin) / __n;
    __densities_.reserve(__b_.size());
    for (size_t __i = 0; __i < __n; ++__i)
    {
        __b_[__i] = __xmin + __i * __d;
        __densities_.push_back(__fw(__b_[__i]));
    }
    __b_[__n] = __xmax;
    __densities_.push_back(__fw(__b_[__n]));
    __init();
}

template<class _RealType>
template<class _URNG>
_RealType
piecewise_linear_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
{
    typedef uniform_real_distribution<result_type> _Gen;
    result_type __u = _Gen()(__g);
    ptrdiff_t __k = _VSTD::upper_bound(__p.__areas_.begin(), __p.__areas_.end(),
                                      __u) - __p.__areas_.begin() - 1;
    __u -= __p.__areas_[__k];
    const result_type __dk = __p.__densities_[__k];
    const result_type __dk1 = __p.__densities_[__k+1];
    const result_type __deltad = __dk1 - __dk;
    const result_type __bk = __p.__b_[__k];
    if (__deltad == 0)
        return __u / __dk + __bk;
    const result_type __bk1 = __p.__b_[__k+1];
    const result_type __deltab = __bk1 - __bk;
    return (__bk * __dk1 - __bk1 * __dk +
        sqrt(__deltab * (__deltab * __dk * __dk + 2 * __deltad * __u))) /
        __deltad;
}

//template <class _CharT, class _Traits, class _RT>
//basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os,
//           const piecewise_linear_distribution<_RT>& __x)
//{
//    __save_flags<_CharT, _Traits> __lx(__os);
//    __os.flags(ios_base::dec | ios_base::left | ios_base::fixed |
//               ios_base::scientific);
//    _CharT __sp = __os.widen(' ');
//    __os.fill(__sp);
//    size_t __n = __x.__p_.__b_.size();
//    __os << __n;
//    for (size_t __i = 0; __i < __n; ++__i)
//        __os << __sp << __x.__p_.__b_[__i];
//    __n = __x.__p_.__densities_.size();
//    __os << __sp << __n;
//    for (size_t __i = 0; __i < __n; ++__i)
//        __os << __sp << __x.__p_.__densities_[__i];
//    __n = __x.__p_.__areas_.size();
//    __os << __sp << __n;
//    for (size_t __i = 0; __i < __n; ++__i)
//        __os << __sp << __x.__p_.__areas_[__i];
//    return __os;
//}

//template <class _CharT, class _Traits, class _RT>
//basic_istream<_CharT, _Traits>&
//operator>>(basic_istream<_CharT, _Traits>& __is,
//           piecewise_linear_distribution<_RT>& __x)
//{
//    typedef piecewise_linear_distribution<_RT> _Eng;
//    typedef typename _Eng::result_type result_type;
//    __save_flags<_CharT, _Traits> __lx(__is);
//    __is.flags(ios_base::dec | ios_base::skipws);
//    size_t __n;
//    __is >> __n;
//    vector<result_type> __b(__n);
//    for (size_t __i = 0; __i < __n; ++__i)
//        __is >> __b[__i];
//    __is >> __n;
//    vector<result_type> __densities(__n);
//    for (size_t __i = 0; __i < __n; ++__i)
//        __is >> __densities[__i];
//    __is >> __n;
//    vector<result_type> __areas(__n);
//    for (size_t __i = 0; __i < __n; ++__i)
//        __is >> __areas[__i];
//    if (!__is.fail())
//    {
//        swap(__x.__p_.__b_, __b);
//        swap(__x.__p_.__densities_, __densities);
//        swap(__x.__p_.__areas_, __areas);
//    }
//    return __is;
//}

_LIBCPP_END_NAMESPACE_STD

_LIBCPP_POP_MACROS

#endif  // _LIBCPP_RANDOM
