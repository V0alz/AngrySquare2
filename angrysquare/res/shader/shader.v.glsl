#version 330 core
  
layout (location = 0) in vec2 coordinate;
layout (location = 1) in vec2 uv;

uniform mat4 _model;

out vec2 v_uv;

void main()
{
	v_uv = uv;
    gl_Position = _model * vec4( coordinate.x, coordinate.y, -1.0, 1.0 );
}
