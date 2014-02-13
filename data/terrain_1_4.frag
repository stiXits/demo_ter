#version 140

uniform sampler2D water;
uniform float a_time;

in vec3 a_position;


out vec4 fragColor;


void main()
{
	fragColor = texture2D(water, a_position.xz + a_time/10);
	fragColor.a = 0.5;
}


