/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:53:51 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/05/02 18:39:19 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_i(char const *s1, char const *s2)
{
	size_t	bufflen;
	char	*buff;

	if (!s2)
		return (NULL);
	if (!s1)
		bufflen = ft_strlen((s2));
	else
		bufflen = ft_strlen((char *) s1) + ft_strlen((char *) s2);
	buff = (char *) malloc(bufflen * sizeof (char) + 1);
	if (!buff)
		return (NULL);
	if (s1)
		while (*s1)
			*(buff++) = *(s1++);
	while (*s2)
		*(buff++) = *(s2++);
	*buff = '\0';
	return (buff - bufflen);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_streolpos(const char *str)
{
	int	pos;

	if (!str)
		return (-1);
	pos = 0;
	while (str[pos])
	{
		if (str[pos] == '\n')
			return (pos);
		pos++;
	}
	return (-1);
}

char	*ft_substr_i(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*buff;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
		return (NULL);
	if (!len && slen)
		len = 1;
	buff = (char *) malloc ((len + 1) * sizeof (char));
	if (!buff)
		return (NULL);
	i = 0;
	while (s[i + start] && i < (len - start))
	{
		buff[i] = s[i + start];
		i++;
	}
	buff[i] = '\0';
	return (buff);
}
