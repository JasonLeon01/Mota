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
		case 0: System.MessageName = { "����" }; System.MessageContent = { "�Ǹ������ܣ�һֱ���������ܿ��ˡ�\n��һ��Ҫ�ӳ�ȥ��" }; System.MessageHead = { 72 }; break;
		case 1: System.MessageName = { "����", "����", "����", "����" }; System.MessageContent = { "�Դ���������ƴ��������ֹ��ħ��֮���Ŷ�֮��ħ��Ӧ�����Ѿ�����������˲Ŷ�", "���ħ�︴�٣�����һ����ʲô����", "���������͹Ŷ�������������ǰ��ȥ����������ȴ��û���ҵ�ʬ��", "����������ԭ���ҵ�����\n��һ��Ҫ��������������" }; System.MessageHead = { -1, -1, -1, -1 }; Exist = false; break;
		case 2: System.MessageName = { "�ľ�����", "����", "�ľ�����", "����", "�ľ�����", "����", "�ľ�����", "����" }; System.MessageContent = { "��Ī���ǡ�������", "�ϲ�������ʶ�ң�", "���������������ʱ������Ե�����ľ�����������λ����", "ԭ��������\n��л�ϲ���ʱ����", "���ӣ����ʹ���δ���ݣ����ֺο��ػ������ĵ�", "�Ҳ������ҵĹ��Һ�������ˮ��\n��ϣ��ȥ����������������", "�����ˣ���������Ϲ�ͷ�ᾡ�������㣬������һ�桸�ľ�����Ҫ���Ʊ���", "лл��" }; System.MessageHead = { 107, -1, 107, -1, 107, -1, 107, -1 }; System.TransformingEventName = "ITEM|3|1"; System.DirectlyFunction = true; break;
		case 3: System.MessageName = { "����", "����" }; System.MessageContent = { "��֪����\n����L�����Ե�֪����ָ��", "������˵����" }; System.MessageHead = { 87, -1 }; break;
		case 4: System.MessageName = { "��������", "����", "��������", "����" }; System.MessageContent = { "�ⲻ�ǹ���������\n����ô���������̫Σ����", "��ʿ�����Ѿ������ˡ�\n�ұ���Ҫ���Լ��������������ҵĹ���", "����������ȷʵ̫��ϧ��\n�����Ҵ���ķ��𣬺���ʿ����ӵ�еĻƽ�������ƣ�ϣ�������а���", "лл�㣡" }; System.MessageHead = { 88, -1, 88, -1 }; System.TransformingEventName = "ITEM|4|1"; System.DirectlyFunction = true; break;
		case 5: System.MessageName = { "ǿ׳����", "ǿ׳����" }; System.MessageContent = { "��������\n�������ͷ�ο��Դ���ħ��", "����Ĺ������ڹ������ʱ�����ħ�����Լӳ����������ӷ�������˺�\n����ÿһ���̱�ʯ�������" }; System.MessageHead = { 89, 89 }; break;
		case 6: System.MessageName = { "����", "����", "����", "����" }; System.MessageContent = { "��\n�ⲻ���ϴεĹ�����", "��ã���������", "�ҾͲ������������Ŀ����\n��һ��ð������Ȼ׼���˴�����Կ��", "����Ļ���ʱ�����Ұ�" }; System.MessageHead = { 103, -1, 103, 103 }; System.TransformingEventName = "KEYSHOP"; System.DirectlyFunction = false; break;
		case 7: System.MessageName = { "����", "����", "����" }; System.MessageContent = { "��֪��ʲô�ǹ���ħ���ͷ���ħ����", "���Ƕ���һ���������������ս���а�Z��X����ʹ�á����ܹ�������Ϣ���������ħ�����������Ч��", "��������ħ������ѧϰ��ֻ�дﵽһ���ȼ����ܳɹ�ʹ��" }; System.MessageHead = { 83, 83, 83 }; break;
		case 8: System.MessageName = { "ƣ̬����", "ƣ̬����" }; System.MessageContent = { "������Ѿ��ܹ�����Щ���ĵĹ����Լ��蹷һ��Ĺ���", "����֧Ԯ�����������ŵ�ǰ������¥�ϣ����Ҫ�ҵ�����" }; System.MessageHead = { 84, 84, 84 }; break;
		case 9: System.MessageName = { "����", "����", "����", "����", "����" }; System.MessageContent = { "���ӣ������ڵ��������ˣ�һ·��û�ٳԿ��", "ȷʵ���ѡ�\n������������һ���������", "������˵����һ����Ҳ��Ϊ���ṩ�����ţ���������3�����ˣ���T��ʹ�ã�û�����ǰɣ�", "������Ȼ", "�����Ǿ���ʶ�ķ��ϣ�֮���һ���$30�ĵ��������㣬�����Ļ����������Ұ�" }; System.MessageHead = { 45,-1,45,-1,45 }; System.TransformingEventName = "ITEM|5|3"; System.DirectlyFunction = true; break;
		case 10: System.MessageName = { "����" }; System.MessageContent = { "���д������Եֵ�һ�����Թ���ĵ�ͼ�˺���" }; System.MessageHead = { 86 }; System.TransformingEventName = "ITEM|12|1"; System.DirectlyFunction = true; break;
		case 11: System.MessageName = { "����", "����" }; System.MessageContent = { "��Ҫ�ִ������ˣ�һ��Ҫ���ģ�������ȫ׼������ȥ", "����\n��˵ǰ���¥��������һ�ֱ�������赲����ӵ�ͼ�϶�����ɵ��˺�" }; System.MessageHead = { 95, 95 }; break;
		case 12: System.MessageName = { "����", "��ڤ��ʦ", "����" }; System.MessageContent = { "������������", "ɱ�������롪�֡��ߡ�", "ħͷ��������" }; System.MessageHead = { -1, 107, -1 }; Exist = false; break;
		case 13: System.MessageName = { "����", "ħ������", "����", "ħ������" }; System.MessageContent = { "�㡭\n��ħ�����죡", "��ѽ�����ò�˵�����Ƕ�λ�ľ����������˸ж�", "����������", "�����ɣ�����ʱ������ɱ������\nǰ������ħ�������ˣ�����������Ļ����������" }; System.MessageHead = { -1, 108, -1, 108 }; System.TransformingEventName = "NPC|14"; System.DirectlyFunction = true; break;
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
			System.MessageName = { "����", "����", "����", "����", "ħ������", "ħ������" };
			System.MessageContent = { "��",
									  "��֡�\n�Ҳ��ǡ�����ô��",
									  "����������", "�������¡�\n����ô����",
									  "��Ǹ���Ŷ�λ��������\n��������������֮��Ϊ����֮Ů��������֮��Ϊ�ȹ�֮������",
									  "��ô��ף��λ����" };
			System.MessageHead = { 106, 106, -1, 106, 108, 108 };
			System.TransformingEventName = "NPC|15";
			System.DirectlyFunction = true;
			break;
		}
		case 15: {
			Exist = false;
			System.GameSwitches[15] = true;
			System.MessageName = { "����", "����", "����", "����", "����", "����", "����", "����", "����", "����", "����", "����", "����", "" };
			System.MessageContent = { "������ô������\n������ô����",
									  "ħ���ƺ����������˸߿գ��ӵ�1�㿪ʼ�𽥱���������ֻ��һ·��������",
									  "�ȵȡ�\n�������ߣ��㲻��������",
									  "һ���Ѿ���\n�в�֪�������Ƿ���Ȼ��ȫ",
									  "����˵�š���Ը������ȥ��ȴ���̾���������ǵĺ�·",
									  "���Ϸ�������������ʱ�ǰ�ȫ��\n��������ħ������ֻʣ����һ����",
									  "������\n������һʱ������벻���ˣ��浹ù��",
									  "���º����ߴ��˴�����ô��",
									  "�Ҿ���Ŀǰֻ��ǰ����",
									  "��Ҳ��ô��Ϊ",
									  "�ðɣ���������������ǣ����������Ҫ�����ſ�����ʱ��������",
									  "��Ҳ�ǣ������ﻹ�кܶ�Կ�ף����ǿ�ǧ������˰�",
									  "���İɣ��ض�ƽ������",
									  "����N�����Դӹ���������֮���л���������" };
			System.MessageHead = { -1, 109, 110, 106, -1, 109, 110, 109, -1, 106, 109, 110, -1, -1 };
			System.TransformingEventName = "NPC|16";
			System.DirectlyFunction = true;
			break;
		}
		case 16: System.Maps[27].MapEvents[106].Exist = false; break;
		case 17: System.MessageName = { "��ɭ����" }; System.MessageContent = { "�ú�ע���ܱߵ�ǽ��Ŷ\n����������" }; System.MessageHead = { 116 }; break;
		case 18: System.MessageName = { "ʧ������", "ʧ������" }; System.MessageContent = { "�����������е��ߣ�������ǿ����ս�Ϳ�ǰ��", "���ˣ���Ҫ�������" }; System.MessageHead = { 104, 104 }; break;
		case 19: System.MessageName = { "����" }; System.MessageContent = { "����������ӭ����\n�պõ��ߴ�Ŷ���ɱ��õ���ֱ�Ӻȵ���" }; System.MessageHead = { 74 }; System.TransformingEventName = "ITEM|15|1"; System.DirectlyFunction = true; break;
		case 20: {
			System.MessageName = { "ħ������", "����", "ħ������", "����", "ħ������" };
			if (Actors[System.GameVariables[1]].Item[12] > 0) {
				System.MessageContent = { "��ѽ��ѽ\n����ȥ�㱻��Щ��ͼ�������ڵúܲ���", "ȷʵ��ˡ�\nʵ���Ƿ���ʤ��", "����һ��ħ��Դʯ�����Լ����ǿ����ķ�������������500����ң��ҾͰ��������㣬������", "�ҿ��ǿ��ǰ�", "��ʱ��ӭ" };
			}
			else {
				System.MessageContent = { "��ѽ��ѽ\n����ȥ�㱻��Щ��ͼ�������ڵúܲ���", "ȷʵ��ˡ�\nʵ���Ƿ���ʤ��", "����һ��ħ��Դʯ�������������͵�ͼ�˺��ķ�������������500����ң��ҾͰ��������㣬������", "�ҿ��ǿ��ǰ�", "��ʱ��ӭ" };
			}
			System.MessageHead = { 89, -1, 89, -1, 89 };
			System.TransformingEventName = "NPC|21";
			break;
		}
		case 21: {
			System.MessageName = { "ħ������" };
			if (Actors[System.GameVariables[1]].Gold >= 500) {
				Actors[System.GameVariables[1]].Gold -= 500;
				System.MessageContent = { "�ɽ��������ǹ������£�����������" };
				System.TransformingEventName = "ITEM|18|1";
				System.DirectlyFunction = true;
			}
			else {
				System.MessageContent = { "��ѽ��ѽ���������£�Ī�����ڻʹ��д����ˣ�����Ǯ�������������" };
			}
			System.MessageHead = { 89 };
			break;
		}
		case 22: System.MessageName = { "����", "����" }; System.MessageContent = { "���ھ�Ȼ������˺���֮��", "��������Դ����\nĪ������ֻʷ��ķ��" }; System.MessageHead = { -1, -1 }; Exist = false; break;
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
		case 24: System.MessageName = { "����" }; System.MessageContent = { "��˵ħ����12����������ı��⣬���������˺ܾö�û�з���" }; System.MessageHead = { 93 }; break;
		case 25: System.MessageName = { "����" }; System.MessageContent = { "ι�����ʲô��\n������˼��Ѽ��˺þõĶ�����" }; System.MessageHead = { 110 }; break;
		case 26: System.MessageName = { "����" }; System.MessageContent = { "ǰ�������ħ���ľ�ͷ�ˡ�\n����С��" }; System.MessageHead = { 93 }; break;
		case 27: System.MessageName = { "����" }; System.MessageContent = { "ǰ�������ħ���ľ�ͷ�ˡ�\n����С��" }; System.MessageHead = { 88 }; break;
		case 28: System.MessageName = { "ħ��Щ��", Actors[System.GameVariables[1]].Name }; System.MessageContent = { "������������\nÿ�ζ������ǻ������ǵĺ��£�", "���ǹ�Ȼ����û��\n���������л����ٸ�����" }; System.MessageHead = { 53, -1 }; Exist = false; break;
		case 29: {
			System.MessageName = { "ħ������", Actors[System.GameVariables[1]].Name, "ħ������", Actors[System.GameVariables[1]].Name, "ħ�������յ�", "ħ��֮�����Ŷ�", "ħ������", Actors[System.GameVariables[1]].Name, "ħ������", Actors[System.GameVariables[1]].Name, "ħ������" };
			System.MessageContent = { "�벻������Ļ�����",
										"�ⲻ����������ģ��һ����������",
										"��ô�����������ѣ�û��ʲô����˵��",
										"��Ȼ���յ��ܸ����һ�Σ��Ǹ���ڶ���Ҳ����Ϊ�棬����˵��һ�θ���ĹŶ���",
										"����",
										"����",
										"Ŷ����Ͳ���֪������Ϊʲô�ܶ�θ�����",
										"��Ϊ���Ǻ��㶼��һ��ͬԴ��Ҳ������ķ����԰�",
										"��������û�뵽���Ȼ�ܿ�������һ��",
										"�л�����Ϊֹ��",
										"�ţ���Ҳ����ô���\n�����������������������㣬����û��Ҫ��" };
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
			System.MessageName = { "����", Actors[System.GameVariables[1]].Name, "����", Actors[System.GameVariables[1]].Name, "����", "����", "����", "����", Actors[System.GameVariables[1]].Name, "����", "����", Actors[System.GameVariables[1]].Name, "����" };
			System.MessageContent = { "����񲢲�����",
										"ͬ��ħ�������������а�������ĵ����ӵ�һ�ο�ʼ���Ǿ��ڻ�������",
										"û�뵽���Ǿ�Ȼ�ỳ�ɰ��������ǵ���\n��~�����˼Һ����İ�",
										"��ô����˵˵�������������������Ŀ��",
										"Ŷ�����԰�",
										"һ�仰����������Դ��ȱ��ħ���ʳ����������������",
										"����ħ�翿������ɱ�����棬�������ڵ�������Ȼ���������ɱ�ˣ���ֻ����ɱ������",
										"�Ͼ���Ϊ�������������\n��ܹ���������һ������ע��Ļ��Ӱ���",
										"����������ˡ",
										"ιι���㲻�ỹ����Ҵ�ɣ��ҿ���ħ�����찥��ħ����ס���",
										"�ҵ����������ֻ�������Ҳ����˵�����ǲ�����",
										"�ǲ��ǲ������ǿɲ���˵\n����㸴��Ļ�����ֻҪ��ɱ����Ϳ�����",
										"��ѽѽ��������̵ĺ���" };
			System.MessageHead = { 31, -1, 31, -1, 31, 31, 31, 31, -1, 31, 31, -1, 31 };
			Exist = false;
			break;
		}
		case 31: {
			System.MessageName = { "����" };
			System.MessageContent = { "�ⲻ���ܡ���" };
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
			System.MessageName = { Actors[!System.GameVariables[1]].Name, "����", Actors[!System.GameVariables[1]].Name, Actors[System.GameVariables[1]].Name, Actors[!System.GameVariables[1]].Name, Actors[!System.GameVariables[1]].Name, "����", "����", Actors[!System.GameVariables[1]].Name, "����", "����" };
			System.MessageContent = { "ûʲô�����ܵ�", 
				"��ô�ᡭ\n��������", 
				"��Ҫմ��ͬ����Ѫ���ܴ򿪵ĵ�·������˵����ֱЦ�����ˣ��ǲ������������˴򿪿��صĵ�·��", 
				"�������������Ķ�����Ϊʲô�������������������",
				"�㲻����Ϊ������������˰ɣ�������ȻҲ�������㿴��",
				"��ֻ��Ҫһ���������Ǿ��ܴ�ɹ�ʶ�����Ƕ��뿪֮���Ҿ���취�ص��������Ķ��㣬������˵�������", 
				"�������ٴ�����֮���Ҿ�һֱ���о���������ص����棬�������ճɹ���",
				"�ҳ�ȥ��̽�������û����������ħ�����һ��ɢɳ���Ѿ�������������ѹ��",
				"��������һ���㳹��ʧ������\n���ң���·����",
				"�����Ժ�ħ��һ�����ٴδ�����\nֻҪ�������������Ȼ���ڣ�ħ����ǲ���ģ�",
				"��ʱ�����ǻ������赲�����𣿣����ǻ������赲�����𣿣�"};
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
		string content = "��á�";
		switch (kind) {
		case 1: Actors[System.GameVariables[1]].Atk += val; content += "�챦ʯ����������+" + to_string(val); break;
		case 2: Actors[System.GameVariables[1]].Def += val; content += "����ʯ����������+" + to_string(val); break;
		case 3: Actors[System.GameVariables[1]].Mdef += val; content += "�̱�ʯ����ħ��+" + to_string(val); break;
		case 4: Actors[System.GameVariables[1]].Level += val; Actors[System.GameVariables[1]].Hp += 250 * val; Actors[System.GameVariables[1]].Atk += 3 * val; Actors[System.GameVariables[1]].Def += 3 * val; Actors[System.GameVariables[1]].BreathLimit += 6 * val; content += "Ծ��֮�����ȼ�+" + to_string(val); break;
		case 5: System.GameVariables[14] = 2; Actors[System.GameVariables[1]].Atk += val; Actors[System.GameVariables[1]].Mdef += 1; content += "������ħ��+1��������+" + to_string(val); break;
		case 6: Actors[System.GameVariables[1]].Def += val; Actors[System.GameVariables[1]].Mdef += 1; content += "���Ρ���ħ��+1��������+" + to_string(val); break;
		case 7: Actors[System.GameVariables[1]].Exp += val; content += "����ҩˮ��������+" + to_string(val); break;
		case 8: Actors[System.GameVariables[1]].Gold += val; content += "���ҡ������+" + to_string(val); break;
		case 9: Actors[System.GameVariables[1]].BreathLimit -= val; Actors[System.GameVariables[1]].Breath = min(Actors[System.GameVariables[1]].Breath, Actors[System.GameVariables[1]].BreathLimit - 1); content += "��Ϣҩˮ������Ϣ���޼���" + to_string(val); break;
		case 10: Actors[System.GameVariables[1]].Item[0] += val; Actors[System.GameVariables[1]].Item[1] += val; Actors[System.GameVariables[1]].Item[2] += val; content += "Կ�׺С�����Կ��+" + to_string(val); break;
		case 11: Actors[System.GameVariables[1]].Breath = min(Actors[System.GameVariables[1]].BreathLimit - 1, Actors[System.GameVariables[1]].Breath + Actors[System.GameVariables[1]].BreathLimit / 6); content += "���֮�𡹣���Ϣ����1��"; break;
		case 12: if (Actors[System.GameVariables[1]].Status == 1) Actors[System.GameVariables[1]].Status = 0; content += "�ⶾ����������ж�״̬"; break;
		case 13: if (Actors[System.GameVariables[1]].Status == 2) { Actors[System.GameVariables[1]].Status = 0; System.GameVariables[5] = 0; } content += "��ơ������˥��״̬"; break;
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
			System.MessageContent.push_back("��á���ҩ��������+" + to_string(val));
			System.MessageHead.push_back(-1);
		}
		Exist = false;
		return;
	}
	if (name[0] == "ITEM") {
		PlaySE(System.GetSE);
		kind << name[1];
		val << name[2];
		string content = "��á�";
		content += Item[kind].Name + "��";
		if (val != 1) {
			content += "��" + to_string(val);
		}
		content += "��";
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
		name = "�ж�";
		description = "����Ĺ����и��ʸ����ж�״̬";
		break;
	case 2:
		name = "˥��";
		description = "����Ĺ����и��ʸ���˥��״̬";
		break;
	case 3:
		name = "��Ѫ";
		description = "��������˺����ָ��˺�ֵ" + Split(Name, "|")[1] + "%������";
		break;
	case 4:
		name = "���";
		description = "����ķ��������ڼ�������-1";
		break;
	case 5:
		name = "�ȹ�";
		description = "ս����ʼʱ�������ȹ���";
		break;
	case 6:
		name = "ħ��";
		description = "ս��ʱ������Ĺ������Ӽ����ķ���";
		break;
	case 7:
		name = to_string(Conatk) + "����";
		description = "����ÿ�غϽ���" + to_string(Conatk) + "�ι���";
		break;
	case 8:
		name = "����";
		description = "ս���󣬹��������Ϊ��һ���";
		break;
	case 9:
		name = "ճҺ";
		description = "ս��ʱ�������ÿ�ι��������Ӽ���" + Split(Name, "|")[1] + "��ƣ��";
		break;
	case 10:
		name = "��ɱ";
		description = "���ﱩ���˺�����ͨ�˺���3��";
		break;
	case 11:
		name = "��ħ";
		description = "��������ħ�����ˣ���ħ���������˺�����";
		break;
	case 12:
		name = "����";
		description = "���﹥���и��ʽ����ҷ�" + Split(Name, "|")[1] + "��ħ�����������0��";
		break;
	case 13:
		name = "����";
		description = "����ҷ����������ڹ��﹥��������˺��ӱ�";
		break;
	case 14:
		name = "����";
		description = "����һ�����5���˺�������ʧ��ǰһ������";
		break;
	case 15:
		name = "����";
		description = "����ͬ���л��ܵ�����������ս��ʱ��������";
		break;
	case 16:
		name = "����";
		description = "���������ʱ���ܵ�" + to_string(Atk / 2) + "���˺�";
		break;
	case 17:
		name = "а��";
		description = "�ù�����ʱ�޷�¥�㴫��";
		break;
	case 18:
		name = "��˪";
		description = "�и����ü���������" + Split(Name, "|")[1] + "�غ����޷�������һ��\nս�����ഥ��һ��";
		break;
	case 19:
		name = "�л�";
		description = "�����������м�ʱ���ܵ����߹�ͬ����";
		break;
	case 20:
		name = "����";
		description = "�������������ҷ���Ϣ���ұ���������ҷ�\n2����Ϣ��������" + Split(Name, "|")[1] + "��ƣ��";
		break;
	case 21:
		name = "����";
		description = "�������һ������·��";
		break;
	case 22:
		name = "����";
		description = "������һ�������������������ȥ��";
		break;
	case 23:
		name = "����";
		description = "ÿ�ι�������һ�ε��˺��ᷭ��";
		break;
	case 24:
		name = "����";
		description = "������Χ��ͨ�е�9���������·��";
		break;
	case 25:
		name = "����";
		description = "����Ϣ������Ϣʱ�����ܵ��˺�";
		break;
	case 26:
		name = "Ѫū";
		description = "���ҷ���һ��������Ϣ���������һ���õз�����һ��";
		break;
	case 27:
		name = "�Ƽ�";
		description = "�����ҷ�һ�����";
		break;
	case 28:
		name = "ѩ��";
		description = "������Χ��ͨ��9����ɱ�";
		break;
	case 29:
		name = "����";
		description = "�����и��ʽ����ҷ�" + Split(Name, "|")[1] + "�㹥��";
		break;
	case 30:
		name = "�Ͷ�";
		description = "�����и��ʸ��Ӷ��������ж��Ķ������ǿ" + Split(Name, "|")[1] + "�㹥��";
		break;
	case 31:
		name = "����";
		description = "��Ϣ����ʱ������һ���������غϽ���";
		break;
	case 32:
		name = "ʥ��";
		description = "����һ�����6���˺�";
		break;
	case 33:
		name = "Ϸ��";
		description = "����ʱ�������ͷ����и��ʷ�ת";
		break;
	case 34:
		name = "�ֻ�";
		description = "һ��9������,ÿ������������10%������\n��30%������,�������ƣ��,��ȡ�ҷ�һ����Ϣ";
		break;
	default:
		name = "��ͨ";
		description = "û������Ч��";
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
	case 1: status = "�� ��"; break;
	case 2: status = "˥ ��"; break;
	default: status = "�� ��"; break;
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
	case 0: towername = "����"; break;
	case 1: towername = "����"; break;
	case 2: towername = "����"; break;
	case 3: towername = "ħ��"; break;
	case 4: towername = "ħ��"; break;
	case 5: towername = "����"; break;
	case 6: towername = "����"; break;
	case 7: towername = "ħ��"; break;
	}
	if (StringInclude(System.Maps[Actors[System.GameVariables[1]].MapID].MapName, ":")) {
		DrawTexts(356, 0, 32, 32, towername, 1);
		DrawTexts(404, 0, 40, 32, to_string(System.GameVariables[2]) + " ��", 1);
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
		DrawTexts(128, 416, 64, 32, "��" + to_string(Actors[System.GameVariables[1]].Item[5]));
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
