#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

ifdef CONFIG_AUDIO_BOARD_CUSTOM
COMPONENT_ADD_INCLUDEDIRS += ./my_codec_driver
COMPONENT_SRCDIRS += ./my_codec_driver

COMPONENT_ADD_INCLUDEDIRS += ./morningclock
COMPONENT_SRCDIRS += ./morningclock
endif