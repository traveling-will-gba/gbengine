
//{{BLOCK(menu)

//======================================================================
//
//	menu, 256x160@4, 
//	Transparent palette entry: 50.
//	+ palette 16 entries, not compressed
//	+ 458 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x20 
//	Total size: 32 + 14656 + 1280 = 15968
//
//	Time-stamp: 2018-11-29, 09:37:01
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MENU_H
#define GRIT_MENU_H

#define menuTilesLen 14656
extern const unsigned int menuTiles[3664];

#define menuMapLen 1280
extern const unsigned short menuMap[640];

#define menuPalLen 32
extern const unsigned short menuPal[16];

#endif // GRIT_MENU_H

//}}BLOCK(menu)
