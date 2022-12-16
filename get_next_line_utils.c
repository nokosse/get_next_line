/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:11:17 by kvisouth          #+#    #+#             */
/*   Updated: 2022/12/16 19:01:47 by kvisouth         ###   ########.fr       */
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
	But it uses pointers instead of indexes.
	Speciality of this one : if s1 is NULL, it will return str
	which is a malloc of s2. (Which is the buffer of GNL)
*/

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	char	*str_ptr;

	if (!s1)
	{
		str = malloc(ft_strlen(s2) + 1);
		str_ptr = str;
		if (!str)
			return (NULL);
		while (*s2)
			*str_ptr++ = *s2++;
		*str_ptr = '\0';
		return (str);
	}
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	str_ptr = str;
	if (!str)
		return (NULL);
	while (*s1)
		*str_ptr++ = *s1++;
	while (*s2)
		*str_ptr++ = *s2++;
	*str_ptr = '\0';
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

// char	*ft_strdup(const char *s)
// {
// 	char	*dup;
// 	int		i;

// 	i = 0;
// 	dup = malloc(ft_strlen(s) + 1);
// 	if (!dup)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		dup[i] = s[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }
