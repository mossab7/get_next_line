/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 22:39:55 by mbouhia           #+#    #+#             */
/*   Updated: 2024/11/09 22:39:57 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(t_stored *stored, int c)
{
	size_t	i;

	i = stored->last_pos;
	if (!stored->content)
		return (NULL);
	while (stored->content[i])
	{
		if (stored->content[i] == (char)c)
		{
			stored->last_pos = i;
			return (&stored->content[i]);
		}
		i++;
	}
	stored->last_pos = i;
	if ((char)c == '\0')
		return (&stored->content[i]);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*extract_line(t_stored *stored)
{
	char	*line;
	char	*remaining;

	if (stored->content[stored->last_pos] == '\n')
		stored->last_pos++;
	else if (stored->content[stored->last_pos] != '\0')
		stored->last_pos = ft_strlen(stored->content);
	line = ft_substr(stored->content, 0, stored->last_pos);
	if (!line)
		return (NULL);
	if (stored->content[stored->last_pos])
	{
		remaining = ft_strdup(&stored->content[stored->last_pos]);
		if (!remaining)
		{
			free(line);
			return (NULL);
		}
	}
	else
		remaining = NULL;
	free(stored->content);
	stored->content = remaining;
	return (line);
}

size_t	read_to_buffer(t_stored *stored, int fd)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (bytes_read);
	}
	buffer[bytes_read] = '\0';
	temp = ft_strjoin(stored->content, buffer);
	free(buffer);
	if (!temp)
		return (0);
	free(stored->content);
	stored->content = temp;
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static t_stored	stored;
	ssize_t			bytes_read;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	stored.last_pos = 0;
	if (!stored.content)
		bytes_read = read_to_buffer(&stored, fd);
	while (!ft_strchr(&stored, '\n'))
	{
		bytes_read = read_to_buffer(&stored, fd);
		if (bytes_read <= 0)
			break ;
	}
	if (!stored.content)
		return (NULL);
	return (extract_line(&stored));
}
