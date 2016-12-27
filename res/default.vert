#version 140

in vec3 in_position;
in vec3 in_normal;
in vec2 in_uv;
out vec4 frag_color;

uniform mat4 projection;
uniform mat4 modelview;

void main(void)
{
    gl_Position = projection * modelview * vec4(in_position, 1);
    frag_color = vec4(in_normal.xy, in_uv.x, 1);
}