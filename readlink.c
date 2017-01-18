/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readlink.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:47:23 by vtenigin          #+#    #+#             */
/*   Updated: 2017/01/17 17:48:26 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	addlink(t_room *start, char	*r1, char *r2)
{
	t_room	*room;
	t_link	*link;

	room = start;
	link = NULL;
	// ft_printf("name = %s r1 = %s r2 = %s\n", room->name, r1, r2);
	// ft_printf("cmp %d\n", ft_strcmp(room->name, r1));
	while (ft_strcmp(room->name, r1))
	{
		if (room->next)
			room = room->next;
		else
			showerr();
		// ft_printf("test %s\n", room->name);
	}
	// ft_printf("link %s\n", room->link);
	if (room->link)
	{
		link = room->link;
		while (link)
		{
			if (!ft_strcmp(link->room->name, r2))
				showerr();
			else if (link->next)
				link = link->next;
			else
				break ;
		}
	}
	if (link)
	{
		link->next = (t_link *)malloc(sizeof(t_link));
		link = link->next;
		link->next = NULL;
	}
	else
	{
		room->link = (t_link *)malloc(sizeof(t_link));
		link = room->link;
		link->next = NULL;
	}
	// ft_printf("test2\n");
	room = start;
	// ft_printf("test3\n");
	while (room)
	{
		if (!ft_strcmp(r2, room->name))
			break ;
		else
			room = room->next;
	}
	if (!room)
		showerr();
	link->room = room;
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
}
