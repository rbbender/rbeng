#version 330 core
layout (location = 0) in vec2 aPos;

uniform mat3 world;
uniform mat3 model;

void main() {
	vec3 t = world * model * vec3(aPos.xy, 1.0f);
	gl_Position = vec4(t, 1.0f);
}
