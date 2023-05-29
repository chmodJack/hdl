all:
	$(vcs) -f files.f -debug_access+all -kdb -lca +lint=PCWM
	./simv -sv_lib ./dpic/libdpic
clean:
	rm -rf csrc  inter.fsdb*  novas.conf  novas.rc  novas_dump.log  simv  simv.daidir    ucli.key  verdiLog tb.fsdb* top.json top.svg vc_hdrs.h

FLATTEN=-flatten
#FLATTEN=
#AIGMAP=aigmap
AIGMAP=

test:
	yosys -p "prep $(FLATTEN); $(AIGMAP); write_json top.json" ./src/counter.v
	netlistsvg top.json -o top.svg
