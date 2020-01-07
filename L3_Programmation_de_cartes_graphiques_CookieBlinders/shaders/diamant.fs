#version 330
uniform mat4 modelViewMatrix;
uniform int disco;
uniform float gap;
uniform int temps;
uniform sampler2D tex0;
in  vec3 vsoNormal;
in  vec2 vsoTexCoord;
in  vec3 vsoModPos;
out vec4 fragColor;

#define PI 3.14159265359

void main(void) {
  float diffuse = 0, spec = 0;
  vec4 color = texture(tex0, vsoTexCoord);
  vec2 pos = abs(2.0 * (vsoTexCoord.xy) - vec2(1));
  float a = atan(pos.x/2, pos.y/2);
  float r = dot(pos/2, pos/2) * .8;
  vec4 c = vec4(sin(PI * mod(0.2 * temps/100 + r * 1.0 / 0.3 + gap, 0.8)), 1.9, 3.0, 1.0);

  vec4 t = mix(c, color, smoothstep(0.05, .4, r));
	fragColor = t * color;

	if(disco == 0)
		fragColor = color;
}
