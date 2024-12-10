CC        		:= gcc
CFLAGS    		:=  -flto-compression-level=19 -march=native  \
					-O3 -Os -s -ffunction-sections -Wl,--gc-sections \
					-fno-asynchronous-unwind-tables -Wl,--strip-all \
					-D_ExceptionHandler_WIN_
CFLAGS_DEBUG 	:=  -D_ExceptionHandler_WIN_ -O3 -D DEBUG_ENABLE
OBJDIR    		:=  file_objects
OBJSTRIP  		:=  --localize-hidden --strip-unneeded 
EXE       		:=  exe
D         		:=  -D DEBUG_ENABLE
FLAG_WIN7 		:=  -D __DISABLE_COLORS_FORE_BACK_GROUND__

# usar la flag __DISABLE_COLORS_FORE_BACK_GROUND__ para compilar en win 7 o plataformas donde alguna secuencia ANSI
# de foreground y background de problemas
# objcopy $(OBJSTRIP) opcodes_prefix.o

.PHONY: all

code.$(EXE): code.c disassembly.c
	@cls
	$(CC) code.c -fvisibility-inlines-hidden -fvisibility=hidden $(CFLAGS) -o $@
	$(CC) -ggdb disassembly.c -fvisibility-inlines-hidden -fvisibility=hidden $(CFLAGS) -o disassembly.$(EXE)
	
compile_debug: code.c disassembly.c
	@cls
	$(CC) code.c $(CFLAGS_DEBUG) -o code.$(EXE)
	$(CC) -ggdb disassembly.c $(CFLAGS_DEBUG) -o disassembly.$(EXE)

compile_hidden: code.c
	@cls
	$(CC) -Wl,--strip-all $^ $(CFLAGS) -o code.$(EXE)

all_dc: code.c
	@cls
	$(CC) $^ $(FLAG_WIN7) $(CFLAGS) -o code.$(EXE)

compile_debug_dc: code.c
	@cls
	$(CC) $^ $(FLAG_WIN7) $(D) $(CFLAGS) -o code.$(EXE)

clean:
	del code.$(EXE)

.PHONY: clean
