#include<graphics.h>
#include<string>
#include<iostream>


IMAGE img_player_left, img_player_right;
IMAGE* img_player = &img_player_left;//实际展示的玩家图片
void loadPlayerImg()
{
	loadimage(&img_player_left, _T("image/jinxi_left.png"), 120, 80);
	loadimage(&img_player_right, _T("image/jinxi_right.png"), 120, 80);
}

POINT playerPos = { 500,500 };
int playerSpeed = 5;

#pragma comment(lib, "MSIMG32.LIB")

inline void putimage_alpha(int x, int y , IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
	
int main()
{
	initgraph(1280, 720);//初始化一个1280x720的窗口

	ExMessage msg;

	IMAGE img_background;
	loadimage(&img_background, _T("image/background.jpg"), 1280, 720);//背景图片
	
	loadPlayerImg();
	
	//玩家的运动状态
	bool moveUp = false, moveDown = false, moveLeft = false, moveRight = false;

	bool running = true;//控制是否运行的bool值，默认为true

	BeginBatchDraw();	
	while (running)
	{
		DWORD beginTime = GetTickCount();	
		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN)//按键控制玩家运动状态
			{
				switch (msg.vkcode)
				{
				case VK_UP:
					moveUp = true;
					break;
				case VK_DOWN:
					moveDown = true;
					break;
				case VK_LEFT:
					moveLeft = true;
					break;
				case VK_RIGHT:
					moveRight = true;
					break;		
				}
			}
			else if (msg.message = WM_KEYUP)
			{
				switch (msg.vkcode)
				{
				case VK_UP:
					moveUp = false;
					break;
				case VK_DOWN:
					moveDown = false;
					break;
				case VK_LEFT:
					moveLeft = false;
					break;
				case VK_RIGHT:
					moveRight = false;
					break;
				}
			}
		}

		

		//根据玩家运动状态确定玩家位置
		if (moveUp)playerPos.y -= playerSpeed;
		if (moveDown)playerPos.y += playerSpeed;
		if (moveLeft)
		{
			playerPos.x -= playerSpeed;
			img_player = &img_player_left;
		}
		if (moveRight)
		{
			playerPos.x += playerSpeed;
			img_player = &img_player_right;
		}
			

		//绘图区
		cleardevice();
		putimage(0, 0, &img_background);
		putimage_alpha(playerPos.x, playerPos.y, img_player);//putimage_alpha不可用
		FlushBatchDraw();

		//计算一帧的剩余时间，并sleep
		DWORD endTime = GetTickCount();
		DWORD deltaTime = endTime - beginTime;
		if (deltaTime < 1000 / 60)
			Sleep(100 / 6 - deltaTime);
	}

	EndBatchDraw();


	return 0;
}