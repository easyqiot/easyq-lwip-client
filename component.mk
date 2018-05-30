# https://github.com/SuperHouse/esp-open-rtos/wiki/Build-Process#adding-a-new-component
#
INC_DIRS += $(easyq-lwip-client_ROOT)

# args for passing into compile rule generation
easyq-lwip-client_SRC_DIR =  $(easyq-lwip-client_ROOT)
easyq-lwip-client_INC_DIR =  $(easyq-lwip-client_ROOT)
#
$(eval $(call component_compile_rules,easyq-lwip-client))
