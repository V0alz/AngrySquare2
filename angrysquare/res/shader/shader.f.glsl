#version 330 core

in vec2 v_uv;

out vec4 color;

uniform sampler2D tex1;

void main()
{
	vec4 outcol;
	outcol = texture( tex1, v_uv );

    color = outcol;
}
