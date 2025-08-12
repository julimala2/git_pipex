/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/08/12 16:15:34 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_pipex(t_pipex *pipex, char **av, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	status = 0;
	init_outfile(pipex, av);
	pid1 = fork();
	if (pid1 < 0)
		exit_with_message_and_free("pid1", pipex, 1);
	if (pid1 == 0)
		cmd1_process(pipex, env);
	pid2 = fork();
	if (pid2 < 0)
		exit_with_message_and_free("pid2", pipex, 1);
	if (pid2 == 0)
		cmd2_process(pipex, env);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (pipex->outfile_error != 0)
		return (1);
	return ((status >> 8) & 0xFF);
}

void	cmd1_process(t_pipex *pipex, char **env)
{
	if (!pipex->pathname_cmd1)
	{
		ft_printf("%s : Command not found\n", pipex->cmd1[0]);
		exit_with_message_and_free(NULL, pipex, 127);
	}
	if (pipex->infile > 0)
		dup2(pipex->infile, 0);
	else
		exit_with_message_and_free(NULL, pipex, 127);
	dup2(pipex->pipefd[1], 1);
	close(pipex->pipefd[0]);
	if (pipex->pathname_cmd1)
		execve(pipex->pathname_cmd1, pipex->cmd1, env);
}

void	cmd2_process(t_pipex *pipex, char **env)
{
	if (!pipex->pathname_cmd2)
	{
		ft_printf("%s : Command not found\n", pipex->cmd2[0]);
		exit_with_message_and_free(NULL, pipex, 127);
	}
	dup2(pipex->pipefd[0], 0);
	if (pipex->outfile > 0)
		dup2(pipex->outfile, 1);
	else
		exit_with_message_and_free(NULL, pipex, 1);
	close(pipex->pipefd[1]);
	if (pipex->pathname_cmd2)
		execve(pipex->pathname_cmd2, pipex->cmd2, env);
}
