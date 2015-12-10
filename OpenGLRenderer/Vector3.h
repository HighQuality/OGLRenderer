#pragma once

struct Vector2
{
	float X;
	float Y;

	Vector2()
	{
		X = 0;
		Y = 0;
	}

	Vector2(float x, float y)
	{
		X = x;
		Y = y;
	}
};

struct Vector3
{
	float X;
	float Y;
	float Z;

	Vector3()
	{
		X = 0;
		Y = 0;
		Z = 0;
	}

	Vector3(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}
};

struct Vector4
{
	float X;
	float Y;
	float Z;
	float W;

	Vector4()
	{
		X = 0;
		Y = 0;
		Z = 0;
		W = 0;
	}

	Vector4(float x, float y, float z, float w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}
};
