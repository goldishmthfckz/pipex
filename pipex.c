/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:27:06 by estegana          #+#    #+#             */
/*   Updated: 2024/01/24 17:27:09 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//separe le contenu de la variable d'env "PATH"
//split cmd si y a une option (ex: "ls -l")
//pr chaque partie de allpath :
//> ajoute "/cmd" a chaque fin
//> si cmd existe et peut s'executer -> renvoie chemin de cmd
//sinon free tout et return cmd
char	*cmdpath(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**split_cmd;

	i = -1;
	allpath = ft_split(printvariableenv("PATH", env), ':');
	split_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, split_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_freelist(split_cmd);
			return (exec);
		}
		free(exec);
	}
	ft_freelist(allpath);
	ft_freelist(split_cmd);
	return (cmd);
}

//split la cmd si elle contient une option (ex: "ls -l")
//releve son chemin (ex: /usr/bin/ls)
//si l'exe a un pb (ex: cmd existe pas) -> msg d'erreur puis free
void	execute_cmd(char *cmd, char **env)
{
	char	**split_cmd;
	char	*path;

	split_cmd = ft_split(cmd, ' ');
	path = cmdpath(split_cmd[0], env);
	if (execve(path, split_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(split_cmd[0], 2);
		ft_freelist(split_cmd);
		exit(127);
	}
}

//ouvre le fichier "infile" (av[1]) pr le lire
//le duplique ds l'entree standard (clavier = 0)
//duplique l'extremite d'ecriture tube[1] en sortie standard pr cmd1 (av[2])
//close l'extremite
//execute cmd1 (av[2])
void	child(char **av, int *tube, char **env)
{
	int		infile;

	infile = open_file(av[1], 0);
	dup2(infile, 0);
	dup2(tube[1], 1);
	close(tube[0]);
	execute_cmd(av[2], env);
}

//ouvre le fichier "outfile" (av[4]) pr y ecrire
//le duplique ds la sortie standard (ecran = 1)
//duplique l'extremite de lecture tube[0] en entree standard pr cmd2 (av[3])
//close l'extremite
//execute cmd2 (av[3])
void	parent(char **av, int *tube, char **env)
{
	int		outfile;

	outfile = open_file(av[4], 1);
	dup2(outfile, 1);
	dup2(tube[0], 0);
	close(tube[1]);
	execute_cmd(av[3], env);
}

//si y a bien 4 argv ;
//> pipe(tube). tube[0] = lecture, tube[1] = ecriture
//>> si ya erreur de pipe, exit tt le programme
//> fork
//>> si ya erreur de fork, exit tt le programme
//> sinon rentre ds processus parent puis enfant
int	main(int ac, char **av, char **env)
{
	int		tube[2];
	pid_t	pid;

	if (ac == 5)
	{
		if (pipe(tube) == -1)
			ft_exit("__ERROR_PIPE__:\nError pipe.\n");
		pid = fork();
		if (pid == -1)
			ft_exit("__ERROR_FORK__:\nError fork.\n");
		else if (pid == 0)
			child(av, tube, env);
		else
			parent(av, tube, env);
		close(tube[0]);
		close(tube[1]);
	}
	else
		ft_exit("__ERROR_ARGS__:\nInvalid number of args.\n");
	return (0);
}
