/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:08:26 by npirard           #+#    #+#             */
/*   Updated: 2024/02/22 11:59:04 by npirard          ###   ########.fr       */
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
	else if (obj_type == PLAN)
		texture->get_color = &texture_get_plan_dame;
	else if (obj_type == CYLINDER)
		texture->get_color = &texture_get_cylinder_dame;
	else if (obj_type == CONE)
		texture->get_color = &texture_get_cone_dame;
}

int	scene_parse_texture_img(char **ptr, t_object *object, int nbr, char *line)
{
	char	*path;

	if (scene_parse_path(ptr, &path))
		return (error_parsing("texture image path", nbr, line), 1);
	object->texture = tex
}

int	scene_parse_texture_dame(char **ptr, t_object *object, int nbr, char *line)
{
	if (scene_parse_color(ptr, &object->texture.color1))
		return (error_parsing("texture color1", nbr, line), 1);
	*ptr = *ptr + 1;
	if (scene_parse_color(ptr, &object->texture.color2))
		return (error_parsing("texture color2", nbr, line), 1);
	*ptr = *ptr + 1;
	if (ft_isdigit(**ptr) == false)
		return (error_parsing("texture resolution", nbr, line), 1);
	if (ft_strtoi(*ptr, &object->texture.resolution))
		return (error_parsing("texture resolution", nbr, line), 1);
	while (ft_isspace(**ptr) == false && **ptr)
		*ptr = *ptr + 1;
	handle_dame_texture(&object->texture, object->type);
	return (0);
}

int	scene_parse_texture_solid(char **ptr, t_object *object, int nbr, char *line)
{
	if (scene_parse_color(ptr, &object->texture.color1))
		return (error_parsing("object color", nbr, line), 1);
	object->texture.get_color = &texture_get_solid_color;
	return (0);
}

int	scene_parse_texture_type(char **ptr, t_object *object)
{
	skip_space(ptr);
	if (!**ptr)
		return (1);
	if (!ft_strncmp("S:", *ptr, 2))
		object->texture.type = TEX_SOLID;
	else if (!ft_strncmp("D:", *ptr, 2))
		object->texture.type = TEX_DAM;
	else if (!ft_strncmp("I:", *ptr, 2))
		object->texture.type = TEX_IMG;
	else
		return (1);
	*ptr = *ptr + 2;
	return (0);
}
