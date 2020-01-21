#version 330

layout (location = 0) in vec2 position;
layout (location = 1) in vec4 indicators;

out float pass_visibility;
out vec3 pass_normal;
out vec3 pass_world_position;
out vec4 pass_clip_space_real;
out vec4 pass_clip_space_grid;

uniform mat4 uni_M;
uniform mat4 uni_V;
uniform mat4 uni_P;
uniform float uni_y_offset;
uniform float uni_wave_time;
uniform float uni_wave_type;

const float density = 0.006;
const float gradient = 1.5;

const float PI = 3.1415926535897932384626433832795;
const float wave_length = 10;
const float wave_amplitude = 0.45;

float offset( float x, float z, float val1, float val2 ) {

    float rad_x, rad_z;

    if(uni_wave_type < 0.5)
    {
        rad_x = ( x / wave_length + uni_wave_time ) * 2.0 * PI;
        rad_z = ( z / wave_length + uni_wave_time ) * 2.0 * PI;
    } 
    else 
    {
        rad_x = ( ( mod( x + z * x * val1 , wave_length ) / wave_length ) + uni_wave_time * mod( x * 0.8 + z, 1.5 ) ) * 2.0 * PI;
        rad_z = ( ( mod( val2 * ( z * x + x * z ) , wave_length ) / wave_length ) + uni_wave_time * 2.0 * mod( x , 2.0 ) ) * 2.0 * PI;
    }

    return wave_amplitude * 0.5 * ( sin(rad_z) + cos(rad_x) );
}

vec3 distort( vec3 vertex ) {

    float x = offset( vertex.x, vertex.z, 1, 2 );
    float y = offset( vertex.x, vertex.z, 2, 1 );
    float z = offset( vertex.x, vertex.z, 2, 2 );
    return vertex + vec3( x, y, z );
}

vec3 calculate_normal( vec3 current_v, vec3 v1, vec3 v2 ) {
    vec3 tangent   = v1 - current_v;
    vec3 bitangent = v2 - current_v;
    return normalize( cross( tangent, bitangent ) );
}

void main() {

    mat4 view_projection_mat = uni_P * uni_V;

    vec3 current_vertex = vec3(position.x, uni_y_offset, position.y);
    // current_vertex = current_vertex + vec3( indicators.z, 0, indicators.w );
    // current_vertex = vec3( indicators.x, uni_y_offset, indicators.y );
    vec3 vertex1 = vec3( indicators.x , uni_y_offset, indicators.y  );
    vec3 vertex2 = vec3( indicators.z , uni_y_offset, indicators.w  );
    //current_vertex = vec3( indicators.z, uni_y_offset, indicators.w );

    pass_clip_space_grid = uni_M * vec4( current_vertex, 1.0 );
    pass_clip_space_grid = view_projection_mat * pass_clip_space_grid;

    vertex1 = distort(vertex1);
    vertex2 = distort(vertex2);
    current_vertex = distort( current_vertex );
    
    pass_normal = calculate_normal( current_vertex, vertex1, vertex2 );
    //pass_normal = vec3(0, 1, 0);

    vec4 world_position = uni_M * vec4( current_vertex, 1.0 );

    pass_world_position = world_position.xyz;
    pass_clip_space_real = view_projection_mat * world_position;
    gl_Position = pass_clip_space_real;


    vec4 position_relative_to_camera = uni_V * world_position;
    float distance = length(position_relative_to_camera.xyz);
    pass_visibility = exp( -pow( ( distance * density ), gradient) );
    pass_visibility = clamp( pass_visibility, 0.0, 1.0 );


}