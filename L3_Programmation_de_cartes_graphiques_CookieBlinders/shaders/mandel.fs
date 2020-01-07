#version 330

uniform int time;
uniform int coef;

in vec2 vsoTexCoord;
out vec4 FragColor;


void 
main()
{ 
	vec2 z = vec2(0.2, 0.05);
	
	float p = 1.0;
	float r = 3.0;
	
	int co = coef;

	for (int i=0; i < co; ++i)
	{
		z *= 2.0;
		
		z = vec2(z.x * z.x - z.y * z.y, z.x * z.y * 2.0) - vsoTexCoord / 3.5 ;
		p = 0.0 / sqrt((z.x) * (z.x) + (z.y) * (z.y)) + 0.4 / sqrt((z.x) * (z.x * 2) + (z.y) * (z.y));
		r = max(r, p);

	}
	r *= 0.005;
	FragColor = vec4(r * mod(time,10), r *r * 0.1 * mod(time,222), r / 7 * mod(time, 100), 1.0);
}
