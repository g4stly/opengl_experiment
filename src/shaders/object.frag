#version 330 core

in vec3 normal;
in vec3 fragPos;
out vec4 fragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform mat4 view;

void main()
{
	// ambient 
	float ambientStr = 0.4;
	vec3 ambient = ambientStr * lightColor;

	// diffuse
	vec3 viewedLightPos = vec3(view * vec4(lightPos, 1));
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(viewedLightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// specular
	float specularStr = 0.8;
	vec3 viewDir = normalize(fragPos);	
	vec3 reflectDir = reflect(lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0), 32);
	vec3 specular = specularStr * spec * lightColor;

	vec3 result = (ambient + diffuse + specular);
	fragColor = vec4(result * objectColor, 1);
}
