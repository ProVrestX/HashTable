# Данные

# 1
callgrind.out.1 -- time = ~23.8s (2048 элементов)

больше всего времени -- sscanf -> strlen

решение -- замена sscanf на StrCpy

# 2 

callgrind.out.2 -- time = ~0.64s (2048 эл)

больше всего времени -- FillTableFromFile -> fscanf

решение -- уменьшение до 8 эл.

# 3

callgrind.out.3 -- time = ~4.8s (8 эл)

больше всего времени -- ListSearch

решение -- замена void* data на __m256i

# 4

callgrind.out.4 -- time = ~3.37s (8 эл)

больше всего времени -- ListSearch

решение -- увеличение до 2048 эл.

# 5

callgrind.out.5 -- time = ~1.1s (2048 эл)

больше всего времени -- FillTableFromFile/Str -> CreateList -> GetHash -> calloc

решение -- переписать GetHash на asm

# 6

callgrind.out.6 -- time = ~0.88s (2048 эл)

больше всего времени -- main -> fprintf

решение -- создание временного буффера

# 7

callgrind.out.7 -- time = ~0.2s (2048 эл)

больше всего времени -- ListSearch

решение -- нет, в рамках учебной программы данной оптимизации достаточно.