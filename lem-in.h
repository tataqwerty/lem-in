#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# define START 1
# define END 2
# define ERROR_HZ -1
# define ERROR_INVALID_FILE 3
# define ERROR_INVALID_QUANTITY_OF_ANTS 4
# define ERROR_WITH_ROOM 5
# define ERROR_NOT_UNIQUE_ROOM 6
# define ERROR_SECOND_START 7
# define ERROR_SECOND_END 8
# define ERROR_NOT_ENOUGH_INFO 9
# define ERROR_INVALID_LINK 10
# define ERROR_INVALID_ORDER 11

typedef	struct		s_ant
{
	int				counter;
	char			*room_name;
	struct s_ant	*next;
}					t_ant;

typedef struct		s_room
{
	int				x;
	int				y;
	int				level;
	int				links_size;
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
	t_way			*way;
	int				length;
}					t_ways;

typedef struct
{
	int				ants_counter;
	t_list			*line_list;
	t_ant			*ant;
	t_room			*room;
	t_ways			**ways;
	int				ways_size;
}					t_str;

typedef struct		s_queue
{
	t_room			*room;
	struct s_queue	*next;
}					t_queue;

#endif
