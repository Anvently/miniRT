/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:36:51 by npirard           #+#    #+#             */
/*   Updated: 2024/02/22 15:33:52 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>

t_color3f	texture_get_solid_color(void *obj, t_double3 *coord)
{
	(void)coord;
	return (((t_object *)obj)->texture.color1);
}

t_color3f	texture_get_sphere_dame(void *obj, t_double3 *coord)
{
	(void)coord;
	return (((t_object *)obj)->texture.color1);
}

t_color3f	texture_get_plan_dame(void *obj, t_double3 *coord)
{
	(void)coord;
	return (((t_object *)obj)->texture.color1);
}

t_color3f	texture_get_cylinder_dame(void *obj, t_double3 *coord)
{
	(void)coord;
	return (((t_object *)obj)->texture.color1);
}

t_color3f	texture_get_cone_dame(void *obj, t_double3 *coord)
{
	(void)coord;
	return (((t_object *)obj)->texture.color1);
}
