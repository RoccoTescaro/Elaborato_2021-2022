uniform sampler2D texture;
uniform float xoffset;


void main(void){
	vec2 uv = gl_FragCoord.xy;
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

	if(uv.x > xoffset){
		if(pixel.g > 0.5f) pixel.a = 0;
	}else{
		if(pixel.g > 0.25f && pixel.r+pixel.b < 0.25f) pixel.rgb = vec3(0.05f,0.025f,0.075f);
	}
	gl_FragColor = gl_Color*pixel;
}