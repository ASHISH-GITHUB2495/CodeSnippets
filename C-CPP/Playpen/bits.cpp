#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include <limits>
#include <utility>
#include <ctime>
#include <bitset>
using namespace std;

/*
ֻ����+,-��λ����ʵ������������(/)��ģ��(%),ע�⣺������log��
*/

//�ж�n�Ƿ���2����������
inline bool is_2exp(unsigned int n)
{
	return !(n&(n-1));
}

//���ָ�λȡ��
inline int negate_bits(unsigned int n)
{
	if(n==0) return 1;
	unsigned int r=0, m=~n;
	while(n)
	{
		r |= (n^(n-1))&m;
		n &= n-1;
	}

	return r;
}

//����n�Ķ����Ʊ�ʾ��1�ĸ���
inline int count1(unsigned int n)
{
	int r = 0;
	while(n)
	{
		n &= n-1;
		r++;
	}
	return r;
}

//����n�Ķ����Ʊ�ʾ��0�ĸ���
inline int count0( unsigned int n)
{
	int r = 0;
	n = negate_bits(n);
	while(n)
	{
		n &= n-1;
		r++;
	}
	return r;
}

//����������Ķ����Ʊ�ʾ��λ��
int count_bit(unsigned int n)
{
	int r = 0;
	while(n)
	{
		n>>=1;
		r++;
	}
	return r;
}

//����ڵ���n����С��2���������磬����1
//ʱ�临�Ӷ�O(n�Ķ�����λ����)
unsigned int high_2exp_1(unsigned int n)
{
	if(n<=1) return 1;
	if(is_2exp(n)) return n;

	unsigned int r = 1;
	while(n)
	{
		n >>= 1;
		r <<= 1;
	}

	return r;
}

//����ڵ���n����С��2���������磬����2
//����ʱ����n�Ķ����Ʊ�ʾ��1�ĸ�����λ���йأ��ȷ���1Ч�ʸ�
//�����µ�ʱ�临�Ӷ��뷽��1��ͬ
unsigned int high_2exp_2(unsigned int n)
{
	if(n<=1) return 1;

	while(!is_2exp(n))
	{
		n |= n-1;
		n++;
	}

	return n;
}

//�ж�n�Ƿ���4����������
bool is_4exp(unsigned int n)
{
	if(!is_2exp(n)) return false;

	int bit_len = count_bit(n)-1;//����ʱ���������λ��
	if((bit_len&0x1)!=1)
		return true;
	else
		return false;
}

int integer_div_0(int dividend, int divisor)
{
	if(divisor == 0)
	{
		cout<<"�Ƿ������������"<<endl;
		exit(1);
	}

	int res = 0;
	while((dividend-=divisor)>=0)
		++res;

	return res;
}

//�ݹ���������
int integer_div_1(unsigned int dividend, unsigned int divisor)
{
	if(divisor == 0)
	{
		cout<<"�Ƿ������������"<<endl;
		exit(1);
	}

	if(dividend < divisor) return 0;
	unsigned int k=0,c=divisor, res=0;
	
	for(;dividend>=c;c<<=1,k++)
		if(dividend-c < divisor)
			return 1<<k;

	return integer_div_1(dividend-(c>>1), divisor)+(1<<(k-1));
}

//�ǵݹ���������
int integer_div_2(unsigned int dividend, unsigned int divisor)
{
	if(divisor == 0)
	{
		cout<<"�Ƿ������������"<<endl;
		exit(1);
	}

	if(dividend < divisor) return 0;
	unsigned int k, c, res=0;

	while(dividend > divisor)
	{
		for(k=0,c=divisor;dividend>=c;c<<=1,k++)
		{
			if(dividend-c < divisor)
			{
				res += 1<<k;
				break;
			}		
		}
		if(dividend-c < divisor)
			break;

		res += 1<<(k-1);
		dividend -= c>>1;
	}

	return res;
}

//��������andȡģ�������̺�����
pair<int,int> integer_div_3(unsigned int dividend, unsigned int divisor)
{
	if(divisor == 0)
	{
		cout<<"�Ƿ������������"<<endl;
		exit(1);
	}

	if(dividend < divisor) 
		return make_pair(0, dividend);
	unsigned int k, c, quotient=0, remainder;

	while(dividend > divisor)
	{
		for(k=0,c=divisor;dividend>=c;c<<=1,k++)
		{
			if(dividend-c < divisor)
			{
				quotient += 1<<k;
				remainder = dividend-c;
				break;
			}		
		}
		if(dividend-c < divisor)
			break;

		quotient += 1<<(k-1);
		dividend -= c>>1;
	}

	return make_pair(quotient, remainder);
}

//��ӡn�Ķ����Ʊ�ʾ
void print_bits(unsigned int n)
{
	bitset<32> bs(n);
	for(int i=bs.size()-1;i>=0;i--)
		cout<<bs.at(i);
	cout<<endl;
}

int main()
{
	unsigned int n,m;
	while(cin>>n>>m)
	{
		cout<<integer_div_3(n,m).first<<" "<<integer_div_3(n,m).second<<endl;
	}
	
	return 0;
}

