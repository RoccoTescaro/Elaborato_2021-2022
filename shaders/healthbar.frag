uniform sampler2D texture;
uniform sampler2D filterTexture;
uniform vec4 rect;
uniform vec2 resolution;
uniform float maxValue;
uniform float value;
uniform vec4 color;
uniform vec4 replacedColor;
uniform float threshold;

void main(void){
	vec2 coord = gl_TexCoord[0].xy;
	vec4 txtColor = texture2D(texture, coord);
	vec4 txtFilterColor = texture2D(filterTexture, coord);
	vec4 finalColor = txtColor;
	
	vec4 nRect = vec4(rect.x/resolution.x, rect.y/resolution.y, rect.z/resolution.x, rect.w/resolution.y);

	if(coord.x > nRect.x && coord.x < nRect.z && coord.y*(1-value/maxValue) > nRect.y && coord.y < nRect.w)
		if(distance(txtColor,replacedColor) < threshold && distance(txtFilterColor,vec4(0.0,0.0,1.0,1.0)) <= .01)
		{ 
			finalColor = color;
		}

	gl_FragColor = finalColor;
}