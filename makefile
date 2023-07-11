CC = gcc
CFLAGS = -W -Wall
TARGET = fft.exe
DTARGET = fft_debug.exe
OBJECTS = main.c FFT.o WAVE.o

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(DTARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -DDEBUG -o $@ $^

clean:
	rm *.o *.exe *.csv