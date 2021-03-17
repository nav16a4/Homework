#include "20210317.h"
#include <iostream>
#include <array>
/*
 *�ڵ�
 *���α׷��� ����Ǵ� �ڵ尡 ����Ǵ� ��
 *
 *������
 *���� ���� ���� ����Ǵ� ��
 *
 *����
 *�������� �� ���� �Ǵ� ��
 *�ش� �Լ��� ������ �����ǹǷ� ���������� ���۷����� �����ϸ� �ȵ�
 *����Լ� �߸����� ������ ������ ������ �Ѵ�.
 *
 *��
 *�����Ҵ����� OS���� �� �޸� ����
 *new delete�� �����ִ�
 *���ð� �޸� �츮�� ���� �����ؾ��ϰ� ������ �߸��� �޸� �Ϻθ� �������� �ʰ� ���� �Ҵ�޾� ���� �Ǹ� �޸𸮸��� �Ͼ��. �̴� ��Ⱓ ���ư����ϴ� ���������� ġ�����̴�.
 * 
 */

int NS20210317::main()
{
	test();
	return 0;
}

void NS20210317::test()
{
	char* test = nullptr;
	static const int testcount = 20;
	std::array<int, testcount> testint =
	{ 1,
		12,
		123,
		1234,
		12345,
		123456,
		1234567,
		12345678,
		123456789,
		1234567890,
		-1,
		-12,
		-123,
		-1234,
		-12345,
		-123456,
		-1234567,
		-12345678,
		-123456789,
		-1234567890
	};


	for (auto iter : testint)
	{
		IntToStr(&test, iter);
		std::cout << iter<<" -> "<<test << std::endl;
		delete[] test;
	}
	std::cout << "==================================\n";
	std::array<char[16], 20> testchar =
	{
		"1",
		"12",
		"1234",
		"12345",
		"123456",
		"1234567",
		"1234a5678",
		"a12345678",
		"01234567890",
		"12345678900", //int ���� �ʰ��� ��
		"-1",
		"-12",
		"-1234",
		"-12345",
		"-123456",
		"-a1234567",//�߰��� ���� �ƴѰ� ����
		"-1234a5678",
		"-12a345678",
		"-0123456789123",
		"-12345678900", //int ���� �ʰ��� ��
	};
	for ( auto iter : testchar)
	{
		std::cout << iter<< " -> "<<StrToInt(iter)<<std::endl;
		
	}

	return;
}



int NS20210317::StrToInt(char* _ptr)
{
	auto plus_and_check = [](const int sign, int& num, const int n)->bool
	{
		bool result = true;
		const long long temp = ((long long)num * 10) + n * sign;
		if (INT32_MIN < temp && temp < INT32_MAX)
		{
			num = temp;
			result = true;
		}
		else
		{
			result = false;
		}
		return result;
	};

	if (nullptr == _ptr)
	{
		return 0;
	}

	int sign = 0;
	char* ptr = const_cast<char*>(_ptr);
	int strsize = strlen(_ptr);

	//��� ���� ���� 
	switch (_ptr[0])
	{
	case '-':
		sign = -1;
		--strsize; //-��ȣ �� ĭ��ŭ �ڷ� ���ܼ� ����� �Ȱ��� ����
		++ptr; //-�� �ڸ����� �۾�
		break;
	default:
		sign = 1;
		break;
	}

	const std::function<bool(int&, const int)> function = [&plus_and_check, sign](int& num, const int n)
	{
		return plus_and_check(sign, num, n);
	};

	int result = 0;


	for (int i = 0; '\0' != ptr[i]; ++i)
	{
		if ('0' <= ptr[i] && ptr[i] <= '9')
		{
			//int ���� ������ ����� ������
			if (false == function(result, ptr[i] - '0'))
			{
				break;
			}
		}
		else//���� �̿� �ٸ� ���� ���� ������
		{
			break;
		}
	}
	return result;

}

void NS20210317::IntToStr(char** ptr, int _number)
{
	char* str = nullptr;

	int sign = 1; //��ȣ
	int numlen = 0; //���� ����
	if (_number < 0)
	{
		sign = -1;
		++numlen; // '-'�ڸ� �� ĭ��
	}

	//std::cout << "number : " << _number << std::endl;
	int num = sign * _number; //�����ΰ�� -1 ���ؼ� ��� ���ó�� ���
	
	
	
	auto getdigit = [](int num)->int
	{
		int size = 0;

		do 
		{
			num = static_cast<int>(static_cast<float>(
				num) * 0.1);
			++size;
		} while (0 != num);

		return size;
	};

	numlen += getdigit(num);
	str = new char[numlen + 1]; // '\0' �ڸ�
	char* tempstr = str;
	str[numlen] = '\0';
	if (_number < 0)
	{
		str[0] = '-';
		tempstr += 1;
		--numlen; //���⼭ �� ���������� �Ʒ��� ���� ���� ó���ؾ���
	}
	

	

	auto getnumber = [](const int _num, const int pos)->int
	{
		
		const long long num = _num;
		
		if (pos <= 0)
		{
			throw std::runtime_error("���� �ڸ�?");
		}

		long long inteager = 1;
		for (int i = 0; i < pos; ++i)
		{
			inteager *= 10;
		}
		long long returnvalue = (num % inteager) / (inteager / 10); 
		return static_cast<int>(returnvalue);
	};


	/*
	 *��: ��� 6�ڸ� 123456
	 *
	 *���� 6
	 *0�ε���	1	2	3	4	5
	 *6�ڸ�		5	4	3	2	1 �����ڸ� �����ڸ�...
	 * 
	 */
	
	for(int i=0; tempstr[i]!='\0';++i)
	{
		int temp = getnumber(num, numlen-i);
		//std::cout << temp << std::endl;
		tempstr[i] = temp+'0';
	}
	
	*ptr = str;
	//std::cout << str;
}
