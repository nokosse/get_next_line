/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:26:38 by kvisouth          #+#    #+#             */
/*   Updated: 2022/12/16 13:16:16 by kvisouth         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	static char *stash;	//Variable statique contenant le resultat de la concatenation de lui meme et du buffer.
	char		*buff;	//Variable contenant le buffer de lecture. (read)
	char		*line;	//Variable contenant la ligne a retourner.
	int			readed;	//Variable contenant le nombre de caracteres lus par read.

	//On lis une fois avant la boucle pour initialiser les variables.
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
		
	readed = read(fd, buff, BUFFER_SIZE); //Juste pour initialiser readed.
	
	//On check si read a lu quelque chose, retourne null si il n'y a rien a lire.
	if (readed <= 0 && !stash)
		return (NULL);

	buff[readed] = '\0'; //On ajoute le \0 a la fin du buffer.
	stash = ft_strjoin(stash, buff); //On concatene le buffer a la variable statique.
	free(buff); //Plus besoin de buff pour le reste de la boucle.

	//On rentre dans le cas ou on a forcement lu quelque chose lors de l'appel a get_next_line.
	while (readed > 0 || stash) 	//Tant qu'on a pas atteint la fin du fichier.
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		readed = read(fd, buff, BUFFER_SIZE); //On lit le fichier.
		buff[readed] = '\0'; //On ajoute le \0 a la fin du buffer.
		stash = ft_strjoin(stash, buff); //On concatene le buffer a la variable statique.
		free(buff); //Plus besoin de buff pour le reste de la boucle.
		
		//CAS 1 : Derniere ligne, pas de \n, read a lu moins que BUFFER_SIZE.
		if (readed < BUFFER_SIZE && check_line(stash) == -1)
		{
			line = stash;
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

//Compiler comme sa : gwww -D BUFFER_SIZE=2 *.c