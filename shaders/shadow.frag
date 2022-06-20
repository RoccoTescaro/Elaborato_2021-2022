#version 330
uniform sampler2D texture;
uniform vec2 resolution;
uniform float[1000] map;
uniform vec2 size;


float getMap(int x, int y)
{   
    int index = x + y * int(resolution.x);
    return map[index];
}

void main(void){
    vec2 uv = gl_FragCoord.xy;
    vec4 pixel = texture2D(texture,uv).rgba;

    if(pixel.g != 1. && getMap(int(uv.x),int(uv.y)) == 1.)
        gl_FragColor = vec4(1.,0.,0.,1.);
    else
        gl_FragColor = vec4(0.,0.,0.,1.);
}