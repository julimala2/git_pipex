/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:34 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/28 17:08:11 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

// arguments ./pipex file1 "cmd1" "cmd2" file2

// equivaut a < file1 cmd1 | cmd2 > file 2
//      < dirige le contenu de file1 dans l'input
//      cmd1 va chercher dans file1
//      | redirige l'output de cmd1 vers l'input de cmd2
//      cmd2 s'execute a partir du resultat de cmd1
//      > dirige l'output de cmd22 vers file2

int	main(int argc, char **argv, char **env)
{
	t_pipex_b	*pipex;
	int			ret;
	int			i;
	int			status;

	ret = 0;
	i = 0;
	status = 0;
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
	printf("je suis arrive ici");
	if (pipex->infile == 0)
	{
		init_outfile(pipex);
		free_struct(pipex);
		return (0);
	}
	printf("je suis arrive ici 2");
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
		printf("je suis arrive ici 3");
		close(pipex->pipefd[i][0]);
		close(pipex->pipefd[i][1]);
		printf("je suis arrive ici 3 bis");
		free_cmd(pipex);
		i++;
	}
	printf("je suis arrive ici 4");
	init_cmd(pipex, argv[i + 2]);
	init_outfile(pipex);
	pipex->pid[i] = fork();
	if (pipex->pid[i] < 0)
		exit_with_message_and_free("pid", pipex, 1);
	if (pipex->pid[i] == 0)
		cmd_process(pipex, env, i);
	i = 0;
	printf("je suis arrive ici 5");
	while (i < pipex->cmd_count)
	{
		waitpid(pipex->pid[i], &status, 0);
		ret = (status >> 8) & 0xFF;
		i++;
	}
	if (pipex->outfile_error == 1)
		return (1);
	printf("je suis arrive ici 6");
	free_struct(pipex);
	return (ret);
}

// int execve(const char *pathname, char *const argv[], char *const envp[]);

// ls -l -R

// /usr/bin/ls {/usr/bin/ls, -l, -R} {env}