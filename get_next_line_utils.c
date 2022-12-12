/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:11:17 by kvisouth          #+#    #+#             */
/*   Updated: 2022/12/12 20:28:47 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
    size_t	i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	size;
	int		i;
	int		j;

	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(size * sizeof(char) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char    *ft_strndup(const char *s1, size_t n)
{
    char    *str;
    size_t  i;

    i = 0;
    str = malloc(sizeof(char) * (n + 1));
    if (!str)
        return (NULL);
    while (i < n)
    {
        str[i] = s1[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

//delete n bytes from the start of the string
char    *ft_strndel(char *str, size_t n)
{
    char    *new;
    size_t  i;

    i = 0;
    new = malloc(sizeof(char) * (ft_strlen(str) - n + 1));
    if (!new)
        return (NULL);
    while (str[n])
        new[i++] = str[n++];
    new[i] = '\0';
    free(str);
    return (new);
}