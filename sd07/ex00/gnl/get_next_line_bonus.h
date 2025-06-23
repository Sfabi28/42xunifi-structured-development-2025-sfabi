/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfabi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:01:53 by sfabi             #+#    #+#             */
/*   Updated: 2023/11/03 16:01:56 by sfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	int				fd;
	char			*ptr;
	struct s_list	*next;
}					t_fd_list;

char	*get_next_line(int fd);
char	*get_single_line(char *str);
char	*f_strjoin(char *s1, char *s2);
int		f_sl(char *c);
char	*ft_calloc(size_t nmemb, size_t size);
char	*free_and_null(char *to_free, char **to_null);

#endif
