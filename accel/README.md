# Application Acceleration Platform

- Vitis Application Acceleration Platform

***

## Create hardware

```shell-session
$ vivado -mode batch -source create_xsa.tcl
```

## Create Linux

- Create PetaLinux project

```shell-session
$ export PRJ=petalinux
$ petalinux-create -t project -n ${PRJ} --template zynqMP
$ petalinux-config -p ${PRJ} --get-hw-description=.
$ petalinux-config -p ${PRJ} -c u-boot
```

- Add following content to _petalinux/project-spec/meta-user/conf/user-rootfsconfig_

```text
CONFIG_xrt
CONFIG_xrt-dev
CONFIG_zocl
CONFIG_opencl-clhpp-dev
CONFIG_opencl-headers-dev
CONFIG_packagegroup-petalinux-opencv
```

- Edit device tree (_petalinux/project-spec/meta-user/recipes-bsp/device-tree/files/system-user.dtsi_)

```text
&amba {
    zyxclmm_drm {
        compatible = "xlnx,zocl";
        status = "okay";
    };
};
```

- Build

```shell-session
$ petalinux-config -p ${PRJ} -c kernel
$ petalinux-config -p ${PRJ} -c rootfs
$ petalinux-build -p ${PRJ}

# Generate SDK
$ petalinux-build -p ${PRJ} --sdk

# Copy the product for platform generation
$ mkdir boot
$ cp ${PRJ}/images/linux/image.ub boot/
$ cp ${PRJ}/images/linux/zynqmp_fsbl.elf boot/
$ cp ${PRJ}/images/linux/pmufw.elf boot/
$ cp ${PRJ}/images/linux/bl31.elf boot/
$ cp ${PRJ}/images/linux/u-boot.elf boot/
```

## Generate platform

```shell-session
$ xsct create_pfm.tcl
```

- Now, the platform is in __\_pfm/u96_accel/export/__

***

## Reference

- UG1393: Vitis Unified Software Platform Documentation - Application Acceleration Development (v2019.2)
