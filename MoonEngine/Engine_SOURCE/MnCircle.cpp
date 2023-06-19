#include "MnCircle.h"
#define PI 3.1415926535

namespace Mn
{
	Circle::Circle()
		:buffer(30)
		,vertices(nullptr)
		,idxVertices(nullptr)
	{
	}
	Circle::~Circle()
	{
	}
	void Circle::Initialize()
	{
		//vertices = new Vertex[buffer];
		//idxVertices = new Vertex[90];
		//int i = 0;
		//for (double angle = 0.0f; angle <= PI * 2.0f; angle += PI / 10.0f) {
		//	vertices[i].pos= Vector3((float)(0.25f * cos(angle)),(float)(0.25f * sin(angle)), 0.0f);
		//	vertices[i].color = Vector4((float)(0.25f * cos(angle)), (float)(0.25f * sin(angle)), 1.0f , 1.0f);
		//	i++;
		//}

		//Index();
	}
	void Circle::Index()
	{
		/*idxVertices[0].pos = Vector3::Zero;
		idxVertices[0].color = Vector4(1.0f,1.0f,1.0f,1.0f);

		idxVertices[1].pos = vertices[1].pos;
		idxVertices[2].pos = vertices[0].pos;
		int i = 1;
		for (int j = 0; j < 90; j+=3)
		{
			idxVertices[j].pos = Vector3::Zero;
			idxVertices[j].color = Vector4(1.0f,1.0f,1.0f,1.0f);
			for (int k = 1; k < 2; k ++)
			{
				idxVertices[j + k].pos = vertices[i].pos;
				idxVertices[j + k+1].pos = vertices[i-1].pos;
				i++;
			}
		}


	}
	double Circle::Degree2Radian(int degree)
	{
		return (degree * PI) / 180;
	}*/
	}
}