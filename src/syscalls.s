	      .public sys_int_enable_all
	      .public sys_int_disable_all
	      .public sys_int_disable
	      .public sys_int_enable
	      .public sys_int_register
	      .public sys_int_pending
	      .public sys_get_info
	      .public sys_int_clear
	      .public sys_chan_read_b
	      .public sys_chan_read
	      .public sys_chan_readline
	      .public sys_chan_write_b
	      .public sys_chan_write
	      .public sys_chan_status
	      .public sys_chan_flush
	      .public sys_chan_seek
	      .public sys_chan_ioctrl
	      .public sys_chan_open
	      .public sys_chan_close
	      .public sys_chan_swap
	      .public sys_chan_device
	      .public sys_bdev_register
	      .public sys_bdev_read
	      .public sys_bdev_write
	      .public sys_bdev_status
	      .public sys_bdev_flush
	      .public sys_bdev_ioctrl
	      .public sys_mem_get_ramtop
	      .public sys_mem_reserve
	      .public sys_time_jiffies
	      .public sys_rtc_set_time
	      .public sys_rtc_get_time
	      .public sys_kbd_scancode
	      .public sys_err_message
	      .public sys_kbd_layout
	      .public sys_var_set
	      .public sys_var_get
	      .public sys_txt_get_capabilities
	      .public sys_txt_set_mode
	      .public sys_txt_setsizes
	      .public sys_txt_set_xy
	      .public sys_txt_get_xy
	      .public sys_txt_get_region
	      .public sys_txt_set_region
	      .public sys_txt_set_color
	      .public sys_txt_get_color
	      .public sys_txt_set_cursor_visible
	      .public sys_txt_set_font
	      .public sys_txt_get_sizes
	      .public sys_txt_set_border
	      .public sys_txt_set_border_color
	      .public sys_txt_put
	      .public sys_txt_print

sys_int_enable_all:   .equlab 0xf000
sys_int_disable_all:  .equlab 0xf004
sys_int_disable:      .equlab 0xf008
sys_int_enable:       .equlab 0xf00c
sys_int_register:     .equlab 0xf010
sys_int_pending:      .equlab 0xf014
sys_get_info:         .equlab 0xf018
sys_int_clear:        .equlab 0xf01c
sys_chan_read_b:      .equlab 0xf020
sys_chan_read:        .equlab 0xf024
sys_chan_readline:    .equlab 0x2c28
sys_chan_write_b:     .equlab 0xf02c
sys_chan_write:       .equlab 0xf030
sys_chan_status:      .equlab 0xf034
sys_chan_flush:       .equlab 0xf038
sys_chan_seek:        .equlab 0xf04c
sys_chan_ioctrl:      .equlab 0xf044
sys_chan_open:        .equlab 0xf048
sys_chan_close:       .equlab 0xf04c
sys_chan_swap:        .equlab 0xf050
sys_chan_device:      .equlab 0xf054
sys_bdev_register:    .equlab 0xf058
sys_bdev_read:        .equlab 0xf05c
sys_bdev_write:       .equlab 0xf060
sys_bdev_status:      .equlab 0xf064
sys_bdev_flush:       .equlab 0xf068
sys_bdev_ioctrl:      .equlab 0xf06c
sys_mem_get_ramtop:   .equlab 0xf070
sys_mem_reserve:      .equlab 0xf074
sys_time_jiffies:     .equlab 0xf078
sys_rtc_set_time:     .equlab 0xf07c
sys_rtc_get_time:     .equlab 0xf080
sys_kbd_scancode:     .equlab 0xf084
sys_err_message:      .equlab 0xf088
sys_kbd_layout:       .equlab 0xf08c
sys_var_set:          .equlab 0xf090
sys_var_get:          .equlab 0xf094
sys_txt_get_capabilities: .equlab 0xf098
sys_txt_set_mode:     .equlab 0xf09c
sys_txt_setsizes:     .equlab 0xf0a0
sys_txt_set_xy:       .equlab 0xf0a4
sys_txt_get_xy:       .equlab 0xf0a8
sys_txt_get_region:   .equlab 0xf0ac
sys_txt_set_region:   .equlab 0xf0b0
sys_txt_set_color:    .equlab 0xf0b4
sys_txt_get_color:    .equlab 0xf0b8
sys_txt_set_cursor_visible: .equlab 0xf0bc
sys_txt_set_font:     .equlab 0xf0c0
sys_txt_get_sizes:    .equlab 0xf0c4
sys_txt_set_border:   .equlab 0xf0c8
sys_txt_set_border_color: .equlab 0xf0cc
sys_txt_put:          .equlab 0xf0d0
sys_txt_print:        .equlab 0xf0d4
