/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:11:44 by shutan            #+#    #+#             */
/*   Updated: 2024/06/28 00:08:41 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == 0)
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}


void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	if (count != 0 && count * size / count != size)
		return (NULL);
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	while (i < size * count)
	{
		tmp[i] = 0;
		i++;
	}
	return (tmp);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	count1;
	size_t	count2;
	size_t	i;
	char	*tmp;

	i = 0;
	count1 = ft_strlen((char *)s1);
	count2 = ft_strlen((char *)s2);
	tmp = (char *)malloc(sizeof(char) * (count1 + count2) + 1);
	if (!tmp)
		return (NULL);
	while (i < count1)
	{
		tmp[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < count2)
	{
		tmp[count1 + i] = s2[i];
		i++;
	}
	tmp[count1 + i] = '\0';
	free(s1);
	return (tmp);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (!dest && !src)
		return (dest);
	d = (char *)dest;
	s = (const char *)src;
	if (d < s)
		while (n--)
			*d++ = *s++;
	else
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	return (dest);
}
