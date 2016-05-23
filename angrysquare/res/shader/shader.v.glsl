#version 330 core
  
layout (location = 0) in vec3 coordinate;

void main()
{
    gl_Position = vec4( coordinate.x, coordinate.y, coordinate.z, 1.0 );
}
