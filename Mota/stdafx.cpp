#include "stdafx.h"

HWND GameActive;
LOGFONT Font;

int Round(double n) {
	return floor(n + 0.5);
}

int QuickPow(int a, int b){
	int res = 1;
	while (b) {
		if (b & 1) {
			res = res * a;
		}
		a = a * a;
		b >>= 1;
	}
	return res;
}

const void operator << (string& a, const int b) {
	a = to_string(b);
}

const void operator << (int& a, const string b) {
	a = stoi(b);
}

const void operator << (short& a, const string b) {
	a = stoi(b);
}

const void operator << (unsigned short& a, const string b) {
	a = stoi(b);
}

const void operator << (bool& a, const string b) {
	a = stoi(b);
}

void OpaqueImage(IMAGE *dstimg, int x, int y, IMAGE *srcimg, int opacity) {
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER,0,opacity,AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

void OpaqueImage(IMAGE *dstimg, int x, int y, int width, int height, int sx, int sy, IMAGE *srcimg, int opacity) {
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = width;
	int h = height;
	BLENDFUNCTION bf = { AC_SRC_OVER,0,opacity,AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, sx, sy, w, h, bf);
}

void BitmapOpaque(string file, int x, int y, int width, int height, int sx, int sy, int opacity) {
	file = "res\\picture\\" + file;
	if (!ExistFile(file)) {
		return;
	}
	IMAGE* pic = nullptr;
	pic = new IMAGE;
	loadimage(pic, _T(file.c_str()));
	OpaqueImage(nullptr, x, y, width, height, sx, sy, pic, opacity);
	delete pic;
}

void BitmapOpaque(string file, int x, int y, int opacity) {
	file = "res\\picture\\" + file;
	if (!ExistFile(file)) {
		return;
	}
	IMAGE* pic = nullptr;
	pic = new IMAGE;
	loadimage(pic, _T(file.c_str()));
	OpaqueImage(nullptr, x, y, pic, opacity);
	delete pic;
}

void BitmapCentre(string file, int x, int y, int opacity) {
	file = "res\\picture\\" + file;
	if (!ExistFile(file)) {
		return;
	}
	IMAGE* pic = nullptr;
	pic = new IMAGE;
	loadimage(pic, _T(file.c_str()));
	OpaqueImage(nullptr, x - pic->getwidth() / 2, y - pic->getheight() / 2, pic, opacity);
	delete pic;
}

void Print(string content) {
	MessageBox(NULL, content.c_str(), "Hint", MB_OK);
}

int YesNoPrint(string content) {
	return MessageBox(NULL, content.c_str(), "Confirmation", MB_ICONEXCLAMATION | MB_YESNO);
}

bool StringInclude(string source, string target) {
	return (source.find(target) != -1);
}

bool ExistFile(string filename) {
	return (_access(filename.c_str(), 0) != -1);
}

vector <string> Split(const string &s, const string &seperator) {
	vector <string> result;
	typedef string::size_type string_size;
	string_size i = 0;
	while (i != s.size()) {
		int flag = 0;
		while (i != s.size() && !flag) {
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x) {
				if (s[i] == seperator[x]) {
					++i;
					flag = 0;
					break;
				}
			}
		}
		flag = 0;
		string_size j = i;
		while (j != s.size() && !flag) {
			for (string_size x = 0; x < seperator.size(); ++x) {
				if (s[j] == seperator[x]) {
					flag = 1;
					break;
				}
			}
			if (!flag) {
				++j;
			}
		}
		if (i != j) {
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}

vector <string> ReadData(string file) {
	vector <string> ret;
	fstream data;
	char buffer[4096];
	data.open(file.c_str(), ios::in);
	while (!data.eof()) {
		data.getline(buffer, 4096);
		string str = buffer;
		int fnd = str.find("=");
		string str2 = (fnd == -1 ? str : Split(str, "=")[1]);
		if (str2 != "") {
			ret.push_back(str2);
		}
	}
	data.close();
	return ret;
}
