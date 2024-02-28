/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:57:59 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdint.h>

void	*alloc_arg_value(char type)
{
	void	*value;

	value = NULL;
	if (type == 'c')
		value = malloc(sizeof(int));
	else if (type == 's')
		value = malloc(sizeof(char *));
	else if (ft_strchr("di", type))
		value = malloc(sizeof(int));
	else if (ft_strchr("uxX", type))
		value = malloc(sizeof(unsigned int));
	else if (ft_strchr("pt", type))
		value = malloc(sizeof(unsigned long));
	if (!value)
		return (alloc_error());
	return (value);
}

void	*get_arg_value(va_list *va_args, char type)
{
	void	*value;

	value = alloc_arg_value(type);
	if (!value)
		return (NULL);
	if (type == 'c')
		*((int *) value) = va_arg(*va_args, int);
	else if (type == 's')
		*((char **) value) = va_arg(*va_args, char *);
	else if (ft_strchr("di", type))
		*((int *) value) = va_arg(*va_args, int);
	else if (ft_strchr("uxX", type))
		*((unsigned int *) value) = va_arg(*va_args, unsigned int);
	else if (ft_strchr("pt", type))
		*((unsigned long *) value) = va_arg(*va_args, unsigned long);
	return (value);
}

void	cast_to_dest(void *dest, void *value, char type)
{
	if (type == 'c')
		*((char *) dest) = *((char *) value);
	else if (type == 's')
		*((char **) dest) = *((char **) value);
	else if (ft_strchr("di", (int) type))
		*((int *) dest) = *((int *) value);
	else if (ft_strchr("uxX", (int) type))
		*((unsigned int *) dest) = *((unsigned int *) value);
	else if (ft_strchr("pt", (int) type))
		*((unsigned long *) dest) = *((unsigned long *) value);
}
