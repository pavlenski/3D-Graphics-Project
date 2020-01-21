#version 330

in vec3 pass_normal;
in vec3 pass_position;
in float pass_visibility;

out vec4 final_colour;

uniform vec3 uni_object_colour;
uniform vec3 uni_light_colour;
uniform vec3 uni_light_direction;
uniform vec3 uni_camera_position;
uniform vec3 uni_sky_colour;

float ambient_factor = 0.16;

void main() {

    /* specular */

    vec3 view_vector = pass_position - uni_camera_position;

    view_vector = normalize(view_vector);
    vec3 neg_view_vector = -view_vector;

    vec3 reflected_light = reflect(normalize(uni_light_direction), normalize(pass_normal));

    float specular_factor = clamp(dot(reflected_light, neg_view_vector), 0, 1);
    specular_factor = pow(specular_factor, 10);

    vec3 specular_light = uni_light_colour * specular_factor;

    /* diffuse */

    float light_factor = clamp(dot(normalize(pass_normal), normalize(-uni_light_direction)), ambient_factor, 1.0);

    vec3 fcolour = specular_light +  (uni_object_colour * uni_light_colour * light_factor);

    //final_colour = mix( vec4(fcolour, 1.0), vec4(uni_sky_colour, 1.0), pass_visibility );
    final_colour = mix( vec4(uni_sky_colour, 1.0), vec4(fcolour, 1.0), pass_visibility );
    //final_colour = vec4(fcolour, 1.0f);

}