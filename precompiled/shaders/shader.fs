#version 330

out vec4 out_colour;

in vec2 tex_coords;

uniform sampler2D sampler;
uniform vec4 custom_color;

void main(void){

    vec4 color = texture2D(sampler,tex_coords);
    out_colour = (color-(vec4(1.0)-custom_color))*1.4;
    
	
}
