#version 330 core
layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

out vec3 color;
out vec2 texCoord;
out vec3 Normal;
flat out vec3 NormalFlat;
out vec3 FragPos;

uniform mat4 camMatrix;
uniform vec3 Color2;


// vertex round or square
uniform bool isRound;

// Controls the size of the vertices
 uniform float vertexSize;

// Inputs the matrices needed for 3D viewing with perspective
uniform mat4 model;

void main()
{
   gl_PointSize = vertexSize;
   gl_Position = camMatrix * model * vec4(aPos, 1.0);
   color = Color2;
   FragPos = vec3(model * vec4(aPos, 1.0f));
   texCoord = aTex;
   NormalFlat = Normal = mat3(transpose(inverse(model))) * aNormal;
}
