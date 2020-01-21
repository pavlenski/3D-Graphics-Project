#version 330

in vec3 pass_normal;
in vec3 pass_position;
in vec2 pass_uv;
in float pass_visibility;

out vec4 final_colour;

// uniform vec3 uni_object_colour;
uniform vec3 uni_light_colour;
uniform vec3 uni_light_direction;
uniform vec3 uni_camera_position;
uniform vec3 uni_object_colour;
uniform vec3 uni_sky_colour;

float ambient_factor = 0.16;

uniform sampler2D uni_background_texture;
uniform sampler2D uni_r_texture;
uniform sampler2D uni_g_texture;
uniform sampler2D uni_blend_map;

uniform float uni_reflection_flag;
uniform float uni_refraction_flag;
// uniform sampler2D uni_b_texture;

void main() {

    if(pass_position.y < -2.05 && uni_reflection_flag > 0.5)
	{
		discard;
	}
	
	if(pass_position.y > -1.3 && uni_refraction_flag > 0.5)
	{
		discard;
	}

    /* textures */

    vec2 tiled_uv = pass_uv * 6.0f;

    // vec4 blend_map_colour = texture(uni_blend_map, pass_uv);
    // //float texture_factor = 1 - (blend_map_colour.r + blend_map_colour.g + blend_map_colour.b);
    // float texture_factor = 1 - blend_map_colour.r;
    // vec4 background_tex_colour = texture(uni_background_texture, tiled_uv) * texture_factor;
    // vec4 r_tex_colour = texture(uni_r_texture, tiled_uv) * blend_map_colour.r;
    // vec4 total_colour = background_tex_colour + r_tex_colour;

    vec4 total_colour;

    //vec4 albedo_colour = texture(uni_background_texture, tiled_uv);

    // total_colour = lerp_textures(tiled_uv);

    float tex_factor;

    if(pass_position.y < -1.5) {

        total_colour = total_colour = texture(uni_background_texture, tiled_uv);
    } else if(pass_position.y > -1.5 && pass_position.y < 0.5) {

        tex_factor = pass_position.y + 1.5;
        tex_factor /= 2;
        total_colour = mix( texture(uni_background_texture, tiled_uv), texture(uni_r_texture, tiled_uv), tex_factor );
    } else if(pass_position.y > 0.5 && pass_position.y <= 3.5) {

        total_colour = texture(uni_r_texture, tiled_uv);
    } else if(pass_position.y > 3.5 && pass_position.y < 4.5) {

        tex_factor = pass_position.y - 3.5;
        tex_factor /= 1;
        total_colour = mix( texture(uni_r_texture, tiled_uv), texture(uni_g_texture, tiled_uv), tex_factor );
    } else if(pass_position.y >= 4.5) {
        
        total_colour = texture(uni_g_texture, tiled_uv);
    }

    /* specular */

    /* diffuse */

    float light_factor = clamp(dot(normalize(pass_normal), normalize(-uni_light_direction)), ambient_factor, 1.0);

    vec3 fcolour = (total_colour.xyz * uni_light_colour * light_factor);

    final_colour = mix( vec4(uni_sky_colour, 1.0), vec4(fcolour, 1.0), pass_visibility );
    
    // final_colour = vec4(fcolour, 1.0f);

    //albedo_colour = vec4(  );


    
    //final_colour = vec4(uni_object_colour, 1.0f);

}