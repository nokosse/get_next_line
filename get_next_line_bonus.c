/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:26:38 by kvisouth          #+#    #+#             */
/*   Updated: 2022/12/28 15:30:50 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strcut(char *str)
{
	char	*cutted_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\n')
		i++;
	cutted_str = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!cutted_str)
		return (NULL);
	i++;
	while (str[i])
		cutted_str[j++] = str[i++];
	cutted_str[j] = '\0';
	free(str);
	return (cutted_str);
}

static int	check_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (-1);
}

static char	*stash_checking(int fd, char *stash, char *buff, int readed)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	readed = read(fd, buff, BUFFER_SIZE);
	if (readed <= 0 && !stash)
		return (free(buff), NULL);
	buff[readed] = '\0';
	if (!stash)
		stash = ft_substr(buff, 0, ft_strlen(buff));
	else
		stash = ft_strjoin(stash, buff);
	free(buff);
	if (stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (stash);
}

char	*cases_handing(char **stash, int readed)
{
	char	*line;

	if (readed < BUFFER_SIZE && check_line(*stash) == -1)
	{
		line = ft_substr(*stash, 0, ft_strlen(*stash));
		free(*stash);
		*stash = NULL;
		return (line);
	}
	else if (check_line(*stash) != -1)
	{
		line = ft_substr(*stash, 0, ft_strchr(*stash, '\n') - *stash + 1);
		*stash = ft_strcut(*stash);
		return (line);
	}
	return (NULL);
}

/*
	GNL with bonus.
	I added [1024] to *stash (1024 is the max number of files that can be open)
	In GNL, I added [fd] to every *stash so it works on the proper file.
	Because I need the same amout of different *stash as the max number of files.
*/

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*buff;
	char		*line;
	int			readed;

	readed = 0;
	buff = NULL;
	if (fd > 1024)
		return (NULL);
	stash[fd] = stash_checking(fd, stash[fd], buff, readed);
	while (stash[fd])
	{
		buff = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!buff)
			return (NULL);
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
			return (free(buff), NULL);
		stash[fd] = ft_strjoin(stash[fd], buff);
		free(buff);
		line = cases_handing(&stash[fd], readed);
		if (line)
			return (line);
	}
	return (NULL);
}

// int main (void)
// {
// 	int fd;
// 	int fd1;
// 	char *str;
// 	char *str1;

// 	fd = open("test1", O_RDONLY);
// 	fd1 = open("test2", O_RDONLY);
// 	str = get_next_line(fd);
// 	str1 = get_next_line(fd1);
// 	while (str != NULL)
// 	{
// 		printf("%s", str);
// 		free(str);
// 		str = get_next_line(fd);
// 		printf("%s", str1);
// 		free(str1);
// 		str1 = get_next_line(fd1);
// 	}
// }
