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
#include <stdio.h>

static char	*set_line(char *line_buffer)
{
	char	*left_c;
	ssize_t	i;

	if (!line_buffer)
		return (NULL);
	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0' || line_buffer[i + 1] == '\0')
	{
		printf("baska bir sey yok\n");
		return (NULL);
	}
	left_c = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (!left_c)
	{
		printf("8hatayi burada aldi\n");
		return (free(line_buffer), line_buffer = NULL, NULL);
	}
	line_buffer[i + 1] = 0;
	return (left_c);
}

static char	*fill_line(int fd, char *left_c, char *buffer)
{
	char	*tmp;
	ssize_t	b_read;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
		{
			printf("7hatayi burada aldi\n");
			return (free(left_c), left_c = NULL, NULL);
		}
		else if (!b_read)
			break ;
		buffer[b_read] = '\0';
		if (!left_c)
			left_c = ft_strdup("");
		if (!left_c)
			printf("6dup\n");
		tmp = ft_strjoin(left_c, buffer);
		if (!tmp)
			printf("5hatayi burada aldi\n");
		free(left_c);
		left_c = tmp;
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

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (free(left_c), left_c = NULL, NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * 1);
	if (!buffer)
	{
		printf("1hatayi burada aldi\n");
		return (free(left_c), left_c = NULL, NULL);
	}
	line = fill_line(fd, left_c, buffer);
	if (!line)
	{
		printf("2hatayi burada aldi\n");
		return (free(buffer), NULL);
	}
	left_c = set_line(line);
	if (!left_c)
	{
		printf("3hatayi burada aldi\n");
	}
	if (!line)
		printf("4hatayi burada aldi\n");
	return (free(buffer), line);
}
