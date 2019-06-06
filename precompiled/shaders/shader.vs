#version 150

in vec2 position;

uniform mat4 transformation;
uniform mat4 projection;
uniform vec4 custom_color;

out vec2 tex_coords;

void main(void){

    tex_coords = position * 0.5 + 0.5;
    
    gl_Position = projection * transformation * vec4(position,0.001,1.0);
    
        
	
}