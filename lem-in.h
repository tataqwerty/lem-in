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
# define ERROR_NOT_UNIQUE_LINK 11
# define ERROR_INVALID_ORDER 12

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
	char			priority;
	int				level;
	struct s_room	*parent;
	char			visited : 1;
	char			iq : 1;
	char			*name;
	struct s_room	**links;
	int				links_size;
	struct s_room	*next;
}					t_room;

typedef struct
{
	int				ants_counter;
	t_list			*line_list;
	t_ant			*ant;
	t_room			*room;
}					t_str;

typedef struct		s_queue
{
	t_room		*room;
	struct s_queue	*next;
}			t_queue;

#endif
