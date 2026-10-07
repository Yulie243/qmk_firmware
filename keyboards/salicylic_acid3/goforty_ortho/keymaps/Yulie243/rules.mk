VIA_ENABLE = yes                    # Enable compatibility with VIA-protocol configurators
UNICODE_ENABLE = yes
#CONSOLE_ENABLE = yes
#COMMAND_ENABLE = yes
NKRO_ENABLE = yes

# If you want to change the display of OLED, you need to change here
SRC +=  naginata_v18.c

# MacUnicodeInputとかな/英数を連動させる。使うキーマップのrules.mkでRAW_ENABLE
ifeq ($(strip $(RAW_ENABLE)), yes)
SRC +=  naginata_hid.c
endif
SRC +=  twpair_on_jis.c
SRC +=  nglist.c
SRC +=  nglistarray.c

# 自分用追加_260915
# マウスキー、コンボ、ワンショット、タップダンス、キーオーバーライド

MOUSEKEY_ENABLE = yes
#COMBO_ENABLE = yes
#TAP_DANCE_ENABLE = yes
#KEY_OVERRIDE_ENABLE = yes