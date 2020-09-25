/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

#define NUM_AXIS 4
#define ABCE 4
#define XYZE 4
#define ABC  3
#define XYZ  3

#define _AXIS(A) (A##_AXIS)

#define _XMIN_ 100
#define _YMIN_ 200
#define _ZMIN_ 300
#define _XMAX_ 101
#define _YMAX_ 201
#define _ZMAX_ 301

#define _FORCE_INLINE_ __attribute__((__always_inline__)) __inline__
#define  FORCE_INLINE  __attribute__((always_inline)) inline
#define _UNUSED      __attribute__((unused))
#define _O0          __attribute__((optimize("O0")))
#define _Os          __attribute__((optimize("Os")))
#define _O1          __attribute__((optimize("O1")))
#define _O2          __attribute__((optimize("O2")))
#define _O3          __attribute__((optimize("O3")))

#ifndef UNUSED
  #if defined(ARDUINO_ARCH_STM32) && !defined(STM32GENERIC)
    #define UNUSED(X) (void)X
  #else
    #define UNUSED(x) ((void)(x))
  #endif
#endif

// Clock speed factors
#if !defined(CYCLES_PER_MICROSECOND) && !defined(__STM32F1__)
  #define CYCLES_PER_MICROSECOND (F_CPU / 1000000UL) // 16 or 20 on AVR
#endif

// Nanoseconds per cycle
#define NANOSECONDS_PER_CYCLE (1000000000.0 / F_CPU)

// Macros to make a string from a macro
#define STRINGIFY_(M) #M
#define STRINGIFY(M) STRINGIFY_(M)

#define A(CODE) " " CODE "\n\t"
#define L(CODE) CODE ":\n\t"

// Macros for bit masks
#undef _BV
#define _BV(n) (1<<(n))
#define TEST(n,b) (!!((n)&_BV(b)))
#define SET_BIT_TO(N,B,TF) do{ if (TF) SBI(N,B); else CBI(N,B); }while(0)

#ifndef SBI
  #define SBI(A,B) (A |= (1 << (B)))
#endif

#ifndef CBI
  #define CBI(A,B) (A &= ~(1 << (B)))
#endif

#define _BV32(b) (1UL << (b))
#define TEST32(n,b) !!((n)&_BV32(b))
#define SBI32(n,b) (n |= _BV32(b))
#define CBI32(n,b) (n &= ~_BV32(b))

#define cu(x)      ((x)*(x)*(x))
#define RADIANS(d) ((d)*float(M_PI)/180.0f)
#define DEGREES(r) ((r)*180.0f/float(M_PI))
#define HYPOT2(x,y) (sq(x)+sq(y))

#define CIRCLE_AREA(R) (float(M_PI) * sq(float(R)))
#define CIRCLE_CIRC(R) (2 * float(M_PI) * float(R))

#define SIGN(a) ((a>0)-(a<0))
#define IS_POWER_OF_2(x) ((x) && !((x) & ((x) - 1)))

// Macros to constrain values
#ifdef __cplusplus

  // C++11 solution that is standards compliant.
  template <class V, class N> static inline constexpr void NOLESS(V& v, const N n) {
    if (n > v) v = n;
  }
  template <class V, class N> static inline constexpr void NOMORE(V& v, const N n) {
    if (n < v) v = n;
  }
  template <class V, class N1, class N2> static inline constexpr void LIMIT(V& v, const N1 n1, const N2 n2) {
    if (n1 > v) v = n1;
    else if (n2 < v) v = n2;
  }

#else

  // Using GCC extensions, but Travis GCC version does not like it and gives
  //  "error: statement-expressions are not allowed outside functions nor in template-argument lists"
  #define NOLESS(v, n) \
    do{ \
      __typeof__(n) _n = (n); \
      if (_n > v) v = _n; \
    }while(0)

  #define NOMORE(v, n) \
    do{ \
      __typeof__(n) _n = (n); \
      if (_n < v) v = _n; \
    }while(0)

  #define LIMIT(v, n1, n2) \
    do{ \
      __typeof__(n1) _n1 = (n1); \
      __typeof__(n2) _n2 = (n2); \
      if (_n1 > v) v = _n1; \
      else if (_n2 < v) v = _n2; \
    }while(0)

#endif

// Macros to chain up to 12 conditions
#define _DO_1(W,C,A)       (_##W##_1(A))
#define _DO_2(W,C,A,B)     (_##W##_1(A) C _##W##_1(B))
#define _DO_3(W,C,A,V...)  (_##W##_1(A) C _DO_2(W,C,V))
#define _DO_4(W,C,A,V...)  (_##W##_1(A) C _DO_3(W,C,V))
#define _DO_5(W,C,A,V...)  (_##W##_1(A) C _DO_4(W,C,V))
#define _DO_6(W,C,A,V...)  (_##W##_1(A) C _DO_5(W,C,V))
#define _DO_7(W,C,A,V...)  (_##W##_1(A) C _DO_6(W,C,V))
#define _DO_8(W,C,A,V...)  (_##W##_1(A) C _DO_7(W,C,V))
#define _DO_9(W,C,A,V...)  (_##W##_1(A) C _DO_8(W,C,V))
#define _DO_10(W,C,A,V...) (_##W##_1(A) C _DO_9(W,C,V))
#define _DO_11(W,C,A,V...) (_##W##_1(A) C _DO_10(W,C,V))
#define _DO_12(W,C,A,V...) (_##W##_1(A) C _DO_11(W,C,V))
#define __DO_N(W,C,N,V...) _DO_##N(W,C,V)
#define _DO_N(W,C,N,V...)  __DO_N(W,C,N,V)
#define DO(W,C,V...)       _DO_N(W,C,NUM_ARGS(V),V)

// Macros to support option testing
#define _CAT(a,V...) a##V
#define SWITCH_ENABLED_false 0
#define SWITCH_ENABLED_true  1
#define SWITCH_ENABLED_0     0
#define SWITCH_ENABLED_1     1
#define SWITCH_ENABLED_0x0   0
#define SWITCH_ENABLED_0x1   1
#define SWITCH_ENABLED_      1
#define _ENA_1(O)           _CAT(SWITCH_ENABLED_, O)
#define _DIS_1(O)           !_ENA_1(O)
#define ENABLED(V...)       DO(ENA,&&,V)
#define DISABLED(V...)      DO(DIS,&&,V)

#define ANY(V...)          !DISABLED(V)
#define NONE(V...)          DISABLED(V)
#define ALL(V...)           ENABLED(V)
#define BOTH(V1,V2)         ALL(V1,V2)
#define EITHER(V1,V2)       ANY(V1,V2)

// Macros to support pins/buttons exist testing
#define _PINEX_1(PN)        (defined(PN##_PIN) && PN##_PIN >= 0)
#define PIN_EXISTS(V...)    DO(PINEX,&&,V)
#define ANY_PIN(V...)       DO(PINEX,||,V)

#define _BTNEX_1(BN)        (defined(BTN_##BN) && BTN_##BN >= 0)
#define BUTTON_EXISTS(V...) DO(BTNEX,&&,V)
#define ANY_BUTTON(V...)    DO(BTNEX,||,V)

#define WITHIN(N,L,H)       ((N) >= (L) && (N) <= (H))
#define NUMERIC(a)          WITHIN(a, '0', '9')
#define DECIMAL(a)          (NUMERIC(a) || a == '.')
#define NUMERIC_SIGNED(a)   (NUMERIC(a) || (a) == '-' || (a) == '+')
#define DECIMAL_SIGNED(a)   (DECIMAL(a) || (a) == '-' || (a) == '+')
#define COUNT(a)            (sizeof(a)/sizeof(*a))
#define ZERO(a)             memset(a,0,sizeof(a))
#define COPY(a,b) do{ \
    static_assert(sizeof(a[0]) == sizeof(b[0]), "COPY: '" STRINGIFY(a) "' and '" STRINGIFY(b) "' types (sizes) don't match!"); \
    memcpy(&a[0],&b[0],_MIN(sizeof(a),sizeof(b))); \
  }while(0)

// Macros for initializing arrays
#define ARRAY_16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,...) { A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P }
#define ARRAY_15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,...) { A,B,C,D,E,F,G,H,I,J,K,L,M,N,O }
#define ARRAY_14(A,B,C,D,E,F,G,H,I,J,K,L,M,N,...) { A,B,C,D,E,F,G,H,I,J,K,L,M,N }
#define ARRAY_13(A,B,C,D,E,F,G,H,I,J,K,L,M,...) { A,B,C,D,E,F,G,H,I,J,K,L,M }
#define ARRAY_12(A,B,C,D,E,F,G,H,I,J,K,L,...) { A,B,C,D,E,F,G,H,I,J,K,L }
#define ARRAY_11(A,B,C,D,E,F,G,H,I,J,K,...) { A,B,C,D,E,F,G,H,I,J,K }
#define ARRAY_10(A,B,C,D,E,F,G,H,I,J,...) { A,B,C,D,E,F,G,H,I,J }
#define ARRAY_9( A,B,C,D,E,F,G,H,I,...) { A,B,C,D,E,F,G,H,I }
#define ARRAY_8( A,B,C,D,E,F,G,H,...) { A,B,C,D,E,F,G,H }
#define ARRAY_7( A,B,C,D,E,F,G,...) { A,B,C,D,E,F,G }
#define ARRAY_6( A,B,C,D,E,F,...) { A,B,C,D,E,F }
#define ARRAY_5( A,B,C,D,E,...) { A,B,C,D,E }
#define ARRAY_4( A,B,C,D,...) { A,B,C,D }
#define ARRAY_3( A,B,C,...) { A,B,C }
#define ARRAY_2( A,B,...) { A,B }
#define ARRAY_1( A,...) { A }

#define _ARRAY_N(N,V...) ARRAY_##N(V)
#define ARRAY_N(N,V...) _ARRAY_N(N,V)

// Macros for adding
#define INC_0 1
#define INC_1 2
#define INC_2 3
#define INC_3 4
#define INC_4 5
#define INC_5 6
#define INC_6 7
#define INC_7 8
#define INC_8 9
#define INCREMENT_(n) INC_##n
#define INCREMENT(n) INCREMENT_(n)

// Macros for subtracting
#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC_4 3
#define DEC_5 4
#define DEC_6 5
#define DEC_7 6
#define DEC_8 7
#define DEC_9 8
#define DECREMENT_(n) DEC_##n
#define DECREMENT(n) DECREMENT_(n)

#define MMM_TO_MMS(MM_M) ((MM_M)/60.0f)
#define MMS_TO_MMM(MM_S) ((MM_S)*60.0f)

#define NOOP (void(0))

#define CEILING(x,y) (((x) + (y) - 1) / (y))

#undef ABS
#ifdef __cplusplus
  template <class T> static inline constexpr const T ABS(const T v) { return v >= 0 ? v : -v; }
#else
  #define ABS(a) ({__typeof__(a) _a = (a); _a >= 0 ? _a : -_a;})
#endif

#define UNEAR_ZERO(x) ((x) < 0.000001f)
#define NEAR_ZERO(x) WITHIN(x, -0.000001f, 0.000001f)
#define NEAR(x,y) NEAR_ZERO((x)-(y))

#define RECIPROCAL(x) (NEAR_ZERO(x) ? 0 : (1 / float(x)))
#define FIXFLOAT(f) (f + (f < 0 ? -0.00005f : 0.00005f))

//
// Maths macros that can be overridden by HAL
//
#define ATAN2(y, x) atan2f(y, x)
#define POW(x, y)   powf(x, y)
#define SQRT(x)     sqrtf(x)
#define RSQRT(x)    (1 / sqrtf(x))
#define CEIL(x)     ceilf(x)
#define FLOOR(x)    floorf(x)
#define LROUND(x)   lroundf(x)
#define FMOD(x, y)  fmodf(x, y)
#define HYPOT(x,y)  SQRT(HYPOT2(x,y))

#ifdef TARGET_LPC1768
  #define I2C_ADDRESS(A) ((A) << 1)
#else
  #define I2C_ADDRESS(A) A
#endif

// Use NUM_ARGS(__VA_ARGS__) to get the number of variadic arguments
#define _NUM_ARGS(_0,_24_,_23,_22,_21,_20,_19,_18,_17,_16,_15,_14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1,N,...) N
#define NUM_ARGS(V...) _NUM_ARGS(0,V,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)

#ifdef __cplusplus

  #ifndef _MINMAX_H_
  #define _MINMAX_H_

    extern "C++" {

      // C++11 solution that is standards compliant. Return type is deduced automatically
      template <class L, class R> static inline constexpr auto _MIN(const L lhs, const R rhs) -> decltype(lhs + rhs) {
        return lhs < rhs ? lhs : rhs;
      }
      template <class L, class R> static inline constexpr auto _MAX(const L lhs, const R rhs) -> decltype(lhs + rhs) {
        return lhs > rhs ? lhs : rhs;
      }
      template<class T, class ... Ts> static inline constexpr const T _MIN(T V, Ts... Vs) { return _MIN(V, _MIN(Vs...)); }
      template<class T, class ... Ts> static inline constexpr const T _MAX(T V, Ts... Vs) { return _MAX(V, _MAX(Vs...)); }

    }

  #endif

#else

  #define MIN_2(a,b)      ((a)<(b)?(a):(b))
  #define MIN_3(a,...)    MIN_2(a,MIN_2(__VA_ARGS__))
  #define MIN_4(a,...)    MIN_2(a,MIN_3(__VA_ARGS__))
  #define MIN_5(a,...)    MIN_2(a,MIN_4(__VA_ARGS__))
  #define MIN_6(a,...)    MIN_2(a,MIN_5(__VA_ARGS__))
  #define MIN_7(a,...)    MIN_2(a,MIN_6(__VA_ARGS__))
  #define MIN_8(a,...)    MIN_2(a,MIN_7(__VA_ARGS__))
  #define MIN_9(a,...)    MIN_2(a,MIN_8(__VA_ARGS__))
  #define MIN_10(a,...)   MIN_2(a,MIN_9(__VA_ARGS__))
  #define __MIN_N(N, ...) MIN_##N(__VA_ARGS__)
  #define _MIN_N(N, ...)  __MIN_N(N,__VA_ARGS__)
  #define _MIN(...)       _MIN_N(NUM_ARGS(__VA_ARGS__), __VA_ARGS__)

  #define MAX_2(a,b)      ((a)>(b)?(a):(b))
  #define MAX_3(a,...)    MAX_2(a,MAX_2(__VA_ARGS__))
  #define MAX_4(a,...)    MAX_2(a,MAX_3(__VA_ARGS__))
  #define MAX_5(a,...)    MAX_2(a,MAX_4(__VA_ARGS__))
  #define MAX_6(a,...)    MAX_2(a,MAX_5(__VA_ARGS__))
  #define MAX_7(a,...)    MAX_2(a,MAX_6(__VA_ARGS__))
  #define MAX_8(a,...)    MAX_2(a,MAX_7(__VA_ARGS__))
  #define MAX_9(a,...)    MAX_2(a,MAX_8(__VA_ARGS__))
  #define MAX_10(a,...)   MAX_2(a,MAX_9(__VA_ARGS__))
  #define __MAX_N(N, ...) MAX_##N(__VA_ARGS__)
  #define _MAX_N(N, ...)  __MAX_N(N,__VA_ARGS__)
  #define _MAX(...)       _MAX_N(NUM_ARGS(__VA_ARGS__), __VA_ARGS__)

#endif
