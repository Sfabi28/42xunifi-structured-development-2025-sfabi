/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfabi <sfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:06:20 by sfabi             #+#    #+#             */
/*   Updated: 2023/10/30 16:14:34 by sfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	*get_next_line(int fd);
char	*get_single_line(char *str);
char	*f_strjoin(char *s1, char *s2);
int		f_sl(char *c);
char	*ft_calloc(size_t nmemb, size_t size);
char	*free_and_null(char *to_free, char **to_null);

#endif
