/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:04:22 by npirard           #+#    #+#             */
/*   Updated: 2024/02/14 11:24:33 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt/minirt.h>
#include <minirt/objects.h>
#include <minirt/parsing.h>

int	scene_parse_camera(t_scene *scene, int nbr, char **ptr, char *line)
{
	if (scene_parse_origin(ptr, &scene->camera.origin))
		return (error_parsing("camera origin", nbr, line), 1);
	if (scene_parse_orientation(ptr, &scene->camera.dir))
		return (error_parsing("camera orientation", nbr, line), 1);
	if (scene_parse_fov(ptr, &scene->camera.fov))
		return (error_parsing("camera fov", nbr, line), 1);
	return (0);
}

int	scene_parse_ambiant(t_scene *scene, int nbr, char **ptr, char *line)
{
	if (scene_parse_ratio(ptr, &scene->ambiant_light.ratio))
		return (error_parsing("ambiant light ratio", nbr, line), 1);
	if (scene_parse_color(ptr, &scene->ambiant_light.color))
		return (error_parsing("ambiant light color", nbr, line), 1);
	return (0);
}

int	scene_parse_light(t_scene *scene, int nbr, char **ptr, char *line)
{
	t_list	*light_node;
	t_light	*light;

	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (error("parsing light object"), 1);
	light_node = ft_lstnew(light);
	if (!light_node)
	{
		free(light);
		return (error("parsing light object"), 1);
	}
	ft_lstadd_back(&scene->lights, light_node);
	if (scene_parse_origin(ptr, &light->origin))
		return (error_parsing("light origin", nbr, line), 1);
	if (scene_parse_ratio(ptr, &light->ratio))
		return (error_parsing("light ratio", nbr, line), 1);
	if (scene_parse_color(ptr, &light->color))
		return (error_parsing("light color", nbr, line), 1);
	return (0);
}

int	scene_parse_object(t_scene *scene, int nbr, char *line)
{
	t_list		*object_node;
	t_object	*object;
	char		*ptr;

	object = ft_calloc(1, sizeof(t_object));
	if (!object)
		return (error("parsing object"), 1);
	object_node = ft_lstnew(object);
	if (!object_node)
	{
		free(object);
		return (error("parsing object"), 1);
	}
	ft_lstadd_back(&scene->objects, object_node);
	ptr = line;
	scene_parse_type(&ptr, &object->type);
	if (object->type == SPHERE && scene_parse_sphere(object, nbr, &ptr, line))
		return (1);
	if (object->type == CYLINDER && scene_parse_cylinder(object, nbr, &ptr, line))
		return (1);
	if (object->type == PLAN && scene_parse_plan(object, nbr, &ptr, line))
		return (1);
	return (0);
}

int	scene_parse_line(t_scene *scene, char *line)
{
	char		*ptr;
	char		type;
	static int	nbr = 0;

	nbr++;
	ptr = line;
	while (ft_isspace(*ptr))
		ptr++;
	if (!*ptr)
		return (0);
	if (scene_parse_type(&ptr, &type))
		return (error_parsing("object type", nbr, line), 1);
	if (type == CAMERA && scene_parse_camera(scene, nbr, &ptr, line))
		return (1);
	else if (type == AMBIANT && scene_parse_ambiant(scene, nbr, &ptr, line))
		return (1);
	else if (type == LIGHT && scene_parse_light(scene, nbr, &ptr, line))
		return (1);
	else if (type >= SPHERE && scene_parse_object(scene, nbr, line))
		return (1);
	return (0);
}
