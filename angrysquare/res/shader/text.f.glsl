#version 330 core

in vec2 v_uv;

out vec4 color;

uniform sampler2D tex;

void main()
{
	vec4 sampled = vec4( 1.0, 1.0, 1.0, texture( tex, v_uv ).r );
	color = vec4( 1, 1, 1, 1 ) * sampled;
}
