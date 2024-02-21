/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:15:19 by npirard           #+#    #+#             */
/*   Updated: 2024/02/21 17:45:59 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include <minirt/minirt.h>
# include <libft.h>
# include <limits.h>

/* -------------------------------------------------------------------------- */
/*                                STRUCT UTILS                                */
/* -------------------------------------------------------------------------- */

void	*t_scene_free(t_scene *scene);
void	t_object_init(t_object *obj);

/* ---------------------------------- PRINT --------------------------------- */

void	t_scene_print(t_scene *scene);
void	t_camera_print(t_camera *camera);
void	t_light_print(t_light *light);
void	t_object_print(t_object *object);

#endif