/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:28:36 by npirard           #+#    #+#             */
/*   Updated: 2024/02/14 10:24:54 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>

/*

Generate a ray for each pixel



*/


/*


*/

void	get_next_pixel(t_coord2 *pxl, t_coord2 *size)
{

}


/*

Let's define size of the screen :

Camera origin vector is the 1 norm.
Each vector are camera_dir + (x * u) + (y * v) OK
But u = ?
	v = ?
*/

void	generate_ray(t_ray *ray, t_coord2 *pxl, t_data *data)
{
	scre
	ray->origin = data->scene.camera.origin;
	//ray->dir = camera_dir + (pxl.x * u) + (pxl.y * v) + center_shift
	ray->
}

/// @brief Compute ray properties of a given pixel
/// @param ray
/// @param x
/// @param y
/// @param camera
void	generate_rays(t_data *data)
{
	t_coord2	pxl;
	t_ray		ray;

	pxl.x = 0;
	while (pxl.x < data->size.x)
	{
		pxl.y = 0;
		while (pxl.y < data->size.y)
		{
			genete_ray(&ray, &pxl, data);
			pxl.y++;
		}
		pxl.x++;
	}
}



int	render(void	*data)
{
	(void) data;
	return (0);
}