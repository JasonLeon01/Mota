#include "Basic.h"

/*
WindowScript
处理游戏剧本的类
*/
class WindowScript :public GameWindow {
public:
	int PicOpacity; // 图片不透明度
	// 构造函数，初始化对象
	WindowScript(int x, int y);
	// 刷新
	void Refresh();
};

/*
WindowHint
处理游戏提示的类
*/
class WindowHint :public GameWindow {
public:
	int Page; // 页数
	// 构造函数，初始化对象
	WindowHint(int x, int y);
	// 刷新
	void Refresh();
};

/*
WindowMonsterBook
处理怪物手册的类
*/
class WindowMonsterBook :public GameWindow {
public:
	int Index;					// 选项
	int Page;					// 页数
	vector <int> FloorEnemies;	// 当前层敌人序列
	// 构造函数，初始化对象
	WindowMonsterBook(int x, int y);
	// 刷新
	void Refresh();
private:
	int MaxPage;
};

/*
WindowEncyclopedia
处理怪物详细信息的类
*/
class WindowEncyclopedia :public GameWindow {
public:
	int eid; // 敌人id
	// 构造函数，初始化对象
	WindowEncyclopedia(int x, int y);
	// 刷新
	void Refresh();
};

/*
WindowMessage
处理对话窗口的类
*/
class WindowMessage :public GameWindow {
public:
	// 构造函数，初始化对象
	WindowMessage(int x, int y);
	// 刷新
	void Refresh();
};

/*
WindowGoldShop
处理金币商店的类
*/
class WindowGoldShop :public GameWindow {
public:
	int ShopID;	// 商店id
	int Index;	// 选项
	// 构造函数，初始化对象
	WindowGoldShop(int x, int y);
	// 刷新
	void Refresh();
};

/*
WindowEXPShop
处理经验商店的类
*/
class WindowEXPShop :public GameWindow {
public:
	int ShopID;	// 商店id
	int Index;	// 选项
	// 构造函数，初始化对象
	WindowEXPShop(int x, int y);
	// 刷新
	void Refresh();
};

/*
WindowKeyShop
处理钥匙商店的类
*/
class WindowKeyShop :public GameWindow {
public:
	int Index; // 选项
	// 构造函数，初始化对象
	WindowKeyShop(int x, int y);
	// 刷新
	void Refresh();
};

/*
WindowSDOORShop
处理随意门商店的类
*/
class WindowSDOORShop :public GameWindow {
public:
	int Index; // 选项
	// 构造函数，初始化对象
	WindowSDOORShop(int x, int y);
	// 刷新
	void Refresh();
};

/*
WindowRECYShop
处理回收钥匙的类
*/
class WindowRECYShop :public GameWindow {
public:
	int Index; // 选项
	// 构造函数，初始化对象
	WindowRECYShop(int x, int y);
	// 刷新
	void Refresh();
};

/*
WindowSkill
处理攻击魔术/剑技的类
*/
class WindowSkill :public GameWindow {
public:
	int Index; // 选项
	// 构造函数，初始化对象
	WindowSkill(int x, int y);
	// 刷新
	void Refresh();
};

/*
WindowDefense
处理防御魔术/防御术的类
*/
class WindowDefense :public GameWindow {
public:
	int Index; // 选项
	// 构造函数，初始化对象
	WindowDefense(int x, int y);
	// 刷新
	void Refresh();
};

/*
WindowDrug
处理药品道具袋的类
*/
class WindowDrug :public GameWindow {
public:
	int Index; // 选项
	// 构造函数，初始化对象
	WindowDrug(int x, int y);
	// 刷新
	void Refresh();
};

/*
WindowBattle
处理战斗窗口的类
*/
class WindowBattle :public GameWindow {
public:
	int aAtk;			// 我方攻击
	int aDef;			// 我方防御
	int aMdef;			// 我方魔法
	int aFatigue;		// 我方疲劳
	int eHp;			// 敌方体力
	int eAtk;			// 敌方攻击
	int eDef;			// 敌方防御
	int eFatigue;		// 敌方疲劳
	int eBreath;		// 敌方气息
	int funckey;		// 执行的功能
	int sword;			// 二连击剩余次数
	int defense;		// 防御剩余次数
	bool Accelerate;	// 加速战斗
	// 构造函数，初始化对象
	WindowBattle(int x, int y);
	// 刷新
	void Refresh();
};

/*
WindowFloorFly
处理楼层传送器的类
*/
class WindowFloorFly :public GameWindow {
public:
	int viewfloorid;	// 当前楼层编号
	int viewmapid;		// 当前地图编号
	bool update;		// 是否更新
	// 构造函数，初始化对象
	WindowFloorFly(int x, int y);
	// 刷新
	void Refresh();
	// 清除图形指针
	void Delete();
private:
	IMAGE *events[121][2];
	IMAGE *floor;
};

/*
WindowFileImage
处理显示存档画面的类
*/
class WindowFileImage :public GameWindow {
public:
	int fileid; // 存档id
	// 构造函数，初始化对象
	WindowFileImage(int x, int y);
	// 刷新
	void Refresh();
};

/*
WindowFileCursor
处理显示存档序号窗口的类
*/
class WindowFileCursor :public GameWindow {
public:
	int Index;				// 当前选项
	int Page;				// 页数
	int RectHeight;			// 矩形高度
	bool Active;			// 是否活动
	bool load;				// 是否是读档
	vector <string> Items;	// 项目序列
	// 构造函数，初始化对象
	WindowFileCursor(int x, int y, int rectheight, vector <string> item);
	// 刷新
	void Refresh();
	// 绘制项目
	void DrawItem(int index, COLORREF colour);
};

/*
GameTitle
处理标题画面的类
*/
class GameTitle :public SceneBase {
public:
	// 主函数
	void Main();
	// 更新画面
	void Update();
	void CommandNewGame();
	void CommandContinue();
	void CommandBackground();
	void CommandExit();
private:
	int siz;
	GameSprite sprite;
	GameSprite weather[250];
	GameSprite title;
	GameSelectWindow window = GameSelectWindow(32, { "新游戏", "继续", "背景概要", "退出游戏" });
	WindowFileImage filewindow = WindowFileImage(32, 256);
	WindowFileCursor cursorwindow = WindowFileCursor(216, 256, 20, { "", "", "", "", "", "" });
};

/*
GameIntro
处理背景概要画面的类
*/
class GameIntro :public SceneBase {
public:
	// 主函数
	void Main();
	// 更新画面
	void Update();
private:
	GameSprite sprite, floor, script;
};

/*
GameStart
处理开始游戏画面的类
*/
class GameStart :public SceneBase {
public:
	// 主函数
	void Main();
	// 更新画面
	void Update();
private:
	GameSprite sprite;
	WindowScript scriptwindow = WindowScript(32, 32);
};

/*
GameMap
处理游戏地图的类
*/
class GameMap :public SceneBase {
public:
	// 主函数
	void Main();
	// 更新画面
	void Update();
	// 读档
	static void LoadData(int fileid);
	// 存档
	static void SaveData(int fileid);
private:
	string record = "";
	GameSprite sprite;
	WindowHint hintwindow = WindowHint(System.MapX, System.MapY);
	WindowMessage messagewindow = WindowMessage(System.MapX + 64, System.MapY + 192);
	WindowMonsterBook monsterbookwindow = WindowMonsterBook(System.MapX, System.MapY);
	WindowEncyclopedia encyclopediawindow = WindowEncyclopedia(System.MapX, System.MapY);
	WindowBattle battlewindow = WindowBattle(System.MapX - 16, System.MapY + 48);
	WindowGoldShop goldshopwindow = WindowGoldShop(System.MapX + 64, System.MapY + 32);
	WindowEXPShop expshopwindow = WindowEXPShop(System.MapX + 64, System.MapY + 32);
	WindowKeyShop keyshopwindow = WindowKeyShop(System.MapX + 64, System.MapY + 32);
	WindowSDOORShop sdoorshopwindow = WindowSDOORShop(System.MapX + 64, System.MapY + 32);
	WindowRECYShop recyshopwindow = WindowRECYShop(System.MapX + 64, System.MapY + 32);
	WindowSkill skillwindow = WindowSkill(System.MapX + 16, System.MapY + 96);
	WindowDefense defensewindow = WindowDefense(System.MapX + 16, System.MapY + 96);
	WindowDrug drugwindow = WindowDrug(System.MapX + 48, System.MapY + 128);
	WindowFloorFly flywindow = WindowFloorFly(System.MapX + 96, System.MapY + 96);
	WindowFileImage filewindow = WindowFileImage(System.MapX + 16, System.MapY + 88);
	WindowFileCursor cursorwindow = WindowFileCursor(System.MapX + 200, System.MapY + 88, 20, { "", "", "", "", "", "" });
	void ShortcutKey();
	void MessageUpdate();
	int BattleUpdate();
	void GameOver();
	void MonsterBookUpdate();
	void FileUpdate();
	void ShopUpdate();
	void BattleFunction();
};

class GameEnd :public SceneBase {
public:
	void Main();
	void Update();
private:
	GameSprite script1, script2, mark1, mark2, shot[10], weather[200];
	int time, index;
	bool pass1, pass2, pass3, pass4, pass5;
};

/*
main
各声明结束后，从这里开始实际处理
*/
int main() {
	initgraph(608, 448);
	BeginBatchDraw();
	System.Initialization();
	GameSprite post("mting-0.png");
	post.X = 0;
	post.Y = 95;
	post.Opacity = 0;
	rfor(i, 0, 17) {
		Graphics.Update();
		post.Opacity += 15;
	}
	rfor(i, 0, 10) {
		Graphics.Update();
	}
	post.Dispose();
	System.Scene = new GameTitle;
	System.ReadyTransition();
	while (System.Scene != nullptr) {
		System.Scene->Main();
	}
	System.DoTransition();
	Graphics.Dispose();
	EndBatchDraw();
	closegraph();
	return 0;
}

WindowScript::WindowScript(int x, int y) {
	X = x;
	Y = y;
	Z = 0;
	Width = 544;
	Height = 352;
	Opacity = 255;
	HasFunction = true;
	Visible = true;
	Graphics.Windows.push_back(this);
}

void WindowScript::Refresh() {
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID, 2);
	WindowBitmap("001-Floor01.png", 0, 0, Width, Height, 0, 0, 255);
	rectangle(X, Y, X + Width, Y + Height);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	WindowBitmap("mting-1281.png", 16, 16, min(PicOpacity, 255));
}

WindowHint::WindowHint(int x, int y) {
	X = x;
	Y = y;
	Z = 0;
	Width = 352;
	Height = 352;
	Opacity = 255;
	HasFunction = true;
	Visible = false;
	Page = 0;
	Graphics.Windows.push_back(this);
}

void WindowHint::Refresh() {
	if (!Visible) {
		return;
	}
	vector <string> ss;
	if (Actors[System.GameVariables[1]].Item[3] > 0) {
		ss.push_back("d=查看怪物能力");
	}
	if (Actors[System.GameVariables[1]].Item[4] > 0) {
		ss.push_back("f=使用银灰色飞羽");
	}
	if (Actors[System.GameVariables[1]].Item[5] > 0) {
		ss.push_back("t=使用随意门");
	}
	if (System.GameSwitches[12]) {
		ss.push_back("w=选择攻击魔术/剑技");
		ss.push_back("z=使用攻击魔术/剑技");
	}
	if (System.GameSwitches[13]) {
		ss.push_back("h=选择防御魔术/防御术");
		ss.push_back("x=使用防御魔术/防御术");
	}
	if (System.GameSwitches[15]) {
		ss.push_back("u=切换操作对象");
	}
	if (Actors[System.GameVariables[1]].Item[15] > 0) {
		ss.push_back("b=使用道具袋");
	}
	if (Page == 0) {
		WDrawTexts(0, 0, 320, 32, "enter/space=确定", 0, 20L);
		WDrawTexts(0, 20, 320, 32, "↑↓←→=控制角色移动/选择物品", 0, 20L);
		WDrawTexts(0, 40, 320, 32, "s=打开/关闭背景音乐", 0, 20L);
		WDrawTexts(0, 60, 320, 32, "space=加速战斗（战斗中使用）", 0, 20L);
		WDrawTexts(0, 80, 320, 32, "v=呼吸减少疲劳（战斗中使用）", 0, 20L);
		WDrawTexts(0, 100, 320, 32, "r=重新开始", 0, 20L);
		WDrawTexts(0, 120, 320, 32, "u=保存进度", 0, 20L);
		WDrawTexts(0, 140, 320, 32, "i=载入进度", 0, 20L);
		WDrawTexts(0, 160, 320, 32, "q=撤退（战斗中使用）", 0, 20L);
		WDrawTexts(0, 180, 320, 32, "左ctrl×2=快速储存（时间距离最近的存档）", 0, 20L);
		WDrawTexts(0, 200, 320, 32, "右ctrl×2=快速读取（时间距离最近的存档）", 0, 20L);
		rfor(i, 0, min(ss.size(), 5)) {
			WDrawTexts(0, 220 + 20 * i, 320, 32, ss[i], 0, 20L);
		}
	}
	else {
		rfor(i, 0, ss.size() - 5) {
			WDrawTexts(0, 20 * i, 320, 32, ss[6 + i], 0, 20L);
		}
	}
	if (Page == 0) {
		WindowBitmap("mting-1427.png", Width - 32, Height - 16, 16, 16, 0, 0);
	}
	else {
		WindowBitmap("mting-1427.png", Width - 32, Height - 16, 16, 16, 16, 0);
	}
	if (Page < (8 + ss.size()) / 16) {
		WindowBitmap("mting-1427.png", Width - 16, Height - 16, 16, 16, 48, 0);
	}
	else {
		WindowBitmap("mting-1427.png", Width - 16, Height - 16, 16, 16, 32, 0);
	}
	if (KeyBoard.TriggerConfirm() || KeyBoard.TriggerCancel()) {
		Visible = false;
		return;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyLEFT)) {
		if (Page > 0) {
			--Page;
			PlaySE(System.CursorSE);
		}
		return;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyRIGHT)) {
		if (Page < (8 + ss.size()) / 16) {
			++Page;
			PlaySE(System.CursorSE);
		}
		return;
	}
}

WindowMessage::WindowMessage(int x, int y) {
	X = x;
	Y = y;
	Z = 0;
	Width = 256;
	Height = 128;
	Opacity = 0;
	HasFunction = true;
	Visible = false;
	Graphics.Windows.push_back(this);
}

void WindowMessage::Refresh() {
	if (System.MessageName.empty()) {
		return;
	}
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID, 2);
	string name = *System.MessageName.begin();
	string content = *System.MessageContent.begin();
	int head = *System.MessageHead.begin();
	if (name != "") {
		X = System.MapX + 64;
		Y = System.MapY + 192;
		Width = 256;
		Height = 128;
		if (head >= 0) {
			Y = System.MapY + 32;
		}
		WindowBitmap("001-Floor01.png", 0, 0, Width, Height, 0, 0, 255);
		rectangle(X, Y, X + Width, Y + Height);
		if (head == -1) {
			WindowBitmap(Actors[System.GameVariables[1]].File, 8, 8, 32, 32, 0, 0, 255);
		}
		else {
			WindowBitmap(System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[head].File[(System.GameTime % 20) / 10], 8, 8, 255);
		}
		rectangle(X + 8, Y + 8, X + 40, Y + 40);
		WDrawTexts(48, 0, 160, 20, name, 1, 24L, true);
	}
	else {
		X = System.MapX - 48;
		Y = System.MapY + 160;
		Width = 416;
		Height = 32;
		WindowBitmap("001-Floor01.png", 0, 0, Width, Height, 0, 0, 255);
		rectangle(X, Y, X + Width, Y + Height);
	}
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	WDrawTexts(0, 32 * (name != "") - 8 * (name == ""), Width - 32, 64, content, 3, 20L);
}

WindowMonsterBook::WindowMonsterBook(int x, int y) {
	X = x;
	Y = y;
	Z = 0;
	Width = 352;
	Height = 352;
	Opacity = 255;
	HasFunction = true;
	Visible = false;
	Graphics.Windows.push_back(this);
}

void WindowMonsterBook::Refresh() {
	if (!Visible) {
		return;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyD) || KeyBoard.TriggerCancel()) {
		PlaySE(System.CancelSE);
		Visible = false;
		return;
	}
	if (FloorEnemies.empty()) {
		return;
	}
	MaxPage = FloorEnemies.size() / 5;
	if (FloorEnemies.size() / 5.0 != MaxPage) {
		++MaxPage;
	}
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID, 2);
	string ele1 = "", ele2 = "";
	rfor(i, 0, min(5, FloorEnemies.size() - 5 * Page)) {
		WindowBitmap(Enemies[FloorEnemies[Page * 5 + i]].File[(System.GameTime % 20) / 10], 16, 16 + 64 * i);
		WDrawTexts(0, 32 + 64 * i, 64, 32, Split(Enemies[FloorEnemies[Page * 5 + i]].Name, "|")[0], 3, 18L);
		rectangle(X + 16, Y + 16 + 64 * i, X + 48, Y + 48 + 64 * i);
		if (Enemies[FloorEnemies[Page * 5 + i]].Element.size() == 1) {
			ele1 = Enemies[FloorEnemies[Page * 5 + i]].EnemyElement(Enemies[FloorEnemies[Page * 5 + i]].Element[0]).first;
			ele2 = "";
		}
		else if (Enemies[FloorEnemies[Page * 5 + i]].Element.size() == 2) {
			ele1 = Enemies[FloorEnemies[Page * 5 + i]].EnemyElement(Enemies[FloorEnemies[Page * 5 + i]].Element[0]).first;
			ele2 = Enemies[FloorEnemies[Page * 5 + i]].EnemyElement(Enemies[FloorEnemies[Page * 5 + i]].Element[1]).first;
		}
		else if (Enemies[FloorEnemies[Page * 5 + i]].Element.size() >= 3) {
			ele1 = "详细…";
			ele2 = "";
		}
		WDrawTexts(32, 64 * i, 96, 16, ele1, 0, 18L);
		WDrawTexts(32, 64 * i + 16, 96, 16, ele2, 0, 18L);
		WDrawTexts(64, 64 * i, 96, 32, "体力：" + to_string(Enemies[FloorEnemies[Page * 5 + i]].Hp), 0, 20L);
		WDrawTexts(144, 64 * i, 96, 32, "攻击：" + to_string(Enemies[FloorEnemies[Page * 5 + i]].Atk), 0, 20L);
		WDrawTexts(224, 64 * i, 96, 32, "防御：" + to_string(Enemies[FloorEnemies[Page * 5 + i]].Def), 0, 20L);
		WDrawTexts(64, 20 + 64 * i, 96, 32, "气息：" + to_string(Enemies[FloorEnemies[Page * 5 + i]].Breath), 0, 20L);
		WDrawTexts(144, 20 + 64 * i, 96, 32, "连击：" + to_string(max(1, Enemies[FloorEnemies[Page * 5 + i]].Conatk)), 0, 20L);
		WDrawTexts(224, 20 + 64 * i, 96, 32, "伤害：" + get<1>(Enemies[FloorEnemies[Page * 5 + i]].GotDamage()), 0, 20L);
		WDrawTexts(64, 40 + 64 * i, 96, 32, "经验：" + to_string(Enemies[FloorEnemies[Page * 5 + i]].Exp), 0, 20L);
		WDrawTexts(144, 40 + 64 * i, 96, 32, "金币：" + to_string(Enemies[FloorEnemies[Page * 5 + i]].Gold), 0, 20L);
	}
	DrawRect(16, 16 + 64 * Index, Width - 32, 64);
	settextcolor(TextColor("green"));
	WDrawTexts(0, 300, 320, 20, "PAGE " + to_string(Page + 1) + "/" + to_string(MaxPage), 2, 20L);
	settextcolor(WHITE);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	if (KeyBoard.Press(KeyBoard.KeyLEFT)) {
		if (Page > 0) {
			--Page;
			Index = 0;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeyRIGHT)) {
		if (Page < MaxPage - 1) {
			++Page;
			Index = 0;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeyUP)) {
		if (Index > 0) {
			--Index;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeyDOWN)) {
		if (Index < min(5, FloorEnemies.size() - 5 * Page) - 1) {
			++Index;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
}

WindowEncyclopedia::WindowEncyclopedia(int x, int y) {
	X = x;
	Y = y;
	Z = 0;
	Width = 352;
	Height = 352;
	Opacity = 255;
	HasFunction = true;
	Visible = false;
	Graphics.Windows.push_back(this);
}

void WindowEncyclopedia::Refresh() {
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID, 2);
	WindowBitmap(Enemies[eid].File[(System.GameTime % 20) / 10], 128, 16);
	rectangle(X + 128, Y + 16, X + 160, Y + 48);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	WDrawTexts(160, 6, 128, 20, Split(Enemies[eid].Name, "|")[0], 0, 22L, true);
	WDrawTexts(0, 40, 128, 20, "体力:" + to_string(Enemies[eid].Hp), 0, 20L);
	WDrawTexts(85, 40, 128, 20, "攻击:" + to_string(Enemies[eid].Atk), 0, 20L);
	WDrawTexts(170, 40, 128, 20, "防御:" + to_string(Enemies[eid].Def), 0, 20L);
	WDrawTexts(255, 40, 128, 20, "气息:" + to_string(Enemies[eid].Breath), 0, 20L);
	WDrawTexts(0, 60, 128, 20, "经验:" + to_string(Enemies[eid].Exp), 0, 20L);
	WDrawTexts(85, 60, 128, 20, "金币:" + to_string(Enemies[eid].Gold), 0, 20L);
	WDrawTexts(170, 60, 128, 20, "临界:" + to_string(Enemies[eid].GotCrisis()), 0, 20L);
	WDrawTexts(255, 60, 128, 20, "伤害:" + get<1>(Enemies[eid].GotDamage()), 0, 20L);
	WDrawTexts(0, 100, 128, 20, "属性:", 0, 20L);
	rfor(i, 0, Enemies[eid].Element.size()) {
		WDrawTexts(0, 120 + 20 * i, 352, 60, Enemies[eid].EnemyElement(Enemies[eid].Element[i]).first, 0, 20L);
		WDrawTexts(48, 120 + 20 * i, 352, 60, Enemies[eid].EnemyElement(Enemies[eid].Element[i]).second, 0, 20L);
	}
}

WindowBattle::WindowBattle(int x, int y) {
	X = x;
	Y = y;
	Z = 0;
	Width = 384;
	Height = 224;
	Opacity = 0;
	HasFunction = true;
	Visible = false;
	Graphics.Windows.push_back(this);
}

void WindowBattle::Refresh() {
	if (System.BattleEnemyID < 0) {
		return;
	}
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID, 2);
	WindowBitmap("001-Floor01.png", 0, 0, Width, Height, 0, 0, 255);
	rectangle(X, Y, X + Width, Y + Height);
	rectangle(X + 32, Y + 32, X + 64, Y + 64);
	rectangle(X + Width - 64, Y + 32, X + Width - 32, Y + 64);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	WindowBitmap(Enemies[System.BattleEnemyID].File[(System.GameTime % 20) / 10], 32, 32);
	WindowBitmap(Actors[System.GameVariables[1]].File, Width - 64, 32, 32, 32, 0, 0);
	if (funckey == 2) {
		BitmapCentre("mting-1227.png", X + Width - 16, Y + 128);
	}
	else {
		BitmapCentre("mting-528.png", X + Width - 16, Y + 128);
	}
	if (funckey == 3 || funckey == 4 || funckey == 5 || sword) {
		BitmapCentre("mting-1227.png", X + Width - 40, Y + 128);
	}
	else {
		BitmapCentre("mting-1215.png", X + Width - 40, Y + 128);
	}
	if (funckey == 6 || funckey == 7 || funckey == 8 || defense) {
		BitmapCentre("mting-1227.png", X + Width - 64, Y + 128);
	}
	else {
		BitmapCentre("mting-1214.png", X + Width - 64, Y + 128);
	}
	WDrawTexts(16, -8, 96, 24, Split(Enemies[System.BattleEnemyID].Name, "|")[0], 1, 22L, true);
	WDrawTexts(64, 16, 64, 20, "体力:", 0, 20L);
	WDrawTexts(64, 40, 64, 20, "攻击力:", 0, 20L);
	WDrawTexts(64, 64, 64, 20, "防御力:", 0, 20L);
	WDrawTexts(64, 112, 64, 20, "疲劳:", 0, 20L);
	WDrawTexts(-8, 136, 64, 20, "气息:", 0, 20L);
	WDrawTexts(Width - 112, -8, 96, 24, _T(Actors[System.GameVariables[1]].Name), 1, 22L, true);
	WDrawTexts(Width - 160, 16, 64, 24, ":体力", 2, 20L);
	WDrawTexts(Width - 160, 40, 64, 24, ":攻击力", 2, 20L);
	WDrawTexts(Width - 160, 64, 64, 24, ":防御力", 2, 20L);
	WDrawTexts(Width - 160, 88, 64, 24, ":魔力", 2, 20L);
	WDrawTexts(Width - 160, 112, 64, 24, ":疲劳", 2, 20L);
	WDrawTexts(Width - 160, 136, 64, 24, "气息:", 2, 20L);
	settextcolor(YELLOW);
	WDrawTexts(-8, 176, 128, 24, "～撤退(Q)～", 0, 22L, true);
	settextcolor(WHITE);
	WDrawTexts(112, 16, 64, 20, to_string(eHp), 0, 20L);
	WDrawTexts(112, 40, 64, 20, to_string(eAtk), 0, 20L);
	WDrawTexts(112, 64, 64, 20, to_string(eDef), 0, 20L);
	WDrawTexts(112, 112, 64, 20, to_string(eFatigue), 0, 20L);
	WDrawTexts(Width - 208, 16, 64, 24, to_string(Actors[System.GameVariables[1]].Hp), 2, 20L);
	WDrawTexts(Width - 208, 40, 64, 24, to_string(aAtk), 2, 20L);
	WDrawTexts(Width - 208, 64, 64, 24, to_string(aDef), 2, 20L);
	WDrawTexts(Width - 208, 88, 64, 24, to_string(aMdef), 2, 20L);
	WDrawTexts(Width - 208, 112, 64, 24, to_string(aFatigue), 2, 20L);
	IMAGE* rect = new IMAGE, *rect2 = new IMAGE;
	loadimage(rect, "res\\picture\\mting-1226.png", 80, 16);
	loadimage(rect2, "res\\picture\\mting-1226.png");
	OpaqueImage(nullptr, X + 48, Y + 160, 80, 8, 0, 0, rect);
	OpaqueImage(nullptr, X + 48, Y + 160, eBreath * 80 / Enemies[System.BattleEnemyID].Breath, 8, 0, 8, rect);
	OpaqueImage(nullptr, X + Width - 80, Y + 160, 80, 4, 0, 0, rect2);
	OpaqueImage(nullptr, X + Width - 80, Y + 160, Actors[System.GameVariables[1]].Breath % (Actors[System.GameVariables[1]].BreathLimit / 6) * 80 / (Actors[System.GameVariables[1]].BreathLimit / 6), 4, 0, 4, rect2);
	string breathfile1[] = { "mting-1211.png", "mting-1212.png", "mting-1213.png" };
	string breathfile2[] = { "mting-1211_g.png", "mting-1212_g.png", "mting-1213_g.png" };
	rfor(i, 0, 5) {
		switch ((System.GameTime % 30) / 10) {
		case 0: WindowBitmap(Actors[System.GameVariables[1]].Breath >= floor(Actors[System.GameVariables[1]].BreathLimit / 6) * (i + 1) ? breathfile1[0] : breathfile2[0], Width - 80 + 14 * i, 145); break;
		case 1: WindowBitmap(Actors[System.GameVariables[1]].Breath >= floor(Actors[System.GameVariables[1]].BreathLimit / 6) * (i + 1) ? breathfile1[1] : breathfile2[1], Width - 79 + 14 * i, 144); break;
		case 2: WindowBitmap(Actors[System.GameVariables[1]].Breath >= floor(Actors[System.GameVariables[1]].BreathLimit / 6) * (i + 1) ? breathfile1[2] : breathfile2[2], Width - 79 + 14 * i, 144); break;
		}
	}
	delete rect;
	delete rect2;
	if (KeyBoard.Trigger(KeyBoard.KeyV) && Actors[System.GameVariables[1]].Breath >= Actors[System.GameVariables[1]].BreathLimit / 6) {
		Actors[System.GameVariables[1]].Breath -= Actors[System.GameVariables[1]].BreathLimit / 6;
		if (Actors[System.GameVariables[1]].Level >= 80) {
			aFatigue = max(0, aFatigue - 20);
		}
		else if (Actors[System.GameVariables[1]].Level >= 70) {
			aFatigue = max(0, aFatigue - 18);
		}
		else if (Actors[System.GameVariables[1]].Level >= 60) {
			aFatigue = max(0, aFatigue - 16);
		}
		else if (Actors[System.GameVariables[1]].Level >= 50) {
			aFatigue = max(0, aFatigue - 14);
		}
		else if (Actors[System.GameVariables[1]].Level >= 40) {
			aFatigue = max(0, aFatigue - 12);
		}
		else if (Actors[System.GameVariables[1]].Level >= 30) {
			aFatigue = max(0, aFatigue - 10);
		}
		else if (Actors[System.GameVariables[1]].Level >= 20) {
			aFatigue = max(0, aFatigue - 8);
		}
		else if (Actors[System.GameVariables[1]].Level >= 10) {
			aFatigue = max(0, aFatigue - 6);
		}
		else {
			aFatigue = max(0, aFatigue - 4);
		}
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeyQ) && funckey == 0) {
		funckey = 1;
		return;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyC) && funckey == 0 && Actors[System.GameVariables[1]].Breath >= Actors[System.GameVariables[1]].BreathLimit / 6) {
		funckey = 2;
		return;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyZ) && funckey == 0) {
		if (System.GameVariables[1] == 0) {
			if (Actors[System.GameVariables[1]].Breath >= Actors[System.GameVariables[1]].BreathLimit / 6 && System.GameVariables[20] == 6) {
				funckey = 3;
			}
			if (Actors[System.GameVariables[1]].Breath >= Actors[System.GameVariables[1]].BreathLimit / 6 && System.GameVariables[20] == 7) {
				funckey = 4;
			}
			if (Actors[System.GameVariables[1]].Breath >= Actors[System.GameVariables[1]].BreathLimit / 3 && System.GameVariables[20] == 8) {
				funckey = 5;
			}
		}
		else {
			if (Actors[System.GameVariables[1]].Breath >= Actors[System.GameVariables[1]].BreathLimit / 3 && System.GameVariables[22] == 19 && sword == 0) {
				sword = 4;
				Actors[System.GameVariables[1]].Breath -= Actors[System.GameVariables[1]].BreathLimit / 3;
				aFatigue += 10;
			}
		}
		return;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyX) && funckey == 0) {
		if (System.GameVariables[1] == 0) {
			if (Actors[System.GameVariables[1]].Breath >= Actors[System.GameVariables[1]].BreathLimit / 6 && System.GameVariables[21] == 9) {
				funckey = 6;
			}
			if (Actors[System.GameVariables[1]].Breath >= Actors[System.GameVariables[1]].BreathLimit / 6 && System.GameVariables[21] == 10) {
				funckey = 7;
			}
			if (Actors[System.GameVariables[1]].Breath >= Actors[System.GameVariables[1]].BreathLimit / 3 && System.GameVariables[21] == 11) {
				funckey = 8;
			}
		}
		else {
			if (Actors[System.GameVariables[1]].Breath >= Actors[System.GameVariables[1]].BreathLimit / 3 && System.GameVariables[23] == 20 && defense == 0) {
				defense = 4;
				Actors[System.GameVariables[1]].Breath -= Actors[System.GameVariables[1]].BreathLimit / 3;
				aFatigue += 10;
			}
		}
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeySPACE) && !Accelerate) {
		Accelerate = true;
		System.FrameRate /= 3;
		return;
	}
}

WindowGoldShop::WindowGoldShop(int x, int y) {
	X = x;
	Y = y;
	Z = 0;
	Width = 224;
	Height = 256;
	Opacity = 0;
	HasFunction = true;
	Visible = false;
	Graphics.Windows.push_back(this);
}

void WindowGoldShop::Refresh() {
	if (!Visible) {
		return;
	}
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID, 2);
	WindowBitmap("001-Floor01.png", 0, 0, Width, Height, 0, 0, 255);
	rectangle(X, Y, X + Width, Y + 128);
	rectangle(X, Y + 128, X + Width, Y + 256);
	rectangle(X + 32, Y + 32, X + 64, Y + 64);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	string face[] = { "mting-495.png", "mting-496.png" };
	WindowBitmap(face[(System.GameTime % 20) / 10], 32, 32);
	WDrawTexts(64, 0, 112, 32, "贪婪之神", 1, 24L, true);
	WDrawTexts(64, 32, 128, 64, "如果你能给我" + to_string(System.ShopPrice[ShopID]) + "金币，我便能满足你一个要求。", 3, 20L);
	WDrawTexts(0, 112, Width, 32, "体力+" + to_string(500 + 300 * ShopID), 1);
	WDrawTexts(0, 144, Width, 32, "攻击+" + to_string(3 + 3 * ShopID), 1);
	WDrawTexts(0, 176, Width, 32, "防御+" + to_string(3 + 3 * ShopID), 1);
	WDrawTexts(0, 208, Width, 32, "离开", 1);
	DrawRect(64, 132 + Index * 32, 128, 24);
	if (KeyBoard.Press(KeyBoard.KeyUP)) {
		if (Index > 0) {
			--Index;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeyDOWN)) {
		if (Index < 3) {
			++Index;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.PressConfirm()) {
		switch (Index) {
		case 0:
			if (Actors[System.GameVariables[1]].Gold >= System.ShopPrice[ShopID]) {
				Actors[System.GameVariables[1]].Hp += 500 + 300 * ShopID;
				Actors[System.GameVariables[1]].Gold -= System.ShopPrice[ShopID];
				System.ShopPrice[ShopID] += ShopID+1;
				PlaySE(System.ShopSE);
			}
			else {
				PlaySE(System.BuzzerSE);
			}
			break;
		case 1:
			if (Actors[System.GameVariables[1]].Gold >= System.ShopPrice[ShopID]) {
				Actors[System.GameVariables[1]].Atk += 3 + 3 * ShopID;
				Actors[System.GameVariables[1]].Gold -= System.ShopPrice[ShopID];
				System.ShopPrice[ShopID] += ShopID + 1;
				PlaySE(System.ShopSE);
			}
			else {
				PlaySE(System.BuzzerSE);
			}
			break;
		case 2:
			if (Actors[System.GameVariables[1]].Gold >= System.ShopPrice[ShopID]) {
				Actors[System.GameVariables[1]].Def += 3 + 3 * ShopID;
				Actors[System.GameVariables[1]].Gold -= System.ShopPrice[ShopID];
				System.ShopPrice[ShopID] += ShopID + 1;
				PlaySE(System.ShopSE);
			}
			else {
				PlaySE(System.BuzzerSE);
			}
			break;
		case 3:
			PlaySE(System.CancelSE);
			System.ShopType = 0;
			Visible = false;
			break;
		}
		return;
	}
}

WindowEXPShop::WindowEXPShop(int x, int y) {
	X = x;
	Y = y;
	Z = 0;
	Width = 224;
	Height = 256;
	Opacity = 0;
	HasFunction = true;
	Visible = false;
	Graphics.Windows.push_back(this);
}

void WindowEXPShop::Refresh() {
	if (!Visible) {
		return;
	}
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID, 2);
	WindowBitmap("001-Floor01.png", 0, 0, Width, Height, 0, 0, 255);
	rectangle(X, Y, X + Width, Y + 128);
	rectangle(X, Y + 128, X + Width, Y + 256);
	rectangle(X + 32, Y + 32, X + 64, Y + 64);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	string face[] = { "mting-508.png", "mting-509.png" };
	WindowBitmap(face[(System.GameTime % 20) / 10], 32, 32);
	WDrawTexts(64, 0, 112, 32, "战斗之神", 1, 24L, true);
	WDrawTexts(64, 32, 128, 64, "我可以将你的经验值转化为你的实质力量！", 3, 20L);
	WDrawTexts(0, 112, Width, 32, "升" + to_string(1 + 2 * ShopID) + "等级（" + to_string(System.ShopEXP[ShopID * 2]) + "exp）", 1);
	WDrawTexts(0, 144, Width, 32, "攻击+" + to_string(1 + 2 * ShopID) + "（" + to_string(System.ShopEXP[ShopID * 2 + 1]) + "exp）", 1);
	WDrawTexts(0, 176, Width, 32, "防御+" + to_string(2 + 3 * ShopID) + "（" + to_string(System.ShopEXP[ShopID * 2 + 1]) + "exp）", 1);
	WDrawTexts(0, 208, Width, 32, "离开", 1);
	DrawRect(64, 132 + Index * 32, 128, 24);
	if (KeyBoard.Press(KeyBoard.KeyUP)) {
		if (Index > 0) {
			--Index;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeyDOWN)) {
		if (Index < 3) {
			++Index;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.PressConfirm()) {
		switch (Index) {
		case 0:
			if (Actors[System.GameVariables[1]].Exp >= System.ShopEXP[ShopID * 2]) {
				Actors[System.GameVariables[1]].Level += 1 + 2 * ShopID;
				Actors[System.GameVariables[1]].BreathLimit += 6 * (1 + 2 * ShopID);
				Actors[System.GameVariables[1]].Hp += 250 * (1 + 2 * ShopID);
				Actors[System.GameVariables[1]].Atk += 3 * (1 + 2 * ShopID);
				Actors[System.GameVariables[1]].Def += 3 * (1 + 2 * ShopID);
				Actors[System.GameVariables[1]].Exp -= System.ShopEXP[ShopID * 2];
				PlaySE(System.ShopSE);
			}
			else {
				PlaySE(System.BuzzerSE);
			}
			break;
		case 1:
			if (Actors[System.GameVariables[1]].Exp >= System.ShopEXP[ShopID * 2 + 1]) {
				Actors[System.GameVariables[1]].Atk += 1 + 2 * ShopID;
				Actors[System.GameVariables[1]].Exp -= System.ShopEXP[ShopID * 2 + 1];
				PlaySE(System.ShopSE);
			}
			else {
				PlaySE(System.BuzzerSE);
			}
			break;
		case 2:
			if (Actors[System.GameVariables[1]].Exp >= System.ShopEXP[ShopID * 2 + 1]) {
				Actors[System.GameVariables[1]].Def += 2 + 3 * ShopID;
				Actors[System.GameVariables[1]].Exp -= System.ShopEXP[ShopID * 2 + 1];
				PlaySE(System.ShopSE);
			}
			else {
				PlaySE(System.BuzzerSE);
			}
			break;
		case 3:
			PlaySE(System.CancelSE);
			System.ShopType = 0;
			Visible = false;
			break;
		}
		return;
	}
}

WindowKeyShop::WindowKeyShop(int x, int y) {
	X = x;
	Y = y;
	Z = 0;
	Width = 224;
	Height = 256;
	Opacity = 0;
	HasFunction = true;
	Visible = false;
	Graphics.Windows.push_back(this);
}

void WindowKeyShop::Refresh() {
	if (!Visible) {
		return;
	}
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID, 2);
	WindowBitmap("001-Floor01.png", 0, 0, Width, Height, 0, 0, 255);
	rectangle(X, Y, X + Width, Y + 128);
	rectangle(X, Y + 128, X + Width, Y + 256);
	rectangle(X + 32, Y + 32, X + 64, Y + 64);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	string face[] = { "mting-504.png", "mting-505.png" };
	WindowBitmap(face[(System.GameTime % 20) / 10], 32, 32);
	WDrawTexts(64, 0, 112, 32, "盗贼", 1, 24L, true);
	WDrawTexts(64, 32, 128, 64, "黄钥匙-$20\n-蓝钥匙$80\n来买吧！", 3, 20L);
	WDrawTexts(0, 112, Width, 32, "黄钥匙", 1);
	WDrawTexts(0, 144, Width, 32, "蓝钥匙", 1);
	WDrawTexts(0, 176, Width, 32, "离开", 1);
	DrawRect(64, 132 + Index * 32, 128, 24);
	if (KeyBoard.Press(KeyBoard.KeyUP)) {
		if (Index > 0) {
			--Index;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeyDOWN)) {
		if (Index < 2) {
			++Index;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.PressConfirm()) {
		switch (Index) {
		case 0:
			if (Actors[System.GameVariables[1]].Gold >= 20) {
				++Actors[System.GameVariables[1]].Item[0];
				Actors[System.GameVariables[1]].Gold -= 20;
				PlaySE(System.ShopSE);
			}
			else {
				PlaySE(System.BuzzerSE);
			}
			break;
		case 1:
			if (Actors[System.GameVariables[1]].Gold >= 80) {
				++Actors[System.GameVariables[1]].Item[1];
				Actors[System.GameVariables[1]].Gold -= 80;
				PlaySE(System.ShopSE);
			}
			else {
				PlaySE(System.BuzzerSE);
			}
			break;
		case 2:
			PlaySE(System.CancelSE);
			System.ShopType = 0;
			Visible = false;
			break;
		}
		return;
	}
}

WindowSDOORShop::WindowSDOORShop(int x, int y) {
	X = x;
	Y = y;
	Z = 0;
	Width = 224;
	Height = 256;
	Opacity = 0;
	HasFunction = true;
	Visible = false;
	Graphics.Windows.push_back(this);
}

void WindowSDOORShop::Refresh() {
	if (!Visible) {
		return;
	}
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID, 2);
	WindowBitmap("001-Floor01.png", 0, 0, Width, Height, 0, 0, 255);
	rectangle(X, Y, X + Width, Y + 128);
	rectangle(X, Y + 128, X + Width, Y + 256);
	rectangle(X + 32, Y + 32, X + 64, Y + 64);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	string face[] = { "mting-510.png", "mting-511.png" };
	WindowBitmap(face[(System.GameTime % 20) / 10], 32, 32);
	WDrawTexts(64, 0, 112, 32, "老人", 1, 24L, true);
	WDrawTexts(64, 32, 128, 64, "嗨！\n要买随意门吗，$30一个", 3, 20L);
	WDrawTexts(0, 112, Width, 32, "买", 1);
	WDrawTexts(0, 144, Width, 32, "离开", 1);
	DrawRect(64, 132 + Index * 32, 128, 24);
	if (KeyBoard.Press(KeyBoard.KeyUP)) {
		if (Index > 0) {
			--Index;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeyDOWN)) {
		if (Index < 1) {
			++Index;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.PressConfirm()) {
		switch (Index) {
		case 0:
			if (Actors[System.GameVariables[1]].Gold >= 30) {
				++Actors[System.GameVariables[1]].Item[5];
				Actors[System.GameVariables[1]].Gold -= 30;
				PlaySE(System.ShopSE);
			}
			else {
				PlaySE(System.BuzzerSE);
			}
			break;
		case 1:
			PlaySE(System.CancelSE);
			System.ShopType = 0;
			Visible = false;
			break;
		}
		return;
	}
}

WindowRECYShop::WindowRECYShop(int x, int y) {
	X = x;
	Y = y;
	Z = 0;
	Width = 224;
	Height = 256;
	Opacity = 0;
	HasFunction = true;
	Visible = false;
	Graphics.Windows.push_back(this);
}

void WindowRECYShop::Refresh() {
	if (!Visible) {
		return;
	}
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID, 2);
	WindowBitmap("001-Floor01.png", 0, 0, Width, Height, 0, 0, 255);
	rectangle(X, Y, X + Width, Y + 128);
	rectangle(X, Y + 128, X + Width, Y + 256);
	rectangle(X + 32, Y + 32, X + 64, Y + 64);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	string face[] = { "mting-514.png", "mting-515.png" };
	WindowBitmap(face[(System.GameTime % 20) / 10], 32, 32);
	WDrawTexts(64, 0, 112, 32, "奸商", 1, 24L, true);
	WDrawTexts(64, 32, 128, 64, "你有多余的钥匙吗，我用体力换！", 3, 20L);
	WDrawTexts(0, 112, Width, 32, "黄钥匙换1000体力", 1);
	WDrawTexts(0, 144, Width, 32, "蓝钥匙换2000体力", 1);
	WDrawTexts(0, 176, Width, 32, "红钥匙换5000体力", 1);
	WDrawTexts(0, 208, Width, 32, "离开", 1);
	DrawRect(64, 132 + Index * 32, 128, 24);
	if (KeyBoard.Press(KeyBoard.KeyUP)) {
		if (Index > 0) {
			--Index;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeyDOWN)) {
		if (Index < 3) {
			++Index;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.PressConfirm()) {
		switch (Index) {
		case 0:
			if (Actors[System.GameVariables[1]].Item[0] > 0) {
				--Actors[System.GameVariables[1]].Item[0];
				Actors[System.GameVariables[1]].Hp += 1000;
				PlaySE(System.ShopSE);
			}
			else {
				PlaySE(System.BuzzerSE);
			}
			break;
		case 1:
			if (Actors[System.GameVariables[1]].Item[1] > 0) {
				--Actors[System.GameVariables[1]].Item[1];
				Actors[System.GameVariables[1]].Hp += 2000;
				PlaySE(System.ShopSE);
			}
			else {
				PlaySE(System.BuzzerSE);
			}
			break;
		case 2:
			if (Actors[System.GameVariables[1]].Item[2] > 0) {
				--Actors[System.GameVariables[1]].Item[2];
				Actors[System.GameVariables[1]].Hp += 5000;
				PlaySE(System.ShopSE);
			}
			else {
				PlaySE(System.BuzzerSE);
			}
			break;
		case 3:
			PlaySE(System.CancelSE);
			System.ShopType = 0;
			Visible = false;
			break;
		}
		return;
	}
}

WindowSkill::WindowSkill(int x, int y) {
	X = x;
	Y = y;
	Z = 0;
	Width = 320;
	Height = 160;
	Opacity = 0;
	HasFunction = true;
	Visible = false;
	Graphics.Windows.push_back(this);
}

void WindowSkill::Refresh() {
	if (!Visible) {
		return;
	}
	vector <int> allpiece, level, breath, fatigue;
	vector <string> desc;
	if (KeyBoard.Trigger(KeyBoard.KeyW) || KeyBoard.TriggerCancel()) {
		PlaySE(System.CancelSE);
		Visible = false;
	}
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID, 2);
	WindowBitmap("001-Floor01.png", 0, 0, Width, Height, 0, 0, 255);
	if (Actors[System.GameVariables[1]].Item[6] > 0) {
		allpiece.push_back(6);
		level.push_back(1);
		breath.push_back(1);
		fatigue.push_back(3);
		desc.push_back("效果:立即对敌方造成基础伤害*2.25+(" + to_string(Actors[System.GameVariables[1]].Mdef * 2) + ")点伤害。");
	}
	if (Actors[System.GameVariables[1]].Item[7] > 0) {
		allpiece.push_back(7);
		level.push_back(25);
		breath.push_back(1);
		fatigue.push_back(4);
		desc.push_back("效果:恢复造成伤害的70%+(" + to_string(Actors[System.GameVariables[1]].Mdef * 2) + ")点体力，但是不会致命");
	}
	if (Actors[System.GameVariables[1]].Item[8] > 0) {
		allpiece.push_back(8);
		level.push_back(25);
		breath.push_back(2);
		fatigue.push_back(10);
		desc.push_back("效果:将敌方血量压制至1/4并额外造成(" + to_string(Actors[System.GameVariables[1]].Mdef) + ")点伤害，但之后造成的伤害会降低至1/3");
	}
	if (Actors[System.GameVariables[1]].Item[19] > 0) {
		allpiece.push_back(19);
		level.push_back(1);
		breath.push_back(2);
		fatigue.push_back(10);
		desc.push_back("效果:4回合内可以2连击");
	}
	rfor(i, 0, allpiece.size()) {
		WindowBitmap(Item[allpiece[i]].File, 8 + 40 * i, 8);
		if (System.GameVariables[1] == 0) {
			if (System.GameVariables[20] == allpiece[i]) {
				settextcolor(TextColor("green"));
				DrawTextsBond(X + 16 + 40 * i, Y + 8, 32, 32, "E", 0, 20L);
				settextcolor(TextColor("white"));
			}
		}
		if (System.GameVariables[1] == 1) {
			if (System.GameVariables[22] == allpiece[i]) {
				settextcolor(TextColor("green"));
				DrawTextsBond(X + 16 + 40 * i, Y + 8, 32, 32, "E", 0, 20L);
				settextcolor(TextColor("white"));
			}
		}
	}
	rectangle(X, Y, X + Width, Y + Height);
	if (allpiece.size() == 0) {
		setlinecolor(WHITE);
		setlinestyle(PS_SOLID, 1);
		return;
	}
	rectangle(X + 8 + 40 * Index, Y + 8, X + 40 + 40 * Index, Y + 40);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	WDrawTexts(0, 24, 256, 32, Item[allpiece[Index]].Name, 1, 24L);
	WDrawTexts(0, 64, 208, 128, desc[Index], 3, 20L);
	WDrawTexts(216, 32, 80, 20, "使用等级=" + to_string(level[Index]), 0, 18);
	WDrawTexts(216, 64, 80, 20, "气息消费=" + to_string(breath[Index]), 0, 18);
	WDrawTexts(216, 96, 80, 20, "疲劳+" + to_string(fatigue[Index]), 0, 18);
	if (KeyBoard.Press(KeyBoard.KeyLEFT)) {
		if (Index > 0) {
			PlaySE(System.CursorSE);
			--Index;
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeyRIGHT)) {
		if (Index < allpiece.size() - 1) {
			PlaySE(System.CursorSE);
			++Index;
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.TriggerConfirm()) {
		if (Actors[System.GameVariables[1]].Level >= level[Index] && Actors[System.GameVariables[1]].Hp > 50 && System.GameVariables[20 + System.GameVariables[1] * 2] != allpiece[Index]) {
			PlaySE(System.DecisionSE);
			Actors[System.GameVariables[1]].Hp -= 50;
			System.GameVariables[20 + System.GameVariables[1] * 2] = allpiece[Index];
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
}

WindowDefense::WindowDefense(int x, int y) {
	X = x;
	Y = y;
	Z = 0;
	Width = 320;
	Height = 160;
	Opacity = 0;
	HasFunction = true;
	Visible = false;
	Graphics.Windows.push_back(this);
}

void WindowDefense::Refresh() {
	if (!Visible) {
		return;
	}
	vector <int> allpiece, level, breath, fatigue;
	vector <string> desc;
	if (KeyBoard.Trigger(KeyBoard.KeyH) || KeyBoard.TriggerCancel()) {
		PlaySE(System.CancelSE);
		Visible = false;
	}
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID, 2);
	WindowBitmap("001-Floor01.png", 0, 0, Width, Height, 0, 0, 255);
	if (Actors[System.GameVariables[1]].Item[9] > 0) {
		allpiece.push_back(9);
		level.push_back(1);
		breath.push_back(1);
		fatigue.push_back(5);
		desc.push_back("效果:所受伤害降低到2/3并减少(" + to_string(Actors[System.GameVariables[1]].Mdef) + ")点伤害。");
	}
	if (Actors[System.GameVariables[1]].Item[10] > 0) {
		allpiece.push_back(10);
		level.push_back(45);
		breath.push_back(1);
		fatigue.push_back(3);
		desc.push_back("效果:所受伤害减少(" + to_string(Actors[System.GameVariables[1]].Mdef * 2) + ")点，并将原伤害的1.3倍加(" + to_string(Actors[System.GameVariables[1]].Mdef) + ")点返还给对方。");
	}
	if (Actors[System.GameVariables[1]].Item[11] > 0) {
		allpiece.push_back(11);
		level.push_back(45);
		breath.push_back(2);
		fatigue.push_back(10);
		desc.push_back("效果:完全防御此次伤害，并吸取对方全部气息。");
	}
	if (Actors[System.GameVariables[1]].Item[20] > 0) {
		allpiece.push_back(20);
		level.push_back(1);
		breath.push_back(2);
		fatigue.push_back(10);
		desc.push_back("效果:4回合内将所受伤害反弹至怪物身上");
	}
	rfor(i, 0, allpiece.size()) {
		WindowBitmap(Item[allpiece[i]].File, 8 + 40 * i, 8);
		if (System.GameVariables[1] == 0) {
			if (System.GameVariables[21] == allpiece[i]) {
				settextcolor(TextColor("green"));
				DrawTextsBond(X + 16 + 40 * i, Y + 8, 32, 32, "E", 0, 20L);
				settextcolor(TextColor("white"));
			}
		}
		if (System.GameVariables[1] == 1) {
			if (System.GameVariables[23] == allpiece[i]) {
				settextcolor(TextColor("green"));
				DrawTextsBond(X + 16 + 40 * i, Y + 8, 32, 32, "E", 0, 20L);
				settextcolor(TextColor("white"));
			}
		}
	}
	rectangle(X, Y, X + Width, Y + Height);
	if (allpiece.size() == 0) {
		setlinecolor(WHITE);
		setlinestyle(PS_SOLID, 1);
		return;
	}
	rectangle(X + 8 + 40 * Index, Y + 8, X + 40 + 40 * Index, Y + 40);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	WDrawTexts(0, 24, 256, 32, Item[allpiece[Index]].Name, 1, 24L);
	WDrawTexts(0, 64, 208, 128, desc[Index], 3, 20L);
	WDrawTexts(216, 32, 80, 20, "使用等级=" + to_string(level[Index]), 0, 18);
	WDrawTexts(216, 64, 80, 20, "气息消费=" + to_string(breath[Index]), 0, 18);
	WDrawTexts(216, 96, 80, 20, "疲劳+" + to_string(fatigue[Index]), 0, 18);
	if (KeyBoard.Press(KeyBoard.KeyLEFT)) {
		if (Index > 0) {
			PlaySE(System.CursorSE);
			--Index;
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeyRIGHT)) {
		if (Index < allpiece.size() - 1) {
			PlaySE(System.CursorSE);
			++Index;
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.TriggerConfirm()) {
		if (Actors[System.GameVariables[1]].Level >= level[Index] && Actors[System.GameVariables[1]].Hp > 50 && System.GameVariables[21 + System.GameVariables[1] * 2] != allpiece[Index]) {
			PlaySE(System.DecisionSE);
			Actors[System.GameVariables[1]].Hp -= 50;
			System.GameVariables[21 + System.GameVariables[1] * 2] = allpiece[Index];
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
}

WindowDrug::WindowDrug(int x, int y) {
	X = x;
	Y = y;
	Z = 0;
	Width = 256;
	Height = 160;
	Opacity = 0;
	HasFunction = true;
	Visible = false;
	Graphics.Windows.push_back(this);
}

void WindowDrug::Refresh() {
	if (!Visible) {
		return;
	}
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID, 2);
	WindowBitmap("001-Floor01.png", 0, 0, Width, Height, 0, 0, 255);
	WindowBitmap("mting-190.png", 48, 32);
	WindowBitmap("mting-191.png", 48, 64);
	rectangle(X, Y, X + Width, Y + Height);
	rectangle(X + 48, Y + 32 + Index * 32, X + 80, Y + 64 + Index * 32);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	WDrawTexts(0, 0, 256, 32, "道具袋", 1, 24L, true);
	WDrawTexts(64, 32, 96, 32, " × " + to_string(Actors[System.GameVariables[1]].Item[13]));
	WDrawTexts(64, 64, 96, 32, " × " + to_string(Actors[System.GameVariables[1]].Item[14]));
	WDrawTexts(112, 32, 128, 32, "恢复中毒和80体力", 0, 20L);
	WDrawTexts(112, 64, 128, 32, "恢复衰弱和180体力", 0, 20L);
	if (KeyBoard.Press(KeyBoard.KeyUP)) {
		if (Index == 1) {
			--Index;
			PlaySE(System.CursorSE);
		}
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeyDOWN)) {
		if (Index == 0) {
			++Index;
			PlaySE(System.CursorSE);
		}
		return;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyB) || KeyBoard.TriggerCancel()) {
		PlaySE(System.CancelSE);
		Visible = false;
		return;
	}
	if (KeyBoard.PressConfirm()) {
		if (Actors[System.GameVariables[1]].Item[13 + Index] > 0) {
			PlaySE("mting-56.wav");
			--Actors[System.GameVariables[1]].Item[13 + Index];
			Actors[System.GameVariables[1]].Hp += 80 + 100 * Index;
			if (Index == 0 && Actors[System.GameVariables[1]].Status == 1) {
				Actors[System.GameVariables[1]].Status = 0;
			}
			if (Index == 1 && Actors[System.GameVariables[1]].Status == 2) {
				Actors[System.GameVariables[1]].Status = 0;
				System.GameVariables[5] = 0;
			}
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
}

WindowFloorFly::WindowFloorFly(int x, int y) {
	X = x;
	Y = y;
	Z = 0;
	Width = 122;
	Height = 122;
	Opacity = 255;
	HasFunction = true;
	Visible = false;
	update = false;
	Graphics.Windows.push_back(this);
}

void WindowFloorFly::Refresh() {
	if (!Visible) {
		return;
	}
	WindowBitmap("001-Floor01.png", -32, 132, 192, 96, 0, 0, 255);
	if (update) {
		rfor(i, 0, 121) {
			if (events[i][0] != nullptr) {
				delete events[i][0];
			}
			if (events[i][1] != nullptr) {
				delete events[i][1];
			}
			if (floor != nullptr) {
				delete floor;
			}
			events[i][0] = new IMAGE;
			events[i][1] = new IMAGE;
			floor = new IMAGE;
		}
		rfor(i, 0, System.Maps[viewmapid].MapEvents.size()) {
			loadimage(events[i][0], ("res\\picture\\" + System.Maps[viewmapid].MapEvents[i].File[0]).c_str(), 11, 11);
			loadimage(events[i][1], ("res\\picture\\" + System.Maps[viewmapid].MapEvents[i].File[1]).c_str(), 11, 11);
		}
		loadimage(floor, ("res\\picture\\" + System.Maps[viewmapid].FloorName).c_str(), 232, 174);
		update = false;
	}
	OpaqueImage(nullptr, X, Y, Width, Height, 0, 0, floor);
	rfor(i, 0, System.Maps[viewmapid].MapEvents.size()) {
		if (System.Maps[viewmapid].MapEvents[i].Exist) {
			if (System.Maps[viewmapid].MapEvents[i].TriggerCondition[0] == 1 && System.GameSwitches[System.Maps[viewmapid].MapEvents[i].TriggerCondition[1]] != System.Maps[viewmapid].MapEvents[i].TriggerCondition[2]) {
				continue;
			}
			if (System.Maps[viewmapid].MapEvents[i].TriggerCondition[0] == 2 && System.GameVariables[System.Maps[viewmapid].MapEvents[i].TriggerCondition[1]] != System.Maps[viewmapid].MapEvents[i].TriggerCondition[2]) {
				continue;
			}
			OpaqueImage(nullptr, X + System.Maps[viewmapid].MapEvents[i].X * 11, Y + System.Maps[viewmapid].MapEvents[i].Y * 11, events[i][(System.GameTime % 20) / 10]);
		}
	}
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID, 2);
	rectangle(X, Y, X + Width, Y + Height);
	rectangle(X - 32, Y + 132, X + 160, Y + 228);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	WDrawTexts(-32, 120, 160, 32, "银灰色飞羽", 1, 20L, true);
	WDrawTexts(-32, 144, 160, 32, to_string(viewfloorid) + " F", 1, 18L);
	WDrawTexts(-32, 192, 96, 32, "-Quit(f)-", 0, 18L);
	WDrawTexts(88, 192, 96, 32, "-Enter-", 0, 18L);
	if (System.FloorRecord[System.GameVariables[3]][0] == viewfloorid) {
		WindowBitmap("mting-1427.png", -16, 168, 16, 16, 0, 0);
	}
	else {
		WindowBitmap("mting-1427.png", -16, 168, 16, 16, 16, 0);
	}
	if (System.FloorRecord[System.GameVariables[3]][System.FloorRecord[System.GameVariables[3]].size() - 1] == viewfloorid) {
		WindowBitmap("mting-1427.png", 128, 168, 16, 16, 32, 0);
	}
	else {
		WindowBitmap("mting-1427.png", 128, 168, 16, 16, 48, 0);
	}
	if (KeyBoard.Press(KeyBoard.KeyLEFT)) {
		if (System.FloorRecord[System.GameVariables[3]][0] != viewfloorid) {
			PlaySE(System.CursorSE);
			viewfloorid = *(find(System.FloorRecord[System.GameVariables[3]].begin(), System.FloorRecord[System.GameVariables[3]].end(), viewfloorid) - 1);
			DataMap tem;
			tem.MapName = to_string(System.GameVariables[3]) + ":" + to_string(viewfloorid);
			viewmapid = find(System.Maps.begin(), System.Maps.end(), tem) - System.Maps.begin();
			update = true;
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeyRIGHT)) {
		if (System.FloorRecord[System.GameVariables[3]][System.FloorRecord[System.GameVariables[3]].size() - 1] != viewfloorid) {
			PlaySE(System.CursorSE);
			viewfloorid = *(find(System.FloorRecord[System.GameVariables[3]].begin(), System.FloorRecord[System.GameVariables[3]].end(), viewfloorid) + 1);
			DataMap tem;
			tem.MapName = to_string(System.GameVariables[3]) + ":" + to_string(viewfloorid);
			viewmapid = find(System.Maps.begin(), System.Maps.end(), tem) - System.Maps.begin();
			update = true;
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.TriggerConfirm()) {
		PlaySE("mting-78.wav");
		Visible = false;
		GameSprite stair("mting.png");
		stair.X = System.MapX;
		stair.Y = System.MapY;
		stair.Opacity = 0;
		rfor(i, 0, 15) {
			stair.Opacity += 17;
			Graphics.Update();
		}
		Actors[System.GameVariables[1]].MapID = viewmapid;
		Player.Direction = 0;
		if (viewfloorid >= System.GameVariables[2]) {
			Actors[System.GameVariables[1]].X = System.Maps[viewmapid].MapEvents[0].X;
			Actors[System.GameVariables[1]].Y = System.Maps[viewmapid].MapEvents[0].Y;
		}
		else {
			Actors[System.GameVariables[1]].X = System.Maps[viewmapid].MapEvents[1].X;
			Actors[System.GameVariables[1]].Y = System.Maps[viewmapid].MapEvents[1].Y;
		}
		System.GameVariables[2] = viewfloorid;
		rfor(i, 0, 5) {
			Graphics.Update();
		}
		System.NeedRefresh = true;
		rfor(i, 0, 15) {
			stair.Opacity -= 17;
			Graphics.Update();
		}
		stair.Dispose();
		return;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyF) || KeyBoard.TriggerCancel()) {
		PlaySE(System.CancelSE);
		Visible = false;
		return;
	}

}

void WindowFloorFly::Delete() {
	rfor(i, 0, 121) {
		delete events[i][0];
		delete events[i][1];
	}
	delete floor;
}

WindowFileImage::WindowFileImage(int x, int y) {
	X = x;
	Y = y;
	Z = 1;
	Width = 176;
	Height = 176;
	Opacity = 255;
	HasFunction = true;
	Visible = false;
	Graphics.Windows.push_back(this);
}

void WindowFileImage::Refresh() {
	if (!Visible) {
		return;
	}
	WindowBitmap("001-Floor01.png", 0, 0, Width, Height, 0, 0, 255);
	if (ExistFile("save\\save" + to_string(fileid) + ".sav")) {
		IMAGE img;
		loadimage(&img, ("save\\save" + to_string(fileid) + ".png").c_str(), 304, 224);
		putimage(X, Y, 176, 176, &img, 112, 16);
	}
	else {
		WDrawTexts(0, 0, 144, 144, "No File Here!", 1, 24L);
	}
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID, 2);
	rectangle(X, Y, X + Width, Y + Height);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
}

WindowFileCursor::WindowFileCursor(int x, int y, int rectheight, vector <string> item) {
	X = x;
	Y = y;
	Z = 1;
	Width = 136;
	Height = 176;
	Opacity = 255;
	HasFunction = true;
	Active = false;
	Visible = false;
	RectHeight = rectheight;
	Items = item;
	Graphics.Windows.push_back(this);
}

void WindowFileCursor::Refresh() {
	if (!Visible) {
		return;
	}
	WindowBitmap("001-Floor01.png", 0, 0, Width, Height, 0, 0, 255);
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID, 2);
	rectangle(X, Y, X + Width, Y + Height);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	if (load) {
		WDrawTexts(0, 0, 104, 20, "Load Page " + to_string(Page), 1, 18L);
	}
	else {
		WDrawTexts(0, 0, 104, 20, "Save Page " + to_string(Page), 1, 18L);
	}
	IMAGE img;
	loadimage(&img, "res\\picture\\mting-1427.png", 32, 8);
	if (Page == 0) {
		OpaqueImage(nullptr, X + 20, Y + 20, 8, 8, 0, 0, &img);
	}
	else {
		OpaqueImage(nullptr, X + 20, Y + 20, 8, 8, 8, 0, &img);
	}
	if (Page == 99) {
		OpaqueImage(nullptr, X + 112, Y + 20, 8, 8, 16, 0, &img);
	}
	else {
		OpaqueImage(nullptr, X + 112, Y + 20, 8, 8, 24, 0, &img);
	}
	rfor(i, 0, Items.size()) {
		WDrawTexts(0, 20 + 20 * i, 104, 20, "Save " + to_string(Page * 6 + i), 0, 18L);
	}
	rfor(i, 0, Items.size()) {
		if (i == Index) {
			DrawRect(16, 36 + RectHeight * i, Width - 32, RectHeight);
		}
		DrawItem(i, NormalColor());
	}
	unless(Active) {
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeyUP)) {
		if (Index > 0) {
			--Index;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeyDOWN)) {
		if (Index < Items.size() - 1) {
			++Index;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeyLEFT)) {
		if (Page > 0) {
			Index = 0;
			--Page;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.Press(KeyBoard.KeyRIGHT)) {
		if (Page < 99) {
			Index = 0;
			++Page;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
}

void WindowFileCursor::DrawItem(int index, COLORREF colour) {
	WDrawTexts(4, 4 + RectHeight * index, Width, RectHeight, Items[index]);
}

void GameTitle::Main() {
	if (System.GameBGM != "sound-0.mp3") {
		System.GameBGM = "sound-0.mp3";
		mciSendString("stop BGM", NULL, 0, NULL);
		mciSendString("close BGM", NULL, 0, NULL);
		mciSendString("open res\\sound\\sound-0.mp3 alias BGM", NULL, 0, NULL);
		mciSendString("play BGM repeat", NULL, 0, NULL);
	}
	System.NeedRefresh = true;
	sprite.ChangeImage(System.TitleName);
	sprite.AddIn();
	title.ChangeImage("mting-1269.png");
	title.AddIn();
	title.X = -96;
	title.Y = 16;
	title.Opacity = 0;
	window.Width = 160;
	window.Height = 160;
	window.Opacity = 190;
	window.X = 512;
	window.Y = 256;
	window.Z = 1;
	siz = 150 + rand() % 100;
	rfor(i, 0, siz) {
		weather[i].ChangeImage("mting-1276.png");
		weather[i].X = rand() % 608;
		weather[i].Y = rand() % 448 - 448;
		weather[i].AddIn();
	}
	if (!ExistFile("save\\recent.dat")) {
		fstream file;
		file.open("save\\recent.dat", ios::ate | ios::out);
		file << 0 << endl;
		file.close();
	}
	Graphics.Update();
	System.DoTransition();
	while (System.Scene == this) {
		if (GameActive == GetForegroundWindow()) {
			Update();
			Graphics.Update();
		}
	}
	System.ReadyTransition();
	sprite.Dispose();
	title.Dispose();
	window.Dispose();
	filewindow.Dispose();
	cursorwindow.Dispose();
	rfor(i, 0, siz) {
		weather[i].Dispose();
	}
}

void GameTitle::Update() {
	if (title.X < 0) {
		title.X += 14;
		title.Opacity = min(title.Opacity + 32, 255);
	}
	if (window.X > 416) {
		window.X -= 12;
	}
	rfor(i, 0, siz) {
		weather[i].X -= 2;
		weather[i].Y += 8;
		weather[i].Opacity = max(0, weather[i].Opacity - 4);
		if (weather[i].Y > 448 || weather[i].X < 0 || weather[i].Opacity == 0) {
			weather[i].X = rand() % 608;
			weather[i].Y = rand() % 448 - 448;
			weather[i].Opacity = 255;
		}
	}
	if (filewindow.Visible) {
		filewindow.fileid = cursorwindow.Page * 6 + cursorwindow.Index;
		if (KeyBoard.TriggerCancel()) {
			PlaySE(System.CancelSE);
			filewindow.Visible = false;
			cursorwindow.Visible = false;
			cursorwindow.Active = false;
			cursorwindow.Page = 0;
			cursorwindow.Index = 0;
			window.Active = true;
			return;
		}
		if (KeyBoard.TriggerConfirm()) {
			if (!ExistFile("save\\save" + to_string(filewindow.fileid) + ".sav")) {
				PlaySE(System.BuzzerSE);
				return;
			}
			PlaySE("mting-78.wav");
			filewindow.Visible = false;
			cursorwindow.Visible = false;
			cursorwindow.Active = false;
			cursorwindow.Page = 0;
			cursorwindow.Index = 0;
			GameMap::LoadData(filewindow.fileid);
			System.NeedRefresh = true;
			System.Scene = new GameMap;
			System.FirstArrive = true;
			return;
			}
		return;
	}
	if (KeyBoard.TriggerConfirm()) {
		switch (window.Index)
		{
		case 0: CommandNewGame(); break;
		case 1: CommandContinue(); break;
		case 2: CommandBackground(); break;
		case 3: CommandExit(); break;
		}
		return;
	}
}

void GameTitle::CommandNewGame() {
	PlaySE(System.DecisionSE);
	System.Reload();
	System.Scene = new GameStart;//GameMap;
	return;
}

void GameTitle::CommandContinue() {
	PlaySE(System.DecisionSE);
	window.Active = false;
	filewindow.Visible = true;
	cursorwindow.load = true;
	cursorwindow.Visible = true;
	cursorwindow.Active = true;
	fstream file;
	file.open("save\\recent.dat", ios::in);
	char buffer[128];
	file.getline(buffer, 128);
	file.close();
	int index = atoi(buffer);
	cursorwindow.Page = index / 6;
	cursorwindow.Index = index % 6;
	return;
}

void GameTitle::CommandBackground() {
	PlaySE(System.DecisionSE);
	System.Scene = new GameIntro;
	return;
}

void GameTitle::CommandExit() {
	PlaySE(System.DecisionSE);
	System.Scene = nullptr;
	return;
}

void GameStart::Main() {
	System.NeedRefresh = true;
	sprite.ChangeImage("mting-1283.png");
	sprite.AddIn();
	scriptwindow.PicOpacity = 0;
	System.DoTransition();
	while (System.Scene == this) {
		if (GameActive == GetForegroundWindow()) {
			Graphics.Update();
			Update();
		}
	}
	System.ReadyTransition();
	sprite.Dispose();
	scriptwindow.Dispose();
}

void GameStart::Update() {
	scriptwindow.PicOpacity += 15;
	if (KeyBoard.TriggerConfirm() && scriptwindow.Opacity >= 255) {
		System.Scene = new GameMap;
		System.FirstArrive = true;
		return;
	}
}

void GameIntro::Main() {
	System.NeedRefresh = true;
	floor.ChangeImage("001-Floor01.png");
	floor.AddIn();
	sprite.ChangeImage("mting-1283.png");
	sprite.AddIn();
	script.ChangeImage("mting-1282.png");
	script.X = 48;
	script.Y = 48;
	script.AddIn();
	System.DoTransition();
	while (System.Scene == this) {
		if (GameActive == GetForegroundWindow()) {
			Graphics.Update();
			Update();
		}
	}
	System.ReadyTransition();
	sprite.Dispose();
	floor.Dispose();
	script.Dispose();
}

void GameIntro::Update() {
	if (KeyBoard.TriggerConfirm() || KeyBoard.TriggerCancel()) {
		PlaySE(System.CancelSE);
		System.Scene = new GameTitle;
		return;
	}
}

void GameMap::Main() {
	mciSendString("stop BGM", NULL, 0, NULL);
	System.NeedRefresh = true;
	sprite.ChangeImage("mting.png");
	sprite.X = System.MapX;
	sprite.Y = System.MapY;
	sprite.AddIn();
	hintwindow.Visible = false;
	Graphics.MapPatterns.Initialization();
	System.DoTransition();
	while (System.Scene == this) {
		if (GameActive == GetForegroundWindow()) {
			Graphics.Update();
			Update();
		}
	}
	System.ReadyTransition();
	Graphics.MapPatterns.Dispose();
	hintwindow.Dispose();
	messagewindow.Dispose();
	monsterbookwindow.Dispose();
	encyclopediawindow.Dispose();
	battlewindow.Dispose();
	goldshopwindow.Dispose();
	expshopwindow.Dispose();
	keyshopwindow.Dispose();
	sdoorshopwindow.Dispose();
	skillwindow.Dispose();
	defensewindow.Dispose();
	drugwindow.Dispose();
	flywindow.Delete();
	flywindow.Dispose();
	filewindow.Dispose();
	cursorwindow.Dispose();
}

void GameMap::Update() {
	if (System.EndGame) {
		System.EndGame = false;
		GameOver();
		return;
	}
	if (System.Victory) {
		System.Scene = new GameEnd;
		return;
	}
	if (System.FirstArrive) {
		System.FirstArrive = false;
		sprite.Opacity = 255;
		rfor(i, 0, 15) {
			sprite.Opacity -= 17;
			Graphics.Update();
		}
	}
	if (System.GameSwitches[21] && System.GameVariables[3] == 7 && !System.GameSwitches[22] && !System.GameSwitches[23]) {
		System.GameSwitches[23] = true;
		if (System.GameVariables[1] == 0) {
			// 勇士先到，勇士献祭
			System.MessageName = { "公主", "勇者", "公主", "勇者", //1
									"妖精", "妖精", "勇者", "妖精", //2
									"公主", "妖精", "勇者", "妖精", //3
									"公主", "妖精", "公主", "妖精", //4
									"勇者", "妖精", "公主", "妖精", //5
									"勇者", "妖精", "公主", "勇者", //6
									"公主", "勇者", "勇者", "勇者", "公主" };
			System.MessageContent = { "勇者先生？",
			"公主？\n这是…",
			"看样子我们汇合了呢",
			"那是…\n曾经帮助过我们的妖精",
			"……",
			"没想到你们还会回来",
			"没错，我们还要找魔物首领算账呢",
			"好吧，但是你没有发现并没有前进的道路吗",
			"确实…\n这是怎么一回事？",
			"带有纯净灵魂的人类之身是无法进入魔界的，它不会显现前进的楼梯",
			"这是什么意思？",
			"你可以理解成魔界在拒绝你们",
			"既然你在这里等着我们\n应该是有办法的吧？",
			"是的，不过你们未必会同意",
			"怎么说？",
			"是否显现前行之路，关键在于灵魂是否纯净，也就是说，手上是不是沾满了同类的鲜血",
			"？！",
			"……如果你们想继续前进的话，恐怕得有一人要献出生命，而且必须由另一人动手",
			"没有…别的办法吗",
			"恐怕是的，所以…现在还有机会回头",
			"没问题，自从参与到这件事中来，我的生命已经不完全属于我自己了",
			"什么？",
			"勇者先生，你……",
			"如果需要这样来开辟前行的道路的话，就由我来挥洒鲜血好了",
			"不行！一定…还有其他办法的",
			"但是没有时间了不是吗，我们每多纠结一秒，就会有更多人被魔物杀死",
			"我们的生命，在进入这座魔塔的时候，就已经不单单属于我们自己了啊",
			"公主殿下，我相信你，一定可以抵达终点的，所以…",
			"什么？！" };
			System.MessageHead = { -1, 108, -1, 108, //1
									109, 109, 108, 109, //2
									-1, 109, 108, 109, //3
									-1, 109, -1, 109, //4
									108, 109, -1, 109,//5
									108, 109, -1, 108, //6
									-1, 108, 108, 108, -1 };
		}
		else {
			// 公主先到，公主献祭
			System.MessageName = { "勇者", "公主", "勇者", "公主", //1
									"妖精", "妖精", "勇者", "妖精", //2
									"公主", "妖精", "勇者", "妖精", //3
									"公主", "妖精", "公主", "妖精", //4
									"勇者", "妖精", "公主", "妖精", //5
									"公主", "妖精", "勇者", "公主", //6
									"勇者", "公主", "公主", "公主", "勇者" };
			System.MessageContent = { "公主？",
			"勇者先生？\n这是…",
			"看样子我们汇合了",
			"那是…\n曾经帮助过我们的妖精",
			"……",
			"没想到你们还会回来",
			"没错，我们还要找魔物首领算账呢",
			"好吧，但是你没有发现并没有前进的道路吗",
			"确实…\n这是怎么一回事？",
			"带有纯净灵魂的人类之身是无法进入魔界的，它不会显现前进的楼梯",
			"这是什么意思？",
			"你可以理解成魔界在拒绝你们",
			"既然你在这里等着我们\n应该是有办法的吧？",
			"是的，不过你们未必会同意",
			"怎么说？",
			"是否显现前行之路，关键在于灵魂是否纯净，也就是说，手上是不是沾满了同类的鲜血",
			"？！",
			"……如果你们想继续前进的话，恐怕得有一人要献出生命，而且必须由另一人动手",
			"没有…别的办法吗",
			"恐怕是的，所以…现在还有机会回头",
			"……\n抱歉呢，这一切的起因都是我，那就由我来做好了",
			"什么？",
			"公主，你……",
			"抱歉啊勇者先生，谢谢你两次都能来救我，看样子也该轮到我做些什么了",
			"不行！\n你是一国公主啊，来救你大家的牺牲，都是为了你啊",
			"我知道，但是我不能因为我，就让魔物践踏我的子民和家园",
			"如果小女子一人的鲜血足以开拓前行的道路，那我将没有任何犹豫和怨言",
			"勇者先生，我相信你，一定可以像之前一样创造奇迹的",
			"什么？！" };
			System.MessageHead = { -1, 107, -1, 107, //1
									109, 109, -1, 109, //2
									107, 109, -1, 109, //3
									107, 109, 107, 109, //4
									-1, 109, 107, 109, //5
									107, 109, -1, 107, //6
									-1, 107, 107, 107, -1 };
		}
	}
	if (System.GameSwitches[21] && System.GameVariables[3] == 7 && System.MessageName.empty() && !System.GameSwitches[22]) {
		PlaySE("mting-39.wav");
		GameSprite white("mting-1248.png");
		white.X = System.MapX;
		white.Y = System.MapY;
		white.Opacity = 0;
		rfor(i, 0, 15) {
			white.Opacity += 17;
			Graphics.Update();
		}
		System.GameSwitches[22] = true;
		rfor(i, 0, 5) {
			Graphics.Update();
		}
		System.NeedRefresh = true;
		rfor(i, 0, 15) {
			white.Opacity -= 17;
			Graphics.Update();
		}
		white.Dispose();
		System.MessageName = { "妖精", Actors[System.GameVariables[1]].Name, "妖精", Actors[System.GameVariables[1]].Name, "妖精" };
		System.MessageContent = { "……",
		"……",
		"所以我才搞不懂人类",
		"……",
		"喂，不要发呆了\n不要辜负了这份心意，继续前进吧" };
		System.MessageHead = { 109, -1, 109, -1, 109 };
	}
	if (System.GameSwitches[21] && System.GameVariables[3] == 7 && System.GameSwitches[22] && !System.GameSwitches[24] && System.MessageName.empty()) {
		System.GameSwitches[24] = true;
		if (System.GameVariables[1] == 0) {
			Actors[0].Hp += Actors[1].Hp;
			Actors[0].Atk += Actors[1].Atk;
			Actors[0].Def += Actors[1].Def;
			Actors[0].Breath = Actors[0].BreathLimit - 1;
			Actors[0].Status = 0;
			System.GameVariables[5] = 0;
			Actors[0].Status = 0;
			Actors[0].Exp += Actors[1].Exp;
			Actors[0].Gold += Actors[1].Gold;
			Actors[0].Item[0] += Actors[1].Item[0];
			Actors[0].Item[1] += Actors[1].Item[1];
			Actors[0].Item[2] += Actors[1].Item[2];
			Actors[0].Item[5] += Actors[1].Item[5];
			Actors[0].Item[12] += Actors[1].Item[12];
			Actors[0].Item[13] += Actors[1].Item[13];
			Actors[0].Item[14] += Actors[1].Item[14];
			Actors[0].Item[15] += Actors[1].Item[15];
			Actors[0].Item[17] += Actors[1].Item[17];
			Actors[0].Item[18] += Actors[1].Item[18];
			System.MessageName = { "" };
			System.MessageContent = { "公主承接了勇者的信念，各项能力增加了" };
			System.MessageHead = { -1 };
		}
		else {
			Actors[1].Hp += Actors[0].Hp;
			Actors[1].Atk += Actors[0].Atk;
			Actors[1].Def += Actors[0].Def;
			Actors[1].Breath = Actors[1].BreathLimit - 1;
			Actors[1].Status = 0;
			System.GameVariables[5] = 0;
			Actors[1].Status = 0;
			Actors[1].Exp += Actors[0].Exp;
			Actors[1].Gold += Actors[0].Gold;
			Actors[1].Item[0] += Actors[0].Item[0];
			Actors[1].Item[1] += Actors[0].Item[1];
			Actors[1].Item[2] += Actors[0].Item[2];
			Actors[1].Item[5] += Actors[0].Item[5];
			Actors[1].Item[12] += Actors[0].Item[12];
			Actors[1].Item[13] += Actors[0].Item[13];
			Actors[1].Item[14] += Actors[0].Item[14];
			Actors[1].Item[15] += Actors[0].Item[15];
			Actors[1].Item[17] += Actors[0].Item[17];
			Actors[1].Item[18] += Actors[0].Item[18];
			System.MessageName = { "" };
			System.MessageContent = { "勇者承接了公主的信念，各项能力增加了" };
			System.MessageHead = { -1 };
		}
	}
	if (System.GameSwitches[16]) {
		System.GameBGM = "";
	}
	else if (System.GameVariables[3] == 0 && System.GameVariables[2] <= 1) {
		System.GameBGM = "sound-1.mp3";
	}
	else if (System.GameVariables[3] == 0 && System.GameVariables[2] > 1) {
		System.GameBGM = "sound-2.mp3";
	}
	else if ((System.GameVariables[3] == 1 || System.GameVariables[3] == 2) && !System.GameSwitches[15]) {
		System.GameBGM = "sound-1.mp3";
	}
	else if (((System.GameVariables[3] == 1 || System.GameVariables[3] == 2) && System.GameSwitches[15]) || System.GameVariables[3] == 3 || System.GameVariables[3] == 4 || System.GameVariables[3] == 5 || System.GameVariables[3] == 6) {
		System.GameBGM = "sound-3.mp3";
	}
	else if (System.GameVariables[3] == 7) {
		System.GameBGM = "sound-4.mp3";
	}
	if (record != System.GameBGM) {
		mciSendString("close BGM", NULL, 0, NULL);
		mciSendString(("open res\\sound\\" + System.GameBGM + " alias BGM").c_str(), NULL, 0, NULL);
		record = System.GameBGM;
		mciSendString("play BGM repeat", NULL, 0, NULL);
	}
	if (monsterbookwindow.Visible || encyclopediawindow.Visible) {
		MonsterBookUpdate();
		return;
	}
	if (hintwindow.Visible || goldshopwindow.Visible || expshopwindow.Visible || keyshopwindow.Visible || sdoorshopwindow.Visible || recyshopwindow.Visible || flywindow.Visible || skillwindow.Visible || defensewindow.Visible || drugwindow.Visible) {
		return;
	}
	if (filewindow.Visible) {
		FileUpdate();
		return;
	}
	if (System.ShopType != 0) {
		ShopUpdate();
		return;
	}
	if (!System.MessageContent.empty()) {
		messagewindow.Visible = true;
		MessageUpdate();
		return;
	}
	if (System.BattleEnemyID >= 0) {
		BattleFunction();
	}
	if (System.TransformingEventName != "") {
		System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].Name = System.TransformingEventName;
		System.TransformingEventName = "";
		if (System.DirectlyFunction) {
			System.DirectlyFunction = false;
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].Order();
		}
	}
	if (System.ScreenShot) {
		saveimage(_T(System.ShotFile.c_str()));
		System.ScreenShot = false;
		System.ShotFile = "";
		return;
	}
	ShortcutKey();
	Player.Update();
}

void GameMap::ShortcutKey() {
	if (KeyBoard.Trigger(KeyBoard.KeyS)) {
		System.GameSwitches[16] = !System.GameSwitches[16];
	}
	if (KeyBoard.Trigger(KeyBoard.KeyB) && Actors[System.GameVariables[1]].Item[15] > 0) {
		drugwindow.Index = 0;
		drugwindow.Visible = true;
		return;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyN) && System.GameSwitches[15] && !System.GameSwitches[21]) {
		PlaySE("mting-39.wav");
		GameSprite white("mting-1248.png");
		white.X = System.MapX;
		white.Y = System.MapY;
		white.Opacity = 0;
		rfor(i, 0, 15) {
			white.Opacity += 17;
			Graphics.Update();
		}
		rfor(i, 0, 5) {
			Graphics.Update();
		}
		Player.Direction = 0;
		swap(System.GameVariables[3], System.GameVariables[26]);
		swap(System.GameVariables[2], System.GameVariables[27]);
		swap(System.GameVariables[5], System.GameVariables[29]);
		System.GameVariables[1] = !System.GameVariables[1];
		System.NeedRefresh = true;
		rfor(i, 0, 15) {
			white.Opacity -= 17;
			Graphics.Update();
		}
		white.Dispose();
		return;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyT) && System.GameSwitches[11] && Actors[System.GameVariables[1]].Item[5] > 0) {
		int dir[4][2] = { {0,1}, {-1,0}, {1,0}, {0,-1} };
		if (System.Maps[Actors[System.GameVariables[1]].MapID].HaveAnEvent(Actors[System.GameVariables[1]].X + dir[Player.Direction][0], Actors[System.GameVariables[1]].Y + dir[Player.Direction][1])) {
			int id = System.Maps[Actors[System.GameVariables[1]].MapID].CheckEvent(Actors[System.GameVariables[1]].X + dir[Player.Direction][0], Actors[System.GameVariables[1]].Y + dir[Player.Direction][1]);
			vector <string> name = Split(System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[id].Name, "|");
			if (name[0] == "SWALL") {
				--Actors[System.GameVariables[1]].Item[5];
				PlaySE(System.DecisionSE);
				if (name.size() == 2) {
					System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[id].Name = "SDOOR|" + name[1];
				}
				else {
					System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[id].Name = "SDOOR";
				}
				System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[id].File[0] = "mting-35.png";
				System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[id].File[1] = "mting-35.png";
				System.NeedRefresh = true;
			}
			else if (name[0] == "ICE") {
				--Actors[System.GameVariables[1]].Item[5];
				PlaySE(System.DecisionSE);
				System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[id].Exist = false;
			}
			else {
				PlaySE(System.BuzzerSE);
			}
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyL)) {
		hintwindow.Page = 0;
		hintwindow.Visible = true;
		return;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyW) && System.GameSwitches[12]) {
		skillwindow.Index = 0;
		skillwindow.Visible = true;
		return;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyH) && System.GameSwitches[13]) {
		defensewindow.Index = 0;
		defensewindow.Visible = true;
		return;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyR)) {
		if (YesNoPrint("你确定要放弃当前进度，返回标题吗？") == IDYES) {
			System.Scene = new GameTitle;
		}
		return;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyD)) {
		if (Actors[System.GameVariables[1]].Item[3] == 0) {
			return;
		}
		monsterbookwindow.Index = 0;
		monsterbookwindow.Page = 0;
		monsterbookwindow.FloorEnemies.clear();
		for (auto ev : System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents) {
			if (Split(ev.Name, "|")[0] == "MONSTER" && ev.Exist) {
				int id = stoi(Split(ev.Name, "|")[1]);
				if (!VectorFind(monsterbookwindow.FloorEnemies, id)) {
					monsterbookwindow.FloorEnemies.push_back(id);
				}
			}
		}
		sort(monsterbookwindow.FloorEnemies.begin(), monsterbookwindow.FloorEnemies.end(), [](const int& a, const int& b) {
			if (get<0>(Enemies[a].GotDamage()) != get<0>(Enemies[b].GotDamage())) {
				return (get<0>(Enemies[a].GotDamage()) < get<0>(Enemies[b].GotDamage()));
			}
			return (Enemies[a].Name < Enemies[b].Name);
		});
		monsterbookwindow.Visible = true;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyF)) {
		if (Actors[System.GameVariables[1]].Item[4] == 0) {
			return;
		}
		if (System.GameSwitches[3]) {
			PlaySE(System.BuzzerSE);
			return;
		}
		for (auto ev : System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents) {
			if (!ev.Exist) {
				continue;
			}
			vector <string> name = Split(ev.Name, "|");
			if (name[0] != "MONSTER") {
				continue;
			}
			if (Enemies[stoi(name[1])].GotP(17)) {
				PlaySE(System.BuzzerSE);
				return;
			}
		}
		flywindow.update = true;
		flywindow.viewmapid = Actors[System.GameVariables[1]].MapID;
		flywindow.viewfloorid = System.GameVariables[2];
		flywindow.Visible = true;
		return;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyU)) {
		filewindow.Visible = true;
		cursorwindow.load = false;
		cursorwindow.Visible = true;
		cursorwindow.Active = true;
		fstream file;
		file.open("save\\recent.dat", ios::in);
		char buffer[128];
		file.getline(buffer, 128);
		file.close();
		int index = atoi(buffer);
		cursorwindow.Page = index / 6;
		cursorwindow.Index = index % 6;
		return;
	}
	if (KeyBoard.Trigger(KeyBoard.KeyI)) {
		filewindow.Visible = true;
		cursorwindow.load = true;
		cursorwindow.Visible = true;
		cursorwindow.Active = true;
		fstream file;
		file.open("save\\recent.dat", ios::in);
		char buffer[128];
		file.getline(buffer, 128);
		file.close();
		int index = atoi(buffer);
		cursorwindow.Page = index / 6;
		cursorwindow.Index = index % 6;
		return;
	}
	if (KeyBoard.DoubleClick(VK_LCONTROL)) {
		int index = 0;
		rfor(i, 0, 600) {
			unless(ExistFile("save\\save" + to_string(i) + ".sav")) {
				index = i;
				break;
			}
		}
		SaveData(index);
		PlaySE(System.SaveSE);
		System.MessageName.push_back("");
		System.MessageContent.push_back("进度已保存至存档 " + to_string(index) + "！");
		System.MessageHead.push_back(0);
		return;
	}
	if (KeyBoard.DoubleClick(VK_RCONTROL)) {
		fstream file;
		file.open("save\\recent.dat", ios::in);
		char buffer[128];
		file.getline(buffer, 128);
		file.close();
		int index = atoi(buffer);
		PlaySE("mting-78.wav");
		GameSprite stair("mting.png");
		stair.X = System.MapX;
		stair.Y = System.MapY;
		stair.Opacity = 0;
		rfor(i, 0, 15) {
			stair.Opacity += 17;
			Graphics.Update();
		}
		LoadData(index);
		rfor(i, 0, 5) {
			Graphics.Update();
		}
		System.NeedRefresh = true;
		rfor(i, 0, 15) {
			stair.Opacity -= 17;
			Graphics.Update();
		}
		stair.Dispose();
		return;
	}
}

void GameMap::MessageUpdate() {
	if (KeyBoard.RepeatConfirm()) {
		System.MessageContent.erase(System.MessageContent.begin());
		System.MessageName.erase(System.MessageName.begin());
		System.MessageHead.erase(System.MessageHead.begin());
		return;
	}
}

int GameMap::BattleUpdate() {
	DataMap::WaitCount(2);
	int adam, edam, conatk, animationid, freezed = 0, doubled = 0, conatk2 = 2, rounding = 0;
	bool turn = true, king = false, bigsword = false;
	battlewindow.Accelerate = false;
	if (Enemies[System.BattleEnemyID].GotP(5)) {
		turn = false;
	}
	if (Enemies[System.BattleEnemyID].GotP(34)) {
		rounding = 8;
	}
	loop{
		conatk = max(Enemies[System.BattleEnemyID].Conatk, 1);
		if (turn) {
			if (battlewindow.funckey == 1) {
				return 2;
			}
			if (freezed > 0) {
				if (freezed == 1) {
					freezed = 0;
				}
				--freezed;
				turn = false;
				continue;
			}
			conatk2 = 2;
			do {
				edam = battlewindow.aAtk > battlewindow.eDef ? battlewindow.aAtk - battlewindow.eDef : 0;
				if (king) {
					edam /= 3;
				}
				animationid = System.GameVariables[14];
				if (edam <= 0) {
					battlewindow.funckey = 0;
					animationid = 9;
				}
				else {
					if (rand() % 100 + 1 <= battlewindow.aFatigue) {
						battlewindow.funckey = 0;
						animationid = 8;
						edam = 0;
					}
					else {
						if (battlewindow.funckey == 3 && edam > 0) {
							Actors[System.GameVariables[1]].Breath -= Actors[System.GameVariables[1]].BreathLimit / 6;
							battlewindow.aFatigue += 3;
							animationid = 16;
							edam = edam * 2.25 + Actors[System.GameVariables[1]].Mdef * 2;
							if (Enemies[System.BattleEnemyID].GotP(11)) {
								edam /= 2;
							}
							battlewindow.funckey = 0;
						}
						if (battlewindow.funckey == 5) {
							Actors[System.GameVariables[1]].Breath -= Actors[System.GameVariables[1]].BreathLimit / 3;
							battlewindow.aFatigue += 10;
							animationid = 58;
							edam = battlewindow.eHp * 3 / 4 + battlewindow.aMdef;
							king = true;
							battlewindow.funckey = 0;
						}
						if (Enemies[System.BattleEnemyID].GotP(25) && (battlewindow.eBreath == 0 || battlewindow.eBreath >= Enemies[System.BattleEnemyID].Breath)) {
							edam = 0;
						}
						if (battlewindow.funckey == 2 && edam > 0) {
							Actors[System.GameVariables[1]].Breath -= Actors[System.GameVariables[1]].BreathLimit / 6;
							battlewindow.aFatigue += 2;
							++animationid;
							edam *= 2;
							battlewindow.funckey = 0;
						}
						else {
							Actors[System.GameVariables[1]].Breath = min(edam > 0 ? (Actors[System.GameVariables[1]].Breath + Round(1.0 * battlewindow.eDef / battlewindow.aAtk * 6)) : Actors[System.GameVariables[1]].Breath, Actors[System.GameVariables[1]].BreathLimit - 1);
						}
					}
				}
				if (edam > 0) {
					if (!Enemies[System.BattleEnemyID].GotP(11)) {
						edam += battlewindow.aMdef;
					}
					if (battlewindow.funckey == 4) {
						Actors[System.GameVariables[1]].Breath -= Actors[System.GameVariables[1]].BreathLimit / 6;
						battlewindow.aFatigue += 4;
						animationid = 40;
						edam = min(battlewindow.eHp - 1, edam);
						int heal = edam * 0.7 + battlewindow.aMdef * 2;
						Graphics.Damages.push({ battlewindow.X + battlewindow.Width - 48, battlewindow.Y + 64, 0, to_string(heal), GameWindow::TextColor("green") });
						Actors[System.GameVariables[1]].Hp += heal;
						battlewindow.funckey = 0;
					}
				}
				battlewindow.eBreath = min(edam > 0 ? (battlewindow.eBreath + Round(edam / 3.0)) : battlewindow.eBreath, Enemies[System.BattleEnemyID].Breath);
				battlewindow.eHp = max(battlewindow.eHp - edam, 0);
				Graphics.Animations.push({ battlewindow.X + 48, battlewindow.Y + 48, 0, Animation[animationid] });
				Graphics.Damages.push({ battlewindow.X + 32, battlewindow.Y + 64, 0, to_string(edam), GameWindow::TextColor("red") });
				DataMap::WaitCount(Animation[animationid].Pattern.size());
				if (!battlewindow.Accelerate) {
					DataMap::WaitCount(3);
				}
				if (battlewindow.eHp <= 0) {
					if (rounding > 0) {
						--rounding;
						battlewindow.eAtk *= 1.1;
						battlewindow.eDef *= 1.1;
						battlewindow.eHp = Enemies[System.BattleEnemyID].Hp * pow(1.3, 8 - rounding);
						battlewindow.eFatigue = 0;
						if (Actors[System.GameVariables[1]].Breath >= Actors[System.GameVariables[1]].BreathLimit / 6) {
							Actors[System.GameVariables[1]].Breath -= Actors[System.GameVariables[1]].BreathLimit / 6;
							battlewindow.eBreath = min(Enemies[System.BattleEnemyID].Breath, battlewindow.eBreath + Actors[System.GameVariables[1]].BreathLimit / 6);
						}
						else {
							battlewindow.eBreath = min(Enemies[System.BattleEnemyID].Breath, battlewindow.eBreath + Actors[System.GameVariables[1]].Breath);
							Actors[System.GameVariables[1]].Breath = 0;
						}
						king = false;
						Graphics.Animations.push({ battlewindow.X + 48, battlewindow.Y + 32, 0, Animation[15] });
						Graphics.Animations.push({ battlewindow.X + battlewindow.Width - 64, battlewindow.Y + 32, 0, Animation[15] });
					}
					else {
						Actors[System.GameVariables[1]].Exp += Enemies[System.BattleEnemyID].Exp;
						Actors[System.GameVariables[1]].Gold += Enemies[System.BattleEnemyID].Gold;
						PlaySE("mting-69.wav");
						return 0;
					}
				}
			} while (--conatk2 && battlewindow.sword);
			if (battlewindow.sword) {
				--battlewindow.sword;
			}
		}
		else {
			while (conatk--) {
				if (battlewindow.funckey == 1) {
					return 2;
				}
				if (Enemies[System.BattleEnemyID].GotP(33) && rand() % 4 == 0) {
					swap(battlewindow.eAtk, battlewindow.eDef);
				}
				adam = max(0, battlewindow.eAtk - (Enemies[System.BattleEnemyID].GotP(6) ? 0 : (Enemies[System.BattleEnemyID].GotP(27) ? battlewindow.aDef / 2 : battlewindow.aDef)));
				if (Enemies[System.BattleEnemyID].GotP(23) && adam > 0) {
					adam *= QuickPow(2, doubled++);
				}
				if (Enemies[System.BattleEnemyID].GotP(13) && battlewindow.eAtk >= battlewindow.aDef) {
					adam *= 2;
				}
				animationid = Enemies[System.BattleEnemyID].AnimationID;
				if (adam <= 0) {
					animationid = 9;
				}
				else {
					if (rand() % 100 + 1 <= battlewindow.eFatigue) {
						animationid = 8;
						adam = 0;
					}
					else {
						if (Enemies[System.BattleEnemyID].GotP(26) && Actors[System.GameVariables[1]].Breath >= Actors[System.GameVariables[1]].BreathLimit / 6) {
							Actors[System.GameVariables[1]].Breath -= Actors[System.GameVariables[1]].BreathLimit / 6;
							battlewindow.eFatigue += 2;
							++animationid;
							if (Enemies[System.BattleEnemyID].GotP(20)) {
								Actors[System.GameVariables[1]].Breath = max(Actors[System.GameVariables[1]].Breath - Actors[System.GameVariables[1]].BreathLimit / 3, 0);
								battlewindow.aFatigue += stoi(Split(Enemies[System.BattleEnemyID].Name, "|")[1]);
							}
							if (Enemies[System.BattleEnemyID].GotP(14)) {
								adam *= 5;
								int lost = battlewindow.eHp / 2;
								battlewindow.eHp -= lost;
								Graphics.Damages.push({ battlewindow.X + 32, battlewindow.Y + 64, 0, to_string(lost), GameWindow::TextColor("red") });
							}
							else if (Enemies[System.BattleEnemyID].GotP(10)) {
								adam *= 3;
							}
							else {
								adam *= 2;
							}
						}
						else {
							if ((battlewindow.eBreath >= Enemies[System.BattleEnemyID].Breath || bigsword) && adam > 0) {
								battlewindow.eBreath = 0;
								battlewindow.eFatigue += 2;
								++animationid;
								if (Enemies[System.BattleEnemyID].GotP(31)) {
									bigsword = true;
								}
								if (Enemies[System.BattleEnemyID].GotP(20)) {
									Actors[System.GameVariables[1]].Breath = max(Actors[System.GameVariables[1]].Breath - Actors[System.GameVariables[1]].BreathLimit / 3, 0);
									battlewindow.aFatigue += stoi(Split(Enemies[System.BattleEnemyID].Name, "|")[1]);
								}
								if (Enemies[System.BattleEnemyID].GotP(14)) {
									adam *= 5;
									int lost = battlewindow.eHp / 2;
									battlewindow.eHp -= lost;
									Graphics.Damages.push({ battlewindow.X + 32, battlewindow.Y + 64, 0, to_string(lost), GameWindow::TextColor("red") });
								}
								else if (Enemies[System.BattleEnemyID].GotP(32)) {
									adam *= 6;
								}
								else if (Enemies[System.BattleEnemyID].GotP(10)) {
									adam *= 3;
								}
								else {
									adam *= 2;
								}
							}
							else {
								battlewindow.eBreath = min(adam > 0 ? (battlewindow.eBreath + Round(1.0 * battlewindow.aDef / battlewindow.aAtk * 6)) : battlewindow.eBreath, Enemies[System.BattleEnemyID].Breath);
							}
						}
					}
				}
				if (Enemies[System.BattleEnemyID].GotP(9)) {
					battlewindow.aFatigue += stoi(Split(Enemies[System.BattleEnemyID].Name, "|")[1]);
				}
				if (Enemies[System.BattleEnemyID].GotP(1)) {
					if (Actors[System.GameVariables[1]].Status == 0) {
						if (rand() % 4 == 0) {
							Actors[System.GameVariables[1]].Status = 1;
							Graphics.Animations.push({ battlewindow.X + battlewindow.Width - 64, battlewindow.Y + 32, 0, Animation[14] });
						}
					}
				}
				if (Enemies[System.BattleEnemyID].GotP(2)) {
					if (Actors[System.GameVariables[1]].Status != 1) {
						if (rand() % 4 == 0) {
							Actors[System.GameVariables[1]].Status = 2;
							Graphics.Animations.push({ battlewindow.X + battlewindow.Width - 64, battlewindow.Y + 32, 0, Animation[14] });
							System.GameVariables[5] += stoi(Split(Enemies[System.BattleEnemyID].Name, "|")[1]);
						}
					}
				}
				if (Enemies[System.BattleEnemyID].GotP(29)) {
					if (rand() % 4 == 0) {
						battlewindow.aAtk -= stoi(Split(Enemies[System.BattleEnemyID].Name, "|")[1]);
						battlewindow.aDef -= stoi(Split(Enemies[System.BattleEnemyID].Name, "|")[1]);
						Graphics.Animations.push({ battlewindow.X + battlewindow.Width - 64, battlewindow.Y + 32, 0, Animation[15] });
					}
				}
				if (Enemies[System.BattleEnemyID].GotP(30)) {
					if (rand() % 4 == 0) {
						if (Actors[System.GameVariables[1]].Status == 0) {
							Actors[System.GameVariables[1]].Status = 1;
							Graphics.Animations.push({ battlewindow.X + battlewindow.Width - 64, battlewindow.Y + 32, 0, Animation[14] });
						}
						else if (Actors[System.GameVariables[1]].Status == 1) {
							battlewindow.eAtk += stoi(Split(Enemies[System.BattleEnemyID].Name, "|")[1]);
							battlewindow.eDef += stoi(Split(Enemies[System.BattleEnemyID].Name, "|")[1]);
							Graphics.Animations.push({ battlewindow.X + 48, battlewindow.Y + 32, 0, Animation[15] });
						}
					}
				}
				if (Enemies[System.BattleEnemyID].GotP(3)) {
					int recover = adam * stoi(Split(Enemies[System.BattleEnemyID].Name, "|")[1]) / 100;
					battlewindow.eHp += recover;
					if (adam > 0) {
						Graphics.Damages.push({ battlewindow.X + 32, battlewindow.Y + 64, 0, to_string(recover), GameWindow::TextColor("green") });
					}
				}
				if (Enemies[System.BattleEnemyID].GotP(12)) {
					if (battlewindow.aMdef > 0) {
						if (rand() % 4 == 0) {
							battlewindow.aMdef = max(battlewindow.aMdef - stoi(Split(Enemies[System.BattleEnemyID].Name, "|")[1]), 0);
							Graphics.Animations.push({ battlewindow.X + battlewindow.Width - 64, battlewindow.Y + 32, 0, Animation[14] });
						}
					}
				}
				if (Enemies[System.BattleEnemyID].GotP(18) && freezed >= 0) {
					if (rand() % 4 == 0) {
						freezed = stoi(Split(Enemies[System.BattleEnemyID].Name, "|")[1]);
						Graphics.Animations.push({ battlewindow.X + battlewindow.Width - 64, battlewindow.Y + 32, 0, Animation[14] });
					}
				}
				if (battlewindow.funckey == 6) {
					Actors[System.GameVariables[1]].Breath -= Actors[System.GameVariables[1]].BreathLimit / 6;
					battlewindow.aFatigue += 5;
					animationid = 26;
					battlewindow.funckey = 0;
					adam = max(adam * 2 / 3 - battlewindow.aMdef, 0);
				}
				if (battlewindow.funckey == 7) {
					Actors[System.GameVariables[1]].Breath -= Actors[System.GameVariables[1]].BreathLimit / 6;
					battlewindow.aFatigue += 3;
					animationid = 49;
					battlewindow.funckey = 0;
					battlewindow.eHp = max(battlewindow.eHp - adam - battlewindow.aMdef, 0);
					Graphics.Damages.push({ battlewindow.X + 32, battlewindow.Y + 64, 0, to_string(adam + battlewindow.aMdef), GameWindow::TextColor("red") });
					adam = max(adam - battlewindow.aMdef * 2, 0);
				}
				if (battlewindow.funckey == 8) {
					Actors[System.GameVariables[1]].Breath -= Actors[System.GameVariables[1]].BreathLimit / 3;
					battlewindow.aFatigue += 10;
					animationid = 59;
					adam = 0;
					Actors[System.GameVariables[1]].Breath = min(Actors[System.GameVariables[1]].BreathLimit - 1, Actors[System.GameVariables[1]].Breath + battlewindow.eBreath);
					battlewindow.eBreath = 0;
					battlewindow.funckey = 0;
				}
				if (battlewindow.defense) {
					--battlewindow.defense;
					animationid = 49;
					battlewindow.funckey = 0;
					battlewindow.eHp = max(battlewindow.eHp - adam, 0);
					Graphics.Damages.push({ battlewindow.X + 32, battlewindow.Y + 64, 0, to_string(adam + battlewindow.aMdef), GameWindow::TextColor("red") });
					adam = 0;
				}
				if (!Enemies[System.BattleEnemyID].GotP(20)) {
					Actors[System.GameVariables[1]].Breath = min(adam > 0 ? (Actors[System.GameVariables[1]].Breath + Round(adam / 10.0)) : Actors[System.GameVariables[1]].Breath, Actors[System.GameVariables[1]].BreathLimit - 1);
				}
				Actors[System.GameVariables[1]].Hp = max(Actors[System.GameVariables[1]].Hp - adam, 0);
				Graphics.Animations.push({ battlewindow.X + battlewindow.Width - 48, battlewindow.Y + 48, 0, Animation[animationid] });
				Graphics.Damages.push({ battlewindow.X + battlewindow.Width - 48, battlewindow.Y + 64, 0, to_string(adam), GameWindow::TextColor("red") });
				DataMap::WaitCount(Animation[Enemies[System.BattleEnemyID].AnimationID].Pattern.size());
				if (!battlewindow.Accelerate) {
					DataMap::WaitCount(3);
				}
				if (Actors[System.GameVariables[1]].Hp <= 0) {
					DataMap::WaitCount(3);
					return 1;
				}
				if (battlewindow.eHp <= 0) {
					if (rounding > 0) {
						--rounding;
						battlewindow.eAtk *= 1.1;
						battlewindow.eDef *= 1.1;
						battlewindow.eHp = Enemies[System.BattleEnemyID].Hp * pow(1.3, 8 - rounding);
						battlewindow.eFatigue = 0;
						if (Actors[System.GameVariables[1]].Breath >= Actors[System.GameVariables[1]].BreathLimit / 6) {
							Actors[System.GameVariables[1]].Breath -= Actors[System.GameVariables[1]].BreathLimit / 6;
							battlewindow.eBreath = min(Enemies[System.BattleEnemyID].Breath, battlewindow.eBreath + Actors[System.GameVariables[1]].BreathLimit / 6);
						}
						else {
							battlewindow.eBreath = min(Enemies[System.BattleEnemyID].Breath, battlewindow.eBreath + Actors[System.GameVariables[1]].Breath);
							Actors[System.GameVariables[1]].Breath = 0;
						}
						king = false;
						Graphics.Animations.push({ battlewindow.X + 48, battlewindow.Y + 32, 0, Animation[15] });
						Graphics.Animations.push({ battlewindow.X + battlewindow.Width - 64, battlewindow.Y + 32, 0, Animation[15] });
					}
					else {
						Actors[System.GameVariables[1]].Exp += Enemies[System.BattleEnemyID].Exp;
						Actors[System.GameVariables[1]].Gold += Enemies[System.BattleEnemyID].Gold;
						PlaySE("mting-69.wav");
						return 0;
					}
				}
			}
		}
		bigsword = false;
		turn = !turn;
	}
}

void GameMap::GameOver() {
	mciSendString("stop BGM", NULL, 0, NULL);
	PlaySE("mting-75.wav");
	GameSprite gg("mting-1268.png");
	gg.X = System.MapX + 16;
	gg.Y = System.MapY + 181;
	gg.Opacity = 0;
	rfor(i, 0, 85) {
		gg.Opacity += 3;
		gg.Y -= 1;
		Graphics.Update();
	}
	DataMap::WaitCount(120);
	gg.Dispose();
	System.Scene = new GameTitle;
}

void GameMap::MonsterBookUpdate() {
	if (encyclopediawindow.Visible) {
		if (KeyBoard.TriggerConfirm() || KeyBoard.TriggerCancel()) {
			encyclopediawindow.Visible = false;
			monsterbookwindow.Visible = true;
			return;
		}
		return;
	}
	if (KeyBoard.TriggerConfirm() && !monsterbookwindow.FloorEnemies.empty()) {
		encyclopediawindow.eid = monsterbookwindow.FloorEnemies[monsterbookwindow.Page * 5 + monsterbookwindow.Index];
		encyclopediawindow.Visible = true;
		monsterbookwindow.Visible = false;
		return;
	}
}

void GameMap::FileUpdate() {
	filewindow.fileid = cursorwindow.Page * 6 + cursorwindow.Index;
	if (cursorwindow.load) {
		if (KeyBoard.Trigger(KeyBoard.KeyI) || KeyBoard.TriggerCancel()) {
			PlaySE(System.CancelSE);
			filewindow.Visible = false;
			cursorwindow.Visible = false;
			cursorwindow.Active = false;
			cursorwindow.Page = 0;
			cursorwindow.Index = 0;
			return;
		}
		if (KeyBoard.TriggerConfirm()) {
			if (!ExistFile("save\\save" + to_string(filewindow.fileid) + ".sav")) {
				PlaySE(System.BuzzerSE);
				return;
			}
			PlaySE("mting-78.wav");
			filewindow.Visible = false;
			cursorwindow.Visible = false;
			cursorwindow.Active = false;
			cursorwindow.Page = 0;
			cursorwindow.Index = 0;
			GameSprite stair("mting.png");
			stair.X = System.MapX;
			stair.Y = System.MapY;
			stair.Opacity = 0;
			rfor(i, 0, 15) {
				stair.Opacity += 17;
				Graphics.Update();
			}
			LoadData(filewindow.fileid);
			rfor(i, 0, 5) {
				Graphics.Update();
			}
			System.NeedRefresh = true;
			rfor(i, 0, 15) {
				stair.Opacity -= 17;
				Graphics.Update();
			}
			stair.Dispose();
			return;
		}
	}
	else {
		if (KeyBoard.Trigger(KeyBoard.KeyU) || KeyBoard.TriggerCancel()) {
			PlaySE(System.CancelSE);
			filewindow.Visible = false;
			cursorwindow.Visible = false;
			cursorwindow.Active = false;
			cursorwindow.Page = 0;
			cursorwindow.Index = 0;
			return;
		}
		if (KeyBoard.TriggerConfirm()) {
			PlaySE(System.SaveSE);
			filewindow.Visible = false;
			cursorwindow.Visible = false;
			cursorwindow.Active = false;
			cursorwindow.Page = 0;
			cursorwindow.Index = 0;
			SaveData(filewindow.fileid);
			System.MessageName.push_back("");
			System.MessageContent.push_back("进度已保存至存档 " + to_string(filewindow.fileid) + "！");
			System.MessageHead.push_back(0);
			return;
		}
	}
}

void GameMap::ShopUpdate() {
	if (System.ShopType == 1) {
		goldshopwindow.Index = 0;
		goldshopwindow.ShopID = System.ShopID;
		goldshopwindow.Visible = true;
		System.ShopType = 0;
		return;
	}
	if (System.ShopType == 2) {
		expshopwindow.Index = 0;
		expshopwindow.ShopID = System.ShopID;
		expshopwindow.Visible = true;
		System.ShopType = 0;
		return;
	}
	if (System.ShopType == 3) {
		keyshopwindow.Index = 0;
		keyshopwindow.Visible = true;
		System.ShopType = 0;
		return;
	}
	if (System.ShopType == 4) {
		sdoorshopwindow.Index = 0;
		sdoorshopwindow.Visible = true;
		System.ShopType = 0;
		return;
	}
	if (System.ShopType == 5) {
		recyshopwindow.Index = 0;
		recyshopwindow.Visible = true;
		System.ShopType = 0;
		return;
	}
}

void GameMap::BattleFunction() {
	battlewindow.aAtk = Actors[System.GameVariables[1]].Atk - System.GameVariables[5];
	battlewindow.aDef = Actors[System.GameVariables[1]].Def - System.GameVariables[5];
	battlewindow.aMdef = Actors[System.GameVariables[1]].Mdef;
	battlewindow.aFatigue = 0;
	battlewindow.eHp = Enemies[System.BattleEnemyID].Hp;
	battlewindow.eAtk = Enemies[System.BattleEnemyID].GotAtk();
	battlewindow.eDef = Enemies[System.BattleEnemyID].GotDef();
	battlewindow.eBreath = 0;
	battlewindow.eFatigue = 0;
	battlewindow.funckey = 0;// Escape 1;Critical 2;Attack Skill 3;Defense Skill 4
	battlewindow.sword = 0;
	battlewindow.defense = 0;
	battlewindow.Visible = true;
	int speed = System.FrameRate;
	int result = BattleUpdate();// Win 0;Lose 1;Escape 2
	System.FrameRate = speed;
	if (result == 0) {
		if (Enemies[System.BattleEnemyID].GotP(8)) {
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].Name = "MONSTER|" + Split(Enemies[System.BattleEnemyID].Name, "|")[2];
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].File[0] = Enemies[stoi(Split(Enemies[System.BattleEnemyID].Name, "|")[2])].File[0];
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].File[1] = Enemies[stoi(Split(Enemies[System.BattleEnemyID].Name, "|")[2])].File[1];
			System.NeedRefresh = true;
		}
		else if (Enemies[System.BattleEnemyID].GotP(21)) {
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].Name = "BARRIER|50";
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].File[0] = "mting-28.png";
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].File[1] = "mting-29.png";
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].Through = true;
			System.NeedRefresh = true;
		}
		else if (Enemies[System.BattleEnemyID].GotP(22)) {
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].Name = "ICE";
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].File[0] = "mting-245.png";
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].File[1] = "mting-245.png";
			System.NeedRefresh = true;
		}
		else if (Enemies[System.BattleEnemyID].GotP(24)) {
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].Name = "BARRIER|50";
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].File[0] = "mting-28.png";
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].File[1] = "mting-29.png";
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].Through = true;
			int x = System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].X, y = System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].Y;
			GameEvent tem;
			int dir[][2] = { {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1} };
			rfor(i, 0, 9) {
				if (System.Maps[Actors[System.GameVariables[1]].MapID].HaveAnEEvent(x + dir[i][0], y + dir[i][1])) {
					if (!System.Maps[Actors[System.GameVariables[1]].MapID].ECheckEvent(x + dir[i][0], y + dir[i][1])->Exist) {
						System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.Maps[Actors[System.GameVariables[1]].MapID].CheckEvent(x + dir[i][0], y + dir[i][1])].Exist = true;
						System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.Maps[Actors[System.GameVariables[1]].MapID].CheckEvent(x + dir[i][0], y + dir[i][1])].Through = true;
						System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.Maps[Actors[System.GameVariables[1]].MapID].CheckEvent(x + dir[i][0], y + dir[i][1])].Name = "BARRIER|50";
						System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.Maps[Actors[System.GameVariables[1]].MapID].CheckEvent(x + dir[i][0], y + dir[i][1])].File[0] = "mting-28.png";
						System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.Maps[Actors[System.GameVariables[1]].MapID].CheckEvent(x + dir[i][0], y + dir[i][1])].File[1] = "mting-29.png";
					}
				}
				else {
					tem.Name = "BARRIER|50";
					tem.File[0] = "mting-28.png";
					tem.File[1] = "mting-29.png";
					tem.X = x + dir[i][0];
					tem.Y = y + dir[i][1];
					tem.TriggerCondition[0] = 0;
					tem.TriggerCondition[1] = 0;
					tem.TriggerCondition[2] = 0;
					tem.Through = true;
					tem.Exist = true;
					System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents.push_back(tem);
				}
			}
			System.NeedRefresh = true;
		}
		else if (Enemies[System.BattleEnemyID].GotP(28)) {
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].Name = "ICE";
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].File[0] = "mting-245.png";
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].File[1] = "mting-245.png";
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].Through = false;
			int x = System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].X, y = System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].Y;
			GameEvent tem;
			int dir[][2] = { {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1} };
			rfor(i, 0, 9) {
				if (System.Maps[Actors[System.GameVariables[1]].MapID].HaveAnEEvent(x + dir[i][0], y + dir[i][1])) {
					if (!System.Maps[Actors[System.GameVariables[1]].MapID].ECheckEvent(x + dir[i][0], y + dir[i][1])->Exist && !(Actors[System.GameVariables[1]].X == x + dir[i][0] && Actors[System.GameVariables[1]].Y == y + dir[i][1])) {
						System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.Maps[Actors[System.GameVariables[1]].MapID].CheckEvent(x + dir[i][0], y + dir[i][1])].Exist = true;
						System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.Maps[Actors[System.GameVariables[1]].MapID].CheckEvent(x + dir[i][0], y + dir[i][1])].Through = false;
						System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.Maps[Actors[System.GameVariables[1]].MapID].CheckEvent(x + dir[i][0], y + dir[i][1])].Name = "ICE";
						System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.Maps[Actors[System.GameVariables[1]].MapID].CheckEvent(x + dir[i][0], y + dir[i][1])].File[0] = "mting-245.png";
						System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.Maps[Actors[System.GameVariables[1]].MapID].CheckEvent(x + dir[i][0], y + dir[i][1])].File[1] = "mting-245.png";
					}
				}
				else {
					if (!(Actors[System.GameVariables[1]].X == x + dir[i][0] && Actors[System.GameVariables[1]].Y == y + dir[i][1])) {
						tem.Name = "ICE";
						tem.File[0] = "mting-245.png";
						tem.File[1] = "mting-245.png";
						tem.X = x + dir[i][0];
						tem.Y = y + dir[i][1];
						tem.TriggerCondition[0] = 0;
						tem.TriggerCondition[1] = 0;
						tem.TriggerCondition[2] = 0;
						tem.Through = false;
						tem.Exist = true;
						System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents.push_back(tem);
					}
				}
			}
			System.NeedRefresh = true;
		}
		else if (System.BattleEnemyID == 92) {
			System.TransformingEventName = "NPC|31";
			System.DirectlyFunction = true;
		}
		else {
			System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].Exist = false;
		}
	}
	else if (result == 1) {
		GameOver();
		return;
	}
	System.BattleEnemyID = -1;
	battlewindow.Visible = false;
	vector <string> tem = Split(System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.FunctioningEventID].Name, "|");
	if (result == 0 && tem.size() == 5) {
		if (stoi(tem[2]) == 1) {
			System.GameSwitches[stoi(tem[3])] = stoi(tem[4]);
		}
		else if (stoi(tem[2]) == 2) {
			System.GameVariables[stoi(tem[3])] += stoi(tem[4]);
		}
	}
}

void GameMap::LoadData(int fileid) {
	System.Reload();
	string filename = "save\\save" + to_string(fileid) + ".sav";
	ifstream inFile(filename, ios::in | ios::binary);
	char data[64];
	int siz1, siz2;
	Read(inFile, siz1);
	rfor(i, 0, siz1) {
		int fst, scd;
		Read(inFile, fst);
		Read(inFile, siz2);
		rfor(j, 0, siz2) {
			Read(inFile, scd);
			System.FloorRecord[fst].push_back(scd);
		}
	}
	Read(inFile, siz1);
	rfor(i, 0, siz1) {
		Read(inFile, data);
		Actors[i].Name = data;
		Read(inFile, data);
		Actors[i].File = data;
		Read(inFile, Actors[i].Status);
		Read(inFile, Actors[i].Level);
		Read(inFile, Actors[i].Hp);
		Read(inFile, Actors[i].Atk);
		Read(inFile, Actors[i].Def);
		Read(inFile, Actors[i].Mdef);
		Read(inFile, Actors[i].BreathLimit);
		Read(inFile, Actors[i].Breath);
		Read(inFile, Actors[i].Exp);
		Read(inFile, Actors[i].Gold);
		Read(inFile, Actors[i].Item);
		Read(inFile, Actors[i].MapID);
		Read(inFile, Actors[i].X);
		Read(inFile, Actors[i].Y);
	}
	Read(inFile, siz1);
	rfor(i, 0, siz1) {
		Read(inFile, data);
		System.Maps[i].MapName = data;
		Read(inFile, data);
		System.Maps[i].FloorName = data;
		Read(inFile, siz2);
		for (int j = 0; j < siz2; ++j) {
			if (j >= System.Maps[i].MapEvents.size()) {
				GameEvent temp;
				Read(inFile, data);
				temp.Name = data;
				Read(inFile, data);
				temp.File[0] = data;
				Read(inFile, data);
				temp.File[1] = data;
				Read(inFile, temp.X);
				Read(inFile, temp.Y);
				Read(inFile, temp.TriggerCondition);
				Read(inFile, temp.Exist);
				Read(inFile, temp.Through);
				System.Maps[i].MapEvents.push_back(temp);
			}
			else {
				Read(inFile, data);
				System.Maps[i].MapEvents[j].Name = data;
				Read(inFile, data);
				System.Maps[i].MapEvents[j].File[0] = data;
				Read(inFile, data);
				System.Maps[i].MapEvents[j].File[1] = data;
				Read(inFile, System.Maps[i].MapEvents[j].X);
				Read(inFile, System.Maps[i].MapEvents[j].Y);
				Read(inFile, System.Maps[i].MapEvents[j].TriggerCondition);
				Read(inFile, System.Maps[i].MapEvents[j].Exist);
				Read(inFile, System.Maps[i].MapEvents[j].Through);
			}
		}
	}
	Read(inFile, System.GameSwitches);
	Read(inFile, System.GameVariables);
	Read(inFile, System.ShopPrice);
	Read(inFile, System.ShopEXP);
	Read(inFile, System.ItemRecord);
	Read(inFile, System.GemRecord);
	Read(inFile, System.BottleRecord);
}

void GameMap::SaveData(int fileid) {
	string filename = "save\\save" + to_string(fileid) + ".sav";
	ofstream outFile(filename, ios::out | ios::binary);
	char data[64];
	int siz = System.FloorRecord.size();
	Write(outFile, siz);
	for (auto m : System.FloorRecord) {
		Write(outFile, m.first);
		int siz2 = m.second.size();
		Write(outFile, siz2);
		for (auto f : m.second) {
			Write(outFile, f);
		}
	}
	siz = Actors.size();
	Write(outFile, siz);
	rfor(i, 0, siz) {
		strcpy_s(data, Actors[i].Name.c_str());
		Write(outFile, data);
		//outFile.write((char*)&data, sizeof(data));
		strcpy_s(data, Actors[i].File.c_str());
		Write(outFile, data);
		Write(outFile, Actors[i].Status);
		Write(outFile, Actors[i].Level);
		Write(outFile, Actors[i].Hp);
		Write(outFile, Actors[i].Atk);
		Write(outFile, Actors[i].Def);
		Write(outFile, Actors[i].Mdef);
		Write(outFile, Actors[i].BreathLimit);
		Write(outFile, Actors[i].Breath);
		Write(outFile, Actors[i].Exp);
		Write(outFile, Actors[i].Gold);
		Write(outFile, Actors[i].Item);
		Write(outFile, Actors[i].MapID);
		Write(outFile, Actors[i].X);
		Write(outFile, Actors[i].Y);
		/*outFile.write((char*)&data, sizeof(data));
		outFile.write((char*)&Actors[i].Level, sizeof(Actors[i].Level));
		outFile.write((char*)&Actors[i].Hp, sizeof(Actors[i].Hp));
		outFile.write((char*)&Actors[i].Atk, sizeof(Actors[i].Atk));
		outFile.write((char*)&Actors[i].Def, sizeof(Actors[i].Def));
		outFile.write((char*)&Actors[i].Mdef, sizeof(Actors[i].Mdef));
		outFile.write((char*)&Actors[i].BreathLimit, sizeof(Actors[i].BreathLimit));
		outFile.write((char*)&Actors[i].Breath, sizeof(Actors[i].Breath));
		outFile.write((char*)&Actors[i].Exp, sizeof(Actors[i].Exp));
		outFile.write((char*)&Actors[i].Gold, sizeof(Actors[i].Gold));
		outFile.write((char*)&Actors[i].MapID, sizeof(Actors[i].MapID));
		outFile.write((char*)&Actors[i].X, sizeof(Actors[i].X));
		outFile.write((char*)&Actors[i].Y, sizeof(Actors[i].Y));*/
	}
	siz = System.Maps.size();
	Write(outFile, siz);
	rfor(i, 0, siz) {
		strcpy_s(data, System.Maps[i].MapName.c_str());
		Write(outFile, data);
		strcpy_s(data, System.Maps[i].FloorName.c_str());
		Write(outFile, data);
		int siz2 = System.Maps[i].MapEvents.size();
		Write(outFile, siz2);
		rfor(j, 0, siz2) {
			strcpy_s(data, System.Maps[i].MapEvents[j].Name.c_str());
			Write(outFile, data);
			strcpy_s(data, System.Maps[i].MapEvents[j].File[0].c_str());
			Write(outFile, data);
			strcpy_s(data, System.Maps[i].MapEvents[j].File[1].c_str());
			Write(outFile, data);
			Write(outFile, System.Maps[i].MapEvents[j].X);
			Write(outFile, System.Maps[i].MapEvents[j].Y);
			Write(outFile, System.Maps[i].MapEvents[j].TriggerCondition);
			Write(outFile, System.Maps[i].MapEvents[j].Exist);
			Write(outFile, System.Maps[i].MapEvents[j].Through);
		}
	}
	Write(outFile, System.GameSwitches);
	Write(outFile, System.GameVariables);
	Write(outFile, System.ShopPrice);
	Write(outFile, System.ShopEXP);
	Write(outFile, System.ItemRecord);
	Write(outFile, System.GemRecord);
	Write(outFile, System.BottleRecord);
	outFile.close();
	fstream file;
	file.open("save\\recent.dat", ios::ate | ios::out);
	file << fileid << endl;
	file.close();
	System.ScreenShot = true;
	System.ShotFile = "save\\save" + to_string(fileid) + ".png";
}

void GameEnd::Main() {
	System.GameBGM = "";
	mciSendString("stop BGM", NULL, 0, NULL);
	mciSendString("close BGM", NULL, 0, NULL);
	mciSendString("open res\\sound\\sound-5.mp3 alias BGM", NULL, 0, NULL);
	mciSendString("play BGM", NULL, 0, NULL);
	mark1.ChangeImage("mting-1440.png");
	mark1.X = 304;
	mark1.Y = 224;
	mark1.Opacity = 0;
	mark1.Position = 1;
	mark1.AddIn();
	mark2.ChangeImage("mting-1441.png");
	mark2.X = 304;
	mark2.Y = 224;
	mark2.Opacity = 0;
	mark2.Position = 1;
	mark2.AddIn();
	rfor(i, 0, 10) {
		shot[i].ChangeImage("mting-" + to_string(1430 + i)+".png");
		shot[i].X = 304 + ((i & 1) ? -160 : 160);
		shot[i].Y = 128 + 24 * i;
		shot[i].Position = 1;
		shot[i].Opacity = 0;
		shot[i].AddIn();
	}
	rfor(i, 0, 200) {
		weather[i].ChangeImage("mting-1276.png");
		weather[i].X = rand() % 608;
		weather[i].Y = rand() % 448 - 448;
		weather[i].Visible = false;
		weather[i].AddIn();
	}
	script1.ChangeImage("mting-1428.png");
	script1.Y = 448;
	script1.Opacity = 0;
	script1.AddIn();
	script2.ChangeImage("mting-1429.png");
	script2.Y = 448;
	script2.Opacity = 0;
	script2.AddIn();
	System.NeedRefresh = true;
	time = 0;
	index = 0;
	System.DoTransition();
	while (System.Scene == this) {
		if (GameActive == GetForegroundWindow()) {
			Graphics.Update();
			Update();
		}
	}
	System.ReadyTransition();
	script1.Dispose();
	script2.Dispose();
	mark1.Dispose();
	mark2.Dispose();
	rfor(i, 0, 200) {
		weather[i].Dispose();
	}
	rfor(i, 0, 10) {
		shot[i].Dispose();
	}
}

void GameEnd::Update() {
	if (pass1) {
		++time;
		if (time < 10) {
			mark1.Opacity = min(255, mark1.Opacity + 26);
		}
		if (time >= 50) {
			mark1.Opacity = max(0, mark1.Opacity - 5);
		}
		if (mark1.Opacity == 0 && time >= 50) {
			time = 0;
			pass1 = false;
			pass2 = true;
			return;
		}
	}
	else if (pass2) {
		++time;
		if (time < 10) {
			mark2.Opacity = min(255, mark2.Opacity + 26);
		}
		if (time >= 50) {
			mark2.Opacity = max(0, mark2.Opacity - 5);
		}
		if (mark2.Opacity == 0 && time >= 50) {
			time = 0;
			pass2 = false;
			pass3 = true;
			rfor(i, 0, 200) {
				weather[i].Visible = true;
			}
			return;
		}
	}
	else if (pass3) {
		rfor(i, 0, 200) {
			weather[i].X -= 2;
			weather[i].Y += 8;
			weather[i].Opacity = max(0, weather[i].Opacity - 4);
			if (weather[i].Y > 448 || weather[i].X < 0 || weather[i].Opacity == 0) {
				weather[i].X = rand() % 608;
				weather[i].Y = rand() % 448 - 448;
				weather[i].Opacity = 255;
			}
		}
		if (script2.Y > 0) {
			script2.Opacity = min(255, script2.Opacity + 5);
		}
		if (script2.Y <= 0) {
			++time;
			if (time >= 10 + index * 70 && time < 20 + index * 70) {
				shot[index].Opacity = min(255, shot[index].Opacity + 26);
			}
			if (time >= 50 + index * 70 && time < 70 + index * 70) {
				shot[index].Opacity = max(0, shot[index].Opacity - 13);
			}
			if (time == 70 + index * 70) {
				++index;
			}
		}
		--script2.Y;
		if (script2.Y <= -938) {
			time = 0;
			pass3 = false;
			pass4 = true;
			return;
		}
	}
	else if (pass4) {
		rfor(i, 0, 200) {
			weather[i].X -= 2;
			weather[i].Y += 8;
			weather[i].Opacity = max(0, weather[i].Opacity - 4);
			if (weather[i].Y > 448 || weather[i].X < 0 || weather[i].Opacity == 0) {
				weather[i].X = rand() % 608;
				weather[i].Y = rand() % 448 - 448;
				weather[i].Opacity = 255;
			}
		}
		++time;
		if (time >= 150) {
			time = 0;
			pass4 = false;
			pass5 = true;
			return;
		}
	}
	else if (pass5) {
		rfor(i, 0, 200) {
			weather[i].X -= 2;
			weather[i].Y += 8;
			weather[i].Opacity = max(0, weather[i].Opacity - 4);
			if (weather[i].Y > 448 || weather[i].X < 0 || weather[i].Opacity == 0) {
				weather[i].X = rand() % 608;
				weather[i].Y = rand() % 448 - 448;
				weather[i].Opacity = 255;
			}
		}
		script2.Opacity = max(0, script2.Opacity - 5);
		if (script2.Opacity == 0) {
			System.Scene = new GameTitle;
			return;
		}
	}
	else {
		if (script1.Y > 0) {
			script1.Opacity = min(255, script1.Opacity + 5);
		}
		--script1.Y;
		if (script1.Y <= -359) {
			script1.Opacity = max(0, script1.Opacity - 5);
			--script1.Y;
		}
		if (script1.Y <= -512) {
			pass1 = true;
			return;
		}
	}
}
