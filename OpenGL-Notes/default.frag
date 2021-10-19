#version 330                               
											
out vec4 fragColor;                    
in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;

void main()                                
{                                          
	fragColor = texture(tex0, texCoord); 
}