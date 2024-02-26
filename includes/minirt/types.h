/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:34:20 by npirard           #+#    #+#             */
/*   Updated: 2024/02/26 14:41:54 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <libft.h>

typedef struct s_int2 {
	int		x;
	int		y;
}			t_int2;

typedef struct s_int3 {
	int		x;
	int		y;
	int		z;
}			t_int3;

typedef struct s_color {
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_double2 {
	double		x;
	double		y;
}				t_double2;

typedef struct s_double3 {
	double		x;
	double		y;
	double		z;
}				t_double3;

typedef struct s_color3f {
	double	r;
	double	g;
	double	b;
}				t_color3f;

typedef t_int2			t_vec2i;
typedef t_int3			t_vec3i;
typedef t_double2		t_vec2f;
typedef t_double3		t_vec3f;
typedef t_int2			t_coord2;
typedef t_int3			t_coord3;
typedef t_double2		t_coord2f;
typedef t_double3		t_coord3f;
typedef t_color3f		(*t_color_get)(void *, t_double3 *);

typedef struct s_matrix4f {
	double		m1[4];
	double		m2[4];
	double		m0[4];
	double		m3[4];
}				t_matrix4f;

typedef struct s_matrix3f {
	double		m0[3];
	double		m1[3];
	double		m2[3];
}				t_matrix3f;

typedef enum e_object_type
{
	CAMERA,
	AMBIANT,
	LIGHT,
	MOVE,
	SPHERE,
	PLAN,
	CYLINDER,
	CONE
}			t_object_type;

typedef enum e_ray_type
{
	CAMERA_RAY,
	LIGHT_RAY,
	REFLECT_RAY,
	REFRACT_RAY
}			t_ray_type;

typedef enum e_texture_type
{
	TEX_SOLID,
	TEX_DAM,
	TEX_IMG
}			t_texture_type;

typedef enum e_move_type
{
	MV_R,
	MV_Rs,
	MV_T,
	MV_S
}			t_move_type;

typedef struct s_texture {
	char				type;
	char				*file_path;
	void				*img;
	void				*img_addr;
	int					len_line;
	int					bbp;
	int					endian;
	int					width;
	int					height;
	t_color3f			color1;
	t_color3f			color2;
	int					resolution;
	t_color_get			get_color;
	struct s_data		*data;
}				t_texture;

/// @brief
/// @param color R,G,B in range [0-1] : 0, 0.5, 1.0
/// @param ratio in the range [0.0;1.0]
/// @param origin x,y,z coordinates of light position
/// @param _ambiant computed color values for ambiant light
typedef struct s_light {
	t_color3f	color;
	double		ratio;
	t_coord3f	origin;
	t_color3f	_color;
}				t_light;

/// @brief
/// ```_variables``` are updated when screen changes ratio.
/// @param _u horizontal pixel vector
/// @param _v vertical pixel vector
/// @param _c vector to reach center of the pixel
/// @param origin x,y,z coordinates of camera position
/// @param dir orientation vector (x,y,z) in range [-1.0;1.0]
/// @param _cz unit vector for camera up dimension
/// @param _cz unit vector for camera forward/backward dimension
/// @param _cy unit vector for camera left/right dimension
/// @param fov horizontal fov in range [0;180]
typedef struct s_camera {
	t_coord3f	_u;
	t_coord3f	_v;
	t_coord3f	_r;
	t_coord3f	origin;
	t_vec3f		dir;
	t_vec3f		_cz;
	t_vec3f		_cy;
	t_vec3f		_cx;
	int			fov;
}				t_camera;

/// @brief
/// @param ambiant_light has no origin coordinates
/// @param objects list of objects
/// @param lights list of light sources
typedef struct s_scene {
	t_camera			camera;
	t_matrix3f			matrix;
	t_light				ambiant_light;
	t_list				*objects;
	t_list				*lights;
	t_list				*moves;
	t_list				*lights_obj;
	struct s_data		*data;
}				t_scene;

typedef struct s_move {
	char				type;
	int					target;
	t_vec3f				value;
	double				speed;
}				t_move;

/// @brief
/// @param type type of object
/// @param origin x,y,z coordinates of center
/// @param diameter sphere or cylinder diameter
/// @param height height of the cylinder
/// @param color R,G,B in range [0-255] : 255, 255, 255
/// @param orientation Orientation of the object (x, y, z) in the range [-1;1]
/// For cylinders, correspond to its axis.
/// @param k_ambiant ambiant light reflexion constant (0 <= ka <= 1)
/// @param k_diffuse diffuse light reflexion constant (0 <= kd <= 1)
/// @param k_specular specular light reflexion constant (0 <= ks <= 1)
/// @param k_plastic portion of plastic reflexion on surface (0 <= p <= 1)
typedef struct s_object {
	int					id;
	char				type;
	t_coord3f			origin;
	t_coord3f			top;
	double				radius;
	double				height;
	t_color3f			color;
	t_vec3f				orientation;
	t_vec3f				loc_x;
	t_vec3f				loc_y;
	t_vec3f				loc_z;
	double				k_ambiant;
	double				k_diffuse;
	double				k_specular;
	double				k_plastic;
	double				k_roughness;
	double				k_reflexion;
	double				i_refraction;
	double				k_light;
	double				k_glow;
	t_color3f			color_light;
	t_color3f			_light;
	t_color3f			color_glow;
	t_color3f			_glow;
	t_texture			texture;
	double				angle;
	struct s_data		*data;
}				t_object;

typedef struct s_ray {
	t_coord3f	origin;
	t_vec3f		dir;
	t_coord3f	inter;
	t_vec3f		normal;
	t_vec3f		old_dir;
	double		t;
	double		theta;
	double		t_min;
	double		t_max;
	t_object	*inter_obj;
	t_object	*inside_obj;
	t_color3f	l_surface;
	t_color3f	l_diffuse;
	t_color3f	l_ambiant;
	t_color3f	l_specular;
	t_color3f	l_final;
	int			nbr_bounce;
	char		type;
}				t_ray;

void	print_t_double3(t_double3 *vec);
void	print_t_color3f(t_color3f *color);

#endif
