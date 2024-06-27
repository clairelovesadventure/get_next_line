/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:38:45 by shutan            #+#    #+#             */
/*   Updated: 2024/06/28 00:41:07 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *read_file(int	fd, char *line_plus)
{
	int		bytes_read;
	char	*buff;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	if (!line_plus)
		line_plus = ft_calloc(1, 1);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		buff[bytes_read] = '\0';
		if (ft_strchr(buff, '\n'))
			break;
		line_plus = ft_strjoin(line_plus, buff);
	}
	free(buff);
	return (line_plus);
}

char	*contract_line(char *line_plus)
{
	char	*line;
	int		i;

	i = 0;
	while (line_plus[i] != '\n' && line_plus[i])
		i++;
	line = malloc((i + 2) * sizeof(char));
	i = 0;
	while (line_plus[i] != '\n' && line_plus[i])
		line[i++] = line_plus[i++]; 
	if (!line_plus[i])
		return (line_plus);
	line[i] = '\n';
	line[i + 1] = '\0';
	return(line);
}

char *get_next_line(int fd)
{
	static char	*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = read_file(fd, buff);
	buff = contract_line(buff);
	return (buff);
}

int	main(void)
{
	int		fd;

	fd = open("./example.txt", O_RDONLY | O_CREAT);
	get_next_line(fd);
	get_next_line(fd);
	return(0);
}