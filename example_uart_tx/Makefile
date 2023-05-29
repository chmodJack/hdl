all:
	$(vcs) -debug_access+all -kdb -lca +lint=PCWM tb.sv ./uart_tx.v
clean:
	rm -rf csrc  inter.fsdb*  novas.conf  novas.rc  novas_dump.log  simv  simv.daidir    ucli.key  verdiLog tb.fsdb* top.json top.svg vc_hdrs.h

FLATTEN=-flatten
#AIGMAP=aigmap

test:
	yosys -p "prep $(FLATTEN); $(AIGMAP); write_json top.json" ./src/counter.v
	netlistsvg top.json -o top.svg
