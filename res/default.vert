#version 120

attribute vec3 in_position;
attribute vec3 in_normal;
attribute vec2 in_uv;
varying vec4 frag_color;

uniform mat4 projection;
uniform mat4 modelview;

void main(void) {
  gl_Position = projection * modelview * vec4(in_position, 1);
  frag_color = vec4(in_normal, 1);
}
