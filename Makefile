SRC	=	src/anim.cpp	\
		src/attack.cpp	\
		src/draw.cpp	\
		src/main.cpp	\
		src/move.cpp	\
		src/noise/noise.cpp	\
		src/Window.cpp	\
		src/player.cpp	\
		src/particles/particle.cpp	\
		src/utils/angle_to_vector.cpp	\
		src/light/light_set.cpp	\
		src/light/utils.cpp	\
		src/light/utils_light.cpp	\
		src/light/angle.cpp	\
		src/light/main_light.cpp	\

FLAGS = -Wall -Wextra

INSTALL_DIR = /usr/bin
NAME = -o smash

# OBJ	=	$(SRC:.cpp=.o)
# OBJ=$(subst .cpp,.o,$(SRCS))

all:	$(SRC)
	g++ $(FLAGS) $(NAME) $(SRC) -I ./include/ -lsfml-graphics -lsfml-window -lsfml-system -O3 -g -Wall -Wextra
