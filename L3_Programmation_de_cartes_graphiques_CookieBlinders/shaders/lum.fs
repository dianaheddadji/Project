#version 330

uniform int time;
uniform int coef;
uniform int resx;
uniform int resy;

in vec2 vsoTexCoord;
out vec4 FragColor;

vec2 res = vec2(resx, resy);

void 
main() 
{

	vec2 position = (gl_FragCoord.xy * 2 -  res) / min(res.x, res.y);
	vec3 destColor = vec3(0.2, 0.06, 0.005 * time/10000);
	float f = 0.0;
	
	for(float i = 0.0; i < 50.0; i++){
		
		float u = 0.02 * -sin(0.1 * time + i ) ;
		float d = 0.02 * -cos(0.1 * time + i );
		f += 0.2 / abs(length(22.0* position * f - vec2(d, u)) - (0.002 * coef));

	FragColor = vec4(vec3(destColor * f), 1.0);
  }
}
