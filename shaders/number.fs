#version 330

out vec4 out_colour;

in vec2 tex_coords;

uniform sampler2D sampler;

void main(void){

    vec2 texture = tex_coords;
    texture.y = 1.0-texture.y;
    vec4 color = texture2D(sampler,texture);
    if(color.a < .5) discard; 
    out_colour = vec4(1.0);
	
}
