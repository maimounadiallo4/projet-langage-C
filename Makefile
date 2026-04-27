# /**
#  * @file Makefile
#  * @brief Règles de compilation pour le projet analyseur
#  *
#  * @author Ousmane
#  */

# Compilateur C à utiliser
CC      = gcc

# Options de compilation :
# -Wall : active la plupart des avertissements du compilateur
# -Wextra : active des avertissements supplémentaires pour plus de sécurité
CFLAGS  = -Wall -Wextra

# Nom de l'exécutable final de l'analyseur
TARGET  = analyseur

# Liste des fichiers sources (les différents modules du projet)
SRCS    = main.c lexique.c analyse_haute.c analyse_basse.c erreur.c

# Liste des fichiers objets générés à partir des sources (.c -> .o)
OBJS    = $(SRCS:.c=.o)

# Cibles factices (qui ne correspondent pas à des fichiers réels sur le disque)
.PHONY: all clean test

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
	-del /Q /F $(OBJS) $(TARGET).exe 2>nul || rm -f $(OBJS) $(TARGET).exe 2>nul
else
	rm -f $(OBJS) $(TARGET)
endif

# Cible pour compiler le testeur universel
tests/tester: tests/tester.c
	$(CC) $(CFLAGS) tests/tester.c -o tests/tester

# Lance les tests automatisés (Uniforme Linux/Windows)
test: all tests/tester
ifeq ($(OS),Windows_NT)
	@tests\tester.exe
else
	@chmod +x tests/tester
	@./tests/tester
endif