/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:58:07 by npirard           #+#    #+#             */
/*   Updated: 2024/02/23 13:52:47 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <pthread.h>
#include <math.h>

int	handle_resize_click(t_data *data)
{
	data->mouse_pressed = true;
	printf("PING\n");
	return (0);
}

void	rotationY(t_data *data, double angle)
{
	t_matrix4f	matrix;

	ft_memset(&matrix, 0, sizeof(t_matrix4f));
	matrix.m0[0] = cos(angle);
	matrix.m0[2] = sin(angle);
	matrix.m1[1] = 1;
	matrix.m2[0] = -sin(angle);
	matrix.m2[2] = cos(angle);
	matrix.m3[3] = 1;
	data->scene.camera._cx = vec3f_matrix4f(&data->scene.camera._cx, &matrix);
	data->scene.camera._cy = vec3f_matrix4f(&data->scene.camera._cy, &matrix);
	data->scene.camera._cz = vec3f_matrix4f(&data->scene.camera._cz, &matrix);
}

void	rotationZ(t_data *data, double angle)
{
	t_matrix4f	matrix;

	ft_memset(&matrix, 0, sizeof(t_matrix4f));
	matrix.m0[0] = cos(angle);
	matrix.m0[1] = -sin(angle);
	matrix.m1[0] = sin(angle);
	matrix.m1[1] = cos(angle);
	matrix.m2[2] = 1;
	matrix.m3[3] = 1;
	data->scene.camera._cx = vec3f_matrix4f(&data->scene.camera._cx, &matrix);
	data->scene.camera._cy = vec3f_matrix4f(&data->scene.camera._cy, &matrix);
	data->scene.camera._cz = vec3f_matrix4f(&data->scene.camera._cz, &matrix);
}

// /// @brief
// /// @param data
// /// @return
// int	handle_rotation(t_data *data)
// {
// 	t_matrix3f	matrix;
// 	t_vec3f		new_vec_x;
// 	t_vec3f		new_vec_y;
// 	t_vec3f		new_dir;

// 	new_vec_x = vec3_scale(&data->scene.camera._u, (double) data->dnd.x);
// 	// print_t_double3(&new_vec_x);
// 	new_vec_y = vec3_scale(&data->scene.camera._v, (double) data->dnd.y);
// 	new_dir = vec3_sum(&data->scene.camera._cx, &new_vec_x);
// 	new_dir = vec3_sum(&new_dir, &new_vec_y);
// 	normalize_vec(&new_dir);
// 	matrix = rotation_matrix(&new_dir);
// 	// display_matrix(&matrix);
// 	matrix = matrix_transpose(&matrix);
// 	// display_matrix(&matrix);
// 	data->scene.camera._cx = vec3f_matrix3f(&data->scene.camera._cx, &matrix);
// 	data->scene.camera._cy = vec3f_matrix3f(&data->scene.camera._cy, &matrix);
// 	data->scene.camera._cz = vec3f_matrix3f(&data->scene.camera._cz, &matrix);
// 	// matrix = matrix_rotate(0.0, 0.0, );
// 	// data->scene.camera._cx = vec3f_matrix4f(&data->scene.camera._cx, &matrix);
// 	// data->scene.camera._cy = vec3f_matrix4f(&data->scene.camera._cy, &matrix);
// 	// rotationY(data, -data->dnd.y / 250.f);
// 	// rotationZ(data, data->dnd.x / 250.f);
// 	// printf("cx*cy = %f, cx*cz = %f, cy * cz = %f\n",
// 	// 	scalar_product(&data->scene.camera._cx, &data->scene.camera._cy),
// 	// 	scalar_product(&data->scene.camera._cx, &data->scene.camera._cz),
// 	// 	scalar_product(&data->scene.camera._cy, &data->scene.camera._cz));
// 	img_update_camera(data);
// 	return (0);
// }

int	handle_zoom(t_data *data, int keycode)
{
	if (keycode == Button4)
		data->scene.camera.origin = vec3_sum(&data->scene.camera.origin,
				&data->scene.camera._cx);
	else if (keycode == Button5)
		data->scene.camera.origin = vec3_diff(&data->scene.camera.origin,
				&data->scene.camera._cx);
	return (0);
}

int	handle_rotation(t_data *data)
{
	t_matrix3f	matrix_y;
	t_matrix3f	matrix_z;

	matrix_y = matrix_rotate(0.0, -data->dnd.y / 250.f, 0.0);
	matrix_z = matrix_rotate(0.0, 0.0, -data->dnd.x / 250.f);
	data->scene.camera._cx = vec3f_matrix3f(&data->scene.camera._cx, &matrix_y);
	data->scene.camera._cy = vec3f_matrix3f(&data->scene.camera._cy, &matrix_y);
	data->scene.camera._cz = vec3f_matrix3f(&data->scene.camera._cz, &matrix_y);
	transform_scene(data, &matrix_z, -data->dnd.x / 250.f);
		// printf("cx*cy = %f, cx*cz = %f, cy * cz = %f\n",
		// 	scalar_product(&data->scene.camera._cx, &data->scene.camera._cy),
		// 	scalar_product(&data->scene.camera._cx, &data->scene.camera._cz),
		// 	scalar_product(&data->scene.camera._cy, &data->scene.camera._cz));
	img_update_camera(data);
	return (0);
}

// int	handle_rotation(t_data *data)
// {
// 	t_matrix4f	matrix;
// 	t_vec3f		old_cz;


// 	old_cz = data->scene.camera._cz;
// 	matrix = matrix_rotate(0.0, 0.0, data->dnd.x / 250.f);
// 	data->scene.camera._cx = vec3f_matrix4f(&data->scene.camera._cx, &matrix);
// 	data->scene.camera._cy = vec3f_matrix4f(&data->scene.camera._cy, &matrix);
// 	// data->scene.camera._cz = vec3f_matrix4f(&data->scene.camera._cz, &matrix);
// 	matrix = matrix_rotate(0.0, -data->dnd.y / 250.f, 0.0);
// 	data->scene.camera._cx = vec3f_matrix4f(&data->scene.camera._cx, &matrix);
// 	// data->scene.camera._cy = vec3f_matrix4f(&data->scene.camera._cy, &matrix);
// 	data->scene.camera._cz = vec3f_matrix4f(&data->scene.camera._cz, &matrix);
// 	// matrix = matrix_rotate(0.0, 0.0, );
// 	// data->scene.camera._cx = vec3f_matrix4f(&data->scene.camera._cx, &matrix);
// 	// data->scene.camera._cy = vec3f_matrix4f(&data->scene.camera._cy, &matrix);
// 	// rotationY(data, -data->dnd.y / 250.f);
// 	// rotationZ(data, data->dnd.x / 250.f);
// 	printf("cx*cy = %f, cx*cz = %f, cy * cz = %f\n",
// 		scalar_product(&data->scene.camera._cx, &data->scene.camera._cy),
// 		scalar_product(&data->scene.camera._cx, &data->scene.camera._cz),
// 		scalar_product(&data->scene.camera._cy, &data->scene.camera._cz));
// 	img_update_camera(data);
// 	return (0);
// }
