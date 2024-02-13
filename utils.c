/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:56:55 by estegana          #+#    #+#             */
/*   Updated: 2024/02/05 16:56:57 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//prend un fichier et
//soit 0 : permet juste de le lire
//soit 1 : permet juste d'y ecrire
//soit -1 : exit tt
int	open_file(char *file, int inout)
{
	int	ret;

	if (inout == 0)
		ret = open(file, O_RDONLY, 0777);
	if (inout == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (ret == -1)
		ft_exit("__ERROR_FILE__:\nCan't read outfile or infile.\n");
	return (ret);
}

//free liste de chaine de char
void	ft_freelist(char **list)
{
	size_t	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}

//dans env, renvoie le contenu de la variable d'environnement recherchee
//(ici PATH)
char	*printvariableenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(sub)) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

//ecrit msg d'erreur correspondant a la situation puis 
void	ft_exit(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}
