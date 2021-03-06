#version 330 

uniform sampler2D uniformParticleTexture;

// uniform float uniformParticleDistanceMax;

in vec2 passUVCoords;
in float passDistance;

out vec4 fragmentColor;

void main() {
	fragmentColor  = texture2D(uniformParticleTexture, passUVCoords);
	float distance = - passDistance;
	float maxDistance = 3.0;

	float alpha =  1.0 - pow( max ( min( (distance / maxDistance), 1.0 ), 0.0 ), 5);
    fragmentColor.w  = max( fragmentColor.w * alpha, 0.0 );
}