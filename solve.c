/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:59:57 by vtenigin          #+#    #+#             */
/*   Updated: 2017/01/20 18:02:03 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	solve(t_en *env, t_ant *first)
{
	t_room	*room;
	t_ant	*ant;

	while (env->nba > 0)
	{
		ant = first;
		while (ant)
		{
			if (!ant->room->end)
			{
				room = findshrt(ant->room->link);
				if (room)
					if ((room->dtoe < ant->room->dtoe && !room->start) || ant->room->start)
					{
						if (!room->end)
							room->ocup = ant->id;
						ant->room->ocup = 0;
						ant->room = room;
						ft_printf("L%d-%s ", ant->id, room->name);
						if (room->end)
							env->nba--;
					}
			}
			ant = ant->next;
		}
		ft_printf("\n");
	}
}

t_room	*findshrt(t_link *start)
{
	t_room	*shrt;
	t_link	*link;

	link = start;
	shrt = NULL;
	while (link)
	{
		if (shrt)
		{
			if (link->room->dtoe < shrt->dtoe && !link->room->ocup && !link->room->start)
				shrt = link->room;
		}
		else
		{
			if (!link->room->ocup && !link->room->start)
				shrt = link->room;
		}
		link = link->next;
	}
	return (shrt);
}
