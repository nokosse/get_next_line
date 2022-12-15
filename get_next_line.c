/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:26:38 by kvisouth          #+#    #+#             */
/*   Updated: 2022/12/15 16:32:59 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//Prototype de read : ssize_t read(int fd, void *buf, size_t count);

//Fonction qui verifie si la string en parametre contient un \n.
static int	check_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

//Fonction qui supprime tout ce qui est avant le \n dans la string en parametre.
static char	*ft_strdel(char *str)
{
	char	*new;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	i++;
	new = ft_strdup(str + i);
	free(str);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*stash;	// Variable resultant de la concatenation de buffer et lui meme.
	char		*buf;	// Variable qui contient ce que read a lu dans son buffer.
	char		*line;	// Variable qui contient la ligne a retourner.
	ssize_t		bytes;	// Variable qui contient le nombre de bytes lus par read.

	if (fd < 0 || BUFFER_SIZE <= 0)	//Retourne NULL si fd OU BUFFER_SIZE est invalide.
		return (NULL);
		
	// Tant qu'on a pas trouver de \n dans stash et qu'on a pas atteint la fin du fichier.
	// Au cas ou on a qu'une ligne dans le fichier.
	bytes = 1;
	while (check_line(stash) == -1)
	{
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1);	//// On alloue de la memoire pour buf.
		if (!buf)										  // 
			return (NULL);								  // On retourne NULL si malloc a echoue.
		bytes = read(fd, buf, BUFFER_SIZE);				  // On lit BUFFER_SIZE bytes dans le fichier.
		if (bytes == 0)
		{
			if (stash && ft_strlen(stash) == 1)	 		  // Si on a atteint la fin du fichier et qu'il n'y a pas de \n dans stash.
			{
    			line = ft_strdup(stash);				  // On copie stash dans line.
				free(stash);
				free(buf);								  // On libere la memoire allouee a buf.
				return (line);							  // On retourne line.
			}
			free(buf);									  // On libere la memoire allouee a buf.
			break;
		}
		if (bytes == 0)									  //
		{
			free(buf);									  // On libere la memoire allouee a buf.
			break;										  // On sort de la boucle si on a atteint la fin du fichier.
		}
		if (bytes == -1)								  // 
		{
			free(buf);									  // On libere la memoire allouee a buf.
			return (NULL);								  // On retourne NULL si read a echoue.
		}
		buf[bytes] = '\0';								  // On met un \0 a la fin de buf.
		stash = ft_strjoin(stash, buf);					  // On concatene buf et stash.
		free(buf);										////
	}

	if(!stash || stash[1] == '\0')	// Si on a atteint la fin du fichier et qu'il n'y a pas de \n dans stash.
		return (NULL);

	// CAS 1 : On a atteint la fin du fichier. Sans aucun \n dans stash. (On a qu'une ligne dans le fichier.)
	if (bytes == 0 && check_line(stash) == -1)	// Si on a atteint la fin du fichier et qu'il n'y a pas de \n dans stash.
	{
		line = ft_strdup(stash);	// On copie stash dans line.
		stash = ft_strdel(stash);	// On supprime tout ce qui est avant le \n dans stash.
		free(stash);				// On libere la memoire de stash.
		return (line);				// On retourne line.
	}
	
	// CAS 2 : Il y a un \n dans stash. Mais peut etre des trucs apres le \n.
	line = ft_substr(stash, 0, ft_strchr(stash, '\n') - stash + 1);	// On copie stash dans line jusqu'au \n.
	stash = ft_strdel(stash);									// On supprime tout ce qui est avant le \n dans stash.
	return (line);												// On retourne line.
}

int main(int argc, char **argv)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open("text.txt", O_RDONLY);
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

//Compiler comme sa : gwww -D BUFFER_SIZE=2 *.c