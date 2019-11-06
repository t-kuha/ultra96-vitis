# ultra96-vitis

## Contents of this repo

- Embedded: Linux & standalone application platform creation

***

## Environment setup

- OS: Ubuntu 18.04

- Install Vitis

- Get necessary board files from [Xilinx GitHub](https://github.com/Xilinx/XilinxBoardStore.git)

- Install OpenCL ICD

```shell-session
$ sudo apt install ocl-icd-libopencl1 opencl-headers ocl-icd-opencl-dev
```

- Install XRT (Xilinx Runtime)
  - Get Linux package from [Xilinx website](https://www.xilinx.com/products/boards-and-kits/alveo/u200.html#gettingStarted)

```shell-session
$ sudo apt install ./xrt_201920.2.3.1301_18.04-xrt.deb
```
