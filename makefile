# Compilateur
CC = gcc

# Options de compilation : warnings + norme ANSI + debug
CFLAGS = -Wall -ansi -g

# Librairie graphique MLV
LDFLAGS = -lMLV

# Dossier de sortie des objets
ODIR = out

# Liste des fichiers objets
OBJ = $(ODIR)/main.o \
      $(ODIR)/graphique.o \
	  $(ODIR)/plateau.o \
        

# Cible par défaut
all: taquin

# Création de l’exécutable final
taquin: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o taquin

# Compilation générique des .c vers out/.o
$(ODIR)/%.o: %.c
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Supprimer objets et exécutable
clean:
	rm -rf $(ODIR) taquin
