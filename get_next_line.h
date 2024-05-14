/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:53:55 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/04/26 18:59:11 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <errno.h> 
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif 

# ifndef MAX_NUM_FD
#  define MAX_NUM_FD 4096
# endif

char	*get_next_line(int fd);
int		ft_read_from_file(int fd, char **s_buffer);
void	ft_write_to_buffer(char **s_buffer, char *buffer);
char	*ft_catch_line(int found, char **s_buffer);
char	*ft_strjoin_i(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_streolpos(const char *str);
char	*ft_substr_i(char const *s, unsigned int start, size_t len);

#endif
