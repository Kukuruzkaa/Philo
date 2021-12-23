/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 09:06:59 by ddiakova          #+#    #+#             */
/*   Updated: 2021/10/24 17:01:47 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int	ft_strchr_g(char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	*ft_joinstr(char *s1, char *s2, size_t size)
{
	size_t	str1len;
	size_t	i;
	size_t	j;
	char	*s3;

	str1len = ft_strlen(s1);
	s3 = (char *)malloc(sizeof(char) * (str1len + size + 1));
	if (!s3)
		return (NULL);
	i = 0;
	while (i < str1len)
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < size)
	{
		s3[str1len + j] = s2[j];
		j++;
	}
	s3[str1len + size] = '\0';
	free(s1);
	s1 = NULL;
	return (s3);
}

void	*ft_getmemset(void *b, int c, size_t len)
{
	size_t	index;
	char	*str;

	str = (char *)b;
	index = 0;
	while (index < len)
	{
		str[index] = (unsigned char)c;
		index++;
	}
	return (b);
}

void	ft_getsubstr(char *s, unsigned int start, size_t len)
{
	size_t		j;
	size_t		length;

	if (!s)
		return ;
	j = 0;
	length = ft_strlen(s);
	if (start >= length)
	{
		ft_getmemset(s, '\0', length);
		return ;
	}
	while (j < len)
	{
		s[j] = s[j + start];
		j++;
	}
	s[j] = '\0';
}
