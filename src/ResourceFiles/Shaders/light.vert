#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 camMatrix;
out vec3 color;
uniform vec3 Color2;

// Controls the size of the vertices
 uniform float vertexSize;

// Inputs the matrices needed for 3D viewing with perspective
uniform mat4 model;
uniform bool isRoundPoint;

void main()
{
   gl_PointSize = vertexSize;
   gl_Position = camMatrix * model * vec4(aPos, 1.0);
   color = Color2;
}
