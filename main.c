/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:07:00 by vtenigin          #+#    #+#             */
/*   Updated: 2017/01/20 18:03:26 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	getnba(t_en *env)
{
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
	env->nba = ft_atoi(env->str);
	if (env->nba < 1)
		showerr();
	ft_printf("%d\n", env->nba);
	ft_strdel(&env->str);
}

void	envinit(t_en *env)
{
	env->start = 0;
	env->end = 0;
	env->nbr = 0;
}

t_ant	*antalloc(t_en *env, t_room *room)
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

int		main(void)
{
	t_en	env;
	t_room	*room;
	t_ant	*ant;

	room = NULL;
	envinit(&env);
	getnba(&env);
	room = readroom(&env);
	readlinks(&env, room);
	checkmap(room);
	setdtoe(room);
	isconnected(room);
	checkdouble(room);
	ant = antalloc(&env, room);
	solve(&env, ant);
	freeroom(room);
	freeant(ant);
}
