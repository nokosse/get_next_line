/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:11:17 by kvisouth          #+#    #+#             */
/*   Updated: 2022/12/16 13:56:21 by kvisouth         ###   ########.fr       */
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

char	*ft_strjoin(char *s1, char *s2)
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
