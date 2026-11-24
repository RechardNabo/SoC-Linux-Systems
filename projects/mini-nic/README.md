# Flagship: Mini-NIC

Integrated host<->device project. Host (Pi 5 / Ubuntu VM) kernel driver talks command mailbox over USB bulk / SPI to PIC32MX795 (or STM32H563) firmware; data plane = own Ethernet MAC DMA rings + DP83848 PHY; BPI-M5 = traffic peer.

- spec/    - M1: register/command layout, queue formats, error model
- host/    - M3: Linux kernel driver + Python CLI
- device/  - M2/M4/M5: firmware skeleton, data plane, signed update + POST

Command set (draft): QUERY_FW_VERSION, QUERY_CAPS, INIT, SET_LINK, GET_COUNTERS, CREATE_QUEUE, DESTROY_QUEUE, ENABLE_LOOPBACK, SELF_TEST, FW_UPDATE.

