/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:07:00 by vtenigin          #+#    #+#             */
/*   Updated: 2017/01/23 21:23:53 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		resetlink(t_room *room)
{
	t_link *link;

	while (room)
	{
		link = room->link;
		while (link)
		{
			link->used = 0;
			link = link->next;
		}
		room = room->next;
	}
}

void		getnba(t_en *env)
{
	long long l;

	if (get_next_line(0, &env->str) < 1)
		showerr();
	while (!ft_isnumber(env->str))
	{
		if (env->str[0] != '#')
			showerr();
		ft_printf("%s\n", env->str);
		ft_strdel(&env->str);
		if (get_next_line(0, &env->str) < 1)
			showerr();
	}
	l = ft_atoll(env->str);
	if (l > 2147483647 || l < 1)
		showerr();
	env->nba = (int)l;
	env->nbant = (int)l;
	ft_printf("%d\n", env->nba);
	ft_strdel(&env->str);
}

t_ant		*antalloc(t_en *env, t_room *room)
{
	int		i;
	t_ant	*ant;
	t_ant	*first;

	while (!room->start)
		room = room->next;
	i = 1;
	ant = (t_ant *)malloc(sizeof(t_ant));
	first = ant;
	ant->next = NULL;
	ant->id = 1;
	ant->room = room;
	while (++i <= env->nba)
	{
		ant->next = (t_ant *)malloc(sizeof(t_ant));
		ant = ant->next;
		ant->next = NULL;
		ant->id = i;
		ant->room = room;
	}
	return (first);
}

int			main(void)
{
	t_en	env;
	t_room	*room;
	t_ant	*ant;

	room = NULL;
	getnba(&env);
	room = readroom(&env);
	if (!room)
		showerr();
	readlinks(&env, room);
	checkmap(room);
	setdtoe(room);
	isconnected(room);
	checkdouble(room);
	ant = antalloc(&env, room);
	solve(&env, ant, room);
	freeroom(room);
	freeant(ant);
}

long long	ft_atoll(const char *str)
{
	long long	res;
	long long	sign;

	res = 0;
	sign = 1;
	while (ft_iswhitespace(*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (sign * res);
}
