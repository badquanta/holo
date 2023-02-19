#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
vec2 FixedTexCoords;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

void main()
{
    FixedTexCoords = TexCoords * vec2(1.0f,-1.0f);
    vec3 ambient=vec3(texture(texture_diffuse1,FixedTexCoords))*0.01;
    vec3 normal =vec3(texture(texture_normal1,FixedTexCoords))*0.01;
    vec3 diffuse=vec3(texture(texture_diffuse1,FixedTexCoords));
    vec3 specular=vec3(texture(texture_specular1,FixedTexCoords))*0.51;
    FragColor=vec4(ambient+diffuse+specular+normal ,1.);

}