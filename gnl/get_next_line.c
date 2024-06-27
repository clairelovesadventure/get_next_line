/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:33:52 by shutan            #+#    #+#             */
/*   Updated: 2024/06/28 01:27:10 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

static char	*ft_read_to_leftover(int fd, char *leftover)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(leftover, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		leftover = ft_strjoin(leftover, buff);
	}
	free(buff);
	return (leftover);
}

static char	*ft_get_line(char *leftover)
{
	int		i;
	char	*str;

	i = 0;
	if (!leftover[i])
		return (NULL);
	while (leftover[i] && leftover[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (leftover[i] && leftover[i] != '\n')
	{
		str[i] = leftover[i];
		i++;
	}
	if (leftover[i] == '\n')
	{
		str[i] = leftover[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_new_leftover(char *leftover)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (!leftover[i])
	{
		free(leftover);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(leftover) - i + 1));
	if (!str)
	{
		free(leftover);
		return (NULL);
	}
	i++;
	j = 0;
	while (leftover[i])
		str[j++] = leftover[i++];
	str[j] = '\0';
	free(leftover);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*leftover;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = ft_read_to_leftover(fd, leftover);
	if (!leftover)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	line = ft_get_line(leftover);
	leftover = ft_new_leftover(leftover);
	if (!leftover || !*leftover)
	{
		free(leftover);
		leftover = NULL;
	}
	return (line);
}

/* int	main(void)
{
	int		fd;
	char	*line;

	fd = open("./example.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
} */