#pragma once

#include "stdafx.h"

#ifndef __Basic_H__
#define __Basic_H__

/*
���ƴ��ھ��Σ��������ھ��κ�ѡ����Σ�
backx		���α�������x����
backy		���α�������y����
cornerx		�����ĸ�������x����
cornery		�����ĸ�������y����
sidex		��������������x����
sidey		��������������y����
backlen		���α�������
cornerlen	���νǳ���
sidelen		���α߳���
opacity		��͸����
drawx		���Ƶ�x����
drawy		���Ƶ�y����
drawwidth	���ƵĿ�
drawheight	���Ƶĸ�
select		�Ƿ��Ǵ�ѡ��Ĵ���
*/
void WindowRect(int backx, int backy, int cornerx[], int cornery[], int sidex[], int sidey[], int backlen, int cornerlen, int sidelen, int opacity, int drawx, int drawy, int drawwidth, int drawheight, bool select);

/*
��������
x		���Ƶ�x����
y		���Ƶ�y����
width	���Ƶ����־��ο��
height	���Ƶ����־��θ߶�
content	���Ƶ���������
pos		�����ھ����е�λ�ã�0 ���룻1 ���У�2 �ҿ��룻3���룬���һ���
size	�����ֺ�
bond	�Ƿ�Ӵ�
*/
void DrawTexts(int x, int y, int width, int height, string content, int pos = 0, LONG size = 22, bool bond = false);

// ���ƴ���Ӱ������
void DrawTextsBond(int x, int y, int width, int height, string content, int pos = 0, LONG size = 22, bool bond = false);

// ������Ч
void PlaySE(string file);

// ���ű�������
void PlayBGM(string file);

#endif

extern HWND GameActive;
extern LOGFONT Font;

// ���г�����Ļ��࣬���������麯��
class SceneBase {
public:
	virtual void Main() = 0;
};

/*
GameEvent
�����¼�����
ͨ��������Ի�ȡ�¼������Լ������¼�����
*/
class GameEvent {
public:
	string Name;				// �¼���
	string File[2];				// �¼�ͼ��
	short X;					// �¼�x����
	short Y;					// �¼�y����
	short TriggerCondition[3];	// �¼��ĳ��ִ�����������һ�1 ���س��֣�2���������֣�3 ���ؿ�ִ�У�4 ������ִ�У��ڶ�����ػ������ţ���������ػ�����������ֵ
	bool Exist;					// �¼��Ƿ񻹴���
	bool Through;				// �¼��Ƿ�ɴ�͸
	//���캯������ʼ������
	GameEvent();
	GameEvent(int x, int y);
	// �ж����¼��Ƿ���ȣ����ڲ�ѯ�¼�����ȵ�������xy������ͬ
	const bool operator == (const GameEvent& ev);
	// �¼�ִ�еĲ���
	void Order();
	// ����
	void OpenDoor();
};

/*
DataMap
�����ͼ���ݵ���
ͨ��������Ի�ȡ��ͼ���Ժ͵�ͼ�е��¼�
�����ж����¼����Ƿ��ͨ�С��Ƿ������Լ��ȴ�����Ϊ��̬�����蹹�����󼴿ɵ���
*/
class DataMap {
public:
	string MapName;								// ��ͼ��
	string FloorName;							// �ذ��ļ���
	vector <GameEvent> MapEvents;				// ��ͼ���¼�
	// �ж�����ͼ�Ƿ���ȣ���ȵ������ǵ�ͼ����ͬ
	const bool operator == (const DataMap& mp);
	// ��(x,y)���Ƿ�����¼�
	bool HaveAnEvent(int x, int y);
	// ��(x,y)���Ƿ�����¼�������ȥ��Ҳ�᷵�أ�
	bool HaveAnEEvent(int x, int y);
	// ������(x,y)�����¼����
	int CheckEvent(int x, int y);
	// ������(x,y)�����¼�ָ��
	GameEvent* ECheckEvent(int x, int y);
	// ָ��id�¼���λ��
	pair <int, int> HeAt(int id);
	// �ж���(x,y)���Ƿ����ͨ��
	bool Passible(int x, int y);
	// �ж����¼����Ƿ����ͨ��
	static bool HaveEventsAlong(pair <int, int> ev1, pair <int, int> ev2);
	// �ж����¼��Ƿ�����
	static bool Beside(pair <int, int> ev1, pair <int, int> ev2);
	// �ȴ�����λ֡��
	static void WaitCount(int times);
};

/*
DataSystem
������Ϸ���ݵ���
���Ա��������ص���Ϸ����
��ȡ���ݡ����¼������ݡ���ʼ�����ڴ�����
*/
class DataSystem {
public:
	map <int, vector<int> > FloorRecord;	// ��¼ȥ����¥��
	vector <DataMap> Maps;					// ���е�ͼ
	SceneBase* Scene;						// �¼�����
	IMAGE *TransitionGraphic;				// ׼������
	unsigned int GameTime = 0;				// ��Ϸʱ��
	short MessagePos;						// ����λ��
	short FrameRate;						// ˢ��Ƶ�ʣ���λms
	short WindowOpacity;					// ���ڵĲ�͸����
	short MapX;								// ��ͼ����Ϸ���ڵ�X����
	short MapY;								// ��ͼ����Ϸ���ڵ�Y����
	short BattleEnemyID;					// ���ڽ��е�ս���е���ID
	short FunctioningEventID;				// ���ڴ�����¼�ID
	short ShopType;							// �̵�����
	short ShopID;							// �̵���
	short TransitionOpacity;				// ���ɲ�͸����
	int GameVariables[5000];				// ����
	short ShopPrice[3];						// �̵�۸�
	short ShopEXP[4];						// �̵꾭��
	bool NeedRefresh;						// �Ƿ���Ҫˢ�µ�ͼ��ˢ�½������¼���ͼ��
	bool ScreenShot;						// �Ƿ���Ļ��ͼ
	bool DirectlyFunction;					// �¼��������Ƿ�ֱ��ִ��
	bool EndGame;							// ��Ϸ����
	bool FirstArrive;						// �״�������ͼ
	bool Transition;						// ���ɱ�־
	bool GameSwitches[5000];				// ����
	bool ItemRecord[99];					// ��ȡ��Ʒ��¼
	bool GemRecord[99][99];					// ��ȡ��ʯ��¼
	bool BottleRecord[999];					// ��ȡѪƿ��¼
	bool Victory;							// ����
	string WindowskinName;					// �����ļ���
	string TitleName;						// �����ļ���
	string FontName;						// ������
	string GameBGM;							// ��Ϸ��������
	string CursorSE;						// ѡ����Ч
	string DecisionSE;						// ȷ����Ч
	string CancelSE;						// ȡ����Ч
	string BuzzerSE;						// ������Ч
	string ShopSE;							// �̵���Ч
	string SaveSE;							// �浵��Ч
	string LoadSE;							// ������Ч
	string GateSE;							// ������Ч
	string GetSE;							// ��ȡ������Ч
	string StairSE;							// ����¥��Ч
	string MoveSE;							// �ƶ���Ч
	string ShotFile;						// ��Ļ��ͼ�ļ���
	string TransformingEventName;			// �¼�������ı��Ϊ������
	vector <string> MessageName;			// ������ʾ�Ľ�ɫ��
	vector <string> MessageContent;			// ������ʾ������
	vector <int> MessageHead;				// ������ʾ���¼�ID
	// ��ȡ����
	void DataLoad();
	// ��Ϸ�����ʼ��
	void Initialization();
	// ���¼�������
	void Reload();
	void ReadyTransition();
	void DoTransition(int time = 8);
}; extern DataSystem System;

/*
GameSprite
������Ϸ�������
ͨ��������Ի�ȡ������������
*/
class GameSprite {
public:
	string Name;						// ���ص�ͼƬ�ļ���
	short X;							// x����
	short Y;							// y����
	short Z;							// z����
	short Width;						// ��Ƭ��0Ϊ����Ƭ��
	short Height;						// ��Ƭ�ߣ�0Ϊ����Ƭ��
	short SrcX;							// ��Ƭ��ԭͼ�е�x����
	short SrcY;							// ��Ƭ��ԭͼ�е�y����
	short Angle;						// ��ת��
	short Position;						// ����ԭ�㣨0����1���У�
	short Opacity;						// ��͸����
	bool Visible;						// �Ƿ����
	IMAGE* Image;						// IMAGEָ��
	// ���캯������ʼ������
	GameSprite();
	GameSprite(string name);
	GameSprite(string name, int opacity);
	GameSprite(string name, int x, int y, int opacity);
	// ��þ�����
	int SpriteWidth();
	// ��þ���߶�
	int SpriteHeight();
	// �ı侫��ͼƬ�ļ���
	void ChangeImage(string name);
	// ���뵽Graphics������
	void AddIn();
	// �ͷ�
	void Dispose();
};

/*
GameKeyBoard
������Ϸ��������
*/
class GameKeyBoard {
public:
	// ȫ���̰����б�
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
	// ���������������ж��Ƿ�˫����
	int hit_times = 0;
	// �ᰴ
	bool LPress(int key);
	// ����
	bool Press(int key);
	// ���°���
	bool Repeat(int key);
	// ��ס
	bool Trigger(int key);
	// ����ȷ��
	bool PressConfirm();
	// ���°���ȷ��
	bool RepeatConfirm();
	// ��סȷ��
	bool TriggerConfirm();
	// ����ȡ��
	bool PressCancel();
	// ���°���ȡ��
	bool RepeatCancel();
	// ��סȡ��
	bool TriggerCancel();
	// ˫��
	bool DoubleClick(int key);
	// �ķ����ж�
	int Dir4();
private:
	map <int, int> key_hash, key_repeat, double_click;
}; extern GameKeyBoard KeyBoard;

/*
GameWindow
������Ϸ���ڵĻ��࣬�������麯��Refresh
ͨ��������Ի�ȡ�������ԣ����ƾ����Լ��ڴ�����������ֺ�ͼ��
*/
class GameWindow {
public:
	short X;					// ����x����
	short Y;					// ����y����
	short Z;					// ����z����
	short Width;				// ���ڿ�
	short Height;				// ���ڸ�
	short Opacity;				// ���ڲ�͸����
	bool HasFunction;			// �Ƿ��й��ܣ�Ϊtrue����Զ�ִ��Refresh������
	bool Visible;				// �Ƿ����
	virtual void Refresh() = 0;	// ˢ�£����麯����
	// ���캯������ʼ������
	GameWindow();
	GameWindow(int x, int y, int width, int height, int opacity = System.WindowOpacity);
	// ���ƾ���
	void DrawRect(int x, int y, int width, int rectheight);
	// ���ƴ������֣�xyΪ0ʱ�����ڴ������Ͻǣ�
	void WDrawTexts(int x, int y, int width, int height, string content, int pos = 0, LONG size = 22, bool bond = false);
	// ���ƴ���ͼ�Σ�xyΪ0ʱ�����ڴ������Ͻǣ�
	void WindowBitmap(string file, int x, int y, int opacity = 255);
	void WindowBitmap(string file, int x, int y, int width, int height, int sx, int sy, int opacity = 255);
	// ��ȡ��ͨ����ɫ
	static COLORREF NormalColor();
	// ��ȡ��Ч����ɫ
	static COLORREF DisabledColor();
	// ��ȡϵͳ����ɫ
	static COLORREF SystemColor();
	// ��ȡΣ������ɫ
	static COLORREF CrisisColor();
	// ��ȡ����ɫ
	static COLORREF TextColor(string type);
	// �ͷ�
	void Dispose();
};

/*
GameSelectWindow
�����ѡ����ڵ���
*/
class GameSelectWindow :public GameWindow{
public:
	int Index;				// ��ǰѡ��
	int RectHeight;			// ���θ߶�
	bool Active;			// �Ƿ�
	vector <string> Items;	// ��Ŀ��
	// ���캯������ʼ������
	GameSelectWindow() {};
	GameSelectWindow(int rectheight, vector <string> item);
	// ˢ��
	void Refresh();
	// ������Ŀ
	void DrawItem(int index, COLORREF colour);
};

/*
GameActors
�洢��ɫ���ݵĽṹ��
*/
struct GameActors {
	string Name;		// ��ɫ��
	string File;		// ��ɫͼ���ļ���
	short Status;		// ״̬
	short Level;		// �ȼ�
	unsigned short Hp;	// ����
	short Atk;			// ����
	short Def;			// ����
	short Mdef;			// ħ��
	short BreathLimit;	// ��Ϣ����
	short Breath;		// ��Ϣ
	short Exp;			// ����
	short Gold;			// ���
	short Item[99];		// ��Ʒ
	short MapID;		// ������ͼID
	short X;			// ����x����
	short Y;			// ����y����
}; extern vector <GameActors> Actors;

/*
GamePlayer
����Ŀǰ�ٿؽ�ɫ����
�������ߺͲ����仯�ķ������ڴ�����
*/
class GamePlayer {
public:
	short Direction;	// ����
	short MovingCount;	// �ƶ���ʱ
	bool Visible;		// �Ƿ����
	short Step;			// ����
	// ���£������ƶ���
	void Update();
	// �ı䲽��
	void ChangeStep();
}; extern GamePlayer Player;

/*
GameEnemies
������Ϸ���˵���
����ȷ�����˵ĸ������������Ժ��˺�
*/
class GameEnemies {
public:
	string Name;			// ����
	string File[2];			// �ļ���
	vector <int> Element;	// ����
	short Hp;				// ����
	short Atk;				// ����
	short Def;				// ����
	short Breath;			// ��Ϣ
	short Conatk;			// ����
	short Exp;				// ����
	short Gold;				// ���
	short AnimationID;		// �������
	// ����С�ںţ���������
	const bool operator < (GameEnemies& en);
	// ��ȡ�˺�
	tuple <int, string> GotDamage();
	// ��ȡ��ʵ����
	int GotAtk();
	// ��ȡ��ʵ����
	int GotDef();
	// �Ƿ�ӵ��ĳ����
	bool GotP(int p);
	// ��ȡ�ٽ�
	int GotCrisis();
	// ��ȡ�������Լ�������
	pair <string, string> EnemyElement(int elementid);
}; extern vector <GameEnemies> Enemies;

/*
GameItem
�洢��Ʒ���ݵĽṹ��
*/
struct GameItem {
	string Name;		// ����
	string File;		// �ļ���
	string Description;	// ����
	short Price;		// �ۼ�
	bool Usable;		// �Ƿ����ʹ��
	bool Cost;			// �Ƿ�����
}; extern vector <GameItem> Item;

/*
GameAnimation
�洢�������ݵĽṹ��
*/
struct GameAnimation {
	vector <string> Pattern;	// ͼ������
	string SEFile;				// ��Ч��
	short SETime;					// ִ����Ч��֡��
}; extern vector <GameAnimation> Animation;

/*
SpriteAnimation
�洢��ͼִ�ж������ݵĽṹ��
*/
struct SpriteAnimation {
	short ActX;			// ����x����
	short ActY;			// ����y����
	short CurrentFrame;	// Ŀǰִ�е���֡��
	GameAnimation Type;	// ִ�еĶ���
};

/*
SpriteDamage
�洢�˺��������ݵĽṹ��
*/
struct SpriteDamage {
	short ActX;			// ����x����
	short ActY;			// ����y����
	short CurrentFrame;	// ���ֵ�ǰ֡
	string Damage;		// ��������
	COLORREF Color;		// ����ɫ
};

/*
SpriteSetMap
�����ͼ��������
*/
class SpriteSetMap {
public:
	bool Active; // �Ƿ�
	// ���캯������ʼ������
	SpriteSetMap();
	// ��ʼ������
	void Initialization();
	// ״̬��
	void MapStatus();
	// ˢ��
	void Update();
	// �ͷ�
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
�����ͼ���������ڸ��ºͶ������µ���
�����ֲ�Ϊ�ȿ�ʼ�Ķ��������ϲ�
���Ҫ����ִ�еĶ��������²㣬��stack��Ϊqueue
*/
class GameGraphics {
public:
	vector <GameSprite*> Patterns;		// ����ͼ������
	SpriteSetMap MapPatterns;			// ��ͼ���
	vector <GameWindow*> Windows;		// ��������
	stack <SpriteAnimation> Animations;	// �������У�����ջ�У�
	stack <SpriteDamage> Damages;		// �������У�����ջ�У�
	// ����
	void Update();
	// �ͷţ��������
	void Dispose();
}; extern GameGraphics Graphics;
