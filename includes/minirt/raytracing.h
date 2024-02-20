/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:44:30 by npirard           #+#    #+#             */
/*   Updated: 2024/02/20 11:24:16 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include <minirt/minirt.h>

t_ray	generate_ray(t_coord2f *pxl, t_data *data);
void	launch_ray(t_data *data, t_ray *ray);
void	check_inter(t_data *data, t_ray *ray);
void	check_lights(t_data *data, t_ray *ray);

#endif