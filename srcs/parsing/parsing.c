/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:29:34 by npirard           #+#    #+#             */
/*   Updated: 2024/02/12 18:56:01 by npirard          ###   ########.fr       */
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
	}
	if (errno == ENOMEM)
		return (error("parsing file"), errno);
	return (0);
}

/// @brief Open given file and parse it
/// @param path
/// @return Allocated scene structure
/// ```NULL``` if error (errors' context is printed)
t_scene	*scene_open(char *path)
{
	t_scene	*scene;
	int		fd;

	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (error(NULL), NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		t_scene_free(&scene);
		return (error_file("opening file", path), NULL);
	}
	if (scene_parse(scene, fd))
		t_scene_free(&scene);
	close(fd);
	return (scene);
}
