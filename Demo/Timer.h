#pragma once
#include <chrono> //��ȡʱ���ͷ�ļ�
using namespace std;

class Timer //��ʱ����
{
private:
	chrono::steady_clock::time_point timerStart;

public:
	void begin()
	{
		timerStart = chrono::steady_clock::now(); //��¼��ʼʱ��
	}
	double delta()
	{
		auto timeNow = chrono::steady_clock::now(); //��¼����ʱ��
		return chrono::duration<double>(timeNow - timerStart).count(); //����ʱ����(���뼶)
	}
};

