#include<graphics.h>
#include<string>
#include<iostream>


IMAGE img_player_left, img_player_right;
IMAGE* img_player = &img_player_left;//ʵ��չʾ�����ͼƬ
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
	initgraph(1280, 720);//��ʼ��һ��1280x720�Ĵ���

	ExMessage msg;

	IMAGE img_background;
	loadimage(&img_background, _T("image/background.jpg"), 1280, 720);//����ͼƬ
	
	loadPlayerImg();
	
	//��ҵ��˶�״̬
	bool moveUp = false, moveDown = false, moveLeft = false, moveRight = false;

	bool running = true;//�����Ƿ����е�boolֵ��Ĭ��Ϊtrue

	BeginBatchDraw();	
	while (running)
	{
		DWORD beginTime = GetTickCount();	
		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN)//������������˶�״̬
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

		

		//��������˶�״̬ȷ�����λ��
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
			

		//��ͼ��
		cleardevice();
		putimage(0, 0, &img_background);
		putimage_alpha(playerPos.x, playerPos.y, img_player);//putimage_alpha������
		FlushBatchDraw();

		//����һ֡��ʣ��ʱ�䣬��sleep
		DWORD endTime = GetTickCount();
		DWORD deltaTime = endTime - beginTime;
		if (deltaTime < 1000 / 60)
			Sleep(100 / 6 - deltaTime);
	}

	EndBatchDraw();


	return 0;
}