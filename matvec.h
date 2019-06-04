#pragma once
#include <vector>

struct vector3D
{
	vector3D() = default;
	vector3D(float x_in, float y_in, float z_in) : x(x_in), y(y_in), z(z_in) {};
	float x, y, z;
};

struct vector2D
{
	vector2D() = default;
	vector2D(float x_in, float y_in) : x(x_in), y(y_in) {};
	float x, y;
	operator vector3D() { return{ x, y, 0 }; }
};

struct triangle
{
	triangle() = default;
	triangle(vector3D vert0, vector3D vert1, vector3D vert2) { points[0] = vert0; points[1] = vert1; points[2] = vert2; };
	vector3D points[3];
	float color;
};

struct mesh
{
	mesh() = default;
	std::vector<triangle> tris;
};

struct mat4x4
{
	float m[4][4] = { 0 };
};
vector3D MultiplyMatrixVector(vector3D &i, mat4x4 &m)
{
	vector3D o;

	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f) //ciê¿ko dostac 0.f z obliczeñ tbh
	{
		o.x /= w; o.y /= w; o.z /= w;
	}

	return o;
}

mat4x4 Mat_T_Fast(mat4x4 &m)
{
	mat4x4 matrix;
	matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
	matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
	matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
	matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
	matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
	matrix.m[3][3] = 1.0f;
	return matrix;
}

mat4x4 Mat_Rot_X(float kat)
{
	mat4x4 matObX;

	matObX.m[0][0] = 1;
	matObX.m[1][1] = cosf(kat * 0.5f);
	matObX.m[1][2] = sinf(kat * 0.5f);
	matObX.m[2][1] = -sinf(kat * 0.5f);
	matObX.m[2][2] = cosf(kat * 0.5f);
	matObX.m[3][3] = 1;

	return matObX;
}

mat4x4 Mat_Rot_Y(float kat)
{
	mat4x4 matObY;
	matObY.m[0][0] = cosf(kat);
	matObY.m[0][2] = sinf(kat);
	matObY.m[2][0] = -sinf(kat);
	matObY.m[1][1] = 1.0f;
	matObY.m[2][2] = cosf(kat);
	matObY.m[3][3] = 1.0f;
	return matObY;
}

mat4x4 Mat_Rot_Z(float kat)
{
	mat4x4 matObZ;

	matObZ.m[0][0] = cosf(kat);
	matObZ.m[0][1] = sinf(kat);
	matObZ.m[1][0] = -sinf(kat);
	matObZ.m[1][1] = cosf(kat);
	matObZ.m[2][2] = 1.0f;
	matObZ.m[3][3] = 1.0f;

	return matObZ;
}

mat4x4 Mat_Proj_Create(float fNear, float fFar, float fFov, float scrnh, float scrnw, float fFovRad)
{
	mat4x4 matProj;

	float fAspectRatio = scrnh / scrnw;


	matProj.m[0][0] = fAspectRatio * fFovRad;
	matProj.m[1][1] = fFovRad;
	matProj.m[2][2] = fFar / (fFar - fNear);
	matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matProj.m[2][3] = 1.0f;
	matProj.m[3][3] = 0.0f;

	return matProj;
}

mat4x4 Mat_Mul_Mat(mat4x4 mat1, mat4x4 mat2)
{
	mat4x4 mul;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			mul.m[j][i] = mat1.m[j][0] * mat2.m[0][i] + mat1.m[j][1] * mat2.m[1][i] + mat1.m[j][2] * mat2.m[2][i] + mat1.m[j][3] * mat2.m[3][i];

	return mul;
}

vector3D Vector_Add(vector3D &v1, vector3D &v2)
{
	return{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

vector3D Vector_Sub(vector3D &v1, vector3D &v2)
{
	return{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

vector3D Vector_Mul(vector3D &v1, float k)
{
	return{ v1.x * k, v1.y * k, v1.z * k };
}

vector3D Vector_Div(vector3D &v1, float k)
{
	return{ v1.x / k, v1.y / k, v1.z / k };
}

float Vector_DotProd(vector3D &v1, vector3D &v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z * v2.z;
}

float Vector_Len(vector3D &v)
{
	return sqrtf(Vector_DotProd(v, v));
}

vector3D Vector_Normalise(vector3D &v)
{
	float l = Vector_Len(v);
	return{ v.x / l, v.y / l, v.z / l };
}

vector3D Vector_VecProd(vector3D &v1, vector3D &v2)
{
	vector3D v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;

	return v;
}

mat4x4 Camera_LookAt(vector3D &pos, vector3D &target, vector3D &up)
{
	vector3D newForward = Vector_Sub(target, pos);
	newForward = Vector_Normalise(newForward);

	vector3D a = Vector_Mul(newForward, Vector_DotProd(up, newForward));
	vector3D newUp = Vector_Sub(up, a);
	newUp = Vector_Normalise(newUp);

	vector3D newRight = Vector_VecProd(newUp, newForward);

	mat4x4 matrix;
	matrix.m[0][0] = newRight.x;	matrix.m[0][1] = newRight.y;	matrix.m[0][2] = newRight.z;	matrix.m[0][3] = 0.0f;
	matrix.m[1][0] = newUp.x;		matrix.m[1][1] = newUp.y;		matrix.m[1][2] = newUp.z;		matrix.m[1][3] = 0.0f;
	matrix.m[2][0] = newForward.x;	matrix.m[2][1] = newForward.y;	matrix.m[2][2] = newForward.z;	matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = pos.x;			matrix.m[3][1] = pos.y;			matrix.m[3][2] = pos.z;			matrix.m[3][3] = 1.0f;
	return matrix;

}