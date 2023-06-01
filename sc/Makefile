SRC=/home/jack/projects/hdl/sc
BUILD=/mnt/d/studys/xilinx/build

all:
	mkdir -p $(BUILD) && cd $(BUILD) && cmake $(SRC) && make && cd -
	$(BUILD)/main_sctool
	cp davinci_pro.xdc $(BUILD)
vcs:
	$(vcs) -debug_access+all -kdb -lca +lint=PCWM tb.sv $(BUILD)/sv_out/main.sv
clean:
	rm -rf $(BUILD)
	rm -rf csrc  inter.fsdb*  novas.conf  novas.rc  novas_dump.log  simv  simv.daidir    ucli.key  verdiLog tb.fsdb* top.json top.svg vc_hdrs.h
