# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g

# flags de linkeo
LDFLAGS=

# Agrear acá los directorios a incluir en la compilación
INCDIR=../ 

# Agregar acá los archivos .cpp a compilar
SOURCES=test.cpp Driver.cpp ../dcnet.cpp ../red.cpp

# Objetos que serán generados (no tocar)
OBJECTS=$(SOURCES:.cpp=.o)

# Nombre del ejecutable a generar
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

.cpp.o:
	$(CC) -I$(INCDIR) $(CFLAGS) $< -c -o $@
