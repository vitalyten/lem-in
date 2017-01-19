/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtoe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 17:18:49 by vtenigin          #+#    #+#             */
/*   Updated: 2017/01/18 17:19:51 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	dtoerec(int dtoe, t_room *room)
{
	t_link	*link;

	link = room->link;
	if (room->start || (room->dtoe != -1 && room->dtoe < dtoe))
		return ;
	if (room->dtoe == -1 || room->dtoe > dtoe)
		room->dtoe = dtoe;
	while (link)
	{
		dtoerec(dtoe + 1, link->room);
		link = link->next;
	}
}

void	setdtoe(t_room *start)
{
	t_room	*room;

	room = start;
	while (!room->end)
		room = room->next;
	if (!room->link)
		showerr();
	dtoerec(0, room);
}
