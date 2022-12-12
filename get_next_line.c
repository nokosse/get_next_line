/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:26:38 by kvisouth          #+#    #+#             */
/*   Updated: 2022/12/12 19:14:22 by kvisouth         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	static char	*stash;		//variable temporaire pour stocker ce qu'on lit
	char		*buffer;	//ce qu'on va lire avec read
	char		*line;		//ce qu'on va retourner
	int			i;			//nb de caracteres lus

	while (read(fd, buffer, BUFFER_SIZE) != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (NULL);
		i = read(fd, buffer, BUFFER_SIZE);
		stash = ft_strjoin(stash, buffer);
	}
}
	