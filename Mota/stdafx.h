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

// 宏定义
#define loop while (true)
#define rfor(i, a, b) for (int i = a; i < b; ++i)
#define unless(c) if (!(c))
#define Write(outFile, data) outFile.write((char*)(&data), sizeof(data))
#define Read(inFile, data) inFile.read((char*)(&data), sizeof(data))

using namespace std;

// 四舍五入
int Round(double n);

// 快速幂
int QuickPow(int a, int b);

// 几个运算符重载
const void operator << (string& a, const int b);

const void operator << (int& a, const string b);

const void operator << (short& a, const string b);

const void operator << (unsigned short& a, const string b);

const void operator << (bool& a, const string b);

/*
透明图片绘制
*dstimg 设备指针
x       图片x坐标
y       事件y坐标
width   截取图片宽度
height  截取图片高度
sx      截取图片在原图片的x坐标
sy      截取图片在原图片的y坐标
*srcimg 接收的图片指针
opacity 不透明度
*/
void OpaqueImage(IMAGE *dstimg, int x, int y, IMAGE *srcimg, int opacity = 255);

void OpaqueImage(IMAGE *dstimg, int x, int y, int width, int height, int sx, int sy, IMAGE *srcimg, int opacity = 255);

/*
直接显示图片
file    文件名，会自动索引至res\picture
x       图片x坐标
y       图片y坐标
width   截取图片宽度
height  截取图片高度
sx      截取图片在原图片的x坐标
sy      截取图片在原图片的y坐标
opacity 不透明度
*/
void BitmapOpaque(string file, int x, int y, int width, int height, int sx = 0, int sy = 0, int opacity = 255);

void BitmapOpaque(string file, int x, int y, int opacity = 255);

/*
以坐标为中心显示图片
file    文件名，会自动索引至res\picture
x       图片x坐标
y       图片y坐标
opacity 不透明度
*/
void BitmapCentre(string file, int x, int y, int opacity = 255);

// MessageBox窗口显示消息
void Print(string content);

// MessageBox窗口显示确认窗口
int YesNoPrint(string content);

// 字符串是否包含某子串
bool StringInclude(string source, string target);

// 文件是否存在
bool ExistFile(string filename);

/*
字符串分割
用vector<string>对象接收
*/
vector <string> Split(const string &s, const string &seperator);

// 读取ini文件
vector <string> ReadData(string file);

// vector中是否包含某对象
template<typename T>
bool VectorFind(vector<T> source, T target) {
	return (find(source.begin(), source.end(), target) != source.end());
}
