/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleggeri <nleggeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:43:20 by nleggeri          #+#    #+#             */
/*   Updated: 2023/03/16 11:16:35 by nleggeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef HEADER_H
# define HEADER_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "./libft/libft.h"

typedef struct s_vars
{
	char	*envpi;
	char	**env;
	char	**cmd1;
	char	**cmd2;
	int		infile;
	int		outfile;
	int		end[2];
	int		pid1;
	int		pid2;
}		t_vars;

/***************main.c********************/
void	mes_error(char *mess);
void	close_pipes(t_vars *pi);
void	init_var(t_vars *pi, char **argv, char **envp);
int		main(int argc, char **argv, char **envp);

/***************pipex.c*******************/
int		search_path_in_env(char **envp);
char	*join_all_path(char *env, char *cmd, char slash);
char	*existence_of_cmd(char **env, char *cmd);
void	first_child_process(t_vars pi, char *argv);
void	second_child_process(t_vars pi, char *argv);

#endif
