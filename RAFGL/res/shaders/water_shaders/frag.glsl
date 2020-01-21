#version 330

in float pass_visibility;
in vec3 pass_normal;
in vec3 pass_world_position;
in vec4 pass_clip_space_real;
in vec4 pass_clip_space_grid;

out vec4 final_colour;

uniform vec3 uni_light_colour;
uniform vec3 uni_light_direction;
uniform vec3 uni_sky_colour;
uniform vec3 uni_camera_position;

uniform sampler2D uni_reflection_tex;
uniform sampler2D uni_refraction_tex;
uniform sampler2D uni_depth_tex;

vec3 uni_object_colour = vec3( 0, 0, 1 );

float ambient_factor = 0.16;

float calculate_fresnel() {
    vec3 view_vector = normalize( pass_world_position - uni_camera_position );
    vec3 neg_view_vector = -view_vector;
    vec3 normalized_normal = normalize( pass_normal );
    float fresnel = dot( neg_view_vector, normalized_normal );
    fresnel = clamp( fresnel, 0.0, 1.0 );
    return fresnel;
}

void main() {

    vec2 ndc = ( pass_clip_space_real.xy / pass_clip_space_real.w ) / 2 + 0.5;
    vec2 ndc_grid = ( pass_clip_space_grid.xy / pass_clip_space_grid.w ) / 2 + 0.5;
    ndc_grid = clamp( ndc_grid, 0.002, 0.998 );

    vec2 reflect_uv = vec2(ndc_grid.x, 1 - ndc_grid.y);
    vec2 refract_uv = vec2(ndc_grid.x, ndc_grid.y);
    vec3 reflect_colour = texture( uni_reflection_tex, reflect_uv ).rgb;
    vec3 refract_colour = texture( uni_refraction_tex, refract_uv ).rgb;

    // float near = 0.1;
    // float far = 1000.0;
    // float depth = texture( uni_depth_tex, refract_uv ).r;
    // float floor_distance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));

    // depth = gl_FragCoord.z;
    // float water_distance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
    // float water_depth = floor_distance - water_distance;

    float light_factor = clamp(dot(normalize(pass_normal), normalize(-uni_light_direction)), ambient_factor, 1.0);

    vec3 view_vector = pass_world_position - uni_camera_position;

    view_vector = normalize(view_vector);
    vec3 neg_view_vector = -view_vector;

    vec3 reflected_light = reflect(normalize(uni_light_direction), normalize(pass_normal));

    float specular_factor = clamp(dot(reflected_light, neg_view_vector), 0, 1);
    specular_factor = pow(specular_factor, 12);

    vec3 specular_light = uni_light_colour * specular_factor;

    //vec3 fcolour = (total_colour.xyz * uni_light_colour * light_factor);

    
    vec3 water_colour = vec3(0.3, 0.6, 0.9);
    reflect_colour = mix(reflect_colour, water_colour, 0.6);
    refract_colour = mix(refract_colour, water_colour, 0.2);

    vec3 f_colour = mix(reflect_colour, refract_colour, calculate_fresnel() );
    f_colour = f_colour * ( (uni_light_colour * light_factor * 2.3) ) + ( specular_light * 0.4 );
    // f_colour = (f_colour * uni_light_colour * light_factor);
    // vec3 fcolour = mix(f_colour, water_colour, 0.2);

    final_colour = mix( vec4(uni_sky_colour, 1.0), vec4(f_colour, 1.0), pass_visibility );

    
    /* OVDE JE PLAVI PLANE */
    // final_colour = vec4( uni_object_colour, 1 );
    
    

    //final_colour = vec4(water_depth / 50.0);


}