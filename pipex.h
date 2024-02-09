/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:29:13 by estegana          #+#    #+#             */
/*   Updated: 2024/01/24 17:29:15 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
//# include <sys/types.h>
# include <unistd.h>
# include "libft/incl/libft.h"

//mandatory
int		open_file(char *file, int n);
char	*printvariableenv(char *name, char **env);
void	ft_freelist(char **list);

#endif
