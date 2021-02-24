C=g++
CFLAGS= -g -Wall

TARGET=task1

RM=rm -rf

LIB=`pkg-config --cflags --libs opencv`

all: $(TARGET)

$(TARGET): $(TARGET).cpp 
	@$(C) $(CFLAGS) -o $(TARGET) $(TARGET).cpp $(LIB)


clean:
	@$(RM) $(TARGET)

.DEFAULT:
	@echo "Wrong Command"
	@echo "help menu opening:"
	@make help
		
help: 
	@echo "help menu:"
	@echo "make help               Show this help"
	@echo "make clean              Remove all intermediate files"
	@echo "make all                Compile the frogram"
	@echo "./task1 image_name      Run the program but first you have to compile it"

