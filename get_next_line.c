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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joinstrs;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	joinstrs = malloc((size + 1) * sizeof(char));
	if (!joinstrs)
		return (NULL);
	ft_strcpy(joinstrs, s1);
	ft_strcat(joinstrs, s2);
	return (joinstrs);
}

void	ft_strmerge(char **dest, char *src)
{
	char	*temp;

	if (!*dest)
		*dest = ft_strdup("");
	if (!*dest)
		return ;
	temp = ft_strjoin(*dest, src);
	if (temp)
	{
		free(*dest);
		*dest = temp;
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
