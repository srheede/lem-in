/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <srheede@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 18:43:57 by srheede           #+#    #+#             */
/*   Updated: 2018/10/22 15:11:54 by srheede          ###   ########.fr       */
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

typedef	struct		s_move
{
	t_room			*room;
	t_room			*tmp;
	t_links			*pos_ants;
	t_links			*pos_new;
	t_links			*tmp_node;
}					t_move;

typedef	struct		s_send
{
	t_room			*room;
	t_links			*pos_ants;
	int				count;
}					t_send;

typedef	struct		s_choose
{
	t_links			*links;
	t_room			*room;
	t_room			*tmp;
}					t_choose;

typedef struct		s_lem
{
	int				count;
	int				n_ants;
	int				n_end;
	int				n_total;
	int				visualizer;
	int				*arr;
	int				fd;
	char			*buffer;
	char			*number;
	t_room			*start;
	t_room			*end;
	t_room			*rooms;
	t_room			*rooms_head;
	t_links			*pos_ants;
	t_links			*pos_new;
	t_links			*pos_new_last;
}					t_lem;

void				delmem(t_lem *lem, int err);
void				count_ants(t_lem *lem);
int					check_start(t_lem *lem);
void				create_room(t_lem *lem, char **arr);
t_links				*linknew(t_room *room);
void				assign_links(t_lem *lem);
t_room				*choose_room(t_lem *lem, t_send *send, t_room *current);
void				send_ants(t_lem *lem);
int					move_ants(t_lem *lem, t_send *send);
void				move3(t_lem *lem, t_send *send, t_move *move);
void				move5(t_lem *lem, t_send *send, t_move *move);
void				result(t_lem *lem, t_send *send, t_room *tmp, t_room *curr);
void				visualize(t_lem *lem);

#endif
