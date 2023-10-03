#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
flat in vec3 NormalFlat;

in vec3 FragPos;
in vec3 crntPos;

uniform sampler2D tex0;

uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec3 camPos;

uniform float aAmbient;
uniform float aSpecular;
uniform float pointSize;
uniform sampler2D circle;

uniform bool isTexture;
uniform bool isRoundPoint;
uniform bool isDiffuse;
uniform bool isPhong;
uniform bool isCarcass;
uniform bool isStripple;
uniform bool isFlatShade;

uniform vec2  u_resolution;
uniform float u_dashSize;
uniform float u_gapSize;

vec3 Diffuse() {
    vec3 normal;
    if (isFlatShade)
      normal = normalize(NormalFlat);
    else
      normal = normalize(Normal);
     vec3 lightDirection = normalize(lightPos - FragPos);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;
    return diffuse;
}

vec3 Ambient() {
    float ambientStrenght = aAmbient;
    vec3 ambient = ambientStrenght * lightColor;
    return ambient;
}

vec3 Specular() {
    vec3 normal;
    if (isFlatShade)
      normal = normalize(NormalFlat);
    else
      normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - FragPos);
    float specularStrenght = aSpecular;
    vec3 viewDirection = normalize(camPos - FragPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 32);
    vec3 specular = specularStrenght * specAmount * lightColor;
    return specular;
}

void IsStripple() {
    // Calculate the distance from the center of the screen
    float dist = length(gl_FragCoord.xy - u_resolution * 0.5);

    // Control the dash size and gap size
    float dashSize = u_dashSize;
    float gapSize = u_gapSize;

    // Create the dashed effect by discarding fragments outside the dash and gap regions
    if (fract(dist / (dashSize + gapSize)) > dashSize / (dashSize + gapSize))
        discard;
}

void main()
{
vec2 coord = gl_PointCoord - vec2(0.5);
 if(isRoundPoint && length(coord) > 0.5)
discard;

     vec3 result;

// light mode
vec4 texColor = isTexture ? texture(tex0, texCoord) : vec4(color, 1.0);

if (isDiffuse && !isCarcass) { result = (Diffuse() + Ambient()) * texColor.rgb;}
if (isPhong && !isCarcass) { result = (Diffuse() + Ambient() + Specular()) * texColor.rgb;}
if (isCarcass) { result = texColor.rgb; }

if (isStripple) {
    IsStripple();
}

FragColor = vec4(result, 1.0f);

}