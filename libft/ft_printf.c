/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:47:13 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

///* ### ```%[m$][flags][width][.precision]conversion```
///*
///*
///* ### m$
///*
///* Alternate format where m is the index of a given argument
///* Allows to use a single argument multiple time.
///*
///* ### flags
///*
///* ```#``` Value is converted to alternate form.
///* For x or X : a non zero result has the string 0x placed before
///* ```0``` The value is padded on the left with zero instead of blank.
///* Works for ```d, i, u, x, X```. A minimum width must be defined.
///* Will be ignored if it comes with a precision flag
///* ```-``` The value is left adjusted on the given width.
///* Overrides a 0 if both given.
///* ```' '``` A blank is left before a positive number. Doesn't affect
///* negative numbers. Works for signed type.
///* ```+``` A sign is always placed before a signed number.
///* Overrides ```' '``` if both given. Expand field width if necessary.
///* Works for signed type.
///*
///* ### width
///*
///* Define a minimum field width. Default padding is right unless
///* ```-``` flag has been given.
///* Can be given as a decimal digit or as * to use the value specified
///* in the next argument or ```*m$``` to use the value specified in the m-th
///* argument.
///*
///* ### precision
///*
///* ```.``` followed by a decimal digit, ```*``` to use the value specified
///* in the next argument or ```*m$``` to use the value specified in the m-th
///* argument. Defines the minimum number of digit to appear for
///* ```d, i, u, x, X``` conversion or the maximum number of character to
///*  be printed for ```s``` conversion. Overrides given field width if bigger.
///* If no precision size is given, zero is to be taken. A 0 precision will
///* only print non-zero numbers and won't print any character when applied to a
///* string conversion. A negative precision (can only be given in parameter)
///* will disable precision flag.
///*
///* ### conversion
///*
///* ```c``` print a char
///* ```s``` print a string
///* ```p``` print hexadecimal address
///* ```d``` print decimal number
///* ```i``` print integer in base 10
///* ```u``` print unsigned decimal
///* ```x``` print a number in hexadecimal using lowercase char
///* ```X``` print a number in hexadecimal using uppercase char
///* ```%``` print '%' sign
///* ``` Varg ```
int	ft_printf(const char *str, ...)
{
	t_list			*fields;
	int				nbr_chars;
	va_list			args;

	nbr_chars = 0;
	if (!str || !*str)
		return (0);
	va_start(args, str);
	fields = build_fields((char *) str, &args);
	va_end(args);
	check_index_format(-1, 0, "");
	if (!fields)
		return (-1);
	if (check_fields(fields))
		nbr_chars = print_fields(fields);
	ft_lstclear(&fields, &free_field);
	return (nbr_chars);
}
