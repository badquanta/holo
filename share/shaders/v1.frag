#version 140
in vec3 fColor;
in vec2 fTexCoord;
out vec4 FragColorOut;

uniform sampler2D activeTexture;

void main(){
  FragColorOut=texture(activeTexture, fTexCoord) + (vec4(fColor,1.0)*0.25);
}