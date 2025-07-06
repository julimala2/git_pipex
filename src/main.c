/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:34 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/04 16:27:13 by jmalaval         ###   ########.fr       */
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
	t_pipex	*pipix;
	char	*path;

	if (argc != 5)
		exit_with_message("Invalid number of arguments\n");
	if (access(argv[1], F_OK) < 0)
		perror("Access");
	path = get_env_value("PATH=", env);
	pipix = malloc(sizeof(t_pipex));
	pipix->directories = ft_split(path, ':');
	if (existing_cmd(argv[2], pipix->directories) == 0 || existing_cmd(argv[3],
			pipix->directories) == 0)
	{
		ft_printf("Non existing command\n");
		free(path);
		free(pipix->directories);
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}

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