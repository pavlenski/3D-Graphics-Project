#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec3 pass_normal;
out vec3 pass_position;
out float pass_visibility;

uniform mat4 uni_M;
uniform mat4 uni_V;
uniform mat4 uni_P;

const float density = 0.006;
const float gradient = 1.5;

void main() {

    mat4 view_projection_mat = uni_P * uni_V;
    vec4 world_position = uni_M * vec4(position, 1.0);
    gl_Position = view_projection_mat * world_position;

    vec4 position_relative_to_camera = uni_V * world_position;
    float distance = length(position_relative_to_camera.xyz);

    pass_visibility = exp( -pow( ( distance * density ), gradient) );
    pass_visibility = clamp( pass_visibility, 0.0, 1.0 );

    pass_normal = (uni_M * vec4(normal, 0.0)).xyz;
    pass_position = world_position.xyz;

}