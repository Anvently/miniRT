/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:08:26 by npirard           #+#    #+#             */
/*   Updated: 2024/02/22 14:07:00 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt/minirt.h>
#include <minirt/parsing.h>
#include <minirt/objects.h>
#include <minirt/calculus.h>

/// @brief
/// @param ptr
/// @param object
/// @return
/// Format [SDI]:[PathColor1]:[Color2]:Resolution
///
int	scene_parse_texture(char **ptr, t_object *object, int nbr, char *line)
{
	if (scene_parse_texture_type(ptr, object))
		return (error_parsing("object texture type", nbr, line), 1);
	if ((object->texture.type == TEX_SOLID
			&& scene_parse_texture_solid(ptr, object, nbr, line))
		|| (object->texture.type == TEX_DAM
			&& scene_parse_texture_dame(ptr, object, nbr, line))
		|| (object->texture.type == TEX_IMG
			&& scene_parse_texture_img(ptr, object, nbr, line)))
		return (1);
	return (0);
}
