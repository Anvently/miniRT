/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:43:56 by npirard           #+#    #+#             */
/*   Updated: 2024/02/19 12:36:41 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/raytracing.h>
#include <minirt/calculus.h>
#include <math.h>

void	init_camera(t_data *data)
{
	data->scene.camera._cx = (t_vec3f){1.0, 0.0, 0.0};
	data->scene.camera._cy = (t_vec3f){0.0, 1.0, 0.0};
	data->scene.camera._cz = (t_vec3f){0.0, 0.0, 1.0};
	img_update_camera(data);
}

void	img_update_camera(t_data *data)
{
	double	screen_w;
	double	screen_h;

	screen_w = 2.0 * tan((double) data->scene.camera.fov / 2.0);
	screen_h = screen_w * data->img_ratio;
	data->scene.camera._u = vec3_scale(&data->scene.camera._cy,
			-screen_w / (double) data->img_size.x);
	data->scene.camera._v = vec3_scale(&data->scene.camera._cz,
			-screen_h / (double) data->img_size.y);
	data->scene.camera._r.x = ((double) data->img_size.x / 2.0)
		* -data->scene.camera._u.x + ((double) data->img_size.y / 2.0)
		* -data->scene.camera._v.x;
	data->scene.camera._r.y = ((double) data->img_size.x / 2.0)
		* -data->scene.camera._u.y + ((double) data->img_size.y / 2.0)
		* -data->scene.camera._v.y;
	data->scene.camera._r.z = ((double) data->img_size.x / 2.0)
		* -data->scene.camera._u.z + ((double) data->img_size.y / 2.0)
		* -data->scene.camera._v.z;
	// printf("cx.x=%f, cx.y=%f, cx.z=%f\n", data->scene.camera._cx.x, data->scene.camera._cx.y,
	// 	data->scene.camera._cx.z);
	// printf("cy.x=%f, cy.y=%f, cy.z=%f\n", data->scene.camera._cy.x, data->scene.camera._cy.y,
	// 	data->scene.camera._cy.z);
	// printf("cz.x=%f, cz.y=%f, cz.z=%f\n", data->scene.camera._cz.x, data->scene.camera._cz.y,
	// 	data->scene.camera._cz.z);
	// printf("ux=%f, uy=%f, uz=%f\n", data->scene.camera._u.x, data->scene.camera._u.y,
	// 	data->scene.camera._u.z);
	// printf("vx=%f, vy=%f, vz=%f\n", data->scene.camera._v.x, data->scene.camera._v.y,
	// 	data->scene.camera._v.z);
	// printf("cx=%f, cz=%f, cz=%f\n", data->scene.camera._r.x, data->scene.camera._r.y,
	// 	data->scene.camera._r.z);
}
