NAME = table
CFLAGS = -I./Include -mavx2
ASFLAGS = -f elf64

# Получаем списки исходников отдельно для C++ и ассемблера
CPP_SOURCES = $(wildcard Src/*.cpp)
ASM_SOURCES = $(wildcard Src/*.asm)

# Формируем список объектных файлов
CPP_OBJS = $(patsubst Src/%.cpp,.Src_o/%.o,$(CPP_SOURCES))
ASM_OBJS = $(patsubst Src/%.asm,.Src_o/%.o,$(ASM_SOURCES))
OBJS = $(CPP_OBJS) $(ASM_OBJS)

all: createDir $(NAME)

$(NAME): $(OBJS)
	g++ -no-pie $(OBJS) -o $@ $(CFLAGS)

# Правило для C++ файлов
.Src_o/%.o: Src/%.cpp
	g++ -c $(CFLAGS) $< -o $@

# Правило для ассемблерных файлов
.Src_o/%.o: Src/%.asm
	nasm $(ASFLAGS) $< -o $@

createDir:
	@mkdir -p .Src_o

clean:
	rm -rf .Src_o