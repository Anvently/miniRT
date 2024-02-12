/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:15:19 by npirard           #+#    #+#             */
/*   Updated: 2024/02/12 18:25:12 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include <minirt/minirt.h>
# include <libft.h>

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
	float		ratio;
	t_coord3f	origin;
}				t_light;

/// @brief
/// @param origin x,y,z coordinates of camera position
/// @param dir orientation vector (x,y,z) in range [-1.0;1.0]
/// @param fov horizontal fov in range [0;180]
typedef struct s_camera {
	t_coord3f	origin;
	t_vec3f		dir;
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
/// @param id type of object
/// @param origin x,y,z coordinates of center
/// @param diameter sphere or cylinder diameter
/// @param height height of the cylinder
/// @param color R,G,B in range [0-255] : 255, 255, 255
/// @param orientation Orientation of the object (x, y, z) in the range [-1;1]
/// For cylinders, correspond to its axis.
typedef struct s_object {
	char		id;
	t_coord3f	origin;
	float		diameter;
	float		height;
	t_color		color;
	t_vec3f		orientation;
}				t_object;

/* -------------------------------------------------------------------------- */
/*                                STRUCT UTILS                                */
/* -------------------------------------------------------------------------- */

void	*t_scene_free(t_scene **scene);

#endif