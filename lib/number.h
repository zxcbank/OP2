#pragma once
#include <cinttypes>
#include <iostream>


struct int2023_t {
  uint8_t a[253] = {0};
  static const int kLength = 253;
  static const int kBit8 = 0xff;
  static const int kChange = 8;
};

static_assert(sizeof(int2023_t) <= 253, "Size of int2023_t must be no higher than 253 bytes");

int2023_t from_int(int32_t i);

int2023_t from_string(const char* buff);

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator++(int2023_t& lhs);

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator-(const int2023_t hs);

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs);

bool operator>(const int2023_t& lhs, const int2023_t& rhs);

bool operator<(const int2023_t& lhs, const int2023_t& rhs);

bool operator>=(const int2023_t& lhs, const int2023_t& rhs);

void shift_left(int2023_t& hs);

bool operator==(const int2023_t& lhs, const int2023_t& rhs);

bool operator!=(const int2023_t& lhs, const int2023_t& rhs);

std::ostream& operator<<(std::ostream& stream, const int2023_t& value);