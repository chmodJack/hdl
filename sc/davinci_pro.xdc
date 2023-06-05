#-------------------------------------------------------------------------------
create_clock -name clk -period 20                       [get_ports clk]
set_property -dict {PACKAGE_PIN R4 IOSTANDARD LVCMOS15} [get_ports clk]
set_property CLOCK_DEDICATED_ROUTE FALSE                [get_nets clk]
set_property -dict {PACKAGE_PIN U7 IOSTANDARD LVCMOS15} [get_ports rst]

#-------------------------------------------------------------------------------
set_property CFGBVS VCCO                        [current_design]
set_property CONFIG_VOLTAGE 3.3                 [current_design]
set_property CONFIG_MODE SPIx4                  [current_design]
set_property BITSTREAM.GENERAL.COMPRESS TRUE    [current_design]
set_property BITSTREAM.CONFIG.CONFIGRATE 50     [current_design]
set_property BITSTREAM.CONFIG.SPI_BUSWIDTH 4    [current_design]
set_property BITSTREAM.CONFIG.SPI_FALL_EDGE YES [current_design]
set_property BITSTREAM.CONFIG.UNUSEDPIN PULLUP  [current_design]

#-------------------------------------------------------------------------------
set_property -dict {PACKAGE_PIN T4 IOSTANDARD LVCMOS15} [get_ports {key[0]}]
set_property -dict {PACKAGE_PIN T3 IOSTANDARD LVCMOS15} [get_ports {key[1]}]
set_property -dict {PACKAGE_PIN R6 IOSTANDARD LVCMOS15} [get_ports {key[2]}]
set_property -dict {PACKAGE_PIN T6 IOSTANDARD LVCMOS15} [get_ports {key[3]}]

#-------------------------------------------------------------------------------
set_property -dict {PACKAGE_PIN V9 IOSTANDARD LVCMOS15} [get_ports {led[0]}]
set_property -dict {PACKAGE_PIN Y8 IOSTANDARD LVCMOS15} [get_ports {led[1]}]
set_property -dict {PACKAGE_PIN Y7 IOSTANDARD LVCMOS15} [get_ports {led[2]}]
set_property -dict {PACKAGE_PIN W7 IOSTANDARD LVCMOS15} [get_ports {led[3]}]

#-------------------------------------------------------------------------------
set_property -dict {PACKAGE_PIN V8 IOSTANDARD LVCMOS15} [get_ports touch]

#-------------------------------------------------------------------------------
set_property -dict {PACKAGE_PIN V7 IOSTANDARD LVCMOS15} [get_ports beep]

#-------------------------------------------------------------------------------
set_property -dict {PACKAGE_PIN E14 IOSTANDARD LVCMOS33} [get_ports uart_rxd]
set_property -dict {PACKAGE_PIN D17 IOSTANDARD LVCMOS33} [get_ports uart_txd]
