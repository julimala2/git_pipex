/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:34 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/29 19:16:09 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex_b	*pipex;
	int			ret;

	ret = 0;
	if (argc < 5)
		exit_with_message("Incorrect number of arguments", "", 1);
	if (access(argv[1], F_OK) < 0)
		perror("Non existing infile");
	pipex = malloc(sizeof(t_pipex_b));
	if (!pipex)
		exit_with_message("", "pipex malloc", 1);
	pipex->path_outfile = argv[argc - 1];
	pipex->cmd_count = argc - 3;
	init_struct(pipex, argv, env);
	if (pipex->infile == -2)
		return (error_infile(pipex));
	ft_pipex(pipex, argv, env);
	ret = ft_waitpid(pipex);	
	if (pipex->outfile_error == 1)
		return (1);
	free_struct(pipex);
	return (ret);
}

void	ft_pipex(t_pipex_b *pipex, char **argv, char **env)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		init_cmd(pipex, argv[i + 2]);
		pipex->pipefd[i] = malloc(sizeof(int) * 2);
		if (pipe(pipex->pipefd[i]) == -1)
			exit_with_message_and_free("Pipe", pipex, 1);
		pipex->pid[i] = fork();
		if (pipex->pid[i] < 0)
			exit_with_message_and_free("pid", pipex, 1);
		if (pipex->pid[i] == 0)
			cmd_process(pipex, env, i);
		close(pipex->pipefd[i][1]);
		if (i > 0)
			close(pipex->pipefd[i-1][0]);
		free_tab(pipex->cmd);
		i++;
	}
	last_cmd(pipex, argv, env, i);
}

void	last_cmd(t_pipex_b *pipex, char **argv, char **env, int i)
{
	init_cmd(pipex, argv[i + 2]);
	init_outfile(pipex);
	pipex->pid[i] = fork();
	if (pipex->pid[i] < 0)
		exit_with_message_and_free("pid", pipex, 1);
	if (pipex->pid[i] == 0)
		cmd_process(pipex, env, i);
	close(pipex->pipefd[i-1][0]);
}

int	ft_waitpid(t_pipex_b *pipex)
{
	int	i;
	int	ret;
	int status;

	i = 0;
	ret = 0;
	status = 0;
	while (i < pipex->cmd_count)
	{
		waitpid(pipex->pid[i], &status, 0);
		ret = (status >> 8) & 0xFF;
		i++;
	}
	return (ret);
}

int	error_infile(t_pipex_b *pipex)
{
	init_outfile(pipex);
	free_struct(pipex);
	return (0);
}
