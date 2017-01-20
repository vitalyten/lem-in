/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:07:00 by vtenigin          #+#    #+#             */
/*   Updated: 2017/01/19 18:49:11 by vtenigin         ###   ########.fr       */
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

void	solve(t_en *env, t_ant *first)
{
	t_room	*room;
	t_ant	*ant;
	// int		i;

	// i = 0;
	while (env->nba > 0)// && ++i < 10)
	{
		// ant = first;
		// while (ant)
		// {
		// 	ft_printf("ant %d room %s\n", ant->id, ant->room->name);
		// 	ant = ant->next;
		// }
		ant = first;
		while (ant)
		{
			if (!ant->room->end)
			{
				room = findshrt(ant->room->link);
				// ft_printf("ant %d room %s\n", ant->id, ant->room->name);
				// if (room)
				// 	ft_printf("name %s\n", room->name);
				// else
				// 	ft_printf("null\n");
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

t_ant	*antalloc(t_en *env, t_room *room)
{
	int		i;
	t_ant	*ant;
	t_ant	*first;

	while (!room->start)
		room = room->next;
	i = 1;
	ant = (t_ant *)malloc(sizeof(t_ant));
	first = ant;
	ant->next = NULL;
	ant->id = 1;
	ant->room = room;
	while (++i <= env->nba)
	{
		ant->next = (t_ant *)malloc(sizeof(t_ant));
		ant = ant->next;
		ant->next = NULL;
		ant->id = i;
		ant->room = room;
	}
	return (first);
}



int	main(void) // add check start connected to end
{
	t_en	env;
	t_room	*room;
	t_room	*start;
	t_link	*link;
	t_ant	*ant;

	room = NULL;
	envinit(&env);
	getnba(&env);
	room = readroom(&env);
	readlinks(&env, room);
	checkmap(room);
	setdtoe(room);
	ant = antalloc(&env, room);
	// while (ant)
	// {
	// 	ft_printf("id = %d room = %s\n", ant->id, ant->room->name);
	// 	ant = ant->next;
	// }
	start = room;
	while (room)
	{
		ft_printf("name = %s start = %d end = %d dtoe = %d\n",
			room->name, room->start, room->end, room->dtoe);
		link = room->link;
		while (link)
		{
			ft_printf("link : name = %s\n", link->room->name);
			link = link->next;
		}
		room = room->next;
	}
	solve(&env, ant);
	freeroom(start);
	freeant(ant);
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
