#define _USE_MATH_DEFINES

#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "matvec.h"
#include "main.h"

#define SCREENHEIGHT 800
#define SCREENWIDTH 800

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = mainWindowClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Rejestracja okna nie powiodła się", "Cudowny Windows",
			MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}

	HWND hwnd;

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, mainWindowClassName, "GraphicsUnit", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, SCREENHEIGHT, SCREENWIDTH, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Okno odmówiło przyjęcia na świat!", "Ale kicha...", MB_ICONEXCLAMATION);
		return 1;
	}
	meshCube.tris = {

			// SOUTH1
			{ {0.0f, 0.0f, 0.0f},   {0.0f, 1.0f, 0.0f},   {1.0f, 1.0f, 0.0f} },
			{ {0.0f, 0.0f, 0.0f},   {1.0f, 1.0f, 0.0f},   {1.0f, 0.0f, 0.0f} },

			// EAST1                                                      
			{ {1.0f, 0.0f, 0.0f},   {1.0f, 1.0f, 0.0f},   {1.0f, 1.0f, 1.0f} },
			{ {1.0f, 0.0f, 0.0f},   {1.0f, 1.0f, 1.0f},   {1.0f, 0.0f, 1.0f} },

			// NORTH1                                                    
			{ {1.0f, 0.0f, 1.0f},   {1.0f, 1.0f, 1.0f},   {0.0f, 1.0f, 1.0f} },
			{ {1.0f, 0.0f, 1.0f},   {0.0f, 1.0f, 1.0f},   {0.0f, 0.0f, 1.0f} },

			// WEST1                                                      
			{ {0.0f, 0.0f, 1.0f},   {0.0f, 1.0f, 1.0f},   {0.0f, 1.0f, 0.0f} },
			{ {0.0f, 0.0f, 1.0f},   {0.0f, 1.0f, 0.0f},   {0.0f, 0.0f, 0.0f} },

			// TOP1                                                       
			{ {0.0f, 1.0f, 0.0f},   {0.0f, 1.0f, 1.0f},   {1.0f, 1.0f, 1.0f} },
			{ {0.0f, 1.0f, 0.0f},   {1.0f, 1.0f, 1.0f},   {1.0f, 1.0f, 0.0f} },

			// BOTTOM1                                                    
			{ {1.0f, 0.0f, 1.0f},   {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f, 0.0f} },
			{ {1.0f, 0.0f, 1.0f},   {0.0f, 0.0f, 0.0f},   {1.0f, 0.0f, 0.0f} },

			// SOUTH2
			{ { 3.0f, 3.0f, 3.0f },{ 3.0f, 4.0f, 3.0f },{ 4.0f, 4.0f, 3.0f } },
			{ { 3.0f, 3.0f, 3.0f },{ 4.0f, 4.0f, 3.0f },{ 4.0f, 3.0f, 3.0f } },

			// EAST2                                                      
			{ { 4.0f, 3.0f, 3.0f },{ 4.0f, 4.0f, 3.0f },{ 4.0f, 4.0f, 4.0f } },
			{ { 4.0f, 3.0f, 3.0f },{ 4.0f, 4.0f, 4.0f },{ 4.0f, 3.0f, 4.0f } },

			// NORTH2                                                     
			{ { 4.0f, 3.0f, 4.0f },{ 4.0f, 4.0f, 4.0f },{ 3.0f, 4.0f, 4.0f } },
			{ { 4.0f, 3.0f, 4.0f },{ 3.0f, 4.0f, 4.0f },{ 3.0f, 3.0f, 4.0f } },

			// WEST2                                                      
			{ { 3.0f, 3.0f, 4.0f },{ 3.0f, 4.0f, 4.0f },{ 3.0f, 4.0f, 3.0f } },
			{ { 3.0f, 3.0f, 4.0f },{ 3.0f, 4.0f, 3.0f },{ 3.0f, 3.0f, 3.0f } },

			// TOP2                                                       
			{ { 3.0f, 4.0f, 3.0f },{ 3.0f, 4.0f, 4.0f },{ 4.0f, 4.0f, 4.0f } },
			{ { 3.0f, 4.0f, 3.0f },{ 4.0f, 4.0f, 4.0f },{ 4.0f, 4.0f, 3.0f } },

			// BOTTOM2                                                    
			{ { 4.0f, 3.0f, 4.0f },{ 3.0f, 3.0f, 4.0f },{ 3.0f, 3.0f, 3.0f } },
			{ { 4.0f, 3.0f, 4.0f },{ 3.0f, 3.0f, 3.0f },{ 4.0f, 3.0f, 3.0f } },

			// SOUTH3
			{ { -4.0f, -4.0f, -4.0f },{ -4.0f, -3.0f, -4.0f },{ -3.0f, -3.0f, -4.0f } },
			{ { -4.0f, -4.0f, -4.0f },{ -3.0f, -3.0f, -4.0f },{ -3.0f, -4.0f, -4.0f } },

			// EAST3                                                     
			{ { -3.0f, -4.0f, -4.0f },{ -3.0f, -3.0f, -4.0f },{ -3.0f, -3.0f, -3.0f } },
			{ { -3.0f, -4.0f, -4.0f },{ -3.0f, -3.0f, -3.0f },{ -3.0f, -4.0f, -3.0f } },

			// NORTH3                                                    
			{ { -3.0f, -4.0f, -3.0f },{ -3.0f, -3.0f, -3.0f },{ -4.0f, -3.0f, -3.0f } },
			{ { -3.0f, -4.0f, -3.0f },{ -4.0f, -3.0f, -3.0f },{ -4.0f, -4.0f, -3.0f } },

			// WEST3                                                     
			{ { -4.0f, -4.0f, -3.0f },{ -4.0f, -3.0f, -3.0f },{ -4.0f, -3.0f, -4.0f } },
			{ { -4.0f, -4.0f, -3.0f },{ -4.0f, -3.0f, -4.0f },{ -4.0f, -4.0f, -4.0f } },

			// TOP3                                                      
			{ { -4.0f, -3.0f, -4.0f },{ -4.0f, -3.0f, -3.0f },{ -3.0f, -3.0f, -3.0f } },
			{ { -4.0f, -3.0f, -4.0f },{ -3.0f, -3.0f, -3.0f },{ -3.0f, -3.0f, -4.0f } },

			// BOTTOM3                                                    
			{ { -3.0f, -4.0f, -3.0f },{ -4.0f, -4.0f, -3.0f },{ -4.0f, -4.0f, -4.0f } },
			{ { -3.0f, -4.0f, -3.0f },{ -4.0f, -4.0f, -4.0f },{ -3.0f, -4.0f, -4.0f } },

		};

		vCamera.x = 0.0f;
		vCamera.y = 0.0f;
		vCamera.x = 0.0f;

		float fNear = 0.1f;
		float fFar = 1000.0f;
		float fFov = 90.0f;
		float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * (float)M_PI);

		matProj = Mat_Proj_Create(fNear, fFar, fFov, SCREENHEIGHT, SCREENHEIGHT, fFovRad);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return (int)message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//time_t stop;
	HDC hdcBufor;
	HBITMAP hbmbuf, hbmOldbuf;
	HDC canvas = GetDC(hwnd);
	mat4x4 matWiev, matCam, obrotCam;
	vector3D vLookStart, vUp;
	vector3D vPrzod = Vector_Mul(vLookAt, 3.0f);
	vector<triangle> vecTriToDraw;
	HBRUSH hBr;
	switch (msg)
	{
	case WM_PAINT:
		RECT rect;
		SetRect(&rect, 0, 0, SCREENWIDTH, SCREENHEIGHT);
		hdcBufor = CreateCompatibleDC(canvas);                                      
		hbmbuf = CreateCompatibleBitmap(canvas, SCREENWIDTH, SCREENHEIGHT);			
		hbmOldbuf = (HBITMAP)SelectObject(hdcBufor, hbmbuf);						
		hBr = CreateSolidBrush(RGB(100, 100, 100));									
		FillRect(hdcBufor, &rect, hBr);

		elapsed = 0.1f;
		fTheta = 45.0f;

		matObZ = Mat_Rot_Y(fTheta);

		matObX = Mat_Rot_X(fTheta);

		vUp = { 0,1,0 };
		vLookStart = { 0,0,1 };
		obrotCam = Mat_Rot_Y(obrotXZ);

		vLookAt = MultiplyMatrixVector(vLookStart, obrotCam);
		vLookStart = Vector_Add(vCamera, vLookAt);

		matCam = Camera_LookAt(vCamera, vLookStart, vUp);
		matWiev = Mat_T_Fast(matCam);

		// Draw Triangles
		for (auto tri : meshCube.tris)
		{
			triangle triProjected, triTranslated, triRotatedY, triRotatedYX, triView;

			triRotatedY.points[0] = MultiplyMatrixVector(tri.points[0], matObZ);
			triRotatedY.points[1] = MultiplyMatrixVector(tri.points[1], matObZ);
			triRotatedY.points[2] = MultiplyMatrixVector(tri.points[2], matObZ);

			triRotatedYX.points[0] = MultiplyMatrixVector(triRotatedY.points[0], matObX);
			triRotatedYX.points[1] = MultiplyMatrixVector(triRotatedY.points[1], matObX);
			triRotatedYX.points[2] = MultiplyMatrixVector(triRotatedY.points[2], matObX);

			triTranslated = triRotatedYX;
			triTranslated.points[0].z = triRotatedYX.points[0].z + 10.0f;
			triTranslated.points[1].z = triRotatedYX.points[1].z + 10.0f;
			triTranslated.points[2].z = triRotatedYX.points[2].z + 10.0f;

			vector3D normal, line1, line2;

			line1 = Vector_Sub(triTranslated.points[1], triTranslated.points[0]);
			line2 = Vector_Sub(triTranslated.points[2], triTranslated.points[0]);

			normal = Vector_VecProd(line1, line2);

			normal = Vector_Normalise(normal);

			vector3D RayCast = Vector_Sub(triTranslated.points[0], vCamera);

			if (Vector_DotProd(RayCast, normal) < 0.0f)
			{
				vector3D light_direction = { 0.0f, 0.0f, -1.0f };
				light_direction = Vector_Normalise(light_direction);

				float dp = Vector_DotProd(normal, light_direction);
				triView.points[0] = MultiplyMatrixVector(triTranslated.points[0], matWiev);
				triView.points[1] = MultiplyMatrixVector(triTranslated.points[1], matWiev);
				triView.points[2] = MultiplyMatrixVector(triTranslated.points[2], matWiev);

				triProjected.points[0] = MultiplyMatrixVector(triView.points[0], matProj);
				triProjected.points[1] = MultiplyMatrixVector(triView.points[1], matProj);
				triProjected.points[2] = MultiplyMatrixVector(triView.points[2],  matProj);

				vector3D offset = { 1,1,0 };
				triProjected.points[0] = Vector_Add(triProjected.points[0], offset);
				triProjected.points[1] = Vector_Add(triProjected.points[1], offset);
				triProjected.points[2] = Vector_Add(triProjected.points[2], offset);

				triProjected.points[0].x *= 0.5f * (float)SCREENWIDTH;
				triProjected.points[0].y *= 0.5f * (float)SCREENHEIGHT;
				triProjected.points[1].x *= 0.5f * (float)SCREENWIDTH;
				triProjected.points[1].y *= 0.5f * (float)SCREENHEIGHT;
				triProjected.points[2].x *= 0.5f * (float)SCREENWIDTH;
				triProjected.points[2].y *= 0.5f * (float)SCREENHEIGHT;

				triProjected.color = dp;

				vecTriToDraw.push_back(triProjected);
				vecTriToDraw.shrink_to_fit();
			}
		}

		sort(vecTriToDraw.begin(), vecTriToDraw.end(), [](triangle &t1, triangle &t2)
		{
			float z1 = (t1.points[0].z + t1.points[1].z + t1.points[2].z) / 3.0f;
			float z2 = (t2.points[0].z + t2.points[1].z + t2.points[2].z) / 3.0f;
			return z1 > z2;
		});

		for (auto &triProjected : vecTriToDraw)
		{

			FillTriangle((int)triProjected.points[0].x, (int)triProjected.points[0].y,
				(int)triProjected.points[1].x, (int)triProjected.points[1].y,
				(int)triProjected.points[2].x, (int)triProjected.points[2].y, hdcBufor, RGB(255*triProjected.color, 0, 0));
		}

		BitBlt(canvas, 0, 0, SCREENWIDTH, SCREENHEIGHT, hdcBufor, 0, 0, SRCCOPY);

		ReleaseDC(hwnd, canvas);
		ReleaseDC(hwnd, hdcBufor);

		//start = clock();
		vecTriToDraw.clear();
		UpdateWindow(hwnd);
		DeleteObject(hbmbuf);             
		DeleteObject(hdcBufor);			  
		DeleteObject(hBr);				  
		DeleteObject(hbmOldbuf);		 
		break;

	case WM_KEYDOWN:
		if (wParam == 0x57) //w
		{
			vCamera = Vector_Add(vCamera, vPrzod);
		}
		if (wParam == 0x53) //s
		{
			vCamera = Vector_Sub(vCamera, vPrzod);
		}
		if (wParam == 0x41) //a
		{
			obrotXZ += 1.0f*0.1f;
		}
		if (wParam == 0x44) //d
		{
			obrotXZ -= 1.0f*0.1f;
		}
		if (wParam == 0x26) //UP
		{
			vCamera.y += 1.0f*0.1f;
		}
		if (wParam == 0x28) //DOWN
		{
			vCamera.y -= 1.0f*0.1f;
		}
		if (wParam == 0x25) //LEFT
		{
			vCamera.x += 1.0f*0.1f;
		}
		if (wParam == 0x27) //RIGHT
		{
			vCamera.x -= 1.0f*0.1f;
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

int Draw_Line_Add(int x1, int y1, int x2, int y2, HDC canvas)
{
	float dy, dx, xrys, yrys, m;

	dy = float(y2 - y1);
	dx = float(x2 - x1);
	if ((int)abs((int)dx) > (int)abs((int)dy))
	{
		m = dy / dx;
		yrys = (float)y1;
		xrys = (float)x1;
		int warunek = x2;
		if (x1 > x2)
		{
			xrys = (float)x2;
			yrys = (float)y2;
			warunek = x1;
		}

		for (; xrys <= warunek; xrys++)
		{
			SetPixel(canvas, (int)xrys, (int)floor(yrys + 0.5f), RGB(0, 0, 0));
			yrys += m;
		}
	}
	else
	{
		m = dx / dy;
		xrys = (float)x1;
		yrys = (float)y1;
		int warunek = y2;
		if (y1 > y2)
		{
			warunek = y1;
			yrys = (float)y2;
			xrys = (float)x2;
		}
		for (; yrys <= warunek; yrys++)
		{
			SetPixel(canvas, (int)floor(xrys + 0.5f), (int)yrys, RGB(0, 0, 0));
			xrys += m;
		}
	}
	return 0;
}

int Draw_Line_Bresenham(int x1, int y1, int x2, int y2, HDC canvas)
{
	int kx, ky, xrys, yrys, dx, dy, e;
	if (x1 > x2)
	{
		kx = -1;
	}
	else
	{
		kx = 1;
	}
	if (y1 > y2)
	{
		ky = -1;
	}
	else
	{
		ky = 1;
	}

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);

	if (dx >= dy)
	{
		e = dx / 2;
		xrys = x1;
		yrys = y1;
		for (int i = 0; i < dx; i++)
		{
			xrys = xrys + kx;
			e = e - dy;
			if (e < 0)
			{
				yrys = yrys + ky;
				e = e + dx;
			}
			SetPixel(canvas, xrys, yrys, RGB(0, 0, 0));
		}
	}
	else
	{
		e = dy / 2;
		xrys = x1;
		yrys = y1;
		for (int i = 0; i < dy; i++)
		{
			yrys = yrys + ky;
			e = e - dx;
			if (e < 0)
			{
				xrys = xrys + kx;
				e = e + dy;
			}
			SetPixel(canvas, xrys, yrys, RGB(0, 0, 0));
		}
	}

	return 0;
}

int Draw_Line_(int x1, int y1, int x2, int y2, HDC canvas)
{
	if (opcja == 0)
	{
		Draw_Line_Add(x1, y1, x2, y2, canvas);
		opcja += 1;
	}
	else
	{
		Draw_Line_Bresenham(x1, y1, x2, y2, canvas);
		opcja -= 1;
	}
	return 0;
}

int DrawTriangle(int p1x, int p1y, int p2x, int p2y, int p3x, int p3y, HDC canvas)
{
	Draw_Line_Add(p1x, p1y, p2x, p2y, canvas);
	Draw_Line_Add(p2x, p2y, p3x, p3y, canvas);
	Draw_Line_Add(p3x, p3y, p1x, p1y, canvas);

	return 0;

}

void FillTriangle(int p1x, int p1y, int p2x, int p2y, int p3x, int p3y, HDC canvas, COLORREF color)
{
	int min_x = min(p1x, min(p2x, p3x));
	int min_y = min(p1y, min(p2y, p3y));
	int max_x = max(p1x, max(p2x, p3x));
	int max_y = max(p1y, max(p2y, p3y));

	for (int i = min_x; i < max_x; i++)
	{
		for (int j = min_y; j < max_y; j++)
		{
			if (PointInTriangle(p1x, p1y, p2x, p2y, p3x, p3y, i, j))
			{
				SetPixel(canvas, i, j, color);
			}
		}
	}

}

float Side_Of_Line(int p1x, int p1y, int p2x, int p2y, int p3x, int p3y)
{
	return float((p1x - p3x) * (p2y - p3y) - (p2x - p3x) * (p1y - p3y));
}

bool PointInTriangle(int p1x, int p1y, int p2x, int p2y, int p3x, int p3y, int pointx, int pointy)
{
	float d1, d2, d3;
	bool has_neg, has_pos;

	d1 = Side_Of_Line(pointx, pointy, p1x, p1y, p2x, p2y);
	d2 = Side_Of_Line(pointx, pointy, p2x, p2y, p3x, p3y);
	d3 = Side_Of_Line(pointx, pointy, p3x, p3y, p1x, p1y);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}

float Side_Of_Line(vector3D& vec1, vector3D& vec2, vector3D& vec3)
{
	return (vec1.x - vec3.x) * (vec2.y - vec3.y) - (vec2.x - vec3.x) * (vec1.y - vec3.y);
}

bool PointInTriangle(triangle& tri, vector2D& vert)
{
	float d1, d2, d3;
	bool has_neg, has_pos;

	d1 = Side_Of_Line((vector3D)vert, tri.points[0], tri.points[1]);
	d2 = Side_Of_Line((vector3D)vert, tri.points[1], tri.points[2]);
	d3 = Side_Of_Line((vector3D)vert, tri.points[2], tri.points[0]);

	has_neg =  signbit(d1) ||  signbit(d2) ||  signbit(d3);
	has_pos = !signbit(d1) || !signbit(d2) || !signbit(d3);

	return !(has_neg && has_pos);
}

void FillTriangle(triangle& tri, HDC canvas, COLORREF color)
{
	                                                                              
	float min_x = (min)( {tri.points[0].x, tri.points[1].x, tri.points[2].x} );   
	float min_y = (min)( {tri.points[0].y, tri.points[1].y, tri.points[2].y} );   
	float max_x = (max)( {tri.points[0].x, tri.points[1].x, tri.points[2].x} );   
	float max_y = (max)( {tri.points[0].y, tri.points[1].y, tri.points[2].y} );   
	                                                                              
	vector2D loopVec = { round(min_x), round(min_y) };

	for (; loopVec.x < max_x; loopVec.x++)
	{
		for (; loopVec.y < max_y; loopVec.y++)
		{
			if (PointInTriangle(tri, loopVec))
			{
				SetPixel(canvas, (int)loopVec.x, (int)loopVec.y, color);
			}
		}
	}

}