/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 18:43:57 by srheede           #+#    #+#             */
/*   Updated: 2018/08/29 17:50:08 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "./libft/libft.h"
# include <libc.h>

typedef struct		s_links
{
	void			*room;
	struct s_links	*next;
}					t_links;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				ant;
	int				count;
	int				distance;
	int				end;
	t_links			*links;
	t_links			*links_head;
	struct s_room	*next;
}					t_room;

typedef struct	s_lem
{
	int			n_ants;
	int			visualizer;
	int			*arr;
	char		*buffer;
	char		*number;
	t_room		*start;
	t_room		*end;
	t_room		*rooms;
	t_room		*head;
}				t_lem;

int				error_check(int argc, char **argv);

#endif
