#pragma once

LPSTR mainWindowClassName = "Main Window";
MSG message;
int x = -1;
int y = -1;

int opcja = 0;
float elapsed = 0;
mesh meshCube;
mat4x4 matObX, matObZ, matProj;
vector3D vCamera, vLookAt;
float obrotXZ;

float fTheta;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
int Draw_Line_Add(int, int, int, int, HDC);
int Draw_Line_Bresenham(int, int, int, int, HDC);
int Draw_Line_(int, int, int, int, HDC);
int DrawTriangle(int, int, int, int, int, int, HDC);
void FillTriangle(int, int, int, int, int, int, HDC, COLORREF);
float Side_Of_Line(int, int, int, int, int, int);
bool PointInTriangle(int, int, int, int, int, int, int, int);