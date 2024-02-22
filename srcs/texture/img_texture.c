/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:01:15 by npirard           #+#    #+#             */
/*   Updated: 2024/02/22 16:09:13 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/parsing.h>
#include <minirt/objects.h>
#include <libft.h>

/// @brief Check if texture given in ```path``` is already opened, and returned
/// its address if so, else return ```NULL```
/// @param data
/// @param path
/// @return
static t_texture	*texture_img_find(t_data *data, char *path)
{
	t_list		*node;
	t_texture	*texture;

	if (!path)
		return (NULL);
	node = data->textures_img;
	while (node)
	{
		texture = (t_texture *)node->content;
		if (!ft_strcmp(texture->file_path, path))
			return (texture);
		node = node->next;
	}
	return (NULL);
}

/// @brief Opened an image given in path
/// @param texture
/// @param path
/// @return ```0``` if error. Can be allocation error, if path is invalid,
/// or if image could not be opened.
static int	texture_img_open(t_data *data, t_texture *texture)
{
	texture->img = mlx_xpm_file_to_image(data->mlx, texture->file_path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (error_file("opening texture file", texture->file_path), 1);
	texture->img_addr = mlx_get_data_addr(texture->img, &texture->bbp,
			&texture->len_line, &texture->endian);
	if (!texture->img_addr)
		return (error_file("opening texture file", texture->file_path), 1);
	return (0);
}

/// @brief Return address of an image texture. If the image was already
/// already opened in another structure, return its address, else a new
/// structure node is allocated in image structure list.
/// @param data
/// @param path
/// @return ```NULL``` if allocation error, or wrong texture path. Error
/// context are printed.
t_texture	*texture_img_get(t_data *data, char *path)
{
	t_texture	*texture;
	t_list		*texture_node;

	texture = texture_img_find(data, path);
	if (texture)
	{
		free(path);
		return (texture);
	}
	texture = calloc(1, sizeof(t_texture));
	if (!texture)
		return (free(path), error("initializing texture"), NULL);
	texture_node = ft_lstnew(texture);
	if (!texture_node)
	{
		free(texture);
		return (free(path), error("initializing texture"), NULL);
	}
	ft_lstadd_back(&data->textures_img, texture_node);
	texture->file_path = path;
	texture->data = data;
	if (texture_img_open(data, texture))
		return (NULL);
	return (texture);
}

t_color3f	texture_img_get_pxl(t_texture *texture, int x, int y)
{
	int	color;

	color = *(int *)(texture->img_addr + (y * texture->len_line
				+ x * (texture->bbp / 8)));
	return (color_getcolor3f(color));
}
