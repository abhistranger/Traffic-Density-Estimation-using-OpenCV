C=g++
CFLAGS= -g -Wall

TARGET=task1

RM=rm -rf

LIB=`pkg-config --cflags --libs opencv`

all: $(TARGET)

$(TARGET): $(TARGET).cpp 
	$(C) $(CFLAGS) -o $(TARGET) $(TARGET).cpp $(LIB)

clean: 
	$(RM) *o $(TARGET)
