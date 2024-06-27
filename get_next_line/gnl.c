#include "get_next_line.h"
#include <stdio.h>

/* with the problem:
 free(): double free detected in tcache 2
zsh: IOT instruction (core dumped)  ./a.out

char *read_file(int fd, char *leftover)
{
    int     bytes_read;
    char    *buff;
    char    *temp;

    buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buff)
        return (NULL);
    bytes_read = 1;
    while (bytes_read > 0)
    {
        bytes_read = read(fd, buff, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(buff);
            return (NULL);
        }
        buff[bytes_read] = '\0';
        temp = leftover;
        leftover = ft_strjoin(leftover, buff);
        free(temp);
        if (ft_strchr(buff, '\n'))
            break;
    }
    free(buff);
    return (leftover);
}

char *extract_line(char *leftover)
{
    char    *line;
    int     i;

    i = 0;
    if (!leftover[i])
        return (NULL);
    while (leftover[i] && leftover[i] != '\n')
        i++;
    line = (char *)malloc((i + 2) * sizeof(char));
    if (!line)
        return (NULL);
    i = 0;
    while (leftover[i] && leftover[i] != '\n')
    {
        line[i] = leftover[i];
        i++;
    }
    if (leftover[i] == '\n')
    {
        line[i] = leftover[i];
        i++;
    }
    line[i] = '\0';
    return (line);
}

char *save_leftover(char *leftover)
{
    char    *new_leftover;
    int     i;
    int     j;

    i = 0;
    while (leftover[i] && leftover[i] != '\n')
        i++;
    if (!leftover[i])
    {
        free(leftover);
        return (NULL);
    }
    new_leftover = (char *)malloc((ft_strlen(leftover) - i + 1) * sizeof(char));
    if (!new_leftover)
        return (NULL);
    i++;
    j = 0;
    while (leftover[i])
        new_leftover[j++] = leftover[i++];
    new_leftover[j] = '\0';
    free(leftover);
    return (new_leftover);
}

char *get_next_line(int fd)
{
    static char *leftover;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    leftover = read_file(fd, leftover);
    if (!leftover)
        return (NULL);
    line = extract_line(leftover);
    leftover = save_leftover(leftover);
    return (line);
}
 */
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

char *read_file(int fd, char *leftover)
{
    int     bytes_read;
    char    *buff;
    char    *temp;

    buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buff)
        return (NULL);
    bytes_read = 1;
    while (bytes_read > 0)
    {
        bytes_read = read(fd, buff, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(buff);
            return (NULL);
        }
        buff[bytes_read] = '\0';
        temp = leftover;
        leftover = ft_strjoin(leftover, buff);
        if (temp)
            free(temp);
        if (ft_strchr(buff, '\n'))
            break;
    }
    free(buff);
    return (leftover);
}

char *extract_line(char *leftover)
{
    char    *line;
    int     i;

    i = 0;
    if (!leftover || !leftover[i])
        return (NULL);
    while (leftover[i] && leftover[i] != '\n')
        i++;
    line = (char *)malloc((i + 2) * sizeof(char));
    if (!line)
        return (NULL);
    i = 0;
    while (leftover[i] && leftover[i] != '\n')
    {
        line[i] = leftover[i];
        i++;
    }
    if (leftover[i] == '\n')
    {
        line[i] = leftover[i];
        i++;
    }
    line[i] = '\0';
    return (line);
}

char *save_leftover(char *leftover)
{
    char    *new_leftover;
    int     i;
    int     j;

    i = 0;
    while (leftover[i] && leftover[i] != '\n')
        i++;
    if (!leftover[i])
    {
        free(leftover);
        return (NULL);
    }
    new_leftover = (char *)malloc((ft_strlen(leftover) - i + 1) * sizeof(char));
    if (!new_leftover)
    {
        free(leftover);
        return (NULL);
    }
    i++;
    j = 0;
    while (leftover[i])
        new_leftover[j++] = leftover[i++];
    new_leftover[j] = '\0';
    free(leftover);
    return (new_leftover);
}

char *get_next_line(int fd)
{
    static char *leftover = NULL;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    leftover = read_file(fd, leftover);
    if (!leftover)
        return (NULL);
    line = extract_line(leftover);
    leftover = save_leftover(leftover);
    return (line);
}

int main(void)
{
    int     fd;
    char    *line;

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
    close(fd);
    return (0);
}

