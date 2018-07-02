#ifndef PERL_NUM_IP_H_
#define PERL_NUM_IP_H_

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief 返回匹配传入的两个数字之间的数字的正则表达式（左开右开）
 * @param num_a 传入的一个数字
 * @param num_b 传入的一个数字
 * @return 返回正则表达式（如果不存在匹配的数字则返回空）
 */
string GetPerlOpenOpen(const string& num_a, const string& num_b);

/**
 * @brief 返回匹配传入的两个数字之间的数字的正则表达式（左开右闭）
 * @param num_a 传入的一个数字
 * @param num_b 传入的一个数字
 * @return 返回正则表达式（如果不存在匹配的数字则返回空）
 */
string GetPerlOpenClose(const string& num_a, const string& num_b);

/**
 * @brief 返回匹配传入的两个数字之间的数字的正则表达式（左闭右开）
 * @param num_a 传入的一个数字
 * @param num_b 传入的一个数字
 * @return 返回正则表达式（如果不存在匹配的数字则返回空）
 */
string GetPerlCloseOpen(const string& num_a, const string& num_b);

/**
 * @brief 返回匹配传入的两个数字之间的数字的正则表达式（左闭右闭）
 * @param num_a 传入的一个数字
 * @param num_b 传入的一个数字
 * @return 返回正则表达式
 */
string GetPerlCloseClose(const string& num_a, const string& num_b);


/**
 * @brief 返回匹配传入的两个IP之间的IP的正则表达式（左开右开）
 * @param ip_a 传入的一个IP
 * @param ip_b 传入的一个IP
 * @return 返回正则表达式（如果不存在匹配的IP则返回空）
 */
string GetPerlIpOpenOpen(const string& ip_a, const string& ip_b);

/**
 * @brief 返回匹配传入的两个IP之间的IP的正则表达式（左闭右开）
 * @param ip_a 传入的一个IP
 * @param ip_b 传入的一个IP
 * @return 返回正则表达式（如果不存在匹配的IP则返回空）
 */
string GetPerlIpCloseOpen(const string& ip_a, const string& ip_b);

/**
 * @brief 返回匹配传入的两个IP之间的IP的正则表达式（左开右闭）
 * @param ip_a 传入的一个IP
 * @param ip_b 传入的一个IP
 * @return 返回正则表达式（如果不存在匹配的IP则返回空）
 */
string GetPerlIpOpenClose(const string& ip_a, const string& ip_b);

/**
 * @brief 返回匹配传入的两个IP之间的IP的正则表达式（左闭右闭）
 * @param ip_a 传入的一个IP
 * @param ip_b 传入的一个IP
 * @return 返回正则表达式
 */
string GetPerlIpCloseClose(const string& ip_a, const string& ip_b);

#endif /* PERL_NUM_IP_H_ */