/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:45:24 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/05/03 14:18:21 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include "get_next_line_bonus.h"

//#define SINGLE_FILE_TEST
#define NLINES 30
#define DIR_PATH "text_files"
//#define FILE_NAME "1char.txt"
//#define FILE_NAME "41_no_nl"
//#define FILE_NAME "41_with_nl"
//#define FILE_NAME "3_with_nl"
//#define FILE_NAME "42_no_nl"
//#define FILE_NAME "42_with_nl"
//#define FILE_NAME "43_no_nl"
//#define FILE_NAME "43_with_nl"
//#define FILE_NAME "alternate_line_nl_no_nl"
//#define FILE_NAME "alternate_line_nl_with_nl"
//#define FILE_NAME "big_line_no_nl"
//#define FILE_NAME "big_line_with_nl"
//#define FILE_NAME "empty"

//#define FILE_NAME "1char.txt"
//#define FILE_NAME "empty.txt"
//#define FILE_NAME "giant_line.txt"
//#define FILE_NAME "giant_line_nl.txt"
//#define FILE_NAME "lines_around_10.txt"
//#define FILE_NAME "multiple_line_no_nl"
//#define FILE_NAME "multiple_line_with_nl"
//#define FILE_NAME "multiple_nl.txt"
//#define FILE_NAME "multiple_nlx5"
//#define FILE_NAME "nl"
//#define FILE_NAME "one_line_no_nl.txt"
//#define FILE_NAME "only_nl.txt"
#define FILE_NAME "read_error.txt"
//#define FILE_NAME "text_file1.txt"
//#define FILE_NAME "text_file2.txt"
//#define FILE_NAME "text_file3.txt"
//#define FILE_NAME "text_file4.txt"
//#define FILE_NAME "text_file5.txt"
//#define FILE_NAME "text_file6.txt"
//#define FILE_NAME "text_file7.txt"
//#define FILE_NAME "variable_nls.txt"
// ls -l text_files | sed -n '1!p' | awk '{print $NF}'

static int	s_fd[MAX_NUM_FD];
static int	s_nfiles;

void	ft_close_files(void);
int		ft_open_files(DIR **dir);

#ifdef SINGLE_FILE_TEST

int     main(void)
{
    int             fd;
    unsigned int    i;
	char			*buffer;
	char			full_file_name[256];

    i = 0;
	snprintf(full_file_name, 256, "%s/%s", DIR_PATH, FILE_NAME);
    fd = open(full_file_name, O_RDONLY);
    if (fd < 0)
	{
		perror("Could not open file");
    	return (-1);
	}
    while ((buffer = get_next_line(fd)))
	{
		printf("Line %d:%s:", 1 + i++, buffer);
		printf("~~\n~~");
		free(buffer);
    }
    close(fd);
}

#else

int	main(void)
{
	int				fd;
	unsigned int	i;
	char			*buffer;
	DIR				*dir;

	srand(time(NULL));
	ft_open_files(&dir);
	i = 0;
	if (s_nfiles)
	{
		while (i++ <= NLINES)
		{
			fd = rand() % s_nfiles;
			printf("Line: %d fd: %d", i, fd);
			buffer = get_next_line(fd);
			printf(":%s:~~\n~~", buffer);
			free(buffer);
			buffer = NULL;
		}
		if (buffer)
			free(buffer);
	}
	ft_close_files();
	closedir(dir);
}

#endif

int	ft_open_files(DIR **dir)
{
	char			path[512];
	struct dirent	*entry;

	s_nfiles = 0;
	*dir = opendir(DIR_PATH);
	if (*dir == NULL)
	{
		return (-1);
		perror("ERROR opening directory.");
	}
	while ((entry = readdir(*dir)))
	{
		if (strcmp(entry->d_name, ".") || strcmp(entry->d_name, ".."))
			snprintf(path, 512, "%s/%s", DIR_PATH, entry->d_name);
		s_fd[s_nfiles] = open(path, O_RDONLY);
		if (s_fd[s_nfiles] == -1)
			return (-1);
		printf("fd:%d path:%s\n", s_fd[s_nfiles], path);
		s_nfiles++;
	}
	return (0);
}

void	ft_close_files(void)
{
	int	i;

	i = 0;
	while (i < s_nfiles)
		close(s_fd[i++]);
}
