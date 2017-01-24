/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:59:57 by vtenigin          #+#    #+#             */
/*   Updated: 2017/01/23 21:23:23 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	moveant(t_en *env, t_ant *ant)
{
	t_link	*link;
	t_room	*room;

	link = findshrt(ant, env);
	if (link)
	{
		room = link->room;
		if (!link->used && (room->dtoe < ant->room->dtoe || ant->room->start))
		{
			ant->room->ocup = 0;
			ant->room = room;
			link->used = 1;
			ft_printf("L%d-%s ", ant->id, room->name);
			(room->end) ? (env->nba--) : (room->ocup = ant->id);
		}
	}
}

void	solve(t_en *env, t_ant *first, t_room *start)
{
	t_ant	*ant;

	while (env->nba > 0)
	{
		resetlink(start);
		ant = first;
		while (ant)
		{
			if (!ant->room->end)
				moveant(env, ant);
			ant = ant->next;
		}
		ft_printf("\n");
	}
}

t_link	*shrtany(t_link *link)
{
	t_link	*shrt;

	shrt = NULL;
	while (link)
	{
		if (shrt)
		{
			if (link->room->dtoe < shrt->room->dtoe && link->room->dtoe != -1)
				shrt = link;
		}
		else
		{
			if (link->room->dtoe != -1)
				shrt = link;
		}
		link = link->next;
	}
	return (shrt);
}

t_link	*shrtunoc(t_link *link)
{
	t_link	*shrt;

	shrt = NULL;
	while (link)
	{
		if (shrt)
		{
			if (link->room->dtoe < shrt->room->dtoe
				&& !link->room->ocup && link->room->dtoe != -1)
				shrt = link;
		}
		else
		{
			if (!link->room->ocup && link->room->dtoe != -1)
				shrt = link;
		}
		link = link->next;
	}
	return (shrt);
}

t_link	*findshrt(t_ant *ant, t_en *env)
{
	t_link	*shrt;
	t_link	*shrt2;

	shrt = shrtunoc(ant->room->link);
	shrt2 = shrtany(ant->room->link);
	if (shrt && shrt2)
	{
		if (!ft_strcmp(shrt->room->name, shrt2->room->name)
			|| shrt->room->dtoe <= env->nbant - ant->id + shrt2->room->dtoe)
			return (shrt);
	}
	return (NULL);
}
