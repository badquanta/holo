#version 140
in vec2 vPos;
in vec3 vColor;
in vec2 vTexCoord;

out vec3 fColor;
out vec2 fTexCoord;

void main(){
  gl_Position=vec4(vPos.xy,0.0,1.0);
  fColor = vColor;
  fTexCoord = vec2(vTexCoord.xy) ;
}