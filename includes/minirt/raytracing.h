/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:44:30 by npirard           #+#    #+#             */
/*   Updated: 2024/02/15 11:47:31 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include <minirt/minirt.h>

void	generate_rays(t_data *data);
t_ray	generate_ray(t_coord2 *pxl, t_data *data);
t_color	get_ray_color(t_ray *ray);

#endif