/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:08:26 by npirard           #+#    #+#             */
/*   Updated: 2024/02/25 15:11:34 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt/minirt.h>
#include <minirt/parsing.h>
#include <minirt/objects.h>
#include <minirt/calculus.h>

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
		return (free(object), error("parsing object"), 1);
	ft_lstadd_back(&scene->objects, object_node);
	t_object_init(object);
	ptr = line;
	object->data = scene->data;
	scene_parse_type(&ptr, &object->type);
	if (scene_parse_obj_entries(object, &ptr, nbr, line))
		return (1);
	return (0);
}

int	scene_parse_obj_entries(t_object *obj, char **ptr, int nbr, char *line)
{
	while (**ptr)
	{
		if (*skip_space(ptr) == '\0')
			break ;
		if (parse_cmp("id:", ptr) && scene_parse_int(ptr, &obj->id))
			return (error_parsing("object id", nbr, line, NULL), 1);
		else if (parse_cmp("origin:", ptr)
			&& scene_parse_origin(ptr, &obj->origin))
			return (error_parsing("object origin", nbr, line, NULL), 1);
		else if (parse_cmp("orientation:", ptr)
			&& scene_parse_orientation(ptr, &obj->orientation))
			return (error_parsing("object orientation", nbr, line, NULL), 1);
		else if (parse_cmp("diameter:", ptr)
			&& (scene_parse_double(ptr, &obj->radius) || obj->radius < 0.f))
			return (error_parsing("object diameter", nbr, line, NULL), 1);
		else if (parse_cmp("height:", ptr)
			&& (scene_parse_double(ptr, &obj->height) || obj->height < 0.f))
			return (error_parsing("object height", nbr, line, NULL), 1);
		else if (parse_cmp("texture:", ptr)
			&& scene_parse_texture(ptr, obj, nbr, line))
			return (1);
		else if (scene_parse_obj_properties(obj, nbr, ptr, line))
			return (1);
	}
	return (0);
}

int	scene_parse_obj_properties(t_object *object, int nbr,
		char **ptr, char *line)
{
	if (parse_cmp("ka:", ptr)
		&& scene_parse_ratio(ptr, &object->k_ambiant))
		return (error_parsing("object ambiant light reflexion",
				nbr, line, NULL), 1);
	else if (parse_cmp("kd:", ptr)
		&& scene_parse_ratio(ptr, &object->k_diffuse))
		return (error_parsing("object diffuse light reflexion",
				nbr, line, NULL), 1);
	else if (parse_cmp("ks:", ptr)
		&& scene_parse_ratio(ptr, &object->k_specular))
		return (error_parsing("object specular light reflexion",
				nbr, line, NULL), 1);
	else if (parse_cmp("glow-ratio:", ptr)
		&& scene_parse_ratio(ptr, &object->k_glow))
		return (error_parsing("object glowing ratio",
				nbr, line, NULL), 1);
	else if (parse_cmp("glow-color:", ptr)
		&& scene_parse_color(ptr, &object->color_glow))
		return (error_parsing("object glowing color", nbr, line, NULL), 1);
	else if (scene_parse_obj_properties2(object, nbr, ptr, line))
		return (1);
	return (0);
}

int	scene_parse_obj_properties2(t_object *object, int nbr,
		char **ptr, char *line)
{
	if (parse_cmp("rf:", ptr)
		&& scene_parse_ratio(ptr, &object->k_reflexion))
		return (error_parsing("object reflexion constant", nbr, line, NULL), 1);
	else if (parse_cmp("ri:", ptr)
		&& (scene_parse_double(ptr, &object->i_refraction)
			|| object->i_refraction < 0.f))
		return (error_parsing("object refractive indice", nbr, line, NULL), 1);
	else if (parse_cmp("sp:", ptr)
		&& scene_parse_ratio(ptr, &object->k_plastic))
		return (error_parsing("object plastic reflexion", nbr, line, NULL), 1);
	else if (parse_cmp("sr:", ptr)
		&& (scene_parse_double(ptr, &object->k_roughness)
			|| object->k_roughness < 1.0))
		return (error_parsing("object roughness", nbr, line, NULL), 1);
	else if (parse_cmp("light-ratio:", ptr)
		&& scene_parse_ratio(ptr, &object->k_light))
		return (error_parsing("object light emission ratio",
				nbr, line, NULL), 1);
	else if (parse_cmp("light-color:", ptr)
		&& scene_parse_light_obj(ptr, object))
		return (error_parsing("object light color", nbr, line, NULL), 1);
	else if (**ptr && ft_isspace(**ptr) == false)
		return (error_parsing("unknown property", nbr, line, *ptr), 1);
	return (0);
}
