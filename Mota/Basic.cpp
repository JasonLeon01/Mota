#include "Basic.h"
#include "bass.h"
#pragma comment(lib, "bass.lib")

DataSystem System;
GameGraphics Graphics;
GameKeyBoard KeyBoard;
vector <GameActors> Actors;
GamePlayer Player;
vector <GameEnemies> Enemies;
vector <GameItem> Item;
vector <GameAnimation> Animation;

void WindowRect(int backx, int backy, int cornerx[], int cornery[], int sidex[], int sidey[], int backlen, int cornerlen, int sidelen, int opacity, int drawx, int drawy, int drawwidth, int drawheight, bool select) {
	if (opacity == 0) {
		return;
	}
	int width = drawwidth - 2 * cornerlen * select + select, height = drawheight - 2 * cornerlen * select + 2 * select, x = drawx + cornerlen * select, y = drawy + cornerlen * select;
	backx = backx * (width - 2 * cornerlen * select) / backlen;
	backy = backy * (height - 2 * cornerlen * select) / backlen;
	IMAGE* rect = new IMAGE, *side = new IMAGE, *back = new IMAGE;
	loadimage(rect, ("res\\picture\\" + System.WindowskinName).c_str(), 192 * (width - 2 * cornerlen * select) / backlen, 128 * (height - 2 * cornerlen * select) / backlen);
	loadimage(side, ("res\\picture\\" + System.WindowskinName).c_str());
	loadimage(back, "res\\picture\\mting.png", width, height);
	OpaqueImage(nullptr, x, y, width, height, backx, backy, rect, opacity);
	rfor(i, 0, drawwidth - 2 * cornerlen) {
		OpaqueImage(nullptr, drawx + i + cornerlen, drawy, 1, cornerlen, sidex[0] + i % sidelen, sidey[0], side, opacity);
		OpaqueImage(nullptr, drawx + i + cornerlen, drawy + drawheight - cornerlen, 1, cornerlen, sidex[1] + i % sidelen, sidey[1], side, opacity);
	}
	rfor(i, 0, drawheight - 2 * cornerlen) {
		OpaqueImage(nullptr, drawx, drawy + i + cornerlen, cornerlen, 1, sidex[2], sidey[2] + i % sidelen, side, opacity);
		OpaqueImage(nullptr, drawx + drawwidth - cornerlen, drawy + i + cornerlen, cornerlen, 1, sidex[3], sidey[3] + i % sidelen, side, opacity);
	}
	OpaqueImage(nullptr, drawx, drawy, cornerlen, cornerlen, cornerx[0], cornery[0], side, opacity);
	OpaqueImage(nullptr, drawx + drawwidth - cornerlen, drawy, cornerlen, cornerlen, cornerx[1], cornery[1], side, opacity);
	OpaqueImage(nullptr, drawx, drawy + drawheight - cornerlen, cornerlen, cornerlen, cornerx[2], cornery[2], side, opacity);
	OpaqueImage(nullptr, drawx + drawwidth - cornerlen, drawy + drawheight - cornerlen, cornerlen, cornerlen, cornerx[3], cornery[3], side, opacity);
	unless(select) {
		OpaqueImage(nullptr, x, y, back, 128);
	}
	delete rect;
	delete side;
	delete back;
}

void DrawTexts(int x, int y, int width, int height, string content, int pos, LONG size, bool bond) {
	int h = Font.lfHeight;
	Font.lfHeight = size;
	if (bond) {
		Font.lfWeight = 600;
	}
	settextstyle(&Font);
	RECT r = { x, y, x + width, y + height };
	switch (pos) {
	case 0: drawtext(content.c_str(), &r, DT_LEFT | DT_WORD_ELLIPSIS); break;
	case 1: drawtext(content.c_str(), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS); break;
	case 2: drawtext(content.c_str(), &r, DT_RIGHT | DT_WORD_ELLIPSIS); break;
	case 3: drawtext(content.c_str(), &r, DT_LEFT | DT_WORDBREAK); break;
	}
	Font.lfHeight = h;
	Font.lfWeight = 0;
	settextstyle(&Font);
}

void DrawTextsBond(int x, int y, int width, int height, string content, int pos, LONG size, bool bond) {
	COLORREF color = gettextcolor();
	settextcolor(BLACK);
	DrawTexts(x + 1, y + 1, width, height, content, pos, size, bond);
	settextcolor(color);
	DrawTexts(x, y, width, height, content, pos, size, bond);
}

void PlaySE(string file) {
	char cmd[512];
	sprintf_s(cmd, "res\\sound\\%s", file.c_str());
	HSTREAM TestSound = 0;
	::BASS_Init(-1, 44100, 0, 0, 0);
	TestSound = ::BASS_StreamCreateFile(FALSE, cmd, 0, 0, NULL);
	::BASS_ChannelPlay(TestSound, true);
}

void PlayBGM(string file) {
	file = "res\\sound\\" + file;
	if (!ExistFile(file)) {
		return;
	}
	string cmd = "open " + file + " alias BGM";
	mciSendString(cmd.c_str(), NULL, 0, NULL);
	mciSendString("stop BGM", NULL, 0, NULL);
	mciSendString("play BGM repeat", NULL, 0, NULL);
}

GameEvent::GameEvent() {
	Name = "UNDEFINED";
	File[0] = "UNDEFINED";
	File[1] = "UNDEFINED";
	X = 0;
	Y = 0;
	TriggerCondition[0] = 0;
	TriggerCondition[1] = 0;
	TriggerCondition[2] = 0;
	Exist = true;
	Through = false;
}

GameEvent::GameEvent(int x, int y) {
	GameEvent();
	X = x;
	Y = y;
}

const bool GameEvent::operator == (const GameEvent& ev) {
	return (X == ev.X && Y == ev.Y);
}

void GameEvent::Order() {
	System.FunctioningEventID = System.Maps[Actors[System.GameVariables[1]].MapID].CheckEvent(X, Y);
	if (TriggerCondition[0] != 0) {
		if (TriggerCondition[0] == 3 && System.GameSwitches[TriggerCondition[1]] != TriggerCondition[2]) {
			return;
		}
		if (TriggerCondition[0] == 4 && System.GameVariables[TriggerCondition[1]] != TriggerCondition[2]) {
			return;
		}
	}
	vector <string> name = Split(Name, "|");
	int kind, val;
	if (name[0] == "TRANS") {
		kind << name[1];
		PlaySE("mting-78.wav");
		GameSprite stair("mting.png");
		stair.X = System.MapX;
		stair.Y = System.MapY;
		stair.Opacity = 0;
		rfor(i, 0, 15) {
			stair.Opacity += 17;
			Graphics.Update();
		}
		switch (kind) {
		case 1: System.GameSwitches[3] = true; Actors[System.GameVariables[1]].MapID = 18; break;
		case 2: System.GameSwitches[3] = false; Actors[System.GameVariables[1]].MapID = 17; break;
		case 3: System.GameSwitches[3] = true; Actors[System.GameVariables[1]].MapID = 25; break;
		case 4: System.GameSwitches[3] = false; Actors[System.GameVariables[1]].MapID = 24; break;
		case 5: System.GameVariables[3] = 3; System.GameVariables[2] = 1; if (System.FloorRecord[3].empty()) System.FloorRecord[3].push_back(1); Actors[0].MapID = 29; break;
		case 6: System.GameVariables[3] = 4; System.GameVariables[2] = 1; if (System.FloorRecord[4].empty()) System.FloorRecord[4].push_back(1); Actors[1].MapID = 30; break;
		case 7: System.GameVariables[3] = 1; System.GameVariables[2] = 25; Actors[0].MapID = 27; break;
		case 8: System.GameVariables[3] = 2; System.GameVariables[2] = 25; Actors[1].MapID = 28; break;
		case 9: System.GameVariables[3] = 5; System.GameVariables[2] = 1; if (System.FloorRecord[5].empty()) System.FloorRecord[5].push_back(1); Actors[0].MapID = 39; break;
		case 10: System.GameVariables[3] = 6; System.GameVariables[2] = 1; if (System.FloorRecord[6].empty()) System.FloorRecord[6].push_back(1); Actors[1].MapID = 40; break;
		case 11: System.GameVariables[3] = 3; System.GameVariables[2] = 5; Actors[0].MapID = 37; break;
		case 12: System.GameVariables[3] = 4; System.GameVariables[2] = 5; Actors[1].MapID = 38; break;
		case 13: System.GameVariables[3] = 3; System.GameVariables[2] = 6; if (!VectorFind(System.FloorRecord[3], 6))System.FloorRecord[3].push_back(6); Actors[0].MapID = 49; break;
		case 14: System.GameSwitches[3] = true; Actors[System.GameVariables[1]].MapID = 59; break;
		case 15: System.GameVariables[3] = 4; System.GameVariables[2] = 6; if (!VectorFind(System.FloorRecord[4], 6))System.FloorRecord[4].push_back(6); Actors[1].MapID = 50; break;
		case 16: System.GameVariables[3] = 5; System.GameVariables[2] = 5; Actors[0].MapID = 47; break;
		case 17: System.GameVariables[3] = 6; System.GameVariables[2] = 5; Actors[1].MapID = 48; break;
		case 18: System.GameSwitches[3] = false; Actors[System.GameVariables[1]].MapID = 47; break;
		case 19: Actors[System.GameVariables[1]].MapID = 60; break;
		case 20: Actors[System.GameVariables[1]].X = 6; Actors[System.GameVariables[1]].Y = 4; break;
		case 21: Actors[System.GameVariables[1]].X = 4; Actors[System.GameVariables[1]].Y = 4; break;
		case 22: Actors[System.GameVariables[1]].MapID = 61; Actors[System.GameVariables[1]].X = 5; Actors[System.GameVariables[1]].Y = 10; break;
		case 23: Actors[System.GameVariables[1]].X = 4; Actors[System.GameVariables[1]].Y = 6; break;
		case 24: Actors[System.GameVariables[1]].MapID = 59; break;
		case 25: Actors[System.GameVariables[1]].MapID = 59; Actors[System.GameVariables[1]].X = 9; Actors[System.GameVariables[1]].Y = 9; break;
		case 26: Actors[System.GameVariables[1]].MapID = 59; Actors[System.GameVariables[1]].X = 1; Actors[System.GameVariables[1]].Y = 0; break;
		case 27: System.GameSwitches[3] = true; Actors[System.GameVariables[1]].MapID = 78; break;
		case 28: System.GameVariables[3] = 5; System.GameVariables[2] = 6; if (!VectorFind(System.FloorRecord[5], 6)) System.FloorRecord[5].push_back(6); Actors[0].MapID = 72; break;
		case 29: System.GameVariables[3] = 6; System.GameVariables[2] = 6; if (!VectorFind(System.FloorRecord[6], 6)) System.FloorRecord[6].push_back(6); Actors[1].MapID = 73; break;
		case 30: System.GameVariables[3] = 3; System.GameVariables[2] = 15; Actors[0].MapID = 70; break;
		case 31: System.GameVariables[3] = 4; System.GameVariables[2] = 15; Actors[1].MapID = 71; break;
		case 32: System.GameSwitches[3] = false; Actors[System.GameVariables[1]].MapID = 64; break;
		case 33: System.GameSwitches[3] = true; Actors[System.GameVariables[1]].MapID = 93; break;
		case 34: System.GameSwitches[3] = true; Actors[System.GameVariables[1]].Y = 10; Actors[System.GameVariables[1]].MapID = 94; break;
		case 35: {
			System.GameVariables[3] = 7;
			System.GameVariables[2] = 16;
			Actors[System.GameVariables[1]].MapID = 95;
			System.FloorRecord[7] = { 16 };
			if (!System.GameSwitches[21]) {
				System.GameSwitches[21] = true;
				swap(System.GameVariables[3], System.GameVariables[26]);
				swap(System.GameVariables[2], System.GameVariables[27]);
				swap(System.GameVariables[5], System.GameVariables[29]);
				System.GameVariables[1] = !System.GameVariables[1];
				System.NeedRefresh = true;
			}
			break;
		}
		case 36: {
			System.GameVariables[3] = 7;
			System.GameVariables[2] = 16;
			Actors[System.GameVariables[1]].MapID = 95;
			System.FloorRecord[7] = { 16 };
			if (!System.GameSwitches[21]) {
				System.GameSwitches[21] = true;
				swap(System.GameVariables[3], System.GameVariables[26]);
				swap(System.GameVariables[2], System.GameVariables[27]);
				swap(System.GameVariables[5], System.GameVariables[29]);
				System.GameVariables[1] = !System.GameVariables[1];
				System.NeedRefresh = true;
			}
			break;
		}
		case 37: System.GameSwitches[3] = false; Actors[System.GameVariables[1]].MapID = 75; break;
		case 38: System.GameSwitches[3] = false; Actors[System.GameVariables[1]].Y = 0; Actors[System.GameVariables[1]].MapID = 84; break;
		case 39: System.GameSwitches[3] = true; Actors[System.GameVariables[1]].MapID = 100; break;
		default: break;
		}
		rfor(i, 0, 5) {
			Graphics.Update();
		}
		System.NeedRefresh = true;
		Player.Direction = 0;
		rfor(i, 0, 15) {
			stair.Opacity -= 17;
			Graphics.Update();
		}
		stair.Dispose();
		return;
	}
	if (name[0] == "NPC") {
		kind << name[1];
		switch (kind) {
		case 0: System.MessageName = { "国王" }; System.MessageContent = { "是父王无能，一直以来让你受苦了。\n你一定要逃出去！" }; System.MessageHead = { 72 }; break;
		case 1: System.MessageName = { "公主", "公主", "公主", "公主" }; System.MessageContent = { "自从勇者先生拼上性命阻止了魔界之王古顿之后，魔物应当是已经被彻底清除了才对", "如今魔物复辟，其中一定有什么秘密", "勇者先生和古顿明明就在我面前死去，但是至今却并没有找到尸体", "父王啊，请原谅我的任性\n我一定要将真相调查清楚！" }; System.MessageHead = { -1, -1, -1, -1 }; Exist = false; break;
		case 2: System.MessageName = { "心镜老人", "公主", "心镜老人", "公主", "心镜老人", "公主", "心镜老人", "公主" }; System.MessageContent = { "你莫非是…公主吗？", "老伯，您认识我？", "你最初被关在塔里时，我有缘将「心镜」赠与了那位勇者", "原来是这样\n多谢老伯当时相助", "孩子，如今皇宫尚未沦陷，你又何苦重回这伤心地", "我不忍弃我的国家和子民于水火\n我希望去做好我能做到的事", "明白了，我们这帮老骨头会尽力帮助你，这是另一面「心镜」，要妥善保管", "谢谢你" }; System.MessageHead = { 107, -1, 107, -1, 107, -1, 107, -1 }; System.TransformingEventName = "ITEM|3|1"; System.DirectlyFunction = true; break;
		case 3: System.MessageName = { "商人", "公主" }; System.MessageContent = { "你知道吗\n按下L键可以得知按键指令", "不用你说……" }; System.MessageHead = { 87, -1 }; break;
		case 4: System.MessageName = { "神秘老人", "公主", "神秘老人", "公主" }; System.MessageContent = { "这不是公主殿下吗？\n您怎么在这里？塔内太危险了", "勇士先生已经不在了…\n我必须要用自己的力量来拯救我的国家", "唉，他的死确实太可惜了\n这是我打造的飞羽，和勇士曾经拥有的黄金飞羽相似，希望对你有帮助", "谢谢你！" }; System.MessageHead = { 88, -1, 88, -1 }; System.TransformingEventName = "ITEM|4|1"; System.DirectlyFunction = true; break;
		case 5: System.MessageName = { "强壮老人", "强壮老人" }; System.MessageContent = { "公主殿下\n你佩戴的头饰可以储存魔力", "在你的攻击大于怪物防御时，你的魔力可以加持武器，无视防御造成伤害\n所以每一个绿宝石都很珍贵" }; System.MessageHead = { 89, 89 }; break;
		case 6: System.MessageName = { "盗贼", "公主", "盗贼", "盗贼" }; System.MessageContent = { "咦\n这不是上次的公主吗", "你好，盗贼先生", "我就不多嘴问你此行目的了\n这一回冒险我仍然准备了大量的钥匙", "不足的话随时来找我吧" }; System.MessageHead = { 103, -1, 103, 103 }; System.TransformingEventName = "KEYSHOP"; System.DirectlyFunction = false; break;
		case 7: System.MessageName = { "老人", "老人", "老人" }; System.MessageContent = { "你知道什么是攻击魔术和防御魔术吗", "它们都是一种特殊的秘术，在战斗中按Z和X可以使用。它能够消耗气息并搭配你的魔力，打出特殊效果", "但是这种魔术难以学习，只有达到一定等级才能成功使用" }; System.MessageHead = { 83, 83, 83 }; break;
		case 8: System.MessageName = { "疲态老人", "疲态老人" }; System.MessageContent = { "想必你已经受够了这些恶心的弓兵以及疯狗一般的怪物", "曾经支援过你们随意门的前辈就在楼上，务必要找到他！" }; System.MessageHead = { 84, 84, 84 }; break;
		case 9: System.MessageName = { "老人", "公主", "老人", "公主", "老人" }; System.MessageContent = { "孩子，你终于到达这里了，一路上没少吃苦吧", "确实艰难…\n勇者先生当初一定很辛苦吧", "长话短说，这一次我也将为你提供随意门，先赠予你3个好了，按T键使用，没有忘记吧？", "这是自然", "看在是旧相识的份上，之后我会以$30的单价卖给你，不够的话尽管来找我吧" }; System.MessageHead = { 45,-1,45,-1,45 }; System.TransformingEventName = "ITEM|5|3"; System.DirectlyFunction = true; break;
		case 10: System.MessageName = { "老人" }; System.MessageContent = { "持有此物，你可以抵挡一半来自怪物的地图伤害…" }; System.MessageHead = { 86 }; System.TransformingEventName = "ITEM|12|1"; System.DirectlyFunction = true; break;
		case 11: System.MessageName = { "老人", "老人" }; System.MessageContent = { "就要抵达塔顶了，一定要当心，做好万全准备再上去", "对了\n据说前面的楼层隐藏着一种宝物，可以阻挡怪物从地图上对你造成的伤害" }; System.MessageHead = { 95, 95 }; break;
		case 12: System.MessageName = { "公主", "幽冥法师", "公主" }; System.MessageContent = { "是勇者先生！", "杀—死—入—侵—者—", "魔头，滚开！" }; System.MessageHead = { -1, 107, -1 }; Exist = false; break;
		case 13: System.MessageName = { "公主", "魔物首领", "公主", "魔物首领" }; System.MessageContent = { "你…\n是魔物首领！", "哎呀，不得不说，你们二位的精神真是令人感动", "…你想怎样", "放轻松，我暂时还不会杀掉你们\n前方便是魔界的入口了，如果有勇气的话便跟进来吧" }; System.MessageHead = { -1, 108, -1, 108 }; System.TransformingEventName = "NPC|14"; System.DirectlyFunction = true; break;
		case 14: {
			PlaySE("mting-39.wav");
			GameSprite white("mting-1248.png");
			white.X = System.MapX;
			white.Y = System.MapY;
			white.Opacity = 0;
			rfor(i, 0, 15) {
				white.Opacity += 17;
				Graphics.Update();
			}
			System.Maps[27].MapEvents[106].File[0] = "mting-1246.png";
			System.Maps[27].MapEvents[106].File[1] = "mting-1246.png";
			System.Maps[27].MapEvents[106].X = 6;
			System.Maps[27].MapEvents[106].Y = 2;
			Actors[0].X = 4;
			Actors[0].Y = 2;
			Player.Direction = 0;
			Actors[1].MapID = 28;
			Actors[1].X = 6;
			Actors[1].Y = 2;
			Actors[1].File = "012-Braver02.png";
			Actors[1].Level = 1;
			Actors[1].Status = 0;
			Actors[1].Hp = 5000;
			Actors[1].Atk = 100;
			Actors[1].Def = 100;
			Actors[1].Mdef = 0;
			Actors[1].Exp = 0;
			Actors[1].Gold = 0;
			Actors[1].Breath = 0;
			Actors[1].BreathLimit = 120;
			System.GameVariables[26] = 2;
			System.GameVariables[27] = 25;
			memset(Actors[1].Item, 0, sizeof(Actors[1].Item));
			Actors[1].Item[0] = 4;
			Actors[1].Item[1] = 1;
			Actors[1].Item[3] = 1;
			Actors[1].Item[4] = 1;
			System.FloorRecord[2].push_back(25);
			System.ShopPrice[0] = 50;
			rfor(i, 0, 5) {
				Graphics.Update();
			}
			System.NeedRefresh = true;
			rfor(i, 0, 15) {
				white.Opacity -= 17;
				Graphics.Update();
			}
			white.Dispose();
			System.MessageName = { "勇者", "勇者", "公主", "勇者", "魔物首领", "魔物首领" };
			System.MessageContent = { "唔…",
									  "奇怪…\n我不是…死了么…",
									  "勇者先生！", "公主殿下…\n你怎么……",
									  "抱歉打扰二位的兴致了\n如你们所见，阴之道为亡国之女所开，阳之道为救国之子所开",
									  "那么，祝二位好运" };
			System.MessageHead = { 106, 106, -1, 106, 108, 108 };
			System.TransformingEventName = "NPC|15";
			System.DirectlyFunction = true;
			break;
		}
		case 15: {
			Exist = false;
			System.GameSwitches[15] = true;
			System.MessageName = { "公主", "老人", "盗贼", "勇者", "公主", "老人", "盗贼", "老人", "公主", "勇者", "老人", "盗贼", "公主", "" };
			System.MessageContent = { "你们怎么上来了\n发生甚么事了",
									  "魔塔似乎是又升到了高空，从第1层开始逐渐崩塌，我们只好一路走了上来",
									  "等等…\n你是勇者？你不是死了吗",
									  "一言难尽…\n尚不知道这里是否仍然安全",
									  "嘴上说着“自愿”跟上去，却立刻就阻断了我们的后路",
									  "依老夫所见，这里暂时是安全的\n不过外界的魔塔恐怕只剩下这一层了",
									  "啊啊…\n看样子一时半会是离不开了，真倒霉…",
									  "殿下和勇者大人打算怎么办",
									  "我觉得目前只能前进了",
									  "我也这么认为",
									  "好吧，我在这里等着你们，如果你们需要随意门可以随时过来找我",
									  "我也是，我这里还有很多钥匙，你们可千万别死了啊",
									  "放心吧，必定平安归来",
									  "按下N键可以从公主和勇者之间切换操作对象" };
			System.MessageHead = { -1, 109, 110, 106, -1, 109, 110, 109, -1, 106, 109, 110, -1, -1 };
			System.TransformingEventName = "NPC|16";
			System.DirectlyFunction = true;
			break;
		}
		case 16: System.Maps[27].MapEvents[106].Exist = false; break;
		case 17: System.MessageName = { "阴森老人" }; System.MessageContent = { "好好注意周边的墙壁哦\n嘻嘻嘻嘻…" }; System.MessageHead = { 116 }; break;
		case 18: System.MessageName = { "失智商人", "失智商人" }; System.MessageContent = { "巧妙运用手中道具，不必与强敌作战就可前进", "对了，你要金坷垃吗" }; System.MessageHead = { 104, 104 }; break;
		case 19: System.MessageName = { "妖精" }; System.MessageContent = { "嘻嘻嘻，欢迎回来\n收好道具袋哦，可别拿到就直接喝掉了" }; System.MessageHead = { 74 }; System.TransformingEventName = "ITEM|15|1"; System.DirectlyFunction = true; break;
		case 20: {
			System.MessageName = { "魔族商人", "公主", "魔族商人", "公主", "魔族商人" };
			if (Actors[System.GameVariables[1]].Item[12] > 0) {
				System.MessageContent = { "哎呀哎呀\n看上去你被这些地图怪物折腾得很惨呢", "确实如此…\n实在是防不胜防", "我有一块魔法源石，可以极大地强化你的反射网。如果你出500个金币，我就把它卖给你，怎样？", "我考虑考虑吧", "随时欢迎" };
			}
			else {
				System.MessageContent = { "哎呀哎呀\n看上去你被这些地图怪物折腾得很惨呢", "确实如此…\n实在是防不胜防", "我有一块魔法源石，可以制作降低地图伤害的反射网。如果你出500个金币，我就把它卖给你，怎样？", "我考虑考虑吧", "随时欢迎" };
			}
			System.MessageHead = { 89, -1, 89, -1, 89 };
			System.TransformingEventName = "NPC|21";
			break;
		}
		case 21: {
			System.MessageName = { "魔族商人" };
			if (Actors[System.GameVariables[1]].Gold >= 500) {
				Actors[System.GameVariables[1]].Gold -= 500;
				System.MessageContent = { "成交！不愧是公主殿下，就是有魄力" };
				System.TransformingEventName = "ITEM|18|1";
				System.DirectlyFunction = true;
			}
			else {
				System.MessageContent = { "哎呀哎呀，公主殿下，莫非你在皇宫中待久了，多少钱都数不清楚了吗" };
			}
			System.MessageHead = { 89 };
			break;
		}
		case 22: System.MessageName = { "公主", "公主" }; System.MessageContent = { "塔内居然还有如此寒冷之地", "寒气的来源……\n莫非是那只史莱姆？" }; System.MessageHead = { -1, -1 }; Exist = false; break;
		case 23: {
			PlaySE("mting-39.wav");
			GameSprite white("mting-1248.png");
			white.X = System.MapX;
			white.Y = System.MapY;
			white.Opacity = 0;
			rfor(i, 0, 15) {
				white.Opacity += 17;
				Graphics.Update();
			}
			System.Maps[Actors[System.GameVariables[1]].MapID].FloorName = "001-Floor01.png";
			System.GameSwitches[18] = true;
			rfor(i, 2, 92) {
				System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[i].Name = "WALL";
				System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[i].File[0] = "mting-240.png";
				System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[i].File[1] = "mting-240.png";
			}
			rfor(i, 0, 5) {
				Graphics.Update();
			}
			System.NeedRefresh = true;
			rfor(i, 0, 15) {
				white.Opacity -= 17;
				Graphics.Update();
			}
			white.Dispose();
			System.TransformingEventName = "ITEM|17|1";
			System.GameSwitches[18] = true;
			System.DirectlyFunction = true;
			break;
		}
		case 24: System.MessageName = { "商人" }; System.MessageContent = { "据说魔塔的12层藏着妖精的宝库，不过我找了很久都没有发现" }; System.MessageHead = { 93 }; break;
		case 25: System.MessageName = { "妖精" }; System.MessageContent = { "喂！你干什么！\n这可是人家搜集了好久的东西！" }; System.MessageHead = { 110 }; break;
		case 26: System.MessageName = { "老人" }; System.MessageContent = { "前方大概是魔塔的尽头了…\n万事小心" }; System.MessageHead = { 93 }; break;
		case 27: System.MessageName = { "老人" }; System.MessageContent = { "前方大概是魔塔的尽头了…\n万事小心" }; System.MessageHead = { 88 }; break;
		case 28: System.MessageName = { "魔神·些多", Actors[System.GameVariables[1]].Name }; System.MessageContent = { "啊啊啊啊啊！\n每次都是你们坏了我们的好事！", "你们果然都还没死\n不过不会有机会再复活了" }; System.MessageHead = { 53, -1 }; Exist = false; break;
		case 29: {
			System.MessageName = { "魔物首领", Actors[System.GameVariables[1]].Name, "魔物首领", Actors[System.GameVariables[1]].Name, "魔王·格勒第", "魔界之王·古顿", "魔物首领", Actors[System.GameVariables[1]].Name, "魔物首领", Actors[System.GameVariables[1]].Name, "魔物首领" };
			System.MessageContent = { "想不到你真的会下手",
										"这不会是无意义的，我会在这里打倒你",
										"怎么，看到老朋友，没有什么话想说吗",
										"既然格勒第能复活第一次，那复活第二次也不足为奇，更别说第一次复活的古顿了",
										"……",
										"……",
										"哦？你就不想知道他们为什么能多次复活吗？",
										"因为他们和你都是一本同源，也就是你的分身，对吧",
										"厉害啊，没想到你居然能看出来这一点",
										"闲话到此为止吧",
										"嗯，我也是这么想的\n本来还想用他们两个吓吓你，看来没必要了" };
			System.MessageHead = { 31, -1, 31, -1, 29, 30, 31, -1, 31, -1, 31 };
			System.TransformingEventName = "NPC|30";
			System.DirectlyFunction = true;
			break;
		}
		case 30: {
			PlaySE("mting-39.wav");
			GameSprite white("mting-1248.png");
			white.X = System.MapX;
			white.Y = System.MapY;
			white.Opacity = 0;
			rfor(i, 0, 15) {
				white.Opacity += 17;
				Graphics.Update();
			}
			System.GameSwitches[25] = true;
			System.Maps[100].MapEvents[31].Name = "MONSTER|92";
			System.Maps[100].MapEvents[31].File[0] = "mting-182.png";
			System.Maps[100].MapEvents[31].File[1] = "mting-183.png";
			rfor(i, 0, 5) {
				Graphics.Update();
			}
			System.NeedRefresh = true;
			rfor(i, 0, 15) {
				white.Opacity -= 17;
				Graphics.Update();
			}
			white.Dispose();
			System.MessageName = { "妖精", Actors[System.GameVariables[1]].Name, "妖精", Actors[System.GameVariables[1]].Name, "妖精", "妖精", "妖精", "妖精", Actors[System.GameVariables[1]].Name, "妖精", "妖精", Actors[System.GameVariables[1]].Name, "妖精" };
			System.MessageContent = { "你好像并不惊讶",
										"同属魔物的妖精哪里会有帮助人类的道理，从第一次开始我们就在怀疑你了",
										"没想到你们居然会怀疑帮助过你们的人\n啊~这让人家很伤心哎",
										"那么可以说说吗，你们入侵人类世界的目的",
										"哦，可以啊",
										"一句话概括就是资源短缺，魔物的食粮是众生的生命力",
										"曾经魔界靠互相屠杀来生存，但是现在的数量显然不能自相残杀了，那只能来杀你们了",
										"毕竟是为了生存嘛，不寒碜\n绑架公主不过是一个引走注意的幌子罢了",
										"……不可饶恕",
										"喂喂，你不会还想跟我打吧，我可是魔物首领哎，魔—物—首—领",
										"我的能力就是轮回永生，也就是说，我是不死的",
										"是不是不死，那可不好说\n如果你复活的话，我只要再杀死你就可以了",
										"哎呀呀，真是顽固的孩子" };
			System.MessageHead = { 31, -1, 31, -1, 31, 31, 31, 31, -1, 31, 31, -1, 31 };
			Exist = false;
			break;
		}
		case 31: {
			System.MessageName = { "妖精" };
			System.MessageContent = { "这不可能……" };
			System.MessageHead = { 31 };
			System.TransformingEventName = "NPC|32";
			System.DirectlyFunction = true;
			break;
		}
		case 32: {
			System.GameSwitches[26] = true;
			if (System.GameVariables[1] == 0) {
				System.Maps[100].MapEvents[0].File[0] = "mting-1246.png";
				System.Maps[100].MapEvents[0].File[1] = "mting-1246.png";
				System.Maps[100].MapEvents[41].File[0] = "mting-1263.png";
				System.Maps[100].MapEvents[41].File[1] = "mting-1263.png";
			}
			else {
				System.Maps[100].MapEvents[0].File[0] = "mting-241.png";
				System.Maps[100].MapEvents[0].File[1] = "mting-242.png";
				System.Maps[100].MapEvents[41].File[0] = "mting-1264.png";
				System.Maps[100].MapEvents[41].File[1] = "mting-1264.png";
			}
			System.NeedRefresh = true;
			System.MessageName = { Actors[!System.GameVariables[1]].Name, "妖精", Actors[!System.GameVariables[1]].Name, Actors[System.GameVariables[1]].Name, Actors[!System.GameVariables[1]].Name, Actors[!System.GameVariables[1]].Name, "老人", "盗贼", Actors[!System.GameVariables[1]].Name, "妖精", "妖精" };
			System.MessageContent = { "没什么不可能的", 
				"怎么会…\n你明明…", 
				"需要沾满同类鲜血才能打开的道路？这种说法简直笑死人了，那不过是你掌握了打开开关的道路吧", 
				"如果真的有这样的东西，为什么不设置在主塔的入口呢",
				"你不会以为我们真的相信了吧，死亡自然也是做给你看的",
				"这只需要一个眼神，我们就能达成共识，你们都离开之后，我就想办法回到了主塔的顶层，跟他们说明了情况", 
				"在主塔再次升空之后，我就一直在研究如何让它回到地面，万幸最终成功了",
				"我出去打探了情况，没有首领带领的魔物就是一团散沙，已经被王国军彻底压制",
				"看样子这一次你彻底失败了呢\n而且，无路可逃",
				"多年以后魔塔一定会再次矗立！\n只要世界的阴暗面仍然存在，魔物就是不灭的！",
				"到时候，你们还可以阻挡我们吗？！你们还可以阻挡我们吗？！"};
			System.MessageHead = { 0, 31, 0, -1, 0, 0, 43, 44, 0, 31, 31 };
			System.TransformingEventName = "NPC|33";
			System.DirectlyFunction = true;
			break;
		}
		case 33: {
			System.Victory = true;
			break;
		}
		default: System.MessageName.clear(); System.MessageContent.clear();	System.MessageHead.clear(); break;
		}
	}
	if (name[0] == "SDOOR") {
		if (Actors[System.GameVariables[1]].Item[0] > 0) {
			PlaySE(System.GateSE);
			--Actors[System.GameVariables[1]].Item[0];
			OpenDoor();
			if (name.size() == 2) {
				File[0] = "mting-243.png";
				File[1] = "mting-244.png";
				System.NeedRefresh = true;
				Name = "TRANS|" + name[1];
				Through = true;
			}
			else {
				Exist = false;
			}
		}
		return;
	}
	if (name[0] == "MONSTER") {
		System.BattleEnemyID << name[1];
		return;
	}
	if (name[0] == "DOOR") {
		if (stoi(name[1]) == 0) {
			PlaySE(System.GateSE);
			OpenDoor();
			Exist = false;
			return;
		}
		if (stoi(name[1]) == 1) {
			if (Actors[System.GameVariables[1]].Item[0] > 0) {
				PlaySE(System.GateSE);
				--Actors[System.GameVariables[1]].Item[0];
				OpenDoor();
				Exist = false;
			}
			return;
		}
		if (stoi(name[1]) == 2) {
			if (Actors[System.GameVariables[1]].Item[1] > 0) {
				PlaySE(System.GateSE);
				--Actors[System.GameVariables[1]].Item[1];
				OpenDoor();
				Exist = false;
			}
			return;
		}
		if (stoi(name[1]) == 3) {
			if (Actors[System.GameVariables[1]].Item[2] > 0) {
				PlaySE(System.GateSE);
				--Actors[System.GameVariables[1]].Item[2];
				OpenDoor();
				Exist = false;
			}
			return;
		}
	}
	if (name[0] == "GEM") {
		PlaySE(System.GetSE);
		kind << name[1];
		val = 1;
		if (name.size() == 3) {
			val << name[2];
		}
		string content = "获得「";
		switch (kind) {
		case 1: Actors[System.GameVariables[1]].Atk += val; content += "红宝石」，攻击力+" + to_string(val); break;
		case 2: Actors[System.GameVariables[1]].Def += val; content += "蓝宝石」，防御力+" + to_string(val); break;
		case 3: Actors[System.GameVariables[1]].Mdef += val; content += "绿宝石」，魔力+" + to_string(val); break;
		case 4: Actors[System.GameVariables[1]].Level += val; Actors[System.GameVariables[1]].Hp += 250 * val; Actors[System.GameVariables[1]].Atk += 3 * val; Actors[System.GameVariables[1]].Def += 3 * val; Actors[System.GameVariables[1]].BreathLimit += 6 * val; content += "跃进之翼」，等级+" + to_string(val); break;
		case 5: System.GameVariables[14] = 2; Actors[System.GameVariables[1]].Atk += val; Actors[System.GameVariables[1]].Mdef += 1; content += "剑」，魔力+1，攻击力+" + to_string(val); break;
		case 6: Actors[System.GameVariables[1]].Def += val; Actors[System.GameVariables[1]].Mdef += 1; content += "服饰」，魔力+1，防御力+" + to_string(val); break;
		case 7: Actors[System.GameVariables[1]].Exp += val; content += "经验药水」，经验+" + to_string(val); break;
		case 8: Actors[System.GameVariables[1]].Gold += val; content += "大金币」，金币+" + to_string(val); break;
		case 9: Actors[System.GameVariables[1]].BreathLimit -= val; Actors[System.GameVariables[1]].Breath = min(Actors[System.GameVariables[1]].Breath, Actors[System.GameVariables[1]].BreathLimit - 1); content += "气息药水」，气息上限减少" + to_string(val); break;
		case 10: Actors[System.GameVariables[1]].Item[0] += val; Actors[System.GameVariables[1]].Item[1] += val; Actors[System.GameVariables[1]].Item[2] += val; content += "钥匙盒」，各钥匙+" + to_string(val); break;
		case 11: Actors[System.GameVariables[1]].Breath = min(Actors[System.GameVariables[1]].BreathLimit - 1, Actors[System.GameVariables[1]].Breath + Actors[System.GameVariables[1]].BreathLimit / 6); content += "灵魂之火」，气息提升1格"; break;
		case 12: if (Actors[System.GameVariables[1]].Status == 1) Actors[System.GameVariables[1]].Status = 0; content += "解毒剂」，解除中毒状态"; break;
		case 13: if (Actors[System.GameVariables[1]].Status == 2) { Actors[System.GameVariables[1]].Status = 0; System.GameVariables[5] = 0; } content += "火酒」，解除衰弱状态"; break;
		}
		if (!System.GemRecord[kind][val]) {
			System.GemRecord[kind][val] = true;
			System.MessageName.push_back("");
			System.MessageContent.push_back(content);
			System.MessageHead.push_back(-1);
		}
		Exist = false;
		return;
	}
	if (name[0] == "BOTTLE") {
		PlaySE(System.GetSE);
		val << name[1];
		Actors[System.GameVariables[1]].Hp += val;
		if (!System.BottleRecord[val]) {
			System.BottleRecord[val] = true;
			System.MessageName.push_back("");
			System.MessageContent.push_back("获得「伤药」，体力+" + to_string(val));
			System.MessageHead.push_back(-1);
		}
		Exist = false;
		return;
	}
	if (name[0] == "ITEM") {
		PlaySE(System.GetSE);
		kind << name[1];
		val << name[2];
		string content = "获得「";
		content += Item[kind].Name + "」";
		if (val != 1) {
			content += "×" + to_string(val);
		}
		content += "，";
		content += Item[kind].Description;
		if (!System.ItemRecord[kind] || val != 1) {
			System.ItemRecord[kind] = true;
			System.MessageName.push_back("");
			System.MessageContent.push_back(content);
			System.MessageHead.push_back(-1);
		}
		Actors[System.GameVariables[1]].Item[kind] += val;
		if (kind == 5 && !System.GameSwitches[11]) {
			System.GameSwitches[11] = true;
			System.TransformingEventName = "SDOORSHOP";
			return;
		}
		if (Actors[System.GameVariables[1]].Item[15] == 0) {
			if (kind == 13) {
				--Actors[System.GameVariables[1]].Item[13];
				if (Actors[System.GameVariables[1]].Status == 1) {
					Actors[System.GameVariables[1]].Status = 0;
				}
				Actors[System.GameVariables[1]].Hp += 80;
			}
			if (kind == 14) {
				--Actors[System.GameVariables[1]].Item[14];
				if (Actors[System.GameVariables[1]].Status == 2) {
					Actors[System.GameVariables[1]].Status = 0;
					System.GameVariables[5] = 0;
				}
				Actors[System.GameVariables[1]].Hp += 180;
			}
		}
		Exist = false;
		if (kind == 6 || kind == 7 || kind == 8) {
			System.GameSwitches[12] = true;
		}
		if (kind == 9 || kind == 10 || kind == 11) {
			System.GameSwitches[13] = true;
		}
		return;
	}
	if (name[0] == "BARRIER") {
		int damage = Actors[System.GameVariables[1]].Item[17] > 0 ? 10 : stoi(name[1]);
		Actors[System.GameVariables[1]].Hp = max(Actors[System.GameVariables[1]].Hp - damage, 0);
		Graphics.Animations.push({ System.MapX + Actors[System.GameVariables[1]].X * 32 + 16, System.MapY + Actors[System.GameVariables[1]].Y * 32 + 16, 0, Animation[33] });
		if (Actors[System.GameVariables[1]].Hp <= 0) {
			System.EndGame = true;
			return;
		}
		if (Actors[System.GameVariables[1]].Item[17] > 0) {
			Exist = false;
		}
	}
	if (name[0] == "GOLDSHOP") {
		System.ShopType = 1;
		System.ShopID << name[1];
		return;
	}
	if (name[0] == "EXPSHOP") {
		System.ShopType = 2;
		System.ShopID << name[1];
		return;
	}
	if (name[0] == "KEYSHOP") {
		System.ShopType = 3;
		return;
	}
	if (name[0] == "SDOORSHOP") {
		System.ShopType = 4;
		return;
	}
	if (name[0] == "RECYSHOP") {
		System.ShopType = 5;
		return;
	}
	if (name[0] == "UP") {
		if (System.GameVariables[3] == 0 && System.GameVariables[2] == 24) {
			System.GameVariables[3] = 1;
		}
		PlaySE(System.StairSE);
		GameSprite stair("mting.png");
		stair.X = System.MapX;
		stair.Y = System.MapY;
		stair.Opacity = 0;
		rfor(i, 0, 15) {
			stair.Opacity += 17;
			Graphics.Update();
		}
		DataMap tem;
		tem.MapName = to_string(System.GameVariables[3]) + ":" + to_string(System.GameVariables[2] + 1);
		if (VectorFind(System.Maps, tem)) {
			++System.GameVariables[2];
			Actors[System.GameVariables[1]].MapID = find(System.Maps.begin(), System.Maps.end(), tem) - System.Maps.begin();
			Player.Direction = 0;
			if (!VectorFind(System.FloorRecord[System.GameVariables[3]], System.GameVariables[2])) {
				System.FloorRecord[System.GameVariables[3]].push_back(System.GameVariables[2]);
				sort(System.FloorRecord[System.GameVariables[3]].begin(), System.FloorRecord[System.GameVariables[3]].end());
			}
		}
		else {
			Print("No such a map!");
		}
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
	if (name[0] == "DOWN") {
		if (System.GameVariables[2] == 6 && (System.GameVariables[3] == 3 || System.GameVariables[3] == 4)) {
			System.GameVariables[3] += 2;
		}
		PlaySE(System.StairSE);
		GameSprite stair("mting.png");
		stair.X = System.MapX;
		stair.Y = System.MapY;
		stair.Opacity = 0;
		rfor(i, 0, 15) {
			stair.Opacity += 17;
			Graphics.Update();
		}
		DataMap tem;
		tem.MapName = to_string(System.GameVariables[3]) + ":" + to_string(System.GameVariables[2] - 1);
		if (VectorFind(System.Maps, tem)) {
			--System.GameVariables[2];
			Actors[System.GameVariables[1]].MapID = find(System.Maps.begin(), System.Maps.end(), tem) - System.Maps.begin();
			if (!VectorFind(System.FloorRecord[System.GameVariables[3]], System.GameVariables[2])) {
				System.FloorRecord[System.GameVariables[3]].push_back(System.GameVariables[2]);
				sort(System.FloorRecord[System.GameVariables[3]].begin(), System.FloorRecord[System.GameVariables[3]].end());
			}
		}
		else {
			Print("No such a map!");
		}
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
	return;
}

void GameEvent::OpenDoor() {
	string F1 = File[0], F2 = File[1];
	rfor(i, 1, 4) {
		File[0] = Split(F1, ".")[0] + "-" + to_string(i) + ".png";
		File[1] = Split(F2, ".")[0] + "-" + to_string(i) + ".png";
		System.NeedRefresh = true;
		Graphics.Update();
	}
}

const bool DataMap::operator == (const DataMap& mp) {
	return (MapName == mp.MapName);
}

bool DataMap::HaveAnEvent(int x, int y) {
	for (auto ev : MapEvents) {
		if (ev.X == x && ev.Y == y && ev.Exist) {
			if (ev.TriggerCondition[0] != 0) {
				if (ev.TriggerCondition[0] == 1 && System.GameSwitches[ev.TriggerCondition[1]] != ev.TriggerCondition[2]) {
					return false;
				}
				if (ev.TriggerCondition[0] == 2 && System.GameVariables[ev.TriggerCondition[1]] != ev.TriggerCondition[2]) {
					return false;
				}
			}
			return true;
		}
	}
	return false;
}

bool DataMap::HaveAnEEvent(int x, int y) {
	for (auto ev : MapEvents) {
		if (ev.X == x && ev.Y == y) {
			return true;
		}
	}
	return false;
}

int DataMap::CheckEvent(int x, int y) {
	GameEvent tem;
	tem.X = x;
	tem.Y = y;
	return (find(MapEvents.begin(), MapEvents.end(), tem) - MapEvents.begin());
}

GameEvent* DataMap::ECheckEvent(int x, int y) {
	return (&System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[System.Maps[Actors[System.GameVariables[1]].MapID].CheckEvent(x, y)]);
}

pair <int, int> DataMap::HeAt(int id) {
	return { MapEvents[id].X, MapEvents[id].Y };
}

bool DataMap::Passible(int x, int y) {
	if (x > 10 || x < 0 || y > 10 || y < 0) {
		return false;
	}
	if (HaveAnEvent(x, y)) {
		if (Split(ECheckEvent(x, y)->Name, "|")[0] == "BARRIER") {
			return true;
		}
		return (ECheckEvent(x, y)->Through);
	}
	return true;
}

bool DataMap::HaveEventsAlong(pair <int, int> ev1, pair <int, int> ev2) {
	if (ev1.first != ev2.first && ev1.second != ev2.second) {
		return true;
	}
	if (ev1.first == ev2.first && ev1.second == ev2.second) {
		return false;
	}
	if (ev1.first == ev2.first) {
		rfor(i, min(ev1.second, ev2.second), max(ev1.second, ev2.second)) {
			if (!System.Maps[Actors[System.GameVariables[1]].MapID].Passible(ev1.first, i)) {
				if (i == ev1.second || i == ev2.second) {
					continue;
				}
				return true;
			}
		}
	}
	else if (ev1.second == ev2.second) {
		rfor(i, min(ev1.first, ev2.first), max(ev1.first, ev2.first)) {
			if (!System.Maps[Actors[System.GameVariables[1]].MapID].Passible(i, ev1.second)) {
				if (i == ev1.first || i == ev2.first) {
					continue;
				}
				return true;
			}
		}
	}
	return false;
}

bool DataMap::Beside(pair <int, int> ev1, pair <int, int> ev2) {
	return ((ev1.first == ev2.first || ev1.second == ev2.second) && abs(ev1.first - ev2.first) <= 1 && abs(ev1.second - ev2.second) <= 1);
}

void DataMap::WaitCount(int times) {
	rfor(i, 0, times) {
		Graphics.Update();
	}
}

void DataSystem::DataLoad() {
	vector <string> dat = ReadData("ini\\GameDatabase.ini");
	System.FrameRate = stoi(dat[0]);
	System.WindowOpacity = stoi(dat[1]);
	System.MapX = stoi(dat[2]);
	System.MapY = stoi(dat[3]);
	System.WindowskinName = dat[4];
	System.TitleName = dat[5];
	System.FontName = dat[6];
	System.GameBGM = dat[7];
	System.CursorSE = dat[8];
	System.DecisionSE = dat[9];
	System.CancelSE = dat[10];
	System.BuzzerSE = dat[11];
	System.ShopSE = dat[12];
	System.SaveSE = dat[13];
	System.LoadSE = dat[14];
	System.GateSE = dat[15];
	System.GetSE = dat[16];
	System.StairSE = dat[17];
	System.MoveSE = dat[18];
	dat.clear();
	dat = ReadData("ini\\Actors.ini");
	for (auto it = dat.begin(); it != dat.end(); ++it) {
		GameActors ac;
		ac.Name = *(++it);
		ac.File = *(++it);
		ac.Level << *(++it);
		ac.Hp << *(++it);
		ac.Atk << *(++it);
		ac.Def << *(++it);
		ac.Mdef << *(++it);
		ac.BreathLimit << *(++it);
		ac.Breath << *(++it);
		ac.Exp << *(++it);
		ac.Gold << *(++it);
		ac.MapID << *(++it);
		ac.X << *(++it);
		ac.Y << *(++it);
		Actors.push_back(ac);
	}
	dat.clear();
	dat = ReadData("ini\\Enemies.ini");
	for (auto it = dat.begin(); it != dat.end(); ++it) {
		GameEnemies en;
		en.Name = *(++it);
		vector <string> efile = Split(*(++it), ",");
		en.File[0] = efile[0];
		en.File[1] = efile.size() == 1 ? efile[0] : efile[1];
		vector <string> ele = Split(*(++it), ",");
		for (auto e : ele) {
			en.Element.push_back(stoi(e));
		}
		en.Hp << *(++it);
		en.Atk << *(++it);
		en.Def << *(++it);
		en.Breath << *(++it);
		en.Conatk << *(++it);
		en.Exp << *(++it);
		en.Gold << *(++it);
		en.AnimationID << *(++it);
		Enemies.push_back(en);
	}
	dat.clear();
	dat = ReadData("ini\\Items.ini");
	for (auto it = dat.begin(); it != dat.end(); ++it) {
		GameItem itm;
		itm.Name = *(++it);
		itm.File = *(++it);
		itm.Description = *(++it);
		itm.Price << *(++it);
		itm.Usable << *(++it);
		itm.Cost << *(++it);
		Item.push_back(itm);
	}
	dat.clear();
	dat = ReadData("ini\\Animations.ini");
	for (auto it = dat.begin(); it != dat.end(); ++it) {
		++it;
		GameAnimation an;
		vector <string> pat = Split(*(++it), ",");
		for (auto p : pat) {
			an.Pattern.push_back(p + ".png");
		}
		an.SEFile = *(++it);
		an.SETime = stoi(*(++it));
		Animation.push_back(an);
	}
	int id = 0;
	char cmapname[128];
	loop{
		sprintf_s(cmapname, "data\\map%03d.dat", id++);
		if (!ExistFile(cmapname)) {
			break;
		}
		dat.clear();
		dat = ReadData(cmapname);
		DataMap tem;
		auto it = dat.begin();
		tem.MapName = *it;
		tem.FloorName = *(++it);
		++it;
		for (; it != dat.end(); ++it) {
			GameEvent ev;
			ev.Name = *(++it);
			ev.File[0] = *(++it);
			ev.File[1] = *(++it);
			ev.X << *(++it);
			ev.Y << *(++it);
			ev.TriggerCondition[0] << *(++it);
			ev.TriggerCondition[1] << *(++it);
			ev.TriggerCondition[2] << *(++it);
			ev.Through << *(++it);
			tem.MapEvents.push_back(ev);
		}
		System.Maps.push_back(tem);
	}
}

void DataSystem::Initialization() {
	Actors.clear();
	Enemies.clear();
	Item.clear();
	Animation.clear();
	FloorRecord.clear();
	Maps.clear();
	GameTime = 0;
	MessagePos = 2;
	BattleEnemyID = -1;
	ShopType = 0;
	ShopID = -1;
	ShopPrice[0] = 20;
	ShopPrice[1] = 50;
	ShopPrice[2] = 300;
	ShopEXP[0] = 70;
	ShopEXP[1] = 20;
	ShopEXP[2] = 190;
	ShopEXP[3] = 40;
	TransformingEventName = "";
	memset(GameVariables, 0, sizeof(GameVariables));
	memset(GameSwitches, false, sizeof(GameSwitches));
	memset(ItemRecord, false, sizeof(ItemRecord));
	memset(GemRecord, false, sizeof(GemRecord));
	memset(BottleRecord, false, sizeof(BottleRecord));
	NeedRefresh = true;
	ScreenShot = false;
	EndGame = false;
	FirstArrive = false;
	ShotFile = "";
	MessageName.clear();
	MessageContent.clear();
	MessageHead.clear();
	DataLoad();
	Player.Step = 0;
	for (auto &dat : Actors) {
		dat.Status = 0;
		memset(dat.Item, 0, sizeof(dat.Item));
	}
	Player = { 0, false, true };
	GameActive = FindWindow(NULL, "Mota");
	setbkmode(TRANSPARENT);
	Font.lfHeight = 22;
	Font.lfWeight = 500;
	Font.lfQuality = PROOF_QUALITY;
	_tcscpy_s(Font.lfFaceName, _T(System.FontName.c_str()));
	settextstyle(&Font);
}

void DataSystem::Reload() {
	Actors.clear();
	Enemies.clear();
	Item.clear();
	Animation.clear();
	FloorRecord.clear();
	Maps.clear();
	GameTime = 0;
	MessagePos = 2;
	BattleEnemyID = -1;
	ShopType = 0;
	ShopID = -1;
	ShopPrice[0] = 20;
	ShopPrice[1] = 50;
	ShopPrice[2] = 300;
	ShopEXP[0] = 70;
	ShopEXP[1] = 20;
	ShopEXP[2] = 190;
	ShopEXP[3] = 40;
	TransformingEventName = "";
	memset(GameVariables, 0, sizeof(GameVariables));
	memset(GameSwitches, false, sizeof(GameSwitches));
	memset(ItemRecord, false, sizeof(ItemRecord));
	memset(GemRecord, false, sizeof(GemRecord));
	memset(BottleRecord, false, sizeof(BottleRecord));
	NeedRefresh = true;
	ScreenShot = false;
	EndGame = false;
	FirstArrive = false;
	ShotFile = "";
	MessageName.clear();
	MessageContent.clear();
	MessageHead.clear();
	DataLoad();
	Player.Step = 0;
	for (auto &dat : Actors) {
		dat.Status = 0;
		memset(dat.Item, 0, sizeof(dat.Item));
	}
	Player = { 0, false, true };
}

void DataSystem::ReadyTransition() {
	TransitionGraphic = new IMAGE;
	getimage(TransitionGraphic, 0, 0, 608, 448);
	Transition = true;
}

void DataSystem::DoTransition(int time) {
	Transition = false;
	int reduce = ceil(255 * 1.0 / time);
	System.TransitionOpacity = 255;
	rfor(i, 0, time) {
		System.TransitionOpacity = max(System.TransitionOpacity - reduce, 0);
		Graphics.Update();
	}
	delete System.TransitionGraphic;
}

GameSprite::GameSprite() {
	Name = "";
	X = 0;
	Y = 0;
	Z = 0;
	Width = 0;
	Height = 0;
	SrcX = 0;
	SrcY = 0;
	Angle = 0;
	Position = 0;
	Visible = true;
	Image = new IMAGE;
	Opacity = 255;
}

GameSprite::GameSprite(string name) : Name(name){
	Name = name;
	X = 0;
	Y = 0;
	Z = 0;
	Width = 0;
	Height = 0;
	SrcX = 0;
	SrcY = 0;
	Angle = 0;
	Position = 0;
	Opacity = 255;
	Visible = true;
	Image = new IMAGE;
	loadimage(Image, ("res\\picture\\" + Name).c_str());
	Graphics.Patterns.push_back(this);
}

GameSprite::GameSprite(string name, int opacity) : Name(name), Opacity(opacity) {
	X = 0;
	Y = 0;
	Z = 0;
	Width = 0;
	Height = 0;
	SrcX = 0;
	SrcY = 0;
	Angle = 0;
	Position = 0;
	Visible = true;
	Image = new IMAGE;
	loadimage(Image, ("res\\picture\\" + Name).c_str());
	Graphics.Patterns.push_back(this);
}

GameSprite::GameSprite(string name, int x, int y, int opacity) : Name(name), X(x), Y(y), Opacity(opacity) {
	Z = 0;
	Width = 0;
	Height = 0;
	SrcX = 0;
	SrcY = 0;
	Angle = 0;
	Position = 0;
	Visible = true;
	Image = new IMAGE;
	loadimage(Image, ("res\\picture\\" + Name).c_str());
	Graphics.Patterns.push_back(this);
}

int GameSprite::SpriteWidth() {
	if (Width == 0) {
		return Image->getwidth();
	}
	return Width;
}

int GameSprite::SpriteHeight() {
	if (Height == 0) {
		return Image->getheight();
	}
	return Height;
}

void GameSprite::ChangeImage(string name) {
	Name = name;
	delete Image;
	Image = new IMAGE;
	loadimage(Image, ("res\\picture\\" + Name).c_str());
}

void GameSprite::AddIn() {
	Graphics.Patterns.push_back(this);
}

void GameSprite::Dispose() {
	delete this->Image;
	auto pos = find(Graphics.Patterns.begin(), Graphics.Patterns.end(), this);
	int pos2 = pos - Graphics.Patterns.begin();
	Graphics.Patterns.erase(pos);
}

bool GameKeyBoard::LPress(int key) {
	if (GetAsyncKeyState(key) != 0) {
		++hit_times;
		return true;
	}
	return false;
}

bool GameKeyBoard::Press(int key) {
	if ((GetAsyncKeyState(key) & 0x8000) != 0) {
		++hit_times;
		return true;
	}
	return false;
}

bool GameKeyBoard::Repeat(int key) {
	int result = GetAsyncKeyState(key) & 0x8000;
	if (result != 0) {
		++hit_times;
		if (key_repeat.find(key) == key_repeat.end()) {
			key_repeat[key] = 0;
			return true;
		}
		key_repeat[key]++;
	}
	else {
		key_repeat.erase(key);
		key_hash[key] = 0;
	}
	if (!(key_repeat.find(key) == key_repeat.end()) && key_repeat[key] > 2) {
		key_repeat[key] = 0;
		++hit_times;
		return true;
	}
	else {
		return false;
	}
}

bool GameKeyBoard::Trigger(int key) {
	int result = GetAsyncKeyState(key) & 0x8000;
	if (key_hash[key] == 1 && result != 0) {
		return false;
	}
	if (result != 0) {
		++hit_times;
		key_hash[key] = 1;
		return true;
	}
	else {
		key_hash[key] = 0;
		return false;
	}
}

bool GameKeyBoard::PressConfirm() {
	return (Press(KeySPACE) || Press(KeyRETURN));
}

bool GameKeyBoard::RepeatConfirm() {
	return (Repeat(KeySPACE) || Repeat(KeyRETURN));
}

bool GameKeyBoard::TriggerConfirm() {
	return (Trigger(KeySPACE) || Trigger(KeyRETURN));
}

bool GameKeyBoard::PressCancel() {
	return (Press(KeyESCAPE) || Press(KeyX));
}

bool GameKeyBoard::RepeatCancel() {
	return (Repeat(KeyESCAPE) || Repeat(KeyX));
}

bool GameKeyBoard::TriggerCancel() {
	return (Trigger(KeyESCAPE) || Trigger(KeyX));
}

bool GameKeyBoard::DoubleClick(int key) {
	int result = Trigger(key);//(GetAsyncKeyState(key) & 0x8000) != 0;
	if (result == 0) {
		return false;
	}
	++hit_times;
	if (double_click[key] == 0) {
		double_click[key] = clock();
		return false;
	}
	else {
		if (clock() - double_click[key] <= 500) {
			double_click[key] = 0;
			return true;
		}
		else {
			double_click[key] = clock();
			return false;
		}
	}
}

int GameKeyBoard::Dir4() {
	if (Press(KeyDOWN)) {
		return 1;
	}
	if (Press(KeyLEFT)) {
		return 2;
	}
	if (Press(KeyRIGHT)) {
		return 3;
	}
	if (Press(KeyUP)) {
		return 4;
	}
	return 0;
}

GameWindow::GameWindow() {
	X = 0;
	Y = 0;
	Z = 0;
	Width = 32;
	Height = 32;
	Opacity = System.WindowOpacity;
	Visible = true;
}

GameWindow::GameWindow(int x, int y, int width, int height, int opacity) {
	X = x;
	Y = y;
	Z = 0;
	Width = width;
	Height = height;
	Opacity = opacity;
	Visible = true;
	Graphics.Windows.push_back(this);
}

void GameWindow::DrawRect(int x, int y, int width, int rectheight) {
	int cornerx[] = { 128, 158, 128, 158 };
	int cornery[] = { 64, 64, 94, 94 };
	int sidex[] = { 130, 130, 128,  158};
	int sidey[] = { 64, 94, 66, 66 };
	int opacity;
	switch (System.GameTime % 16) {
	case 0:opacity = 240; break;
	case 1:opacity = 225; break;
	case 2:opacity = 210; break;
	case 3:opacity = 195; break;
	case 4:opacity = 180; break;
	case 5:opacity = 165; break;
	case 6:opacity = 150; break;
	case 7:opacity = 135; break;
	case 8:opacity = 150; break;
	case 9:opacity = 165; break;
	case 10:opacity = 180; break;
	case 11:opacity = 195; break;
	case 12:opacity = 210; break;
	case 13:opacity = 225; break;
	case 14:opacity = 240; break;
	case 15:opacity = 255; break;
	}
	WindowRect(130, 66, cornerx, cornery, sidex, sidey, 28, 2, 28, opacity, x + X, y + Y, width, rectheight, true);
}

void GameWindow::WDrawTexts(int x, int y, int width, int height, string content, int pos, LONG size, bool bond) {
	DrawTexts(x + X + 16, y + Y + 16, width, height, content, pos, size, bond);
}

void GameWindow::WindowBitmap(string file, int x, int y, int opacity) {
	BitmapOpaque(file, x + X, y + Y, opacity);
}

void GameWindow::WindowBitmap(string file, int x, int y, int width, int height, int sx, int sy, int opacity) {
	BitmapOpaque(file, x + X, y + Y, width, height, sx, sy, opacity);
}

COLORREF GameWindow::NormalColor() {
	return RGB(255, 255, 255);
}

COLORREF GameWindow::DisabledColor() {
	return RGB(128, 128, 128);
}

COLORREF GameWindow::SystemColor() {
	return RGB(192, 224, 255);
}

COLORREF GameWindow::CrisisColor() {
	return RGB(255, 255, 64);
}

COLORREF GameWindow::TextColor(string type) {
	if (type == "white") {
		return RGB(255, 255, 255);
	}
	if (type == "gray") {
		return RGB(175, 175, 175);
	}
	if (type == "black") {
		return RGB(0, 0, 0);
	}
	if (type == "red") {
		return RGB(255, 50, 50);
	}
	if (type == "yellow") {
		return RGB(255, 255, 128);
	}
	if (type == "orange") {
		return RGB(255, 185, 25);
	}
	if (type == "blue") {
		return RGB(128, 255, 255);
	}
	if (type == "green") {
		return RGB(128, 255, 128);
	}
	if (type == "pink") {
		return RGB(255, 128, 255);
	}
	return RGB(255, 255, 255);
}

void GameWindow::Dispose() {
	auto pos = find(Graphics.Windows.begin(), Graphics.Windows.end(), this);
	Graphics.Windows.erase(pos);
}

GameSelectWindow::GameSelectWindow(int rectheight, vector <string> item) {
	X = 0;
	Y = 0;
	Z = 0;
	Width = 32;
	Height = 32;
	Opacity = 255;
	HasFunction = true;
	Active = true;
	RectHeight = rectheight;
	Items = item;
	Graphics.Windows.push_back(this);
}

void GameSelectWindow::Refresh() {
	rfor(i, 0, Items.size()) {
		if (i == Index) {
			DrawRect(16, 16 + RectHeight * i, Width - 32, RectHeight);
		}
		DrawItem(i, NormalColor());
	}
	unless(Active) {
		return;
	}
	if (KeyBoard.Repeat(KeyBoard.KeyUP)) {
		if (Index > 0) {
			--Index;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
	if (KeyBoard.Repeat(KeyBoard.KeyDOWN)) {
		if (Index < Items.size()-1) {
			++Index;
			PlaySE(System.CursorSE);
		}
		else {
			PlaySE(System.BuzzerSE);
		}
		return;
	}
}

void GameSelectWindow::DrawItem(int index, COLORREF colour) {
	WDrawTexts(4, 4 + RectHeight * index, Width, RectHeight, Items[index]);
}

void GamePlayer::Update() {
	if (MovingCount > 0) {
		return;
	}
	switch (KeyBoard.Dir4()) {
	case 1:
		Direction = 0;
		if (System.Maps[Actors[System.GameVariables[1]].MapID].Passible(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y + 1)) {
			PlaySE(System.MoveSE);
			++Player.Step;
			MovingCount = 4;
			++Actors[System.GameVariables[1]].Y;
			ChangeStep();
			if (System.Maps[Actors[System.GameVariables[1]].MapID].HaveAnEvent(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y)) {
				System.Maps[Actors[System.GameVariables[1]].MapID].ECheckEvent(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y)->Order();
			}
		}
		else {
			if (System.Maps[Actors[System.GameVariables[1]].MapID].HaveAnEvent(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y + 1)) {
				System.Maps[Actors[System.GameVariables[1]].MapID].ECheckEvent(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y + 1)->Order();
			}
		}
		break;
	case 2:
		Direction = 1;
		if (System.Maps[Actors[System.GameVariables[1]].MapID].Passible(Actors[System.GameVariables[1]].X - 1, Actors[System.GameVariables[1]].Y)) {
			PlaySE(System.MoveSE);
			++Player.Step;
			MovingCount = MovingCount < 2 ? 2 : 4;
			--Actors[System.GameVariables[1]].X;
			ChangeStep();
			if (System.Maps[Actors[System.GameVariables[1]].MapID].HaveAnEvent(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y)) {
				System.Maps[Actors[System.GameVariables[1]].MapID].ECheckEvent(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y)->Order();
			}
		}
		else {
			if (System.Maps[Actors[System.GameVariables[1]].MapID].HaveAnEvent(Actors[System.GameVariables[1]].X - 1, Actors[System.GameVariables[1]].Y)) {
				System.Maps[Actors[System.GameVariables[1]].MapID].ECheckEvent(Actors[System.GameVariables[1]].X - 1, Actors[System.GameVariables[1]].Y)->Order();
			}
		}
		break;
	case 3:
		Direction = 2;
		if (System.Maps[Actors[System.GameVariables[1]].MapID].Passible(Actors[System.GameVariables[1]].X + 1, Actors[System.GameVariables[1]].Y)) {
			PlaySE(System.MoveSE);
			++Player.Step;
			MovingCount = MovingCount < 2 ? 2 : 4;
			++Actors[System.GameVariables[1]].X;
			ChangeStep();
			if (System.Maps[Actors[System.GameVariables[1]].MapID].HaveAnEvent(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y)) {
				System.Maps[Actors[System.GameVariables[1]].MapID].ECheckEvent(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y)->Order();
			}
		}
		else {
			if (System.Maps[Actors[System.GameVariables[1]].MapID].HaveAnEvent(Actors[System.GameVariables[1]].X + 1, Actors[System.GameVariables[1]].Y)) {
				System.Maps[Actors[System.GameVariables[1]].MapID].ECheckEvent(Actors[System.GameVariables[1]].X + 1, Actors[System.GameVariables[1]].Y)->Order();
			}
		}
		break;
	case 4:
		Direction = 3;
		if (System.Maps[Actors[System.GameVariables[1]].MapID].Passible(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y - 1)) {
			PlaySE(System.MoveSE);
			++Player.Step;
			MovingCount = MovingCount < 2 ? 2 : 4;
			--Actors[System.GameVariables[1]].Y;
			ChangeStep();
			if (System.Maps[Actors[System.GameVariables[1]].MapID].HaveAnEvent(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y)) {
				System.Maps[Actors[System.GameVariables[1]].MapID].ECheckEvent(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y)->Order();
			}
		}
		else {
			if (System.Maps[Actors[System.GameVariables[1]].MapID].HaveAnEvent(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y - 1)) {
				System.Maps[Actors[System.GameVariables[1]].MapID].ECheckEvent(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y - 1)->Order();
			}
		}
		break;
	}
	return;
}

void GamePlayer::ChangeStep() {
	if (Actors[System.GameVariables[1]].Status == 1) {
		Actors[System.GameVariables[1]].Hp = max(Actors[System.GameVariables[1]].Hp - 10, 0);
		if (Actors[System.GameVariables[1]].Hp <= 0) {
			System.EndGame = true;
			return;
		}
	}
	for (auto ev : System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents) {
		if (!ev.Exist) {
			continue;
		}
		vector <string> name = Split(ev.Name, "|");
		if (name[0] == "MONSTER") {
			int id = stoi(name[1]);
			if (Enemies[id].GotP(15)) {
				if (!DataMap::HaveEventsAlong({ Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y }, { ev.X, ev.Y })) {
					int dam = Enemies[id].Atk - Actors[System.GameVariables[1]].Def + System.GameVariables[5];
					if (Actors[System.GameVariables[1]].Item[18] > 0) {
						dam -= dam * 3 / 4;
					}
					else if (Actors[System.GameVariables[1]].Item[12] > 0) {
						dam -= dam / 2;
					}
					if (dam > 0) {
						Actors[System.GameVariables[1]].Hp = max(Actors[System.GameVariables[1]].Hp - dam, 0);
						Graphics.Animations.push({ System.MapX + Actors[System.GameVariables[1]].X * 32 + 16, System.MapY + Actors[System.GameVariables[1]].Y * 32 + 16, 0, Animation[23] });
						if (Actors[System.GameVariables[1]].Hp <= 0) {
							System.EndGame = true;
							return;
						}
					}
				}
			}
			if (Enemies[id].GotP(16)) {
				if (DataMap::Beside({ ev.X, ev.Y }, { Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y })) {
					int dam = Enemies[id].Atk / 2;
					if (Actors[System.GameVariables[1]].Item[18] > 0) {
						dam -= dam * 3 / 4;
					}
					else if (Actors[System.GameVariables[1]].Item[12] > 0) {
						dam -= dam / 2;
					}
					Actors[System.GameVariables[1]].Hp = max(Actors[System.GameVariables[1]].Hp - dam, 0);
					Graphics.Animations.push({ System.MapX + Actors[System.GameVariables[1]].X * 32 + 16, System.MapY + Actors[System.GameVariables[1]].Y * 32 + 16, 0, Animation[Enemies[id].AnimationID] });
					if (Actors[System.GameVariables[1]].Hp <= 0) {
						System.EndGame = true;
						return;
					}
				}
			}
		}
	}
	if (System.Maps[Actors[System.GameVariables[1]].MapID].HaveAnEvent(Actors[System.GameVariables[1]].X + 1, Actors[System.GameVariables[1]].Y)) {
		if (System.Maps[Actors[System.GameVariables[1]].MapID].HaveAnEvent(Actors[System.GameVariables[1]].X - 1, Actors[System.GameVariables[1]].Y)) {
			int id1 = System.Maps[Actors[System.GameVariables[1]].MapID].CheckEvent(Actors[System.GameVariables[1]].X + 1, Actors[System.GameVariables[1]].Y), id2 = System.Maps[Actors[System.GameVariables[1]].MapID].CheckEvent(Actors[System.GameVariables[1]].X - 1, Actors[System.GameVariables[1]].Y);
			if (System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[id1].Name == System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[id2].Name) {
				vector <string> name = Split(System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[id1].Name, "|");
				if (name[0] == "MONSTER") {
					int id = stoi(name[1]);
					if (Enemies[id].GotP(19)) {
						int dam = Enemies[id].Atk * 2;
						if (Actors[System.GameVariables[1]].Item[18] > 0) {
							dam -= dam * 3 / 4;
						}
						else if (Actors[System.GameVariables[1]].Item[12] > 0) {
							dam -= dam / 2;
						}
						Actors[System.GameVariables[1]].Hp = max(Actors[System.GameVariables[1]].Hp - dam, 0);
						Graphics.Animations.push({ System.MapX + Actors[System.GameVariables[1]].X * 32 + 16, System.MapY + Actors[System.GameVariables[1]].Y * 32 + 16, 0, Animation[Enemies[id].AnimationID] });
						if (Actors[System.GameVariables[1]].Hp <= 0) {
							System.EndGame = true;
							return;
						}
					}
				}
			}
		}
	}
	if (System.Maps[Actors[System.GameVariables[1]].MapID].HaveAnEvent(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y + 1)) {
		if (System.Maps[Actors[System.GameVariables[1]].MapID].HaveAnEvent(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y - 1)) {
			int id1 = System.Maps[Actors[System.GameVariables[1]].MapID].CheckEvent(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y + 1), id2 = System.Maps[Actors[System.GameVariables[1]].MapID].CheckEvent(Actors[System.GameVariables[1]].X, Actors[System.GameVariables[1]].Y - 1);
			if (System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[id1].Name == System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[id2].Name) {
				vector <string> name = Split(System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[id1].Name, "|");
				if (name[0] == "MONSTER") {
					int id = stoi(name[1]);
					if (Enemies[id].GotP(19)) {
						int dam = Enemies[id].Atk * 2;
						if (Actors[System.GameVariables[1]].Item[18] > 0) {
							dam -= dam * 3 / 4;
						}
						else if (Actors[System.GameVariables[1]].Item[12] > 0) {
							dam -= dam / 2;
						}
						Actors[System.GameVariables[1]].Hp = max(Actors[System.GameVariables[1]].Hp - dam, 0);
						Graphics.Animations.push({ System.MapX + Actors[System.GameVariables[1]].X * 32 + 16, System.MapY + Actors[System.GameVariables[1]].Y * 32 + 16, 0, Animation[Enemies[id].AnimationID] });
						if (Actors[System.GameVariables[1]].Hp <= 0) {
							System.EndGame = true;
							return;
						}
					}
				}
			}
		}
	}

}

const bool GameEnemies::operator < (GameEnemies& en) {
	if (GotDamage() != en.GotDamage()) {
		return (GotDamage() < en.GotDamage());
	}
	return (Name < en.Name);
}

tuple <int, string> GameEnemies::GotDamage() {
	int vampire = 0;
	int first = 0;
	int ma = Actors[System.GameVariables[1]].Atk - System.GameVariables[5];
	int md = Actors[System.GameVariables[1]].Def - System.GameVariables[5];
	int mmd = Actors[System.GameVariables[1]].Mdef;
	int ehp = Hp;
	int ea = Atk;
	int ed = Def;
	if (VectorFind(Element, 6)) {
		md = 0;
	}
	if (VectorFind(Element, 3)) {
		vampire = (ea - md) * stoi(Split(Name, "|")[1]) / 100;
	}
	if (VectorFind(Element, 4)) {
		ed = max(ed, ma - 1);
	}
	if (VectorFind(Element, 5)) {
		first = max(Conatk, 1);
	}
	if (VectorFind(Element, 11)) {
		mmd = 0;
	}
	if (VectorFind(Element, 15)) {
		ea /= 2;
	}
	if (VectorFind(Element, 27)) {
		md /= 2;
	}
	if (ma <= ed) {
		return { 999999, "DIE" };
	}
	if (ehp + vampire * first <= ma + mmd - ed) {
		return { 0, "0" };
	}
	if (ma + mmd > ed + vampire * max(1, Conatk)) {
		int eatimes = (ehp + vampire * first) / (ma + mmd - ed - vampire * max(1, Conatk));
		if (eatimes == (ehp + vampire * first) * 1.0 / (ma + mmd - ed - vampire * max(1, Conatk))) {
			--eatimes;
		}
		eatimes += first;
		eatimes = max(eatimes, 0);
		if (md >= ea) {
			return { 0, "0" };
		}
		int res = max(0, (ea - md) * max(1, Conatk) * eatimes);
		if (VectorFind(Element, 13) && ea >= Actors[System.GameVariables[1]].Def - System.GameVariables[5]) {
			res *= 2;
		}
		if (VectorFind(Element, 23) && eatimes >= 1) {
			res *= (QuickPow(2, eatimes) - 1) / eatimes;
		}
		return { res, to_string(res) };
	}
	else {
		return { 999999, "DIE" };
	}
}

int GameEnemies::GotAtk() {
	return (GotP(15) ? Atk / 2 : Atk);
}

int GameEnemies::GotDef() {
	return GotP(4) ? max(Actors[System.GameVariables[1]].Atk - System.GameVariables[5] - 1, Def) : Def;
}

bool GameEnemies::GotP(int p) {
	return (VectorFind(Element, p));
}

int GameEnemies::GotCrisis() {
	if (Actors[System.GameVariables[1]].Atk <= GotDef()) {
		return (GotDef() + 1);
	}
	if (Actors[System.GameVariables[1]].Atk >= Hp + GotDef()) {
		return -2;
	}
	if (GotP(4)) {
		return -1;
	}
	return (ceil(Hp * 1.0 / max(ceil(Hp * 1.0 / (Actors[System.GameVariables[1]].Atk + (GotP(11) ? 0 : Actors[System.GameVariables[1]].Mdef) - System.GameVariables[5] - GotDef())) - 1, 0)) + GotDef() + System.GameVariables[5] - (GotP(11) ? 0 : Actors[System.GameVariables[1]].Mdef));
}

pair <string, string> GameEnemies::EnemyElement(int elementid) {
	string name, description;
	switch (elementid)
	{
	case 1:
		name = "中毒";
		description = "怪物的攻击有概率附加中毒状态";
		break;
	case 2:
		name = "衰弱";
		description = "怪物的攻击有概率附加衰弱状态";
		break;
	case 3:
		name = "吸血";
		description = "怪物造成伤害后会恢复伤害值" + Split(Name, "|")[1] + "%的生命";
		break;
	case 4:
		name = "坚固";
		description = "怪物的防御不少于己方攻击-1";
		break;
	case 5:
		name = "先攻";
		description = "战斗开始时怪物率先攻击";
		break;
	case 6:
		name = "魔攻";
		description = "战斗时，怪物的攻击无视己方的防御";
		break;
	case 7:
		name = to_string(Conatk) + "连击";
		description = "怪物每回合进行" + to_string(Conatk) + "次攻击";
		break;
	case 8:
		name = "再生";
		description = "战斗后，怪物会变身成为另一怪物。";
		break;
	case 9:
		name = "粘液";
		description = "战斗时，怪物的每次攻击会增加己方" + Split(Name, "|")[1] + "点疲劳";
		break;
	case 10:
		name = "必杀";
		description = "怪物暴击伤害是普通伤害的3倍";
		break;
	case 11:
		name = "破魔";
		description = "怪物无视魔力固伤，且魔法技对其伤害减半";
		break;
	case 12:
		name = "幻手";
		description = "怪物攻击有概率降低我方" + Split(Name, "|")[1] + "点魔力（不会低于0）";
		break;
	case 13:
		name = "死咒";
		description = "如果我方防御不高于怪物攻击则怪物伤害加倍";
		break;
	case 14:
		name = "暴躁";
		description = "会心一击造成5倍伤害，并损失当前一半体力";
		break;
	case 15:
		name = "伏击";
		description = "与其同行列会受到攻击，近身战斗时攻击减半";
		break;
	case 16:
		name = "领域";
		description = "经过其身边时会受到" + to_string(Atk / 2) + "点伤害";
		break;
	case 17:
		name = "邪眼";
		description = "该怪物存活时无法楼层传送";
		break;
	case 18:
		name = "寒霜";
		description = "有概率让己方冰冻，" + Split(Name, "|")[1] + "回合内无法攻击，一次\n战斗至多触发一次";
		break;
	case 19:
		name = "夹击";
		description = "经过两怪物中间时会受到二者共同攻击";
		break;
	case 20:
		name = "天雷";
		description = "攻击不会增加我方气息，且暴击会减少我方\n2格气息，并附加" + Split(Name, "|")[1] + "点疲劳";
		break;
	case 21:
		name = "炽炎";
		description = "死后会变成一块熔岩路障";
		break;
	case 22:
		name = "极寒";
		description = "死后变成一块冰（可以用随意门消去）";
		break;
	case 23:
		name = "灼烧";
		description = "每次攻击后，下一次的伤害会翻倍";
		break;
	case 24:
		name = "爆炎";
		description = "死后周围可通行的9格会变成熔岩路障";
		break;
	case 25:
		name = "气场";
		description = "满气息和零气息时不会受到伤害";
		break;
	case 26:
		name = "血奴";
		description = "若我方有一格以上气息，则会消耗一格让敌方会心一击";
		break;
	case 27:
		name = "破甲";
		description = "无视我方一半防御";
		break;
	case 28:
		name = "雪国";
		description = "死后周围可通行9格会变成冰";
		break;
	case 29:
		name = "穿刺";
		description = "攻击有概率降低我方" + Split(Name, "|")[1] + "点攻防";
		break;
	case 30:
		name = "猛毒";
		description = "攻击有概率附加毒，攻击中毒的对象会增强" + Split(Name, "|")[1] + "点攻防";
		break;
	case 31:
		name = "绝剑";
		description = "气息积满时，会心一击持续到回合结束";
		break;
	case 32:
		name = "圣剑";
		description = "会心一击造成6倍伤害";
		break;
	case 33:
		name = "戏法";
		description = "攻击时，攻击和防御有概率翻转";
		break;
	case 34:
		name = "轮回";
		description = "一共9次生命,每次死亡会提升10%的能力\n和30%的体力,清空自身疲劳,吸取我方一格气息";
		break;
	default:
		name = "普通";
		description = "没有特殊效果";
		break;
	}
	return { name,description };
}

SpriteSetMap::SpriteSetMap() {
	Active = false;
}

void SpriteSetMap::Initialization() {
	Active = true;
	FloorImage = new IMAGE;
	loadimage(FloorImage, ("res\\picture\\" + System.Maps[Actors[System.GameVariables[1]].MapID].FloorName).c_str());
	ActorImage = new IMAGE;
	loadimage(ActorImage, ("res\\picture\\" + Actors[System.GameVariables[1]].File).c_str());
	ActorWidth = ActorImage->getwidth() / 4;
	ActorHeight = ActorImage->getheight() / 4;
	rfor(i, 0, 121) {
		EventsImage[i][0] = new IMAGE;
		EventsImage[i][1] = new IMAGE;
	}
	rfor(i, 0, System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents.size()) {
		loadimage(EventsImage[i][0], ("res\\picture\\" + System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[i].File[0]).c_str());
		loadimage(EventsImage[i][1], ("res\\picture\\" + System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[i].File[1]).c_str());
	}
	StatusImage = new IMAGE;
	loadimage(StatusImage, "res\\picture\\mting-1284.png");
}

void SpriteSetMap::MapStatus() {
	OpaqueImage(nullptr, 0, 0, StatusImage);
	BitmapOpaque(Actors[System.GameVariables[1]].File, 40, 40, ActorWidth, ActorHeight, 0, 0);
	string status;
	switch (Actors[System.GameVariables[1]].Status) {
	case 1: status = "中 毒"; break;
	case 2: status = "衰 弱"; break;
	default: status = "正 常"; break;
	}
	DrawTexts(104, 56, 64, 20, status, 1);
	Font.lfItalic = 1;
	settextstyle(&Font);
	DrawTexts(90, 98, 100, 16, to_string(Actors[System.GameVariables[1]].Level), 1);
	DrawTexts(90, 126, 100, 16, to_string(Actors[System.GameVariables[1]].Hp), 1);
	DrawTexts(90, 154, 100, 16, to_string(Actors[System.GameVariables[1]].Atk), 1);
	DrawTexts(90, 182, 100, 16, to_string(Actors[System.GameVariables[1]].Def), 1);
	DrawTexts(90, 210, 100, 16, to_string(Actors[System.GameVariables[1]].Mdef), 1);
	DrawTexts(90, 238, 100, 16, to_string(Actors[System.GameVariables[1]].Exp), 1);
	if (Actors[System.GameVariables[1]].Status == 2) {
		settextcolor(GameWindow::TextColor("red"));
		DrawTexts(90, 154, 100, 24, "(- " + to_string(System.GameVariables[5]) + ")", 2, 14L);
		DrawTexts(90, 182, 100, 24, "(- " + to_string(System.GameVariables[5]) + ")", 2, 14L);
		settextcolor(GameWindow::TextColor("white"));
	}
	Font.lfItalic = 0;
	settextstyle(&Font);
	char num[3][4];
	sprintf_s(num[0], "%02d", Actors[System.GameVariables[1]].Item[0]);
	sprintf_s(num[1], "%02d", Actors[System.GameVariables[1]].Item[1]);
	sprintf_s(num[2], "%02d", Actors[System.GameVariables[1]].Item[2]);
	DrawTexts(110, 326, 100, 24, num[0], 0);
	DrawTexts(129, 324, 100, 24, "/", 0, 26L);
	DrawTexts(140, 326, 100, 24, num[1], 0);
	DrawTexts(159, 324, 100, 24, "/", 0, 26L);
	DrawTexts(170, 326, 100, 24, num[2], 0);
	DrawTexts(100, 358, 90, 18, to_string(Actors[System.GameVariables[1]].Gold), 1, 24L);
	string towername;
	switch (System.GameVariables[3]) {
	case 0: towername = "主塔"; break;
	case 1: towername = "主塔"; break;
	case 2: towername = "主塔"; break;
	case 3: towername = "魔塔"; break;
	case 4: towername = "魔塔"; break;
	case 5: towername = "侧塔"; break;
	case 6: towername = "侧塔"; break;
	case 7: towername = "魔塔"; break;
	}
	if (StringInclude(System.Maps[Actors[System.GameVariables[1]].MapID].MapName, ":")) {
		DrawTexts(356, 0, 32, 32, towername, 1);
		DrawTexts(404, 0, 40, 32, to_string(System.GameVariables[2]) + " 层", 1);
	}
	else {
		towername = System.Maps[Actors[System.GameVariables[1]].MapID].MapName;
		DrawTexts(352, 0, 96, 32, towername, 1);
	}
	DrawTexts(0, 420, 600, 32, "-Press L-", 2);
	string breathfile1[] = { "mting-1211.png", "mting-1212.png", "mting-1213.png" };
	string breathfile2[] = { "mting-1211_g.png", "mting-1212_g.png", "mting-1213_g.png" };
	rfor(i, 0, 5) {
		switch ((System.GameTime % 30) / 10) {
		case 0: BitmapOpaque(Actors[System.GameVariables[1]].Breath >= floor(Actors[System.GameVariables[1]].BreathLimit / 6) * (i + 1) ? breathfile1[0] : breathfile2[0], 104 + 14 * i, 254); break;
		case 1: BitmapOpaque(Actors[System.GameVariables[1]].Breath >= floor(Actors[System.GameVariables[1]].BreathLimit / 6) * (i + 1) ? breathfile1[1] : breathfile2[1], 105 + 14 * i, 253); break;
		case 2: BitmapOpaque(Actors[System.GameVariables[1]].Breath >= floor(Actors[System.GameVariables[1]].BreathLimit / 6) * (i + 1) ? breathfile1[2] : breathfile2[2], 105 + 14 * i, 253); break;
		}
	}
	BitmapOpaque("mting-1226.png", 99, 271, 80, 4, 0, 0);
	BitmapOpaque("mting-1226.png", 99, 271, Actors[System.GameVariables[1]].Breath % (Actors[System.GameVariables[1]].BreathLimit / 6) * 80 / (Actors[System.GameVariables[1]].BreathLimit / 6), 4, 0, 4);
	if (Actors[System.GameVariables[1]].Item[3] > 0) {
		BitmapOpaque("mting-1267.png", 8, 416);
	}
	if (Actors[System.GameVariables[1]].Item[4] > 0) {
		BitmapOpaque("mting-1266.png", 48, 416);
	}
	if (System.GameSwitches[11]) {
		BitmapOpaque("mting-1217.png", 88, 416);
		DrawTexts(128, 416, 64, 32, "×" + to_string(Actors[System.GameVariables[1]].Item[5]));
	}
	if (Actors[System.GameVariables[1]].Item[18] > 0) {
		BitmapOpaque("mting-1280.png", 168, 416);
	}
	else if (Actors[System.GameVariables[1]].Item[12] > 0) {
		BitmapOpaque("mting-1279.png", 168, 416);
	}
	if (Actors[System.GameVariables[1]].Item[15] > 0) {
		BitmapOpaque("mting-1265.png", 208, 416);
	}
	if (Actors[System.GameVariables[1]].Item[17] > 0) {
		BitmapOpaque("mting-15.png", 248, 416);
	}
	else if (Actors[System.GameVariables[1]].Item[16] > 0) {
		BitmapOpaque("mting-246.png", 248, 416);
	}
}

void SpriteSetMap::Update() {
	if (System.NeedRefresh) {
		delete FloorImage;
		FloorImage = new IMAGE;
		loadimage(FloorImage, ("res\\picture\\" + System.Maps[Actors[System.GameVariables[1]].MapID].FloorName).c_str());
		delete ActorImage;
		ActorImage = new IMAGE;
		loadimage(ActorImage, ("res\\picture\\" + Actors[System.GameVariables[1]].File).c_str());
		ActorWidth = ActorImage->getwidth() / 4;
		ActorHeight = ActorImage->getheight() / 4;
		rfor(i, 0, 121) {
			delete EventsImage[i][0];
			delete EventsImage[i][1];
			EventsImage[i][0] = new IMAGE;
			EventsImage[i][1] = new IMAGE;
		}
		rfor(i, 0, System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents.size()) {
			loadimage(EventsImage[i][0], ("res\\picture\\" + System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[i].File[0]).c_str());
			loadimage(EventsImage[i][1], ("res\\picture\\" + System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[i].File[1]).c_str());
		}
		System.NeedRefresh = false;
	}
	putimage(System.MapX, System.MapY, FloorImage);
	rfor(i, 0, System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents.size()) {
		unless(System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[i].Exist) {
			continue;
		}
		if (System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[i].TriggerCondition[0] != 0) {
			if (System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[i].TriggerCondition[0] == 1 && System.GameSwitches[System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[i].TriggerCondition[1]] != System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[i].TriggerCondition[2]) {
				continue;
			}
			if (System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[i].TriggerCondition[0] == 2 && System.GameVariables[System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[i].TriggerCondition[1]] != System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[i].TriggerCondition[2]) {
				continue;
			}
		}
		OpaqueImage(nullptr, System.MapX + System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[i].X * 32 + 16 - EventsImage[i][(System.GameTime % 20) / 10]->getwidth() / 2, System.MapY + System.Maps[Actors[System.GameVariables[1]].MapID].MapEvents[i].Y * 32 + 16 - EventsImage[i][(System.GameTime % 20) / 10]->getheight() / 2, EventsImage[i][(System.GameTime % 20) / 10]);
	}
	unless(Player.Visible) {
		return;
	}
	switch (Player.Direction) {
	case 0: OpaqueImage(nullptr, System.MapX + Actors[System.GameVariables[1]].X * 32, System.MapY + Actors[System.GameVariables[1]].Y * 32 - 8 * Player.MovingCount, ActorWidth, ActorHeight, max(0, Player.MovingCount - 1) * ActorWidth, ActorHeight * Player.Direction, ActorImage); break;
	case 1: OpaqueImage(nullptr, System.MapX + Actors[System.GameVariables[1]].X * 32 + 8 * Player.MovingCount, System.MapY + Actors[System.GameVariables[1]].Y * 32, ActorWidth, ActorHeight, max(0, Player.MovingCount - 1) * ActorWidth, ActorHeight * Player.Direction, ActorImage); break;
	case 2: OpaqueImage(nullptr, System.MapX + Actors[System.GameVariables[1]].X * 32 - 8 * Player.MovingCount, System.MapY + Actors[System.GameVariables[1]].Y * 32, ActorWidth, ActorHeight, max(0, Player.MovingCount - 1) * ActorWidth, ActorHeight * Player.Direction, ActorImage); break;
	case 3: OpaqueImage(nullptr, System.MapX + Actors[System.GameVariables[1]].X * 32, System.MapY + Actors[System.GameVariables[1]].Y * 32 + 8 * Player.MovingCount, ActorWidth, ActorHeight, max(0, Player.MovingCount - 1) * ActorWidth, ActorHeight * Player.Direction, ActorImage); break;
	}
	
	if (Player.MovingCount > 0) {
		--Player.MovingCount;
	}
	MapStatus();
}

void SpriteSetMap::Dispose() {
	Active = false;
	delete FloorImage;
	delete ActorImage;
	delete StatusImage;
	rfor(i, 0, 121) {
		delete EventsImage[i][0];
		delete EventsImage[i][1];
	}
}

void GameGraphics::Update() {
	cleardevice();
	if (System.Transition) {
		OpaqueImage(nullptr, 0, 0, System.TransitionGraphic, 255);
		FlushBatchDraw();
		++System.GameTime;
		Sleep(System.FrameRate);
		return;
	}
	if (MapPatterns.Active) {
		MapPatterns.Update();
	}
	rfor(z, 0, 9) {
		unless(Windows.empty()) {
			for (auto win : Windows) {
				unless(win->Visible) {
					continue;
				}
				unless(win->Z == z) {
					continue;
				}
				int cornerx[] = { 128, 176, 128, 176 };
				int cornery[] = { 0, 0, 48, 48 };
				int sidex[] = { 144, 144, 128, 176 };
				int sidey[] = { 0, 48, 16, 16 };
				WindowRect(0, 0, cornerx, cornery, sidex, sidey, 128, 16, 32, win->Opacity, win->X, win->Y, win->Width, win->Height, false);
				if (win->HasFunction) {
					win->Refresh();
				}
			}
		}
		unless(Patterns.empty()) {
			for (auto spr : Patterns) {
				unless(spr->Visible) {
					continue;
				}
				unless(spr->Z == z) {
					continue;
				}
				if (spr->Width == 0 || spr->Height == 0) {
					if (spr->Position == 0) {
						OpaqueImage(nullptr, spr->X, spr->Y, spr->Image, spr->Opacity);
					}
					else if (spr->Position == 1) {
						OpaqueImage(nullptr, spr->X - spr->SpriteWidth() / 2, spr->Y - spr->SpriteHeight() / 2, spr->Image, spr->Opacity);
					}
				}
				else {
					OpaqueImage(nullptr, spr->X, spr->Y, spr->Width, spr->Height, spr->SrcX, spr->SrcY, spr->Image, spr->Opacity);
				}
			}
		}
	}
	int index = 0;
	stack <SpriteAnimation> stk;
	while (!Animations.empty()) {
		SpriteAnimation temp = Animations.top();
		Animations.pop();
		BitmapCentre(temp.Type.Pattern[temp.CurrentFrame], temp.ActX, temp.ActY);
		if (temp.CurrentFrame == temp.Type.SETime) {
			PlaySE(temp.Type.SEFile);
		}
		++temp.CurrentFrame;
		if (temp.CurrentFrame < temp.Type.Pattern.size()) {
			stk.push(temp);
		}
	}
	unless(stk.empty()) {
		swap(Animations, stk);
	}
	stack <SpriteDamage> dstk;
	while (!Damages.empty()) {
		SpriteDamage temp = Damages.top();
		Damages.pop();
		if (temp.Damage == "0") {
			continue;
		}
		settextcolor(temp.Color);
		Font.lfOrientation = -150;
		settextstyle(&Font);
		rfor(i, 0, min(temp.CurrentFrame, temp.Damage.length() * 2)) {
			if (temp.CurrentFrame & 1 && i == temp.CurrentFrame - 1) {
				DrawTexts(temp.ActX + floor(i / 2) * 8, temp.ActY, 96, 32, " " + temp.Damage.substr(i / 2, 1), 0, 12L, true);
			}
			else {
				DrawTexts(temp.ActX + floor(i / 2) * 8, temp.ActY, 96, 32, " " + temp.Damage.substr(i / 2, 1), 0, 22L, true);
			}
		}
		settextcolor(WHITE);
		Font.lfOrientation = 0;
		settextstyle(&Font);
		++temp.CurrentFrame;
		if (temp.CurrentFrame / 2 <= temp.Damage.length() + 1) {
			dstk.push(temp);
		}
	}
	unless(dstk.empty()) {
		swap(Damages, dstk);
	}
	if (System.TransitionOpacity > 0) {
		OpaqueImage(nullptr, 0, 0, System.TransitionGraphic, System.TransitionOpacity);
	}
	FlushBatchDraw();
	++System.GameTime;
	Sleep(System.FrameRate);
}

void GameGraphics::Dispose() {
	cleardevice();
}
