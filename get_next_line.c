/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:53:44 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/05/03 14:11:15 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*s_buffer;
	int				found;
	int				nread;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX || fd > MAX_NUM_FD)
		return (NULL);
	nread = read(fd, "", 0);
	if (nread == -1)
		return (NULL);
	found = ft_read_from_file(fd, &s_buffer);
	if (found == -1)
		return (NULL);
	if (s_buffer)
		return (ft_catch_line(found, &s_buffer));
	else
		return (s_buffer);
}

int	ft_read_from_file(int fd, char **s_buffer)
{
	char	*buffer;
	int		nread;
	int		found;

	nread = 1;
	found = 0;
	while (nread && !found)
	{
		buffer = (char *) malloc (BUFFER_SIZE * sizeof (char) + 1);
		if (!buffer)
			return (-1);
		nread = read(fd, buffer, BUFFER_SIZE);
		if (nread == -1)
			return (free(buffer), -1);
		buffer[nread] = '\0';
		ft_write_to_buffer(s_buffer, buffer);
		(free (buffer), buffer = NULL);
		if (ft_streolpos(*s_buffer) >= 0)
			found = 1;
	}
	return (found);
}

void	ft_write_to_buffer(char **s_buffer, char *buffer)
{
	char	*tmp;

	if (!*s_buffer)
		*s_buffer = ft_strjoin_i(NULL, buffer);
	else
	{
		tmp = ft_strjoin_i(*s_buffer, buffer);
		(free(*s_buffer), *s_buffer = NULL);
		*s_buffer = ft_strjoin_i(NULL, tmp);
		(free(tmp), tmp = NULL);
	}
	if (*s_buffer && !ft_strlen(*s_buffer))
		(free(*s_buffer), *s_buffer = NULL);
}

char	*ft_catch_line(int found, char **s_buffer)
{
	char	*tmp[2];

	if (!ft_strlen(*s_buffer))
		return (free(*s_buffer), NULL);
	if (found)
	{
		tmp[0] = ft_substr_i(*s_buffer, 0, ft_streolpos(*s_buffer) + 1);
		tmp[1] = ft_substr_i(*s_buffer, ft_streolpos(*s_buffer) + 1, \
				ft_strlen(*s_buffer) + 1);
		(free(*s_buffer), *s_buffer = NULL);
		*s_buffer = ft_strjoin_i(NULL, tmp[1]);
		(free(tmp[1]), tmp[1] = NULL);
	}
	else
	{
		tmp[0] = ft_strjoin_i(NULL, *s_buffer);
		if (*s_buffer)
			(free(*s_buffer), *s_buffer = NULL);
	}
	if (*s_buffer && !ft_strlen(*s_buffer))
		(free (*s_buffer), *s_buffer = NULL);
	return (tmp[0]);
}
