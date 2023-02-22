#pragma once

#include "stdafx.h"

#ifndef __Basic_H__
#define __Basic_H__

/*
绘制窗口矩形（包括窗口矩形和选项矩形）
backx		矩形背景所在x坐标
backy		矩形背景所在y坐标
cornerx		矩形四个角所在x坐标
cornery		矩形四个角所在y坐标
sidex		矩形四条边所在x坐标
sidey		矩形四条边所在y坐标
backlen		矩形背景长度
cornerlen	矩形角长度
sidelen		矩形边长度
opacity		不透明度
drawx		绘制的x坐标
drawy		绘制的y坐标
drawwidth	绘制的宽
drawheight	绘制的高
select		是否是待选项的窗口
*/
void WindowRect(int backx, int backy, int cornerx[], int cornery[], int sidex[], int sidey[], int backlen, int cornerlen, int sidelen, int opacity, int drawx, int drawy, int drawwidth, int drawheight, bool select);

/*
绘制文字
x		绘制的x坐标
y		绘制的y坐标
width	绘制的文字矩形宽度
height	绘制的文字矩形高度
content	绘制的文字内容
pos		文字在矩形中的位置：0 左靠齐；1 居中；2 右靠齐；3左靠齐，触右换行
size	文字字号
bond	是否加粗
*/
void DrawTexts(int x, int y, int width, int height, string content, int pos = 0, LONG size = 22, bool bond = false);

// 绘制带阴影的文字
void DrawTextsBond(int x, int y, int width, int height, string content, int pos = 0, LONG size = 22, bool bond = false);

// 播放音效
void PlaySE(string file);

// 播放背景音乐
void PlayBGM(string file);

#endif

extern HWND GameActive;
extern LOGFONT Font;

// 所有场景类的基类，仅包含纯虚函数
class SceneBase {
public:
	virtual void Main() = 0;
};

/*
GameEvent
处理事件的类
通过此类可以获取事件属性以及激活事件方法
*/
class GameEvent {
public:
	string Name;				// 事件名
	string File[2];				// 事件图形
	short X;					// 事件x坐标
	short Y;					// 事件y坐标
	short TriggerCondition[3];	// 事件的出现触发条件：第一项：1 开关出现，2，变量出现，3 开关可执行，4 变量可执行；第二项：开关或变量编号；第三项：开关或变量需满足的值
	bool Exist;					// 事件是否还存在
	bool Through;				// 事件是否可穿透
	//构造函数，初始化对象
	GameEvent();
	GameEvent(int x, int y);
	// 判定两事件是否相等，用于查询事件，相等的条件是xy坐标相同
	const bool operator == (const GameEvent& ev);
	// 事件执行的操作
	void Order();
	// 开门
	void OpenDoor();
};

/*
DataMap
处理地图数据的类
通过此类可以获取地图属性和地图中的事件
其中判定两事件间是否可通行、是否相邻以及等待函数为静态，无需构建对象即可调用
*/
class DataMap {
public:
	string MapName;								// 地图名
	string FloorName;							// 地板文件名
	vector <GameEvent> MapEvents;				// 地图中事件
	// 判断两地图是否相等，相等的条件是地图名相同
	const bool operator == (const DataMap& mp);
	// 在(x,y)处是否存在事件
	bool HaveAnEvent(int x, int y);
	// 在(x,y)处是否存在事件（被消去的也会返回）
	bool HaveAnEEvent(int x, int y);
	// 返回在(x,y)处的事件编号
	int CheckEvent(int x, int y);
	// 返回在(x,y)处的事件指针
	GameEvent* ECheckEvent(int x, int y);
	// 指定id事件的位置
	pair <int, int> HeAt(int id);
	// 判断在(x,y)处是否可以通行
	bool Passible(int x, int y);
	// 判断两事件间是否可以通行
	static bool HaveEventsAlong(pair <int, int> ev1, pair <int, int> ev2);
	// 判断两事件是否相邻
	static bool Beside(pair <int, int> ev1, pair <int, int> ev2);
	// 等待（单位帧）
	static void WaitCount(int times);
};

/*
DataSystem
处理游戏数据的类
可以保存各种相关的游戏参数
读取数据、重新加载数据、初始化均在此类中
*/
class DataSystem {
public:
	map <int, vector<int> > FloorRecord;	// 记录去过的楼层
	vector <DataMap> Maps;					// 所有地图
	SceneBase* Scene;						// 事件基类
	IMAGE *TransitionGraphic;				// 准备过渡
	unsigned int GameTime = 0;				// 游戏时间
	short MessagePos;						// 文章位置
	short FrameRate;						// 刷新频率，单位ms
	short WindowOpacity;					// 窗口的不透明度
	short MapX;								// 地图在游戏窗口的X坐标
	short MapY;								// 地图在游戏窗口的Y坐标
	short BattleEnemyID;					// 正在进行的战斗中敌人ID
	short FunctioningEventID;				// 正在处理的事件ID
	short ShopType;							// 商店类型
	short ShopID;							// 商店编号
	short TransitionOpacity;				// 过渡不透明度
	int GameVariables[5000];				// 变量
	short ShopPrice[3];						// 商店价格
	short ShopEXP[4];						// 商店经验
	bool NeedRefresh;						// 是否需要刷新地图（刷新将会重新加载图像）
	bool ScreenShot;						// 是否屏幕截图
	bool DirectlyFunction;					// 事件改名后是否直接执行
	bool EndGame;							// 游戏结束
	bool FirstArrive;						// 首次来到地图
	bool Transition;						// 过渡标志
	bool GameSwitches[5000];				// 开关
	bool ItemRecord[99];					// 获取物品记录
	bool GemRecord[99][99];					// 获取宝石记录
	bool BottleRecord[999];					// 获取血瓶记录
	bool Victory;							// 过关
	string WindowskinName;					// 窗口文件名
	string TitleName;						// 标题文件名
	string FontName;						// 字体名
	string GameBGM;							// 游戏背景音乐
	string CursorSE;						// 选择音效
	string DecisionSE;						// 确认音效
	string CancelSE;						// 取消音效
	string BuzzerSE;						// 警告音效
	string ShopSE;							// 商店音效
	string SaveSE;							// 存档音效
	string LoadSE;							// 读档音效
	string GateSE;							// 开门音效
	string GetSE;							// 获取道具音效
	string StairSE;							// 上下楼音效
	string MoveSE;							// 移动音效
	string ShotFile;						// 屏幕截图文件名
	string TransformingEventName;			// 事件结束后改变成为的名字
	vector <string> MessageName;			// 窗口显示的角色名
	vector <string> MessageContent;			// 窗口显示的文字
	vector <int> MessageHead;				// 窗口显示的事件ID
	// 读取数据
	void DataLoad();
	// 游戏整体初始化
	void Initialization();
	// 重新加载数据
	void Reload();
	void ReadyTransition();
	void DoTransition(int time = 8);
}; extern DataSystem System;

/*
GameSprite
处理游戏精灵的类
通过此类可以获取精灵的相关属性
*/
class GameSprite {
public:
	string Name;						// 加载的图片文件名
	short X;							// x坐标
	short Y;							// y坐标
	short Z;							// z坐标
	short Width;						// 切片宽（0为不切片）
	short Height;						// 切片高（0为不切片）
	short SrcX;							// 切片在原图中的x坐标
	short SrcY;							// 切片在原图中的y坐标
	short Angle;						// 旋转角
	short Position;						// 坐标原点（0左上1居中）
	short Opacity;						// 不透明度
	bool Visible;						// 是否可视
	IMAGE* Image;						// IMAGE指针
	// 构造函数，初始化对象
	GameSprite();
	GameSprite(string name);
	GameSprite(string name, int opacity);
	GameSprite(string name, int x, int y, int opacity);
	// 获得精灵宽度
	int SpriteWidth();
	// 获得精灵高度
	int SpriteHeight();
	// 改变精灵图片文件名
	void ChangeImage(string name);
	// 加入到Graphics数组中
	void AddIn();
	// 释放
	void Dispose();
};

/*
GameKeyBoard
处理游戏按键的类
*/
class GameKeyBoard {
public:
	// 全键盘按键列表
	int KeyBACK = 0x08;
	int KeyTAB = 0x09;
	int KeyRETURN = 0x0D;
	int KeySHIFT = 0x10;
	int KeyCTRL = 0x11;
	int KeyALT = 0x12;
	int KeyPAUSE = 0x13;
	int KeyCAPITAL = 0x14;
	int KeyESCAPE = 0x1B;
	int KeySPACE = 0x20;
	int KeyPRIOR = 0x21;
	int KeyNEXT = 0x22;
	int KeyEND = 0x23;
	int KeyHOME = 0x24;
	int KeyLEFT = 0x25;
	int KeyUP = 0x26;
	int KeyRIGHT = 0x27;
	int KeyDOWN = 0x28;
	int KeySELECT = 0x29;
	int KeyPRINT = 0x2A;
	int KeySNAPSHOT = 0x2C;
	int INSERT = 0x2D;
	int KeyDELETE;
	int Key0 = 0x30;
	int Key1 = 0x31;
	int Key2 = 0x32;
	int Key3 = 0x33;
	int Key4 = 0x34;
	int Key5 = 0x35;
	int Key6 = 0x36;
	int Key7 = 0x37;
	int Key8 = 0x38;
	int Key9 = 0x39;
	int KeyA = 0x41;
	int KeyB = 0x42;
	int KeyC = 0x43;
	int KeyD = 0x44;
	int KeyE = 0x45;
	int KeyF = 0x46;
	int KeyG = 0x47;
	int KeyH = 0x48;
	int KeyI = 0x49;
	int KeyJ = 0x4A;
	int KeyK = 0x4B;
	int KeyL = 0x4C;
	int KeyM = 0x4D;
	int KeyN = 0x4E;
	int KeyO = 0x4F;
	int KeyP = 0x50;
	int KeyQ = 0x51;
	int KeyR = 0x52;
	int KeyS = 0x53;
	int KeyT = 0x54;
	int KeyU = 0x55;
	int KeyV = 0x56;
	int KeyW = 0x57;
	int KeyX = 0x58;
	int KeyY = 0x59;
	int KeyZ = 0x5A;
	// 按键次数（用于判断是否双击）
	int hit_times = 0;
	// 轻按
	bool LPress(int key);
	// 按下
	bool Press(int key);
	// 重新按下
	bool Repeat(int key);
	// 按住
	bool Trigger(int key);
	// 按下确定
	bool PressConfirm();
	// 重新按下确定
	bool RepeatConfirm();
	// 按住确定
	bool TriggerConfirm();
	// 按下取消
	bool PressCancel();
	// 重新按下取消
	bool RepeatCancel();
	// 按住取消
	bool TriggerCancel();
	// 双击
	bool DoubleClick(int key);
	// 四方向判定
	int Dir4();
private:
	map <int, int> key_hash, key_repeat, double_click;
}; extern GameKeyBoard KeyBoard;

/*
GameWindow
所有游戏窗口的基类，包括纯虚函数Refresh
通过此类可以获取窗口属性，绘制矩形以及在窗口内描绘文字和图像
*/
class GameWindow {
public:
	short X;					// 窗口x坐标
	short Y;					// 窗口y坐标
	short Z;					// 窗口z坐标
	short Width;				// 窗口宽
	short Height;				// 窗口高
	short Opacity;				// 窗口不透明度
	bool HasFunction;			// 是否有功能（为true则会自动执行Refresh方法）
	bool Visible;				// 是否可视
	virtual void Refresh() = 0;	// 刷新（纯虚函数）
	// 构造函数，初始化对象
	GameWindow();
	GameWindow(int x, int y, int width, int height, int opacity = System.WindowOpacity);
	// 绘制矩形
	void DrawRect(int x, int y, int width, int rectheight);
	// 绘制窗口文字（xy为0时文字在窗口左上角）
	void WDrawTexts(int x, int y, int width, int height, string content, int pos = 0, LONG size = 22, bool bond = false);
	// 绘制窗口图形（xy为0时文字在窗口左上角）
	void WindowBitmap(string file, int x, int y, int opacity = 255);
	void WindowBitmap(string file, int x, int y, int width, int height, int sx, int sy, int opacity = 255);
	// 获取普通文字色
	static COLORREF NormalColor();
	// 获取无效文字色
	static COLORREF DisabledColor();
	// 获取系统文字色
	static COLORREF SystemColor();
	// 获取危机文字色
	static COLORREF CrisisColor();
	// 获取文字色
	static COLORREF TextColor(string type);
	// 释放
	void Dispose();
};

/*
GameSelectWindow
处理带选择项窗口的类
*/
class GameSelectWindow :public GameWindow{
public:
	int Index;				// 当前选项
	int RectHeight;			// 矩形高度
	bool Active;			// 是否活动
	vector <string> Items;	// 项目数
	// 构造函数，初始化对象
	GameSelectWindow() {};
	GameSelectWindow(int rectheight, vector <string> item);
	// 刷新
	void Refresh();
	// 绘制项目
	void DrawItem(int index, COLORREF colour);
};

/*
GameActors
存储角色数据的结构体
*/
struct GameActors {
	string Name;		// 角色名
	string File;		// 角色图像文件名
	short Status;		// 状态
	short Level;		// 等级
	unsigned short Hp;	// 体力
	short Atk;			// 攻击
	short Def;			// 防御
	short Mdef;			// 魔法
	short BreathLimit;	// 气息上限
	short Breath;		// 气息
	short Exp;			// 经验
	short Gold;			// 金币
	short Item[99];		// 物品
	short MapID;		// 所处地图ID
	short X;			// 所在x坐标
	short Y;			// 所在y坐标
}; extern vector <GameActors> Actors;

/*
GamePlayer
处理目前操控角色的类
人物行走和步数变化的方法均在此类中
*/
class GamePlayer {
public:
	short Direction;	// 朝向
	short MovingCount;	// 移动计时
	bool Visible;		// 是否可视
	short Step;			// 步数
	// 更新（包含移动）
	void Update();
	// 改变步数
	void ChangeStep();
}; extern GamePlayer Player;

/*
GameEnemies
处理游戏敌人的类
可以确定敌人的各种能力、属性和伤害
*/
class GameEnemies {
public:
	string Name;			// 名称
	string File[2];			// 文件名
	vector <int> Element;	// 属性
	short Hp;				// 体力
	short Atk;				// 攻击
	short Def;				// 防御
	short Breath;			// 气息
	short Conatk;			// 连击
	short Exp;				// 经验
	short Gold;				// 金币
	short AnimationID;		// 动画编号
	// 重载小于号，用于排序
	const bool operator < (GameEnemies& en);
	// 获取伤害
	tuple <int, string> GotDamage();
	// 获取真实攻击
	int GotAtk();
	// 获取真实防御
	int GotDef();
	// 是否拥有某属性
	bool GotP(int p);
	// 获取临界
	int GotCrisis();
	// 获取文字属性及其描述
	pair <string, string> EnemyElement(int elementid);
}; extern vector <GameEnemies> Enemies;

/*
GameItem
存储物品数据的结构体
*/
struct GameItem {
	string Name;		// 名称
	string File;		// 文件名
	string Description;	// 描述
	short Price;		// 售价
	bool Usable;		// 是否可以使用
	bool Cost;			// 是否消耗
}; extern vector <GameItem> Item;

/*
GameAnimation
存储动画数据的结构体
*/
struct GameAnimation {
	vector <string> Pattern;	// 图像序列
	string SEFile;				// 音效名
	short SETime;					// 执行音效的帧数
}; extern vector <GameAnimation> Animation;

/*
SpriteAnimation
存储地图执行动画数据的结构体
*/
struct SpriteAnimation {
	short ActX;			// 动画x坐标
	short ActY;			// 动画y坐标
	short CurrentFrame;	// 目前执行到的帧数
	GameAnimation Type;	// 执行的动画
};

/*
SpriteDamage
存储伤害文字数据的结构体
*/
struct SpriteDamage {
	short ActX;			// 文字x坐标
	short ActY;			// 文字y坐标
	short CurrentFrame;	// 文字当前帧
	string Damage;		// 文字内容
	COLORREF Color;		// 文字色
};

/*
SpriteSetMap
处理地图画面活动的类
*/
class SpriteSetMap {
public:
	bool Active; // 是否活动
	// 构造函数，初始化对象
	SpriteSetMap();
	// 初始化变量
	void Initialization();
	// 状态栏
	void MapStatus();
	// 刷新
	void Update();
	// 释放
	void Dispose();
private:
	int ActorWidth;
	int ActorHeight;
	IMAGE* FloorImage;
	IMAGE* ActorImage;
	IMAGE* EventsImage[121][2];
	IMAGE* StatusImage;
};

/*
GameGraphics
处理地图画面活动、窗口更新和动画更新的类
动画分层为先开始的动画在最上层
如果要让先执行的动画在最下层，则将stack改为queue
*/
class GameGraphics {
public:
	vector <GameSprite*> Patterns;		// 精灵图形序列
	SpriteSetMap MapPatterns;			// 地图活动块
	vector <GameWindow*> Windows;		// 窗口序列
	stack <SpriteAnimation> Animations;	// 动画序列（存在栈中）
	stack <SpriteDamage> Damages;		// 文字序列（存在栈中）
	// 更新
	void Update();
	// 释放，清除画面
	void Dispose();
}; extern GameGraphics Graphics;
