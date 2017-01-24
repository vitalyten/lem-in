/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 18:39:13 by vtenigin          #+#    #+#             */
/*   Updated: 2017/01/23 21:23:01 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/ft_printf.h"

typedef struct	s_room
{
	char			*name;
	struct s_room	*next;
	struct s_link	*link;
	int				x;
	int				y;
	int				start;
	int				end;
	int				dtoe;
	int				ocup;
}				t_room;

typedef struct	s_link
{
	struct s_link	*next;
	t_room			*room;
	int				used;
}				t_link;

typedef struct	s_ant
{
	int				id;
	struct s_ant	*next;
	t_room			*room;
}				t_ant;

typedef struct	s_en
{
	int		nba;
	int		nbant;
	int		start;
	int		end;
	char	*str;
	t_room	*room;
}				t_en;

void			showerr(void);
void			resetlink(t_room *room);
void			getnba(t_en *env);
int				ft_isnumber(char *n);
t_room			*roomalloc(t_en *env);
t_room			*readroom(t_en *env);
int				spllen(char **spl);
void			addlink(t_room *start, char	*r1, char *r2);
void			makelink(t_en *env, t_room *room);
void			readlinks(t_en *env, t_room *room);
void			setdtoe(t_room *start);
void			dtoerec(int dtoe, t_room *room);
void			freeant(t_ant *ant);
void			freeroom(t_room *room);
int				ft_isnumber(char *n);
void			showerr(void);
void			checkdouble(t_room *start);
void			isconnected(t_room *room);
void			checkmap(t_room *room);
void			solve(t_en *env, t_ant *first, t_room *room);
t_link			*findshrt(t_ant *ant, t_en *env);
t_room			*findroom(t_room *room, char *name);
t_link			*linkalloc(t_room *room);
t_ant			*antalloc(t_en *env, t_room *room);
long long		ft_atoll(const char *str);

#endif
