#ifndef _MATHS_H
#define _MATHS_H
#include "pch.h"

#pragma pack(push, 1)

struct Rect
{
	f32 x;
	f32 y;
	f32 w;
	f32 h;
    
	Rect MapToRect(const Rect& b) const
	{
		Rect res = {};
		if (b.x > 0)
			res.x = x / b.x;
		if (b.y > 0)
			res.y = x / b.y;
		if (b.w > 0)
			res.w = w / b.w;
		if (b.h > 0)
			res.h = h / b.h;
		return res;
	}
};

struct Vec2
{
	union
	{
        
		f32 data[2];
        
		struct
		{
			f32 x;
			f32 y;
		};
	};
    
	operator bool()
	{
		return (x && y);
	}
    
	Vec2 operator+(const Vec2& b) const
	{
		return { x + b.x, y + b.y };
	}
    
	Vec2 operator-(const Vec2& b) const
	{
		return { x - b.x, y - b.y };
	}
    
	Vec2 operator*(const Vec2& b) const
	{
		return { x * b.x, y * b.y };
	}
    
	Vec2 operator/(const Vec2& b) const
	{
		return { x / b.x, y / b.y };
	}
    
	Vec2& operator+=(const Vec2& b)
	{
		x += b.x;
		y += b.y;
		return *this;
	}
    
	Vec2& operator-=(const Vec2& b)
	{
		x -= b.x;
		y -= b.y;
		return *this;
	}
    
	Vec2& operator/=(const Vec2& b)
	{
		x /= b.x;
		y /= b.y;
		return *this;
	}
    
	Vec2& operator*=(const Vec2& b)
	{
		x *= b.x;
		y *= b.y;
		return *this;
	}
    
	f32 length() const
	{
		return sqrt(x * x + y * y);
	}
    
	f32 distance(const Vec2& b) const
	{
		f32 diffX = x - b.x;
		f32 diffY = y - b.y;
		return sqrt((diffY * diffY) + (diffX * diffX));
	}
    
	bool operator==(const Vec2& b)
	{
		return (x == b.x && y == b.y);
	}
    
	bool operator!=(const Vec2& b)
	{
		return (x != b.x || y != b.y);
	}
};

struct Vec3
{
	union
	{
		f32 data[3];
        
		struct
		{
			f32 x;
			f32 y;
			f32 z;
		};
        
		struct
		{
			f32 r;
			f32 g;
			f32 b;
		};
        
	};
    
	operator bool()
	{
		return (x && y && z);
	}
    
	Vec3 operator+(const Vec3& b) const
	{
		return { x + b.x, y + b.y, z + b.z };
	}
    
	Vec3 operator-(const Vec3& b) const
	{
		return { x - b.x, y - b.y, z - b.z };
	}
    
	Vec3 operator*(const Vec3& b) const
	{
		return { x * b.x, y * b.y, z * b.z };
	}
    
	Vec3 operator/(const Vec3& b) const
	{
		return { x / b.x, y / b.y, z / b.z };
	}
    
	Vec3& operator+=(const Vec3& b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
		return *this;
	}
    
	Vec3& operator-=(const Vec3& b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
		return *this;
	}
    
	Vec3& operator/=(const Vec3& b)
	{
		x /= b.x;
		y /= b.y;
		z /= b.z;
		return *this;
	}
    
	Vec3& operator*=(const Vec3& b)
	{
		x *= b.x;
		y *= b.y;
		z *= b.z;
		return *this;
	}
    
	f32 length() const
	{
		return sqrt(x * x + y * y + z * z);
	}
    
	f32 distance(const Vec3& b) const
	{
		f32 diffX = x - b.x;
		f32 diffY = y - b.y;
		f32 diffZ = z - b.z;
		return sqrt((diffY * diffY) + (diffX * diffX) + (diffZ * diffZ));
	}
    
	bool operator==(const Vec3& b)
	{
		return (x == b.x && y == b.y && z == b.z);
	}
    
	bool operator!=(const Vec3& b)
	{
		return (x != b.x || y != b.y || z != b.z);
	}
    
};

struct Vec4
{
	union
	{
		
		f32 data[4];
		
		struct
		{
			f32 x;
			f32 y;
			f32 z;
			f32 w;
		};
        
		struct
		{
			f32 r;
			f32 g;
			f32 b;
			f32 a;
		};
		
	};
	
	operator bool()
	{
		return (x && y && z && w);
	}
    
	Vec4 operator+(const Vec4& b) const
	{
		return { x + b.x, y + b.y, z + b.z, w + b.w };
	}
    
	Vec4 operator-(const Vec4& b) const
	{
		return { x - b.x, y - b.y, z - b.z, w - b.w };
	}
    
	Vec4 operator*(const Vec4& b) const
	{
		return { x * b.x, y * b.y, z * b.z , w * b.w };
	}
    
	Vec4 operator/(const Vec4& b) const
	{
		return { x / b.x, y / b.y, z / b.z , w / b.w };
	}
    
	Vec4& operator+=(const Vec4& b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
		w += b.w;
		return *this;
	}
    
	Vec4& operator-=(const Vec4& b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
		w -= b.w;
		return *this;
	}
    
	Vec4& operator/=(const Vec4& b)
	{
		x /= b.x;
		y /= b.y;
		z /= b.z;
		w /= b.w;
		return *this;
	}
    
	Vec4& operator*=(const Vec4& b)
	{
		x *= b.x;
		y *= b.y;
		z *= b.z;
		w *= b.w;
		return *this;
	}
    
	f32 length() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}
    
	f32 distance(const Vec4& b) const
	{
		f32 diffX = x - b.x;
		f32 diffY = y - b.y;
		f32 diffZ = z - b.z;
		f32 diffW = w - b.w;
		return sqrt((diffY * diffY) + (diffX * diffX) + (diffZ * diffZ) + (diffW * diffW));
	}
    
	bool operator==(const Vec4& b)
	{
		return (x == b.x && y == b.y && z == b.z && w == b.w);
	}
    
	bool operator!=(const Vec4& b)
	{
		return (x != b.x || y != b.y || z != b.z || w != b.w);
	}
};

struct Mat2
{
	union
	{
		f32 elements[2][2] = {};
	};
    
	Mat2()
	{
	}
    
	Mat2(f32 diagonal)
	{
		elements[0][0] = diagonal; elements[0][1] = 0;
		elements[1][0] = 0; elements[1][1] = diagonal;
	}
    
	Mat2(const f32 _data[2][2])
	{
        elements[0][0] = _data[0][0]; elements[0][1] = _data[0][1];
		elements[1][0] = _data[1][0]; elements[1][1] = _data[1][1];
	}
    
	Mat2 identity()
	{
		return Mat2(1.0f);
	}
    
    Mat2 transpose()
    {
        Mat2 res;
        res.elements[0][0] = elements[0][0];
        res.elements[0][1] = elements[1][0];
        res.elements[1][0] = elements[0][1];
        res.elements[1][1] = elements[1][1];
        return res;
    }
    
    Mat2& transposeSelf()
    {
        Mat2 res = *this;
        elements[0][0] = res.elements[0][0];
        elements[0][1] = res.elements[1][0];
        elements[1][0] = res.elements[0][1];
        elements[1][1] = res.elements[1][1];
        return *this;
    }
    
    Mat2 negateTranspose()
    {
        Mat2 res = *this;
        res.elements[0][0] = elements[1][1];
        res.elements[0][1] = -elements[0][1];
        res.elements[1][0] = -elements[1][0];
        res.elements[1][1] = elements[0][0];
        return res;
    }
    
    Mat2& negateTransposeSelf()
    {
        Mat2 res = *this;
        elements[0][0] = res.elements[1][1];
        elements[0][1] = -res.elements[0][1];
        elements[1][0] = -res.elements[1][0];
        elements[1][1] = res.elements[0][0];
        return *this;
    }
    
    float determinant() const
    {
        return elements[0][0] * elements[1][1] - elements[1][0] * elements[0][1];
    }
    
    void print() const
    {
        printf("%f, %f\n%f, %f\n", elements[0][0], elements[0][1], elements[1][0], elements[1][1]);
    }
    
    Mat2 operator+(float val) const
    {
        Mat2 res = *this;
        res.elements[0][0] += val;
        res.elements[0][1] += val;
        res.elements[1][0] += val;
        res.elements[1][1] += val;
        return res;
    }
    
    Mat2& operator+=(float val)
    {
        elements[0][0] += val;
        elements[0][1] += val;
        elements[1][0] += val;
        elements[1][1] += val;
        return *this;
    }
    
    Mat2 operator-(float val) const
    {
        Mat2 res = *this;
        res.elements[0][0] -= val;
        res.elements[0][1] -= val;
        res.elements[1][0] -= val;
        res.elements[1][1] -= val;
        return res;
    }
    
    Mat2& operator-=(float val)
    {
        elements[0][0] -= val;
        elements[0][1] -= val;
        elements[1][0] -= val;
        elements[1][1] -= val;
        return *this;
    }
    
    Mat2 operator/(float denom) const
    {
        Mat2 res = *this;
        res.elements[0][0] /= denom;
        res.elements[0][1] /= denom;
        res.elements[1][0] /= denom;
        res.elements[1][1] /= denom;
        return res;
    }
    
    Mat2& operator/=(float denom)
    {
        elements[0][0] /= denom;
        elements[0][1] /= denom;
        elements[1][0] /= denom;
        elements[1][1] /= denom;
        return *this;
    }
    
    Mat2 operator*(float times) const
    {
        Mat2 res = *this;
        res.elements[0][0] *= times;
        res.elements[0][1] *= times;
        res.elements[1][0] *= times;
        res.elements[1][1] *= times;
        return res;
    }
    
    Mat2& operator*=(float times)
    {
        elements[0][0] *= times;
        elements[0][1] *= times;
        elements[1][0] *= times;
        elements[1][1] *= times;
        return *this;
    }
    
    Mat2 operator+(const Mat2& b) const
    {
        Mat2 res = *this;
        res.elements[0][0] += b.elements[0][0];
        res.elements[0][1] += b.elements[0][1];
        res.elements[1][0] += b.elements[1][0];
        res.elements[1][1] += b.elements[1][1];
        return res;
    }
    
    Mat2& operator+=(const Mat2& b)
    {
        elements[0][0] += b.elements[0][0];
        elements[0][1] += b.elements[0][1];
        elements[1][0] += b.elements[1][0];
        elements[1][1] += b.elements[1][1];
        return *this;
    }
    
    Mat2 operator-(const Mat2& b) const
    {
        Mat2 res = *this;
        res.elements[0][0] -= b.elements[0][0];
        res.elements[0][1] -= b.elements[0][1];
        res.elements[1][0] -= b.elements[1][0];
        res.elements[1][1] -= b.elements[1][1];
        return res;
    }
    
    Mat2& operator-=(const Mat2& b)
    {
        elements[0][0] -= b.elements[0][0];
        elements[0][1] -= b.elements[0][1];
        elements[1][0] -= b.elements[1][0];
        elements[1][1] -= b.elements[1][1];
        return *this;
    }
    
	Mat2 operator*(const Mat2& b) const
	{
		Mat2 res;
        
        res.elements[0][0] = elements[0][0] * b.elements[0][0] + elements[0][1] * b.elements[1][0];
        res.elements[0][1] = elements[0][0] * b.elements[0][1] + elements[0][1] * b.elements[1][1];
        res.elements[1][0] = elements[1][0] * b.elements[0][0] + elements[1][1] * b.elements[1][0];
        res.elements[1][1] = elements[1][0] * b.elements[0][1] + elements[1][1] * b.elements[1][1];
        
        return res;
	}
    
    Mat2& operator*=(const Mat2& b)
	{
		Mat2 temp = *this;
        
        elements[0][0] = temp.elements[0][0] * b.elements[0][0] + temp.elements[0][1] * b.elements[1][0];
        elements[0][1] = temp.elements[0][0] * b.elements[0][1] + temp.elements[0][1] * b.elements[1][1];
        elements[1][0] = temp.elements[1][0] * b.elements[0][0] + temp.elements[1][1] * b.elements[1][0];
        elements[1][1] = temp.elements[1][0] * b.elements[0][1] + temp.elements[1][1] * b.elements[1][1];
        
        return *this;
	}
    
    Mat2 inverse() const
    {
        Mat2 res = *this;
        res.negateTransposeSelf();
        float d = 1 / determinant();
        res *= d;
        return res;
    }
    
    Mat2& inverseSelf()
    {
        negateTransposeSelf();
        *(this) *= 1/determinant();
        return *this;
    }
    
    
    //TODO:: check if matrix division even works it should
    Mat2 operator/(const Mat2& b) const
    {
        Mat2 res;
        auto bInverse = b.inverse();
        res = *(this) * bInverse;
        return res;
    }
    
    Mat2& operator/=(const Mat2& b)
    {
        auto bInverse = b.inverse();
        *(this) *=  bInverse;
        return *this;
    }
};

//TODO:: Mat3 and 4 needs alot of work
struct Mat3
{
	union
	{
		f32 elements[3][3] = {};
	};
    
	Mat3()
	{
	}
    
	Mat3(f32 diagonal)
	{
		elements[0][0] = diagonal; elements[0][1] = 0; elements[0][2] = 0;
		elements[1][0] = 0; elements[1][1] = diagonal; elements[1][2] = 0;
		elements[2][0] = 0; elements[2][1] = 0; elements[2][2] = diagonal;
	}
    
	Mat3(const f32 _data[3][3])
	{
        elements[0][0] = _data[0][0]; elements[0][1] = _data[0][1]; elements[0][2] = _data[0][2];
        elements[1][0] = _data[1][0]; elements[1][1] = _data[1][1]; elements[1][2] = _data[1][2];
        elements[2][0] = _data[2][0]; elements[2][1] = _data[2][1]; elements[2][2] = _data[2][2];
	}
    
	Mat3 identity()
	{
		return Mat3(1.0f);
	}
    
    Mat3 transpose()
    {
        Mat3 res;
        res.elements[0][0] = elements[0][0]; res.elements[0][1] = elements[1][0]; res.elements[0][2] = elements[1][0];
        res.elements[1][0] = elements[0][1]; res.elements[1][1] = elements[1][1]; res.elements[1][2] = elements[1][0];
        res.elements[2][0] = elements[0][2]; res.elements[2][1] = elements[1][1]; res.elements[2][2] = elements[1][0];
        return res;
    }
    
    Mat3& transposeSelf()
    {
        Mat3 res = *this;
        elements[0][0] = res.elements[0][0]; elements[0][1] = res.elements[1][0]; elements[0][1] = res.elements[1][0];
        elements[1][0] = res.elements[0][1]; elements[1][1] = res.elements[1][1]; elements[1][1] = res.elements[1][0];
        elements[2][0] = res.elements[0][1]; elements[2][1] = res.elements[1][1]; elements[2][1] = res.elements[1][0];
        return *this;
    }
    
    Mat3 negateTranspose()
    {
        Mat3 res = *this;
        res.elements[0][0] =  elements[1][1]; res.elements[0][1] = -elements[0][1]; res.elements[0][2] = -elements[0][1];
        res.elements[1][0] = -elements[1][0]; res.elements[1][1] =  elements[0][0]; res.elements[1][2] = -elements[0][1];
        res.elements[2][0] = -elements[1][0]; res.elements[2][1] =  elements[0][0]; res.elements[2][2] = -elements[0][1];
        return res;
    }
    
    Mat3& negateTransposeSelf()
    {
        Mat3 res = *this;
        elements[0][0] =  res.elements[1][1]; elements[0][1] =  res.elements[0][1]; elements[0][2] = res.elements[0][1];
        elements[1][0] =  res.elements[1][0]; elements[1][1] =  res.elements[0][0]; elements[1][2] = res.elements[0][1];
        elements[2][0] =  res.elements[1][0]; elements[2][1] =  res.elements[0][0]; elements[2][2] = res.elements[0][1];
        return *this;
    }
    
    float determinant() const
    {
        return (elements[0][0]*elements[1][1]*elements[2][2]) + (elements[0][2]*elements[1][0]*elements[2][1]) + (elements[0][1]*elements[2][0]*elements[1][2]) - (elements[0][2]*elements[1][1]*elements[2][0]) - (elements[0][0]*elements[2][1]*elements[1][2]) - (elements[0][1]*elements[1][0]*elements[2][2]);
    }
    
    void print() const
    {
        printf("%f, %f, %f\n%f, %f, %f\n%f, %f, %f\n",
               elements[0][0], elements[0][1], elements[0][2],
               elements[1][0], elements[1][1], elements[1][2],
               elements[2][0], elements[2][1], elements[2][2]
               );
    }
    
    Mat3 operator+(float val) const
    {
        Mat3 res = *this;
        res.elements[0][0] += val; res.elements[0][1] += val; res.elements[0][2] += val;
        res.elements[1][0] += val; res.elements[1][1] += val; res.elements[1][2] += val;
        res.elements[2][0] += val; res.elements[2][1] += val; res.elements[2][2] += val;
        return res;
    }
    
    Mat3& operator+=(float val)
    {
        elements[0][0] += val; elements[0][1] += val; elements[0][2] += val;
        elements[1][0] += val; elements[1][1] += val; elements[1][2] += val;
        elements[2][0] += val; elements[2][1] += val; elements[2][2] += val;
        return *this;
    }
    
    Mat3 operator-(float val) const
    {
        Mat3 res = *this;
        res.elements[0][0] -= val; res.elements[0][1] -= val; res.elements[0][2] -= val;
        res.elements[1][0] -= val; res.elements[1][1] -= val; res.elements[1][2] -= val;
        res.elements[2][0] -= val; res.elements[2][1] -= val; res.elements[2][2] -= val;
        return res;
    }
    
    Mat3& operator-=(float val)
    {
        elements[0][0] -= val; elements[0][1] -= val; elements[0][2] -= val;
        elements[1][0] -= val; elements[1][1] -= val; elements[1][2] -= val;
        elements[2][0] -= val; elements[2][1] -= val; elements[2][2] -= val;
        return *this;
    }
    
    Mat3 operator/(float val) const
    {
        Mat3 res = *this;
        res.elements[0][0] /= val; res.elements[0][1] /= val; res.elements[0][2] /= val;
        res.elements[1][0] /= val; res.elements[1][1] /= val; res.elements[1][2] /= val;
        res.elements[2][0] /= val; res.elements[2][1] /= val; res.elements[2][2] /= val;
        return res;
    }
    
    Mat3& operator/=(float val)
    {
        elements[0][0] /= val; elements[0][1] /= val; elements[0][2] /= val;
        elements[1][0] /= val; elements[1][1] /= val; elements[1][2] /= val;
        elements[2][0] /= val; elements[2][1] /= val; elements[2][2] /= val;
        return *this;
    }
    
    Mat3 operator*(float val) const
    {
        Mat3 res = *this;
        res.elements[0][0] *= val; res.elements[0][1] *= val; res.elements[0][2] *= val;
        res.elements[1][0] *= val; res.elements[1][1] *= val; res.elements[1][2] *= val;
        res.elements[2][0] *= val; res.elements[2][1] *= val; res.elements[2][2] *= val;
        return res;
    }
    
    Mat3& operator*=(float val)
    {
        elements[0][0] *= val; elements[0][1] *= val; elements[0][2] *= val;
        elements[1][0] *= val; elements[1][1] *= val; elements[1][2] *= val;
        elements[2][0] *= val; elements[2][1] *= val; elements[2][2] *= val;
        return *this;
    }
    
    Mat3 operator+(const Mat3& b) const
    {
        Mat3 res = *this;
        res.elements[0][0] += b.elements[0][0]; res.elements[0][1] += b.elements[0][1]; res.elements[0][2] += b.elements[0][2];
        res.elements[1][0] += b.elements[1][0]; res.elements[1][1] += b.elements[1][1]; res.elements[1][2] += b.elements[1][2];
        res.elements[2][0] += b.elements[2][0]; res.elements[2][1] += b.elements[2][1]; res.elements[2][2] += b.elements[2][2];
        return res;
    }
    
    Mat3& operator+=(const Mat3& b)
    {
        elements[0][0] += b.elements[0][0]; elements[0][1] += b.elements[0][1]; elements[0][2] += b.elements[0][2];
        elements[1][0] += b.elements[1][0]; elements[1][1] += b.elements[1][1]; elements[1][2] += b.elements[1][2];
        elements[2][0] += b.elements[2][0]; elements[2][1] += b.elements[2][1]; elements[2][2] += b.elements[2][2];
        return *this;
    }
    
    Mat3 operator-(const Mat3& b) const
    {
        Mat3 res = *this;
        
        res.elements[0][0] -= b.elements[0][0]; res.elements[0][1] -= b.elements[0][1]; res.elements[0][2] -= b.elements[0][2];
        res.elements[1][0] -= b.elements[1][0]; res.elements[1][1] -= b.elements[1][1]; res.elements[1][2] -= b.elements[1][2];
        res.elements[2][0] -= b.elements[2][0]; res.elements[2][1] -= b.elements[2][1]; res.elements[2][2] -= b.elements[2][2];
        return res;
    }
    
    Mat3& operator-=(const Mat3& b)
    {
        elements[0][0] -= b.elements[0][0]; elements[0][1] -= b.elements[0][1]; elements[0][2] -= b.elements[0][2];
        elements[1][0] -= b.elements[1][0]; elements[1][1] -= b.elements[1][1]; elements[1][2] -= b.elements[1][2];
        elements[2][0] -= b.elements[2][0]; elements[2][1] -= b.elements[2][1]; elements[2][2] -= b.elements[2][2];
        return *this;
    }
    
	Mat3 operator*(const Mat3& b) const
	{
		Mat3 res;
        
        res.elements[0][0] = elements[0][0] * b.elements[0][0] + elements[0][1] * b.elements[1][0];
        res.elements[0][1] = elements[0][0] * b.elements[0][1] + elements[0][1] * b.elements[1][1];
        res.elements[1][0] = elements[1][0] * b.elements[0][0] + elements[1][1] * b.elements[1][0];
        res.elements[1][1] = elements[1][0] * b.elements[0][1] + elements[1][1] * b.elements[1][1];
        return res;
	}
    
    Mat3& operator*=(const Mat3& b)
	{
		Mat3 temp = *this;
        
        elements[0][0] = temp.elements[0][0] * b.elements[0][0] + temp.elements[0][1] * b.elements[1][0];
        elements[0][1] = temp.elements[0][0] * b.elements[0][1] + temp.elements[0][1] * b.elements[1][1];
        elements[1][0] = temp.elements[1][0] * b.elements[0][0] + temp.elements[1][1] * b.elements[1][0];
        elements[1][1] = temp.elements[1][0] * b.elements[0][1] + temp.elements[1][1] * b.elements[1][1];
        
        return *this;
	}
    
    Mat3 inverse() const
    {
        Mat3 res = *this;
        res.negateTransposeSelf();
        float d = 1 / determinant();
        res *= d;
        return res;
    }
    
    Mat3& inverseSelf()
    {
        negateTransposeSelf();
        *(this) *= 1/determinant();
        return *this;
    }
    
    
    //TODO:: check if matrix division even works it should
    Mat3 operator/(const Mat3& b) const
    {
        Mat3 res;
        auto bInverse = b.inverse();
        res = *(this) * bInverse;
        return res;
    }
    
    Mat3& operator/=(const Mat3& b)
    {
        auto bInverse = b.inverse();
        *(this) *=  bInverse;
        return *this;
    }
};

struct Mat4
{
	union
	{
		f32 elements[4][4] = {};
	};
    
	Mat4()
	{
	}
    
	Mat4(f32 diagonal)
	{
		elements[0][0] = diagonal; elements[0][1] = 0; elements[0][2] = 0; elements[0][3] = 0;
		elements[1][0] = 0; elements[1][1] = diagonal; elements[1][2] = 0; elements[1][3] = 0;
		elements[2][0] = 0; elements[2][1] = 0; elements[2][2] = diagonal; elements[2][3] = 0;
		elements[3][0] = 0; elements[3][1] = 0; elements[3][2] = 0; elements[3][3] = diagonal;
	}
    
	Mat4(const f32 _data[4][4])
	{
        elements[0][0] = _data[0][0]; elements[0][1] = _data[0][1]; elements[0][2] = _data[0][2]; elements[0][3] = _data[0][3];
        elements[1][0] = _data[1][0]; elements[1][1] = _data[1][1]; elements[1][2] = _data[1][2]; elements[1][3] = _data[1][3];
        elements[2][0] = _data[2][0]; elements[2][1] = _data[2][1]; elements[2][2] = _data[2][2]; elements[2][3] = _data[2][3];
        elements[3][0] = _data[3][0]; elements[3][1] = _data[3][1]; elements[3][2] = _data[3][2]; elements[3][3] = _data[3][3];
	}
    
	Mat4 identity()
	{
		return Mat4(1.0f);
	}
    
    Mat4 transpose()
    {
        Mat4 res;
        res.elements[0][0] = elements[0][0]; res.elements[0][1] = elements[1][0];
        res.elements[1][0] = elements[0][1]; res.elements[1][1] = elements[1][1];
        return res;
    }
    
    Mat4& transposeSelf()
    {
        Mat4 res = *this;
        elements[0][0] = res.elements[0][0]; elements[0][1] = res.elements[1][0];
        elements[1][0] = res.elements[0][1]; elements[1][1] = res.elements[1][1];
        return *this;
    }
    
    Mat4 negateTranspose()
    {
        Mat4 res = *this;
        res.elements[0][0] =  elements[1][1]; res.elements[0][1] = -elements[0][1];
        res.elements[1][0] = -elements[1][0]; res.elements[1][1] =  elements[0][0];
        return res;
    }
    
    Mat4& negateTransposeSelf()
    {
        Mat4 res = *this;
        elements[0][0] =  res.elements[1][1]; elements[0][1] = -res.elements[0][1];
        elements[1][0] = -res.elements[1][0]; elements[1][1] =  res.elements[0][0];
        return *this;
    }
    
    float determinant() const
    {
        return elements[0][0] * elements[1][1] - elements[1][0] * elements[0][1];
    }
    
    void print() const
    {
        printf("%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f ,%f\n",
               elements[0][0], elements[0][1], elements[0][2], elements[0][3],
               elements[1][0], elements[1][1], elements[1][2], elements[1][3],
               elements[2][0], elements[2][1], elements[2][2], elements[2][3],
               elements[3][0], elements[3][1], elements[3][2], elements[3][3]
               );
    }
    
    Mat4 operator+(float val) const
    {
        Mat4 res = *this;
        res.elements[0][0] += val; res.elements[0][1] += val; res.elements[0][2] += val; res.elements[0][3] += val;
        res.elements[1][0] += val; res.elements[1][1] += val; res.elements[1][2] += val; res.elements[1][3] += val;
        res.elements[2][0] += val; res.elements[2][1] += val; res.elements[2][2] += val; res.elements[2][3] += val;
        res.elements[3][0] += val; res.elements[3][1] += val; res.elements[3][2] += val; res.elements[3][3] += val;
        return res;
    }
    
    Mat4& operator+=(float val)
    {
        elements[0][0] += val; elements[0][1] += val; elements[0][2] += val; elements[0][3] += val;
        elements[1][0] += val; elements[1][1] += val; elements[1][2] += val; elements[1][3] += val;
        elements[2][0] += val; elements[2][1] += val; elements[2][2] += val; elements[2][3] += val;
        elements[3][0] += val; elements[3][1] += val; elements[3][2] += val; elements[3][3] += val;
        return *this;
    }
    
    Mat4 operator-(float val) const
    {
        Mat4 res = *this;
        res.elements[0][0] -= val; res.elements[0][1] -= val; res.elements[0][2] -= val; res.elements[0][3] -= val;
        res.elements[1][0] -= val; res.elements[1][1] -= val; res.elements[1][2] -= val; res.elements[1][3] -= val;
        res.elements[2][0] -= val; res.elements[2][1] -= val; res.elements[2][2] -= val; res.elements[2][3] -= val;
        res.elements[3][0] -= val; res.elements[3][1] -= val; res.elements[3][2] -= val; res.elements[3][3] -= val;
        return res;
    }
    
    Mat4& operator-=(float val)
    {
        elements[0][0] -= val; elements[0][1] -= val; elements[0][2] -= val; elements[0][3] -= val;
        elements[1][0] -= val; elements[1][1] -= val; elements[1][2] -= val; elements[1][3] -= val;
        elements[2][0] -= val; elements[2][1] -= val; elements[2][2] -= val; elements[2][3] -= val;
        elements[3][0] -= val; elements[3][1] -= val; elements[3][2] -= val; elements[3][3] -= val;
        return *this;
    }
    
    Mat4 operator/(float val) const
    {
        Mat4 res = *this;
        res.elements[0][0] /= val; res.elements[0][1] /= val; res.elements[0][2] /= val; res.elements[0][3] /= val;
        res.elements[1][0] /= val; res.elements[1][1] /= val; res.elements[1][2] /= val; res.elements[1][3] /= val;
        res.elements[2][0] /= val; res.elements[2][1] /= val; res.elements[2][2] /= val; res.elements[2][3] /= val;
        res.elements[3][0] /= val; res.elements[3][1] /= val; res.elements[3][2] /= val; res.elements[3][3] /= val;
        return res;
    }
    
    Mat4& operator/=(float val)
    {
        elements[0][0] /= val; elements[0][1] /= val; elements[0][2] /= val; elements[0][3] /= val;
        elements[1][0] /= val; elements[1][1] /= val; elements[1][2] /= val; elements[1][3] /= val;
        elements[2][0] /= val; elements[2][1] /= val; elements[2][2] /= val; elements[2][3] /= val;
        elements[3][0] /= val; elements[3][1] /= val; elements[3][2] /= val; elements[3][3] /= val;
        return *this;
    }
    
    Mat4 operator*(float val) const
    {
        Mat4 res = *this;
        res.elements[0][0] *= val; res.elements[0][1] *= val; res.elements[0][2] *= val; res.elements[0][3] *= val;
        res.elements[1][0] *= val; res.elements[1][1] *= val; res.elements[1][2] *= val; res.elements[1][3] *= val;
        res.elements[2][0] *= val; res.elements[2][1] *= val; res.elements[2][2] *= val; res.elements[2][3] *= val;
        res.elements[3][0] *= val; res.elements[3][1] *= val; res.elements[3][2] *= val; res.elements[3][3] *= val;
        return res;
    }
    
    Mat4& operator*=(float val)
    {
        elements[0][0] *= val; elements[0][1] *= val; elements[0][2] *= val; elements[0][3] *= val;
        elements[1][0] *= val; elements[1][1] *= val; elements[1][2] *= val; elements[1][3] *= val;
        elements[2][0] *= val; elements[2][1] *= val; elements[2][2] *= val; elements[2][3] *= val;
        elements[3][0] *= val; elements[3][1] *= val; elements[3][2] *= val; elements[3][3] *= val;
        return *this;
    }
    
    Mat4 operator+(const Mat4& b) const
    {
        Mat4 res = *this;
        res.elements[0][0] += b.elements[0][0]; res.elements[0][1] += b.elements[0][1]; res.elements[0][2] += b.elements[0][2];
        res.elements[0][3] += b.elements[0][3];
        res.elements[1][0] += b.elements[1][0]; res.elements[1][1] += b.elements[1][1]; res.elements[1][2] += b.elements[1][2];
        res.elements[1][3] += b.elements[1][3];
        res.elements[2][0] += b.elements[2][0]; res.elements[2][1] += b.elements[2][1]; res.elements[2][2] += b.elements[2][2];
        res.elements[2][3] += b.elements[2][3];
        res.elements[3][0] += b.elements[3][0]; res.elements[3][1] += b.elements[3][1]; res.elements[3][2] += b.elements[3][2];
        res.elements[3][3] += b.elements[3][3];
        return res;
    }
    
    Mat4& operator+=(const Mat4& b)
    {
        elements[0][0] += b.elements[0][0]; elements[0][1] += b.elements[0][1]; elements[0][2] += b.elements[0][2];
        elements[0][3] += b.elements[0][3];
        elements[1][0] += b.elements[1][0]; elements[1][1] += b.elements[1][1]; elements[1][2] += b.elements[1][2];
        elements[1][3] += b.elements[1][3];
        elements[2][0] += b.elements[2][0]; elements[2][1] += b.elements[2][1]; elements[2][2] += b.elements[2][2];
        elements[2][3] += b.elements[2][3];
        elements[3][0] += b.elements[3][0]; elements[3][1] += b.elements[3][1]; elements[3][2] += b.elements[3][2];
        elements[3][3] += b.elements[3][3];
        return *this;
    }
    
    Mat4 operator-(const Mat4& b) const
    {
        Mat4 res = *this;
        res.elements[0][0] -= b.elements[0][0]; res.elements[0][1] -= b.elements[0][1]; res.elements[0][2] -= b.elements[0][2];
        res.elements[0][3] -= b.elements[0][3];
        res.elements[1][0] -= b.elements[1][0]; res.elements[1][1] -= b.elements[1][1]; res.elements[1][2] -= b.elements[1][2];
        res.elements[1][3] -= b.elements[1][3];
        res.elements[2][0] -= b.elements[2][0]; res.elements[2][1] -= b.elements[2][1]; res.elements[2][2] -= b.elements[2][2];
        res.elements[2][3] -= b.elements[2][3];
        res.elements[3][0] -= b.elements[3][0]; res.elements[3][1] -= b.elements[3][1]; res.elements[3][2] -= b.elements[3][2];
        res.elements[3][3] -= b.elements[3][3];
        return res;
    }
    
    Mat4& operator-=(const Mat4& b)
    {
        elements[0][0] -= b.elements[0][0]; elements[0][1] -= b.elements[0][1]; elements[0][2] -= b.elements[0][2];
        elements[0][3] -= b.elements[0][3];
        elements[1][0] -= b.elements[1][0]; elements[1][1] -= b.elements[1][1]; elements[1][2] -= b.elements[1][2];
        elements[1][3] -= b.elements[1][3];
        elements[2][0] -= b.elements[2][0]; elements[2][1] -= b.elements[2][1]; elements[2][2] -= b.elements[2][2];
        elements[2][3] -= b.elements[2][3];
        elements[3][0] -= b.elements[3][0]; elements[3][1] -= b.elements[3][1]; elements[3][2] -= b.elements[3][2];
        elements[3][3] -= b.elements[3][3];
        return *this;
    }
    
	Mat4 operator*(const Mat4& b) const
	{
		Mat4 res;
        
        res.elements[0][0] = elements[0][0] * b.elements[0][0] + elements[0][1] * b.elements[1][0];
        res.elements[0][1] = elements[0][0] * b.elements[0][1] + elements[0][1] * b.elements[1][1];
        res.elements[1][0] = elements[1][0] * b.elements[0][0] + elements[1][1] * b.elements[1][0];
        res.elements[1][1] = elements[1][0] * b.elements[0][1] + elements[1][1] * b.elements[1][1];
        
        return res;
	}
    
    Mat4& operator*=(const Mat4& b)
	{
		Mat4 temp = *this;
        
        elements[0][0] = temp.elements[0][0] * b.elements[0][0] + temp.elements[0][1] * b.elements[1][0];
        elements[0][1] = temp.elements[0][0] * b.elements[0][1] + temp.elements[0][1] * b.elements[1][1];
        elements[1][0] = temp.elements[1][0] * b.elements[0][0] + temp.elements[1][1] * b.elements[1][0];
        elements[1][1] = temp.elements[1][0] * b.elements[0][1] + temp.elements[1][1] * b.elements[1][1];
        
        return *this;
	}
    
    Mat4 inverse() const
    {
        Mat4 res = *this;
        res.negateTransposeSelf();
        float d = 1 / determinant();
        res *= d;
        return res;
    }
    
    Mat4& inverseSelf()
    {
        negateTransposeSelf();
        *(this) *= 1/determinant();
        return *this;
    }
    
    
    //TODO:: check if matrix division even works it should
    Mat4 operator/(const Mat4& b) const
    {
        Mat4 res;
        auto bInverse = b.inverse();
        res = *(this) * bInverse;
        return res;
    }
    
    Mat4& operator/=(const Mat4& b)
    {
        auto bInverse = b.inverse();
        *(this) *=  bInverse;
        return *this;
    }
};

#pragma pack(pop)

#endif //_MATHS_H
