#version 120

attribute vec3 in_position;
attribute vec3 in_normal;
attribute vec3 in_uv;
// varying vec4 frag_color;

void main()
{
  vec4 my_vector = vec4(in_position.x, in_normal.y, in_uv.x, 1);
  gl_Position = vec4(0, 0, 0.5, 1);
}
