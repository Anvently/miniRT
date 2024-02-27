/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:27:05 by npirard           #+#    #+#             */
/*   Updated: 2024/02/27 09:23:59 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt/minirt.h>
#include <minirt/parsing.h>
#include <minirt/objects.h>

int		scene_parse_type(char **ptr, char *type);
int		scene_parse_fov(char **ptr, int *fov);
int		scene_parse_ratio(char **ptr, double *ratio);
int		scene_parse_double(char **ptr, double *value);

/// @brief Check if ptr points toward a valid type (```A, C, L, pl, sp, cy```)
/// and assign it to ```type```.
/// First spaces are ignored.
/// @param ptr
/// @param type
/// @return ```0``` if no error.
int	scene_parse_type(char **ptr, char *type)
{
	if (parse_cmp("A", ptr))
		*type = AMBIANT;
	else if (parse_cmp("C", ptr))
		*type = CAMERA;
	else if (parse_cmp("L", ptr))
		*type = LIGHT;
	else if (parse_cmp("pl", ptr))
		*type = PLAN;
	else if (parse_cmp("sp", ptr))
		*type = SPHERE;
	else if (parse_cmp("cy", ptr))
		*type = CYLINDER;
	else if (parse_cmp("co", ptr))
		*type = CONE;
	else if (parse_cmp("move", ptr))
		*type = MOVE;
	else if (parse_cmp("tr", ptr))
		*type = TR;
	else
		return (1);
	return (0);
}

int	scene_parse_fov(char **ptr, int *fov)
{
	while (ft_isspace(**ptr))
		*ptr = *ptr + 1;
	if (ft_strtoi(*ptr, fov) || *fov < 0 || *fov > 180)
		return (1);
	while (**ptr && !ft_isspace(**ptr))
		*ptr = *ptr + 1;
	return (0);
}

int	scene_parse_ratio(char **ptr, double *ratio)
{
	if (ft_strtod(*ptr, ratio, ptr) || *ratio < 0.0 || *ratio > 1.0)
		return (1);
	return (0);
}

int	scene_parse_double(char **ptr, double *value)
{
	if (ft_strtod(*ptr, value, ptr))
		return (1);
	return (0);
}

int	scene_parse_int(char **ptr, int *value)
{
	if (ft_strtoi(*ptr, value))
		return (1);
	while (**ptr && !ft_isspace(**ptr))
		*ptr = *ptr + 1;
	return (0);
}
