/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:08:26 by npirard           #+#    #+#             */
/*   Updated: 2024/02/23 16:30:06 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt/minirt.h>
#include <minirt/parsing.h>
#include <minirt/objects.h>
#include <minirt/calculus.h>

int	scene_parse_texture_type(char **ptr, t_object *object)
{
	skip_space(ptr);
	if (!**ptr)
		return (1);
	if (parse_cmp("S:", ptr))
		object->texture.type = TEX_SOLID;
	else if (parse_cmp("D:", ptr))
		object->texture.type = TEX_DAM;
	else if (parse_cmp("I:", ptr))
		object->texture.type = TEX_IMG;
	else
		return (1);
	return (0);
}

/// @brief
/// @param ptr
/// @param object
/// @return
/// Format [SDI]:[PathColor1]:[Color2]:Resolution
///
int	scene_parse_texture(char **ptr, t_object *object, int nbr, char *line)
{
	if (scene_parse_texture_type(ptr, object))
		return (error_parsing("object texture type", nbr, line, NULL), 1);
	if ((object->texture.type == TEX_SOLID
			&& scene_parse_texture_solid(ptr, object, nbr, line))
		|| (object->texture.type == TEX_DAM
			&& scene_parse_texture_dame(ptr, object, nbr, line))
		|| (object->texture.type == TEX_IMG
			&& scene_parse_texture_img(ptr, object, nbr, line)))
		return (1);
	return (0);
}
