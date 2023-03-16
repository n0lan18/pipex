/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleggeri <nleggeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:15:42 by nleggeri          #+#    #+#             */
/*   Updated: 2023/03/16 10:57:50 by nleggeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	mes_error(char *mess)
{
	perror(mess);
	exit(1);
}

void	close_pipes(t_vars *pi)
{
	if (close(pi->infile) == -1)
		mes_error("ERR_CLOSE_INFILE");
	if (close(pi->outfile) == -1)
		mes_error("ERR_CLOSE_INFILE");
	if (close(pi->end[0]) == -1)
		mes_error("ERR_CLOSE_WRITE");
	if (close(pi->end[1]) == -1)
		mes_error("ERR_CLOSE_READ");
}

void	init_var(t_vars *pi, char **argv, char **envp)
{
	pi->infile = open(argv[1], O_RDONLY);
	pi->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pi->outfile < 0 || pi->infile < 0)
		mes_error("ERR_OPEN_FILE");
	if (pipe(pi->end) < 0)
		mes_error("ERR_PIPE");
	pi->envpi = &envp[search_path_in_env(envp)][5];
	pi->env = ft_split(pi->envpi, ':');
	if (pi->env == NULL)
		exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	pi;

	if (argc != 5)
		mes_error("ERR_ARG");
	init_var(&pi, argv, envp);
	pi.pid1 = fork();
	if (pi.pid1 < 0)
		mes_error("ERR_FORK");
	if (pi.pid1 == 0)
		first_child_process(pi, argv[2]);
	pi.pid2 = fork();
	if (pi.pid2 < 0)
		mes_error("ERR_FORK");
	if (pi.pid2 == 0)
		second_child_process(pi, argv[3]);
	close_pipes(&pi);
	waitpid(pi.pid1, NULL, 0);
	waitpid(pi.pid2, NULL, 0);
	exit(0);
}
