uniform vec2 resolution;
uniform float time;
const float intensity = 1.25;
const float pulseAmpl = 0.5;

void main(void){
    vec2 uv = gl_FragCoord.xy/resolution.xy;
    uv *= 1. - uv.yx;
    float vig = pow(uv.x*uv.y*15.,intensity-abs(sin(time))*pulseAmpl);
    gl_FragColor = vec4(0,0,0,1.-vig);
}