#include "perl_num_ip.h"

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<sstream>
#include<iostream>
#include<string>

using std::string;
/* #define INITDIFFPOS 10 表示2个ip出现不同的位置的变量的初始值，大于3就行 */
const int kInitDiffPos = 10;

/* 从低位到高位 */
void LowToHigh(const string& small, const int& diff_pos, string* perl) {
  int k = small.length() - 1;
  for (k = small.length() - 1; k > diff_pos; k--) {
    if ('9' == small[k]) {
      continue;
    }
    string node(small, 0, k);
    char small_node[100] = {0};
    char left = small[k]+1;
    sprintf(small_node, "[%c-9]", left);
    node += small_node;
    if (0 != small.length() - 1 - k) {
      char temp[100] = {0};
      sprintf(temp, "[0-9]{%d}", small.length() - 1 -k);
      node += temp;
    }
    node += "|";
    *perl += node;
  }
}

/* 从高位到低位 */
void HighToLow(const string& big, const int& diff_pos, string* perl) {
  int k = diff_pos + 1;
  for (k = diff_pos + 1; k < big.length(); k++) {
    if ('0' == big[k]) {
      continue;
    }
    string node(big, 0, k);
    char temp[100] = {0};
    char right = big[k] - 1;
    if (0 != big.length() - 1 - k) {
      sprintf(temp, "[0-%c][0-9]{%d}|", right, big.length() - 1 -k);
    } else {
      sprintf(temp, "[0-%c]|", right);
    }
    node += temp;
    *perl += node;
  }
}

/* 数字长度相等处理 */
string NumSameLength(const string& num_a, const string& num_b, string* perl) {
  if (0 == num_a.compare(num_b)) {
    return *perl;
  }
  string big = num_a;
  string small = num_b;
  if (0 > num_a.compare(num_b)) {  /* 如果后者大 */
    big = num_b;
    small = num_a;
  }
  /* 找不一样的最高位 */
  int diff_pos = 0;
  int i = 0;
  for (i = 0; i < num_a.length(); i++) {
    if (num_b[i] != num_a[i]) {
      diff_pos = i;
      break;
    }
  }
  LowToHigh(small, diff_pos, perl);
  if (small[diff_pos]+1 != big[diff_pos]) {
    string node(small, 0, diff_pos);
    char temp[100] = {0};
    char left = small[diff_pos] + 1;
    char right = big[diff_pos] - 1;
    if (0 != num_a.length() - 1 - diff_pos) {
      sprintf(temp, "[%c-%c][0-9]{%d}|", left, right,
              num_a.length() - 1 - diff_pos);
    } else {
      sprintf(temp, "[%c-%c]|", left, right);
    }
    node += temp;
    *perl += node;
  }
  /* 从高位到低位 */
  HighToLow(big, diff_pos, perl);
  return *perl;
}

/* 数字长度不相等处理 */
string NumNotSameLength(const string& small, const string& big,
                        string* perl) {
  LowToHigh(small, 0, perl);  /* 小的数从低位到最高位 */
  int len_small = small.length();
  int len_big = big.length();
  if ('9' != small[0]) {
    string node;
    char temp[100] = {0};
    char left = small[0] + 1;
    if (0 != len_small - 1) {
      sprintf(temp, "[%c-9][0-9]{%d}|", left, len_small - 1);
    } else {
      sprintf(temp, "[%c-9]|", left);
    }
    *perl += temp;
  }
  int k = len_small;
  for (k = len_small; k < len_big - 1; k++) {
    string node;
    char temp[100] = {0};
    if (0 != k) {
      sprintf(temp, "[1-9][0-9]{%d}|", k);
    } else {
      sprintf(temp, "[1-9]|");
    }
    *perl += temp;
  }
  if ('1' != big[0]) {  /* 大的数的最高位部分 */
    string node;
    char temp[100] = {0};
    if (0 != len_big-1) {
      sprintf(temp, "[1-%c][0-9]{%d}|", big[0] - 1, len_big-1);
    } else {
      sprintf(temp, "[1-%c]|", big[0] - 1);
    }
    *perl += temp;
  }
  HighToLow(big, 0, perl);  /* 大的数从高位到低位 */
  return *perl;
}

/* 从传入的2个切分后的ip中区分大和小的ip。返回2个ip首次不同的位置*/
int BigAndSmallIp(const string (&ip_a)[4], const string (&ip_b)[4],
                  string (*ip_big)[4], string (*ip_small)[4]) {
  int i = 0;
  int diff_pos = 10;
  for (i = 0; i < 4; i++) {  /* 比较，并找出首次不同的位置 */
    int k = 0;
    if (atoi(ip_a[i].c_str()) == atoi(ip_b[i].c_str())) {
      continue;
    } else if (atoi(ip_a[i].c_str()) > atoi(ip_b[i].c_str())) {
      for (k = 0; k < 4; k++) {
        (*ip_big)[k] = ip_a[k];
        (*ip_small)[k] = ip_b[k];
      }
      diff_pos = i;
      break;
    } else {
      for (k = 0; k < 4; k++) {
        (*ip_big)[k] = ip_b[k];
        (*ip_small)[k] = ip_a[k];
      }
      diff_pos = i;
      break;
    }
  }
  return diff_pos;
}

string GetPerlOpenOpen(const string& num_a, const string& num_b) {
  string big = num_a;
  string small = num_b;
  string perl;
  /* 如果长度一样 */
  if (num_a.length() == num_b.length()) {
    NumSameLength(num_a, num_b, &perl);
  } else {
    if (num_a.length() < num_b.length()) {
      big = num_b;
      small = num_a;
    }
    NumNotSameLength(small, big, &perl);
  }
  perl = perl.substr(0, perl.length() - 1);
  return perl;
}

string GetPerlOpenClose(const string& num_a, const string& num_b) {
  string big = num_a;
  string small = num_b;
  string perl;
  /* 如果长度一样 */
  if (num_a.length() == num_b.length()) {
    if (0 == num_a.compare(num_b)) {
      return perl;
    }
    if (0 <= num_a.compare(num_b)) {
      big = num_b;
      small = num_a;
    }
  }
  if (num_a.length() <= num_b.length()) {
    big = num_b;
    small = num_a;
  }
  perl = GetPerlOpenOpen(big, small);
  if (0 == perl.length()) {
    perl = big;
  } else {
    perl += "|";
    perl += big;
  }
  return perl;
}

string GetPerlCloseOpen(const string& num_a, const string& num_b) {
  string big = num_a;
  string small = num_b;
  string perl;
  /* 如果长度一样 */
  if (num_a.length() == num_b.length()) {
    if (0 == num_a.compare(num_b)) {
      return perl;
    }
    if (0 <= num_a.compare(num_b)) {
      big = num_b;
      small = num_a;
    }
  }
  if (num_a.length() <= num_b.length()) {
    big = num_b;
    small = num_a;
  }
  string perl_open_open = GetPerlOpenOpen(big, small);
  perl = small;
  if (0 != perl_open_open.length()) {
    perl += "|";
    perl += perl_open_open;
  }
  return perl;
}

string GetPerlCloseClose(const string& num_a, const string& num_b) {
  string big = num_a;
  string small = num_b;
  string perl;
  /* 如果长度一样 */
  if (num_a.length() == num_b.length()) {
    if (0 == num_a.compare(num_b)) {
      return num_a;
    }
    if (0 <= num_a.compare(num_b)) {
      big = num_b;
      small = num_a;
    }
  }
  if (num_a.length() <= num_b.length()) {
    big = num_b;
    small = num_a;
  }
  string perl_open_open = GetPerlOpenOpen(big, small);
  perl += small;
  perl += "|";

  if (0 != perl_open_open.length()) {
    perl += perl_open_open;
    perl += "|";
  }
  perl += big;
  return perl;
}

void GetSplitIp(const string ip, string (*split_ip)[4]) {
  int i = 0;
  int k = 0;
  for (i = 0; i < ip.length(); i++) {
    if ('.' == ip[i]) {
      k++;
      continue;
    }
    (*split_ip)[k] += ip[i];
  }
}



void GetPerlIp(const int& diff_pos, const string (&split_ip_small)[4],
               const string (&split_ip_big)[4], string* perl_ip) {
  string perl_0_255 = GetPerlCloseClose("0", "255");
  int i = 0;
  for (i = 3 ; i >= diff_pos; i--) {
    string perl;
    if (i == diff_pos) {
      perl = GetPerlOpenOpen(split_ip_small[diff_pos], split_ip_big[diff_pos]);
    } else {
      perl = GetPerlOpenClose(split_ip_small[i], "255");
    }
    if (0 != perl.length()) {
      string node;
      int k = 0;
      for (k = 0; k < i; k++) {
        node += split_ip_small[k] + ".";
      }
      node += "(" + perl + ")";
      for (k = 0; k < 3-i; k++) {
        node += ".(" + perl_0_255 + ")";
      }
      *perl_ip += node + "|";
    }
  }
  for (i = diff_pos + 1; i <= 3; i++) {
    string perl = GetPerlCloseOpen("0", split_ip_big[i]);
    if (0 != perl.length()) {
      string node;
      int k = 0;
      for (k = 0; k < i; k++) {
        node += split_ip_big[k] + ".";
      }
      node += "(" + perl + ")";
      for (k = 0; k < 3 - i; k++) {
        node +=".("+ perl_0_255+ ")";
      }
      *perl_ip += node + "|";
    }
  }
}

string GetPerlIpOpenOpen(const string& ip_a, const string& ip_b) {
  string split_ip_a[4];
  string split_ip_b[4];
  GetSplitIp(ip_a, &split_ip_a);
  GetSplitIp(ip_b, &split_ip_b);
  string split_ip_big[4];
  string split_ip_small[4];
  int diff_pos = BigAndSmallIp(split_ip_a, split_ip_b,
                               &split_ip_big, &split_ip_small);
  string perl_ip;
  if (kInitDiffPos == diff_pos) { /* i 没赋值给diff_pos说明没有不同的地方 */
    return perl_ip;
  }
  GetPerlIp(diff_pos, split_ip_small, split_ip_big, &perl_ip);
  if (0 == perl_ip.length()) {
    return perl_ip;
  }
  if ('|' == perl_ip[perl_ip.length() - 1]) {
    perl_ip.substr(0, perl_ip.length() - 1);
  }
  return perl_ip;
}

string GetPerlIpCloseOpen(const string& ip_a, const string& ip_b) {
  string split_ip_a[4];
  string split_ip_b[4];
  GetSplitIp(ip_a, &split_ip_a);
  GetSplitIp(ip_b, &split_ip_b);
  string big_ip = ip_a;
  string small_ip = ip_b;
  string split_ip_big[4];
  string split_ip_small[4];
  /* 比较，并找出首次不同的位置 */
  int diff_pos = BigAndSmallIp(split_ip_a, split_ip_b,
                               &split_ip_big, &split_ip_small);
  string perl_ip;
  if (kInitDiffPos == diff_pos) { /* i 没赋值给diff_pos说明没有不同的地方 */
    return perl_ip;
  }
  string perl_ip_open_open = GetPerlIpOpenOpen(small_ip, big_ip);
  perl_ip += small_ip;
  if (0 != perl_ip_open_open.length()) {
    perl_ip += "|";
    perl_ip += perl_ip_open_open;
  }
  return perl_ip;
}

string GetPerlIpOpenClose(const string& ip_a, const string& ip_b) {
  /* 将ip切分 */
  string split_ip_a[4];
  string split_ip_b[4];
  GetSplitIp(ip_a, &split_ip_a);
  GetSplitIp(ip_b, &split_ip_b);
  string big_ip = ip_a;
  string small_ip = ip_b;
  string split_ip_big[4];
  string split_ip_small[4];
  /* 比较，并找出首次不同的位置 */
  int diff_pos = BigAndSmallIp(split_ip_a, split_ip_b,
                               &split_ip_big, &split_ip_small);
  string perl_ip;
  if (kInitDiffPos == diff_pos) { /* i没赋值给diff_pos说明没不同的地方ip一样 */
    return perl_ip;
  }
  string perl_ip_open_open = GetPerlIpOpenOpen(small_ip, big_ip);
  if (0 != perl_ip_open_open.length()) {
    perl_ip += perl_ip_open_open;
    perl_ip += "|";
  }
  perl_ip += big_ip;
}

string GetPerlIpCloseClose(const string& ip_a, const string& ip_b) {
  /* 将ip切分 */
  string split_ip_a[4];
  string split_ip_b[4];
  GetSplitIp(ip_a, &split_ip_a);
  GetSplitIp(ip_b, &split_ip_b);
  string big_ip = ip_a;
  string small_ip = ip_b;
  string split_ip_big[4];
  string split_ip_small[4];
  /* 比较，并找出首次不同的位置 */
  int diff_pos = BigAndSmallIp(split_ip_a, split_ip_b,
                               &split_ip_big, &split_ip_small);
  string perl_ip = small_ip;
  perl_ip += "|";
  if (kInitDiffPos == diff_pos) { /* i没赋值给diff_pos说明没不同的地方ip一样 */
    perl_ip += big_ip;
    return perl_ip;
  }
  string perl_ip_open_open = GetPerlIpOpenOpen(small_ip, big_ip);
  if (0 != perl_ip_open_open.length()) {
    perl_ip += perl_ip_open_open;
    perl_ip += "|";
  }
  perl_ip += big_ip;
  return perl_ip;
}