/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:34 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/11 01:01:26 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// arguments ./pipex file1 "cmd1" "cmd2" file2

// equivaut a < file1 cmd1 | cmd2 > file 2
//      < dirige le contenu de file1 dans l'input
//      cmd1 va chercher dans file1
//      | redirige l'output de cmd1 vers l'input de cmd2
//      cmd2 s'execute a partir du resultat de cmd1
//      > dirige l'output de cmd22 vers file2

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;
	

	if (argc != 5)
		ft_putendl_fd("Incorrect number of arguments", 2);
	if (access(argv[1], F_OK) < 0)
		perror("Access");
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		perror("pipex malloc");
	pipex->path = get_env_value("PATH=", env);
	pipex->directories = ft_split(pipex->path, ':');
	char **test = ft_split("Coucou je m'appelle Juliette", ' ');
	int i = 0;
	while (test[i++])
		printf("%s\n", test[i]);
	return 0;
	while (pipex->directories && pipex->directories[i++])
		printf("%s\n", pipex->directories[i]);  /// split finit par segfault alors que le dernier tab est set a NULL, il manque le premier mot
	return 0;
	init_struct(pipex);
	init_pipex(pipex, argv, env);
	ft_printf("%s\n", pipex->path); //////////////////////////////// test ///////////////////////
	if (pipe(pipex->pipefd) == -1)
	{
		free_struct(pipex);
		perror("Pipe");
	}
	ft_pipex(pipex, env);
	free_struct(pipex);
	return (0);
}

// pb avec get pathname a regler

// Main checklist

// OK ---- Check the existence of infile and outfile
// be sure to understand what > does when the file does not exist
// Create the necessary pipe (or pipes)
// Create a child process for each command
// Wait for all the processes to end before writing to the outfile
// When using here_doc, the second argument is not a command ;)

// Execute checklist
// Remember that the execve() function needs the path to a binary file as parameter,
	// so you'll have to find where the commands binaries are stored on your computer.
// Before going further, you have to know how to find any command binary.
// OK ---- Check in all possible locations if the binary (command) requested by the user exists.
// "Build" the arguments array for the command.
// Execute the command using execve()

// int execve(const char *pathname, char *const argv[], char *const envp[]);

// ls -l -R

// /usr/bin/ls {/usr/bin/ls, -l, -R} {env}