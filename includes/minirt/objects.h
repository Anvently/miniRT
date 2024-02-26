/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:15:19 by npirard           #+#    #+#             */
/*   Updated: 2024/02/26 13:46:29 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include <minirt/minirt.h>
# include <libft.h>
# include <limits.h>

/* -------------------------------------------------------------------------- */
/*                                   TEXTURE                                  */
/* -------------------------------------------------------------------------- */

t_texture	*texture_img_get(t_data *data, char *path);
t_color3f	texture_img_get_pxl(t_texture *texture, int x, int y);

t_color3f	texture_get_solid_color(void *obj, t_double3 *coord);
t_color3f	texture_get_sphere_dame(void *obj, t_double3 *coord);
t_color3f	texture_get_plan_dame(void *obj, t_double3 *coord);
t_color3f	texture_get_cylinder_dame(void *obj, t_double3 *coord);
t_color3f	texture_get_cone_dame(void *obj, t_double3 *coord);
t_color3f	texture_get_sphere_img(void *obj, t_double3 *coord);
t_color3f	texture_get_plan_img(void *obj, t_double3 *coord);
t_color3f	texture_get_cylinder_img(void *obj, t_double3 *coord);
t_color3f	texture_get_cone_img(void *obj, t_double3 *coord);

/* -------------------------------------------------------------------------- */
/*                                STRUCT UTILS                                */
/* -------------------------------------------------------------------------- */

void		*t_scene_free(t_scene *scene);
void		t_object_init(t_object *obj);
void		t_texture_free(void *texture_ptr);

/* ---------------------------------- PRINT --------------------------------- */

void		t_scene_print(t_scene *scene);
void		t_camera_print(void *camera_ptr);
void		t_light_print(void *light_ptr);
void		t_texture_print(t_texture *texture);
void		t_object_properties_print(t_object *obj);
void		t_object_print(void *object_ptr);
void		t_move_print(void *move_ptr);

#endif