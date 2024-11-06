/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:56:29 by mbouhia           #+#    #+#             */
/*   Updated: 2024/11/06 15:56:33 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strmerge(char **dest, char *src)
{
	char	*tmp;
	size_t	size;

	if (!*dest)
		*dest = ft_strdup("");
	if (!*dest)
		return ;
	size = ft_strlen(*dest) + ft_strlen(src);
	tmp = malloc((size + 1) * sizeof(char));
	if (tmp)
	{
		ft_strcpy(tmp, *dest);
		ft_strcat(tmp, src);
		free(*dest);
		*dest = tmp;
	}
}

char	*extract_line(char **stored)
{
	char	*newline_pos;
	char	*line;
	char	*remaining;

	newline_pos = ft_strchr(*stored, '\n');
	if (newline_pos)
	{
		*newline_pos = '\0';
		line = ft_strdup(*stored);
		if (!line)
			return (NULL);
		remaining = ft_strdup(newline_pos + 1);
		free(*stored);
		*stored = remaining;
		return (line);
	}
	else
	{
		line = *stored;
		*stored = NULL;
		return (line);
	}
}

char	*get_next_line(int fd)
{
	static char	*stored[OPEN_MAX];
	char		buffer[BUFFER_SIZE + 1];
	int			bytes_read;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	while (!stored[fd] || !ft_strchr(stored[fd], '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(stored[fd]);
			stored[fd] = NULL;
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		ft_strmerge(&stored[fd], buffer);
		if (!stored[fd])
			return (NULL);
	}
	if (!stored[fd] || stored[fd][0] == '\0')
	{
		free(stored[fd]);
		stored[fd] = NULL;
		return (NULL);
	}
	return (extract_line(&stored[fd]));
}
