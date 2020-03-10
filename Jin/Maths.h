#pragma once
#include <cmath>

#pragma pack(push, 1)

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
		f32 data[2 * 2];
		f32 elements[2 * 2];
		Vec2 rows[2];
	};

	Mat2()
	{
		memset(elements, 0, 2 * 2 * sizeof(f32));
	}

	Mat2(f32 diagonal)
	{
		memset(elements, 0, 2 * 2 * sizeof(f32));
		elements[0 + 0 * 2] = diagonal;
		elements[1 + 1 * 2] = diagonal;
	}

	Mat2(f32* data)
	{
		memcpy(elements, data, 2 * 2 * sizeof(f32));
	}

	Mat2(const Vec2& row0, const Vec2& row1)
	{
		rows[0] = row0;
		rows[1] = row1;
	}

	Mat2 identity()
	{
		return Mat2(1.0f);
	}

	Mat2 operator*(const Mat2& b)
	{
		f32 _data[2 * 2];
		for (i32 row = 0; row < 2; row++)
		{
			for (i32 col = 0; col < 2; col++)
			{
				f32 sum = 0;
				for (i32 e = 0; e < 2; e++)
				{
					sum += elements[e + row * 2] * b.elements[col + e * 2];
				}
				_data[col + row * 2] = sum;
			}
		}

		return Mat2(_data);
	}

};

#pragma pack(pop)