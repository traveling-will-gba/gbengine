
//{{BLOCK(menu)

//======================================================================
//
//	menu, 256x160@4, 
//	Transparent palette entry: 17.
//	+ palette 16 entries, not compressed
//	+ 384 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x20 
//	Total size: 32 + 12288 + 1280 = 13600
//
//	Time-stamp: 2018-11-29, 08:56:12
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MENU_H
#define GRIT_MENU_H

#define menuTilesLen 12288
extern const unsigned int menuTiles[3072];

#define menuMapLen 1280
extern const unsigned short menuMap[640];

#define menuPalLen 32
extern const unsigned short menuPal[16];

#endif // GRIT_MENU_H

//}}BLOCK(menu)
