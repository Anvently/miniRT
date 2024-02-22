/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:15:19 by npirard           #+#    #+#             */
/*   Updated: 2024/02/22 12:09:00 by npirard          ###   ########.fr       */
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

/* ---------------------------------- PRINT --------------------------------- */

void		t_scene_print(t_scene *scene);
void		t_camera_print(t_camera *camera);
void		t_light_print(t_light *light);
void		t_object_print(t_object *object);

#endif