CC = gcc
CFLAGS = -W -Wall

TARGET = fft.exe
DTARGET = fft_debug.exe
OBJECTS = main.c FFT.o WAVE.o

TEST_WAVE_TARGET = test_wave.exe
TEST_FFT_TARGET = test_fft.exe
TEST_OBJECTS = test.c WAVE.o FFT.o

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(DTARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -DDEBUG -o $@ $^

$(TEST_WAVE_TARGET) : $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -DTEST_WAVE -o $@ $^

$(TEST_FFT_TARGET) : $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -DTEST_FFT -o $@ $^

clean:
	rm *.o *.exe *.csv