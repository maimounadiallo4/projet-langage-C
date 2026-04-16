CC      = gcc
CFLAGS  = -Wall -Wextra
TARGET  = analyseur
SRCS    = main.c lexique.c analyse_haute.c analyse_basse.c erreur.c
OBJS    = $(SRCS:.c=.o)

.PHONY: all clean

# Lien final : produit ./analyseur depuis les fichiers objets
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compilation incrémentale : chaque .c → son .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Supprime les objets ET le binaire
clean:
ifeq ($(OS),Windows_NT)
	del /Q /F $(OBJS) $(TARGET).exe
else
	rm -f $(OBJS) $(TARGET)
endif
