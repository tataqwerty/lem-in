#ifndef LEM_IN_H
# define LEM_IN_H

# define INV_FILE 1
# define INV_ANTS 2
# define LINK_BEFORE_ROOM 3
# define WTF 4
# define SEVERAL_STARTS 5
# define SEVERAL_ENDS 6
# define NOT_A_ROOM 7

typedef	struct		s_ant
{
	int				counter;
	char			*room_name;
	struct s_ant	*next;
}					t_ant;

typedef struct		s_alist
{
	void			*link;
	struct s_alist	*next;
}					t_alist;

typedef struct		s_room
{
	char			flags : 2;
	char			*name;
	t_alist			*neighbour;
	struct s_room	*next;
}					t_room;

typedef struct
{
	int				ants;
	int				rooms_counter;
	t_list			*line_list;
	t_ant			*ant;
	t_room			*room;
}					t_str;

#endif