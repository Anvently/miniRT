/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:23:38 by npirard           #+#    #+#             */
/*   Updated: 2024/02/21 13:14:12 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# elif BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

/* ---------------------------------- MATH ---------------------------------- */

int		ft_abs(int n);
int		ft_imax(int a, int b);
double	ft_dmax(double a, double b);
void	*ft_max(void *a, void *b, size_t size);

///------------------------ CHAR TEST -----------------------------

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(char c);

///------------------------ CHAR CONVERSION ------------------------

int		ft_toupper(int c);
int		ft_tolower(int c);

///------------------------ STRING EDITION ------------------------

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin2(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);

///----------------------- STRING TEST -------------------------

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strncmp_rev(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

///------------------------------ MEM --------------------------

void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t nmenb, size_t size);

/* --------------------------------- STRINGS -------------------------------- */

char	**ft_split(char const *s, char c);
char	**ft_free_strs(char **strings);
char	***ft_free_strss(char ***strs);
int		ft_strslen(char **strs);
int		ft_strsslen(char ***strs);
char	*ft_strschr(char **strs, char *str);

///---------------------- TYPE CONVERSION -----------------------

int		ft_atoi(const char *nptr);
int		ft_atol(const char *nptr);
int		ft_strtoi(const char *str, int *dest);
int		ft_strtof(char *str, float *dest, char **ptr);
int		ft_strtod(char *str, double *dest, char **ptr);
char	*ft_itoa(int n);
char	*ft_uitoa(unsigned int n);
char	*ft_ultoa(unsigned long n);
char	*ft_ultoa_base(unsigned long n, char *base);

///------------------------ ITERATION ---------------------------

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

///------------------------ FD I/O ----------------------------

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/* ---------------------------------- ERROR --------------------------------- */

void	*alloc_error(void);
void	*null_error(char *msg);

/* ---------------------------------- PRINT --------------------------------- */

void	ft_print_strs(char **strs);

/*--------------------------------------------------------------
---------------------------- LIST ------------------------------
-----------------------------------------------------------------*/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

///----------------------- EDITION ----------------------------

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **list, t_list *new);
void	ft_lstadd_back(t_list **list, t_list *new);
void	ft_lstinsert(t_list *node_before, t_list *node);
void	ft_lstdelone(t_list *list, void (*del)(void *));
void	ft_lstdelif(t_list **lst, int (*f)(void *), void (*del)(void *));
void	ft_lstclear(t_list **list, void (*del)(void *));
void	ft_lstiter(t_list *list, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstmerge(t_list *node, t_list **from);

///----------------------- READ ------------------------------

int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstprint(t_list *pt, void (*disp)(void *));

/* ------------------------------- STRING LIST ------------------------------ */

void	ft_lst_str_print(t_list *lst);
int		ft_lst_str_append(t_list **lst, char *str);
char	**ft_lsttostrs(t_list *list);
t_list	*ft_strstolst(char **strs);

///-----------------------------------------------------------

/*--------------------------------------------------------------
---------------------- GET_NEXT_LINE -----------------------------
-----------------------------------------------------------------*/

char	*ft_gnl(int fd);

/*--------------------------------------------------------------
---------------------------- PRINTF -----------------------------
-----------------------------------------------------------------*/

int		ft_printf(const char *str, ...);

//Error handling
void	*null_error(char *msg);
void	*format_error(int error, char *parsing);
void	*alloc_error(void);
int		arg_index_error(int error, int index);
bool	flag_error(char flag);

///* ```# alternate form``` Value is converted to alternate form.
///* For x or X : a non zero result has the string 0x placed before
///*
///* ```0 zero_padding``` The value is padded on the left with zero
///* instead of blank. Works for ```d, i, u, x, X```. A minimum width
///* must be defined. Will be ignored if it comes with a precision flag
///*
///* ```- left_justify``` The value is left adjusted on the given width.
///* Overrides a 0 if both given.
///*
///* ```' ' sign_blank``` A blank is left before a positive number.
///* Doesn't affect negative numbers.
///*
///* ```+ force_sign``` A sign is always placed before a signed number.
///* Overrides ```' '``` if both given. Expand field width if necessary.
///*
///* ```. precision``` Defines if a precision was given.
typedef struct s_flags
{
	bool	alternate_form;
	bool	zero_padding;
	bool	left_justify;
	bool	sign_blank;
	bool	force_sign;
	bool	precision;
}			t_flags;

///* ### Flags
///*
///* Boolean list of all flags. All flags are set to false by default.
///*
///* ### Width
///*
///* Define a minimum field width. Default padding is right unless
///* ```-``` flag has been given.
///* Can be given as a decimal digit or as * to use the value specified
///* in a given argument.
///*
///* ### Precision
///*
///* Defines the minimum number of digit to appear for ```d, i, u, x, X```
///* conversion or the maximum number of character to be printed for ```s```
///*  conversion. Overrides given field width if bigger. A 0 precision will
///* only print non-zero numbers and won't print any character when applied to a
///* string conversion.
///*
///* ### Type
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
///*
///* ### Value
///*
///* Address of the value to print. Type is specified in conversion member.
///* NULL if value is not assigned yet (case of %).
typedef struct s_field
{
	t_flags	flags;
	size_t	width;
	int		precision;
	char	type;
	void	*value;
}			t_field;

//Structure util

t_list	*new_field_node(void);
void	init_field(t_field *field);
void	free_field(void *field);

//Input parsing

t_list	*build_fields(char *str, va_list *va_args);
char	*get_next_field(char *str, t_list **fields,
			t_list **args_req, int *arg_index);
char	*parse_field(char *str, t_field *field,
			t_list **args_req, int *arg_index);

//Field parsing

char	*parse_arg_index(char *str, int *arg_index,
			int *given_index, bool begin);
char	*parse_flags(char *str, t_field *field);
char	*parse_width(char *str, t_field *field,
			t_list **args_req, int *arg_index);
char	*parse_precision(char *str, t_field *field,
			t_list **args_req, int *arg_index);
char	*parse_conversion_type(char *str, t_field *field);

typedef struct s_arg_req
{
	size_t	index;
	void	*dest;
	char	type;
}			t_arg_req;

//Struct util

t_list	*new_argument_node(void);
void	free_arg_req(void *arg_req);
t_list	*insert_arg_req(t_list **args_req, t_list *arg_node);

//Args retrieving

t_list	*register_arg_request(t_list **args_req, void *dest,
			size_t index, char type);
int		retrieve_arguments(t_list *args_req, va_list *va_args);

//Check

bool	check_index_format(int new_format, int given_index, char *parsing);
bool	check_type_conflict(t_arg_req *node1, t_arg_req *node2);
bool	check_flag_conflict(t_field *field);
bool	check_fields(t_list *fields);

//Casting

void	*alloc_arg_value(char type);
void	*get_arg_value(va_list *va_args, char type);
void	cast_to_dest(void *dest, void *value, char type);

//Printing functions

int		print_fields(t_list *fields);
int		print_field(t_field *field);
char	*build_str(t_field *field);
char	*get_str_value(t_field *field);

//Conversion

char	*char_to_str(char c);
char	*address_to_str(unsigned long addr);
char	*str_to_str(char *str);
char	*hexa_to_str(unsigned int nbr, char type);

//Formatting

char	*format_str(t_field *field, char *str);
char	*format_precision(t_field *field, char *str);
char	*format_alt_form(t_field *field, char *str);
char	*format_sign(t_field *field, char *str);
char	*format_width(t_field *field, char *str);
char	*insert_n_char(char *str, int start, int n, char c);

#endif
