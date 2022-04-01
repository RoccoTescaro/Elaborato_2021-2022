uniform vec2 resolution;
uniform float radius;

void main(void){
    vec2 uv = gl_FragCoord.xy/resolution.xy;
    uv *= 1. - uv.yx;
    float vig = pow(uv.x*uv.y*radius*15.,.5*(1.-radius));
    gl_FragColor = vec4(0,0,0,1.-vig);
}