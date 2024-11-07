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

#include "get_next_line_bonus.h"

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

char	*extract_line(char **stored, char *newline_pos)
{
	char	*line;
	char	*remaining;

	if (!*stored || *stored[0] == '\0')
	{
		free(*stored);
		*stored = NULL;
		return (NULL);
	}
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
	line = *stored;
	*stored = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stored[OPEN_MAX];
	char		*buffer;
	char		*newline_pos;
	int			bytes_read;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	newline_pos = NULL;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if(!buffer)
		return NULL;
	while (!stored[fd] || !ft_strchr(stored[fd], '\n', &newline_pos))
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
	free(buffer);
	buffer = NULL;
	return (extract_line(&stored[fd], newline_pos));
}
