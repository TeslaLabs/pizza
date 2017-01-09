#version 120

attribute vec3 in_position;
attribute vec3 in_normal;
attribute vec2 in_uv;

uniform mat4 projection;
uniform mat4 modelview;

void main(void) {
  gl_Position = projection * modelview * vec4(in_position, 1);
}
