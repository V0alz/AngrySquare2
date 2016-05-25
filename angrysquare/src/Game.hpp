#pragma once

#include "Mesh.hpp"

class Game
{
public:
	Game()
	{
		MeshData d;
		d.Set( glm::vec2( 0.0f, 0.5f ) );
		d.Set( glm::vec2( 0.5f, -0.5f ) );
		d.Set( glm::vec2( -0.5f, -0.5f ) );
		d.AddFace( glm::vec3( 0, 1, 2 ) );
		m.Set( d );
	}

	~Game()
	{

	}

	void Frame()
	{
		m.Draw();
	}

private:
	Mesh m;
};