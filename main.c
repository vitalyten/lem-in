/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:07:00 by vtenigin          #+#    #+#             */
/*   Updated: 2017/01/16 21:25:57 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	getnba(t_en *env)
{
	if (get_next_line(0, &env->str) < 1)
		showerr();
	if (!ft_isnumber(env->str))
		showerr();
	env->nba = ft_atoi(env->str);
	if (env->nba < 1)
		showerr();
	ft_printf("%d\n", env->nba);
	ft_strdel(&env->str);
}

void	envinit(t_en *env)
{
	env->start = 0;
	env->end = 0;
	env->nbr = 0;
}

void	addlink(t_room *start, char	*r1, char *r2)
{
	t_room	*room;
	t_link	*link;

	room = start;
	while (ft_strcmp(room->name, r1))
	{
		if (room->next)
			room = room->next;
		else
			showerr();
	}
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
	link->next = (t_link *)malloc(sizeof(t_link));
	link = link->next;
	room = start;
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

int	main(void)
{
	t_en	env;
	t_room	*room;
	t_link	*link;

	room = NULL;
	envinit(&env);
	getnba(&env);
	room = readroom(&env);
	readlinks(&env, room);
	while (room)
	{
		ft_printf("name = %s start = %d end = %d\n",
			room->name, room->start, room->end);
		link = room->link;
		// while (link)
		// {
		// 	ft_printf("link : name = %s\n", link->room->name);
		// 	link = link->next;
		// }
		room = room->next;
	}
}

void		showerr(void)
{
	write(2, "ERROR\n", 6);
	exit(EXIT_FAILURE);
}

int			ft_isnumber(char *n)
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

// long long	ft_atoll(const char *str)
// {
// 	long long	res;
// 	long long	sign;

// 	res = 0;
// 	sign = 1;
// 	while (ft_iswhitespace(*str))
// 		str++;
// 	if (*str == '-')
// 	{
// 		sign = -1;
// 		str++;
// 	}
// 	else if (*str == '+')
// 		str++;
// 	while (ft_isdigit(*str))
// 	{
// 		res = res * 10 + *str - '0';
// 		str++;
// 	}
// 	return (sign * res);
// }



// void	free2d(char **strs)
// {
// 	int i;

// 	i = -1;
// 	while (strs[++i])
// 		free(strs[i]);
// 	free(strs);
// }
