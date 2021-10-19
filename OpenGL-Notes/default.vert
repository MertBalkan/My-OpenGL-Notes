#version 330                      
								
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colour;
layout (location = 2) in vec2 aTex;

out vec3 color;
out vec2 texCoord;

uniform float scale;

void main()                       
{                                 
	gl_Position = vec4(pos.x + pos.x * scale, pos.y + pos.y * scale, pos.z + pos.z * scale, 1.0);
	color = colour;
	texCoord = aTex;
}