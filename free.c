/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 17:49:11 by vtenigin          #+#    #+#             */
/*   Updated: 2017/01/19 17:51:50 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	freeroom(t_room *room)
{
	t_room	*tmp;
	t_link	*link;

	while (room)
	{
		while (room->link)
		{
			link = room->link;
			room->link = room->link->next;
			free(link);
		}
		tmp = room;
		room = room->next;
		free(tmp);
	}
}

void	freeant(t_ant *ant)
{
	t_ant *tmp;

	while (ant)
	{
		tmp = ant;
		ant = ant->next;
		free(tmp);
	}
}
