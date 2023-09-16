#pragma once
#include <iostream>
using namespace std;

// 3 * 3매트릭스, 4 * 4매트릭스
#define Matrix33\
	{			\
	{1,0,0}		\
	,{0,1,0}	\
	,{0,0,1}	\
	}			\

#define Matrix44\
	{			\
	{1,0,0,0}	\
	,{0,1,0,0}	\
	,{0,0,1,0}	\
	,{0,0,0,1}	\
	}			\

//1*3행렬
struct Matrix13
{
	union
	{
		struct
		{
			float _11, _12, _13;
		};
		float matrix[1][3] = { {0,0,0} };
	};
	int col = 3;
	int row = 1;

	Matrix13() { matrix[0][0] = 0; matrix[0][1] = 0; matrix[0][2] = 0; }

	Matrix13(float arr[1][3])
	{
		for (int i = 0; i < col; i++)
		{
			matrix[0][i] = arr[0][i];
		}
	}

	Matrix13(float arr[3])
	{
		for (int i = 0; i < col; i++)
		{
			matrix[0][i] = arr[i];
		}
	}

	Matrix13(float num1, float num2, float num3)
	{
		matrix[0][0] = num1; matrix[0][1] = num2; matrix[0][2] = num3;
	}

	Matrix13(const Matrix13& pos)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				matrix[i][j] = pos.matrix[i][j];
			}
		}
	}
};

//1*4행렬
struct Matrix14
{
	union
	{
		struct
		{
			float _11, _12, _13, _14;
		};
		float matrix[1][4] = { {0,0,0,0} };
	};

	int col = 4;
	int row = 1;

	Matrix14() { matrix[0][0] = 0; matrix[0][1] = 0; matrix[0][2] = 0; matrix[0][3] = 0; }

	Matrix14(float arr[1][4])
	{
		for (int i = 0; i < col; i++)
		{
			matrix[0][i] = arr[0][i];
		}
	}

	Matrix14(float arr[4])
	{
		for (int i = 0; i < col; i++)
		{
			matrix[0][i] = arr[i];
		}
	}

	Matrix14(float num1, float num2, float num3, float num4)
	{
		matrix[0][0] = num1; matrix[0][1] = num2; matrix[0][2] = num3; matrix[0][2] = num4;
	}

	Matrix14(const Matrix14& pos)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				matrix[i][j] = pos.matrix[i][j];
			}
		}
	}
};

//3*3행렬
struct Matrix3
{
	union
	{
		struct
		{
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
		};
		float matrix[3][3] = Matrix33;
	};

	int size = 3;

	Matrix3() {  }

	Matrix3(float arr[3][3])
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				matrix[i][j] = arr[i][j];
			}
		}
	}

	Matrix3(float num1, float num2, float num3,
		float num4, float num5, float num6,
		float num7, float num8, float num9)
	{
		matrix[0][0] = num1; matrix[0][1] = num2; matrix[0][2] = num3;
		matrix[1][0] = num4; matrix[1][1] = num5; matrix[1][2] = num6;
		matrix[2][0] = num7; matrix[2][1] = num8; matrix[2][2] = num9;
	}

	Matrix3(const Matrix3& pos)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				matrix[i][j] = pos.matrix[i][j];
			}
		}
	}
};

//4*4행렬
struct Matrix4
{
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float matrix[4][4] = Matrix44;
	};

	int size = 4;

	Matrix4() {  }

	Matrix4(float arr[4][4])
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				matrix[i][j] = arr[i][j];
			}
		}
	}

	Matrix4(float num1, float num2, float num3, float num4,
		float num5, float num6, float num7, float num8,
		float num9, float num10, float num11, float num12)
	{
		matrix[0][0] = num1; matrix[0][1] = num2; matrix[0][2] = num3; matrix[0][3] = num4;
		matrix[1][0] = num5; matrix[1][1] = num6; matrix[1][2] = num7; matrix[1][3] = num8;
		matrix[2][0] = num9; matrix[2][1] = num10; matrix[2][2] = num11; matrix[2][3] = num12;
	}

	Matrix4(const Matrix4& pos)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				matrix[i][j] = pos.matrix[i][j];
			}
		}
	}

};

//3*3행렬이 같은지
bool IsEqualMatrix(Matrix3 m1, Matrix3 m2)
{
	if (m1.size != m2.size)
	{
		return false;
	}

	for (int i = 0; i < m1.size; i++)
	{
		for (int j = 0; j < m1.size; j++)
		{
			if (m1.matrix[i][j] != m2.matrix[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

//4*4행렬이 같은지
bool IsEqualMatrix(Matrix4 m1, Matrix4 m2)
{
	if (m1.size != m2.size)
	{
		return false;
	}

	for (int i = 0; i < m1.size; i++)
	{
		for (int j = 0; j < m1.size; j++)
		{
			if (m1.matrix[i][j] != m2.matrix[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

//3*3행렬 덧셈
Matrix3 MatrixSum(Matrix3 m1, Matrix3 m2)
{
	Matrix3 tmpmat;

	for (int i = 0; i < tmpmat.size; i++)
	{
		for (int j = 0; j < tmpmat.size; j++)
		{
			tmpmat.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
		}
	}
	return tmpmat;
}

//4*4행렬 덧셈
Matrix4 MatrixSum(Matrix4 m1, Matrix4 m2)
{
	Matrix4 tmpmat;

	for (int i = 0; i < tmpmat.size; i++)
	{
		for (int j = 0; j < tmpmat.size; j++)
		{
			tmpmat.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
		}
	}
	return tmpmat;
}

//3*3행렬 뺄셈
Matrix3 MatrixSub(Matrix3 m1, Matrix3 m2)
{
	Matrix3 tmpmat;

	for (int i = 0; i < tmpmat.size; i++)
	{
		for (int j = 0; j < tmpmat.size; j++)
		{
			tmpmat.matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
		}
	}
	return tmpmat;
}

//4*4행렬 뺄셈
Matrix4 MatrixSub(Matrix4 m1, Matrix4 m2)
{
	Matrix4 tmpmat;

	for (int i = 0; i < tmpmat.size; i++)
	{
		for (int j = 0; j < tmpmat.size; j++)
		{
			tmpmat.matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
		}
	}
	return tmpmat;
}

//3*3행렬 곱셈
Matrix3 MatrixMulply(Matrix3 m1, Matrix3 m2)
{
	Matrix3 tmpmat;

	for (int i = 0; i < m1.size; i++)
	{
		for (int j = 0; j < m2.size; j++)
		{
			for (int k = 0; k < m1.size; k++)
			{
				tmpmat.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];

			}
		}
	}
	return tmpmat;
}

//4*4행렬 곱셈
Matrix4 MatrixMulply(Matrix4 m1, Matrix4 m2)
{
	Matrix4 tmpmat;

	for (int i = 0; i < m1.size; i++)
	{
		for (int j = 0; j < m2.size; j++)
		{

			for (int k = 0; k < m1.size; k++)
			{
				tmpmat.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];

			}
		}
	}
	return tmpmat;
}

//1*3행렬과 3*3행렬 곱셈
Matrix13 MatrixMulply(Matrix13 m1, Matrix3 m2)
{
	Matrix13 tmpmat;

	for (int i = 0; i < m1.row; i++)
	{
		for (int j = 0; j < m2.size; j++)
		{
			for (int k = 0; k < m1.col; k++)
			{
				tmpmat.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
			}
		}
	}

	return tmpmat;
}

//1*4행렬과 4*4행렬 곱셈
Matrix14 MatrixMulply(Matrix14 m1, Matrix4 m2)
{
	Matrix14 tmpmat;

	for (int i = 0; i < m1.row; i++)
	{
		for (int j = 0; j < m2.size; j++)
		{
			for (int k = 0; k < m1.col; k++)
			{
				tmpmat.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
			}
		}
	}
	return tmpmat;
}

//3*3행렬 스칼라곱
Matrix3 MatrixScalar(Matrix3 m1, int scalar)
{
	Matrix3 tmpmat;

	for (int i = 0; i < tmpmat.size; i++)
	{
		for (int j = 0; j < tmpmat.size; j++)
		{
			tmpmat.matrix[i][j] = m1.matrix[i][j] * scalar;
		}
	}
	return tmpmat;
}

//4*4행렬 스칼라곱
Matrix4 MatrixScalar(Matrix4 m1, int scalar)
{
	Matrix4 tmpmat;

	for (int i = 0; i < tmpmat.size; i++)
	{
		for (int j = 0; j < tmpmat.size; j++)
		{
			tmpmat.matrix[i][j] = m1.matrix[i][j] * scalar;
		}
	}
	return tmpmat;
}

//3*3행렬 출력(콘솔용)
void ShowMatrix(Matrix3 m1)
{
	for (int i = 0; i < m1.size; i++)
	{
		for (int j = 0; j < m1.size; j++)
		{
			cout << m1.matrix[i][j] << " ";
		}
		cout << endl;
	}
}

//4*4행렬 출력(콘솔용)
void ShowMatrix(Matrix4 m1)
{
	for (int i = 0; i < m1.size; i++)
	{
		for (int j = 0; j < m1.size; j++)
		{
			cout << m1.matrix[i][j] << " ";
		}
		cout << endl;
	}
}

//1*3행렬 출력(콘솔용)
void ShowMatrix(Matrix13 m1)
{
	for (int i = 0; i < m1.row; i++)
	{
		for (int j = 0; j < m1.col; j++)
		{
			cout << m1.matrix[i][j] << " ";
		}
		cout << endl;
	}
}

//1*4행렬 출력(콘솔용)
void ShowMatrix(Matrix14 m1)
{
	for (int i = 0; i < m1.row; i++)
	{
		for (int j = 0; j < m1.col; j++)
		{
			cout << m1.matrix[i][j] << " ";
		}
		cout << endl;
	}
}

//전치행렬
void TransPos(Matrix13 mat, float outmat[3][1])
{
	int sizecol = sizeof(mat.matrix[0]) / sizeof(float);
	int sizerow = sizeof(mat) / sizeof(mat.matrix[0]);

	for (int i = 0; i < sizecol; i++)
	{
		for (int j = 0; j < sizerow; j++)
		{
			outmat[i][j] = mat.matrix[j][i];
		}
	}
}

#pragma region MatrixTo
//벡터를 1*4행렬로
void SetVecToMat1X4(Matrix14& mat, Vector3D vec)
{
	mat._11 = vec.GetX();
	mat._12 = vec.GetY();
	mat._13 = vec.GetZ();
	mat._14 = 1;
}
//1*4행렬을 벡터로
void SetMat1X4ToVec(Vector3D& vec, Matrix14 m)
{
	vec.SetXYZ(m._11, m._12, m._13);
}
//Point구조체를 3*3행렬로
void SetMat3X3ToPos(Matrix3& m, Point _dpos)
{
	m._31 = _dpos.x;
	m._32 = _dpos.y;
}
//Point구조체를 1*3행렬로
void SetPosToMat1X3(Matrix13& m, Point _pos)
{
	m._11 = _pos.x;
	m._12 = _pos.y;
	m._13 = 1;
}
//1*3행렬을 Point구조체로
void SetMat1X3ToPos(Point& _pos, Matrix13 m)
{
	_pos.x = m._11;
	_pos.y = m._12;
}
//벡터를 3*3행렬로
void SetVecToMat3X3(Matrix3& m, Vector3D _dpos)
{
	m._31 = _dpos.GetX();
	m._32 = _dpos.GetY();
}
//벡터를 1*3행렬로
void SetVecToMat1X3(Matrix13& m, Vector3D _pos)
{
	m._11 = _pos.GetX();
	m._12 = _pos.GetY();
	m._13 = 1;
}
//1*3행렬을 벡터로
void SetMat1X3ToVec(Vector3D& _pos, Matrix13 m)
{
	_pos.SetXYZ(m._11, m._12, m._13);
}

#pragma endregion

