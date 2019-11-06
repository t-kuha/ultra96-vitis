# 
# Create Linux platform for Ultra96
# 

platform create -name u96_emb -hw ultra96.xsa -out _linux -proc psu_cortexa53 -os linux
platform write

# ================================                                                                                 
# NAME             DESCRIPTION
# ================================
# *u96_emb         u96_emb

# Domain - Linux
domain active linux_domain

domain config -bif {src/linux.bif}
domain config -boot {boot}
platform write

platform generate -domains linux_domain
