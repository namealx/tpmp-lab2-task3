# Makefile для проекта tpmp-lab2-task3
# Автор: Юранов Никита, группа 12

# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS =

# Директории
SRCDIR = src
INCDIR = include
BINDIR = bin
OBJDIR = obj

# Исходные файлы
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/airplane.c
OBJECTS = $(OBJDIR)/main.o $(OBJDIR)/airplane.o
TARGET = $(BINDIR)/airplane_program

# Цель по умолчанию (выполняется при вызове make без параметров)
all: $(TARGET)

# Создание директорий bin и obj
$(BINDIR) $(OBJDIR):
	mkdir -p $@

# Компоновка - создание исполняемого файла из объектных
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Сборка завершена. Исполняемый файл: $(TARGET)"

# Компиляция main.c
$(OBJDIR)/main.o: $(SRCDIR)/main.c $(INCDIR)/airplane.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция airplane.c
$(OBJDIR)/airplane.o: $(SRCDIR)/airplane.c $(INCDIR)/airplane.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка проекта (удаление объектных и исполняемых файлов)
clean:
	rm -rf $(OBJDIR) $(BINDIR)
	@echo "Проект очищен"

# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Проверка для GitHub Actions
check: all
	@echo "Проверка пройдена"

# Дистрибутивная проверка
distcheck: all
	@echo "Дистрибутивная проверка пройдена"

# Объявление целей, которые не являются файлами
.PHONY: all clean run check distcheck
