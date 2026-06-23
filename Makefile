# Компилятор и флаги
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -O2
LDFLAGS  = -lm

# Имя исполняемого файла
TARGET = numer_diff

# Директории
SRCDIR   = src
BUILDDIR = build

# Автоматически находим все .cpp в src/
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

# Цель по умолчанию
all: $(TARGET)

# Линковка исполняемого файла
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Компиляция каждого .cpp в .o
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Создание папки build, если её нет
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Запуск программы (после сборки)
run: $(TARGET)
	./$(TARGET)

# Очистка временных файлов и исполняемого
clean:
	rm -rf $(BUILDDIR) $(TARGET)

# Объявляем, что clean и run не являются файлами
.PHONY: all clean run