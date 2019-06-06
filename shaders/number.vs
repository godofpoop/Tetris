#version 150

in vec2 position;

uniform mat4 transformation;
uniform mat4 projection;
uniform int row;

out vec2 tex_coords;

void main(void){

    tex_coords = position * 0.5 + 0.5;
    tex_coords.x /= 10;
    tex_coords.x += row*(1.0 / 10.0);
	gl_Position = projection * transformation * vec4(position,0.0,1.0);
	
}