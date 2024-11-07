/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utilities.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:56:44 by mbouhia           #+#    #+#             */
/*   Updated: 2024/11/06 15:56:45 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t	destlen;
	char	*original;

	original = dest;
	destlen = ft_strlen(dest);
	while (*src)
	{
		*(dest + destlen) = *src;
		destlen++;
		src++;
	}
	*(dest + destlen) = '\0';
	return (original);
}

char	*ft_strchr(const char *str, int c, char **ptr)
{
	while (*str)
	{
		if (*str == (char)c)
		{
			*ptr = (char *)str;
			return ((char *)str);
		}
		str++;
	}
	if ((char)c == '\0')
	{
		*ptr = (char *)str;
		return ((char *)str);
	}
	return (NULL);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(src);
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	ft_strcpy(dest, src);
	return (dest);
}
