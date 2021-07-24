#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat3 world;
uniform mat3 model;

out vec2 TexCoord;

void main() {
	vec3 t = world * model * vec3(aPos.x, aPos.y, 1.0f);
	gl_Position = vec4(t, 1.0f);
	TexCoord = aTexCoord;
}
