/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:44:30 by npirard           #+#    #+#             */
/*   Updated: 2024/02/26 13:41:50 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include <minirt/minirt.h>

t_ray		generate_ray(t_coord2f *pxl, t_data *data);
void		launch_ray(t_data *data, t_ray *ray);
void		check_luminosity(t_data *data, t_ray *ray);
void		check_inter(t_data *data, t_ray *ray);
void		check_lights(t_data *data, t_ray *ray);
void		check_light_obj(t_data *data, t_ray *ray);

t_color3f	get_refract_color(t_data *data, t_ray *previous_ray);
t_color3f	get_reflect_color(t_data *data, t_ray *previous_ray);

t_color3f	compute_lights(t_data *data, t_ray *ray, t_light *light);
void		compute_ambiant(t_ray *ray, t_color3f *ambiant_color);
t_color3f	compute_diffuse(t_ray *light_ray, t_color3f *light_color);
t_color3f	compute_specular(t_ray *light_ray, t_color3f *light_color);


#endif