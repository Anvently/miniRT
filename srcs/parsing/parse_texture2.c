/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:08:26 by npirard           #+#    #+#             */
/*   Updated: 2024/02/27 10:04:50 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt/minirt.h>
#include <minirt/parsing.h>
#include <minirt/objects.h>
#include <minirt/calculus.h>

static void	handle_dame_texture(t_texture *texture, char obj_type)
{
	texture->height = texture->resolution;
	texture->width = texture->resolution;
	if (obj_type == SPHERE)
	{
		texture->width = texture->height * 2;
		texture->get_color = &texture_get_sphere_dame;
	}
	else if (obj_type == PLAN || obj_type == TR)
		texture->get_color = &texture_get_plan_dame;
	else if (obj_type == CYLINDER)
		texture->get_color = &texture_get_cylinder_dame;
	else if (obj_type == CONE)
		texture->get_color = &texture_get_cone_dame;
}

static bool	check_texture_format(char *path)
{
	if (!ft_strncmp_rev(path, ".xpm", 4))
		return (true);
	return (false);
}

int	scene_parse_texture_img(char **ptr, t_object *object, int nbr, char *line)
{
	char		*path;
	t_texture	*texture;

	if (scene_parse_path(ptr, &path) > 0)
		return (error_parsing("texture image path", nbr, line, NULL), 1);
	if (path == NULL)
		return (1);
	if (check_texture_format(path) == false)
		return (free(path),
			error_parsing("incorrect texture format", nbr, line, NULL), 1);
	texture = texture_img_get(object->data, path);
	if (!texture)
		return (1);
	object->texture = *texture;
	if (object->type == SPHERE)
		object->texture.get_color = &texture_get_sphere_img;
	else if (object->type == PLAN || object->type == TR)
		object->texture.get_color = &texture_get_plan_img;
	else if (object->type == CYLINDER)
		object->texture.get_color = &texture_get_cylinder_img;
	else if (object->type == CONE)
		object->texture.get_color = &texture_get_cone_img;
	return (0);
}

int	scene_parse_texture_dame(char **ptr, t_object *object, int nbr, char *line)
{
	if (scene_parse_color(ptr, &object->texture.color1))
		return (error_parsing("texture color1", nbr, line, NULL), 1);
	if (**ptr != ':')
		return (error_parsing("texture color2", nbr, line, NULL), 1);
	*ptr = *ptr + 1;
	if (scene_parse_color(ptr, &object->texture.color2))
		return (error_parsing("texture color2", nbr, line, NULL), 1);
	if (**ptr != ':')
		return (error_parsing("texture resolution", nbr, line, NULL), 1);
	*ptr = *ptr + 1;
	if (ft_isdigit(**ptr) == false)
		return (error_parsing("texture resolution", nbr, line, NULL), 1);
	if (ft_strtoi(*ptr, &object->texture.resolution))
		return (error_parsing("texture resolution", nbr, line, NULL), 1);
	while (ft_isspace(**ptr) == false && **ptr)
		*ptr = *ptr + 1;
	handle_dame_texture(&object->texture, object->type);
	return (0);
}

int	scene_parse_texture_solid(char **ptr, t_object *object, int nbr, char *line)
{
	if (scene_parse_color(ptr, &object->texture.color1))
		return (error_parsing("object color", nbr, line, NULL), 1);
	object->texture.get_color = &texture_get_solid_color;
	return (0);
}
