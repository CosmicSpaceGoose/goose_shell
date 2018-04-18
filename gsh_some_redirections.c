/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_some_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:43:35 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/22 16:43:36 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

/*
**		**red - redirections	*fds - piped descriptors
*/

static int	gsh_detect_input(char *red)
{
	char	*ptr;
	int		fd;

	if ((ptr = ft_strchr(red, '<')))
	{
		fd = open(ptr + 1, O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);
		return (fd);
	}
	return (-2);
}

// void	gsh_make_input_redirections(char **red, int *fds)
// {
// 	int		fd;
// 	int		i;
// 	char	buf[1025];

// 	ft_dprintf(2, "fds[%d %d %d %d]\n", fds[-2], fds[-1], fds[0], fds[1]);	//<<-----☢️
// 	while (*red)
// 	{
// 		if ((fd = gsh_detect_input(*red)) > -1)
// 		{
// 			while ((i = read(fd, buf, 1024)))
// 				write(fds[-1], buf, i);
// 			close(fd);
// 		}
// 		else if (fd == -1)
// 		{
// 			;// 		read heredoc	
// 		}
// 		red++;
// 	}
// 	// close(fds[-1]);
// }

// void	gsh_make_output_redirections(char **red, int *fds)
// {
// 	int file;
// 	int i;
// 	int fd[2];
// 	char buf[1025];

// 	pipe(fd);
// 	file = open("some_file", O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR |
		 // S_IWGRP | S_IWOTH);
// 	close(fds[1]);
// 	while ((i = read(fds[0], buf, 1024)))
// 	{
// 		write(file, buf, i);
// 		write(fd[1], buf, i);
// 	}
// 	close(fd[1]);
// 	close(file);

// 	close(fds[0]);
// 	close(fds[1]);
// 	fds[0] = dup(fd[0]);
// 	fds[1] = dup(fd[1]);
// }

void gsh_make_input_redirections(char **red, int *fds)
{
	int fd[2];
	char buf[1025];
	int i;
	int file;

	ft_dprintf(2, "fds[%d %d]\t", fds[-2], fds[-1]);	//<<-----☢
	pipe(fd);
	close(fds[-1]);
	ft_putstr_fd("+", 2);								//<<-----☢
	while ((i = read(fds[-2], buf, 1024)))
		write(fd[1], buf, i);
	close(fds[-2]);
	ft_putstr_fd("-", 2);							//<<-----☢
	while (*red)
	{
		if ((file = gsh_detect_input(*red)) > -1)
		{
			while((i = read(file, buf, 1024)))
				write(fd[1], buf, i);
			close(file);
		}
		red++;
	}
	ft_dprintf(2, "fd[%d %d]\t", fd[0], fd[1]);	//<<-----☢️
	fds[-2] = dup(fd[0]);
	fds[-1] = dup(fd[1]);
	close(fds[-1]);
	close(fd[0]);
	close(fd[1]);
	ft_dprintf(2, "new_fds[%d %d]\n", fds[-2], fds[-1], fds[0], fds[1]);	//<<-----☢️
}