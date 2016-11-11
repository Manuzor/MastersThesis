//
// Vertex Shader
//
layout(binding=0) uniform Buffer { mat4 MVP; };
layout(location=0) in vec3 Pos;
void main() {
  gl_Position = MVP * vec4(Pos, 1.0f);
}

//
// Fragment Shader
//
layout(location=0) out vec4 FragmentColor;
void main() {
  FragmentColor.rgb = vec3(0.4, 0.6, 0.9); // Cornflower blue.
}
