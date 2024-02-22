/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_get2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:36:51 by npirard           #+#    #+#             */
/*   Updated: 2024/02/22 14:02:25 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>

t_color3f	texture_get_sphere_img(void *obj, t_double3 *coord)
{
	(void)coord;
	return (((t_object *)obj)->texture.color1);
}

t_color3f	texture_get_plan_img(void *obj, t_double3 *coord)
{
	(void)coord;
	return (((t_object *)obj)->texture.color1);
}

t_color3f	texture_get_cylinder_img(void *obj, t_double3 *coord)
{
	(void)coord;
	return (((t_object *)obj)->texture.color1);
}

t_color3f	texture_get_cone_img(void *obj, t_double3 *coord)
{
	(void)coord;
	return (((t_object *)obj)->texture.color1);
}
