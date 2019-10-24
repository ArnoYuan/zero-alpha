CROSS_COMPILE		?= arm-linux-gnueabihf-
CC 					:= $(CROSS_COMPILE)gcc
LD 					:= $(CROSS_COMPILE)ld
OBJCOPY				:= $(CROSS_COMPILE)objcopy
OBJDUMP 			:= $(CROSS_COMPILE)objdump

TARGET 				?= alpha

BUILD_DIR 			?= build

CFLGAS 				:= -Wall -nostdlib -std=gnu11 -mfloat-abi=hard -mcpu=cortex-a7

INCDIRS				:= alpha \
					   driver/include \
					   system/include \
					   platform/imx6ul

SRCDIRS 			:= alpha \
					   alpha/driver \
					   alpha/application \
					   system \
					   driver \
					   driver/bus \
					   driver/chip

INCLUDE 			:= $(patsubst %, -I %, $(INCDIRS))

SFILES 				:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.S))
CFILES 				:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

SOBJS				:= $(patsubst %, $(BUILD_DIR)/%, $(SFILES:.S=.o))
COBJS 				:= $(patsubst %, $(BUILD_DIR)/%, $(CFILES:.c=.o))
OBJS 				:= $(SOBJS) $(COBJS)

OBJS_DIR			:= $(addprefix $(BUILD_DIR)/, $(SRCDIRS))

VPATH 				:= $(SRCDIRS)
.PHONY: clean

all: $(OBJS_DIR) $(TARGET).bin

$(OBJS_DIR):
	mkdir -p $@

$(TARGET).bin : $(OBJS)
	$(LD) -Talpha/imx6ul.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis


$(SOBJS) : $(BUILD_DIR)/%.o : %.S
	$(CC) $(CFLGAS) -c $(INCLUDE) -o $@ $<

$(COBJS) : $(BUILD_DIR)/%.o : %.c
	$(CC) $(CFLGAS) -c $(INCLUDE) -o $@ $<

clean:
	rm -rf $(TARGET).elf $(TARGET).dis $(TARGET).bin $(COBJS) $(SOBJS)
	rm -rf $(OBJS_DIR)
