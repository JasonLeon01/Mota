#pragma once
#pragma comment(lib, "winmm")
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"Winmm.lib")

#include <Windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <graphics.h>
#include <io.h>
#include <conio.h>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <cstdint>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>

// �궨��
#define loop while (true)
#define rfor(i, a, b) for (int i = a; i < b; ++i)
#define unless(c) if (!(c))
#define Write(outFile, data) outFile.write((char*)(&data), sizeof(data))
#define Read(inFile, data) inFile.read((char*)(&data), sizeof(data))

using namespace std;

// ��������
int Round(double n);

// ������
int QuickPow(int a, int b);

// �������������
const void operator << (string& a, const int b);

const void operator << (int& a, const string b);

const void operator << (short& a, const string b);

const void operator << (unsigned short& a, const string b);

const void operator << (bool& a, const string b);

/*
͸��ͼƬ����
*dstimg �豸ָ��
x       ͼƬx����
y       �¼�y����
width   ��ȡͼƬ���
height  ��ȡͼƬ�߶�
sx      ��ȡͼƬ��ԭͼƬ��x����
sy      ��ȡͼƬ��ԭͼƬ��y����
*srcimg ���յ�ͼƬָ��
opacity ��͸����
*/
void OpaqueImage(IMAGE *dstimg, int x, int y, IMAGE *srcimg, int opacity = 255);

void OpaqueImage(IMAGE *dstimg, int x, int y, int width, int height, int sx, int sy, IMAGE *srcimg, int opacity = 255);

/*
ֱ����ʾͼƬ
file    �ļ��������Զ�������res\picture
x       ͼƬx����
y       ͼƬy����
width   ��ȡͼƬ���
height  ��ȡͼƬ�߶�
sx      ��ȡͼƬ��ԭͼƬ��x����
sy      ��ȡͼƬ��ԭͼƬ��y����
opacity ��͸����
*/
void BitmapOpaque(string file, int x, int y, int width, int height, int sx = 0, int sy = 0, int opacity = 255);

void BitmapOpaque(string file, int x, int y, int opacity = 255);

/*
������Ϊ������ʾͼƬ
file    �ļ��������Զ�������res\picture
x       ͼƬx����
y       ͼƬy����
opacity ��͸����
*/
void BitmapCentre(string file, int x, int y, int opacity = 255);

// MessageBox������ʾ��Ϣ
void Print(string content);

// MessageBox������ʾȷ�ϴ���
int YesNoPrint(string content);

// �ַ����Ƿ����ĳ�Ӵ�
bool StringInclude(string source, string target);

// �ļ��Ƿ����
bool ExistFile(string filename);

/*
�ַ����ָ�
��vector<string>�������
*/
vector <string> Split(const string &s, const string &seperator);

// ��ȡini�ļ�
vector <string> ReadData(string file);

// vector���Ƿ����ĳ����
template<typename T>
bool VectorFind(vector<T> source, T target) {
	return (find(source.begin(), source.end(), target) != source.end());
}
