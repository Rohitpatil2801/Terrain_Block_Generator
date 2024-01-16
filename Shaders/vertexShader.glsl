attribute highp vec4 posAttr;
attribute lowp vec4 colAttr;
attribute highp vec4 normalAttr;

varying lowp vec4 col;
varying highp vec3 normal;
varying highp vec3 fragPos;  

uniform highp mat4 matrix_proj;
uniform highp mat4 matrix_view;
uniform highp mat4 matrix_model;

void main() {
    col = colAttr;

    normal = normalize((matrix_model * normalAttr).xyz);

    fragPos = posAttr.xyz;  

    gl_Position = matrix_proj * matrix_model * matrix_view * posAttr;
}