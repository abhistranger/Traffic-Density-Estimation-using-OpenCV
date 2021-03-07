C=g++
CFLAGS= -g -Wall

TARGET1=task1
TARGET2=task2

RM=rm -rf

LIB=`pkg-config --cflags --libs opencv`

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(TARGET1).cpp 
	@$(C) $(CFLAGS) -o $(TARGET1) $(TARGET1).cpp $(LIB)

$(TARGET2): $(TARGET2).cpp $(TARGET1).h
	@$(C) $(CFLAGS) -o $(TARGET2) $(TARGET2).cpp $(TARGET1).h $(LIB)
	

clean:
	@$(RM) $(TARGET1) $(TARGET2)

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

