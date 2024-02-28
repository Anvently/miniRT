/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:12:17 by npirard           #+#    #+#             */
/*   Updated: 2024/01/08 14:50:22 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char	*ft_strncpy(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

/// @brief Expand line with given string.
/// @param line Address of the pointer to line. The pointer is directly
/// modified.
/// If NULL, a new string will be allocated. Ends with a NULL byte.
/// @param tail String to expand line with.
/// @param l_line Current size of line.
/// @param n Number of characters to add from tail
/// @return Address of newly allocated string.
/// NULL if allocation error.
static char	*line_join(char **line, const char *tail, size_t l_line, size_t n)
{
	char	*buffer;
	size_t	i;

	buffer = malloc((size_t) l_line + n + 1);
	if (buffer)
	{
		if (*line)
			ft_strncpy(buffer, *line, l_line);
		i = 0;
		while (i < n)
		{
			buffer[l_line + i] = tail[i];
			i++;
		}
		buffer[l_line + n] = '\0';
	}
	free(*line);
	*line = buffer;
	return (buffer);
}

/// @brief Check if a line can be found within buffer.
/// If so, expand current line with all chars preceding \\n in buffer.
/// @param buffer Every read character is replaced with NULL bytes and
/// first null bytes of buffer are ignored (as they have been already read).
/// Non read characters are left untouched to ensure next call to
/// function get_next_line will work.
/// @param line Can be NULL if no line started in a previous call to the
/// function. String is expanded with every character preceding \\n
/// if found or with the full buffer if no \\n is found. Always NULL
/// terminated.
/// @param Current Pointer toward the current size of line. The size
/// is updated after any manipulation of line.
/// @return Address of line if \\n is found.
/// NULL if no new line or error.
static char	*parse_buffer(char *buffer, char **line, size_t *l_line)
{
	size_t	i;
	size_t	start;

	start = 0;
	i = 0;
	while (i < BUFFER_SIZE && buffer[i] == '\0')
	{
			start++;
			i++;
	}
	while (i < BUFFER_SIZE)
	{
		if (buffer[i] == '\n' || buffer[i] == '\0')
		{
			line_join(line, buffer + start, *l_line, i - start + 1);
			ft_memset(buffer, '\0', i + 1);
			return (*line);
		}
		i++;
	}
	if (BUFFER_SIZE - start > 0)
		line_join(line, buffer + start, *l_line, BUFFER_SIZE - start);
	*l_line += BUFFER_SIZE - start;
	return (NULL);
}

/// @brief Fill buffer with NULL byte then read() into given file descriptor.
/// @param fd File descriptor to read into.
/// @param buffer Buffer receiving the data of the read.
/// @return Number of byte read.
/// 0 if EOF.
/// -1 if error.
static ssize_t	update_buffer(int fd, char *buffer)
{
	if (!buffer)
		return (0);
	ft_memset(buffer, '\0', BUFFER_SIZE);
	return (read(fd, buffer, BUFFER_SIZE));
}

/// @brief Read the next line into a given file.
/// @param fd File descriptor to read into. |
/// 0. STDIN_FILENO. |
/// 0-1024
/// @return The line that has been read, including \\n.
/// No \\n if end at the end of file.
/// NULL if error or no line is found.
char	*ft_gnl(int fd)
{
	char		*line;
	size_t		l_line;
	static char	buffer[1024][BUFFER_SIZE];

	line = NULL;
	l_line = 0;
	if (fd < 0 || fd > 1024)
		return (NULL);
	if (parse_buffer(buffer[fd], &line, &l_line))
		return (line);
	while (update_buffer(fd, buffer[fd]) > 0)
		if (parse_buffer(buffer[fd], &line, &l_line))
			return (line);
	return (line);
}
