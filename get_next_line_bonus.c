/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: flima <flima@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/18 15:48:58 by mahkilic      #+#    #+#                 */
/*   Updated: 2024/11/27 20:06:13 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*left_over(char *storage)
{
	char	*new_storage;
	char	*ptr;
	int		len;

	ptr = ft_strchr(storage, '\n');
	if (!ptr)
		return (free(storage), storage = NULL, new_storage = NULL);
	else
		len = (ptr - storage) + 1;
	if (!storage[len])
		return (free(storage), storage = NULL);
	new_storage = ft_substr(storage, len, ft_strlen(storage) - len);
	(free(storage), storage = NULL);
	if (!new_storage)
		return (NULL);
	return (new_storage);
}

static char	*new_line(char *storage)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_strchr(storage, '\n');
	len = (ptr - storage) + 1;
	line = ft_substr(storage, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

static char	*read_buffer(int fd, char *storage)
{
	int		rid;
	char	*buffer;

	rid = 1;
	buffer = malloc((BUFFER_SIZE + 1) * 1);
	if (!buffer)
		return (free(storage), storage = NULL, NULL);
	buffer[0] = '\0';
	while (rid > 0 && !ft_strchr(buffer, '\n'))
	{
		rid = read (fd, buffer, BUFFER_SIZE);
		if (rid > 0)
		{
			buffer[rid] = '\0';
			storage = ft_strjoin(storage, buffer);
		}
	}
	free(buffer);
	if (rid == -1)
		return (free(storage), storage = NULL, NULL);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*line;

	if (fd < 0)
		return (free(storage[fd]), storage[fd] = NULL, NULL);
	if ((storage[fd] && !ft_strchr(storage[fd], '\n')) || !storage[fd])
		storage[fd] = read_buffer (fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = new_line(storage[fd]);
	if (!line)
		return (free(storage[fd]), storage[fd] = NULL, NULL);
	storage[fd] = left_over(storage[fd]);
	return (line);
}
