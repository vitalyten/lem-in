/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:59:57 by vtenigin          #+#    #+#             */
/*   Updated: 2017/01/23 20:14:04 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	resetlink(t_room *room)
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

void	solve(t_en *env, t_ant *first, t_room *start)
{
	t_room	*room;
	t_link	*link;
	t_ant	*ant;
	int	i;

	i = 0;
	while (env->nba > 0)
	{
		resetlink(start);
		i++;
		ft_printf("%3d ", i);
		ant = first;
		while (ant)
		{
			if (!ant->room->end)
			{
				link = findshrt(ant, env);
				if (link)
				{
					room = link->room;
					if ((room->dtoe < ant->room->dtoe && !link->used)
						|| (ant->room->start && !link->used))
					{
						ant->room->ocup = 0;
						ant->room = room;
						link->used = 1;
						ft_printf("L%d-%s ", ant->id, room->name);
						(room->end) ? (env->nba--) : (room->ocup = ant->id);
					}
				}
			}
			ant = ant->next;
		}
		ft_printf("\n");
	}
}

t_link	*findshrt(t_ant *ant, t_en *env)
{
	t_link	*shrt;
	t_link	*shrt2;
	t_link	*link;

	link = ant->room->link;
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
	link = ant->room->link;
	shrt2 = NULL;
	while (link)
	{
		if (shrt2)
		{
			if (link->room->dtoe < shrt2->room->dtoe && link->room->dtoe != -1)
				shrt2 = link;
		}
		else
		{
			if (link->room->dtoe != -1)
				shrt2 = link;
		}
		link = link->next;
	}
	// return (shrt);
	if (shrt && shrt2)
	{
		if (!ft_strcmp(shrt->room->name, shrt2->room->name)
			|| shrt->room->dtoe <= env->nbant - ant->id + shrt2->room->dtoe)
			return (shrt);
	}
	return (NULL);
}
