/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_texture.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:43:38 by npirard           #+#    #+#             */
/*   Updated: 2024/02/22 15:11:18 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <libft.h>
#include <minirt/objects.h>

void	t_texture_free(void *texture_ptr)
{
	t_texture	*texture;

	texture = (t_texture *)texture_ptr;
	free(texture->file_path);
	if (texture->img)
		mlx_destroy_image(texture->data->mlx, texture->img);
	free(texture);
}
