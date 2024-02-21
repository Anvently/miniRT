/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:29:34 by npirard           #+#    #+#             */
/*   Updated: 2024/02/21 18:16:44 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/objects.h>
#include <minirt/parsing.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

char	*skip_space(char **ptr)
{
	while (ft_isspace(**ptr))
		*ptr = *ptr + 1;
	return (*ptr);
}

/// @brief Read file opened in fd and fill scene structure.
/// @param scene
/// @param fd
/// @return ```0``` if no error occured. Error context are printed.
static int	scene_parse(t_scene *scene, int fd)
{
	char	*line;

	while (1)
	{
		line = ft_gnl(fd);
		if (!line)
			break ;
		if (scene_parse_line(scene, line))
		{
			free(line);
			return (1);
		}
		free(line);
	}
	if (errno == ENOMEM)
		return (error("parsing file"), errno);
	return (0);
}

/// @brief Open given file and parse it
/// @param path
/// @return ```0``` if no error occured (errors' context is printed)
int	scene_open(char *path, t_scene *scene)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_file("opening file", path), 1);
	if (scene_parse(scene, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
