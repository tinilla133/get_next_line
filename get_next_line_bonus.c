/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:53:44 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/05/03 14:11:32 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char		*s_buffer[MAX_NUM_FD];
	char			**ptr_s_buffer;
	int				found;
	int				nread;

	ptr_s_buffer = s_buffer;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX || fd > 1024)
		return (NULL);
	nread = read(fd, "", 0);
	if (nread == -1)
		return (NULL);
	found = ft_read_from_file(fd, &ptr_s_buffer);
	if (found == -1)
		return (NULL);
	if (ptr_s_buffer[fd])
		return (ft_catch_line(fd, found, &ptr_s_buffer));
	else
		return (ptr_s_buffer[fd]);
}

int	ft_read_from_file(int fd, char ***s_buffer)
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
		ft_write_to_buffer(fd, s_buffer, buffer);
		free (buffer);
		if (ft_streolpos((*s_buffer)[fd]) >= 0)
			found = 1;
	}
	return (found);
}

void	ft_write_to_buffer(int fd, char ***s_buffer, char *buffer)
{
	char	*tmp;

	if (!(*s_buffer)[fd])
		(*s_buffer)[fd] = ft_strjoin_i(NULL, buffer);
	else
	{
		tmp = ft_strjoin_i((*s_buffer)[fd], buffer);
		(free((*s_buffer)[fd]), (*s_buffer)[fd] = NULL);
		(*s_buffer)[fd] = ft_strjoin_i(NULL, tmp);
		(free(tmp), tmp = NULL);
	}
	if ((*s_buffer)[fd] && !ft_strlen((*s_buffer)[fd]))
		(free((*s_buffer)[fd]), (*s_buffer)[fd] = NULL);
}

char	*ft_catch_line(int fd, int found, char ***s_buffer)
{
	char	*tmp[2];

	if (!ft_strlen((*s_buffer)[fd]))
		return (free((*s_buffer)[fd]), NULL);
	if (found)
	{
		tmp[0] = ft_substr_i((*s_buffer)[fd], 0, \
				ft_streolpos((*s_buffer)[fd]) + 1);
		tmp[1] = ft_substr_i((*s_buffer)[fd], \
				ft_streolpos((*s_buffer)[fd]) + 1, \
				ft_strlen((*s_buffer)[fd]) + 1);
		(free((*s_buffer)[fd]), (*s_buffer)[fd] = NULL);
		(*s_buffer)[fd] = ft_strjoin_i(NULL, tmp[1]);
		(free(tmp[1]), tmp[1] = NULL);
	}
	else
	{
		tmp[0] = ft_strjoin_i(NULL, (*s_buffer)[fd]);
		if ((*s_buffer)[fd])
			(free((*s_buffer)[fd]), (*s_buffer)[fd] = NULL);
	}
	if ((*s_buffer)[fd] && !ft_strlen((*s_buffer)[fd]))
		(free((*s_buffer)[fd]), (*s_buffer)[fd] = NULL);
	return (tmp[0]);
}
