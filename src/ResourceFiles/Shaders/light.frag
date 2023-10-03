#version 330 core

out vec4 FragColor;

in vec3 color;

uniform vec4 lightColor;

uniform bool isRoundPoint;

void main()
{
    vec2 coord = gl_PointCoord - vec2(0.5);
     if(isRoundPoint && length(coord) > 0.5)
    discard;
	FragColor = vec4(color,1.0f);
}