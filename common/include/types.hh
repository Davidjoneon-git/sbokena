// common types & aliases.

#pragma once

#include <cmath>
#include <concepts>
#include <cstdint>

namespace sbokena::types {

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using usize = std::size_t;

using f32 = std::float_t;
using f64 = std::double_t;

// a 2D cardinal direction.
enum struct Direction : u8 {
  Up = 0b0001,
  Down = 0b0010,
  Left = 0b0100,
  Right = 0b1000,
};

// a set of 2D directions.
class Directions {
public:
  // construct a directions set from a direction.
  constexpr Directions(const Direction &) noexcept;
  // construct a directions set from a raw flag value.
  // this zeroes the upper bits of the value.
  constexpr Directions(u8 flags) noexcept;

  // does this set contain some cardinal direction?
  constexpr bool contains(const Direction &) const noexcept;

  // does this set contain all of these directions?
  constexpr bool contains_all(const Directions &) const noexcept;

  // does this set contain any of these directions?
  constexpr bool contains_any(const Directions &) const noexcept;

  // is this set empty?
  constexpr bool empty() const noexcept;

  // return the raw flag value.
  constexpr u8 flags() const noexcept;

private:
  u8 flags_ = 0b0000;
};

constexpr Directions operator|(const Direction &, const Direction &) noexcept;
constexpr Directions operator|(const Directions &, const Direction &) noexcept;
constexpr Directions operator|(const Directions &, const Directions &) noexcept;
constexpr Directions &operator|=(Directions &, const Direction &) noexcept;
constexpr Directions &operator|=(Directions &, const Directions &) noexcept;

// a position in a 2D grid.
template <std::integral T>
struct Position {
  T x;
  T y;

  // this position with x and y swapped.
  [[nodiscard("transposed() does not modify `this`")]]
  constexpr Position transposed() const noexcept;
};

template <std::integral T>
constexpr Position<T> &operator+=(Position<T> &, const Position<T> &) noexcept;

template <std::integral T>
constexpr Position<T> &operator-=(Position<T> &, const Position<T> &) noexcept;

template <std::integral T>
[[nodiscard("operator+() does not modify `this`")]]
constexpr Position<T> operator+(const Position<T> &,
                                const Position<T> &) noexcept;

template <std::integral T>
[[nodiscard("operator-() does not modify `this`")]]
constexpr Position<T> operator-(const Position<T> &,
                                const Position<T> &) noexcept;

template <std::signed_integral T>
[[nodiscard("operator-() does not modify `this`")]]
constexpr Position<T> operator-(const Position<T> &) noexcept;

} // namespace sbokena::types
