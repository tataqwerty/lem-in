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
# define ERROR_S_START 7
# define ERROR_S_END 8

typedef	struct		s_ant
{
	int				counter;
	char			*room_name;
	struct s_ant	*next;
}					t_ant;

typedef struct		s_link
{
	void			*link;
	struct s_alist	*next;
}					t_link;

typedef struct		s_room
{
	int				x;
	int				y;
	char			priority;
	char			*name;
	t_link			*sibling;
	struct s_room	*next;
}					t_room;

typedef struct
{
	int				ants_counter;
	t_list			*line_list;
	t_ant			*ant;
	t_room			*room;
}					t_str;

#endif