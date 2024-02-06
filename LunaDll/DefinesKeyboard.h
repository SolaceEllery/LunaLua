#ifndef DefinesKeyboard_hhhh
#define DefinesKeyboard_hhhh

// Uncomment to also include other Windows.h functions. They're already defined though, so idk why you would need to uncomment it.
//#define includeWindowsHFunctions

// **Keyboard constants**
#ifdef includeWindowsHFunctions
#define VK_LBUTTON         1
#define VK_RBUTTON         2
#define VK_CANCEL          3
#define VK_MBUTTON         4
#define VK_XBUTTON1        5
#define VK_XBUTTON2        6
#define VK_RESERVED1       7
#define VK_BACK            8
#define VK_TAB             9
#define VK_RESERVED2       10

#define VK_RESERVED3       11
#define VK_CLEAR           12
#define VK_RETURN          13
#define VK_RESERVED4       14
#define VK_RESERVED5       15
#define VK_SHIFT           16
#define VK_CONTROL         17
#define VK_MENU            18
#define VK_PAUSE           19
#define VK_CAPITAL         20

#define VK_KANA            21
#define VK_HANGUL          22
#define VK_IME_ON          23
#define VK_JUNJA           24
#define VK_FINAL           25
#define VK_HANJA           26
#define VK_ESCAPE          27
#define VK_KANJI           28
#define VK_IME_OFF         29
#define VK_CONVERT         30

#define VK_NONCONVERT      31
#define VK_SPACE           32
#define VK_PRIOR           33
#define VK_NEXT            34
#define VK_END             35
#define VK_HOME            36
#define VK_LEFT            37
#define VK_UP              38
#define VK_RIGHT           39
#define VK_DOWN            40

#define VK_SELECT          41
#define VK_PRINT           42
#define VK_EXECUTE         43
#define VK_SNAPSHOT        44
#define VK_INSERT          45
#define VK_DELETE          46
#define VK_HELP            47
#endif

// Numbers
#define VK_ZERO            48
#define VK_ONE             49
#define VK_TWO             50

#define VK_THREE           51
#define VK_FOUR            52
#define VK_FIVE            53
#define VK_SIX             54
#define VK_SEVEN           55
#define VK_EIGHT           56
#define VK_NINE            57

// Alternative number keyboard constants
#define VK_0               48
#define VK_1               49
#define VK_2               50
#define VK_3               51
#define VK_4               52
#define VK_5               53
#define VK_6               54
#define VK_7               55
#define VK_8               56
#define VK_9               57

#ifdef includeWindowsHFunctions
#define VK_RESERVED6       58
#define VK_RESERVED7       59
#define VK_RESERVED8       60

#define VK_RESERVED9       61
#define VK_RESERVED10      62
#define VK_RESERVED11      63
#define VK_RESERVED12      64
#endif

// Letters
#define VK_A               65
#define VK_B               66
#define VK_C               67
#define VK_D               68
#define VK_E               69
#define VK_F               70

#define VK_G               71
#define VK_H               72
#define VK_I               73
#define VK_J               74
#define VK_K               75
#define VK_L               76
#define VK_M               77
#define VK_N               78
#define VK_O               79
#define VK_P               80

#define VK_Q               81
#define VK_R               82
#define VK_S               83
#define VK_T               84
#define VK_U               85
#define VK_V               86
#define VK_W               87
#define VK_X               88
#define VK_Y               89
#define VK_Z               90

// Everything else
#ifdef includeWindowsHFunctions
#define VK_LWIN            91
#define VK_RWIN            92
#define VK_APPS            93
#define VK_RESERVED13      94
#define VK_SLEEP           95
#define VK_NUMPAD0         96
#define VK_NUMPAD1         97
#define VK_NUMPAD2         98
#define VK_NUMPAD3         99
#define VK_NUMPAD4         100

#define VK_NUMPAD5         101
#define VK_NUMPAD6         102
#define VK_NUMPAD7         103
#define VK_NUMPAD8         104
#define VK_NUMPAD9         105
#define VK_MULTIPLY        106
#define VK_ADD             107
#define VK_SEPARATOR       108
#define VK_SUBTRACT        109
#define VK_DECIMAL         110

#define VK_DIVIDE          111
#define VK_F1              112
#define VK_F2              113
#define VK_F3              114
#define VK_F4              115
#define VK_F5              116
#define VK_F6              117
#define VK_F7              118
#define VK_F8              119
#define VK_F9              120

#define VK_F10             121
#define VK_F11             122
#define VK_F12             123
#define VK_F13             124
#define VK_F14             125
#define VK_F15             126
#define VK_F16             127
#define VK_F17             128
#define VK_F18             129
#define VK_F19             130

#define VK_F20             131
#define VK_F21             132
#define VK_F22             133
#define VK_F23             134
#define VK_F24             135
#define VK_UNASSIGNED      136
#define VK_UNASSIGNED2     137
#define VK_UNASSIGNED3     138
#define VK_UNASSIGNED4     139
#define VK_UNASSIGNED5     140

#define VK_UNASSIGNED6     141
#define VK_UNASSIGNED7     142
#define VK_UNASSIGNED8     143
#define VK_NUMLOCK         144
#define VK_SCROLL          145
#define VK_OEM_RESERVED_1  146
#define VK_OEM_RESERVED_2  147
#define VK_OEM_RESERVED_3  148
#define VK_OEM_RESERVED_4  149
#define VK_OEM_RESERVED_5  150

#define VK_UNASSIGNED9     151
#define VK_UNASSIGNED10    152
#define VK_UNASSIGNED11    153
#define VK_UNASSIGNED12    154
#define VK_UNASSIGNED13    155
#define VK_UNASSIGNED14    156
#define VK_UNASSIGNED15    157
#define VK_UNASSIGNED16    158
#define VK_UNASSIGNED17    159
#define VK_LSHIFT          160

#define VK_RSHIFT             161
#define VK_LCONTROL           162
#define VK_RCONTROL           163
#define VK_LMENU              164
#define VK_RMENU              165
#define VK_BROWSER_BACK       166
#define VK_BROWSER_FORWARD    167
#define VK_BROWSER_REFRESH    168
#define VK_BROWSER_STOP       169
#define VK_BROWSER_SEARCH     170

#define VK_BROWSER_FAVORITES  171
#define VK_BROWSER_HOME       172
#define VK_VOLUME_MUTE        173
#define VK_VOLUME_DOWN        174
#define VK_VOLUME_UP          175
#define VK_MEDIA_NEXT_TRACK   176
#define VK_MEDIA_PREV_TRACK   177
#define VK_MEDIA_STOP         178
#define VK_MEDIA_PLAY_PAUSE   179
#define VK_LAUNCH_MAIL        180

#define VK_LAUNCH_MEDIA_SELECT  181
#define VK_LAUNCH_APP1          182
#define VK_LAUNCH_APP2          183
#define VK_RESERVED14           184
#define VK_RESERVED15           185
#define VK_OEM_1                186 //Colon/Semicolon (It can vary by keyboard though)
#define VK_OEM_PLUS             187 //Plus/Equals
#define VK_OEM_COMMA            188 //Comma/Less Than
#define VK_OEM_MINUS            189 //Underscore/Dash (Hyphen)
#define VK_OEM_PERIOD           190 //Period/Greater Than

#define VK_OEM_2                191 //Question Mark/Slash (It can vary by keyboard though)
#define VK_OEM_3                192 //Tilde/Acute (It can vary by keyboard though)
#define VK_RESERVED16           193
#define VK_RESERVED17           194
#define VK_RESERVED18           195
#define VK_RESERVED19           196
#define VK_RESERVED20           197
#define VK_RESERVED21           198
#define VK_RESERVED22           199
#define VK_RESERVED23           200

#define VK_RESERVED24           201
#define VK_RESERVED25           202
#define VK_RESERVED26           203
#define VK_RESERVED27           204
#define VK_RESERVED28           205
#define VK_RESERVED29           206
#define VK_RESERVED30           207
#define VK_RESERVED31           208
#define VK_RESERVED32           209
#define VK_RESERVED33           210

#define VK_RESERVED34           211
#define VK_RESERVED35           212
#define VK_RESERVED36           213
#define VK_RESERVED37           214
#define VK_RESERVED38           215
#define VK_UNASSIGNED18         216
#define VK_UNASSIGNED19         217
#define VK_UNASSIGNED20         218
#define VK_OEM_4                219 //Left Brace/Left Bracket (It can vary by keyboard though)
#define VK_OEM_5                220 //Backslash/Pipe (It can vary by keyboard though)

#define VK_OEM_6                221 //Right Brace/Right Bracket (It can vary by keyboard though)
#define VK_OEM_7                222 //Quote/Apostrophe (It can vary by keyboard though)
#define VK_OEM_8                223 //This can vary by keyboard
#define VK_RESERVED39           224
#define VK_OEM_RESERVED_6       225
#define VK_OEM_102              226 //<> Keys (Or \| on non-US 102-key keyboard)
#define VK_OEM_RESERVED_7       227
#define VK_OEM_RESERVED_8       228
#define VK_PROCESSKEY           229
#define VK_OEM_RESERVED_9       230

#define VK_PACKET               231 //Used to pass Unicode characters as if they were keystrokes. The VK_PACKET key is the low word of a 32-bit Virtual Key value used for non-keyboard input methods.
#define VK_UNASSIGNED21         232
#define VK_OEM_RESERVED_10      233
#define VK_OEM_RESERVED_11      234
#define VK_OEM_RESERVED_12      235
#define VK_OEM_RESERVED_13      236
#define VK_OEM_RESERVED_14      237
#define VK_OEM_RESERVED_15      238
#define VK_OEM_RESERVED_16      239
#define VK_OEM_RESERVED_17      240

#define VK_OEM_RESERVED_18      241
#define VK_OEM_RESERVED_19      242
#define VK_OEM_RESERVED_20      243
#define VK_OEM_RESERVED_21      244
#define VK_OEM_RESERVED_22      245
#define VK_OEM_RESERVED_23      246
#define VK_ATTN                 247
#define VK_CRSEL                248
#define VK_EXSEL                249
#define VK_EREOF                250

#define VK_PLAY                 251
#define VK_ZOOM                 252
#define VK_NONAME               253
#define VK_PA1                  254
#define VK_OEM_CLEAR            255
#endif

#endif
