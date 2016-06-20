#version 330 core
  
layout (location = 0) in vec4 vertex;

uniform mat4 _model;
uniform mat4 _view;
uniform mat4 _projection;

out vec2 v_uv;

void main()
{
	v_uv = vertex.zw;
    gl_Position = _projection * _view * _model * vec4( vertex.xy, 0.0, 1.0 );
}
