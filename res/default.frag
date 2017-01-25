#version 120

varying vec4 frag_color;

void main(void)
{
  int newx = int(frag_color.x * 8.0);
  int newy = int(frag_color.y * 8.0);
  int newz = int(frag_color.z * 8.0);
  gl_FragColor = vec4(newx / 8.0,
                      newy / 8.0,
                      newz / 8.0,
                      frag_color.w);
}
