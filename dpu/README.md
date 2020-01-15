# DPU implementation in Vitis

- Clone Vitis AI repo:

```shell-session
$ git clone https://github.com/Xilinx/Vitis-AI.git
```

- Copy config files

```shell-session
$ cp prj_config  Vitis-AI/DPU-TRD/prj/Vitis/config_file/
$ cp dpu_conf.vh Vitis-AI/DPU-TRD/prj/Vitis/
```

- Edit _Vitis-AI/DPU-TRD/prj/Vitis/Makefile_: Add ``--jobs $(shell nproc)`` to ``XOCC_OPTS = ...`` to speedup synthesis.

- Build

```shell-session
$ export SDX_PLATFORM=<path to u96_accel.xpfm>

$ cd Vitis-AI/DPU-TRD/prj/Vitis/
$ make KERNEL=DPU DEVICE=u96
# or...
$ make KERNEL=DPU_SM DEVICE=u96
```
