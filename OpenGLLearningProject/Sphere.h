#pragma once
#include "Mesh.h"
#include "ObjectLoader.h"
#include <GLM/gtc/constants.hpp>

class Sphere : public Mesh
{
	float pi = glm::pi<float>();
protected:
	inline void LoadMesh() override
	{
		// UV Sphere with a radius of 0.5
		int ringCount = 16;
		int verticesPerRing = 64;
		
		float radiansPerVertex = 2*pi / verticesPerRing; // 2*pi
		float radiansPerRing = pi / (ringCount + 1);	//pi
		float x, y, ringHeight, ringRadius, currentRingRadian, u, v;
		glm::vec3 vertexPos; //glm:vec3

		// create vertices
		m_Vertices.push_back(Vertex(glm::vec3(0, 0.5f, 0), glm::vec3(0, 1, 0), glm::vec2(0, 0))); // top pole vertex

		for (int i = 0; i < ringCount; i++)
		{
			currentRingRadian = (pi/2)-i * radiansPerRing; // pi/2
			ringHeight = sinf(currentRingRadian); // visualize the sphere from the front: this is the vertical height of the ring
			ringRadius = cosf(currentRingRadian); // visualize the sphere from the top and front: this is the radius of the ring
			v = i / float(ringCount);

			for (int j = 0; j < verticesPerRing; j++)
			{
				x = cosf(j * radiansPerVertex) * ringRadius; // visualize the ring as a circle: this is the x position of a point on the circle with a given radius
				y = sinf(j * radiansPerVertex) * ringRadius; // visualize the ring as a circle: this is the y position of a point on the circle with a given radius
				u = j / float(verticesPerRing);
				vertexPos = { x, ringHeight, y }; // in a 1 radius sphere with 0,0,0 as center this is also the normal vector of the vertex
				m_Vertices.push_back(Vertex(vertexPos * 0.5f, vertexPos, { u, v }, { u,v,u * v,1 })); // position is halfed for 0.5 radius
			}
		}

		m_Vertices.push_back(Vertex(glm::vec3(0, -0.5, 0), glm::vec3(0, -1, 0), glm::vec2(1, 1))); // bottom pole vertex

		// set indices
		for (int i = 0; i < verticesPerRing; i++) // top pole triangles
		{
			AddTriangle(0, (i + 1) % verticesPerRing + 1, i + 1);
		}

		int ringIndexStart;
		int nextRingIndexStart;
		for (int i = 0; i < ringCount - 1; i++) // middle quads
		{
			ringIndexStart = verticesPerRing * i + 1;
			nextRingIndexStart = verticesPerRing * (i + 1) + 1;
			for (int j = 0; j < verticesPerRing; j++)
			{
				AddQuad(
					ringIndexStart + j,
					ringIndexStart + (j + 1) % verticesPerRing, // roll over to first index of current ring
					nextRingIndexStart + (j + 1) % verticesPerRing, // roll over to first index of next ring
					nextRingIndexStart + j
				);
			}
		}

		int bottomPoleIndex = verticesPerRing * ringCount + 1;
		for (int i = 0; i < verticesPerRing; i++) // bottom pole triangles
		{
			AddTriangle(bottomPoleIndex, i + nextRingIndexStart, (i + 1) % verticesPerRing + nextRingIndexStart);
		}
	}
};