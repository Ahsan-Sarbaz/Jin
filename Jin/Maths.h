#pragma once
#include <cmath>

#pragma pack(push, 1)

struct Vec2
{
	union
	{

		float data[2];

		struct
		{
			float x;
			float y;
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

	float length() const
	{
		return sqrt(x * x + y * y);
	}

	float distance(const Vec2& b) const
	{
		float diffX = x - b.x;
		float diffY = y - b.y;
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

		float data[3];

		struct
		{
			float x;
			float y;
			float z;
		};

		struct
		{
			float r;
			float g;
			float b;
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

	float length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	float distance(const Vec3& b) const
	{
		float diffX = x - b.x;
		float diffY = y - b.y;
		float diffZ = z - b.z;
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
		
		float data[4];
		
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
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

	float length() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	float distance(const Vec4& b) const
	{
		float diffX = x - b.x;
		float diffY = y - b.y;
		float diffZ = z - b.z;
		float diffW = w - b.w;
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
		float data[2 * 2];
		float elements[2 * 2];
		Vec2 rows[2];
	};

	Mat2()
	{
		memset(elements, 0, 2 * 2 * sizeof(float));
	}

	Mat2(float diagonal)
	{
		memset(elements, 0, 2 * 2 * sizeof(float));
		elements[0 + 0 * 2] = diagonal;
		elements[1 + 1 * 2] = diagonal;
	}

	Mat2(float* data)
	{
		memcpy(elements, data, 2 * 2 * sizeof(float));
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
		float _data[2 * 2];
		for (int row = 0; row < 2; row++)
		{
			for (int col = 0; col < 2; col++)
			{
				float sum = 0;
				for (int e = 0; e < 2; e++)
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