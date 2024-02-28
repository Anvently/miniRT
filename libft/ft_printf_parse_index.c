/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_index.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:08:11 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	get_index(char **str, int *arg_index,
			int *given_index, bool begin)
{
	int	i;
	int	pos_format;

	*given_index = 0;
	pos_format = 0;
	i = 0;
	if ((*str) && ft_isdigit((*str)[i + !begin]))
	{
		while (ft_isdigit((*str)[i + !begin]))
			i++;
		if ((*str)[i + !begin] == '$')
		{
			*given_index = ft_atoi((*str) + !begin);
			pos_format = 2;
		}
	}
	if ((*str) && begin == false && (*str)[0] == '*' && !pos_format)
	{
		pos_format = 1;
		*given_index = ++(*arg_index);
	}
	if (*given_index)
		*str = (*str) + ((i + !begin) * (pos_format == 2)) + 1;
	return (pos_format);
}

/// @brief Look for a ```*m$``` format and retrieve the proper
/// index. Additionnaly check for any conflict between a m$ and a normal format.
/// @param str String to look into.
/// @param arg_index Index of the last argument read in ```args```. Start at 0.
/// @param given_index Variable where the result of the parsing will be stored.
/// If no ```*m$``` is found then stays at 0.
/// @return Right boundary of the parsed sequence.
/// ```str``` if no sequence is found. ```NULL``` in case of format error.
char	*parse_arg_index(char *str, int *arg_index,
			int *given_index, bool begin)
{
	int			new_format;

	new_format = get_index(&str, arg_index, given_index, begin);
	if (!str || !check_index_format(new_format, *given_index,
			"position of argument"))
		return (NULL);
	return (str);
}
