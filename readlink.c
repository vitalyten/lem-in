/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readlink.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:47:23 by vtenigin          #+#    #+#             */
/*   Updated: 2017/01/24 17:22:17 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_link	*linkalloc(t_room *room)
{
	t_link *link;

	link = (t_link *)malloc(sizeof(t_link));
	link->next = NULL;
	link->room = room;
	link->used = 0;
	return (link);
}

t_room	*findroom(t_room *room, char *name)
{
	while (ft_strcmp(room->name, name))
	{
		room = room->next;
		if (!room)
			showerr();
	}
	return (room);
}

void	addlink(t_room *start, char *r1, char *r2)
{
	t_room	*room1;
	t_room	*room2;
	t_link	*link;

	link = NULL;
	(!ft_strcmp(r1, r2)) ? showerr() : 0;
	room1 = findroom(start, r1);
	room2 = findroom(start, r2);
	if (room1->link)
	{
		link = room1->link;
		while (link)
		{
			if (!ft_strcmp(link->room->name, r2))
				return ;
			else if (link->next)
				link = link->next;
			else
				break ;
		}
	}
	if (link)
		link->next = linkalloc(room2);
	else
		room1->link = linkalloc(room2);
}

void	makelink(t_en *env, t_room *room)
{
	char	**spl;

	if (env->str[0] != '#' && !ft_strchr(env->str, '-'))
		showerr();
	spl = ft_strsplit(env->str, '-');
	if (spllen(spl) != 2 && env->str[0] != '#')
		showerr();
	if (spllen(spl) == 2 && env->str[0] != '#')
	{
		addlink(room, spl[0], spl[1]);
		addlink(room, spl[1], spl[0]);
	}
	ft_printf("%s\n", env->str);
	free2d(spl);
}

void	readlinks(t_en *env, t_room *room)
{
	if (env->str)
	{
		makelink(env, room);
		ft_strdel(&env->str);
	}
	while (get_next_line(0, &env->str) > 0)
	{
		makelink(env, room);
		ft_strdel(&env->str);
	}
	ft_printf("\n");
}
