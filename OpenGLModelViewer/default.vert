#version 330 core

//positions for object coordinates
layout (location = 0) in vec3 aPos;
//colors
layout (location = 1) in vec3 aColor;
//texture coordinates
layout (location = 2) in vec2 aTex;

//outputs the color to fragment shader
out vec3 color;
// outputs texture coordinates to frag shader
out vec2 texCoord;

uniform mat4 camMatrix;

void main()
{
//Outputs the positions/coordinates of all the verticies
  gl_Position = camMatrix * vec4(aPos, 1.0);
  color = aColor;
  texCoord = aTex;
}