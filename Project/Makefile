SRC_DIR := Algorithm
GUI_DIR := Gui
BUILD_DIR := Exe
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
SOURCE:= $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%)

CFLAGS := -Wall -g -w
CGUIFLAGS := `pkg-config --cflags --libs gtk+-3.0`

all:gui $(SOURCE)  menu
	chmod 755 $(SOURCE) menu

menu: menu.c
	gcc $(CFLAGS) menu.c -o menu

gui: $(GUI_DIR)/gui_functions.c
	gcc $(CGUIFLAGS) -c $(GUI_DIR)/gui_functions.c -o $(GUI_DIR)/gui_functions.o

$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	gcc $(CGUIFLAGS) $(CFLAGS) $< $(GUI_DIR)/gui_functions.o -o $@
	
clean:
	rm -f Exe/*    #Remove all executables files of Algorithms
	rm -f menu     #Remove the executable file of menu
	rm -f List.txt #Remove the text file List 
	rm -f Gui/gui_functions.o
	
