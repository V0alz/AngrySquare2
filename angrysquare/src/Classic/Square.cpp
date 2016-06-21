/*
*	Angry Square 2
*	Copyright(C) 2015-2016 Dennis Walsh
*
*	This program is free software : you can redistribute it and / or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
#include "Square.hpp"
#include "../Graphics/Loader/BMP.hpp"

Square::Square()
	:m_transform( glm::vec3() )
{
}

Square::Square( const std::string& texPath )
	:m_transform( glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ) )
{
	std::cout << "This constructor is a bad way at making \"Squares\"...\nLook at SquaresPlayer.*pp" << std::endl;
	m_sprite = new Sprite( glm::vec2( 0.22f, 0.22f ), BMP::Load( texPath ) );
}

Square::~Square()
{
	if( m_sprite != nullptr )
	{
		delete m_sprite;
		m_sprite = nullptr;
	}
}

void Square::Update()
{
}

void Square::Render( Shader& shader )
{
	shader.SetUniform( "_model", m_transform.GetModelMatrix() );
	m_sprite->Draw();
}
