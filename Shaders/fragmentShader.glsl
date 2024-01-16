varying lowp vec4 col;
varying highp vec3 normal;
varying highp vec3 fragPos;

void main() {
    highp vec3 lightDir = normalize(vec3(200,200,10) - fragPos);

    highp float diffuse = max(dot(normal, lightDir), 0.0);
    
    highp vec3 lighting = vec3(0.2, 1.0, 0.0);
    
    highp vec3 resultColor =clamp(0.3 * lighting + 0.8 * diffuse * lighting, 0.0, 1.0);

    gl_FragColor = vec4(resultColor,1.0);
}