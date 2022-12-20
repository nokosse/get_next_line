/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:11:17 by kvisouth          #+#    #+#             */
/*   Updated: 2022/12/20 12:07:28 by kvisouth         ###   ########.fr       */
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

/*
	ft_strjoin that works exactly like libft's ft_strjoin.
	It is used in GNL to concatenate the stash and the buffer.
*/

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

/*
	ft_strchr is used to find the \n and is used only
	as a parameter for ft_substr. (it's size_t len)
*/

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (0);
}

/*
	ft_substr is used to get the line from the stash in GNL.
	In case 1 : Last line, it is doing a strdup of the stash.
	In case 2 : Not last line, it is strduping from start to \n.
*/

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;
	int		y;

	if (start >= ft_strlen(s))
		start = ft_strlen(s);
	y = 0;
	while (start + y < start + len && s[start + y] != '\0')
		y++;
	i = 0;
	str = malloc((y) + 1);
	if (!str || start > ft_strlen(s))
		return (NULL);
	while (i < y)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

/*
	ft_strdup is used to duplicate the buffer of read in stash
	in case of stash is NULL.
	stash become the content of the buffer and is \0 terminated.
*/

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
