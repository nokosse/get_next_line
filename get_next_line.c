/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:26:38 by kvisouth          #+#    #+#             */
/*   Updated: 2022/12/12 20:29:59 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//prototype de read : ssize_t read(int fd, void *buf, size_t count);
//Read reste a l'endroit ou il s'est arrete la derniere fois. Il faut donc un buffer pour stocker ce qu'il lit.

	//notre char *buffer sera malloc de BUFFER_SIZE +1 pour le \0
	//on utilise read pour lire le fichier en boucle. jusqu'a ce qu'il nous retourne 0. (plus rien a lire)
	//dans la boucle :
		//on met dans un char *buffer ce quon a lu avec read
		//on concatene dans *stash ce qu'il y a dans buffer.
		//dans *stash, on verifie lettre par lettre si il y a un \n grace a la fonction check_newline
		//si il y a un \n on sort de la boucle
	//on efface ce quil y a apres le \n dans *stash.
	//on copie ce qu'il y a avant le \n (\n compris) dans *stash vers *line
	//on supprime dans *stash ce qu'il y a avant le \n (\n compris), pourquoi pas faire les 2 en meme temps ?
	  //peut etre faire toutes ces instructions avant la boucle au cas ou on a un enorme buffer qui a lu tout le fichier en une fois.
	  //et donc gerer un cas ou il y a plusieurs \n dans le buffer.
	//on retourne *line

int	check_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stash;		//variable temporaire pour stocker ce qu'on lit
	char		*buffer;	//ce qu'on va lire avec read
	char		*line;		//ce qu'on va retourner
	size_t		readed;		//nb de caracteres lus
	size_t		i;			//nb de caracteres a supprimer dans stash

	readed = BUFFER_SIZE;
	while (read(fd, buffer, BUFFER_SIZE) != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (NULL);
		readed += read(fd, buffer, BUFFER_SIZE);
		stash = ft_strjoin(stash, buffer);
		free (buffer);
		if (check_newline(stash) == 1)
			break ;
	}
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	line = strndup(stash, i);
	stash = ft_strndel(stash, i);
}
	