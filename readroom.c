/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readroom.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:12:27 by vtenigin          #+#    #+#             */
/*   Updated: 2017/01/18 17:36:08 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*roomalloc(t_en *env) // add check for doubles
{
	char	**spl;
	t_room	*room;

	spl = ft_strsplit(env->str, ' ');
	if (spllen(spl) != 3)
		showerr();
	if (!ft_isnumber(spl[1]) || !ft_isnumber(spl[2]))
		showerr();
	// ft_printf("%s\n", spl[0]);
	room = (t_room *)malloc(sizeof(t_room));
	room->name = ft_strdup(spl[0]);
	room->x = ft_atoi(spl[1]);
	room->y = ft_atoi(spl[2]);
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

t_room	*readroom(t_en *env)
{
	t_room	*room;
	t_room	*first;
	int		i;

	i = 0;
	while (get_next_line(0, &env->str) > 0)
	{
		if (env->str[0] == 'L')
			showerr();
		if (env->str[0] != '#' && !ft_strchr(env->str, ' '))
			break ;
		if (!ft_strcmp(env->str, "##start"))
			env->start = 1;
		if (!ft_strcmp(env->str, "##end"))
			env->end = 1;
		if (env->str[0] != '#')
		{
			if (i++ == 0)
			{
				room = roomalloc(env);
				first = room;
			}
			else
			{
				room->next = roomalloc(env);
				room = room->next;
			}
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
