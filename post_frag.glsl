#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{ 
    FragColor = texture(screenTexture, TexCoords);

    if (abs(TexCoords.x - 0.5f) < 0.002f && abs(TexCoords.y - 0.5f) < 0.002f) {
        FragColor = vec4(1, 1, 1, 1.0);
    }
}