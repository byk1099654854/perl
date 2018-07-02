#ifndef PERL_NUM_IP_H_
#define PERL_NUM_IP_H_

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief ����ƥ�䴫�����������֮������ֵ�������ʽ�����ҿ���
 * @param num_a �����һ������
 * @param num_b �����һ������
 * @return ����������ʽ�����������ƥ��������򷵻ؿգ�
 */
string GetPerlOpenOpen(const string& num_a, const string& num_b);

/**
 * @brief ����ƥ�䴫�����������֮������ֵ�������ʽ�����ұգ�
 * @param num_a �����һ������
 * @param num_b �����һ������
 * @return ����������ʽ�����������ƥ��������򷵻ؿգ�
 */
string GetPerlOpenClose(const string& num_a, const string& num_b);

/**
 * @brief ����ƥ�䴫�����������֮������ֵ�������ʽ������ҿ���
 * @param num_a �����һ������
 * @param num_b �����һ������
 * @return ����������ʽ�����������ƥ��������򷵻ؿգ�
 */
string GetPerlCloseOpen(const string& num_a, const string& num_b);

/**
 * @brief ����ƥ�䴫�����������֮������ֵ�������ʽ������ұգ�
 * @param num_a �����һ������
 * @param num_b �����һ������
 * @return ����������ʽ
 */
string GetPerlCloseClose(const string& num_a, const string& num_b);


/**
 * @brief ����ƥ�䴫�������IP֮���IP��������ʽ�����ҿ���
 * @param ip_a �����һ��IP
 * @param ip_b �����һ��IP
 * @return ����������ʽ�����������ƥ���IP�򷵻ؿգ�
 */
string GetPerlIpOpenOpen(const string& ip_a, const string& ip_b);

/**
 * @brief ����ƥ�䴫�������IP֮���IP��������ʽ������ҿ���
 * @param ip_a �����һ��IP
 * @param ip_b �����һ��IP
 * @return ����������ʽ�����������ƥ���IP�򷵻ؿգ�
 */
string GetPerlIpCloseOpen(const string& ip_a, const string& ip_b);

/**
 * @brief ����ƥ�䴫�������IP֮���IP��������ʽ�����ұգ�
 * @param ip_a �����һ��IP
 * @param ip_b �����һ��IP
 * @return ����������ʽ�����������ƥ���IP�򷵻ؿգ�
 */
string GetPerlIpOpenClose(const string& ip_a, const string& ip_b);

/**
 * @brief ����ƥ�䴫�������IP֮���IP��������ʽ������ұգ�
 * @param ip_a �����һ��IP
 * @param ip_b �����һ��IP
 * @return ����������ʽ
 */
string GetPerlIpCloseClose(const string& ip_a, const string& ip_b);

#endif /* PERL_NUM_IP_H_ */