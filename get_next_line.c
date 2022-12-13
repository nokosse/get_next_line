/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:26:38 by kvisouth          #+#    #+#             */
/*   Updated: 2022/12/13 13:02:38 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//Prototype de read : ssize_t read(int fd, void *buf, size_t count);

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

//Fonction qui verifie si la string en parametre contient un \n.
int	check_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (-1);
}

//Fonction qui supprime tout ce qui est avant le \n dans la string en parametre.
static char	*ft_strdel(char *str)
{
	char	*new;
	int		i;
	int		j;
	
	i = 0;
	while (str[i] != '\n')
		i++;
	new = malloc (sizeof(char) * (ft_strlen(str) - i) + 1);
	if (!new)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		new[j++] = str[i++];
	new[j] = '\0';
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*stash;	// Variable resultant de la concatenation de buffer et lui meme.
	char		*buf;	// Variable qui contient ce que read a lu dans son buffer.
	char		*line;	// Variable qui contient la ligne a retourner.
	ssize_t		bytes;	// Variable qui contient le nombre de bytes lus par read.
	size_t		readed;	// Variable qui contient le nombre de bytes lus par read au total.

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// Tant qu'on a pas trouver de \n dans stash et qu'on a pas atteint la fin du fichier.
	// Au cas ou on a qu'une ligne dans le fichier.
	while((check_line(stash) != 1) && (read(fd, buf, bytes) != 0))
	{
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1);	////
		if (!buf)										  //
			return (NULL);								  //
		bytes = read(fd, buf, BUFFER_SIZE);				  //
		readed += bytes;								  //
		if (bytes == -1)								  //
			return (NULL);								  // On a fait en sorte que buf contienne ce que read a lu dans son buffer.
		buf[bytes] = '\0';								  // On met un \0 a la fin de buf.
		stash = ft_strjoin(stash, buf);					  // On concatene buf et stash.
		free(buf);										////
	}
	// CAS 1 : Il y a un \n dans stash. Mais peut etre des trucs apres le \n.
	// CAS 2 : On a atteint la fin du fichier. Sans forcement avoir de \n dans stash. (On a qu'une ligne dans le fichier.)

	//On gere le 2eme cas.
	if (check_line(stash) == 0)
	{								// Si on a qu'une ligne dans le fichier, ou rien du tout.
		line = ft_strdup(stash);	// On copie stash dans line.
		return (line);				// On retourne line.
	}
	
	//On gere le 1er cas.
	line = ft_substr(stash, 0, ft_strchr(stash, '\n') - stash);	// On copie stash dans line jusqu'au \n.
	stash = ft_strdel(stash);									// On supprime tout ce qui est avant le \n dans stash.
	return (line);												// On retourne line.

	if (readed == 0)	// Si on a rien lu dans le fichier.
		return (NULL);	// On retourne NULL.
}

int main (void)
{
	int		fd;
	char	*line;
	char	*line2;

	fd = open("text.txt", O_RDONLY);
	printf("fd de text.txt = %d\n", fd);
	line = get_next_line(fd);
	printf("Premiere ligne : %s", line);
	line2 = get_next_line(fd);
	printf("Deuxieme ligne : %s", line2);
	close(fd);
	return (0);
}
//Compiler comme sa : gwww -D BUFFER_SIZE=42 *.c