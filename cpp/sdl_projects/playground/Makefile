IDIR = ../sdl/include/SDL2/
CC = g++
CFLAGS = -I$(IDIR)

SDIR = src
ODIR = build

TARGET = $(ODIR)/project

LIBS = -lmingw32 -lSDL2main -lSDL2

#_DEPS = hellomake.h
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = 01_hello_SDL.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.cpp #$(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

run: $(TARGET)
	$(TARGET)

clean:
	del $(ODIR)\*.o $(ODIR)\*.exe
