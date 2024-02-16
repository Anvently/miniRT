/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:34:20 by npirard           #+#    #+#             */
/*   Updated: 2024/02/16 17:30:08 by npirard          ###   ########.fr       */
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

typedef t_int2		t_vec2i;
typedef t_int3		t_vec3i;
typedef t_double2	t_vec2f;
typedef t_double3	t_vec3f;
typedef t_int2		t_coord2;
typedef t_int3		t_coord3;
typedef t_double2	t_coord2f;
typedef t_double3	t_coord3f;

typedef struct s_ray {
	t_coord3f	origin;
	t_vec3f		dir;
	t_coord3f	inter;
	t_vec3f		normal;
	double		t;
	t_color		color;
}				t_ray;

typedef enum e_object_type
{
	CAMERA,
	AMBIANT,
	LIGHT,
	SPHERE,
	PLAN,
	CYLINDER
}			t_object_type;

/// @brief
/// @param color R,G,B in range [0-255] : 255, 255, 255
/// @param ratio in the range [0.0;1.0]
/// @param origin x,y,z coordinates of light position
typedef struct s_light {
	t_color		color;
	double		ratio;
	t_coord3f	origin;
}				t_light;

/// @brief
/// ```_variables``` are updated when screen changes ratio.
/// @param _u horizontal pixel vector
/// @param _v vertical pixel vector
/// @param _c vector to reach center of the pixel
/// @param origin x,y,z coordinates of camera position
/// @param dir orientation vector (x,y,z) in range [-1.0;1.0]
/// @param cy unit vector for camera up dimension
/// @param cx unit vector for camera left/right dimension
/// @param fov horizontal fov in range [0;180]
typedef struct s_camera {
	t_coord3f	_u;
	t_coord3f	_v;
	t_coord3f	_r;
	t_coord3f	origin;
	t_vec3f		dir;
	t_vec3f		cy;
	t_vec3f		cx;
	int			fov;
}				t_camera;

/// @brief
/// @param ambiant_light has no origin coordinates
/// @param objects list of objects
/// @param lights list of light sources
typedef struct s_scene {
	t_camera	camera;
	t_light		ambiant_light;
	t_list		*objects;
	t_list		*lights;
}				t_scene;

/// @brief
/// @param type type of object
/// @param origin x,y,z coordinates of center
/// @param diameter sphere or cylinder diameter
/// @param height height of the cylinder
/// @param color R,G,B in range [0-255] : 255, 255, 255
/// @param orientation Orientation of the object (x, y, z) in the range [-1;1]
/// For cylinders, correspond to its axis.
typedef struct s_object {
	char		type;
	t_coord3f	origin;
	t_coord3f	top;
	double		radius;
	double		height;
	t_color		color;
	t_vec3f		orientation;
}				t_object;

void	print_t_double3(t_double3 *vec);

#endif
