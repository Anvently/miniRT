/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:27:05 by npirard           #+#    #+#             */
/*   Updated: 2024/02/13 16:46:59 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt/minirt.h>
#include <minirt/parsing.h>
#include <minirt/objects.h>

int		scene_parse_type(char **ptr, char *type);
int		scene_parse_fov(char **ptr, int *fov);
int		scene_parse_ratio(char **ptr, float *ratio);
int		scene_parse_float(char **ptr, float *value);

/// @brief Check if ptr points toward a valid type (```A, C, L, pl, sp, cy```)
/// and assign it to ```type```.
/// First spaces are ignored.
/// @param ptr
/// @param type
/// @return ```0``` if no error.
int	scene_parse_type(char **ptr, char *type)
{
	char	*it;

	it = *ptr;
	if (!ft_strncmp(it, "A", 1))
		*type = AMBIANT;
	else if (!ft_strncmp(it, "C", 1))
		*type = CAMERA;
	else if (!ft_strncmp(it, "L", 1))
		*type = LIGHT;
	else if (!ft_strncmp(it, "pl", 2))
		*type = PLAN;
	else if (!ft_strncmp(it, "sp", 2))
		*type = SPHERE;
	else if (!ft_strncmp(it, "cy", 2))
		*type = CYLINDER;
	while (*it && !ft_isspace(*it))
		it++;
	*ptr = it;
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

int	scene_parse_ratio(char **ptr, float *ratio)
{
	if (ft_strtof(*ptr, ratio, ptr) || *ratio < 0.0 || *ratio > 1.0)
		return (1);
	return (0);
}

int	scene_parse_float(char **ptr, float *value)
{
	if (ft_strtof(*ptr, value, ptr))
		return (1);
	return (0);
}
