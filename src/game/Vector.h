/*
 * Copyright (c) 2014-2015, Julien Bernard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifndef GAME_VECTOR_H
#define GAME_VECTOR_H

#include <cmath>

namespace game {

  /**
   * @brief A vector with two float components
   *
   * @ingroup base
   */
  struct Vector2f {
    float x;
    float y;
  };

  /**
   * @brief Test vectors' equality
   *
   * @ingroup base
   */
  inline
  bool operator==(const Vector2f& lhs, const Vector2f& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  /**
   * @brief Test vectors' inequality
   *
   * @ingroup base
   */
  inline
  bool operator!=(const Vector2f& lhs, const Vector2f& rhs) {
    return lhs.x != rhs.x || lhs.y != rhs.y;
  }

  /**
   * @brief Compute vector opposite
   *
   * @ingroup base
   */
  inline
  Vector2f operator-(const Vector2f& v) {
    return { - v.x, - v.y };
  }

  /**
   * @brief Compute the addition of two vectors
   *
   * @ingroup base
   */
  inline
  Vector2f operator+(const Vector2f& lhs, const Vector2f& rhs) {
    return { lhs.x + rhs.x, lhs.y + rhs.y };
  }

  /**
   * @brief Compute the addition of two vectors and assign to the first
   *
   * @ingroup base
   */
  inline
  Vector2f& operator+=(Vector2f& lhs, const Vector2f& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
  }

  /**
   * @brief Compute the substraction of two vectors
   *
   * @ingroup base
   */
  inline
  Vector2f operator-(const Vector2f& lhs, const Vector2f& rhs) {
    return { lhs.x - rhs.x, lhs.y - rhs.y };
  }

  /**
   * @brief Compute the substraction of two vectors and assign to the first
   *
   * @ingroup base
   */
  inline
  Vector2f& operator-=(Vector2f& lhs, const Vector2f& rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
  }

  /**
   * @brief Compute the scalar left multiplication of a vector
   *
   * @ingroup base
   */
  inline
  Vector2f operator*(float lhs, const Vector2f& rhs) {
    return { lhs * rhs.x, lhs * rhs.y };
  }

  /**
   * @brief Compute the scalar right multiplication of a vector
   *
   * @ingroup base
   */
  inline
  Vector2f operator*(const Vector2f& lhs, float rhs) {
    return { lhs.x * rhs, lhs.y * rhs };
  }

  /**
   * @brief Compute the scalar multiplication of a vector and assign to the vector
   *
   * @ingroup base
   */
  inline
  Vector2f& operator*=(Vector2f& lhs, float rhs) {
    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;
  }

  /**
   * @brief Compute the scalar division of a vector
   *
   * @ingroup base
   */
  inline
  Vector2f operator/(const Vector2f& lhs, float rhs) {
    return { lhs.x / rhs, lhs.y / rhs };
  }

  /**
   * @brief Compute the scalar division of a vector and assign to the vector
   *
   * @ingroup base
   */
  inline
  Vector2f& operator/=(Vector2f& lhs, float rhs) {
    lhs.x /= rhs;
    lhs.y /= rhs;
    return lhs;
  }

  /**
   * @brief Compute the dot product of two vectors
   *
   * @ingroup base
   */
  inline
  float dotProduct(const Vector2f& lhs, const Vector2f& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }

  /**
   * @brief Compute the manhattan length of a vector
   *
   * @ingroup base
   */
  inline
  float manhattanLength(const Vector2f& v) {
    return std::abs(v.x) + std::abs(v.y);
  }

  /**
   * @brief Compute the euclidean length of a vector
   *
   * @ingroup base
   */
  inline
  float euclideanLength(const Vector2f& v) {
    return std::hypot(v.x, v.y);
  }

  /**
   * @brief Compute the chebyshev length of a vector
   *
   * @ingroup base
   */
  inline
  float chebyshevLength(const Vector2f& v) {
    return std::fmax(std::abs(v.x), std::abs(v.y));
  }

  /**
   * @brief Compute the manhattan distance of two vectors
   *
   * @ingroup base
   */
  inline
  float manhattanDistance(const Vector2f& lhs, const Vector2f& rhs) {
    return manhattanLength(lhs - rhs);
  }

  /**
   * @brief Compute the euclidean distance of two vectors
   *
   * @ingroup base
   */
  inline
  float euclideanDistance(const Vector2f& lhs, const Vector2f& rhs) {
    return euclideanLength(lhs - rhs);
  }

  /**
   * @brief Compute the chebyshev distance of two vectors
   *
   * @ingroup base
   */
  inline
  float chebyshevDistance(const Vector2f& lhs, const Vector2f& rhs) {
    return chebyshevLength(lhs - rhs);
  }

  /**
   * @brief Compute the dot product of two vectors
   *
   * @ingroup base
   */
  inline
  float vectorAngle(const Vector2f& v) {
    return std::atan2(v.y, v.x);
  }

  /**
   * @brief Compute the unit vector in the same direction as a vector
   *
   * @ingroup base
   */
  inline
  Vector2f unit(const Vector2f& v) {
    float n = euclideanLength(v);
    return { v.x / n, v.y / n };
  }

  /**
   * @brief Compute the unit vector with an angle
   *
   * @ingroup base
   */
  inline
  Vector2f unit(float angle) {
    return { std::cos(angle), std::sin(angle) };
  }

}


#endif // GAME_VECTOR_H
