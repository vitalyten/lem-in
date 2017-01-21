/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:51:23 by vtenigin          #+#    #+#             */
/*   Updated: 2017/01/20 17:58:46 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	showerr(void)
{
	write(2, "ERROR\n", 6);
	exit(EXIT_FAILURE);
}

int		ft_isnumber(char *n)
{
	int i;

	i = 0;
	if (n[0] == '-' || n[0] == '+')
		i++;
	while (n[i])
		if (!ft_isdigit(n[i++]))
			return (0);
	return (1);
}

void	isconnected(t_room *room)
{
	t_link *link;

	while (!room->start)
		room = room->next;
	link = room->link;
	while (link)
	{
		if (link->room->dtoe != -1)
			return ;
		link = link->next;
	}
	if (!link)
		showerr();
}

void	checkdouble(t_room *start)
{
	t_room *room;
	t_room *next;

	room = start;
	while (room)
	{
		next = room->next;
		while (next)
		{
			if (!ft_strcmp(room->name, next->name))
				showerr();
			if (room->x == next->x && room->y == next->y)
				showerr();
			next = next->next;
		}
		room = room->next;
	}
}

void	checkmap(t_room *room)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (room)
	{
		if (room->start)
			start++;
		if (room->end)
			end++;
		room = room->next;
	}
	if (start != 1 || end != 1)
		showerr();
}
