C=g++
CFLAGS= -g -Wall

TARGET1=task1
TARGET2=task2
TARGET3=task3

RM=rm -rf

LIB=`pkg-config --cflags --libs opencv`

all: $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET1): $(TARGET1).cpp 
	@$(C) $(CFLAGS) -o $(TARGET1) $(TARGET1).cpp $(LIB)

$(TARGET2): $(TARGET2).cpp $(TARGET1).h
	@$(C) $(CFLAGS) -o $(TARGET2) $(TARGET2).cpp $(TARGET1).h $(LIB)
	
$(TARGET3): $(TARGET3).cpp $(TARGET1).h
	@$(C) $(CFLAGS) -pthread -std=c++11 -o $(TARGET3) $(TARGET3).cpp $(TARGET1).h $(LIB)
	

clean:
	@$(RM) $(TARGET1) $(TARGET2) $(TARGET3)

.DEFAULT:
	@echo "Wrong Command"
	@echo "help menu opening:"
	@make help
		
help: 
	@echo "help menu:"
	@echo "make help               Show this help"
	@echo "make clean              Remove all intermediate files"
	@echo "make all                Compile the frogram"
	@echo "make task1              Compile task1"
	@echo "make task2              Compile task2"
	@echo "make task3              Compile task3"
	@echo "./task1 image_name      Run task1 program but first compile it, if you haven't"
	@echo "./task2 video_name      Run task2 program but first compile it, if you haven't"
	@echo "./task3 method_name video_name  Run task3 program but first compile it, if you haven't, for example:./task3 method1"

