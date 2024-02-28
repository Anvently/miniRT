/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str_conversion.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:32:00 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*char_to_str(char c)
{
	char	*buffer;

	buffer = malloc(2);
	if (!buffer)
		return (alloc_error());
	buffer[0] = c;
	buffer[1] = '\0';
	return (buffer);
}

char	*address_to_str(unsigned long addr)
{
	char	*buffer;
	char	*str_addr;

	if (!addr)
		return (ft_strdup("(nil)"));
	buffer = ft_ultoa_base(addr, "0123456789abcdef");
	if (!buffer)
		return (alloc_error());
	str_addr = ft_strjoin("0x", buffer);
	free(buffer);
	if (!str_addr)
		return (alloc_error());
	return (str_addr);
}

char	*str_to_str(char *str)
{
	if (!str)
		return (ft_strdup("(null)"));
	return (ft_strdup(str));
}

char	*hexa_to_str(unsigned int nbr, char type)
{
	if (type == 'x')
		return (ft_ultoa_base((unsigned long) nbr, "0123456789abcdef"));
	else if (type == 'X')
		return (ft_ultoa_base((unsigned long) nbr, "0123456789ABCDEF"));
	return (NULL);
}
