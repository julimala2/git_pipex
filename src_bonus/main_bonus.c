/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:34 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/20 18:26:13 by jmalaval         ###   ########.fr       */
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

	ret = 0;
	i = 2;
	if (argc < 5)
		exit_with_message("Incorrect number of arguments", "", 1);
	if (access(argv[1], F_OK) < 0)
		perror("Non existing infile");
	pipex = malloc(sizeof(t_pipex_b));
	if (!pipex)
		exit_with_message("", "pipex malloc", 1);
	init_struct(pipex, argv);
	if (pipex->infile == 0)
	{
		init_outfile(pipex, argv);
		free_struct(pipex);
		return (0);
	}
	while (argv[i + 1] != argv[argc - 1])
	{
		init_struct(pipex, argv);
		if (argv[i-1] == argv[1])
			pipex->first_cmd = 1;
		if (argv[i + 2] == argv[argc - 1])
			pipex->last_cmd = 1;
		init_pipex(pipex, argv[i], argv[i + 1], env);
		if (pipe(pipex->pipefd) == -1)
			exit_with_message_and_free("Pipe", pipex, 1);
		ret = ft_pipex(pipex, argv, env);
		free_struct(pipex);
		i++;
	}
	return (ret);
}

// int execve(const char *pathname, char *const argv[], char *const envp[]);

// ls -l -R

// /usr/bin/ls {/usr/bin/ls, -l, -R} {env}