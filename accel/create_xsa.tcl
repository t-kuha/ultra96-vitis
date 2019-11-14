# Setting
set PRJ_DIR     _vivado
set PRJ_NAME    ultra96
set BD_NAME     ${PRJ_NAME}
set SRC_DIR     src
set NUM_JOBS    4


# Create project
create_project ${PRJ_NAME} ${PRJ_DIR} -part xczu3eg-sbva484-1-e
set_property board_part em.avnet.com:ultra96:part0:1.2 [current_project]

# Create block design
source $SRC_DIR/bd.tcl

# Generate block design
regenerate_bd_layout
save_bd_design
generate_target all [get_files  ${PRJ_DIR}/${PRJ_NAME}.srcs/sources_1/bd/${BD_NAME}/${BD_NAME}.bd]
set_property generate_synth_checkpoint true [get_files -norecurse *.bd]

export_ip_user_files -of_objects [get_files ${PRJ_DIR}/${PRJ_NAME}.srcs/sources_1/bd/${BD_NAME}/${BD_NAME}.bd] -no_script -sync -force -quiet

# Set top-level source
make_wrapper -files [get_files ${PRJ_DIR}/${PRJ_NAME}.srcs/sources_1/bd/${BD_NAME}/${BD_NAME}.bd] -top
add_files -norecurse ${PRJ_DIR}/${PRJ_NAME}.srcs/sources_1/bd/${BD_NAME}/hdl/${BD_NAME}_wrapper.v
set_property top ${BD_NAME}_wrapper [current_fileset]

update_compile_order -fileset sources_1
update_compile_order -fileset sim_1

# Set the project design intent 
set_property platform.design_intent.embedded "true" [current_project]
set_property platform.design_intent.server_managed "false" [current_project]
set_property platform.design_intent.external_host "false" [current_project]
set_property platform.design_intent.datacenter "false" [current_project]
set_property platform.default_output_type "sd_card" [current_project]

# set_property platform.post_sys_link_tcl_hook dynamic_postlink.tcl [current_project]

# Generate bitstream
launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1

# Create .xsa (with bitstream included)
# "-fixed" option must not be added
write_hw_platform -include_bit -force -file ${PRJ_NAME}.xsa
validate_hw_platform ${PRJ_NAME}.xsa

# Finish - close project
close_project
