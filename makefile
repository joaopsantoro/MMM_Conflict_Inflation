# Model compilation options
TARGET=lsd
FUN=fun_micro_macro_v.2.1
FUN_EXTRA=fun_time_step.h fun_init.h fun_functions.h fun_macro.h fun_macro_sfc.h fun_classes.h fun_external_sector.h fun_government.h fun_sector_external.h fun_sector_aggregates.h fun_sector_demand.h fun_entry_exit.h fun_firm_capital.h fun_firm_finance.h fun_firm_investment.h fun_firm_price.h fun_firm_production.h fun_firm_profit.h fun_firm_rnd.h fun_firm_sales.h fun_inputs.h fun_capital_goods.h   fun_sector_analysis.h fun_sector_behavior.h
SWITCH_CC=-O0 -ggdb3
SWITCH_CC_LNK=

# System compilation options
LSDROOT=C:/Lsd
SRC=src
EXT=.exe

# Libraries options
TCL_VERSION=86
PATH_TCL_HEADER=$(LSDROOT)/gnu64/include
PATH_TK_HEADER=$(LSDROOT)/gnu64/include
PATH_HEADER=$(LSDROOT)/gnu64/include
PATH_TCL_LIB=$(LSDROOT)/gnu64/lib
PATH_TK_LIB=$(LSDROOT)/gnu64/lib
PATH_LIB=$(LSDROOT)/gnu64/lib
TCL_LIB=-ltcl$(TCL_VERSION)
TK_LIB=-ltk$(TCL_VERSION)
LIBS=-lz

# Compiler options
CC=x86_64-w64-mingw32-g++
GLOBAL_CC=-march=native -std=gnu++14 -w
SSWITCH_CC=-mthreads -mwindows -O3
LSDROOT=C:/Lsd

# Body of makefile (from src/makefile_base.txt)
# Specify where are the sources of the system. Do not modify unless using a different
# directory structure (why should you?).
SRC_DIR=$(LSDROOT)/$(SRC)/

# Variable used to prepare the options to search for the tcl and tk headers
# Do not modify
INCLUDE=-I$(PATH_TCL_HEADER) -I$(PATH_TK_HEADER) -I$(PATH_HEADER) -I$(LSDROOT)/$(SRC)

$(TARGET)$(EXT): $(FUN).o $(SRC_DIR)main_gnuwin.o $(SRC_DIR)file.o $(SRC_DIR)util.o $(SRC_DIR)object.o \
$(SRC_DIR)variab.o $(SRC_DIR)interf.o $(SRC_DIR)draw.o $(SRC_DIR)runtime.o $(SRC_DIR)debug.o $(SRC_DIR)edit.o \
$(SRC_DIR)edit_dat.o $(SRC_DIR)set_all.o $(SRC_DIR)analysis.o $(SRC_DIR)show_eq.o $(SRC_DIR)lsdmain.o \
$(SRC_DIR)report.o $(SRC_DIR)nets.o
	$(CC) $(GLOBAL_CC) $(SWITCH_CC) $(FUN).o $(SRC_DIR)file.o $(SRC_DIR)main_gnuwin.o $(SRC_DIR)util.o \
	$(SRC_DIR)draw.o $(SRC_DIR)object.o $(SRC_DIR)set_all.o $(SRC_DIR)variab.o $(SRC_DIR)interf.o \
	$(SRC_DIR)show_eq.o $(SRC_DIR)runtime.o $(SRC_DIR)debug.o $(SRC_DIR)edit.o $(SRC_DIR)edit_dat.o \
	$(SRC_DIR)analysis.o $(SRC_DIR)lsdmain.o $(SRC_DIR)report.o $(SRC_DIR)nets.o \
	$(SWITCH_CC_LNK) -L$(PATH_TCL_LIB) $(TCL_LIB) -L$(PATH_TK_LIB) $(TK_LIB) -L$(PATH_LIB) $(LIBS) \
	-o $(TARGET)

$(SRC_DIR)file.o: $(SRC_DIR)choose.h $(SRC_DIR)system_options.txt $(SRC_DIR)file.cpp $(SRC_DIR)decl.h
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) -c $(SRC_DIR)file.cpp -o $(SRC_DIR)file.o $(INCLUDE)

$(SRC_DIR)interf.o: $(SRC_DIR)choose.h $(SRC_DIR)system_options.txt $(SRC_DIR)interf.cpp $(SRC_DIR)decl.h
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) -c $(SRC_DIR)interf.cpp  -o $(SRC_DIR)interf.o $(INCLUDE)

$(SRC_DIR)main_gnuwin.o: $(SRC_DIR)choose.h $(SRC_DIR)system_options.txt $(SRC_DIR)main_gnuwin.cpp $(SRC_DIR)decl.h
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) -c $(SRC_DIR)main_gnuwin.cpp -o $(SRC_DIR)main_gnuwin.o $(INCLUDE)

$(SRC_DIR)util.o: $(SRC_DIR)choose.h $(SRC_DIR)system_options.txt $(SRC_DIR)util.cpp $(SRC_DIR)decl.h
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) -c $(SRC_DIR)util.cpp -o $(SRC_DIR)util.o $(INCLUDE)

$(SRC_DIR)variab.o: $(SRC_DIR)choose.h $(SRC_DIR)system_options.txt $(SRC_DIR)variab.cpp $(SRC_DIR)decl.h
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) -c $(SRC_DIR)variab.cpp -o $(SRC_DIR)variab.o $(INCLUDE)

$(SRC_DIR)object.o: $(SRC_DIR)choose.h $(SRC_DIR)system_options.txt $(SRC_DIR)object.cpp $(SRC_DIR)decl.h
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) -c $(SRC_DIR)object.cpp -o $(SRC_DIR)object.o $(INCLUDE)

$(SRC_DIR)debug.o: $(SRC_DIR)choose.h $(SRC_DIR)system_options.txt $(SRC_DIR)debug.cpp $(SRC_DIR)decl.h
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) -c $(SRC_DIR)debug.cpp -o $(SRC_DIR)debug.o $(INCLUDE)

$(SRC_DIR)edit.o: $(SRC_DIR)choose.h $(SRC_DIR)system_options.txt $(SRC_DIR)edit.cpp $(SRC_DIR)decl.h
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) -c $(SRC_DIR)edit.cpp -o $(SRC_DIR)edit.o $(INCLUDE)

$(SRC_DIR)edit_dat.o: $(SRC_DIR)choose.h $(SRC_DIR)system_options.txt  $(SRC_DIR)edit_dat.cpp $(SRC_DIR)decl.h
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) -c $(SRC_DIR)edit_dat.cpp -o $(SRC_DIR)edit_dat.o $(INCLUDE)

$(SRC_DIR)set_all.o: $(SRC_DIR)choose.h $(SRC_DIR)system_options.txt $(SRC_DIR)set_all.cpp $(SRC_DIR)decl.h $(SRC_DIR)nolh.h
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) -c $(SRC_DIR)set_all.cpp -o $(SRC_DIR)set_all.o $(INCLUDE)

$(SRC_DIR)draw.o: $(SRC_DIR)choose.h $(SRC_DIR)system_options.txt $(SRC_DIR)draw.cpp $(SRC_DIR)decl.h
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) -c $(SRC_DIR)draw.cpp -o $(SRC_DIR)draw.o $(INCLUDE)

$(SRC_DIR)analysis.o: $(SRC_DIR)choose.h $(SRC_DIR)system_options.txt $(SRC_DIR)analysis.cpp $(SRC_DIR)decl.h
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) -c $(SRC_DIR)analysis.cpp -o $(SRC_DIR)analysis.o $(INCLUDE)

$(SRC_DIR)show_eq.o: $(SRC_DIR)choose.h $(SRC_DIR)system_options.txt $(SRC_DIR)show_eq.cpp $(SRC_DIR)decl.h
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) -c $(SRC_DIR)show_eq.cpp -o $(SRC_DIR)show_eq.o $(INCLUDE)

$(SRC_DIR)runtime.o: $(SRC_DIR)choose.h $(SRC_DIR)system_options.txt $(SRC_DIR)runtime.cpp $(SRC_DIR)decl.h
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) -c $(SRC_DIR)runtime.cpp -o $(SRC_DIR)runtime.o $(INCLUDE)

$(SRC_DIR)lsdmain.o: $(SRC_DIR)choose.h $(SRC_DIR)system_options.txt $(SRC_DIR)lsdmain.cpp $(SRC_DIR)decl.h
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) -c $(SRC_DIR)lsdmain.cpp -o $(SRC_DIR)lsdmain.o $(INCLUDE)

$(SRC_DIR)report.o: $(SRC_DIR)choose.h $(SRC_DIR)system_options.txt $(SRC_DIR)report.cpp $(SRC_DIR)decl.h
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) -c $(SRC_DIR)report.cpp -o $(SRC_DIR)report.o $(INCLUDE)

$(SRC_DIR)nets.o: $(SRC_DIR)choose.h $(SRC_DIR)system_options.txt $(SRC_DIR)nets.cpp $(SRC_DIR)decl.h
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) -c $(SRC_DIR)nets.cpp -o $(SRC_DIR)nets.o $(INCLUDE)

$(FUN).o: $(FUN).cpp $(FUN_EXTRA) model_options.txt $(SRC_DIR)choose.h $(SRC_DIR)decl.h $(SRC_DIR)check.h $(SRC_DIR)fun_head.h $(SRC_DIR)fun_head_fast.h
	$(CC) $(GLOBAL_CC) $(SWITCH_CC) -c $(FUN).cpp $(INCLUDE)
	
clean:
	rm $(SRC_DIR)*.o $(FUN).o $(TARGET)*