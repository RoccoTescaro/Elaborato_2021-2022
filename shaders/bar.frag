uniform sampler2D texture;
uniform vec2 dir;
uniform vec4 rect;
uniform float maxValue;
uniform float value;
uniform vec4 color;
uniform vec4 replacedColor;
uniform float threshold;


void func(){
	vec2 center = vec2(abs(rect.x-rect.z)/2.f,abs(rect.y-rect.w)/2.f);
	float radius = max(dist(center,rect.xy),dist(center,rect.zw));
	vec2 startingPoint = center-dir*radius;

	

}


void main(void){
	vec2 coord = gl_TexCoord[0].xy;
	vec4 pixelColor = texture2D(texture, coord);

	if(coord.x > rect.x && coord.y > rect.y && coord.x < rect.z && coord.y < rect.w )
	{ //pixel is inside the rect
		if(distance(pixelColor,replacedColor) < threshold)
		{ //pixel has the right color to be replaced
			if()

		}
	}


	if(uv.x > rect.x && uv.y > rect.y uv.y < rect.y){
		if(pixel.g > 0.5f) pixel.a = 0;
	}else{
		if(pixel.g > 0.25f && pixel.r+pixel.b < 0.25f) pixel.rgb = vec3(0.05f,0.025f,0.075f);
	}
	gl_FragColor = gl_Color*pixelColor;
}