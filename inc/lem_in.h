/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 10:29:18 by tkiselev          #+#    #+#             */
/*   Updated: 2018/11/05 13:33:05 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# define START 1
# define END 2
# define ERROR_INVALID_FILE 3
# define ERROR_INVALID_QUANTITY_OF_ANTS 4
# define ERROR_WITH_ROOM 5
# define ERROR_NOT_UNIQUE_ROOM 6
# define ERROR_SECOND_START 7
# define ERROR_SECOND_END 8
# define ERROR_NOT_ENOUGH_INFO 9
# define ERROR_INVALID_LINK 10
# define ERROR_NO_SOLUTION 11

typedef struct		s_room
{
	int				x;
	int				y;
	int				level;
	int				links_size;
	int				ants;
	int				ant_id;
	char			priority;
	char			used : 1;
	char			iq : 1;
	char			visited : 1;
	char			*name;
	struct s_room	*parent;
	struct s_room	*next;
	struct s_room	**links;
}					t_room;

typedef struct		s_way
{
	t_room			*room;
	struct s_way	*next;
}					t_way;

typedef struct
{
	int				length;
	t_way			*way;
}					t_ways;

typedef struct
{
	int				ants_counter;
	t_list			*line_list;
	t_room			*room;
	t_ways			**ways;
	int				ways_size;
}					t_str;

typedef struct		s_queue
{
	t_room			*room;
	struct s_queue	*next;
}					t_queue;

char				is_command(char *str);
char				is_room(char *str);
char				is_link(char *str);
char				is_comment(char *str);
char				is_int(char *str);
t_room				*init_room(char **arr, char priority);
void				room_push_front(t_room **room, char **arr, char priority);
void				room_push_back(t_room **room, char **arr, char priority);
void				add_room(t_room **room, char *str, char priority);
void				add_room_with_command(t_str *s, char **line, char *flag);
void				apply_link(t_room ***links, t_room *room, int *size);
char				connect_links(t_room *room1, t_room *room2);
char				find_place_n_connect_links(t_room **head, char *link);
void				get_ants_counter(int *counter, t_list **list, char *line);
void				get_rooms(t_str *s, char **line);
char				get_links(t_str *s, char **line);
char				parsing(t_str *s);
void				send_ants(t_ways **ways, int ways_size,
					int *ants_counter, char *flag);
void				bring_remaining_ants(t_ways **ways,
					int ways_size, char *flag);
void				print_steps(t_str *s, t_room *end);
void				output(t_str *s);
void				remalloc_ways(t_ways ***ways,
					t_way *new_way, int *ways_size);
void				pushback(t_way **way, t_room *room);
t_way				*create_way(t_room *end_room);
void				generate_ways(t_str *s);
void				enqueue(t_queue **queue, t_room *room);
void				dequeue(t_queue **queue);
t_room				*get_room_from_queue(t_queue *queue, t_room *room_to_find);
char				bfs(t_queue **queue);
int					length_way(t_way *way);
void				clear_rooms(t_room *room);
void				error(char error);

#endif
