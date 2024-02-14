/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:27:19 by npirard           #+#    #+#             */
/*   Updated: 2024/02/14 11:39:57 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt/minirt.h>
#include <minirt/parsing.h>
#include <minirt/objects.h>

int		scene_parse_origin(char **ptr, t_coord3f *origin);
int		scene_parse_orientation(char **ptr, t_vec3f *orientation);
int		scene_parse_color(char **ptr, t_color *color);

int	scene_parse_color(char **ptr, t_color *color)
{
	char	*it;

	it = *ptr;
	while (ft_isspace(*it))
		it++;
	if (ft_strtoi(it, &color->r) || color->r < 0 || color->r > 255)
		return (1);
	while (*it && *it != ',' && !ft_isspace(*it))
		it++;
	if (*it++ != ',')
		return (1);
	if (ft_isspace(*it) || ft_strtoi(it, &color->g)
		|| color->g < 0 || color->g > 255)
		return (1);
	while (*it && *it != ',' && !ft_isspace(*it))
		it++;
	if (*it++ != ',')
		return (1);
	if (ft_isspace(*it) || ft_strtoi(it, &color->b)
		|| color->b < 0 || color->b > 255)
		return (1);
	while (*it && !ft_isspace(*it))
		it++;
	*ptr = it;
	return (0);
}

int	scene_parse_orientation(char **ptr, t_vec3f *dir)
{
	char	*it;

	it = *ptr;
	while (ft_isspace(*it))
		it++;
	if (ft_strtod(it, &dir->x, NULL) || dir->x < -1.0 || dir->x > 1.0)
		return (1);
	while (*it && *it != ',' && !ft_isspace(*it))
		it++;
	if (*it++ != ',')
		return (1);
	if (ft_isspace(*it) || ft_strtod(it, &dir->y, NULL)
		|| dir->y < -1.0 || dir->y > 1.0)
		return (1);
	while (*it && *it != ',' && !ft_isspace(*it))
		it++;
	if (*it++ != ',')
		return (1);
	if (ft_isspace(*it) || ft_strtod(it, &dir->z, NULL)
		|| dir->z < -1.0 || dir->z > 1.0)
		return (1);
	while (*it && !ft_isspace(*it))
		it++;
	*ptr = it;
	return (0);
}

int	scene_parse_origin(char **ptr, t_coord3f *origin)
{
	char	*it;

	it = *ptr;
	while (ft_isspace(*it))
		it++;
	if (ft_strtod(it, &origin->x, NULL))
		return (1);
	while (*it && *it != ',' && !ft_isspace(*it))
		it++;
	if (*it++ != ',')
		return (1);
	if (ft_isspace(*it) || ft_strtod(it, &origin->y, NULL))
		return (1);
	while (*it && *it != ',' && !ft_isspace(*it))
		it++;
	if (*it++ != ',')
		return (1);
	if (ft_isspace(*it) || ft_strtod(it, &origin->z, NULL))
		return (1);
	while (*it && !ft_isspace(*it))
		it++;
	*ptr = it;
	return (0);
}