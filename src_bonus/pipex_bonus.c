/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/29 19:14:42 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	cmd_process(t_pipex_b *pipex, char **env, int index)
{
	if (index == 0)
	{
		if (pipex->infile)
			ft_dup2_and_close(pipex->infile, 0);
	}
	else
		ft_dup2_and_close(pipex->pipefd[index - 1][0], 0);

	if (index == pipex->cmd_count - 1)
	{
		init_outfile(pipex);
		ft_dup2_and_close(pipex->outfile, 1);
	}
	else
		ft_dup2_and_close(pipex->pipefd[index][1], 1);
	close_fd(pipex, index);
	if (pipex->pathname_cmd)
		execve(pipex->pathname_cmd, pipex->cmd, env);
	else if (!pipex->pathname_cmd && index == pipex->cmd_count - 1)
		exit_with_message_and_free("cmd fail", pipex, 127);
}

void	close_fd(t_pipex_b *pipex, int index)
{
	int i;
	
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (i != index && i != index - 1)
		{
			close(pipex->pipefd[i][0]);
			close(pipex->pipefd[i][1]);
		}
		else if (i == index - 1)
			close(pipex->pipefd[i][1]);
		else if (i == index)
			close(pipex->pipefd[i][0]);
		i++;
	}
}

void	ft_dup2_and_close(int fd, int n)
{
		dup2(fd, n);
		close(fd);
}