# Compiler and flags
CC       = cc
CFLAGS   = -Wall -Wextra -Werror


# Colors for messages
YELLOW = \033[1;33m
GREEN = \033[1;32m
RESET = \033[0m

BOX_TOP    = ╔══════════════════════╗
BOX_MIDDLE = ║                      ║
BOX_BOTTOM = ╚══════════════════════╝

# Directories
SRC_DIR  = srcs
#BONUS_DIR = bonus
OBJ_DIR  = objs
#LIBFT_DIR = libft

# Libraries
#LIBFT    = $(LIBFT_DIR)/libft.a
#LIBS     = -L$(LIBFT_DIR) -lft

# Includes
INCLUDES = -Iinclude
#BONUS_INCLUDES = -Ibonus_include -I$(LIBFT_DIR)

# Source files
SRCS     = $(SRC_DIR)/checks.c \
		   $(SRC_DIR)/philo.c\
		   $(SRC_DIR)/tools.c \
		   $(SRC_DIR)/tools2.c

# Bonus source files
#BONUS_SRCS = $(BONUS_DIR)/

# Objects files
OBJS     = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Bonus object files
#BONUS_OBJS = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output executable
NAME     = philo
#BONUS_NAME = philo_bonus

# Rules
all: $(NAME)

# Make bonus version
#bonus: $(LIBFT) $(BONUS_NAME)

# Compile libft if not already compiled
#$(LIBFT):
#	@echo "$(YELLOW)Compiling my beautiful libft...$(RESET)"
#	@$(MAKE) -C $(LIBFT_DIR) all > /dev/null
#	@echo "$(GREEN)Compilation of libft finished.$(RESET)"

# Create object directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c | $(OBJ_DIR)
#	@$(CC) $(CFLAGS) $(BONUS_INCLUDES) -c $< -o $@

# Link the executable
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(BOX_TOP)"
	@echo "$(GREEN)║ Executable compiled. ║$(RESET)"
	@echo "$(GREEN)$(BOX_BOTTOM)$(RESET)"

#$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
#	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBS) -o $(BONUS_NAME)
#	@echo "$(GREEN)$(BOX_TOP)"
#	@echo "║ Bonus ver. compiled. ║$(RESET)"
#	@echo "$(GREEN)$(BOX_BOTTOM)$(RESET)"

# Clean object files
clean:
	@rm -rf $(OBJ_DIR)
	@echo "Clean done."

# Clean object files and executable
fclean: clean
#	@echo "$(YELLOW)Cleaning libft...$(RESET)"
#	@$(MAKE) -s -C $(LIBFT_DIR) fclean
#	@echo "$(GREEN)libft cleaned.$(RESET)"
	@rm -f $(NAME) $(BONUS_NAME)
	@echo "$(GREEN)$(BOX_TOP)"
	@echo "$(GREEN)║   Full clean done.   ║$(RESET)"
	@echo "$(GREEN)$(BOX_BOTTOM)$(RESET)"

# Rebuild
re: fclean all
#rebonus: fclean bonus
.PHONY: all clean fclean re
