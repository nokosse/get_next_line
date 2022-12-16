/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:26:38 by kvisouth          #+#    #+#             */
/*   Updated: 2022/12/16 19:29:44 by kvisouth         ###   ########.fr       */
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
	static char *stash;	//Variable statique contenant le resultat de la concatenation de lui meme et du buffer.
	char		*buff;	//Variable contenant le buffer de lecture. (read)
	char		*line;	//Variable contenant la ligne a retourner.
	int			readed;	//Variable contenant le nombre de caracteres lus par read.

	if (fd < 0 || BUFFER_SIZE <= 0) //Gestion input invalides.
		return (NULL);

	//On lis une fois avant la boucle pour initialiser les variables 
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);

	readed = read(fd, buff, BUFFER_SIZE);
	
	//Tout lu et stash vide : retourne null.
	if (readed <= 0 && !stash)
		return (NULL);

	buff[readed] = '\0';
	stash = ft_strjoin(stash, buff);
	free(buff);

	//Va sortir de la boucle quand le stash sera vide
	while (stash)
	{
		//Sa lis
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		readed = read(fd, buff, BUFFER_SIZE);
		buff[readed] = '\0';
		stash = ft_strjoin(stash, buff);
		free(buff);

		//CAS 1 : Derniere ligne, pas de \n, read a lu moins que BUFFER_SIZE.
		if (readed < BUFFER_SIZE && check_line(stash) == -1)
		{
			line = ft_substr(stash, 0, ft_strlen(stash)); //Comme strdup mais on utilise ft_substr
			free(stash);
			stash = NULL;
			return (line);
		}
		//CAS 2 : Pas derniere ligne, il y a un \n dans stash. Read lit forcement BUFFER_SIZE.
		else if (check_line(stash) != -1)
		{
			line = ft_substr(stash, 0, ft_strchr(stash, '\n') - stash + 1);
			stash = ft_strcut(stash);
			return (line);
		}
	}
	//Retourne null si on sort de la boucle (donc qu'on a forcement readed <= 0)
	return (NULL);
}

int main(int argc, char **argv)
{
	char	*line;

	int i = 0;
	int fd = open("text.txt", O_RDONLY);
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
