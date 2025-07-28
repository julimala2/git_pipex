/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/28 16:54:45 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

// int	ft_pipex(t_pipex_b *pipex, char **env)
// {
// 	int	status;
// 	int	i;

// 	status = 0;
// 	i = 0;
// 	while (i < pipex->cmd_count)
// 	{
// 		pipex->pid[i] = fork();
// 		if (pipex->pid[i] < 0)
// 			exit_with_message_and_free("pid", pipex, 1);
// 		if (pipex->pid[i] == 0)
// 			//cmd_process(pipex, env);
// 		// close(pipex->pipefd[0]);
// 		close(pipex->pipefd[1]);
// 		i++;
// 	} // je pense que c'est pas la qu'il faut fermer mais on verra plus tard
// 	// bah merde je dois boucler sur les argv aussi ptn
// 	waitpid(pipex->pid[i], &status, 0);
// 	if (pipex->outfile_error == 1)
// 		return (1);
// 	return ((status >> 8) & 0xFF);
// 	// en fait il me faut un while dans cette fonction
// }

void	cmd_process(t_pipex_b *pipex, char **env, int index)
{
	int	i;

	i = 0;
	if (index == 0)
	{
		if (pipex->infile)
		{
			dup2(pipex->infile, 0);
			close(pipex->infile);
		}
	}
	else
	{
		dup2(pipex->pipefd[index - 1][0], 0);
		close(pipex->pipefd[index - 1][0]);
	}
	if (index == pipex->cmd_count - 1)
	{
		init_outfile(pipex);
		dup2(pipex->outfile, 1);
		close(pipex->outfile);
	}
	else
	{
		dup2(pipex->pipefd[index][1], 1);
		close(pipex->pipefd[index][1]);
	}
	while (i < pipex->cmd_count - 1)
	{
		close(pipex->pipefd[i][0]);
		close(pipex->pipefd[i][1]);
	}
	if (pipex->pathname_cmd)
		execve(pipex->pathname_cmd, pipex->cmd, env);
}
