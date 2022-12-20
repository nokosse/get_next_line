/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:26:38 by kvisouth          #+#    #+#             */
/*   Updated: 2022/12/20 20:03:09 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
	check_line is juste a boolean that returns 1 if our string contains a \n.
	Else it returns -1.
*/

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

/*
	ft_strcut is used in one case in GNL.
	When the stash contains a \n, we are cutting the string
	from the \n to the end of the string, so our new stash does not
	longer contain the \n ans the past line.
*/

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

/*
	GNL is the main function of the project.
	How it simply works : We read the file and store the result in a buffer.
	Then we concatenate the buffer to the stash.
	Then we check if the stash contains a \n.
	If it does, we cut the stash from the \n to the end of the string.
	Then we return the line.
	Else we return NULL.
*/

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buff;
	char		*line;
	int			readed;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	readed = read(fd, buff, BUFFER_SIZE);
	if (readed <= 0 && !stash)
	{
		free(buff);
		return (NULL);
	}
	buff[readed] = '\0';
	if (!stash)
		stash = ft_strdup(buff);
	else
		stash = ft_strjoin(stash, buff);
	free(buff);
	while (stash)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		readed = read(fd, buff, BUFFER_SIZE);
		buff[readed] = '\0';
		stash = ft_strjoin(stash, buff);
		free(buff);
		if (readed < BUFFER_SIZE && check_line(stash) == -1)
		{
			line = ft_strdup(stash);
			free(stash);
			stash = NULL;
			return (line);
		}
		else if (check_line(stash) != -1)
		{
			line = ft_substr(stash, 0, ft_strchr(stash, '\n') - stash + 1);
			stash = ft_strcut(stash);
			return (line);
		}
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	char	*line;

	int i = 0;
	int fd = open("gnlTester/files/41_no_nl", O_RDONLY);
	if (argc == 2)
	{
		while (i < atoi(argv[1]))
		{
			line = get_next_line(fd);
			printf("Ligne %d : %s\n", i + 1, line);
			free(line);
			i++;
		}
	}
	return (0);
}

/*

Path to Tripouille test files :

gnlTester/files/nl
gnlTester/files/41_no_nl
gnlTester/files/41_with_nl
gnlTester/files/42_no_nl
gnlTester/files/42_with_nl
gnlTester/files/43_no_nl
gnlTester/files/43_with_nl
gnlTester/files/alternate_line_nl_no_nl
gnlTester/files/alternate_line_nl_with_nl
gnlTester/files/big_line_no_nl
gnlTester/files/big_line_with_nl
gnlTester/files/empty
gnlTester/files/multiple_lines_no_nl
gnlTester/files/multiple_lines_with_nl
gnlTester/files/multiple_nlx5

*/