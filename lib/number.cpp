#include <cstring>
#include "number.h"

int2023_t from_int(int32_t num) {
  int2023_t res;
  bool is_negative = false;

  if (num < 0){
    num = -num;
    is_negative = true;
  }

  for (int i = int2023_t::kLength-1; i > int2023_t::kLength-5; i--){
    res.a[i] =  num & int2023_t::kBit8;
    num >>= int2023_t::kChange;
  }
  if (is_negative)
    res = -res;

  return res;
}

int2023_t from_string(const char* buff) {
  int2023_t res;
  bool is_negative = (buff[0] == '-');
  int len = strlen(buff);
  
  for (int i = is_negative; i < len; i++){
    res = res * from_int(10);
    res = res + from_int(buff[i] - '0');
  }

  if (is_negative)
    return -res;
  return res;
}

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs) {
  int2023_t res;
  int buff = 0;
  for (int i = int2023_t::kLength-1; i >= 0; i--){
    buff = (buff + lhs.a[i] + rhs.a[i]);
    res.a[i] = buff & int2023_t::kBit8;
    buff >>= int2023_t::kChange;
  }
  return res;
}

int2023_t operator++(int2023_t& lhs){
  int r = 1;
  for (int i = int2023_t::kLength-1; i >= 0; i--){
    lhs.a[i] += r;
    if (int(lhs.a[i]) == 0){
      r = 1;
    }
    else {
      return lhs;
    }
    if (i == 0 && r == 1)
      exit(EXIT_FAILURE);
  }
  return lhs;
}

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs) {
  return lhs + (-rhs);
}

int2023_t operator-(const int2023_t hs){
  int2023_t res = hs;
  int2023_t null_2023 = from_int(0);
  if (hs == null_2023)
    return null_2023;

  for (int i = 0; i < int2023_t::kLength; i++){
    res.a[i] = ~res.a[i];
  }
  return (++res);
}

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs) {
  int2023_t res, a = lhs, b = rhs;

  if (a < from_int(0))
    a = -a;
  if (b < from_int(0))
    b = -b;

  int buff[253] = {0};
  int add = 0;

  for (int i = 252; i >= 0; i--) {
    for (int j = 252; j >= 0; j--) {
      if (i + j < 252){
        break;
      }
      add += (a.a[i] * b.a[j]);
      buff[i + j - 252] += add & int2023_t::kBit8;
      add >>= int2023_t::kChange;
    }
  }
  add = 0;
  for (int i = int2023_t::kLength - 1; i >= 0; i--){
    add += buff[i];
    res.a[i] = add & int2023_t::kBit8;
    add >>= int2023_t::kChange;
  }

  if (((lhs.a[0] >> 6) & 1)^((rhs.a[0] >> 6) & 1))
    return -res;
  return res;
}

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs) {
  int2023_t res, a = lhs, b = rhs, R;
  if (lhs == from_int(0) && !(rhs == from_int(0)))
    return from_int(0);

  if (rhs == from_int(0))
    exit(EXIT_FAILURE);


  if (rhs < from_int(0))
    b = -b;
  if (lhs < from_int(0))
    a = -a;

  for (int i = 0; i < int2023_t::kLength; i++){
    for (int j = 6 + (i != 0); j >= 0; j--){
      shift_left(res);
      shift_left(R);
      R.a[252] |= (a.a[i] >> j) &1;

      if (R >= b){
        R = R - b;
        res.a[252] = res.a[252] | 1;
      }
    }
  }
  if ((lhs < from_int(0))^((rhs < from_int(0))))
    return -res;
  return res;
}

bool operator==(const int2023_t& lhs, const int2023_t& rhs) {
  for (int i = 0; i < int2023_t::kLength; i++)
    if (lhs.a[i] != rhs.a[i])
      return false;
  return true;
}

bool operator!=(const int2023_t& lhs, const int2023_t& rhs) {
  return !(lhs == rhs);
}
bool operator<(const int2023_t& lhs, const int2023_t& rhs){
  if (!(lhs > rhs) && lhs != rhs)
    return true;

  return false;
}
bool operator>(const int2023_t& lhs, const int2023_t& rhs){
  int2023_t a = lhs, b = rhs;
  if (((lhs.a[0] >> 6) & 1) && !((rhs.a[0] >> 6) & 1))
    return false;
  if (!((lhs.a[0] >> 6) & 1) && ((rhs.a[0] >> 6) & 1))
    return true;

  a.a[0] &= 0x7f;
  b.a[0] &= 0x7f;
  int i = 0;
  while (i < int2023_t::kLength){
    if (a.a[i] > b.a[i])
      return true;
    if (b.a[i] > a.a[i])
      return false;
    i++;
  }

  return false;
}

void shift_left(int2023_t& hs){
  bool buff = false;

  for (int i = int2023_t::kLength-1; i >= 0 ; i--){
    bool buff2 = hs.a[i] >> 7;
    hs.a[i] = (hs.a[i] << 1) + buff;
    buff = buff2;
  }
}

bool operator>= (const int2023_t& lhs, const int2023_t& rhs){
  return lhs > rhs || lhs == rhs;
}

std::ostream& operator<<(std::ostream& stream, const int2023_t& value) {
  int2023_t copy_value = value;
  if (value < from_int(0)){
    stream << "-";
    copy_value = -value;
  }
  int i = 0;
  while (int(copy_value.a[i]) == 0 && i < int2023_t::kLength){
    i++;
  }
  if (i >= int2023_t::kLength){
    stream << 0;
    return stream;
  }

  for (; i < int2023_t::kLength; i++){
    stream << std::hex << int(copy_value.a[i] >> 4);
    stream << std::hex << int(copy_value.a[i] & 0xF);
  }

  return stream;
}