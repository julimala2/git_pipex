/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/20 18:39:00 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	ft_pipex(t_pipex_b *pipex, char **av, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	status = 0;
	pid1 = fork();
	if (pid1 < 0)
		exit_with_message_and_free("pid1", pipex, 1);
	if (pid1 == 0)
	{
		if (pipex->first_cmd == 1)
			cmd1_process(pipex, env);
		else
			inbetween_cmd(pipex, env);
	}
	pid2 = fork();
	if (pid2 < 0)
		exit_with_message_and_free("pid2", pipex, 1);
	if (pid2 == 0)
	{
		if (pipex->last_cmd == 1)
		{
			init_outfile(pipex, av); 	       // enlever le av 
			cmd2_process(pipex, env);
		}
		else
			inbetween_cmd(pipex, env);
	}
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (pipex->outfile_error == 1)
		return (1);
	return ((status >> 8) & 0xFF);
}

void	cmd1_process(t_pipex_b *pipex, char **env)
{
	if (pipex->infile)
		dup2(pipex->infile, 0);
	dup2(pipex->pipefd[1], 1);
	close(pipex->pipefd[0]);
	if (pipex->pathname_cmd1)
		execve(pipex->pathname_cmd1, pipex->cmd1, env);
}

void	inbetween_cmd(t_pipex_b *pipex, char **env)
{
	dup2(pipex->pipefd[0], 0);
	dup2(pipex->outfile, 1);
	close(pipex->pipefd[1]);
	if (pipex->pathname_cmd2)
		execve(pipex->pathname_cmd2, pipex->cmd2, env);
	else
		exit_with_message_and_free("cmd2 fail", pipex, 127);
}

void	cmd2_process(t_pipex_b *pipex, char **env)
{
	dup2(pipex->pipefd[0], 0);
	dup2(pipex->outfile, 1);
	close(pipex->pipefd[1]);
	if (pipex->pathname_cmd2)
		execve(pipex->pathname_cmd2, pipex->cmd2, env);
	else
		exit_with_message_and_free("cmd2 fail", pipex, 127);
}
