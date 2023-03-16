/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleggeri <nleggeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:08:02 by nleggeri          #+#    #+#             */
/*   Updated: 2023/03/16 10:59:42 by nleggeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	search_path_in_env(char **envp)
{
	int	j;

	j = 0;
	while (envp[j])
	{
		if (envp[j][0] == 'P' && envp[j][1] == 'A' \
			&& envp[j][2] == 'T' && envp[j][3] == 'H')
			break ;
		j++;
	}
	return (j);
}

char	*join_all_path(char *env, char *cmd, char slash)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!env || !cmd)
		return (NULL);
	join = malloc(sizeof(char) * (ft_strlen(env) + ft_strlen(cmd) + slash + 1));
	if (!join)
		return (NULL);
	while (env[i])
		join[j++] = env[i++];
	join[j] = slash;
	j++;
	i = 0;
	while (cmd[i])
		join[j++] = cmd[i++];
	join[j] = '\0';
	return (join);
}

char	*existence_of_cmd(char **env, char *cmd)
{
	int		j;
	char	*tmp;

	j = -1;
	while (env[++j])
	{
		tmp = join_all_path(env[j], cmd, '/');
		if (access(tmp, F_OK) == 0)
			return (tmp);
		free(tmp);
	}
	return (NULL);
}

void	first_child_process(t_vars pi, char *argv)
{
	char	*tmp;

	if (dup2(pi.infile, STDIN_FILENO) == -1 || \
			dup2(pi.end[1], STDOUT_FILENO) == -1)
		return (mes_error("ERR_DUP"));
	if (close(pi.end[0]) == -1)
		return (mes_error("BAD_CLOSE"));
	pi.cmd1 = ft_split(argv, ' ');
	tmp = existence_of_cmd(pi.env, pi.cmd1[0]);
	if (!tmp)
		mes_error("ERR_CMD");
	execve(tmp, pi.cmd1, NULL);
}

void	second_child_process(t_vars pi, char *argv)
{
	char	*tmp;

	if (dup2(pi.outfile, STDOUT_FILENO) == -1 || \
			dup2(pi.end[0], STDIN_FILENO) == -1)
		return (mes_error("ERR_DUP"));
	if (close(pi.end[1]) == -1)
		return (mes_error("BAD_CLOSE"));
	pi.cmd2 = ft_split(argv, ' ');
	tmp = existence_of_cmd(pi.env, pi.cmd2[0]);
	if (!tmp)
		mes_error("ERR_CMD");
	execve(tmp, pi.cmd2, NULL);
}
