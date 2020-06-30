#version 440
layout (location=0) in vec3 vs_position;
layout (location=1) in vec2 vs_offset;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;



void main(){
	vec4 pos = vec4(vs_position+vec3(vs_offset,0.f),1.f);
	gl_Position = projectionMatrix*viewMatrix*modelMatrix*pos;
}

