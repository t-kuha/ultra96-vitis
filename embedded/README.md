# Embeddesd platform

- Vitis embedded platform

***

## Old Xilinx SDK-like flow

### Create hardware

```shell-session
$ vivado -mode batch -source create_vivado_project.tcl 
```

### Create (standalone) application

```shell-session
$ xsct create_app.tcl
$ sdcard_gen \
--xpfm _application/ultra96/export/ultra96/ultra96.xpfm \
--sys_config ultra96 \
--elf _application/hello_world/Release/hello_world.elf
```

### Run

- Copy the contens of __sd\_card__ directory to SD card

