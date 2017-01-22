/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readroom.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:12:27 by vtenigin          #+#    #+#             */
/*   Updated: 2017/01/21 17:42:08 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*roomalloc(t_en *env)
{
	char		**spl;
	t_room		*room;
	long long	l;

	spl = ft_strsplit(env->str, ' ');
	(spllen(spl) != 3) ? showerr() : 0;
	(!ft_isnumber(spl[1]) || !ft_isnumber(spl[2])) ? showerr() : 0;
	room = (t_room *)malloc(sizeof(t_room));
	room->name = ft_strdup(spl[0]);
	l = ft_atoll(spl[1]);
	(l > 2147483647 || l < -2147483648) ? showerr() : 0;
	room->x = (int)l;
	l = ft_atoll(spl[2]);
	(l > 2147483647 || l < -2147483648) ? showerr() : 0;
	room->y = (int)l;
	room->dtoe = -1;
	room->ocup = 0;
	room->next = NULL;
	room->link = NULL;
	room->start = (env->start) ? 1 : 0;
	env->start = 0;
	room->end = (env->end) ? 1 : 0;
	env->end = 0;
	free2d(spl);
	return (room);
}

void	setsten(t_en *env)
{
	if (!ft_strcmp(env->str, "##start"))
		env->start = 1;
	if (!ft_strcmp(env->str, "##end"))
		env->end = 1;
}

t_room	*readroom(t_en *env)
{
	t_room	*room;
	t_room	*first;

	room = NULL;
	while (get_next_line(0, &env->str) > 0)
	{
		if (env->str[0] == 'L')
			showerr();
		if (env->str[0] != '#' && !ft_strchr(env->str, ' '))
			break ;
		setsten(env);
		if (env->str[0] != '#' && !room)
		{
			room = roomalloc(env);
			first = room;
		}
		else if (env->str[0] != '#')
		{
			room->next = roomalloc(env);
			room = room->next;
		}
		ft_printf("%s\n", env->str);
		ft_strdel(&env->str);
	}
	return (first);
}

int		spllen(char **spl)
{
	int i;

	i = 0;
	while (spl[i])
		i++;
	return (i);
}
