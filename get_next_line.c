/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/18 15:48:58 by mahkilic      #+#    #+#                 */
/*   Updated: 2024/11/18 15:48:58 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == s[i])
		return ((char *)&s[i]);
	return (0);
}

static char	*set_line(char *line_buffer)
{
	char	*left_c;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[1] == 0)
		return (NULL);
	left_c = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*left_c == 0)
	{
		free(left_c);
		free(line_buffer);
		left_c = NULL;
	}
	line_buffer[i + 1] = 0;
	return (left_c);
}

static char	*fill_line(int fd, char *left_c, char *buffer)
{
	ssize_t	b_read;
	char	*tmp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
			return (free(left_c), free(buffer), NULL);
		else if (b_read == 0)
			break ;
		buffer[b_read] = 0;
		if (left_c == 0)
			left_c = ft_strdup("");
		if (!left_c)
			return (free(left_c), free(buffer), NULL);
		tmp = left_c;
		left_c = ft_strjoin(tmp, buffer);
		if (!left_c)
			return (free(tmp), free(buffer), NULL);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left_c);
}

char	*get_next_line(int fd)
{
	static char	*left_c;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
	{
		free(left_c);
		free(buffer);
		left_c = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (buffer == 0)
		return (free(left_c), NULL);
	line = fill_line(fd, left_c, buffer);
	if (!line)
		return (NULL);
	free(buffer);
	buffer = NULL;
	if (line == 0)
		return (NULL);
	left_c = set_line(line);
	return (line);
}

