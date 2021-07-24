#version 330 core
in vec2 TexCoord;

uniform sampler2D tex;

void main() {
	vec4 texColor = texture(tex, TexCoord);
	//if (texColor.a < 0.1)
	//	discard;
	gl_FragColor = texColor;
}