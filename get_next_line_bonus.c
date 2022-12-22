/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:26:38 by kvisouth          #+#    #+#             */
/*   Updated: 2022/12/22 14:02:51 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
	This function handles the errors of the read function.
	It returns 0 if there is an error.
	Else it returns 1.
*/

static int	read_errors_handling(int readed, char *buff)
{
	if (readed == -1)
	{
		free(buff);
		return (0);
	}
	return (1);
}

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
	I used this function to make GNL less than 25 lines.
	This block of code was between the variable declaration and the while loop.
	This function is checking the validity of fd, BUFFER_SIZE and the stash.
	And it's initializing our stash for the rest of GNL if the verification passed.
*/

static char	*stash_checking(int fd, char *stash, char *buff, int readed)
{
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

/*
	I also used this function to make GNL less than 25 lines.
	This bllock of code was replaced by the 3 last lines in the while loop.
	This function is handling the 2 cases of GNL.
	1. The last line case.
	2. The line with a \n case.
	It's parameter is **stash and not *stash because of we need to modify the
	original stash, and not a copy of it. It's called a : Pass by reference in C.
*/

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
		*stash = ft_gnl_strcut(*stash);
		return (line);
	}
	return (NULL);
}

/*
	GNL is a function that reads a file line by line.
	We read the file until we find a \n or the end of the file.
	And we return the line we just read.
	It returns NULL if there is nothing to read.
*/

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buff;
	char		*line;
	int			readed;

	readed = 0;
	buff = NULL;
	stash = stash_checking(fd, stash, buff, readed);
	while (stash)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		readed = read(fd, buff, BUFFER_SIZE);
		if (read_errors_handling(readed, buff) == 0)
			return (NULL);
		buff[readed] = '\0';
		stash = ft_strjoin(stash, buff);
		free(buff);
		line = cases_handing(&stash, readed);
		if (line)
			return (line);
	}
	return (NULL);
}

// int main(int argc, char **argv)
// {
// 	char	*line;

// 	int i = 0;
// 	int fd = open("text.txt", O_RDONLY);
// 	if (argc == 2)
// 	{
// 		while (i < atoi(argv[1]))
// 		{
// 			line = get_next_line(fd);
// 			printf("Ligne %d : %s\n", i + 1, line);
// 			free(line);
// 			i++;
// 		}
// 	}
// 	return (0);
// }

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
gnlTester/files/multiple_line_no_nl
gnlTester/files/multiple_line_with_nl
gnlTester/files/multiple_nlx5

*/