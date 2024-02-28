/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:29:45 by npirard           #+#    #+#             */
/*   Updated: 2024/02/28 10:44:54 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <minirt/raytracing.h>

static double	get_spec_ratio(t_ray *ray)
{
	double	ratio;
	t_vec3f	reflect;

	reflect.x = -ray->dir.x + 2.f * (ray->theta) * ray->normal.x;
	reflect.y = -ray->dir.y + 2.f * (ray->theta) * ray->normal.y;
	reflect.z = -ray->dir.z + 2.f * (ray->theta) * ray->normal.z;
	normalize_vec(&reflect);
	ratio = scalar_product(&reflect, &(t_vec3f){-ray->old_dir.x,
			-ray->old_dir.y, -ray->old_dir.z});
	if (ratio < 0.0)
		return (0.0);
	ratio = pow(ratio, ray->inter_obj->k_roughness);
	return (ratio);
}

t_color3f	compute_specular(t_ray *light_ray, t_color3f *light_color)
{
	t_color3f	l_specular;
	double		ratio;

	ratio = get_spec_ratio(light_ray);
	l_specular.r = light_color->r * light_ray->inter_obj->k_specular \
		* ratio * ((1 - light_ray->inter_obj->k_plastic) \
			* light_ray->l_surface.r + light_ray->inter_obj->k_plastic);
	l_specular.g = light_color->g * light_ray->inter_obj->k_specular \
		* ratio * ((1 - light_ray->inter_obj->k_plastic) \
			* light_ray->l_surface.g + light_ray->inter_obj->k_plastic);
	l_specular.b = light_color->b * light_ray->inter_obj->k_specular \
		* ratio * ((1 - light_ray->inter_obj->k_plastic) \
			* light_ray->l_surface.b + light_ray->inter_obj->k_plastic);
	return (l_specular);
}

t_color3f	compute_diffuse(t_ray *light_ray, t_color3f *light_color)
{
	t_color3f	l_diffuse;

	l_diffuse.r = light_color->r * light_ray->theta \
		* light_ray->l_surface.r * light_ray->inter_obj->k_diffuse;
	l_diffuse.g = light_color->g * light_ray->theta \
		* light_ray->l_surface.g * light_ray->inter_obj->k_diffuse;
	l_diffuse.b = light_color->b * light_ray->theta \
		* light_ray->l_surface.b * light_ray->inter_obj->k_diffuse;
	return (l_diffuse);
}

void	compute_ambiant(t_ray *ray, t_color3f *ambiant_color)
{
	ray->l_final.r = ray->l_surface.r * ray->inter_obj->k_ambiant
		* ambiant_color->r;
	ray->l_final.g = ray->l_surface.g * ray->inter_obj->k_ambiant
		* ambiant_color->g;
	ray->l_final.b = ray->l_surface.b * ray->inter_obj->k_ambiant
		* ambiant_color->b;
}
