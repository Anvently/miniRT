/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:43:56 by npirard           #+#    #+#             */
/*   Updated: 2024/02/16 18:59:27 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/raytracing.h>
#include <minirt/calculus.h>
#include <math.h>

static t_vec3f	find_cy(t_vec3f *dir)
{
	t_vec3f	cy;

	cy.z = dir->z;
	cy.x = 1.0;
	cy.y = (-dir->x * cy.x - dir->z * cy.z) / dir->y;
	normalize_vec(&cy);
	return (cy);
}

void	img_update_camera(t_data *data)
{
	double	screen_w;
	double	screen_h;

	screen_w = 2.0 * tan((double) data->scene.camera.fov / 2.0);
	screen_h = screen_w * data->img_ratio;
	normalize_vec(&data->scene.camera.dir);
	data->scene.camera.cy = find_cy(&data->scene.camera.dir);
	data->scene.camera.cx = vector_product(&data->scene.camera.dir,
			&data->scene.camera.cy);
	normalize_vec(&data->scene.camera.cx);
	data->scene.camera._u = vec3_scale(&data->scene.camera.cx,
			screen_w / (double) data->img_size.x);
	data->scene.camera._v = vec3_scale(&data->scene.camera.cy,
			screen_h / (double) data->img_size.y);
	data->scene.camera._r.x = (-screen_w / 2.0) * data->scene.camera._u.x
		- (screen_h / 2.0) * data->scene.camera._v.x;
	data->scene.camera._r.y = (-screen_w / 2.0) * data->scene.camera._u.y
		- (screen_h / 2.0) * data->scene.camera._v.y;
	data->scene.camera._r.z = (-screen_w / 2.0) * data->scene.camera._u.z
		- (screen_h / 2.0) * data->scene.camera._v.z;
	// printf("dir.x=%f, dir.y=%f, dir.z=%f\n", data->scene.camera.dir.x, data->scene.camera.dir.y,
	// 	data->scene.camera.dir.z);
	// printf("cx.x=%f, cx.y=%f, cx.z=%f\n", data->scene.camera.cx.x, data->scene.camera.cx.y,
	// 	data->scene.camera.cx.z);
	// printf("cy.x=%f, cy.y=%f, cy.z=%f\n", data->scene.camera.cy.x, data->scene.camera.cy.y,
	// 	data->scene.camera.cy.z);
	// printf("ux=%f, uy=%f, uz=%f\n", data->scene.camera._u.x, data->scene.camera._u.y,
	// 	data->scene.camera._u.z);
	// printf("vx=%f, vy=%f, vz=%f\n", data->scene.camera._v.x, data->scene.camera._v.y,
	// 	data->scene.camera._v.z);
	// printf("cx=%f, cy=%f, cz=%f\n", data->scene.camera._r.x, data->scene.camera._r.y,
	// 	data->scene.camera._r.z);
}
