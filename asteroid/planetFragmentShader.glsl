#version 440
in vec2 texcoord;
out vec4 fs_color;

uniform sampler2D texture0;

void main(){
	//fs_color = vec4(1.f,0.f,0.f,0.5f);
	fs_color = texture(texture0,texcoord);
	//fs_color = vec4(texcoord,0.f,1.f);
}
