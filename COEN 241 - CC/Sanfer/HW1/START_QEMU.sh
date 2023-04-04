#!/bin/bash
qemu-system-aarch64 \
-accel hvf -cpu cortex-a57 -M virt,highmem=off -m 6G \
-smp 6 \
-drive file=/opt/homebrew/Cellar/qemu/6.2.0_1/share/qemu/edk2-aarch64-code.fd,if=pflash,format=raw,readonly=on \
-drive if=none,file=ubuntu.img,format=qcow2,id=hd0 \
-device virtio-blk-device,drive=hd0,serial="trial_2" \
-device virtio-net-device,netdev=net0 \
-netdev user,id=net0 \
-vga none -device ramfb \
-device usb-ehci -device usb-kbd -device usb-mouse -usb -nographic