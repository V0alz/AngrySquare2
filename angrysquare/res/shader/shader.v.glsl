#version 330 core
  
layout (location = 0) in vec2 coordinate;

void main()
{
    gl_Position = vec4( coordinate.x, coordinate.y, -1.0, 1.0 );
}
