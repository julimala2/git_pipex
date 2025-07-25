/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/24 17:43:34 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	ft_pipex(t_pipex_b *pipex, char **env)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	pipex->pids[i] = fork();
	if (pipex->pids[i] < 0)
		exit_with_message_and_free("pid1", pipex, 1);
	if (pipex->pids[i] == 0)
		cmd_process(pipex, env);
	// close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	// waitpid(pid2, &status, 0);
	if (pipex->outfile_error == 1)
		return (1);
	return ((status >> 8) & 0xFF);
}

void	cmd_process(t_pipex_b *pipex, char **env)
{
	if (pipex->first_cmd == 1)
	{
		if (pipex->infile)
		{
			dup2(pipex->infile, 0);
			close(pipex->infile);
		}
	}
	else
	{
		dup2(pipex->prev_fd, 0);
		close(pipex->prev_fd);
	}
	if (pipex->last_cmd == 1)
	{
		init_outfile(pipex);
		dup2(pipex->outfile, 1);
		close(pipex->outfile);
	}
	else
	{
		dup2(pipex->pipefd[1], 1);
		close(pipex->pipefd[1]);
	}
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]); // a fermer
	pipex->first_cmd = 0;
	pipex->last_cmd = 0;
	if (pipex->pathname_cmd)
		execve(pipex->pathname_cmd, pipex->cmd, env);
}
