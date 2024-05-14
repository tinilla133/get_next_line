/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:07:51 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/05/03 14:34:49 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"
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

int	main(void)
{
	int				fd;
	unsigned int	i;
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
	while (i < 10)
	{
		buffer = get_next_line(fd);
		printf("Line %d:%s", 1 + i++, buffer);
		printf("~~\n~~");
		free(buffer);
	}
	close(fd);
	fd = open(full_file_name, O_RDONLY);
	i = 0;
	while (i < 10)
	{
		buffer = get_next_line(fd);
		printf("Line %d:%s", 1 + i++, buffer);
		printf("~~\n~~");
		free(buffer);
	}
	close(fd);
}