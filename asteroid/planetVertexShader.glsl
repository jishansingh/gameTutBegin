#version 440
layout (location=0) in vec4 vs_position;
//layout (location=1) in vec2 vs_offset;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec2 offsets[1000];

out vec2 texcoord;

void main(){
	vec4 pos = vec4(vs_position.xy+offsets[gl_InstanceID],0.f,1.f);
	texcoord = vec2(vs_position.zw);
	gl_Position = projectionMatrix*viewMatrix*modelMatrix*pos;
}

