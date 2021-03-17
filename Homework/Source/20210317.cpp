#include "20210317.h"
#include <iostream>
#include <array>
/*
 *코드
 *프로그램이 실행되는 코드가 저장되는 곳
 *
 *데이터
 *전역 변수 등이 저장되는 곳
 *
 *스택
 *지역변수 등 저장 되는 곳
 *해당 함수가 끝나면 해제되므로 지역변수의 레퍼런스를 리턴하면 안됨
 *재귀함수 잘못쓰면 스택이 가득차 터지곤 한다.
 *
 *힙
 *동적할당으로 OS에서 얻어돈 메모리 공간
 *new delete와 관련있다
 *스택과 달리 우리가 직접 관리해야하고 관리를 잘못해 메모리 일부를 해제하지 않고 새로 할당받아 쓰게 되면 메모리릭이 일어난다. 이는 장기간 돌아가야하는 서버에서는 치명적이다.
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
		"12345678900", //int 범위 초과할 때
		"-1",
		"-12",
		"-1234",
		"-12345",
		"-123456",
		"-a1234567",//중간에 숫자 아닌거 섞기
		"-1234a5678",
		"-12a345678",
		"-0123456789123",
		"-12345678900", //int 범위 초과할 때
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

	//양수 음수 구분 
	switch (_ptr[0])
	{
	case '-':
		sign = -1;
		--strsize; //-부호 한 칸만큼 뒤로 땡겨서 양수와 똑같이 맞춤
		++ptr; //-뒷 자리부터 작업
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
			//int 범위 밖으로 벗어나면 끝내기
			if (false == function(result, ptr[i] - '0'))
			{
				break;
			}
		}
		else//숫자 이외 다른 문자 오면 끝내기
		{
			break;
		}
	}
	return result;

}

void NS20210317::IntToStr(char** ptr, int _number)
{
	char* str = nullptr;

	int sign = 1; //부호
	int numlen = 0; //숫자 길이
	if (_number < 0)
	{
		sign = -1;
		++numlen; // '-'자리 한 칸더
	}

	//std::cout << "number : " << _number << std::endl;
	int num = sign * _number; //음수인경우 -1 곱해서 잠시 양수처럼 취급
	
	
	
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
	str = new char[numlen + 1]; // '\0' 자리
	char* tempstr = str;
	str[numlen] = '\0';
	if (_number < 0)
	{
		str[0] = '-';
		tempstr += 1;
		--numlen; //여기서 안 돌려놓으면 아래서 음수 따로 처리해야함
	}
	

	

	auto getnumber = [](const int _num, const int pos)->int
	{
		
		const long long num = _num;
		
		if (pos <= 0)
		{
			throw std::runtime_error("음수 자리?");
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
	 *예: 양수 6자리 123456
	 *
	 *길이 6
	 *0인덱스	1	2	3	4	5
	 *6자리		5	4	3	2	1 일의자리 십의자리...
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
